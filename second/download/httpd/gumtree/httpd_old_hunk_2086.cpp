        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_UNSET) {
            sc->server->pphrase_dialog_type = SSL_PPTYPE_BUILTIN;
        }

    }

    /*
     * SSL external crypto device ("engine") support
     */
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
    ssl_init_Engine(base_server, p);
#endif

#if APR_HAS_THREADS
    ssl_util_thread_setup(p);
#endif

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Initialized %s library", SSL_LIBRARY_NAME);

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     * only need ptemp here; nothing inside allocated from the pool
