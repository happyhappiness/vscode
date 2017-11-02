void metalink_cleanup(void)
{
#ifdef USE_NSS
  if(nss_context) {
    NSS_ShutdownContext(nss_context);
    nss_context = NULL;
  }
#endif
}