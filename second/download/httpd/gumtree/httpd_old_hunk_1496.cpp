            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);
                return SSL_TLSEXT_ERR_ALERT_WARNING;
            }
        }
    }

    return SSL_TLSEXT_ERR_NOACK;
}
