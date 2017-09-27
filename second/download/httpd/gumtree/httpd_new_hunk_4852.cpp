            /* "Upgrade: TLS/1.0, ..." header not found, don't do Upgrade */
        return ap_pass_brigade(f->next, bb);
    }

    apr_table_unset(r->headers_out, "Upgrade");

    csd_data = (secsocket_data*)ap_get_module_config(r->connection->conn_config, &nwssl_module);
    csd = csd_data->csd;

    /* Send the interim 101 response. */
    upgradebb = apr_brigade_create(r->pool, f->c->bucket_alloc);

    ap_fputstrs(f->next, upgradebb, SWITCH_STATUS_LINE, CRLF,
                UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);
