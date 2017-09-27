 
 /*
  * NOTICE: if you tweak this you should look at is_empty_table() 
  * and table_elts() in alloc.h
  */
 #ifdef MAKE_TABLE_PROFILE
-static apr_table_entry_t *table_push(apr_table_t *t)
+static apr_table_entry_t *do_table_push(const char *func, apr_table_t *t)
 {
     if (t->a.nelts == t->a.nalloc) {
-        return NULL;
+        fprintf(stderr, "%s: table created by %p hit limit of %u\n",
+                func ? func : "table_push", t->creator, t->a.nalloc);
     }
     return (apr_table_entry_t *) apr_array_push_noclear(&t->a);
 }
+#if defined(__GNUC__) && __GNUC__ >= 2
+#define table_push(t) do_table_push(__FUNCTION__, t)
+#else
+#define table_push(t) do_table_push(NULL, t)
+#endif
 #else /* MAKE_TABLE_PROFILE */
 #define table_push(t)	((apr_table_entry_t *) apr_array_push_noclear(&(t)->a))
 #endif /* MAKE_TABLE_PROFILE */
 
 APR_DECLARE(const apr_array_header_t *) apr_table_elts(const apr_table_t *t)
 {
