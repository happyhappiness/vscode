    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext)." NL);
    apr_file_printf(errfile, " -s  Force SHA encryption of the password." NL);
    apr_file_printf(errfile, " -b  Use the password from the command line "
            "rather than prompting for it." NL);
    apr_file_printf(errfile, " -D  Delete the specified user." NL);
    apr_file_printf(errfile,
            "On other systems than Windows and NetWare the '-p' flag will "
            "probably not work." NL);
    apr_file_printf(errfile,
            "The SHA algorithm does not use a salt and is less secure than "
            "the MD5 algorithm." NL);
    exit(ERR_SYNTAX);
}
