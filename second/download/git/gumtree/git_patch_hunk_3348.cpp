 		struct strbuf man_page = STRBUF_INIT;
 
 		if (!path)
 			path = "emacsclient";
 		strbuf_addf(&man_page, "(woman \"%s\")", page);
 		execlp(path, "emacsclient", "-e", man_page.buf, (char *)NULL);
-		warning(_("failed to exec '%s': %s"), path, strerror(errno));
+		warning_errno(_("failed to exec '%s'"), path);
 	}
 }
 
 static void exec_man_konqueror(const char *path, const char *page)
 {
 	const char *display = getenv("DISPLAY");
