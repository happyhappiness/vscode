                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         key_id, pathlen);
        }
    }

    if (SSL_X509_match_name(ptemp, cert, (const char *)s->server_hostname,
                            TRUE, s) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                     "%s server certificate does NOT include an ID "
                     "which matches the server name", key_id);
    }
}

