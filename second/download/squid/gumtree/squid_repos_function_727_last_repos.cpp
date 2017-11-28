static void
dump_SBufList(StoreEntry * entry, const SBufList &words)
{
    for (SBufList::const_iterator i = words.begin(); i != words.end(); ++i) {
        entry->append(i->rawContent(), i->length());
        entry->append(" ",1);
    }
    entry->append("\n",1);
}