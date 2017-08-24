}

/** Return the type ID of the CPU */
kwsys_stl::string SystemInformation::GetTypeID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Type;
  return str.str();
}

/** Return the family of the CPU present */
kwsys_stl::string SystemInformation::GetFamilyID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Family;
  return str.str();
}

// Return the model of CPU present */
kwsys_stl::string SystemInformation::GetModelID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Model;
  return str.str();
}

/** Return the stepping code of the CPU present. */
kwsys_stl::string SystemInformation::GetSteppingCode()
{ 
  kwsys_ios::ostringstream str;
  str << this->ChipID.Revision;
  return str.str();
}

/** Return the stepping code of the CPU present. */
