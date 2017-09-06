kwsys_stl::string SystemInformation::GetTypeID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Type;
  return str.str();
}