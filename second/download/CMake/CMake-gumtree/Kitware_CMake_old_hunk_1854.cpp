  SetIcon(m_hIcon, FALSE);		// Set small icon

  // Load source and build dirs from registry

  this->LoadFromRegistry();

  // try to load the cmake cache from disk

  this->LoadCacheFromDiskToGUI();

  m_WhereBuildControl.LimitText(2048);

  m_WhereSourceControl.LimitText(2048);

  // Set the version number

  char tmp[1024];

  sprintf(tmp,"Version %d.%d", cmMakefile::GetMajorVersion(),

