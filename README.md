# QtWebBrowserKiosk

Usage: ./qtwebbrowserkiosk [options] [startUrl]
This is a modified Qt Web Browser working in kiosk mode

Options:
  -h, --help               Displays this help.
  -v, --version            Displays version information.
  -c, --config <filepath>  Configuration INI-file
  -r, --reset              Deletes saved config file and either (i) replaces
                           with the data of config file passed with [config]
                           option or (ii) creates a config file with default
                           settings

Arguments:
  startUrl                 Open this URL, optionally (else the homepage in
                           config file will be used)
 
****************************************************************************
****************************************************************************
   
Below is a sample config file
  
  
[application]
icon=qrc:///qml/assets/icons/AppLogoColor.png
name=QtWebBrowserKiosk
organization=The Qt Company
organization-domain=http://www.qt.io
version=1.0.0

[browser]
homepage=http://www.qt.io
ignore_ssl_errors=true
javascript=true
javascript_can_open_windows=false
plugins=true
webgl=false

[localstorage]
enable=false

[proxy]
auth=false
enable=false
host=proxy.example.com
password=password
port=3128
system=true
username=username

[video]
playlist=qrc:///qml/assets/videos/Qt.m4v
timeout=5000

[view]
fixed-height=600
fixed-size=false
fixed-width=1024
fullscreen=true
maximized=false
minimal-height=200
minimal-width=320
show_keyboard=true