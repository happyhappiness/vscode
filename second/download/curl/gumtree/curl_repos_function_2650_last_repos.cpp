static void Curl_nss_cleanup(void)
{
  /* This function isn't required to be threadsafe and this is only done
   * as a safety feature.
   */
  PR_Lock(nss_initlock);
  if(initialized) {
    /* Free references to client certificates held in the SSL session cache.
     * Omitting this hampers destruction of the security module owning
     * the certificates. */
    SSL_ClearSessionCache();

    nss_unload_module(&pem_module);
    nss_unload_module(&trust_module);
    NSS_ShutdownContext(nss_context);
    nss_context = NULL;
  }

  /* destroy all CRL items */
  Curl_llist_destroy(&nss_crl_list, NULL);

  PR_Unlock(nss_initlock);

  PR_DestroyLock(nss_initlock);
  PR_DestroyLock(nss_crllock);
  PR_DestroyLock(nss_findslot_lock);
  PR_DestroyLock(nss_trustload_lock);
  nss_initlock = NULL;

  initialized = 0;
}