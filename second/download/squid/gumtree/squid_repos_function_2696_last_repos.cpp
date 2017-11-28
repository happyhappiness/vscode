char *
internalLocalUri(const char *dir, const SBuf &name)
{
    return internalRemoteUri(getMyHostname(),
                             getMyPort(), dir, name);
}