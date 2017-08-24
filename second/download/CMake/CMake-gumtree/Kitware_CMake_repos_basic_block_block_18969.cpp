{
    pFSEventStreamInvalidate(ref);
    pFSEventStreamRelease(ref);
    return -EMFILE;
  }