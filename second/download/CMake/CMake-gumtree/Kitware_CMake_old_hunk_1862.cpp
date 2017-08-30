  this->LoadFromRegistry();

  // try to load the cmake cache from disk

  this->LoadCacheFromDiskToGUI();

  // Set the version number

  char tmp[1024];

  sprintf(tmp,"Version %s", cmMakefile::GetVersion());

