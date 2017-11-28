wordlist *
ACLUserData::dump()
{
    wordlist *wl = NULL;

    if (flags.case_insensitive)
        wordlistAdd(&wl, "-i");

    /* damn this is VERY inefficient for long ACL lists... filling
     * a wordlist this way costs Sum(1,N) iterations. For instance
     * a 1000-elements list will be filled in 499500 iterations.
     */
    if (flags.required)
        wordlistAdd(&wl, "REQUIRED");
    else if (names)
        names->walk(aclDumpUserListWalkee, &wl);

    return wl;
}