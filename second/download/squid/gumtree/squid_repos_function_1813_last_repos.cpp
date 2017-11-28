void
NotePairs::replaceOrAdd(const NotePairs *src)
{
    for (std::vector<NotePairs::Entry *>::const_iterator  i = src->entries.begin(); i != src->entries.end(); ++i) {
        remove((*i)->name.termedBuf());
    }
    append(src);
}