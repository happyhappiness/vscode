  this->Makefile->AddDefinition("PACKAGE_FIND_NAME", this->Name.c_str());
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION",
                                this->Version.c_str());
  if(this->VersionCount >= 3)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionPatch);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_PATCH");
    }
  if(this->VersionCount >= 2)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionMinor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MINOR");
    }
  if(this->VersionCount >= 1)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MAJOR");
    }

  // Load the version check file.
  bool found = false;
