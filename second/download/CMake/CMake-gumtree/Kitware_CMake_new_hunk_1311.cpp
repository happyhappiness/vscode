        generators.Add(i->c_str());

    wxString cmversion, cmsversion;
    cmsversion.Printf("v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);

    dlg->SetAboutText(cmversion, cmsversion, generators);