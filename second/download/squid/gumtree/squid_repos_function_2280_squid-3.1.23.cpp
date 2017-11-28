static void
redirectHandleReply(void *data, char *reply)
{
    redirectStateData *r = static_cast<redirectStateData *>(data);
    char *t;
    void *cbdata;
    debugs(61, 5, "redirectHandleRead: {" << (reply && *reply != '\0' ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' ')))
            *t = '\0';

        if (*reply == '\0')
            reply = NULL;
    }

    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata, reply);

    redirectStateFree(r);
}