        fp = fopen(file_name, "r");
    }

    if (fp == NULL)
        fatalf("Unable to open configuration file: %s: %s", file_name, xstrerror());

#if _SQUID_WINDOWS_
    setmode(fileno(fp), O_TEXT);
#endif

    SetConfigFilename(file_name, bool(is_pipe));

    memset(config_input_line, '\0', BUFSIZ);

