{
      this->ChipID.Vendor = "IBM";
      len = sizeof(this->ChipID.Family);
      err = sysctlbyname("hw.cputype", &this->ChipID.Family, &len, NULL, 0);
      len = sizeof(this->ChipID.Model);
      err = sysctlbyname("hw.cpusubtype", &this->ChipID.Model, &len, NULL, 0);
      this->FindManufacturer();
    }