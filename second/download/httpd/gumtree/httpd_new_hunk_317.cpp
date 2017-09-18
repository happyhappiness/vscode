                ch = ((unsigned char)*((char *)(s) + i * DUMP_WIDTH + j)) & 0xff;
                apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= ' ') && (ch <= '~')) ? ch : '.');
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " |", sizeof(buf)-strlen(buf));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
                     "%s", buf);
    }
    if (trunc > 0)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
                "| %04ld - <SPACES/NULS>", len + trunc);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
            "+-------------------------------------------------------------------------+");
    return;
}

long ssl_io_data_cb(BIO *bio, int cmd,
                    MODSSL_BIO_CB_ARG_TYPE *argp,
