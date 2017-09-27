     expanded_path = newarg;
 #endif
 
     return expanded_path;
 }
 
+void add_dynamic_link_opts(command_t *cmd_data, count_chars *args)
+{
+#ifdef DYNAMIC_LINK_OPTS
+    if (cmd_data->options.pic_mode != pic_AVOID) {
+        if (!cmd_data->options.silent) {
+           printf("Adding: %s\n", DYNAMIC_LINK_OPTS);
+        }
+        push_count_chars(args, DYNAMIC_LINK_OPTS);
+        if (cmd_data->undefined_flag) {
+            push_count_chars(args, "-undefined");
+#if defined(__APPLE__)
+            /* -undefined dynamic_lookup is used by the bundled Python in
+             * 10.4, but if we don't set MACOSX_DEPLOYMENT_TARGET to 10.3+,
+             * we'll get a linker error if we pass this flag.
+             */
+            if (strcasecmp(cmd_data->undefined_flag,
+                           "dynamic_lookup") == 0) {
+                insert_count_chars(cmd_data->program_opts,
+                                   "MACOSX_DEPLOYMENT_TARGET=10.3", 0);
+            }
+#endif
+            push_count_chars(args, cmd_data->undefined_flag);
+        }
+        else {
+#ifdef DYNAMIC_LINK_UNDEFINED
+            if (!cmd_data->options.silent) {
+                printf("Adding: %s\n", DYNAMIC_LINK_UNDEFINED);
+            }
+            push_count_chars(args, DYNAMIC_LINK_UNDEFINED);
+#endif
+        }
+    }
+#endif
+}
+
 /* Read the final install location and add it to runtime library search path. */
 #ifdef RPATH
 void add_rpath(count_chars *cc, const char *path)
 {
     int size = 0;
     char *tmp;
