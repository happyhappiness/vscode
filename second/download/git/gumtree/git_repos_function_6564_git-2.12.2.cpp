static FORCEINLINE long win32_getcurrentthreadid(void) {
#ifdef _MSC_VER
#if defined(_M_IX86)
  long *threadstruct=(long *)__readfsdword(0x18);
  long threadid=threadstruct[0x24/sizeof(long)];
  return threadid;
#elif defined(_M_X64)
  /* todo */
  return GetCurrentThreadId();
#else
  return GetCurrentThreadId();
#endif
#else
  return GetCurrentThreadId();
#endif
}