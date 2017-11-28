    }

    helperStats(sentry, redirectors, "Redirector Statistics");

    if (Config.onoff.redirector_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all redirectors were busy: %d\n", n_bypassed);
}

/**** PUBLIC FUNCTIONS ****/

void
redirectStart(ClientHttpRequest * http, RH * handler, void *data)
{
    ConnStateData * conn = http->getConn();
    redirectStateData *r = NULL;
    const char *fqdn;
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    http_status status;
    char claddr[MAX_IPSTRLEN];
    char myaddr[MAX_IPSTRLEN];
    assert(http);
    assert(handler);
    debugs(61, 5, "redirectStart: '" << http->uri << "'");

    if (Config.onoff.redirector_bypass && redirectors->stats.queue_size) {
        /* Skip redirector if there is one request queued */
        ++n_bypassed;
        handler(data, NULL);
        return;
    }

    r = cbdataAlloc(redirectStateData);
    r->orig_url = xstrdup(http->uri);
    if (conn != NULL)
        r->client_addr = conn->log_addr;
    else
        r->client_addr.SetNoAddr();
    r->client_ident = NULL;
#if USE_AUTH
    if (http->request->auth_user_request != NULL) {
        r->client_ident = http->request->auth_user_request->username();
        debugs(61, 5, HERE << "auth-user=" << (r->client_ident?r->client_ident:"NULL"));
    }
