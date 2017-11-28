        }
    }

#if USE_OPENSSL
    if (s->flags.tunnelSslBumping)
        storeAppendPrintf(e, " ssl-bump");

    if (s->cert)
        storeAppendPrintf(e, " cert=%s", s->cert);

    if (s->key)
        storeAppendPrintf(e, " key=%s", s->key);

    if (s->version)
        storeAppendPrintf(e, " version=%d", s->version);

    if (s->options)
        storeAppendPrintf(e, " options=%s", s->options);

    if (s->cipher)
        storeAppendPrintf(e, " cipher=%s", s->cipher);

    if (s->cafile)
        storeAppendPrintf(e, " cafile=%s", s->cafile);

    if (s->capath)
        storeAppendPrintf(e, " capath=%s", s->capath);

    if (s->crlfile)
        storeAppendPrintf(e, " crlfile=%s", s->crlfile);

    if (s->dhfile)
        storeAppendPrintf(e, " dhparams=%s", s->dhfile);

    if (s->tls_dh)
        storeAppendPrintf(e, " tls-dh=%s", s->tls_dh);

    if (s->sslflags)
        storeAppendPrintf(e, " sslflags=%s", s->sslflags);

    if (s->sslContextSessionId)
        storeAppendPrintf(e, " sslcontext=%s", s->sslContextSessionId);

    if (s->generateHostCertificates)
        storeAppendPrintf(e, " generate-host-certificates");

    if (s->dynamicCertMemCacheSize != std::numeric_limits<size_t>::max())
        storeAppendPrintf(e, "dynamic_cert_mem_cache_size=%lu%s\n", (unsigned long)s->dynamicCertMemCacheSize, B_BYTES_STR);
#endif
}

static void
dump_PortCfg(StoreEntry * e, const char *n, const AnyP::PortCfgPointer &s)
{
