				printf("error %s lock error\n", ref->name);
			rc = 1;
			continue;
		}

		/* Set up revision info for this refspec */
		commit_argc = 3;
		new_sha1_hex = xstrdup(sha1_to_hex(ref->new_sha1));
		old_sha1_hex = NULL;
		commit_argv[1] = "--objects";
		commit_argv[2] = new_sha1_hex;
		if (!push_all && !is_null_sha1(ref->old_sha1)) {
			old_sha1_hex = xmalloc(42);
			sprintf(old_sha1_hex, "^%s",
				sha1_to_hex(ref->old_sha1));
			commit_argv[3] = old_sha1_hex;
			commit_argc++;
		}
		commit_argv[commit_argc] = NULL;
		init_revisions(&revs, setup_git_directory());
		setup_revisions(commit_argc, commit_argv, &revs, NULL);
		revs.edge_hint = 0; /* just in case */
		free(new_sha1_hex);
		if (old_sha1_hex) {
			free(old_sha1_hex);
			commit_argv[1] = NULL;
		}

		/* Generate a list of objects that need to be pushed */
		pushing = 0;
		if (prepare_revision_walk(&revs))
			die("revision walk setup failed");
		mark_edges_uninteresting(&revs, NULL);
