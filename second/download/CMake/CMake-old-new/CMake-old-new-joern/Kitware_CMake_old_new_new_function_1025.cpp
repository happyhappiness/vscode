bool SystemInformationImplementation::QuerySolarisInfo()
{
  // Parse values
  this->NumberOfPhysicalCPU = static_cast<unsigned int>(
    atoi(this->ParseValueFromKStat("-n syste_misc -s ncpus").c_str()));
  this->NumberOfLogicalCPU = this->NumberOfPhysicalCPU;
  
  if(this->NumberOfPhysicalCPU!=0)
    {
    this->NumberOfLogicalCPU /= this->NumberOfPhysicalCPU;
    }

  this->CPUSpeedInMHz = static_cast<float>(atoi(this->ParseValueFromKStat("-s clock_MHz").c_str()));

  // Chip family
  this->ChipID.Family = 0; 
 
  // Chip Vendor
  this->ChipID.Vendor = "Sun";
  this->FindManufacturer();
  
  // Chip Model
  this->ChipID.ProcessorName = this->ParseValueFromKStat("-s cpu_type");
  this->ChipID.Model = 0;

  // Cache size
  this->Features.L1CacheSize = 0; 
  this->Features.L2CacheSize = 0;  

  char* tail;
  unsigned long totalMemory =
       strtoul(this->ParseValueFromKStat("-s physmem").c_str(),&tail,0);
  this->TotalPhysicalMemory = totalMemory/1024;
  this->TotalPhysicalMemory *= 8192;
  this->TotalPhysicalMemory /= 1024;

  // Undefined values (for now at least)
  this->TotalVirtualMemory = 0;
  this->AvailablePhysicalMemory = 0;
  this->AvailableVirtualMemory = 0;

  return true;
}