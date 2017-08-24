{
    char buf[64];
    sprintf(buf, "%u", this->VersionPatch);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
    }