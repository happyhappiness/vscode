        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_UNSET) {
            sc->server->pphrase_dialog_type = SSL_PPTYPE_BUILTIN;
        }

    }

#if APR_HAS_THREADS
    ssl_util_thread_setup(p);
#endif

    /*
     * SSL external crypto device ("engine") support
     */
#ifdef SSL_EXPERIMENTAL_ENGINE
    ssl_init_Engine(base_server, p);
#endif

    ssl_init_SSLLibrary(base_server);

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     * only need ptemp here; nothing inside allocated from the pool
     * needs to live once we return from ssl_rand_seed().
     */
