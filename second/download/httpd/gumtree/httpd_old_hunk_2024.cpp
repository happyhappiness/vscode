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
