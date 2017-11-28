         snprintf((char *) service.value, strlen(service_name) + strlen(host_name) + 2,
                  "%s@%s", service_name, host_name);
         service.length = strlen((char *) service.value);
         xfree(host_name);
     }
 
+    if (rcache_type) {
+        rcache_type_env = (char *) xmalloc(strlen("KRB5RCACHETYPE=")+strlen(rcache_type)+1);
+        strcpy(rcache_type_env, "KRB5RCACHETYPE=");
+        strcat(rcache_type_env, rcache_type);
+        putenv(rcache_type_env);
+        debug((char *) "%s| %s: INFO: Setting replay cache type to %s\n",
+              LogTime(), PROGRAM, rcache_type);
+    }
+
+    if (rcache_dir) {
+        rcache_dir_env = (char *) xmalloc(strlen("KRB5RCACHEDIR=")+strlen(rcache_dir)+1);
+        strcpy(rcache_dir_env, "KRB5RCACHEDIR=");
+        strcat(rcache_dir_env, rcache_dir);
+        putenv(rcache_dir_env);
+        debug((char *) "%s| %s: INFO: Setting replay cache directory to %s\n",
+              LogTime(), PROGRAM, rcache_dir);
+    }
+
+    if (keytab_name) {
+        keytab_name_env = (char *) xmalloc(strlen("KRB5_KTNAME=")+strlen(keytab_name)+1);
+        strcpy(keytab_name_env, "KRB5_KTNAME=");
+        strcat(keytab_name_env, keytab_name);
+        putenv(keytab_name_env);
+    } else {
+        keytab_name_env = getenv("KRB5_KTNAME");
+        if (!keytab_name_env) {
+            ret = krb5_init_context(&context);
+            if (!check_k5_err(context, "krb5_init_context", ret)) {
+                krb5_kt_default_name(context, default_keytab, MAXPATHLEN);
+            }
+            keytab_name = xstrdup(default_keytab);
+            krb5_free_context(context);
+        } else
+            keytab_name = xstrdup(keytab_name_env);
+    }
+    debug((char *) "%s| %s: INFO: Setting keytab to %s\n", LogTime(), PROGRAM, keytab_name);
+#if HAVE_KRB5_MEMORY_KEYTAB
+    ret = krb5_init_context(&context);
+    if (!check_k5_err(context, "krb5_init_context", ret)) {
+        memory_keytab_name = (char *)xmalloc(strlen("MEMORY:negotiate_kerberos_auth_")+16);
+        snprintf(memory_keytab_name, strlen("MEMORY:negotiate_kerberos_auth_")+16,
+                 "MEMORY:negotiate_kerberos_auth_%d", (unsigned int) getpid());
+        ret = krb5_read_keytab(context, keytab_name, &ktlist);
+        if (check_k5_err(context, "krb5_read_keytab", ret)) {
+            debug((char *) "%s| %s: ERROR: Reading keytab %s into list failed\n",
+                  LogTime(), PROGRAM, keytab_name);
+        } else {
+            ret = krb5_write_keytab(context, ktlist, memory_keytab_name);
+            if (check_k5_err(context, "krb5_write_keytab", ret)) {
+                debug((char *) "%s| %s: ERROR: Writing list into keytab %s\n",
+                      LogTime(), PROGRAM, memory_keytab_name);
+            } else {
+                keytab_name_env = (char *) xmalloc(strlen("KRB5_KTNAME=")+strlen(memory_keytab_name)+1);
+                strcpy(keytab_name_env, "KRB5_KTNAME=");
+                strcat(keytab_name_env, memory_keytab_name);
+                putenv(keytab_name_env);
+                xfree(keytab_name);
+                keytab_name = xstrdup(memory_keytab_name);
+                debug((char *) "%s| %s: INFO: Changed keytab to %s\n",
+                      LogTime(), PROGRAM, memory_keytab_name);
+            }
+        }
+        ret = krb5_free_kt_list(context,ktlist);
+        if (check_k5_err(context, "krb5_free_kt_list", ret)) {
+            debug((char *) "%s| %s: ERROR: Freeing list failed\n",
+                  LogTime(), PROGRAM);
+        }
+    }
+    krb5_free_context(context);
+#endif
+#ifdef HAVE_HEIMDAL_KERBEROS
+    gsskrb5_register_acceptor_identity(keytab_name);
+#endif
     while (1) {
         if (fgets(buf, sizeof(buf) - 1, stdin) == NULL) {
             if (ferror(stdin)) {
                 debug((char *) "%s| %s: FATAL: fgets() failed! dying..... errno=%d (%s)\n",
                       LogTime(), PROGRAM, ferror(stdin),
                       strerror(ferror(stdin)));
 
                 fprintf(stdout, "BH input error\n");
-                exit(1);	/* BIIG buffer */
+                exit(1);    /* BIIG buffer */
             }
             fprintf(stdout, "BH input error\n");
             exit(0);
         }
         c = (char *) memchr(buf, '\n', sizeof(buf) - 1);
         if (c) {
