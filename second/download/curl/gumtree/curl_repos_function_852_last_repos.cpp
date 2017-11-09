void metalink_cleanup(void)
{
#ifdef HAVE_NSS_CONTEXT
  if(nss_context) {
    NSS_ShutdownContext(nss_context);
    nss_context = NULL;
  }
#endif
}