                 ip = NULL;
             }
             if (!ip || buf[0] == '#') {
                 /* copy things we can't process */
                 apr_file_printf(fp, "%s\n", buf);
             } else if (strcmp(ip, s->ip) !=0 ) {
-                hm_server_t node; 
+                hm_server_t node;
                 apr_time_t seen;
                 /* Update seen time according to the last file modification */
                 apr_table_clear(hbt);
                 qs_to_table(apr_pstrdup(pool, t), hbt, pool);
                 if (apr_table_get(hbt, "busy")) {
                     node.busy = atoi(apr_table_get(hbt, "busy"));
