  ver += "_VERSION";

  if(this->VersionFound.empty())

    {

    this->Makefile->RemoveDefinition(ver);

    }

  else

    {

    this->Makefile->AddDefinition(ver, this->VersionFound.c_str());

    }



  // Store the version components.

  char buf[64];

  sprintf(buf, "%u", this->VersionFoundMajor);

  this->Makefile->AddDefinition(ver+"_MAJOR", buf);

  sprintf(buf, "%u", this->VersionFoundMinor);

  this->Makefile->AddDefinition(ver+"_MINOR", buf);

  sprintf(buf, "%u", this->VersionFoundPatch);

  this->Makefile->AddDefinition(ver+"_PATCH", buf);

  sprintf(buf, "%u", this->VersionFoundTweak);

  this->Makefile->AddDefinition(ver+"_TWEAK", buf);

  sprintf(buf, "%u", this->VersionFoundCount);

  this->Makefile->AddDefinition(ver+"_COUNT", buf);

}



//----------------------------------------------------------------------------
