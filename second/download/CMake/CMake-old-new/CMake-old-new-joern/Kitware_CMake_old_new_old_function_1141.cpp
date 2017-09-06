const char * SystemInformation::GetFamilyID()
{
  char * temp = new char[32];
  sprintf(temp,"%d",this->ChipID.Family);
  return temp;
}