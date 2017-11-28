static void
gen_default_postscriptum(const EntryList &head, std::ostream &fout)
{
    fout << "static void" << std::endl <<
         "defaults_postscriptum(void)" << std::endl <<
         "{" << std::endl <<
         "    cfg_filename = \"Default Configuration (postscriptum)\";" << std::endl <<
         "    config_lineno = 0;" << std::endl;

    for (EntryList::const_iterator entry = head.begin(); entry != head.end(); ++entry) {
        assert(entry->name.size());

        if (!entry->loc.size())
            continue;

        if (entry->defaults.postscriptum.empty())
            continue;

        if (entry->ifdef.size())
            fout << "#if " << entry->ifdef << std::endl;

        for (LineList::const_iterator l = entry->defaults.postscriptum.begin(); l != entry->defaults.postscriptum.end(); ++l)
            fout << "    default_line(\"" << entry->name << " " << *l <<"\");" << std::endl;

        if (entry->ifdef.size())
            fout << "#endif" << std::endl;
    }

    fout << "    cfg_filename = NULL;" << std::endl <<
         "}" << std::endl << std::endl;
}