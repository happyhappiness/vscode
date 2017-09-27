    apr_file_printf(errfile, " -n  Don't update file; display results on "
                    "stdout." NL);
    apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
        " (default)"
        "." NL);
    apr_file_printf(errfile, " -d  Force CRYPT encryption of the password"
            " (8 chars max, insecure)." NL);
    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext)." NL);
    apr_file_printf(errfile, " -s  Force SHA encryption of the password"
            " (insecure)." NL);
    apr_file_printf(errfile, " -b  Use the password from the command line "
            "rather than prompting for it." NL);
    apr_file_printf(errfile, " -D  Delete the specified user." NL);
    apr_file_printf(errfile,
            "On other systems than Windows and NetWare the '-p' flag will "
            "probably not work." NL);
