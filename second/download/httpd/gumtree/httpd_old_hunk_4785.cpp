#ifndef OPENSSL_NO_EC
        || have_ecc
#endif
          )) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01911)
                "Oops, no " KEYTYPES " server private key found?!");
        ssl_die();
    }
}

#ifdef HAVE_TLS_SESSION_TICKETS
static void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
