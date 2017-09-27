         apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
         for (j = 0; j < DUMP_WIDTH; j++) {
             if (((i * DUMP_WIDTH) + j) >= len)
                 apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
             else {
                 ch = ((unsigned char)*((char *)(s) + i * DUMP_WIDTH + j)) & 0xff;
+#if APR_CHARSET_EBCDIC 
+                apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= 0x20 /*' '*/) && (ch <= 0x7e /*'~'*/)) ? ebcdic_text[j] : '.');
+#else
                 apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= ' ') && (ch <= '~')) ? ch : '.');
+#endif
                 apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
             }
         }
         apr_cpystrn(buf+strlen(buf), " |", sizeof(buf)-strlen(buf));
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
                      "%s", buf);
