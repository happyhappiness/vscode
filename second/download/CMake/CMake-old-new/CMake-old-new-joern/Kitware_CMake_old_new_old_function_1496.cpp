BOOL CMakeSetupDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  this->DragAcceptFiles(true);

  // Add "Create shortcut" menu item to system menu.

  // IDM_CREATESHORTCUT must be in the system command range.
  ASSERT((IDM_CREATESHORTCUT & 0xFFF0) == IDM_CREATESHORTCUT);
  ASSERT(IDM_CREATESHORTCUT < 0xF000);

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
    {
    CString strCreateShortcutMenu;
    strCreateShortcutMenu.LoadString(IDS_CREATESHORTCUT);
    if (!strCreateShortcutMenu.IsEmpty())
      {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, 
                           IDM_CREATESHORTCUT, 
                           strCreateShortcutMenu);
      }

    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
      {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, 
                           IDM_ABOUTBOX, 
                           strAboutMenu);
      }
    }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon
  // Load source and build dirs from registry
  this->LoadFromRegistry();
  std::vector<std::string> names;
  this->m_CMakeInstance->GetRegisteredGenerators(names);
  for(std::vector<std::string>::iterator i = names.begin();
      i != names.end(); ++i)
    {
    m_GeneratorChoice.AddString(i->c_str());
    }
  if (m_GeneratorChoiceString == _T("")) 
    {
    m_GeneratorChoiceString = "Visual Studio 6";
    }

  // try to load the cmake cache from disk
  this->LoadCacheFromDiskToGUI();
  m_WhereBuildControl.LimitText(2048);
  m_WhereSourceControl.LimitText(2048);
  m_GeneratorChoice.LimitText(2048);
    
  // Set the version number
  char tmp[1024];
  sprintf(tmp,"Version %d.%d - %s", cmake::GetMajorVersion(),
          cmake::GetMinorVersion(), cmake::GetReleaseVersion());
  SetDlgItemText(IDC_CMAKE_VERSION, tmp);
  SetDlgItemText(IDC_PROGRESS, "");
  this->UpdateData(FALSE);
  return TRUE;  // return TRUE  unless you set the focus to a control
}