static int
gen_default(const EntryList &head, std::ostream &fout)
{
    int rc = 0;
    fout << "static void" << std::endl <<
    "default_line(const char *s)" << std::endl <<
    "{" << std::endl <<
    "    LOCAL_ARRAY(char, tmp_line, BUFSIZ);" << std::endl <<
    "    xstrncpy(tmp_line, s, BUFSIZ);" << std::endl <<
    "    xstrncpy(config_input_line, s, BUFSIZ);" << std::endl <<
    "    config_lineno++;" << std::endl <<
    "    parse_line(tmp_line);" << std::endl <<
    "}" << std::endl << std::endl;
    fout << "static void" << std::endl <<
    "default_all(void)" << std::endl <<
    "{" << std::endl <<
    "    cfg_filename = \"Default Configuration\";" << std::endl <<
    "    config_lineno = 0;" << std::endl;

    for (EntryList::const_iterator entry = head.begin(); entry != head.end(); ++entry) {
        assert(entry->name.size());

        if (!entry->name.compare("comment"))
            continue;

        if (!entry->type.compare("obsolete"))
            continue;

        if (!entry->loc.size()) {
            std::cerr << "NO LOCATION FOR " << entry->name << std::endl;
            rc |= 1;
            continue;
        }

        if (!entry->defaults.preset.size() && entry->defaults.if_none.empty()) {
            std::cerr << "NO DEFAULT FOR " << entry->name << std::endl;
            rc |= 1;
            continue;
        }

        if (!entry->defaults.preset.size() || entry->defaults.preset.front().compare("none") == 0) {
            fout << "    // No default for " << entry->name << std::endl;
        } else {
            if (entry->ifdef.size())
                fout << "#if " << entry->ifdef << std::endl;

            for (LineList::const_iterator l = entry->defaults.preset.begin(); l != entry->defaults.preset.end(); ++l) {
                fout << "    default_line(\"" << entry->name << " " << *l << "\");" << std::endl;
            }

            if (entry->ifdef.size())
                fout << "#endif" << std::endl;
        }
    }

    fout << "    cfg_filename = NULL;" << std::endl <<
    "}" << std::endl << std::endl;
    return rc;
}