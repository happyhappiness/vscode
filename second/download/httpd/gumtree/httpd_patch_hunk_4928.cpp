         fprintf(stderr, "apr_MD5InitEBCDIC()->%d\n", rv);
         return APR_EGENERAL;
     }
 #endif /*APR_CHARSET_EBCDIC*/
 
     /* Set MD5 as default */
-    (*hdbm)->alg = ALG_APMD5;
+    (*hdbm)->ctx.alg = ALG_APMD5;
     (*hdbm)->type = "default";
     return APR_SUCCESS;
 }
 
 static apr_status_t htdbm_open(htdbm_t *htdbm)
 {
     if (htdbm->create)
         return apr_dbm_open_ex(&htdbm->dbm, htdbm->type, htdbm->filename, APR_DBM_RWCREATE,
-                            APR_OS_DEFAULT, htdbm->pool);
+                            APR_OS_DEFAULT, htdbm->ctx.pool);
     else
         return apr_dbm_open_ex(&htdbm->dbm, htdbm->type, htdbm->filename,
                             htdbm->rdonly ? APR_DBM_READONLY : APR_DBM_READWRITE,
-                            APR_OS_DEFAULT, htdbm->pool);
+                            APR_OS_DEFAULT, htdbm->ctx.pool);
 }
 
 static apr_status_t htdbm_save(htdbm_t *htdbm, int *changed)
 {
     apr_datum_t key, val;
 
