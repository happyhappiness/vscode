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
