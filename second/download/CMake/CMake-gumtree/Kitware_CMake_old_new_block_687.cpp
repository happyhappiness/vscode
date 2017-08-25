{
        sprintf(buf, "%u", this->VersionMinor);
        this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
        }