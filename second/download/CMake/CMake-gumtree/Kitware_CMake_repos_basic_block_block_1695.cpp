{
    // Retrieve cache information.
    if (!RetrieveCPUCacheDetails()) {
      RetrieveClassicalCPUCacheDetails();
    }

    // Retrieve the extended CPU details.
    if (!RetrieveExtendedCPUIdentity()) {
      RetrieveClassicalCPUIdentity();
    }

    RetrieveExtendedCPUFeatures();
    RetrieveCPUPowerManagement();

    // Now attempt to retrieve the serial number (if possible).
    RetrieveProcessorSerialNumber();
  }