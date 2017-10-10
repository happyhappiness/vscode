	 */
	if (!obj->used) {
		if (show_dangling)
			printf("dangling %s %s\n", typename(obj->type),
			       sha1_to_hex(obj->sha1));
		if (write_lost_and_found) {
			const char *filename = git_path("lost-found/%s/%s",
				obj->type == OBJ_COMMIT ? "commit" : "other",
				sha1_to_hex(obj->sha1));
			FILE *f;

			if (safe_create_leading_directories_const(filename)) {
				error("Could not create lost-found");
				return;
			}
			if (!(f = fopen(filename, "w")))
				die_errno("Could not open '%s'", filename);
			if (obj->type == OBJ_BLOB) {
