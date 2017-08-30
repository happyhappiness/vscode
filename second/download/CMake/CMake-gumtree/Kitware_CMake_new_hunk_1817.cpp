    

  // Set the version number

  char tmp[1024];

  sprintf(tmp,"Version %d.%d - %s", cmake::GetMajorVersion(),

          cmake::GetMinorVersion(), cmake::GetReleaseVersion());

  SetDlgItemText(IDC_CMAKE_VERSION, tmp);

  this->UpdateData(FALSE);

  return TRUE;  // return TRUE  unless you set the focus to a control

