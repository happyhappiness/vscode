    m_cmGeneratorChoice->SetStringSelection(generator);

    

    wxString str;

    str.Printf("CMake %s", cmVersion::GetCMakeVersion());

    str.Printf("CMakeSetup v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);



    SetTitle(str);

