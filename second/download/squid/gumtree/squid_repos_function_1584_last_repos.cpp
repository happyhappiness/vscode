static void
gen_free(const EntryList &head, std::ostream &fout)
{
    fout <<
         "static void" << std::endl <<
         "free_all(void)" << std::endl <<
         "{" << std::endl <<
         "    debugs(5, 4, HERE);" << std::endl;

    for (EntryList::const_iterator e = head.begin(); e != head.end(); ++e) {
        if (!e->loc.size() || e->loc.compare("none") == 0)
            continue;

        if (e->name.compare("comment") == 0)
            continue;

        if (e->ifdef.size())
            fout << "#if " << e->ifdef << std::endl;

        fout << "    free_" << e->type << "(&" << e->loc << (e->array_flag ? "[0]" : "") << ");" << std::endl;

        if (e->ifdef.size())
            fout << "#endif" << std::endl;
    }

    fout << "}" << std::endl << std::endl;
}