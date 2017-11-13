static int CommandLineInterpreter(scr_t screenID, const char *commandLine)
{
    char *szCommand = "APACHE2 ";
    int iCommandLen = 8;
    char szcommandLine[256];
    char *pID;
    screenID = screenID;


    if (commandLine == NULL)
        return NOTMYCOMMAND;
    if (strlen(commandLine) <= strlen(szCommand))
        return NOTMYCOMMAND;

    strncpy (szcommandLine, commandLine, sizeof(szcommandLine)-1);

    /*  All added commands begin with "APACHE2 " */

    if (!strnicmp(szCommand, szcommandLine, iCommandLen)) {
        ActivateScreen (getscreenhandle());

        /* If an instance id was not given but the nlm is loaded in
            protected space, then the the command belongs to the
            OS address space instance to pass it on. */
        pID = strstr (szcommandLine, "-p");
        if ((pID == NULL) && nlmisloadedprotected())
            return NOTMYCOMMAND;

        /* If we got an instance id but it doesn't match this
            instance of the nlm, pass it on. */
        if (pID) {
            pID = &pID[2];
            while (*pID && (*pID == ' '))
                pID++;
        }
        if (pID && ap_my_addrspace && strnicmp(pID, ap_my_addrspace, strlen(ap_my_addrspace)))
            return NOTMYCOMMAND;

        /* If we have determined that this command belongs to this
            instance of the nlm, then handle it. */
        if (!strnicmp("RESTART",&szcommandLine[iCommandLen],3)) {
            printf("Restart Requested...\n");
            restart();
        }
        else if (!strnicmp("VERSION",&szcommandLine[iCommandLen],3)) {
            printf("Server version: %s\n", ap_get_server_version());
            printf("Server built:   %s\n", ap_get_server_built());
        }
        else if (!strnicmp("MODULES",&szcommandLine[iCommandLen],3)) {
            ap_show_modules();
        }
        else if (!strnicmp("DIRECTIVES",&szcommandLine[iCommandLen],3)) {
                ap_show_directives();
        }
        else if (!strnicmp("SHUTDOWN",&szcommandLine[iCommandLen],3)) {
            printf("Shutdown Requested...\n");
            shutdown_pending = 1;
        }
        else if (!strnicmp("SETTINGS",&szcommandLine[iCommandLen],3)) {
            if (show_settings) {
                show_settings = 0;
                ClearScreen (getscreenhandle());
                show_server_data();
            }
            else {
                show_settings = 1;
                display_settings();
            }
        }
        else {
            show_settings = 0;
            if (strnicmp("HELP",&szcommandLine[iCommandLen],3))
                printf("Unknown APACHE2 command %s\n", &szcommandLine[iCommandLen]);
            printf("Usage: APACHE2 [command] [-p <instance ID>]\n");
            printf("Commands:\n");
            printf("\tDIRECTIVES - Show directives\n");
            printf("\tHELP       - Display this help information\n");
            printf("\tMODULES    - Show a list of the loaded modules\n");
            printf("\tRESTART    - Reread the configuration file and restart Apache\n");
            printf("\tSETTINGS   - Show current thread status\n");
            printf("\tSHUTDOWN   - Shutdown Apache\n");
            printf("\tVERSION    - Display the server version information\n");
        }

        /*  Tell NetWare we handled the command */
        return HANDLEDCOMMAND;
    }

    /*  Tell NetWare that the command isn't mine */
    return NOTMYCOMMAND;
}