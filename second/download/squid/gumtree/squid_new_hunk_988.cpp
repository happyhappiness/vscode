        }
    }

#if USE_OPENSSL
    if (s->flags.tunnelSslBumping)
        storeAppendPrintf(e, " ssl-bump");
#endif

    s->secure.dumpCfg(e, "tls-");

#if USE_OPENSSL
    if (s->sslContextSessionId)
        storeAppendPrintf(e, " sslcontext=%s", s->sslContextSessionId);

    if (!s->generateHostCertificates)
        storeAppendPrintf(e, " generate-host-certificates=off");

    if (s->dynamicCertMemCacheSize != 4*1024*1024) // 4MB default
        storeAppendPrintf(e, "dynamic_cert_mem_cache_size=%" PRIuSIZE "%s\n", s->dynamicCertMemCacheSize, B_BYTES_STR);
#endif
}

static void
dump_PortCfg(StoreEntry * e, const char *n, const AnyP::PortCfgPointer &s)
{
