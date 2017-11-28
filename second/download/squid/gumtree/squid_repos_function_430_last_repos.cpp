void
ClientRequestContext::clientStoreIdDone(const Helper::Reply &reply)
{
    HttpRequest *old_request = http->request;
    debugs(85, 5, "'" << http->uri << "' result=" << reply);
    assert(store_id_state == REDIRECT_PENDING);
    store_id_state = REDIRECT_DONE;

    // Put helper response Notes into the transaction state record (ALE) eventually
    // do it early to ensure that no matter what the outcome the notes are present.
    if (http->al != NULL)
        (void)SyncNotes(*http->al, *old_request);

    UpdateRequestNotes(http->getConn(), *old_request, reply.notes);

    switch (reply.result) {
    case Helper::Unknown:
    case Helper::TT:
        // Handler in redirect.cc should have already mapped Unknown
        // IF it contained valid entry for the old helper protocol
        debugs(85, DBG_IMPORTANT, "ERROR: storeID helper returned invalid result code. Wrong helper? " << reply);
        break;

    case Helper::TimedOut:
    // Timeouts for storeID are not implemented
    case Helper::BrokenHelper:
        debugs(85, DBG_IMPORTANT, "ERROR: storeID helper: " << reply);
        break;

    case Helper::Error:
        // no change to be done.
        break;

    case Helper::Okay: {
        const char *urlNote = reply.notes.findFirst("store-id");

        // prevent broken helpers causing too much damage. If old URL == new URL skip the re-write.
        if (urlNote != NULL && strcmp(urlNote, http->uri) ) {
            // Debug section required for some very specific cases.
            debugs(85, 9, "Setting storeID with: " << urlNote );
            http->request->store_id = urlNote;
            http->store_id = urlNote;
        }
    }
    break;
    }

    http->doCallouts();
}