 
 /*
  * (Try to) load the shared object `file'. Won't complain if it isn't a shared
  * object, but it will bitch about a shared object not having a
  * ``module_register'' symbol..
  */
-static int plugin_load_file (char *file)
+static int plugin_load_file (char *file, uint32_t flags)
 {
 	lt_dlhandle dlh;
 	void (*reg_handle) (void);
 
 	DEBUG ("file = %s", file);
 
 	lt_dlinit ();
 	lt_dlerror (); /* clear errors */
 
-	if ((dlh = lt_dlopen (file)) == NULL)
+#if LIBTOOL_VERSION == 2
+	if (flags & PLUGIN_FLAGS_GLOBAL) {
+		lt_dladvise advise;
+		lt_dladvise_init(&advise);
+		lt_dladvise_global(&advise);
+		dlh = lt_dlopenadvise(file, advise);
+		lt_dladvise_destroy(&advise);
+	} else {
+        	dlh = lt_dlopen (file);
+	}
+#else /* if LIBTOOL_VERSION == 1 */
+	if (flags & PLUGIN_FLAGS_GLOBAL)
+		ERROR ("plugin_load_file: The global flag is not supported, "
+				"libtool 2 is required for this.");
+	dlh = lt_dlopen (file);
+#endif
+
+	if (dlh == NULL)
 	{
 		const char *error = lt_dlerror ();
 
 		ERROR ("lt_dlopen (%s) failed: %s", file, error);
 		fprintf (stderr, "lt_dlopen (%s) failed: %s\n", file, error);
 		return (1);
