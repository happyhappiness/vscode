const char *
NotePairs::toString(const char *sep) const
{
    static String value;
    value.clean();
    for (Vector<NotePairs::Entry *>::const_iterator  i = entries.begin(); i != entries.end(); ++i) {
        value.append((*i)->name);
        value.append(": ");
        value.append((*i)->value);
        value.append(sep);
    }
    return value.size() ? value.termedBuf() : NULL;
}