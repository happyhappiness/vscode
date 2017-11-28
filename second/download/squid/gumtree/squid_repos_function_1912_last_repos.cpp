static int
httpHdrMangle(HttpHeaderEntry * e, HttpRequest * request, HeaderManglers *hms)
{
    int retval;

    assert(e);

    const headerMangler *hm = hms->find(*e);

    /* mangler or checklist went away. default allow */
    if (!hm || !hm->access_list) {
        debugs(66, 7, "couldn't find mangler or access list. Allowing");
        return 1;
    }

    ACLFilledChecklist checklist(hm->access_list, request, NULL);

    if (checklist.fastCheck().allowed()) {
        /* aclCheckFast returns true for allow. */
        debugs(66, 7, "checklist for mangler is positive. Mangle");
        retval = 1;
    } else if (NULL == hm->replacement) {
        /* It was denied, and we don't have any replacement */
        debugs(66, 7, "checklist denied, we have no replacement. Pass");
        retval = 0;
    } else {
        /* It was denied, but we have a replacement. Replace the
         * header on the fly, and return that the new header
         * is allowed.
         */
        debugs(66, 7, "checklist denied but we have replacement. Replace");
        e->value = hm->replacement;
        retval = 1;
    }

    return retval;
}