 }
 
 /* Print generic help. */
 static void cliOutputGenericHelp(void) {
     sds version = cliVersion();
     printf(
-        "redis-cli %s\r\n"
-        "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
-        "      \"help <command>\" for help on <command>\r\n"
-        "      \"help <tab>\" to get a list of possible help topics\r\n"
-        "      \"quit\" to exit\r\n",
+        "redis-cli %s\n"
+        "To get help about Redis commands type:\n"
+        "      \"help @<group>\" to get a list of commands in <group>\n"
+        "      \"help <command>\" for help on <command>\n"
+        "      \"help <tab>\" to get a list of possible help topics\n"
+        "      \"quit\" to exit\n"
+        "\n"
+        "To set redis-cli perferences:\n"
+        "      \":set hints\" enable online hints\n"
+        "      \":set nohints\" disable online hints\n"
+        "Set your preferences in ~/.redisclirc\n",
         version
     );
     sdsfree(version);
 }
 
 /* Output all command help, filtering by group or command name. */
