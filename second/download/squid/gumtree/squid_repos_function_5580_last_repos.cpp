void
Comm::ConnOpener::setHost(const char * new_host)
{
    // unset and erase if already set.
    if (host_ != NULL)
        safe_free(host_);

    // set the new one if given.
    if (new_host != NULL)
        host_ = xstrdup(new_host);
}