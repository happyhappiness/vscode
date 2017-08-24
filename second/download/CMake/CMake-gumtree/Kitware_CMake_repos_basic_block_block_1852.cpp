{
    int id = atoi(idc.c_str());
    PhysicalIDs.insert(id);
    idc = this->ExtractValueFromCpuInfoFile(buffer, "physical id",
                                            this->CurrentPositionInFile + 1);
  }