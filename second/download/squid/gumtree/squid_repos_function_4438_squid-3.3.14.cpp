wordlist *
ACLARP::dump() const
{
    wordlist *w = NULL;
    data->walk(aclDumpArpListWalkee, &w);
    return w;
}