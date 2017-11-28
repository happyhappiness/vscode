void Adaptation::Icap::Options::TransferList::report(int level, const char *prefix) const
{
    if (extensions) {
        for (wordlist *e = extensions; e; e = e->next)
            debugs(93,level, prefix << name << ": " << e->key);
    } else {
        debugs(93,level, prefix << "no " << name << " extensions");
    }
}