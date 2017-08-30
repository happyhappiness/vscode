    

  // Set the version number

  char tmp[1024];

  sprintf(tmp,"Version %d.%d - %s", cmMakefile::GetMajorVersion(),

          cmMakefile::GetMinorVersion(), cmMakefile::GetReleaseVersion());

  SetDlgItemText(IDC_CMAKE_VERSION, tmp);

  this->UpdateData(FALSE);

  return TRUE;  // return TRUE  unless you set the focus to a control

