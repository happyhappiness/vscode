@@ -46,6 +46,7 @@
 #include "aboutdlg.h"
 
 // cmake includes
+#include "../cmVersion.h"
 #include "../cmListFileCache.h"
 #include "../cmCacheManager.h"
 #include "../cmGlobalGenerator.h"
@@ -699,7 +700,9 @@ void CMakeSetupFrm::DoInitFrame(cmCommandLineInfo &cm, const wxString &fn)
     m_cmGeneratorChoice->SetStringSelection(generator);
     
     wxString str;
-    //str.Printf("CMake %d.%d - %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
+    str.Printf("CMake %d.%d - %s", cmVersion::GetMajorVersion(),
+               cmVersion::GetMinorVersion(), 
+               cmVersion::GetReleaseVersion().c_str());
     str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);
 
     SetTitle(str);
@@ -1693,7 +1696,7 @@ void CMakeSetupFrm::OnAboutClick( wxCommandEvent& event )
         generators.Add(i->c_str());
 
     wxString cmversion, cmsversion;
-    cmversion.Printf("v%i.%i %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
+//    cmversion.Printf("v%i.%i %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
     cmsversion.Printf("v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);
 
     dlg->SetAboutText(cmversion, cmsversion, generators);