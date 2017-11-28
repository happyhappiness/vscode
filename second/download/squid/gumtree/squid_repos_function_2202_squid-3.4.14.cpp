void
NotePairs::append(const NotePairs *src)
{
    for (Vector<NotePairs::Entry *>::const_iterator  i = src->entries.begin(); i != src->entries.end(); ++i) {
        entries.push_back(new NotePairs::Entry((*i)->name.termedBuf(), (*i)->value.termedBuf()));
    }
}