wordlist *
ACLCertificateData::dump()
{
    wordlist *wl = NULL;
    wordlistAdd(&wl, attribute);
    /* damn this is VERY inefficient for long ACL lists... filling
     * a wordlist this way costs Sum(1,N) iterations. For instance
     * a 1000-elements list will be filled in 499500 iterations.
     */
    /* XXX FIXME: don't break abstraction */
    values.values->walk(aclDumpAttributeListWalkee, &wl);
    return wl;
}