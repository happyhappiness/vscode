static void
gen_conf(const EntryList &head, std::ostream &fout, bool verbose_output)
{
    for (EntryList::const_iterator entry = head.begin(); entry != head.end(); ++entry) {
        char buf[8192];
        LineList def;
        int enabled = 1;

        // Display TAG: line
        if (!entry->name.compare("comment"))
            (void) 0;
        else if (!entry->name.compare("obsolete"))
            (void) 0;
        else if (verbose_output) {
            fout << "#  TAG: " << entry->name;

            if (entry->comment.size())
                fout << "\t" << entry->comment;

            fout << std::endl;
        }

        // Display --enable/--disable disclaimer
        if (!isDefined(entry->ifdef)) {
            if (verbose_output) {
                fout << "# Note: This option is only available if Squid is rebuilt with the" << std::endl <<
                "#       " << available_if(entry->ifdef) << std::endl <<
                "#" << std::endl;
            }
            enabled = 0;
        }

        // Display DOC_START section
        if (verbose_output && entry->doc.size()) {
            for (LineList::const_iterator line = entry->doc.begin(); line != entry->doc.end(); ++line) {
                fout << "#" << *line << std::endl;
            }
        }

        if (entry->defaults.docs.size()) {
            // Display the DEFAULT_DOC line(s)
            def = entry->defaults.docs;
        } else {
            if (entry->defaults.preset.size() && entry->defaults.preset.front().compare("none") != 0) {
                // Display DEFAULT: line(s)
                for (LineList::const_iterator l = entry->defaults.preset.begin(); l != entry->defaults.preset.end(); ++l) {
                    snprintf(buf, sizeof(buf), "%s %s", entry->name.c_str(), l->c_str());
                    def.push_back(buf);
                }
            } else if (entry->defaults.if_none.size()) {
                // Display DEFAULT_IF_NONE: line(s)
                for (LineList::const_iterator l = entry->defaults.if_none.begin(); l != entry->defaults.if_none.end(); ++l) {
                    snprintf(buf, sizeof(buf), "%s %s", entry->name.c_str(), l->c_str());
                    def.push_back(buf);
                }
            }
        }

        // Display "none" if no default is set or comments to display
        if (def.empty() && entry->nocomment.empty() && entry->name.compare("comment") != 0)
            def.push_back("none");

        if (verbose_output && def.size()) {
            fout << "#Default:\n";
            while (def.size()) {
                fout << "# " << def.front() << std::endl;
                def.pop_front();
            }
            if (entry->doc.empty() && entry->nocomment.empty())
                fout << std::endl;
        }

        if (verbose_output && entry->nocomment.size())
            fout << "#" << std::endl;

        if (enabled || verbose_output) {
            for (LineList::const_iterator line = entry->nocomment.begin(); line != entry->nocomment.end(); ++line) {
                if (!enabled && line->at(0) != '#')
                    fout << "#";
                fout << *line << std::endl;
            }
        }

        if (verbose_output && entry->doc.size()) {
            fout << std::endl;
        }
    }
}