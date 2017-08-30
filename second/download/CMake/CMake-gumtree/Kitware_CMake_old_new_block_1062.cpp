{
        sprintf(buf, "%u", this->VersionPatch);
        this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
        }