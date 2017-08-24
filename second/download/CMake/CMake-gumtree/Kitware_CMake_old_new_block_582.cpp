{
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
    }