kwsys_stl::string SystemInformation::GetModelID()
{
  kwsys_ios::ostringstream str;
  str << this->ChipID.Model;
  return str.str();
}