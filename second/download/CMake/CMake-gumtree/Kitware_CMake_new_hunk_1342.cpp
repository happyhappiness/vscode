}

//----------------------------------------------------------------------------
bool cmFindPackageCommand::FindConfigFileToLoad(std::string const& dir,
                                                std::string& file)
{
  if(this->FileFound.empty())
    {
    // The file location was cached.  Look for the correct file.
    return this->FindConfigFile(dir, file);
    }
  else
    {
    // The file location was just found during this call.
    // Use the file found without searching again.
    file = this->FileFound;
    return true;
    }
}

//----------------------------------------------------------------------------
bool cmFindPackageCommand::CheckVersion(std::string const& config_file)
{
  // Get the filename without the .cmake extension.
  std::string::size_type pos = config_file.rfind('.');
  std::string version_file_base = config_file.substr(0, pos);

  // Look for foo-config-version.cmake
  std::string version_file = version_file_base;
  version_file += "-version.cmake";
  if(cmSystemTools::FileExists(version_file.c_str(), true))
    {
    return this->CheckVersionFile(version_file);
    }

  // Look for fooConfigVersion.cmake
  version_file = version_file_base;
  version_file += "Version.cmake";
  if(cmSystemTools::FileExists(version_file.c_str(), true))
    {
    return this->CheckVersionFile(version_file);
    }

  // If no version was requested a versionless package is acceptable.
  if(this->Version.empty())
    {
    return true;
    }

  // No version file found.  Assume the version is incompatible.
  return false;
}

//----------------------------------------------------------------------------
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
  if(this->VersionCount >= 3)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionPatch);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_PATCH", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_PATCH");
    }
  if(this->VersionCount >= 2)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionMinor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MINOR", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MINOR");
    }
  if(this->VersionCount >= 1)
    {
    char buf[64];
    sprintf(buf, "%u", this->VersionMajor);
    this->Makefile->AddDefinition("PACKAGE_FIND_VERSION_MAJOR", buf);
    }
  else
    {
    this->Makefile->RemoveDefinition("PACKAGE_FIND_VERSION_MAJOR");
    }

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
      this->VersionFoundCount =
        sscanf(this->VersionFound.c_str(), "%u.%u.%u",
               &parsed_major, &parsed_minor, &parsed_patch);
      switch(this->VersionFoundCount)
        {
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

//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
#include <cmsys/Directory.hxx>
#include <cmsys/Glob.hxx>
#include <cmsys/String.h>