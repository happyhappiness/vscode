             fprintf(stderr, "%s: ERROR: Input Too Large: %s\n", program_name, line);
             while (fgets(line, sizeof(line), stdin)) {
                 fprintf(stderr, "%s: ERROR: Input Too Large..: %s\n", program_name, line);
                 if (strchr(line, '\n') != NULL)
                     break;
             }
-            SEND_ERR("Input Too Large.");
+            SEND_BH(HLP_MSG("Input Too Large."));
             continue;
         }
         *cp = '\0';
         address = strtok(line, " \t");
         username = strtok(NULL, " \t");
         if (!address || !username) {
             debug("%s: unable to read tokens\n", program_name);
-            SEND_ERR("Invalid Input.");
+            SEND_BH(HLP_MSG("Invalid Input."));
             continue;
         }
         rfc1738_unescape(address);
         rfc1738_unescape(username);
         int result = dict_lookup(current_entry, username, address);
         debug("%s: result: %d\n", program_name, result);
