wordlist *
ACLHierCodeData::dump()
{
    wordlist *W = NULL;

    for (hier_code iter=HIER_NONE; iter<HIER_MAX; ++iter) {
        if (!values[iter]) continue;
        wordlistAdd(&W, hier_code_str[iter]);
    }

    return W;
}