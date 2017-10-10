 	warning(_("failed to exec '%s': %s"), cmd, strerror(errno));
 }
 
 static void add_man_viewer(const char *name)
 {
 	struct man_viewer_list **p = &man_viewer_list;
-	size_t len = strlen(name);
 
 	while (*p)
 		p = &((*p)->next);
-	*p = xcalloc(1, (sizeof(**p) + len + 1));
-	memcpy((*p)->name, name, len); /* NUL-terminated by xcalloc */
+	FLEX_ALLOC_STR(*p, name, name);
 }
 
 static int supported_man_viewer(const char *name, size_t len)
 {
 	return (!strncasecmp("man", name, len) ||
 		!strncasecmp("woman", name, len) ||
