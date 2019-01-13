# QtWebBrowserKiosk

Usage: qtwebbrowserkiosk [options] [homeUrl]

This is a modified Qt Web Browser working in kiosk mode

Options:
  -h, --help               Displays this help.
  -v, --version            Displays version information.
  -c, --config <filepath>  Configuration INI-file

Arguments:
  homeUrl                  Open this URL and set as home page, optionally
 
****************************************************************************
****************************************************************************
   
Below is a sample config file
  
  
[application]
icon=qrc:///assets/icon/AppLogoColor.png
name=QtWebBrowserKiosk
organization=The Qt Company
organization-domain=www.qt.io
version=1.0.0

[browser]
homepage=www.qt.io
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

[view]
fixed-height=600
fixed-size=false
fixed-width=1024
fullscreen=true
maximized=false
minimal-height=200
minimal-width=320
