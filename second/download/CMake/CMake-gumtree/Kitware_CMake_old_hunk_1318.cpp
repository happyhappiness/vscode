    ver += "_FIND_VERSION";

    this->Makefile->AddDefinition(ver.c_str(), this->Version.c_str());

    char buf[64];

    switch(this->VersionCount)

      {

      case 3:

        {

        sprintf(buf, "%u", this->VersionPatch);

        this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);

        } // no break

      case 2:

        {

        sprintf(buf, "%u", this->VersionMinor);

        this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);

        } // no break

      case 1:

        {

        sprintf(buf, "%u", this->VersionMajor);

        this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);

        } // no break

      default: break;

      }



    // Tell the module whether an exact version has been requested.

    std::string exact = this->Name;

