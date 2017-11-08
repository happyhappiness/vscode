static void internalSetEnv(const char * name, char * value)
{
  /* Add your OS-specific code here. */
#ifdef __riscos__
  _kernel_setenv(name, value);
#endif
  return;
}