    m_cmGeneratorChoice->SetStringSelection(generator);

    

    wxString str;

    //str.Printf("CMake %d.%d - %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());

    str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);



    SetTitle(str);

