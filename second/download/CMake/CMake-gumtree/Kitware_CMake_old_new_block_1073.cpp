{
      sprintf(buf, "%u", this->VersionFoundMinor);
      this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
      }