  this->ChipID.Family = 0; 
 
  // Chip Vendor
  this->ChipID.Vendor = "Sun";
  this->FindManufacturer();
  
  // Chip Model
  this->ChipID.ProcessorName = this->ParseValueFromKStat("-s cpu_type");
  this->ChipID.Model = 0;

  // Cache size
