const char *
Note::match(HttpRequest *request, HttpReply *reply, const AccessLogEntry::Pointer &al)
{

    typedef Values::iterator VLI;
    ACLFilledChecklist ch(NULL, request, NULL);
    ch.reply = reply;
    if (reply)
        HTTPMSGLOCK(ch.reply);

    for (VLI i = values.begin(); i != values.end(); ++i ) {
        const int ret= ch.fastCheck((*i)->aclList);
        debugs(93, 5, HERE << "Check for header name: " << key << ": " << (*i)->value
               <<", HttpRequest: " << request << " HttpReply: " << reply << " matched: " << ret);
        if (ret == ACCESS_ALLOWED) {
            if (al != NULL && (*i)->valueFormat != NULL) {
                static MemBuf mb;
                mb.reset();
                (*i)->valueFormat->assemble(mb, al, 0);
                return mb.content();
            } else
                return (*i)->value.termedBuf();
        }
    }
    return NULL;
}