void
storeIdStart(ClientHttpRequest * http, HLPCB * handler, void *data)
{
    assert(http);
    assert(handler);
    debugs(61, 5, "storeIdStart: '" << http->uri << "'");

    if (Config.onoff.store_id_bypass && storeIds->willOverload()) {
        /* Skip StoreID Helper if the queue is full */
        ++storeIdBypassed;
        Helper::Reply bypassReply;

        bypassReply.result = Helper::Okay;

        bypassReply.notes.add("message","StoreId helper queue too long. Bypassed.");
        handler(data, bypassReply);
        return;
    }

    constructHelperQuery("storeId helper", storeIds, storeIdHandleReply, http, handler, data, storeIdExtrasFmt);
}