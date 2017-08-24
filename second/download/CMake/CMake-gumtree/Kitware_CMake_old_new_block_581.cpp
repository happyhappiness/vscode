{
    char buf[64];
    sprintf(buf, "%u", this->VersionMinor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
    }