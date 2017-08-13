    // package has been requested.
    std::string ver = this->Name;
    ver += "_FIND_VERSION";
    this->AddFindDefinition(ver.c_str(), this->Version.c_str());
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->AddFindDefinition((ver+"_MAJOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionMinor);
    this->AddFindDefinition((ver+"_MINOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionPatch);
    this->AddFindDefinition((ver+"_PATCH").c_str(), buf);
    sprintf(buf, "%u", this->VersionTweak);
    this->AddFindDefinition((ver+"_TWEAK").c_str(), buf);
    sprintf(buf, "%u", this->VersionCount);
    this->AddFindDefinition((ver+"_COUNT").c_str(), buf);

    // Tell the module whether an exact version has been requested.
    std::string exact = this->Name;
    exact += "_FIND_VERSION_EXACT";
    this->AddFindDefinition(exact.c_str(), this->VersionExact? "1":"0");
   }
}

