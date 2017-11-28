        NULL
    };
    ConfigParser::ParseString(&name);
    ConfigParser::ParseQuotedString(&value);

    // TODO: Find a way to move this check to ICAP
    for (int i = 0; warnFor[i] != NULL; i++) {
        if (name.caseCmp(warnFor[i]) == 0) {
            fatalf("%s:%d: meta name \"%s\" is a reserved ICAP header name",
                   cfg_filename, config_lineno, name.termedBuf());
        }
    }

