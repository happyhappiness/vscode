            csd_data->is_secure = 1;
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Upgradeable socket handle not found");
        return ap_pass_brigade(f->next, bb);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Awaiting re-negotiation handshake");

    return ap_pass_brigade(f->next, bb);
}

static void ssl_hook_Insert_Filter(request_rec *r)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(r->server);

