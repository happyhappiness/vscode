wordlist *
ACLHTTPStatus::dump() const
{
    wordlist *w = NULL;
    data->walk(aclDumpHTTPStatusListWalkee, &w);
    return w;
}