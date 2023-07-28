# Windows Porting

## Qwt Installation

### Arch Linux

```sh
sudo pacman -Syu
sudo pacman -S qwt
```

### Windows

Download source package:
- https:\\sourceforge.net\projects\qwt\files\qwt\

First, add **C:\Qt\Qt5.XX.X\Tools\mingwXX_64\bin** to PATH (adjust X with proper version number).

Next extract downloaded package and comment these lines:

```
QWT_CONFIG     += QwtDesigner
QWT_CONFIG     += QwtExamples
QWT_CONFIG     += QwtPlayground
QWT_CONFIG     += QwtTests
```

Then open "All Programs -> Qt -> Command Prompt", run command

```sh
cd qwt-6.2.0

qmake qwt.pro
```

Then compile the library

```sh
mingw32-make -j4
```

If succesfully compiled, install the library

```sh
mingw32-make install
```

which will install library in **C:\Qwt-6.2.0**.

Lastly, you can optionally delete source folder.

## Qwt Project

Include code snippet below into pro file to use Qwt:

```make
CONFIG += qwt

unix: INCLUDEPATH += \usr\include\qwt\
unix: LIBS += -lqwt

win32: INCLUDEPATH += C:\Qwt-6.2.0\include
win32: LIBS += C:\Qwt-6.2.0\lib\qwt.dll
```

## Deployment

### Shared Libraries Sources
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5Gui.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5Core.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5OpenGL.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5SerialPort.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5Svg.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\Qt5Widgets.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\libgcc_s_seh-1.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\libstdc++-6.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\bin\libwinpthread-1.dll
- C:\Qt\Qt5.XX.X\5.XX.X\mingwXX_64\plugins\platforms\qwindows.dll
- C:\Qwt-6.2.0\lib\qwt.dll

### Intaller Building

Download NSIS program:
- https:\\nsis.sourceforge.io\Download

Create a NSIS script named **installer.nsi** inside binary and libraries folder:

```
!define APPNAME "EcuPNM"
OutFile "${APPNAME}_Installer.exe"
InstallDir "$PROGRAMFILES64\${APPNAME}"

Section
	SetOutPath "$INSTDIR"
	File ecu_view.exe
	File Qt5Core.dll
	File Qt5Gui.dll
	File Qt5OpenGL.dll
	File Qt5SerialPort.dll
	File Qt5Svg.dll
	File Qt5Widgets.dll
	File libgcc_s_seh-1.dll
	File libstdc++-6.dll
	File libwinpthread-1.dll
	File qwt.dll
	
	CreateDirectory "$INSTDIR\platforms"
	SetOutPath "$INSTDIR\platforms"
	File platforms\qwindows.dll
	
	WriteUninstaller "$INSTDIR\uninstall.exe"
	
	# C:\Users\Administrator\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\EcuPNM
	CreateDirectory "$SMPROGRAMS\${APPNAME}"
	CreateShortcut "$SMPROGRAMS\${APPNAME}\${APPNAME}.lnk" "$INSTDIR\ecu_view.exe"
	CreateShortcut "$SMPROGRAMS\${APPNAME}\uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section "uninstall"
	Delete "$SMPROGRAMS\${APPNAME}\${APPNAME}.lnk"
	Delete "$SMPROGRAMS\${APPNAME}\uninstall.lnk"
	
	Delete "$INSTDIR\ecu_view.exe"
	Delete "$INSTDIR\Qt5Core.dll"
	Delete "$INSTDIR\Qt5Gui.dll"
	Delete "$INSTDIR\Qt5OpenGL.dll"
	Delete "$INSTDIR\Qt5SerialPort.dll"
	Delete "$INSTDIR\Qt5Svg.dll"
	Delete "$INSTDIR\Qt5Widgets.dll"
	Delete "$INSTDIR\libgcc_s_seh-1.dll"
	Delete "$INSTDIR\libstdc++-6.dll"
	Delete "$INSTDIR\libwinpthread-1.dll"
	Delete "$INSTDIR\qwt.dll"
	Delete "$INSTDIR\platforms\qwindows.dll"
	
	Delete "$INSTDIR\uninstall.exe"
	
	RMDir "$SMPROGRAMS\${APPNAME}"
	RMDir "$INSTDIR\platforms"
    RMDir "$INSTDIR"
SectionEnd
``` 

Make sure all files and folders in same folder with script.
Then right-click the script and click **Compile Script**.