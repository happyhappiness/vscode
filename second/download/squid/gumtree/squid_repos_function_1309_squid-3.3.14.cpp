const char *
ps_state::url() const
{
    if (entry)
        return entry->url();

    if (request)
        return urlCanonical(request);

    return "[no URL]";
}