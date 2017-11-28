void
storeIdStart(ClientHttpRequest * http, HLPCB * handler, void *data)
{
    assert(http);
    assert(handler);
    debugs(61, 5, "storeIdStart: '" << http->uri << "'");

    if (Config.onoff.store_id_bypass && storeIds->stats.queue_size) {
        /* Skip StoreID Helper if there is one request queued */
        ++storeIdBypassed;
        HelperReply bypassReply;

        bypassReply.result = HelperReply::Okay;

        bypassReply.notes.add("message","StoreId helper queue too long. Bypassed.");
        handler(data, bypassReply);
        return;
    }

    constructHelperQuery("storeId helper", storeIds, storeIdHandleReply, http, handler, data);
}