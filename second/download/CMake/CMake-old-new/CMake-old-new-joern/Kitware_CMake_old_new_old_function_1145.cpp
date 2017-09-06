void CMakeSetupFrm::OnAboutClick( wxCommandEvent& event )
{
    CMAboutDlg *dlg = new CMAboutDlg(this);
    
    wxArrayString generators;
    std::vector<std::string> names; 
    m_cmake->GetRegisteredGenerators(names);
    for(std::vector<std::string>::iterator i = names.begin(); i != names.end(); ++i)
        generators.Add(i->c_str());

    wxString cmversion, cmsversion;
    cmversion.Printf("v%i.%i %s", cmake::GetMajorVersion(), cmake::GetMinorVersion(), cmake::GetReleaseVersion());
    cmsversion.Printf("v%i.%i%s", CMAKEGUI_MAJORVER, CMAKEGUI_MINORVER, CMAKEGUI_ADDVER);

    dlg->SetAboutText(cmversion, cmsversion, generators);

    dlg->ShowModal();
    dlg->Destroy();
}