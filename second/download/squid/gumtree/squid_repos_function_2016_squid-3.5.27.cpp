static void
gen_dump(const EntryList &head, std::ostream &fout)
{
    fout <<
         "static void" << std::endl <<
         "dump_config(StoreEntry *entry)" << std::endl <<
         "{" << std::endl <<
         "    debugs(5, 4, HERE);" << std::endl;

    for (EntryList::const_iterator e = head.begin(); e != head.end(); ++e) {

        if (!e->loc.size() || e->loc.compare("none") == 0)
            continue;

        if (e->name.compare("comment") == 0)
            continue;

        if (e->ifdef.size())
            fout << "#if " << e->ifdef << std::endl;

        fout << "    dump_" << e->type << "(entry, \"" << e->name << "\", " << e->loc << ");" << std::endl;

        if (e->ifdef.size())
            fout << "#endif" << std::endl;
    }

    fout << "}" << std::endl << std::endl;
}