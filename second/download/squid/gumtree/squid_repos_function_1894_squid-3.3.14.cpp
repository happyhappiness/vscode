void
Entry::genParse(std::ostream &fout) const
{
    if (name.compare("comment") == 0)
        return;

    // Once for the current directive name
    genParseAlias(name, fout);

    // All accepted aliases
    for (EntryAliasList::const_iterator a = alias.begin(); a != alias.end(); ++a) {
        genParseAlias(*a, fout);
    }
}