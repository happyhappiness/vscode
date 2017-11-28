const SBuf
ps_state::url() const
{
    if (entry)
        return SBuf(entry->url());

    if (request)
        return request->effectiveRequestUri();

    static const SBuf noUrl("[no URL]");
    return noUrl;
}