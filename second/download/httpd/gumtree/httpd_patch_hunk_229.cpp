 #endif
             ".\n");
     apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext).\n");
     apr_file_printf(errfile, " -s  Force SHA encryption of the password.\n");
     apr_file_printf(errfile, " -b  Use the password from the command line "
             "rather than prompting for it.\n");
+    apr_file_printf(errfile, " -D  Delete the specified user.\n");
     apr_file_printf(errfile,
             "On Windows, NetWare and TPF systems the '-m' flag is used by "
             "default.\n");
     apr_file_printf(errfile,
             "On all other systems, the '-p' flag will probably not work.\n");
     exit(ERR_SYNTAX);
