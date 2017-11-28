void
NotePairs::remove(const char *key)
{
    Vector<NotePairs::Entry *>::iterator i = entries.begin();
    while (i != entries.end()) {
        if ((*i)->name.cmp(key) == 0) {
            NotePairs::Entry *e = (*i);
            entries.prune(e);
            delete e;
            i = entries.begin(); // vector changed underneath us
        } else
            ++i;
    }
}