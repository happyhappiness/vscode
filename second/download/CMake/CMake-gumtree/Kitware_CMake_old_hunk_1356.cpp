        generators.Add(i->c_str());

    wxString cmversion, cmsversion;
    cmversion.Printf("v%i.%i %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
    cmsversion.Printf("v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);

    dlg->SetAboutText(cmversion, cmsversion, generators);