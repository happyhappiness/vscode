{
  NX_LOCK_INFO_ALLOC(liblock, "Per-Application Data Lock", 0);

#ifndef __GNUC__
#pragma unused(cmdLine)
#pragma unused(loadDirPath)
#pragma unused(uninitializedDataLength)
#pragma unused(NLMFileHandle)
#pragma unused(readRoutineP)
#pragma unused(customDataOffset)
#pragma unused(customDataSize)
#pragma unused(messageCount)
#pragma unused(messages)
#endif

  /*
   * Here we process our command line, post errors (to the error screen),
   * perform initializations and anything else we need to do before being able
   * to accept calls into us. If we succeed, we return non-zero and the NetWare
   * Loader will leave us up, otherwise we fail to load and get dumped.
   */
  gAllocTag = AllocateResourceTag(NLMHandle,
                                  "<library-name> memory allocations",
                                  AllocSignature);

  if(!gAllocTag) {
    OutputToScreen(errorScreen, "Unable to allocate resource tag for "
                   "library memory allocations.\n");
    return -1;
  }

  gLibId = register_library(DisposeLibraryData);

  if(gLibId < -1) {
    OutputToScreen(errorScreen, "Unable to register library with kernel.\n");
    return -1;
  }

  gLibHandle = NLMHandle;

  gLibLock = NXMutexAlloc(0, 0, &liblock);

  if(!gLibLock) {
    OutputToScreen(errorScreen, "Unable to allocate library data lock.\n");
    return -1;
  }

  return 0;
}