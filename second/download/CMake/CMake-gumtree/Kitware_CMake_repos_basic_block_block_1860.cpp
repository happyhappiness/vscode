{
    memAvail =
      min((SystemInformation::LongLong)rlim.rlim_cur / 1024, memAvail);
  }