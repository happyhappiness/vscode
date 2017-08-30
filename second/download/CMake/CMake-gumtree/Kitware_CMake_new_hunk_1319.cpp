  this->Makefile->AddDefinition("PACKAGE_FIND_NAME", this->Name.c_str());
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION",
                                this->Version.c_str());
  char buf[64];
  sprintf(buf, "%u", this->VersionMajor);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
  sprintf(buf, "%u", this->VersionMinor);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
  sprintf(buf, "%u", this->VersionPatch);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
  sprintf(buf, "%u", this->VersionTweak);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_TWEAK", buf);
  sprintf(buf, "%u", this->VersionCount);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_COUNT", buf);

  // Load the version check file.
  bool found = false;
