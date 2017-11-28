void
ClientRequestContext::clientStoreIdDone(const HelperReply &reply)
{
    HttpRequest *old_request = http->request;
    debugs(85, 5, "'" << http->uri << "' result=" << reply);
    assert(store_id_state == REDIRECT_PENDING);
    store_id_state = REDIRECT_DONE;

    // Put helper response Notes into the transaction state record (ALE) eventually
    // do it early to ensure that no matter what the outcome the notes are present.
    if (http->al != NULL) {
        NotePairs &notes = SyncNotes(*http->al, *old_request);
        notes.append(&reply.notes);
    }

    switch (reply.result) {
    case HelperReply::Unknown:
    case HelperReply::TT:
        // Handler in redirect.cc should have already mapped Unknown
        // IF it contained valid entry for the old helper protocol
        debugs(85, DBG_IMPORTANT, "ERROR: storeID helper returned invalid result code. Wrong helper? " << reply);
        break;

    case HelperReply::BrokenHelper:
        debugs(85, DBG_IMPORTANT, "ERROR: storeID helper: " << reply << ", attempt #" << (store_id_fail_count+1) << " of 2");
        if (store_id_fail_count < 2) { // XXX: make this configurable ?
            ++store_id_fail_count;
            // reset state flag to try StoreID again from scratch.
            store_id_done = false;
        }
        break;

    case HelperReply::Error:
        // no change to be done.
        break;

    case HelperReply::Okay: {
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