(numBytes <= (UInt32)(p->HiUnit - p->LoUnit))
  {
    void *retVal = p->LoUnit;
    p->LoUnit += numBytes;
    return retVal;
  }