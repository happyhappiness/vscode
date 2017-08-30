  this->ChipID.Family = 0; 

 

  // Chip Vendor

  strcpy(this->ChipID.Vendor,"Sun");

  this->FindManufacturer();

  

  // Chip Model

  sprintf(this->ChipID.ProcessorName,"%s",this->ParseValueFromKStat("-s cpu_type").c_str());

  this->ChipID.Model = 0;



  // Cache size

