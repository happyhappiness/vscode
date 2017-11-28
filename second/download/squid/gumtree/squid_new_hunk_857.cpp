    if (Config.onoff.store_id_bypass)
        storeAppendPrintf(sentry, "\nNumber of requests bypassed "
                          "because all StoreId helpers were busy: %d\n", storeIdBypassed);
}

static void
constructHelperQuery(const char *name, helper *hlp, HLPCB *replyHandler, ClientHttpRequest * http, HLPCB *handler, void *data, Format::Format *requestExtrasFmt)
{
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    Http::StatusCode status;

    /** TODO: create a standalone method to initialize
     * the RedirectStateData for all the helpers.
     */
    RedirectStateData *r = new RedirectStateData(http->uri);
    r->handler = handler;
    r->data = cbdataReference(data);

    static MemBuf requestExtras;
    requestExtras.reset();
    if (requestExtrasFmt)
        requestExtrasFmt->assemble(requestExtras, http->al, 0);

    sz = snprintf(buf, MAX_REDIRECTOR_REQUEST_STRLEN, "%s%s%s\n",
                  r->orig_url.c_str(),
                  requestExtras.hasContent() ? " " : "",
                  requestExtras.hasContent() ? requestExtras.content() : "");

    if ((sz<=0) || (sz>=MAX_REDIRECTOR_REQUEST_STRLEN)) {
        if (sz<=0) {
            status = Http::scInternalServerError;
            debugs(61, DBG_CRITICAL, "ERROR: Gateway Failure. Can not build request to be passed to " << name << ". Request ABORTED.");
        } else {
