         dfr=N   Number of async ops queued for deferred release
         rel=N   Number of async ops released
         gc=N    Number of deferred-release async ops garbage collected
 
 63 events to collect in 13 groups
 */
-static void fscache_submit (const char *section, const char *name,
-        value_t value)
-{
-    value_list_t vl = VALUE_LIST_INIT;
-
-    vl.values = &value;
-    vl.values_len = 1;
-
-    sstrncpy(vl.host, hostname_g, sizeof (vl.host));
-    sstrncpy(vl.plugin, "fscache", sizeof (vl.plugin));
-    sstrncpy(vl.plugin_instance, section, sizeof (vl.plugin_instance));
-    sstrncpy(vl.type, "fscache_stat", sizeof(vl.type));
-    sstrncpy(vl.type_instance, name, sizeof(vl.type_instance));
+static void fscache_submit(const char *section, const char *name,
+                           value_t value) {
+  value_list_t vl = VALUE_LIST_INIT;
+
+  vl.values = &value;
+  vl.values_len = 1;
+
+  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
+  sstrncpy(vl.plugin, "fscache", sizeof(vl.plugin));
+  sstrncpy(vl.plugin_instance, section, sizeof(vl.plugin_instance));
+  sstrncpy(vl.type, "fscache_stat", sizeof(vl.type));
+  sstrncpy(vl.type_instance, name, sizeof(vl.type_instance));
 
-    plugin_dispatch_values (&vl);
+  plugin_dispatch_values(&vl);
 }
 
-static void fscache_read_stats_file (FILE *fh)
-{
-    char section[DATA_MAX_NAME_LEN];
-    size_t section_len;
+static void fscache_read_stats_file(FILE *fh) {
+  char section[DATA_MAX_NAME_LEN];
+  size_t section_len;
+
+  char linebuffer[BUFSIZE];
+
+  /*
+   *  cat /proc/fs/fscache/stats
+   *      FS-Cache statistics
+   *      Cookies: idx=2 dat=0 spc=0
+   *      Objects: alc=0 nal=0 avl=0 ded=0
+   *      ChkAux : non=0 ok=0 upd=0 obs=0
+   *      Pages  : mrk=0 unc=0
+   *      Acquire: n=2 nul=0 noc=0 ok=2 nbf=0 oom=0
+   *      Lookups: n=0 neg=0 pos=0 crt=0
+   *      Updates: n=0 nul=0 run=0
+   *      Relinqs: n=0 nul=0 wcr=0
+   *      AttrChg: n=0 ok=0 nbf=0 oom=0 run=0
+   *      Allocs : n=0 ok=0 wt=0 nbf=0
+   *      Allocs : ops=0 owt=0
+   *      Retrvls: n=0 ok=0 wt=0 nod=0 nbf=0 int=0 oom=0
+   *      Retrvls: ops=0 owt=0
+   *      Stores : n=0 ok=0 agn=0 nbf=0 oom=0
+   *      Stores : ops=0 run=0
+   *      Ops    : pend=0 run=0 enq=0
+   *      Ops    : dfr=0 rel=0 gc=0
+   */
+
+  /* Read file line by line */
+  while (fgets(linebuffer, sizeof(linebuffer), fh) != NULL) {
+    char *lineptr;
+    char *fields[32];
+    int fields_num;
+
+    /* Find the colon and replace it with a null byte */
+    lineptr = strchr(linebuffer, ':');
+    if (lineptr == NULL)
+      continue;
+    *lineptr = 0;
+    lineptr++;
+
+    /* Copy and clean up the section name */
+    sstrncpy(section, linebuffer, sizeof(section));
+    section_len = strlen(section);
+    while ((section_len > 0) && isspace((int)section[section_len - 1])) {
+      section_len--;
+      section[section_len] = 0;
+    }
+    if (section_len == 0)
+      continue;
 
-    char linebuffer[BUFSIZE];
+    fields_num = strsplit(lineptr, fields, STATIC_ARRAY_SIZE(fields));
+    if (fields_num <= 0)
+      continue;
+
+    for (int i = 0; i < fields_num; i++) {
+      char *field_name;
+      char *field_value_str;
+      value_t field_value_cnt;
+      int status;
+
+      field_name = fields[i];
+      assert(field_name != NULL);
+
+      field_value_str = strchr(field_name, '=');
+      if (field_value_str == NULL)
+        continue;
+      *field_value_str = 0;
+      field_value_str++;
+
+      status = parse_value(field_value_str, &field_value_cnt, DS_TYPE_DERIVE);
+      if (status != 0)
+        continue;
 
-/*
- *  cat /proc/fs/fscache/stats
- *      FS-Cache statistics
- *      Cookies: idx=2 dat=0 spc=0
- *      Objects: alc=0 nal=0 avl=0 ded=0
- *      ChkAux : non=0 ok=0 upd=0 obs=0
- *      Pages  : mrk=0 unc=0
- *      Acquire: n=2 nul=0 noc=0 ok=2 nbf=0 oom=0
- *      Lookups: n=0 neg=0 pos=0 crt=0
- *      Updates: n=0 nul=0 run=0
- *      Relinqs: n=0 nul=0 wcr=0
- *      AttrChg: n=0 ok=0 nbf=0 oom=0 run=0
- *      Allocs : n=0 ok=0 wt=0 nbf=0
- *      Allocs : ops=0 owt=0
- *      Retrvls: n=0 ok=0 wt=0 nod=0 nbf=0 int=0 oom=0
- *      Retrvls: ops=0 owt=0
- *      Stores : n=0 ok=0 agn=0 nbf=0 oom=0
- *      Stores : ops=0 run=0
- *      Ops    : pend=0 run=0 enq=0
- *      Ops    : dfr=0 rel=0 gc=0
- */
-
-    /* Read file line by line */
-    while (fgets (linebuffer, sizeof (linebuffer), fh) != NULL)
-    {
-        char *lineptr;
-        char *fields[32];
-        int fields_num;
-
-        /* Find the colon and replace it with a null byte */
-        lineptr = strchr (linebuffer, ':');
-        if (lineptr == NULL)
-            continue;
-        *lineptr = 0;
-        lineptr++;
-
-        /* Copy and clean up the section name */
-        sstrncpy (section, linebuffer, sizeof (section));
-        section_len = strlen (section);
-        while ((section_len > 0) && isspace ((int) section[section_len - 1]))
-        {
-            section_len--;
-            section[section_len] = 0;
-        }
-        if (section_len == 0)
-            continue;
-
-        fields_num = strsplit (lineptr, fields, STATIC_ARRAY_SIZE (fields));
-        if (fields_num <= 0)
-            continue;
-
-        for (int i = 0; i < fields_num; i++)
-        {
-            char *field_name;
-            char *field_value_str;
-            value_t field_value_cnt;
-            int status;
-
-            field_name = fields[i];
-            assert (field_name != NULL);
-
-            field_value_str = strchr (field_name, '=');
-            if (field_value_str == NULL)
-                continue;
-            *field_value_str = 0;
-            field_value_str++;
-
-            status = parse_value (field_value_str, &field_value_cnt,
-                    DS_TYPE_DERIVE);
-            if (status != 0)
-                continue;
-
-            fscache_submit (section, field_name, field_value_cnt);
-        }
-    } /* while (fgets) */
+      fscache_submit(section, field_name, field_value_cnt);
+    }
+  } /* while (fgets) */
 } /* void fscache_read_stats_file */
 
-static int fscache_read (void){
-    FILE *fh;
-    fh = fopen("/proc/fs/fscache/stats", "r");
-    if (fh != NULL){
-        fscache_read_stats_file(fh);
-        fclose(fh);
-
-    }else{
-        printf("cant open file\n");
-        return (-1);
-    }
-    return (0);
+static int fscache_read(void) {
+  FILE *fh;
+  fh = fopen("/proc/fs/fscache/stats", "r");
+  if (fh != NULL) {
+    fscache_read_stats_file(fh);
+    fclose(fh);
+
+  } else {
+    printf("cant open file\n");
+    return (-1);
+  }
+  return (0);
 }
 
-void module_register (void)
-{
-    plugin_register_read ("fscache", fscache_read);
+void module_register(void) {
+  plugin_register_read("fscache", fscache_read);
 } /* void module_register */
 
 /* vim: set sw=4 sts=4 et : */
