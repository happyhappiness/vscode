 	if (display && *display) {
 		struct strbuf man_page = STRBUF_INIT;
 		const char *filename = "kfmclient";
 
 		/* It's simpler to launch konqueror using kfmclient. */
 		if (path) {
-			const char *file = strrchr(path, '/');
-			if (file && !strcmp(file + 1, "konqueror")) {
-				char *new = xstrdup(path);
-				char *dest = strrchr(new, '/');
-
-				/* strlen("konqueror") == strlen("kfmclient") */
-				strcpy(dest + 1, "kfmclient");
-				path = new;
-			}
-			if (file)
-				filename = file;
+			size_t len;
+			if (strip_suffix(path, "/konqueror", &len))
+				path = xstrfmt("%.*s/kfmclient", (int)len, path);
+			filename = basename((char *)path);
 		} else
 			path = "kfmclient";
 		strbuf_addf(&man_page, "man:%s(1)", page);
 		execlp(path, filename, "newTab", man_page.buf, (char *)NULL);
 		warning(_("failed to exec '%s': %s"), path, strerror(errno));
 	}
