}



/** Return the type ID of the CPU */

const char * SystemInformation::GetTypeID()

{

  char * temp = new char[32];

  sprintf(temp,"%d",this->ChipID.Type);

  return temp;

}



/** Return the family of the CPU present */

const char * SystemInformation::GetFamilyID()

{

  char * temp = new char[32];

  sprintf(temp,"%d",this->ChipID.Family);

  return temp;

}



// Return the model of CPU present */

const char * SystemInformation::GetModelID()

{

  char * temp = new char[32];

  sprintf(temp,"%d",this->ChipID.Model);

  return temp;

}



/** Return the stepping code of the CPU present. */

const char * SystemInformation::GetSteppingCode()

{

  char * temp = new char[32];

  sprintf(temp,"%d",this->ChipID.Revision);

  return temp;

}



/** Return the stepping code of the CPU present. */

