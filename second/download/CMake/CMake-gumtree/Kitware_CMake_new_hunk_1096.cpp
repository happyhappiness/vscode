    m_cmGeneratorChoice->SetStringSelection(generator);
    
    wxString str;
    str.Printf("CMake %d.%d - %s", cmVersion::GetMajorVersion(),
               cmVersion::GetMinorVersion(), 
               cmVersion::GetReleaseVersion().c_str());
    str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);

    SetTitle(str);
