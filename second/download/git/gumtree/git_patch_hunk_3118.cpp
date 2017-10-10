 			return;
 		} else {
 			die("could not read file '%s': %s", filename,
 				strerror(errno));
 		}
 	} else {
-		strbuf_getline(&str, fp, '\n');
+		strbuf_getline_lf(&str, fp);
 		*read_bad = strbuf_detach(&str, NULL);
-		strbuf_getline(&str, fp, '\n');
+		strbuf_getline_lf(&str, fp);
 		*read_good = strbuf_detach(&str, NULL);
 	}
 	strbuf_release(&str);
 	fclose(fp);
 }
 
