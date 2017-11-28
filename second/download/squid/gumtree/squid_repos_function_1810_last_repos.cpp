bool
NotePairs::hasPair(const char *key, const char *value) const
{
    for (std::vector<NotePairs::Entry *>::const_iterator  i = entries.begin(); i != entries.end(); ++i) {
        if ((*i)->name.cmp(key) == 0 && (*i)->value.cmp(value) == 0)
            return true;
    }
    return false;
}