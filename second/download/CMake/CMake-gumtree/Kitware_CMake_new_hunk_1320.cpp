    this->Makefile->AddDefinition(ver.c_str(), this->VersionFound.c_str());

    }



  // Store the version components.

  char buf[64];

  sprintf(buf, "%u", this->VersionFoundMajor);

  this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);

  sprintf(buf, "%u", this->VersionFoundMinor);

  this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);

  sprintf(buf, "%u", this->VersionFoundPatch);

  this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);

  sprintf(buf, "%u", this->VersionFoundTweak);

  this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);

  sprintf(buf, "%u", this->VersionFoundCount);

  this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);

}



//----------------------------------------------------------------------------
