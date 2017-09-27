                    rv = apr_file_read(fp, digest, &ds);
                    if ((rv == APR_SUCCESS || rv == APR_EOF) &&
                        ds == APR_MD5_DIGESTSIZE) {
                        rv = APR_SUCCESS;
                        apr_md5(digest2, ptr, nbytes);
                        if (memcmp(digest, digest2, APR_MD5_DIGESTSIZE)) {
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                         APLOGNO(02551) "bad md5 match");
                            rv = APR_EGENERAL;
                        }
                    }
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 APLOGNO(02552) "at EOF... bypassing md5 match check (old persist file?)");
                }
            }
            else if (nbytes != size) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             APLOGNO(02553) "Expected %" APR_SIZE_T_FMT ": Read %" APR_SIZE_T_FMT,
                             size, nbytes);
                rv = APR_EGENERAL;
            }
            apr_file_close(fp);
        }
