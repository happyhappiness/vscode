int64_t
HttpRequest::getRangeOffsetLimit()
{
    /* -2 is the starting value of rangeOffsetLimit.
     * If it is -2, that means we haven't checked it yet.
     *  Otherwise, return the current value */
    if (rangeOffsetLimit != -2)
        return rangeOffsetLimit;

    rangeOffsetLimit = 0; // default value for rangeOffsetLimit

    ACLFilledChecklist ch(NULL, this, NULL);
    ch.src_addr = client_addr;
    ch.my_addr =  my_addr;

    for (AclSizeLimit *l = Config.rangeOffsetLimit; l; l = l -> next) {
        /* if there is no ACL list or if the ACLs listed match use this limit value */
        if (!l->aclList || ch.fastCheck(l->aclList) == ACCESS_ALLOWED) {
            debugs(58, 4, HERE << "rangeOffsetLimit=" << rangeOffsetLimit);
            rangeOffsetLimit = l->size; // may be -1
            break;
        }
    }

    return rangeOffsetLimit;
}