{
        sprintf(buf, "%u", this->VersionMajor);
        this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
        }