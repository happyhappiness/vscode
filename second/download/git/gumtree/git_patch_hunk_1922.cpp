 	fd = hold_lock_file_for_update(shallow_lock, git_path("shallow"),
 				       LOCK_DIE_ON_ERROR);
 	check_shallow_file_for_update();
 	if (write_shallow_commits(&sb, 0, extra)) {
 		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
 			die_errno("failed to write to %s",
-				  shallow_lock->filename);
-		*alternate_shallow_file = shallow_lock->filename;
+				  shallow_lock->filename.buf);
+		*alternate_shallow_file = shallow_lock->filename.buf;
 	} else
 		/*
 		 * is_repository_shallow() sees empty string as "no
 		 * shallow file".
 		 */
 		*alternate_shallow_file = "";
