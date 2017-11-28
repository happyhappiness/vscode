int
main(int argc, char *argv[])
{
    char *input_filename;
    const char *output_filename = _PATH_PARSER;
    const char *conf_filename = _PATH_SQUID_CONF;
    const char *conf_filename_short = _PATH_SQUID_CONF_SHORT;
    const char *type_depend;
    int linenum = 0;
    EntryList entries;
    TypeList types;
    enum State state;
    int rc = 0;
    char *ptr = NULL;
    char buff[MAX_LINE];
    std::ifstream fp;
    std::stack<std::string> IFDEFS;

    if (argc != 3)
        usage(argv[0]);

    input_filename = argv[1];
    type_depend = argv[2];

    /*-------------------------------------------------------------------*
     * Parse type dependencies
     *-------------------------------------------------------------------*/
    fp.open(type_depend, std::ifstream::in);
    if (fp.fail()) {
        std::cerr << "Error while opening type dependencies file '" <<
                  type_depend << "': " << strerror(errno) << std::endl;
        exit(1);
    }

    while (fp.good()) {
        fp.getline(buff,MAX_LINE);
        const char *type = strtok(buff, WS);
        const char *dep;
        if (!type || type[0] == '#')
            continue;
        Type t(type);
        while ((dep = strtok(NULL, WS)) != NULL) {
            t.depend.push_front(dep);
        }
        types.push_front(t);
    }
    fp.close();
    fp.clear(); // BSD does not reset flags in close().

    /*-------------------------------------------------------------------*
     * Parse input file
     *-------------------------------------------------------------------*/

    /* Open input file */
    fp.open(input_filename, std::ifstream::in);
    if (fp.fail()) {
        std::cerr << "Error while opening input file '" <<
                  input_filename << "': " << strerror(errno) << std::endl;
        exit(1);
    }

    state = sSTART;

    while (fp.getline(buff,MAX_LINE), fp.good() && state != sEXIT) {
        char *t;

        ++linenum;

        if ((t = strchr(buff, '\n')))
            *t = '\0';

        if (strncmp(buff, "IF ", 3) == 0) {
            if ((ptr = strtok(buff + 3, WS)) == NULL) {
                errorMsg(input_filename, linenum, "Missing IF parameter");
                exit(1);
            }
            IFDEFS.push(ptr);
            continue;
        } else if (strcmp(buff, "ENDIF") == 0) {
            if (IFDEFS.size() == 0) {
                errorMsg(input_filename, linenum, "ENDIF without IF first");
                exit(1);
            }
            IFDEFS.pop();
        } else if (!IFDEFS.size() || isDefined(IFDEFS.top()))
            switch (state) {

            case sSTART:

                if ((strlen(buff) == 0) || (!strncmp(buff, "#", 1))) {
                    /* ignore empty and comment lines */
                    (void) 0;
                } else if (!strncmp(buff, "NAME:", 5)) {
                    char *name, *aliasname;

                    if ((name = strtok(buff + 5, WS)) == NULL) {
                        errorMsg(input_filename, linenum, buff);
                        exit(1);
                    }

                    entries.push_back(name);

                    while ((aliasname = strtok(NULL, WS)) != NULL)
                        entries.back().alias.push_front(aliasname);

                    state = s1;
                } else if (!strcmp(buff, "EOF")) {
                    state = sEXIT;
                } else if (!strcmp(buff, "COMMENT_START")) {
                    entries.push_back("comment");
                    entries.back().loc = "none";
                    state = sDOC;
                } else {
                    errorMsg(input_filename, linenum, buff);
                    exit(1);
                }

                break;

            case s1: {
                Entry &curr = entries.back();

                if ((strlen(buff) == 0) || (!strncmp(buff, "#", 1))) {
                    /* ignore empty and comment lines */
                    (void) 0;
                } else if (!strncmp(buff, "COMMENT:", 8)) {
                    ptr = buff + 8;

                    while (isspace((unsigned char)*ptr))
                        ++ptr;

                    curr.comment = ptr;
                } else if (!strncmp(buff, "DEFAULT:", 8)) {
                    ptr = buff + 8;

                    while (isspace((unsigned char)*ptr))
                        ++ptr;

                    curr.defaults.preset.push_back(ptr);
                } else if (!strncmp(buff, "DEFAULT_IF_NONE:", 16)) {
                    ptr = buff + 16;

                    while (isspace((unsigned char)*ptr))
                        ++ptr;

                    curr.defaults.if_none.push_back(ptr);
                } else if (!strncmp(buff, "POSTSCRIPTUM:", 13)) {
                    ptr = buff + 13;

                    while (isspace((unsigned char)*ptr))
                        ++ptr;

                    curr.defaults.postscriptum.push_back(ptr);
                } else if (!strncmp(buff, "DEFAULT_DOC:", 12)) {
                    ptr = buff + 12;

                    while (isspace((unsigned char)*ptr))
                        ++ptr;

                    curr.defaults.docs.push_back(ptr);
                } else if (!strncmp(buff, "LOC:", 4)) {
                    if ((ptr = strtok(buff + 4, WS)) == NULL) {
                        errorMsg(input_filename, linenum, buff);
                        exit(1);
                    }

                    curr.loc = ptr;
                } else if (!strncmp(buff, "TYPE:", 5)) {
                    if ((ptr = strtok(buff + 5, WS)) == NULL) {
                        errorMsg(input_filename, linenum, buff);
                        exit(1);
                    }

                    /* hack to support arrays, rather than pointers */
                    if (0 == strcmp(ptr + strlen(ptr) - 2, "[]")) {
                        curr.array_flag = 1;
                        *(ptr + strlen(ptr) - 2) = '\0';
                    }

                    checkDepend(curr.name, ptr, types, entries);
                    curr.type = ptr;
                } else if (!strncmp(buff, "IFDEF:", 6)) {
                    if ((ptr = strtok(buff + 6, WS)) == NULL) {
                        errorMsg(input_filename, linenum, buff);
                        exit(1);
                    }

                    curr.ifdef = ptr;
                } else if (!strcmp(buff, "DOC_START")) {
                    state = sDOC;
                } else if (!strcmp(buff, "DOC_NONE")) {
                    state = sSTART;
                } else {
                    errorMsg(input_filename, linenum, buff);
                    exit(1);
                }
            }
            break;

            case sDOC:
                if (!strcmp(buff, "DOC_END") || !strcmp(buff, "COMMENT_END")) {
                    state = sSTART;
                } else if (!strcmp(buff, "NOCOMMENT_START")) {
                    state = sNOCOMMENT;
                } else { // if (buff != NULL) {
                    assert(buff != NULL);
                    entries.back().doc.push_back(buff);
                }
                break;

            case sNOCOMMENT:
                if (!strcmp(buff, "NOCOMMENT_END")) {
                    state = sDOC;
                } else { // if (buff != NULL) {
                    assert(buff != NULL);
                    entries.back().nocomment.push_back(buff);
                }
                break;

            case sEXIT:
                assert(0);      /* should never get here */
                break;
            }

    }

    if (state != sEXIT) {
        errorMsg(input_filename, linenum, "Error: unexpected EOF");
        exit(1);
    }

    fp.close();

    /*-------------------------------------------------------------------*
     * Generate default_all()
     * Generate parse_line()
     * Generate dump_config()
     * Generate free_all()
     * Generate example squid.conf.default file
     *-------------------------------------------------------------------*/

    /* Open output x.c file */

    std::ofstream fout(output_filename,std::ostream::out);
    if (!fout.good()) {
        std::cerr << "Error while opening output .c file '" <<
                  output_filename << "': " << strerror(errno) << std::endl;
        exit(1);
    }

    fout <<  "/*\n" <<
         " * Generated automatically from " << input_filename << " by " <<
         argv[0] << "\n"
         " *\n"
         " * Abstract: This file contains routines used to configure the\n"
         " *           variables in the squid server.\n"
         " */\n"
         "\n";

    rc = gen_default(entries, fout);

    gen_default_if_none(entries, fout);

    gen_default_postscriptum(entries, fout);

    gen_parse(entries, fout);

    gen_dump(entries, fout);

    gen_free(entries, fout);

    fout.close();

    /* Open output x.conf file */
    fout.open(conf_filename,std::ostream::out);
    if (!fout.good()) {
        std::cerr << "Error while opening output conf file '" <<
                  output_filename << "': " << strerror(errno) << std::endl;
        exit(1);
    }

    gen_conf(entries, fout, 1);

    fout.close();

    fout.open(conf_filename_short,std::ostream::out);
    if (!fout.good()) {
        std::cerr << "Error while opening output short conf file '" <<
                  output_filename << "': " << strerror(errno) << std::endl;
        exit(1);
    }
    gen_conf(entries, fout, 0);
    fout.close();

    return (rc);
}