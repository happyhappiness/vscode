{
      sprintf(buf, "%u", this->VersionFoundPatch);
      this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
      }