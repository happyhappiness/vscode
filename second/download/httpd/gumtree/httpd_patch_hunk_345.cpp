         }
         strncpy(kb, key.dptr, key.dsize);
         kb[key.dsize] = '\0';
         fprintf(stderr, "    %-32s", kb);
         strncpy(rec, val.dptr, val.dsize);
         rec[val.dsize] = '\0';
-        cmnt = strchr(rec, ';');
+        cmnt = strchr(rec, ':');
         if (cmnt)
             fprintf(stderr, cmnt + 1);
         fprintf(stderr, "\n");
         rv = apr_dbm_nextkey(htdbm->dbm, &key);
         if (rv != APR_SUCCESS)
             fprintf(stderr, "Failed getting NextKey\n");
