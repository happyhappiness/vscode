 
 #include "collectd.h"
 #include "common.h"
 #include "plugin.h"
 
 #include "utils_cache.h"
+#include "utils_parse_option.h"
 
 #define print_to_socket(fh, ...) \
   if (fprintf (fh, __VA_ARGS__) < 0) { \
     char errbuf[1024]; \
     WARNING ("handle_getval: failed to write to socket #%i: %s", \
 	fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
     return -1; \
   }
 
-int handle_getval (FILE *fh, char **fields, int fields_num)
+int handle_getval (FILE *fh, char *buffer)
 {
+  char *command;
+  char *identifier;
+  char *identifier_copy;
+
   char *hostname;
   char *plugin;
   char *plugin_instance;
   char *type;
   char *type_instance;
   gauge_t *values;
   size_t values_num;
 
-  char *identifier_copy;
-
   const data_set_t *ds;
 
   int   status;
   int   i;
 
-  if (fields_num != 2)
+  if ((fh == NULL) || (buffer == NULL))
+    return (-1);
+
+  DEBUG ("utils_cmd_getval: handle_getval (fh = %p, buffer = %s);",
+      (void *) fh, buffer);
+
+  command = NULL;
+  status = parse_string (&buffer, &command);
+  if (status != 0)
   {
-    DEBUG ("unixsock plugin: Wrong number of fields: %i", fields_num);
-    print_to_socket (fh, "-1 Wrong number of fields: Got %i, expected 2.\n",
-	fields_num);
+    print_to_socket (fh, "-1 Cannot parse command.\n");
     return (-1);
   }
-  DEBUG ("unixsock plugin: Got query for `%s'", fields[1]);
+  assert (command != NULL);
 
-  if (strlen (fields[1]) < strlen ("h/p/t"))
+  if (strcasecmp ("GETVAL", command) != 0)
   {
-    print_to_socket (fh, "-1 Invalied identifier, %s\n", fields[1]);
+    print_to_socket (fh, "-1 Unexpected command: `%s'.\n", command);
+    return (-1);
+  }
+
+  identifier = NULL;
+  status = parse_string (&buffer, &identifier);
+  if (status != 0)
+  {
+    print_to_socket (fh, "-1 Cannot parse identifier.\n");
+    return (-1);
+  }
+  assert (identifier != NULL);
+
+  if (*buffer != 0)
+  {
+    print_to_socket (fh, "-1 Garbage after end of command: %s\n", buffer);
     return (-1);
   }
 
   /* parse_identifier() modifies its first argument,
    * returning pointers into it */
-  identifier_copy = sstrdup (fields[1]);
+  identifier_copy = sstrdup (identifier);
 
   status = parse_identifier (identifier_copy, &hostname,
       &plugin, &plugin_instance,
       &type, &type_instance);
   if (status != 0)
   {
-    DEBUG ("unixsock plugin: Cannot parse `%s'", fields[1]);
-    print_to_socket (fh, "-1 Cannot parse identifier.\n");
+    DEBUG ("handle_getval: Cannot parse identifier `%s'.", identifier);
+    print_to_socket (fh, "-1 Cannot parse identifier `%s'.\n", identifier);
     sfree (identifier_copy);
     return (-1);
   }
 
   ds = plugin_get_ds (type);
   if (ds == NULL)
   {
-    DEBUG ("unixsock plugin: plugin_get_ds (%s) == NULL;", type);
+    DEBUG ("handle_getval: plugin_get_ds (%s) == NULL;", type);
     print_to_socket (fh, "-1 Type `%s' is unknown.\n", type);
     sfree (identifier_copy);
     return (-1);
   }
 
   values = NULL;
   values_num = 0;
-  status = uc_get_rate_by_name (fields[1], &values, &values_num);
+  status = uc_get_rate_by_name (identifier, &values, &values_num);
   if (status != 0)
   {
     print_to_socket (fh, "-1 No such value\n");
     sfree (identifier_copy);
     return (-1);
   }
