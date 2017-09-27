                 show_settings = 1;
                 display_settings();
             }
         }
         else {
             show_settings = 0;
-            if (!strnicmp("HELP",&szcommandLine[iCommandLen],3))
+            if (strnicmp("HELP",&szcommandLine[iCommandLen],3))
                 printf("Unknown APACHE2 command %s\n", &szcommandLine[iCommandLen]);
             printf("Usage: APACHE2 [command] [-p <instance ID>]\n");
             printf("Commands:\n");
             printf("\tDIRECTIVES - Show directives\n");
             printf("\tHELP       - Display this help information\n");
             printf("\tMODULES    - Show a list of the loaded modules\n");
-            printf("\tRESTART    - Reread the configurtion file and restart Apache\n");
+            printf("\tRESTART    - Reread the configuration file and restart Apache\n");
             printf("\tSETTINGS   - Show current thread status\n");
             printf("\tSHUTDOWN   - Shutdown Apache\n");
             printf("\tVERSION    - Display the server version information\n");
         }
 
         /*  Tell NetWare we handled the command */
