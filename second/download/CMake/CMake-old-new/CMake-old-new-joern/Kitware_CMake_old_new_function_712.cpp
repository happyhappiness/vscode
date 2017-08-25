const char * SystemInformation::GetModelID()
{
  char * temp = new char[32];
  sprintf(temp,"%d",this->ChipID.Model);
  return temp;
}