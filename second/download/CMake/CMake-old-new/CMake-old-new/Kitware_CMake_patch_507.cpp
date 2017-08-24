@@ -700,9 +700,7 @@ void CMakeSetupFrm::DoInitFrame(cmCommandLineInfo &cm, const wxString &fn)
     m_cmGeneratorChoice->SetStringSelection(generator);
     
     wxString str;
-    str.Printf("CMake %d.%d - %s", cmVersion::GetMajorVersion(),
-               cmVersion::GetMinorVersion(), 
-               cmVersion::GetReleaseVersion().c_str());
+    str.Printf("CMake %s", cmVersion::GetCMakeVersion());
     str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);
 
     SetTitle(str);
@@ -1696,7 +1694,6 @@ void CMakeSetupFrm::OnAboutClick( wxCommandEvent& event )
         generators.Add(i->c_str());
 
     wxString cmversion, cmsversion;
-//    cmversion.Printf("v%i.%i %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
     cmsversion.Printf("v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);
 
     dlg->SetAboutText(cmversion, cmsversion, generators);