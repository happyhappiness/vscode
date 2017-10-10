 			continue;
 		if (is_absolute_path(line.buf)) {
 			add_to_alternates_file(line.buf);
 			continue;
 		}
 		abs_path = mkpathdup("%s/objects/%s", src_repo, line.buf);
-		normalize_path_copy(abs_path, abs_path);
-		add_to_alternates_file(abs_path);
+		if (!normalize_path_copy(abs_path, abs_path))
+			add_to_alternates_file(abs_path);
+		else
+			warning("skipping invalid relative alternate: %s/%s",
+				src_repo, line.buf);
 		free(abs_path);
 	}
 	strbuf_release(&line);
 	fclose(in);
 }
 
