 		return temp;
 	}
 	else {
 		if (diff_populate_filespec(one, 0))
 			die("cannot read data blob for %s", one->path);
 		prep_temp_blob(name, temp, one->data, one->size,
-			       one->sha1, one->mode);
+			       &one->oid, one->mode);
 	}
 	return temp;
 }
 
 static void add_external_diff_name(struct argv_array *argv,
 				   const char *name,
