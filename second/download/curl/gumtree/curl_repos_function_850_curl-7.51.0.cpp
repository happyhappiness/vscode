static void internalSetEnv(const char * name, char * value)
{
  /* Add your OS-specific code here. */
#ifdef __riscos__
  _kernel_setenv(name, value);
#elif defined (CURLDEBUG)
  curl_memlog("ENV %s = %s\n", name, value);
#endif
  return;
}