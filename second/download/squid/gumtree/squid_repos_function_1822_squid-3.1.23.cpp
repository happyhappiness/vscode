void
Entry::genParseAlias(const std::string &aName, std::ostream &fout) const
{
    fout << "    if (!strcmp(token, \"" << aName << "\")) {" << std::endl;
    fout << "        ";
    if (type.compare("obsolete") == 0) {
        fout << "debugs(0, DBG_CRITICAL, \"ERROR: Directive '" << aName << "' is obsolete.\");\n";
        for (LineList::const_iterator l = doc.begin(); l != doc.end(); ++l) {
            // offset line to strip initial whitespace tab byte
            fout << "        debugs(0, opt_parse_cfg_only?0:1, \"" << aName << " : " << &(*l)[1] << "\");" << std::endl;
        }
        fout << "        parse_obsolete(token);";
    } else if (!loc.size() || loc.compare("none") == 0) {
        fout << "parse_" << type << "();";
    } else {
        fout << "parse_" << type << "(&" << loc << (array_flag ? "[0]" : "") << ");";
    }
    fout << std::endl;
    fout << "        return 1;" << std::endl;
    fout << "    };" << std::endl;
}