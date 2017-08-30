    ver += "_FIND_VERSION";
    this->Makefile->AddDefinition(ver.c_str(), this->Version.c_str());
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionMinor);
    this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionPatch);
    this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
    sprintf(buf, "%u", this->VersionTweak);
    this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
    sprintf(buf, "%u", this->VersionCount);
    this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);

    // Tell the module whether an exact version has been requested.
    std::string exact = this->Name;
