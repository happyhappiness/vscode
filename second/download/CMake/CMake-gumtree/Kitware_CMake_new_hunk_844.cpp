    // package has been requested.

    std::string ver = this->Name;

    ver += "_FIND_VERSION";

    this->AddFindDefinition(ver, this->Version.c_str());

    char buf[64];

    sprintf(buf, "%u", this->VersionMajor);

    this->AddFindDefinition(ver+"_MAJOR", buf);

    sprintf(buf, "%u", this->VersionMinor);

    this->AddFindDefinition(ver+"_MINOR", buf);

    sprintf(buf, "%u", this->VersionPatch);

    this->AddFindDefinition(ver+"_PATCH", buf);

    sprintf(buf, "%u", this->VersionTweak);

    this->AddFindDefinition(ver+"_TWEAK", buf);

    sprintf(buf, "%u", this->VersionCount);

    this->AddFindDefinition(ver+"_COUNT", buf);



    // Tell the module whether an exact version has been requested.

    std::string exact = this->Name;

    exact += "_FIND_VERSION_EXACT";

    this->AddFindDefinition(exact, this->VersionExact? "1":"0");

   }

}



