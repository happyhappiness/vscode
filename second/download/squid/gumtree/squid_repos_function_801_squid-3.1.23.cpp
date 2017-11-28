void
HttpReply::calcMaxBodySize(HttpRequest& request)
{
    // hack: -2 is used as "we have not calculated max body size yet" state
    if (bodySizeMax != -2) // already tried
        return;
    bodySizeMax = -1;

    ACLFilledChecklist ch(NULL, &request, NULL);
#if FOLLOW_X_FORWARDED_FOR
    if (Config.onoff.acl_uses_indirect_client)
        ch.src_addr = request.indirect_client_addr;
    else
#endif
        ch.src_addr = request.client_addr;
    ch.my_addr = request.my_addr;
    ch.reply = HTTPMSGLOCK(this); // XXX: this lock makes method non-const
    for (acl_size_t *l = Config.ReplyBodySize; l; l = l -> next) {
        /* if there is no ACL list or if the ACLs listed match use this size value */
        if (!l->aclList || ch.matchAclListFast(l->aclList)) {
            debugs(58, 4, HERE << "bodySizeMax=" << bodySizeMax);
            bodySizeMax = l->size; // may be -1
            break;
        }
    }
}