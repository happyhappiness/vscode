            /* "Upgrade: TLS/1.0, ..." header not found, don't do Upgrade */
        return ap_pass_brigade(f->next, bb);
    }

    apr_table_unset(r->headers_out, "Upgrade");

    if (r) {
        csd_data = (secsocket_data*)ap_get_module_config(r->connection->conn_config, &nwssl_module);
        csd = csd_data->csd;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02131)
                     "Unable to get upgradeable socket handle");
        return ap_pass_brigade(f->next, bb);
    }


    /* Send the interim 101 response. */
    upgradebb = apr_brigade_create(r->pool, f->c->bucket_alloc);

    ap_fputstrs(f->next, upgradebb, SWITCH_STATUS_LINE, CRLF,
                UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);
