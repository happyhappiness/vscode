static void usage(void)
{
    apr_file_printf(errfile, "Usage:" NL);
    apr_file_printf(errfile, "\thtpasswd [-cmdpsD] passwordfile username" NL);
    apr_file_printf(errfile, "\thtpasswd -b[cmdpsD] passwordfile username "
                    "password" NL NL);
    apr_file_printf(errfile, "\thtpasswd -n[mdps] username" NL);
    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password" NL);
    apr_file_printf(errfile, " -c  Create a new file." NL);
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
    apr_file_printf(errfile,
            "The SHA algorithm does not use a salt and is less secure than "
            "the MD5 algorithm." NL);
    exit(ERR_SYNTAX);
}