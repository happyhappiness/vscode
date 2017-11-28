wordlist *
ACLStringData::dump()
{
    wordlist *wl = NULL;
    /* damn this is VERY inefficient for long ACL lists... filling
     * a wordlist this way costs Sum(1,N) iterations. For instance
     * a 1000-elements list will be filled in 499500 iterations.
     */
    values->walk(aclDumpStringWalkee, &wl);
    return wl;
}