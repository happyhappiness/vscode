    r->useragent_addr = req->useragent_addr;
    r->useragent_ip = req->useragent_ip;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  req->proxy_ips
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies%s",
                  req->useragent_ip,
                  (req->proxy_ips ? req->proxy_ips : ""));
    return OK;
}

static const command_rec remoteip_cmds[] =
{
    AP_INIT_TAKE1("RemoteIPHeader", header_name_set, NULL, RSRC_CONF,
