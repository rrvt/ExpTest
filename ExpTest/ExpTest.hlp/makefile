

ExpTest.chm : *.htm ExpTest.hhp ExpTest.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" ExpTest


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F ExpTest.chm


Release/ExpTest.chm : ExpTest.chm
  copy $(MAKEDIR)\ExpTest.chm  $(MAKEDIR)\..\Release\ExpTest.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del ExpTest.chm
  cd $(MAKEDIR)


Debug/ExpTest.chm : ExpTest.chm
  copy $(MAKEDIR)\ExpTest.chm  $(MAKEDIR)\..\Debug\ExpTest.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del ExpTest.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/ExpTest.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/ExpTest.chm


