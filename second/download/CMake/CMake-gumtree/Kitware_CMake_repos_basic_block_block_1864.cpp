(procLimitEnvVarValue) {
      SystemInformation::LongLong procLimit =
        atoLongLong(procLimitEnvVarValue);
      if (procLimit > 0) {
        memAvail = min(procLimit, memAvail);
      }
    }