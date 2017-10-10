 			add_branch = o->branch2;
 			other_branch = o->branch1;
 			mode = b_mode;
 			oid = b_oid;
 			conf = _("directory/file");
 		}
-		if (dir_in_way(path, !o->call_depth)) {
+		if (dir_in_way(path, !o->call_depth,
+			       S_ISGITLINK(a_mode))) {
 			char *new_path = unique_path(o, path, add_branch);
 			clean_merge = 0;
 			output(o, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
 			       "Adding %s as %s"),
 			       conf, path, other_branch, path, new_path);
 			if (update_file(o, 0, oid, mode, new_path))
