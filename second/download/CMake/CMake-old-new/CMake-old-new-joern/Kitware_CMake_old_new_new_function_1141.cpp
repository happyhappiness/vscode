kwsys_stl::string SystemInformation::GetFamilyID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Family;
  return str.str();
}