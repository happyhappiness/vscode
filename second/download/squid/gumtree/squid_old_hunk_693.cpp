
ACLASN::match(Ip::Address toMatch)
{
    return asnMatchIp(data, toMatch);
}

wordlist *
ACLASN::dump()
{
    wordlist *W = NULL;
    char buf[32];
    CbDataList<int> *ldata = data;

    while (ldata != NULL) {
        snprintf(buf, sizeof(buf), "%d", ldata->element);
        wordlistAdd(&W, buf);
        ldata = ldata->next;
    }

    return W;
}

bool
ACLASN::empty () const
{
    return data == NULL;
