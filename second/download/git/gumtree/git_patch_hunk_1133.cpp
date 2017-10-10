 		error_errno("cannot open mbox %s", file);
 		goto out;
 	}
 
 	do {
 		peek = fgetc(f);
+		if (peek == EOF) {
+			if (f == stdin)
+				/* empty stdin is OK */
+				ret = skip;
+			else {
+				fclose(f);
+				error(_("empty mbox: '%s'"), file);
+			}
+			goto out;
+		}
 	} while (isspace(peek));
 	ungetc(peek, f);
 
 	if (strbuf_getwholeline(&buf, f, '\n')) {
 		/* empty stdin is OK */
 		if (f != stdin) {
