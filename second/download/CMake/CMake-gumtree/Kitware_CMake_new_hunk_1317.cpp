    // package has been requested.
    std::string ver = this->Name;
    ver += "_FIND_VERSION";
    this->AddFindDefinition(ver.c_str(), this->Version.c_str());
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->AddFindDefinition((ver+"_MAJOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionMinor);
    this->AddFindDefinition((ver+"_MINOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionPatch);
    this->AddFindDefinition((ver+"_PATCH").c_str(), buf);
    sprintf(buf, "%u", this->VersionTweak);
    this->AddFindDefinition((ver+"_TWEAK").c_str(), buf);
    sprintf(buf, "%u", this->VersionCount);
    this->AddFindDefinition((ver+"_COUNT").c_str(), buf);

    // Tell the module whether an exact version has been requested.
    std::string exact = this->Name;
    exact += "_FIND_VERSION_EXACT";
    this->AddFindDefinition(exact.c_str(), this->VersionExact? "1":"0");
   }
}

//----------------------------------------------------------------------------
void cmFindPackageCommand::AddFindDefinition(const char* var, const char* val)
{
  if(const char* old = this->Makefile->GetDefinition(var))
    {
    this->OriginalDefs[var].exists = true;
    this->OriginalDefs[var].value = old;
    }
  else
    {
    this->OriginalDefs[var].exists = false;
    }
  this->Makefile->AddDefinition(var, val);
}

//----------------------------------------------------------------------------
void cmFindPackageCommand::RestoreFindDefinitions()
{
  for(std::map<cmStdString, OriginalDef>::iterator
        i = this->OriginalDefs.begin(); i != this->OriginalDefs.end(); ++i)
    {
    OriginalDef const& od = i->second;
    if(od.exists)
      {
      this->Makefile->AddDefinition(i->first.c_str(), od.value.c_str());
      }
    else
      {
      this->Makefile->RemoveDefinition(i->first.c_str());
      }
    }
}

//----------------------------------------------------------------------------
bool cmFindPackageCommand::FindModule(bool& found)
