
        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");
    }
}

#ifdef SSLC_VERSION_NUMBER
static int ssl_init_FindCAList_X509NameCmp(char **a, char **b)
{
