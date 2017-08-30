{
      sprintf(buf, "%u", this->VersionFoundMajor);
      this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
      }