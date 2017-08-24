{
      SystemInformation::LongLong hostLimit =
        atoLongLong(hostLimitEnvVarValue);
      if (hostLimit > 0) {
        memTotal = min(hostLimit, memTotal);
      }
    }