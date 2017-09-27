ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, mctx->pks->cert_files[0]);