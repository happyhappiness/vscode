const char *
NotePairs::find(const char *noteKey, const char *sep) const
{
    static String value;
    value.clean();
    for (Vector<NotePairs::Entry *>::const_iterator  i = entries.begin(); i != entries.end(); ++i) {
        if ((*i)->name.cmp(noteKey) == 0) {
            if (value.size())
                value.append(sep);
            value.append((*i)->value);
        }
    }
    return value.size() ? value.termedBuf() : NULL;
}