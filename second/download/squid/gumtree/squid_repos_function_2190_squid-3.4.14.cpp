const char *
Note::match(HttpRequest *request, HttpReply *reply)
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
        if (ret == ACCESS_ALLOWED)
            return (*i)->value.termedBuf();
    }
    return NULL;
}