		die_errno("could not open %s", path.buf);

	strbuf_addch(&path, '/');
	baselen = path.len;
	while ((e = readdir(dir)) != NULL) {
		struct stat st;
		unsigned char obj_sha1[20], blob_sha1[20];

		if (is_dot_or_dotdot(e->d_name))
			continue;

		if (strlen(e->d_name) != 40 || get_sha1_hex(e->d_name, obj_sha1)) {
			if (o->verbosity >= 3)
				printf("Skipping non-SHA1 entry '%s%s'\n",
					path.buf, e->d_name);
			continue;
		}

		strbuf_addstr(&path, e->d_name);
		/* write file as blob, and add to partial_tree */
		if (stat(path.buf, &st))
			die_errno("Failed to stat '%s'", path.buf);
		if (index_path(blob_sha1, path.buf, &st, HASH_WRITE_OBJECT))
			die("Failed to write blob object from '%s'", path.buf);
		if (add_note(partial_tree, obj_sha1, blob_sha1, NULL))
			die("Failed to add resolved note '%s' to notes tree",
			    path.buf);
		if (o->verbosity >= 4)
			printf("Added resolved note for object %s: %s\n",
				sha1_to_hex(obj_sha1), sha1_to_hex(blob_sha1));
		strbuf_setlen(&path, baselen);
	}

	create_notes_commit(partial_tree, partial_commit->parents,
			    msg, strlen(msg), result_sha1);
	unuse_commit_buffer(partial_commit, buffer);
	if (o->verbosity >= 4)
		printf("Finalized notes merge commit: %s\n",
			sha1_to_hex(result_sha1));
	strbuf_release(&path);
	closedir(dir);
	return 0;
}

int notes_merge_abort(struct notes_merge_options *o)
