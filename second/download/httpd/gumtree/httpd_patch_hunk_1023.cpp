                                htdbm->comment, NULL);
         val.dsize += (strlen(htdbm->comment) + 1);
     }
     return apr_dbm_store(htdbm->dbm, key, val);
 }
 
-static apr_status_t htdbm_del(htdbm_t *htdbm) 
+static apr_status_t htdbm_del(htdbm_t *htdbm)
 {
     apr_datum_t key;
 
     key.dptr = htdbm->username;
     key.dsize = strlen(htdbm->username);
     if (!apr_dbm_exists(htdbm->dbm, key))
         return APR_ENOENT;
 
     return apr_dbm_delete(htdbm->dbm, key);
 }
 
-static apr_status_t htdbm_verify(htdbm_t *htdbm) 
+static apr_status_t htdbm_verify(htdbm_t *htdbm)
 {
     apr_datum_t key, val;
     char pwd[MAX_STRING_LEN] = {0};
     char *rec, *cmnt;
 
     key.dptr = htdbm->username;
     key.dsize = strlen(htdbm->username);
     if (!apr_dbm_exists(htdbm->dbm, key))
-        return APR_ENOENT;    
+        return APR_ENOENT;
     if (apr_dbm_fetch(htdbm->dbm, key, &val) != APR_SUCCESS)
         return APR_ENOENT;
     rec = apr_pstrndup(htdbm->pool, val.dptr, val.dsize);
-    cmnt = strchr(rec, ';');
+    cmnt = strchr(rec, ':');
     if (cmnt)
         strncpy(pwd, rec, cmnt - rec);
     else
         strcpy(pwd, rec);
     return apr_password_validate(htdbm->userpass, pwd);
 }
 
-static apr_status_t htdbm_list(htdbm_t *htdbm) 
+static apr_status_t htdbm_list(htdbm_t *htdbm)
 {
     apr_status_t rv;
     apr_datum_t key, val;
     char *rec, *cmnt;
     char kb[MAX_STRING_LEN];
     int i = 0;
 
     rv = apr_dbm_firstkey(htdbm->dbm, &key);
     if (rv != APR_SUCCESS) {
-        fprintf(stderr, "Empty database -- %s\n", htdbm->filename); 
+        fprintf(stderr, "Empty database -- %s\n", htdbm->filename);
         return APR_ENOENT;
     }
     rec = apr_pcalloc(htdbm->pool, HUGE_STRING_LEN);
 
-    fprintf(stderr, "Dumping records from database -- %s\n", htdbm->filename); 
-    fprintf(stderr, "    %-32sComment\n", "Username");    
+    fprintf(stderr, "Dumping records from database -- %s\n", htdbm->filename);
+    fprintf(stderr, "    %-32sComment\n", "Username");
     while (key.dptr != NULL) {
         rv = apr_dbm_fetch(htdbm->dbm, key, &val);
         if (rv != APR_SUCCESS) {
             fprintf(stderr, "Failed getting data from %s\n", htdbm->filename);
             return APR_EGENERAL;
         }
