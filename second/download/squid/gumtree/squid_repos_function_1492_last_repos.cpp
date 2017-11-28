static void
copyResultsFromEntry(HttpRequest *req, const ExternalACLEntryPointer &entry)
{
    if (req) {
#if USE_AUTH
        if (entry->user.size())
            req->extacl_user = entry->user;

        if (entry->password.size())
            req->extacl_passwd = entry->password;
#endif
        if (!req->tag.size())
            req->tag = entry->tag;

        if (entry->log.size())
            req->extacl_log = entry->log;

        if (entry->message.size())
            req->extacl_message = entry->message;

        // attach the helper kv-pair to the transaction
        UpdateRequestNotes(req->clientConnectionManager.get(), *req, entry->notes);
    }
}