    }

    helperStats(sentry, redirectors, "Redirector Statistics");

    if (Config.onoff.redirector_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all redirectors were busy: %d\n", redirectorBypassed);
}

static void
storeIdStats(StoreEntry * sentry)
{
    if (storeIds == NULL) {
        storeAppendPrintf(sentry, "No StoreId helpers defined\n");
        return;
    }

    helperStats(sentry, storeIds, "StoreId helper Statistics");

    if (Config.onoff.store_id_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all StoreId helpers were busy: %d\n", storeIdBypassed);
}

static void
constructHelperQuery(const char *name, helper *hlp, HLPCB *replyHandler, ClientHttpRequest * http, HLPCB *handler, void *data)
{
    ConnStateData * conn = http->getConn();
    const char *fqdn;
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    Http::StatusCode status;
    char claddr[MAX_IPSTRLEN];
    char myaddr[MAX_IPSTRLEN];

    /** TODO: create a standalone method to initialize
     * the cbdata\redirectStateData for all the helpers.
     */
    redirectStateData *r = cbdataAlloc(redirectStateData);
    r->orig_url = xstrdup(http->uri);
    if (conn != NULL)
        r->client_addr = conn->log_addr;
    else
        r->client_addr.setNoAddr();
    r->client_ident = NULL;
#if USE_AUTH
    if (http->request->auth_user_request != NULL) {
        r->client_ident = http->request->auth_user_request->username();
        debugs(61, 5, HERE << "auth-user=" << (r->client_ident?r->client_ident:"NULL"));
    }
