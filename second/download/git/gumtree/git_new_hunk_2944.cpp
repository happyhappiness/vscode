				printf("error %s lock error\n", ref->name);
			rc = 1;
			continue;
		}

		/* Set up revision info for this refspec */
		argv_array_push(&commit_argv, ""); /* ignored */
		argv_array_push(&commit_argv, "--objects");
		argv_array_push(&commit_argv, oid_to_hex(&ref->new_oid));
		if (!push_all && !is_null_oid(&ref->old_oid))
			argv_array_pushf(&commit_argv, "^%s",
					 oid_to_hex(&ref->old_oid));
		init_revisions(&revs, setup_git_directory());
		setup_revisions(commit_argv.argc, commit_argv.argv, &revs, NULL);
		revs.edge_hint = 0; /* just in case */

		/* Generate a list of objects that need to be pushed */
		pushing = 0;
		if (prepare_revision_walk(&revs))
			die("revision walk setup failed");
		mark_edges_uninteresting(&revs, NULL);
