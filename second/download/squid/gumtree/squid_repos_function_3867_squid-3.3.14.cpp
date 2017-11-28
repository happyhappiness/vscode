const char *
Adaptation::Config::MetaHeader::match(HttpRequest *request, HttpReply *reply)
{

    typedef Values::iterator VLI;
    ACLFilledChecklist ch(NULL, request, NULL);
    if (reply)
        ch.reply = HTTPMSGLOCK(reply);

    for (VLI i = values.begin(); i != values.end(); ++i ) {
        const int ret= ch.fastCheck((*i)->aclList);
        debugs(93, 5, HERE << "Check for header name: " << name << ": " << (*i)->value
               <<", HttpRequest: " << request << " HttpReply: " << reply << " matched: " << ret);
        if (ret == ACCESS_ALLOWED)
            return (*i)->value.termedBuf();
    }
    return NULL;
}