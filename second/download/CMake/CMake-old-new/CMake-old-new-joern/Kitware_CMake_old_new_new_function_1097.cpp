void cmFindPackageCommand::StoreVersionFound()
{
  // Store the whole version string.
  std::string ver = this->Name;
  ver += "_VERSION";
  if(this->VersionFound.empty())
    {
    this->Makefile->RemoveDefinition(ver.c_str());
    }
  else
    {
    this->Makefile->AddDefinition(ver.c_str(), this->VersionFound.c_str());
    }

  // Store the portions that could be parsed.
  char buf[64];
  switch(this->VersionFoundCount)
    {
    case 3:
      {
      sprintf(buf, "%u", this->VersionFoundPatch);
      this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
      } // no break
    case 2:
      {
      sprintf(buf, "%u", this->VersionFoundMinor);
      this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
      } // no break
    case 1:
      {
      sprintf(buf, "%u", this->VersionFoundMajor);
      this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
      } // no break
    default: break;
    }
}