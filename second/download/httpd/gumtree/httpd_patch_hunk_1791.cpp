     strcpy(newarg, LINKER_FLAG_PREFIX);
     strcat(newarg, arg);
     push_count_chars(cc, newarg);
 #endif
 }
 
+/* returns just a file's name without the path */
+const char *jlibtool_basename(const char *fullpath)
+{
+    const char *name = strrchr(fullpath, '/');
+
+    if (name == NULL) {
+        name = strrchr(fullpath, '\\');
+    }
+
+    if (name == NULL) {
+        name = fullpath;
+    } else {
+        name++;
+    }
+
+    return name;
+}
+
+/* returns just a file's name without path or extension */
+const char *nameof(const char *fullpath)
+{
+    const char *name;
+    const char *ext;
+
+    name = jlibtool_basename(fullpath);
+    ext = strrchr(name, '.');
+
+    if (ext) {
+        char *trimmed;
+        trimmed = malloc(ext - name + 1);
+        strncpy(trimmed, name, ext - name);
+        trimmed[ext-name] = 0;
+        return trimmed;
+    }
+
+    return name;
+}
+
+int explode_static_lib(command_t *cmd_data, const char *lib)
+{
+    count_chars tmpdir_cc, libname_cc;
+    const char *tmpdir, *libname;
+    char savewd[PATH_MAX];
+    const char *name;
+    DIR *dir;
+    struct dirent *entry;
+    const char *lib_args[4];
+
+    /* Bah! */
+    if (cmd_data->options.dry_run) {
+        return 0;
+    }
+
+    name = jlibtool_basename(lib);
+
+    init_count_chars(&tmpdir_cc);
+    push_count_chars(&tmpdir_cc, ".libs/");
+    push_count_chars(&tmpdir_cc, name);
+    push_count_chars(&tmpdir_cc, ".exploded/");
+    tmpdir = flatten_count_chars(&tmpdir_cc, 0);
+
+    if (!cmd_data->options.silent) {
+        printf("Making: %s\n", tmpdir);
+    }
+    safe_mkdir(tmpdir);
+
+    push_count_chars(cmd_data->tmp_dirs, tmpdir);
+
+    getcwd(savewd, sizeof(savewd));
+
+    if (chdir(tmpdir) != 0) {
+        if (!cmd_data->options.silent) {
+            printf("Warning: could not explode %s\n", lib);
+        }
+        return 1;
+    }
+
+    if (lib[0] == '/') {
+        libname = lib;
+    }
+    else {
+        init_count_chars(&libname_cc);
+        push_count_chars(&libname_cc, "../../");
+        push_count_chars(&libname_cc, lib);
+        libname = flatten_count_chars(&libname_cc, 0);
+    }
+
+    lib_args[0] = LIBRARIAN;
+    lib_args[1] = "x";
+    lib_args[2] = libname;
+    lib_args[3] = NULL;
+
+    external_spawn(cmd_data, LIBRARIAN, lib_args);
+
+    chdir(savewd);
+    dir = opendir(tmpdir);
+
+    while ((entry = readdir(dir)) != NULL) {
+#if defined(__APPLE__) && defined(RANLIB)
+        /* Apple inserts __.SYMDEF which isn't needed.
+         * Leopard (10.5+) can also add '__.SYMDEF SORTED' which isn't
+         * much fun either.  Just skip them.
+         */
+        if (strstr(entry->d_name, "__.SYMDEF") != NULL) {
+            continue;
+        }
+#endif
+        if (entry->d_name[0] != '.') {
+            push_count_chars(&tmpdir_cc, entry->d_name);
+            name = flatten_count_chars(&tmpdir_cc, 0);
+            if (!cmd_data->options.silent) {
+                printf("Adding: %s\n", name);
+            }
+            push_count_chars(cmd_data->obj_files, name);
+            pop_count_chars(&tmpdir_cc);
+        }
+    }
+
+    closedir(dir);
+    return 0;
+}
+
 int parse_input_file_name(char *arg, command_t *cmd_data)
 {
     char *ext = strrchr(arg, '.');
     char *name = strrchr(arg, '/');
     int pathlen;
     enum lib_type libtype;
