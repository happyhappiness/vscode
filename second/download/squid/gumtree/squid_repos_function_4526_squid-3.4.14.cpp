wordlist *
ACLHTTPHeaderData::dump()
{
    wordlist *W = NULL;
    wordlistAdd(&W, hdrName.termedBuf());
    wordlist * regex_dump = regex_rule->dump();
    wordlistAddWl(&W, regex_dump);
    wordlistDestroy(&regex_dump);
    return W;
}