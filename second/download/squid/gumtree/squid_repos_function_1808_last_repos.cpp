void
NotePairs::remove(const char *key)
{
    std::vector<NotePairs::Entry *>::iterator i = entries.begin();
    while (i != entries.end()) {
        if ((*i)->name.cmp(key) == 0) {
            delete *i;
            i = entries.erase(i);
        } else {
            ++i;
        }
    }
}