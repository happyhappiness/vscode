SBufList
ToSBufList(wordlist *wl)
{
    SBufList rv;
    while (wl != NULL) {
        rv.push_back(SBuf(wl->key));
        wl = wl->next;
    }
    return rv;
}