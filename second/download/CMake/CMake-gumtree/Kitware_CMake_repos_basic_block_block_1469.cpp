{
    kwsysProcessTime length = kwsysProcessTimeFromDouble(cp->Timeout);
    cp->TimeoutTime = kwsysProcessTimeAdd(cp->StartTime, length);
  }