void
HttpReply::calcMaxBodySize(HttpRequest& request)
{
    // hack: -2 is used as "we have not calculated max body size yet" state
    if (bodySizeMax != -2) // already tried
        return;
    bodySizeMax = -1;

    // short-circuit ACL testing if there are none configured
    if (!Config.ReplyBodySize)
        return;

    ACLFilledChecklist ch(NULL, &request, NULL);
    ch.reply = HTTPMSGLOCK(this); // XXX: this lock makes method non-const
    for (AclSizeLimit *l = Config.ReplyBodySize; l; l = l -> next) {
        /* if there is no ACL list or if the ACLs listed match use this size value */
        if (!l->aclList || ch.fastCheck(l->aclList) == ACCESS_ALLOWED) {
            debugs(58, 4, HERE << "bodySizeMax=" << bodySizeMax);
            bodySizeMax = l->size; // may be -1
            break;
        }
    }
}