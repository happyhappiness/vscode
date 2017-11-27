  * </Plugin>
  */
 static int cf_callback_plugin_dispatch (const char *shortvar, const char *var,
 		const char *arguments, const char *value, lc_flags_t flags,
 		void *extra)
 {
-	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
-			shortvar, var, arguments, value);
+	DEBUG_CALLBACK (shortvar, var, arguments, value);
 
 	if ((nesting_depth == 0) || (current_module == NULL))
 	{
 		fprintf (stderr, ERR_NEEDS_SECTION, shortvar);
 		return (LC_CBRET_ERROR);
 	}
