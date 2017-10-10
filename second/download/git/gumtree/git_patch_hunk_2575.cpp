 	pack_objects.in = -1;
 	pack_objects.out = bundle_fd;
 	pack_objects.git_cmd = 1;
 	if (start_command(&pack_objects))
 		return error(_("Could not spawn pack-objects"));
 
-	/*
-	 * start_command closed bundle_fd if it was > 1
-	 * so set the lock fd to -1 so commit_lock_file()
-	 * won't fail trying to close it.
-	 */
-	lock->fd = -1;
-
 	for (i = 0; i < revs->pending.nr; i++) {
 		struct object *object = revs->pending.objects[i].item;
 		if (object->flags & UNINTERESTING)
 			write_or_die(pack_objects.in, "^", 1);
 		write_or_die(pack_objects.in, sha1_to_hex(object->sha1), 40);
 		write_or_die(pack_objects.in, "\n", 1);
