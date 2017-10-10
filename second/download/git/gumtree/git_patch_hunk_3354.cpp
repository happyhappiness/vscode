 
 		free(file);
 		file = xstrfmt("%s/%s", maildir, list.items[i].string);
 
 		f = fopen(file, "r");
 		if (!f) {
-			error("cannot open mail %s (%s)", file, strerror(errno));
+			error_errno("cannot open mail %s", file);
 			goto out;
 		}
 
 		if (strbuf_getwholeline(&buf, f, '\n')) {
-			error("cannot read mail %s (%s)", file, strerror(errno));
+			error_errno("cannot read mail %s", file);
 			goto out;
 		}
 
 		name = xstrfmt("%s/%0*d", dir, nr_prec, ++skip);
 		split_one(f, name, 1);
 		free(name);
