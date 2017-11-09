int notes_merge_commit(struct notes_merge_options *o,
		       struct notes_tree *partial_tree,
		       struct commit *partial_commit,
		       struct object_id *result_oid)
{
	/*
	 * Iterate through files in .git/NOTES_MERGE_WORKTREE and add all
	 * found notes to 'partial_tree'. Write the updated notes tree to
	 * the DB, and commit the resulting tree object while reusing the
	 * commit message and parents from 'partial_commit'.
	 * Finally store the new commit object OID into 'result_oid'.
	 */
	DIR *dir;
	struct dirent *e;
	struct strbuf path = STRBUF_INIT;
	const char *buffer = get_commit_buffer(partial_commit, NULL);
	const char *msg = strstr(buffer, "\n\n");
	int baselen;

	git_path_buf(&path, NOTES_MERGE_WORKTREE);
	if (o->verbosity >= 3)
		printf("Committing notes in notes merge worktree at %s\n",
			path.buf);

	if (!msg || msg[2] == '\0')
		die("partial notes commit has empty message");
	msg += 2;

	dir = opendir(path.buf);
	if (!dir)
		die_errno("could not open %s", path.buf);

	strbuf_addch(&path, '/');
	baselen = path.len;
	while ((e = readdir(dir)) != NULL) {
		struct stat st;
		struct object_id obj_oid, blob_oid;

		if (is_dot_or_dotdot(e->d_name))
			continue;

		if (get_oid_hex(e->d_name, &obj_oid)) {
			if (o->verbosity >= 3)
				printf("Skipping non-SHA1 entry '%s%s'\n",
					path.buf, e->d_name);
			continue;
		}

		strbuf_addstr(&path, e->d_name);
		/* write file as blob, and add to partial_tree */
		if (stat(path.buf, &st))
			die_errno("Failed to stat '%s'", path.buf);
		if (index_path(blob_oid.hash, path.buf, &st, HASH_WRITE_OBJECT))
			die("Failed to write blob object from '%s'", path.buf);
		if (add_note(partial_tree, &obj_oid, &blob_oid, NULL))
			die("Failed to add resolved note '%s' to notes tree",
			    path.buf);
		if (o->verbosity >= 4)
			printf("Added resolved note for object %s: %s\n",
				oid_to_hex(&obj_oid), oid_to_hex(&blob_oid));
		strbuf_setlen(&path, baselen);
	}

	create_notes_commit(partial_tree, partial_commit->parents,
			    msg, strlen(msg), result_oid->hash);
	unuse_commit_buffer(partial_commit, buffer);
	if (o->verbosity >= 4)
		printf("Finalized notes merge commit: %s\n",
			oid_to_hex(result_oid));
	strbuf_release(&path);
	closedir(dir);
	return 0;
}