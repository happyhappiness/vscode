 	die(_("no info viewer handled the request"));
 }
 
 static void get_html_page_path(struct strbuf *page_path, const char *page)
 {
 	struct stat st;
+	char *to_free = NULL;
+
 	if (!html_path)
-		html_path = system_path(GIT_HTML_PATH);
+		html_path = to_free = system_path(GIT_HTML_PATH);
 
 	/* Check that we have a git documentation directory. */
 	if (!strstr(html_path, "://")) {
 		if (stat(mkpath("%s/git.html", html_path), &st)
 		    || !S_ISREG(st.st_mode))
 			die("'%s': not a documentation directory.", html_path);
 	}
 
 	strbuf_init(page_path, 0);
 	strbuf_addf(page_path, "%s/%s.html", html_path, page);
+	free(to_free);
 }
 
 /*
  * If open_html is not defined in a platform-specific way (see for
  * example compat/mingw.h), we use the script web--browse to display
  * HTML.
