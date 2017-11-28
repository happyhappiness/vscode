static int
parseOneConfigFile(const char *file_name, unsigned int depth)
{
    FILE *fp = NULL;
    const char *orig_cfg_filename = cfg_filename;
    const int orig_config_lineno = config_lineno;
    char *token = NULL;
    char *tmp_line = NULL;
    int tmp_line_len = 0;
    int err_count = 0;
    int is_pipe = 0;

    debugs(3, 1, "Processing Configuration File: " << file_name << " (depth " << depth << ")");
    if (depth > 16) {
        fatalf("WARNING: can't include %s: includes are nested too deeply (>16)!\n", file_name);
        return 1;
    }

    if (file_name[0] == '!' || file_name[0] == '|') {
        fp = popen(file_name + 1, "r");
        is_pipe = 1;
    } else {
        fp = fopen(file_name, "r");
    }

    if (fp == NULL)
        fatalf("Unable to open configuration file: %s: %s", file_name, xstrerror());

#if _SQUID_WINDOWS_
    setmode(fileno(fp), O_TEXT);
#endif

    SetConfigFilename(file_name, bool(is_pipe));

    memset(config_input_line, '\0', BUFSIZ);

    config_lineno = 0;

    Vector<bool> if_states;
    while (fgets(config_input_line, BUFSIZ, fp)) {
        ++config_lineno;

        if ((token = strchr(config_input_line, '\n')))
            *token = '\0';

        if ((token = strchr(config_input_line, '\r')))
            *token = '\0';

        // strip any prefix whitespace off the line.
        const char *p = skip_ws(config_input_line);
        if (config_input_line != p)
            memmove(config_input_line, p, strlen(p)+1);

        if (strncmp(config_input_line, "#line ", 6) == 0) {
            static char new_file_name[1024];
            static char *file;
            static char new_lineno;
            token = config_input_line + 6;
            new_lineno = strtol(token, &file, 0) - 1;

            if (file == token)
                continue;	/* Not a valid #line directive, may be a comment */

            while (*file && xisspace((unsigned char) *file))
                ++file;

            if (*file) {
                if (*file != '"')
                    continue;	/* Not a valid #line directive, may be a comment */

                xstrncpy(new_file_name, file + 1, sizeof(new_file_name));

                if ((token = strchr(new_file_name, '"')))
                    *token = '\0';

                cfg_filename = new_file_name;
            }

            config_lineno = new_lineno;
        }

        if (config_input_line[0] == '#')
            continue;

        if (config_input_line[0] == '\0')
            continue;

        const char* append = tmp_line_len ? skip_ws(config_input_line) : config_input_line;

        size_t append_len = strlen(append);

        tmp_line = (char*)xrealloc(tmp_line, tmp_line_len + append_len + 1);

        strcpy(tmp_line + tmp_line_len, append);

        tmp_line_len += append_len;

        if (tmp_line[tmp_line_len-1] == '\\') {
            debugs(3, 5, "parseConfigFile: tmp_line='" << tmp_line << "'");
            tmp_line[--tmp_line_len] = '\0';
            continue;
        }

        trim_trailing_ws(tmp_line);
        ProcessMacros(tmp_line, tmp_line_len);
        debugs(3, (opt_parse_cfg_only?1:5), "Processing: " << tmp_line);

        if (const char* expr = FindStatement(tmp_line, "if")) {
            if_states.push_back(EvalBoolExpr(expr)); // store last if-statement meaning
        } else if (FindStatement(tmp_line, "endif")) {
            if (!if_states.empty())
                if_states.pop_back(); // remove last if-statement meaning
            else
                fatalf("'endif' without 'if'\n");
        } else if (FindStatement(tmp_line, "else")) {
            if (!if_states.empty())
                if_states.back() = !if_states.back();
            else
                fatalf("'else' without 'if'\n");
        } else if (if_states.empty() || if_states.back()) { // test last if-statement meaning if present
            /* Handle includes here */
            if (tmp_line_len >= 9 && strncmp(tmp_line, "include", 7) == 0 && xisspace(tmp_line[7])) {
                err_count += parseManyConfigFiles(tmp_line + 8, depth + 1);
            } else if (!parse_line(tmp_line)) {
                debugs(3, 0, HERE << cfg_filename << ":" << config_lineno << " unrecognized: '" << tmp_line << "'");
                ++err_count;
            }
        }

        safe_free(tmp_line);
        tmp_line_len = 0;

    }
    if (!if_states.empty())
        fatalf("if-statement without 'endif'\n");

    if (is_pipe) {
        int ret = pclose(fp);

        if (ret != 0)
            fatalf("parseConfigFile: '%s' failed with exit code %d\n", file_name, ret);
    } else {
        fclose(fp);
    }

    cfg_filename = orig_cfg_filename;
    config_lineno = orig_config_lineno;

    xfree(tmp_line);
    return err_count;
}