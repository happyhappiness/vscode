void
ExternalACLLookup::LookupDone(void *data, const ExternalACLEntryPointer &result)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));
    checklist->extacl_entry = result;

    // attach the helper kv-pair to the transaction
    if (checklist->extacl_entry != NULL) {
        if (HttpRequest * req = checklist->request) {
            // XXX: we have no access to the transaction / AccessLogEntry so cant SyncNotes().
            // workaround by using anything already set in HttpRequest
            // OR use new and rely on a later Sync copying these to AccessLogEntry
            if (!req->notes)
                req->notes = new NotePairs;

            req->notes->appendNewOnly(&checklist->extacl_entry->notes);
        }
    }

    checklist->resumeNonBlockingCheck(ExternalACLLookup::Instance());
}