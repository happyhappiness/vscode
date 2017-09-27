
            apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
                    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));
            exit(1);
        }
        apr_file_printf(errfile, "Adding password for %s in realm %s.\n",
                    argv[4], argv[3]);
        add_password(argv[4], argv[3], f);
        apr_file_close(f);
        exit(0);
    }
    else if (argc != 4)
        usage();

