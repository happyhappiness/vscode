kwsys_stl::string SystemInformation::GetSteppingCode()
{ 
  kwsys_ios::ostringstream str;
  str << this->ChipID.Revision;
  return str.str();
}