static void
gen_default_if_none(const EntryList &head, std::ostream &fout)
{
    fout << "static void" << std::endl <<
    "defaults_if_none(void)" << std::endl <<
    "{" << std::endl <<
    "    cfg_filename = \"Default Configuration (if absent)\";" << std::endl <<
    "    config_lineno = 0;" << std::endl;

    for (EntryList::const_iterator entry = head.begin(); entry != head.end(); ++entry) {
        assert(entry->name.size());

        if (!entry->loc.size())
            continue;

        if (entry->defaults.if_none.empty())
            continue;

        if (!entry->defaults.preset.empty()) {
            std::cerr << "ERROR: " << entry->name << " has preset defaults. DEFAULT_IF_NONE cannot be true." << std::endl;
            exit(1);
        }

        if (entry->ifdef.size())
            fout << "#if " << entry->ifdef << std::endl;

        fout << "    if (check_null_" << entry->type << "(" << entry->loc << ")) {" << std::endl;
        for (LineList::const_iterator l = entry->defaults.if_none.begin(); l != entry->defaults.if_none.end(); ++l)
            fout << "        default_line(\"" << entry->name << " " << *l <<"\");" << std::endl;
        fout << "    }" << std::endl;

        if (entry->ifdef.size())
            fout << "#endif" << std::endl;
    }

    fout << "    cfg_filename = NULL;" << std::endl <<
    "}" << std::endl << std::endl;
}