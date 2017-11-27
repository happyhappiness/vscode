 
 #include "collectd.h"
 
 #include "common.h"
 #include "plugin.h"
 #include "utils_cmd_flush.h"
-#include "utils_parse_option.h"
 
-int handle_flush(FILE *fh, char *buffer) {
-  int success = 0;
-  int error = 0;
-
-  double timeout = 0.0;
-  char **plugins = NULL;
-  size_t plugins_num = 0;
-  char **identifiers = NULL;
-  size_t identifiers_num = 0;
-
-#define PRINT_TO_SOCK(fh, ...)                                                 \
-  do {                                                                         \
-    if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
-      char errbuf[1024];                                                       \
-      WARNING("handle_flush: failed to write to socket #%i: %s", fileno(fh),   \
-              sstrerror(errno, errbuf, sizeof(errbuf)));                       \
-      strarray_free(plugins, plugins_num);                                     \
-      strarray_free(identifiers, identifiers_num);                             \
-      return -1;                                                               \
-    }                                                                          \
-    fflush(fh);                                                                \
-  } while (0)
-
-  if ((fh == NULL) || (buffer == NULL))
-    return (-1);
-
-  DEBUG("utils_cmd_flush: handle_flush (fh = %p, buffer = %s);", (void *)fh,
-        buffer);
-
-  if (strncasecmp("FLUSH", buffer, strlen("FLUSH")) != 0) {
-    PRINT_TO_SOCK(fh, "-1 Cannot parse command.\n");
-    return (-1);
+cmd_status_t cmd_parse_flush(size_t argc, char **argv, cmd_flush_t *ret_flush,
+                             const cmd_options_t *opts,
+                             cmd_error_handler_t *err) {
+
+  if ((ret_flush == NULL) || (opts == NULL)) {
+    errno = EINVAL;
+    cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_flush.");
+    return (CMD_ERROR);
   }
-  buffer += strlen("FLUSH");
 
-  while (*buffer != 0) {
+  for (size_t i = 0; i < argc; i++) {
     char *opt_key;
     char *opt_value;
     int status;
 
     opt_key = NULL;
     opt_value = NULL;
-    status = parse_option(&buffer, &opt_key, &opt_value);
+    status = cmd_parse_option(argv[i], &opt_key, &opt_value, err);
     if (status != 0) {
-      PRINT_TO_SOCK(fh, "-1 Parsing options failed.\n");
-      strarray_free(plugins, plugins_num);
-      strarray_free(identifiers, identifiers_num);
-      return (-1);
+      if (status == CMD_NO_OPTION)
+        cmd_error(CMD_PARSE_ERROR, err, "Invalid option string `%s'.", argv[i]);
+      cmd_destroy_flush(ret_flush);
+      return (CMD_PARSE_ERROR);
     }
 
-    if (strcasecmp("plugin", opt_key) == 0)
-      strarray_add(&plugins, &plugins_num, opt_value);
-    else if (strcasecmp("identifier", opt_key) == 0)
-      strarray_add(&identifiers, &identifiers_num, opt_value);
-    else if (strcasecmp("timeout", opt_key) == 0) {
+    if (strcasecmp("plugin", opt_key) == 0) {
+      strarray_add(&ret_flush->plugins, &ret_flush->plugins_num, opt_value);
+    } else if (strcasecmp("identifier", opt_key) == 0) {
+      identifier_t *id =
+          realloc(ret_flush->identifiers,
+                  (ret_flush->identifiers_num + 1) * sizeof(*id));
+      if (id == NULL) {
+        cmd_error(CMD_ERROR, err, "realloc failed.");
+        cmd_destroy_flush(ret_flush);
+        return (CMD_ERROR);
+      }
+
+      ret_flush->identifiers = id;
+      id = ret_flush->identifiers + ret_flush->identifiers_num;
+      ret_flush->identifiers_num++;
+      if (parse_identifier(opt_value, &id->host, &id->plugin,
+                           &id->plugin_instance, &id->type, &id->type_instance,
+                           opts->identifier_default_host) != 0) {
+        cmd_error(CMD_PARSE_ERROR, err, "Invalid identifier `%s'.", opt_value);
+        cmd_destroy_flush(ret_flush);
+        return (CMD_PARSE_ERROR);
+      }
+    } else if (strcasecmp("timeout", opt_key) == 0) {
       char *endptr;
 
       errno = 0;
       endptr = NULL;
-      timeout = strtod(opt_value, &endptr);
+      ret_flush->timeout = strtod(opt_value, &endptr);
 
-      if ((endptr == opt_value) || (errno != 0) || (!isfinite(timeout))) {
-        PRINT_TO_SOCK(fh, "-1 Invalid value for option `timeout': "
-                          "%s\n",
-                      opt_value);
-        strarray_free(plugins, plugins_num);
-        strarray_free(identifiers, identifiers_num);
-        return (-1);
-      } else if (timeout < 0.0) {
-        timeout = 0.0;
+      if ((endptr == opt_value) || (errno != 0) ||
+          (!isfinite(ret_flush->timeout))) {
+        cmd_error(CMD_PARSE_ERROR, err,
+                  "Invalid value for option `timeout': %s", opt_value);
+        cmd_destroy_flush(ret_flush);
+        return (CMD_PARSE_ERROR);
+      } else if (ret_flush->timeout < 0.0) {
+        ret_flush->timeout = 0.0;
       }
     } else {
-      PRINT_TO_SOCK(fh, "-1 Cannot parse option %s\n", opt_key);
-      strarray_free(plugins, plugins_num);
-      strarray_free(identifiers, identifiers_num);
-      return (-1);
+      cmd_error(CMD_PARSE_ERROR, err, "Cannot parse option `%s'.", opt_key);
+      cmd_destroy_flush(ret_flush);
+      return (CMD_PARSE_ERROR);
     }
-  } /* while (*buffer != 0) */
+  }
 
-  for (size_t i = 0; (i == 0) || (i < plugins_num); i++) {
+  return (CMD_OK);
+} /* cmd_status_t cmd_parse_flush */
+
+cmd_status_t cmd_handle_flush(FILE *fh, char *buffer) {
+  cmd_error_handler_t err = {cmd_error_fh, fh};
+  cmd_t cmd;
+
+  int success = 0;
+  int error = 0;
+  int status;
+
+  if ((fh == NULL) || (buffer == NULL))
+    return (-1);
+
+  DEBUG("utils_cmd_flush: cmd_handle_flush (fh = %p, buffer = %s);", (void *)fh,
+        buffer);
+
+  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
+    return (status);
+  if (cmd.type != CMD_FLUSH) {
+    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
+              CMD_TO_STRING(cmd.type));
+    cmd_destroy(&cmd);
+    return (CMD_UNKNOWN_COMMAND);
+  }
+
+  for (size_t i = 0; (i == 0) || (i < cmd.cmd.flush.plugins_num); i++) {
     char *plugin = NULL;
 
-    if (plugins_num != 0)
-      plugin = plugins[i];
+    if (cmd.cmd.flush.plugins_num != 0)
+      plugin = cmd.cmd.flush.plugins[i];
 
-    for (size_t j = 0; (j == 0) || (j < identifiers_num); j++) {
+    for (size_t j = 0; (j == 0) || (j < cmd.cmd.flush.identifiers_num); j++) {
       char *identifier = NULL;
+      char buffer[1024];
       int status;
 
-      if (identifiers_num != 0)
-        identifier = identifiers[j];
+      if (cmd.cmd.flush.identifiers_num != 0) {
+        identifier_t *id = cmd.cmd.flush.identifiers + j;
+        if (format_name(buffer, sizeof(buffer), id->host, id->plugin,
+                        id->plugin_instance, id->type,
+                        id->type_instance) != 0) {
+          error++;
+          continue;
+        }
+        identifier = buffer;
+      }
 
-      status = plugin_flush(plugin, DOUBLE_TO_CDTIME_T(timeout), identifier);
+      status = plugin_flush(plugin, DOUBLE_TO_CDTIME_T(cmd.cmd.flush.timeout),
+                            identifier);
       if (status == 0)
         success++;
       else
         error++;
     }
   }
 
-  PRINT_TO_SOCK(fh, "0 Done: %i successful, %i errors\n", success, error);
+  cmd_error(CMD_OK, &err, "Done: %i successful, %i errors", success, error);
 
-  strarray_free(plugins, plugins_num);
-  strarray_free(identifiers, identifiers_num);
+  cmd_destroy(&cmd);
   return (0);
 #undef PRINT_TO_SOCK
-} /* int handle_flush */
+} /* cmd_status_t cmd_handle_flush */
+
+void cmd_destroy_flush(cmd_flush_t *flush) {
+  if (flush == NULL)
+    return;
+
+  strarray_free(flush->plugins, flush->plugins_num);
+  flush->plugins = NULL;
+  flush->plugins_num = 0;
+
+  sfree(flush->identifiers);
+  flush->identifiers_num = 0;
+} /* void cmd_destroy_flush */
 
 /* vim: set sw=4 ts=4 tw=78 noexpandtab : */
