void cmFindPackageCommand::SetModuleVariables(const std::string& components)
{
  // Store the list of components.
  std::string components_var = this->Name + "_FIND_COMPONENTS";
  this->Makefile->AddDefinition(components_var.c_str(), components.c_str());
   
  if(this->Quiet)
    {
    // Tell the module that is about to be read that it should find
    // quietly.
    std::string quietly = this->Name;
    quietly += "_FIND_QUIETLY";
    this->Makefile->AddDefinition(quietly.c_str(), "1");
    }

  if(this->Required)
    {
    // Tell the module that is about to be read that it should report
    // a fatal error if the package is not found.
    std::string req = this->Name;
    req += "_FIND_REQUIRED";
    this->Makefile->AddDefinition(req.c_str(), "1");
    }

  if(!this->Version.empty())
    {
    // Tell the module that is about to be read what version of the
    // package has been requested.
    std::string ver = this->Name;
    ver += "_FIND_VERSION";
    this->Makefile->AddDefinition(ver.c_str(), this->Version.c_str());
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionMinor);
    this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
    sprintf(buf, "%u", this->VersionPatch);
    this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
    sprintf(buf, "%u", this->VersionTweak);
    this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
    sprintf(buf, "%u", this->VersionCount);
    this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);

    // Tell the module whether an exact version has been requested.
    std::string exact = this->Name;
    exact += "_FIND_VERSION_EXACT";
    this->Makefile->AddDefinition(exact.c_str(),
                                  this->VersionExact? "1":"0");
   }
}