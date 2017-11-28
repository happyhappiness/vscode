wordlist *
ACLIP::dump() const
{
    wordlist *w = NULL;
    data->walk (DumpIpListWalkee, &w);
    return w;
}