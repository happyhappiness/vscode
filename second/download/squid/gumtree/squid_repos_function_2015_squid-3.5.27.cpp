static void
gen_parse(const EntryList &head, std::ostream &fout)
{
    fout <<
         "static int\n"
         "parse_line(char *buff)\n"
         "{\n"
         "\tchar\t*token;\n"
         "\tif ((token = strtok(buff, w_space)) == NULL) \n"
         "\t\treturn 1;\t/* ignore empty lines */\n"
         "\tConfigParser::SetCfgLine(strtok(NULL, \"\"));\n";

    for (EntryList::const_iterator e = head.begin(); e != head.end(); ++e)
        e->genParse(fout);

    fout << "\treturn 0; /* failure */\n"
         "}\n\n";

}