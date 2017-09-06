bool cmFindPackageCommand::CheckVersionFile(std::string const& version_file)
{
  // The version file will be loaded in an isolated scope.
  this->Makefile->PushScope();

  // Clear the output variables.
  this->Makefile->RemoveDefinition("PACKAGE_VERSION");
  this->Makefile->RemoveDefinition("PACKAGE_VERSION_COMPATIBLE");
  this->Makefile->RemoveDefinition("PACKAGE_VERSION_EXACT");

  // Set the input variables.
  this->Makefile->AddDefinition("PACKAGE_FIND_NAME", this->Name.c_str());
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION",
                                this->Version.c_str());
  char buf[64];
  sprintf(buf, "%u", this->VersionMajor);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
  sprintf(buf, "%u", this->VersionMinor);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
  sprintf(buf, "%u", this->VersionPatch);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
  sprintf(buf, "%u", this->VersionTweak);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_TWEAK", buf);
  sprintf(buf, "%u", this->VersionCount);
  this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_COUNT", buf);

  // Load the version check file.
  bool found = false;
  if(this->ReadListFile(version_file.c_str()))
    {
    // Check the output variables.
    found = this->Makefile->IsOn("PACKAGE_VERSION_EXACT");
    if(!found && !this->VersionExact)
      {
      found = this->Makefile->IsOn("PACKAGE_VERSION_COMPATIBLE");
      }
    if(found || this->Version.empty())
      {
      // Get the version found.
      this->VersionFound =
        this->Makefile->GetSafeDefinition("PACKAGE_VERSION");

      // Try to parse the version number and store the results that were
      // successfully parsed.
      unsigned int parsed_major;
      unsigned int parsed_minor;
      unsigned int parsed_patch;
      unsigned int parsed_tweak;
      this->VersionFoundCount =
        sscanf(this->VersionFound.c_str(), "%u.%u.%u.%u",
               &parsed_major, &parsed_minor,
               &parsed_patch, &parsed_tweak);
      switch(this->VersionFoundCount)
        {
        case 4: this->VersionFoundTweak = parsed_tweak; // no break!
        case 3: this->VersionFoundPatch = parsed_patch; // no break!
        case 2: this->VersionFoundMinor = parsed_minor; // no break!
        case 1: this->VersionFoundMajor = parsed_major; // no break!
        default: break;
        }
      }
    }

  // Restore the original scope.
  this->Makefile->PopScope();

  // Succeed if the version was found or no version was requested.
  return found || this->Version.empty();
}