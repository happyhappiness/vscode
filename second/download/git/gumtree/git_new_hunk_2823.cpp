	 * deleted a branch by mistake, this is a prime candidate to
	 * start looking at, for example.
	 */
	if (!obj->used) {
		if (show_dangling)
			printf("dangling %s %s\n", typename(obj->type),
			       oid_to_hex(&obj->oid));
		if (write_lost_and_found) {
			char *filename = git_pathdup("lost-found/%s/%s",
				obj->type == OBJ_COMMIT ? "commit" : "other",
				oid_to_hex(&obj->oid));
			FILE *f;

			if (safe_create_leading_directories_const(filename)) {
				error("Could not create lost-found");
				free(filename);
				return;
			}
			if (!(f = fopen(filename, "w")))
				die_errno("Could not open '%s'", filename);
			if (obj->type == OBJ_BLOB) {
				if (stream_blob_to_fd(fileno(f), obj->oid.hash, NULL, 1))
					die_errno("Could not write '%s'", filename);
			} else
				fprintf(f, "%s\n", oid_to_hex(&obj->oid));
			if (fclose(f))
				die_errno("Could not finish '%s'",
					  filename);
			free(filename);
		}
		return;
