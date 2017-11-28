wordlist *
ACLEui64::dump() const
{
    wordlist *w = NULL;
    data->walk(aclDumpEuiListWalkee, &w);
    return w;
}