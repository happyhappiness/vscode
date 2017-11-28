             fprintf(stderr, "%s: ERROR: Too large: %s\n", argv[0], buf);
             while (fgets(buf, HELPER_INPUT_BUFFER, stdin)) {
                 fprintf(stderr, "%s: ERROR: Too large..: %s\n", argv[0], buf);
                 if (strchr(buf, '\n') != NULL)
                     break;
             }
-            SEND_ERR("Invalid Request. Too Long.");
+            SEND_BH(HLP_MSG("Invalid Request. Too Long."));
             continue;
         }
         if ((p = strchr(buf, '\n')) != NULL)
-            *p = '\0';		/* strip \n */
+            *p = '\0';      /* strip \n */
         if ((p = strchr(buf, '\r')) != NULL)
-            *p = '\0';		/* strip \r */
+            *p = '\0';      /* strip \r */
 
         debug("Got '%s' from Squid (length: %d).\n", buf, strlen(buf));
 
         if (buf[0] == '\0') {
-            SEND_ERR("Invalid Request. No Input.");
+            SEND_BH(HLP_MSG("Invalid Request. No Input."));
             continue;
         }
         username = strtok(buf, " ");
         for (n = 0; (group = strtok(NULL, " ")) != NULL; ++n) {
             rfc1738_unescape(group);
             groups[n] = group;
         }
         groups[n] = NULL;
         numberofgroups = n;
 
         if (NULL == username) {
-            SEND_ERR("Invalid Request. No Username.");
+            SEND_BH(HLP_MSG("Invalid Request. No Username."));
             continue;
         }
         rfc1738_unescape(username);
 
         if ((use_global ? Valid_Global_Groups(username, groups) : Valid_Local_Groups(username, groups))) {
             SEND_OK("");
