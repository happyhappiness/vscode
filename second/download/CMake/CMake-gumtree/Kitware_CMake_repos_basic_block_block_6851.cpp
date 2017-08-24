{
    /* Free references to client certificates held in the SSL session cache.
     * Omitting this hampers destruction of the security module owning
     * the certificates. */
    SSL_ClearSessionCache();

    nss_unload_module(&pem_module);
    nss_unload_module(&trust_module);
    NSS_ShutdownContext(nss_context);
    nss_context = NULL;
  }