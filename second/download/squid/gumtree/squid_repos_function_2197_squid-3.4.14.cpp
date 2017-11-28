const char *
NotePairs::findFirst(const char *noteKey) const
{
    for (Vector<NotePairs::Entry *>::const_iterator  i = entries.begin(); i != entries.end(); ++i) {
        if ((*i)->name.cmp(noteKey) == 0)
            return (*i)->value.termedBuf();
    }
    return NULL;
}