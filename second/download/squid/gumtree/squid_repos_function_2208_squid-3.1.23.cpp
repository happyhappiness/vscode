static int
httpHdrMangle(HttpHeaderEntry * e, HttpRequest * request, int req_or_rep)
{
    int retval;

    /* check with anonymizer tables */
    header_mangler *hm;
    assert(e);

    if (ROR_REQUEST == req_or_rep) {
        hm = &Config.request_header_access[e->id];
    } else if (ROR_REPLY == req_or_rep) {
        hm = &Config.reply_header_access[e->id];
    } else {
        /* error. But let's call it "request". */
        hm = &Config.request_header_access[e->id];
    }

    /* mangler or checklist went away. default allow */
    if (!hm || !hm->access_list) {
        return 1;
    }

    ACLFilledChecklist checklist(hm->access_list, request, NULL);

    if (checklist.fastCheck()) {
        /* aclCheckFast returns true for allow. */
        retval = 1;
    } else if (NULL == hm->replacement) {
        /* It was denied, and we don't have any replacement */
        retval = 0;
    } else {
        /* It was denied, but we have a replacement. Replace the
         * header on the fly, and return that the new header
         * is allowed.
         */
        e->value = hm->replacement;
        retval = 1;
    }

    return retval;
}