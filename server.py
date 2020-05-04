# Run a local webserveer that monitors the state of Zoom.
# Launch or kill it according to received HTTP payloads.
import psutil
import time
import os
import signal
import subprocess
from http.server import BaseHTTPRequestHandler, HTTPServer

# Check if Zoom is running
def checkProcessState(pName):
    for proc in psutil.process_iter():
        try:
            if pName.lower() in proc.name().lower():
                return True
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass
    return False;

# Find the PID of Zoom
def getProcessId(pName):
    for proc in psutil.process_iter():
        try:
            if pName.lower() in proc.name().lower():
                return proc.pid
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass
    return False;

# Drive the webserver
class runServer(BaseHTTPRequestHandler):
  def do_GET(self):
    self.send_response(200)
    self.send_header('Content-type', 'text/html')
    self.end_headers()

    zoomState=checkProcessState('zoom')
    if zoomState:
      self.wfile.write(b"Yes")
    else:
      self.wfile.write(b"No")

    if self.path == "/killzoom":
      zoomPid = getProcessId('zoom')
      if zoomPid:
        subprocess.call(["/usr/bin/pkill", "zoom"])

    if self.path == "/spawnzoom":
      zoomPid = getProcessId('zoom')

      if not zoomPid:
        proc = subprocess.Popen(
          ["/usr/bin/open", "-W", "-n", "-a", "/Applications/zoom.us.app"],
          stdout=subprocess.PIPE,
          stderr=subprocess.STDOUT)


# Run the webserver
httpd = HTTPServer(("0.0.0.0", 8000), runServer)
try:
    httpd.serve_forever()
except:
    KeyboardInterrupt
