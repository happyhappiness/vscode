char *
UrnState::getHost(const SBuf &urlpath)
{
    /** FIXME: this appears to be parsing the URL. *very* badly. */
    /*   a proper encapsulated URI/URL type needs to clear this up. */
    size_t p;
    if ((p = urlpath.find(':')) != SBuf::npos)
        return SBufToCstring(urlpath.substr(0, p-1));

    return SBufToCstring(urlpath);
}