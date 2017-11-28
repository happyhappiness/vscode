void
StoreEntry::replaceHttpReply(HttpReply *rep, bool andStartWriting)
{
    debugs(20, 3, "StoreEntry::replaceHttpReply: " << url());

    if (!mem_obj) {
        debugs(20, DBG_CRITICAL, "Attempt to replace object with no in-memory representation");
        return;
    }

    mem_obj->replaceHttpReply(rep);

    if (andStartWriting)
        startWriting();
}