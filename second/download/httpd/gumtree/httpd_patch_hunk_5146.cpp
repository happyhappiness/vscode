             if (bsize == 0) {
                 break;
             }
             buf[bsize - 1] = 0;
             t = strchr(buf, ' ');
             if (t) {
-                ip = apr_pstrndup(pool, buf, t - buf);
+                ip = apr_pstrmemdup(pool, buf, t - buf);
             } else {
                 ip = NULL;
             }
             if (!ip || buf[0] == '#') {
                 /* copy things we can't process */
                 apr_file_printf(fp, "%s\n", buf);
