void
NotePairs::add(const char *key, const char *note)
{
    entries.push_back(new NotePairs::Entry(key, note));
}