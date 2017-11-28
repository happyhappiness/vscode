int krb5_create_cache(char *kf, char *pn) {

#define KT_PATH_MAX 256
#define MAX_RENEW_TIME "365d"
#define DEFAULT_SKEW (krb5_deltat) 600

    static char *keytab_filename = NULL, *principal_name = NULL;
    static krb5_keytab keytab = 0;
    static krb5_keytab_entry entry;
    static krb5_kt_cursor cursor;
    static krb5_creds *creds = NULL;
#if USE_HEIMDAL_KRB5 && !HAVE_KRB5_GET_RENEWED_CREDS
    static krb5_creds creds2;
#endif
    static krb5_principal principal = NULL;
    static krb5_deltat skew;

#if HAVE_KRB5_GET_INIT_CREDS_OPT_ALLOC
    krb5_get_init_creds_opt *options;
#else
    krb5_get_init_creds_opt options;
#endif
    krb5_error_code code = 0;
    krb5_deltat rlife;
#if HAVE_PROFILE_H && HAVE_KRB5_GET_PROFILE && HAVE_PROFILE_GET_INTEGER && HAVE_PROFILE_RELEASE
    profile_t profile;
#endif
#if USE_HEIMDAL_KRB5 && !HAVE_KRB5_GET_RENEWED_CREDS
    krb5_kdc_flags flags;
#if HAVE_KRB5_PRINCIPAL_GET_REALM
    const char *client_realm;
#else
    krb5_realm client_realm;
#endif
#endif
    char *mem_cache;

restart:
    /*
     * Check if credentials need to be renewed
     */
    if (creds &&
            (creds->times.endtime - time(0) > skew) &&
            (creds->times.renew_till - time(0) > 2 * skew)) {
        if (creds->times.endtime - time(0) < 2 * skew) {
#if HAVE_KRB5_GET_RENEWED_CREDS
            /* renew ticket */
            code =
                krb5_get_renewed_creds(kparam.context, creds, principal,
                                       kparam.cc, NULL);
#else
            /* renew ticket */
            flags.i = 0;
            flags.b.renewable = flags.b.renew = 1;

            code =
                krb5_cc_get_principal(kparam.context, kparam.cc,
                                      &creds2.client);
            if (code) {
                debugs(11, 5,
                       HERE <<
                       "Error while getting principal from credential cache : "
                       << error_message(code));
                return (1);
            }
#if HAVE_KRB5_PRINCIPAL_GET_REALM
            client_realm = krb5_principal_get_realm(kparam.context, principal);
#else
            client_realm = krb5_princ_realm(kparam.context, creds2.client);
#endif
            code =
                krb5_make_principal(kparam.context, &creds2.server,
                                    (krb5_const_realm)&client_realm, KRB5_TGS_NAME,
                                    (krb5_const_realm)&client_realm, NULL);
            if (code) {
                debugs(11, 5,
                       HERE << "Error while getting krbtgt principal : " <<
                       error_message(code));
                return (1);
            }
            code =
                krb5_get_kdc_cred(kparam.context, kparam.cc, flags, NULL,
                                  NULL, &creds2, &creds);
            krb5_free_creds(kparam.context, &creds2);
#endif
            if (code) {
                if (code == KRB5KRB_AP_ERR_TKT_EXPIRED) {
                    krb5_free_creds(kparam.context, creds);
                    creds = NULL;
                    /* this can happen because of clock skew */
                    goto restart;
                }
                debugs(11, 5,
                       HERE << "Error while get credentials : " <<
                       error_message(code));
                return (1);
            }
        }
    } else {
        /* reinit */
        if (!kparam.context) {
            code = krb5_init_context(&kparam.context);
            if (code) {
                debugs(11, 5,
                       HERE << "Error while initialising Kerberos library : "
                       << error_message(code));
                return (1);
            }
        }
#if HAVE_PROFILE_H && HAVE_KRB5_GET_PROFILE && HAVE_PROFILE_GET_INTEGER && HAVE_PROFILE_RELEASE
        code = krb5_get_profile(kparam.context, &profile);
        if (code) {
            if (profile)
                profile_release(profile);
            debugs(11, 5,
                   HERE << "Error while getting profile : " <<
                   error_message(code));
            return (1);
        }
        code =
            profile_get_integer(profile, "libdefaults", "clockskew", 0,
                                5 * 60, &skew);
        if (profile)
            profile_release(profile);
        if (code) {
            debugs(11, 5,
                   HERE << "Error while getting clockskew : " <<
                   error_message(code));
            return (1);
        }
#elif USE_HEIMDAL_KRB5 && HAVE_KRB5_GET_MAX_TIME_SKEW
        skew = krb5_get_max_time_skew(kparam.context);
#elif USE_HEIMDAL_KRB5 && HAVE_MAX_SKEW_IN_KRB5_CONTEXT
        skew = kparam.context->max_skew;
#else
        skew = DEFAULT_SKEW;
#endif

        if (!kf) {
            char buf[KT_PATH_MAX], *p;

            krb5_kt_default_name(kparam.context, buf, KT_PATH_MAX);
            p = strchr(buf, ':');
            if (p)
                ++p;
            xfree(keytab_filename);
            keytab_filename = xstrdup(p ? p : buf);
        } else {
            keytab_filename = xstrdup(kf);
        }

        code = krb5_kt_resolve(kparam.context, keytab_filename, &keytab);
        if (code) {
            debugs(11, 5,
                   HERE << "Error while resolving keytab filename " <<
                   keytab_filename << " : " << error_message(code));
            return (1);
        }

        if (!pn) {
            code = krb5_kt_start_seq_get(kparam.context, keytab, &cursor);
            if (code) {
                debugs(11, 5,
                       HERE << "Error while starting keytab scan : " <<
                       error_message(code));
                return (1);
            }
            code =
                krb5_kt_next_entry(kparam.context, keytab, &entry, &cursor);
            krb5_copy_principal(kparam.context, entry.principal,
                                &principal);
            if (code && code != KRB5_KT_END) {
                debugs(11, 5,
                       HERE << "Error while scanning keytab : " <<
                       error_message(code));
                return (1);
            }

            code = krb5_kt_end_seq_get(kparam.context, keytab, &cursor);
            if (code) {
                debugs(11, 5,
                       HERE << "Error while ending keytab scan : " <<
                       error_message(code));
                return (1);
            }
#if USE_HEIMDAL_KRB5 || ( HAVE_KRB5_KT_FREE_ENTRY && HAVE_DECL_KRB5_KT_FREE_ENTRY)
            code = krb5_kt_free_entry(kparam.context, &entry);
#else
            code = krb5_free_keytab_entry_contents(kparam.context, &entry);
#endif
            if (code) {
                debugs(11, 5,
                       HERE << "Error while freeing keytab entry : " <<
                       error_message(code));
                return (1);
            }

        } else {
            principal_name = xstrdup(pn);
        }

        if (!principal) {
            code =
                krb5_parse_name(kparam.context, principal_name, &principal);
            if (code) {
                debugs(11, 5,
                       HERE << "Error while parsing principal name " <<
                       principal_name << " : " << error_message(code));
                return (1);
            }
        }

        creds = (krb5_creds *) xmalloc(sizeof(*creds));
        memset(creds, 0, sizeof(*creds));
#if HAVE_KRB5_GET_INIT_CREDS_OPT_ALLOC
        krb5_get_init_creds_opt_alloc(kparam.context, &options);
#else
        krb5_get_init_creds_opt_init(&options);
#endif
        code = krb5_string_to_deltat((char *) MAX_RENEW_TIME, &rlife);
        if (code != 0 || rlife == 0) {
            debugs(11, 5,
                   HERE << "Error bad lifetime value " << MAX_RENEW_TIME <<
                   " : " << error_message(code));
            return (1);
        }
#if HAVE_KRB5_GET_INIT_CREDS_OPT_ALLOC
        krb5_get_init_creds_opt_set_renew_life(options, rlife);
        code =
            krb5_get_init_creds_keytab(kparam.context, creds, principal,
                                       keytab, 0, NULL, options);
#if HAVE_KRB5_GET_INIT_CREDS_FREE_CONTEXT
        krb5_get_init_creds_opt_free(kparam.context, options);
#else
        krb5_get_init_creds_opt_free(options);
#endif
#else
        krb5_get_init_creds_opt_set_renew_life(&options, rlife);
        code =
            krb5_get_init_creds_keytab(kparam.context, creds, principal,
                                       keytab, 0, NULL, &options);
#endif
        if (code) {
            debugs(11, 5,
                   HERE <<
                   "Error while initializing credentials from keytab : " <<
                   error_message(code));
            return (1);
        }
#if !HAVE_KRB5_MEMORY_CACHE
        mem_cache =
            (char *) xmalloc(strlen("FILE:/tmp/peer_proxy_negotiate_auth_")
                             + 16);
        if (!mem_cache) {
            debugs(11, 5, "Error while allocating memory");
            return(1);
        }
        snprintf(mem_cache,
                 strlen("FILE:/tmp/peer_proxy_negotiate_auth_") + 16,
                 "FILE:/tmp/peer_proxy_negotiate_auth_%d", (int) getpid());
#else
        mem_cache =
            (char *) xmalloc(strlen("MEMORY:peer_proxy_negotiate_auth_") +
                             16);
        if (!mem_cache) {
            debugs(11, 5, "Error while allocating memory");
            return(1);
        }
        snprintf(mem_cache,
                 strlen("MEMORY:peer_proxy_negotiate_auth_") + 16,
                 "MEMORY:peer_proxy_negotiate_auth_%d", (int) getpid());
#endif

        setenv("KRB5CCNAME", mem_cache, 1);
        code = krb5_cc_resolve(kparam.context, mem_cache, &kparam.cc);
        xfree(mem_cache);
        if (code) {
            debugs(11, 5,
                   HERE << "Error while resolving memory credential cache : "
                   << error_message(code));
            return (1);
        }
        code = krb5_cc_initialize(kparam.context, kparam.cc, principal);
        if (code) {
            debugs(11, 5,
                   HERE <<
                   "Error while initializing memory credential cache : " <<
                   error_message(code));
            return (1);
        }
        code = krb5_cc_store_cred(kparam.context, kparam.cc, creds);
        if (code) {
            debugs(11, 5,
                   HERE << "Error while storing credentials : " <<
                   error_message(code));
            return (1);
        }

        if (!creds->times.starttime)
            creds->times.starttime = creds->times.authtime;
    }
    return (0);
}