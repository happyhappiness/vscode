				 * in the output; otherwise we would
				 * end up triggering "empty bundle"
				 * error.
				 */
				obj = parse_object_or_die(sha1, e->name);
				obj->flags |= SHOWN;
				add_pending_object(revs, obj, e->name);
			}
			free(ref);
			continue;
		}

		ref_count++;
		write_or_die(bundle_fd, sha1_to_hex(e->item->sha1), 40);
		write_or_die(bundle_fd, " ", 1);
		write_or_die(bundle_fd, display_ref, strlen(display_ref));
		write_or_die(bundle_fd, "\n", 1);
		free(ref);
	}

	/* end header */
	write_or_die(bundle_fd, "\n", 1);
	return ref_count;
}

int create_bundle(struct bundle_header *header, const char *path,
		  int argc, const char **argv)
{
	static struct lock_file lock;
	int bundle_fd = -1;
	int bundle_to_stdout;
	int ref_count = 0;
	struct rev_info revs;

	bundle_to_stdout = !strcmp(path, "-");
	if (bundle_to_stdout)
		bundle_fd = 1;
	else
		bundle_fd = hold_lock_file_for_update(&lock, path,
						      LOCK_DIE_ON_ERROR);

	/* write signature */
	write_or_die(bundle_fd, bundle_signature, strlen(bundle_signature));

	/* init revs to list objects for pack-objects later */
	save_commit_buffer = 0;
	init_revisions(&revs, NULL);

	/* write prerequisites */
	if (compute_and_write_prerequisites(bundle_fd, &revs, argc, argv))
		return -1;

	argc = setup_revisions(argc, argv, &revs, NULL);

	if (argc > 1)
		return error(_("unrecognized argument: %s"), argv[1]);

	object_array_remove_duplicates(&revs.pending);

	ref_count = write_bundle_refs(bundle_fd, &revs);
	if (!ref_count)
		die(_("Refusing to create empty bundle."));
	else if (ref_count < 0)
		return -1;

	/* write pack */
	if (write_pack_data(bundle_fd, &lock, &revs))
		return -1;

	if (!bundle_to_stdout) {
		if (commit_lock_file(&lock))
			die_errno(_("cannot create '%s'"), path);
	}
	return 0;
}

int unbundle(struct bundle_header *header, int bundle_fd, int flags)
{
	const char *argv_index_pack[] = {"index-pack",
					 "--fix-thin", "--stdin", NULL, NULL};
	struct child_process ip = CHILD_PROCESS_INIT;

	if (flags & BUNDLE_VERBOSE)
		argv_index_pack[3] = "-v";

	if (verify_bundle(header, 0))
		return -1;
	ip.argv = argv_index_pack;
	ip.in = bundle_fd;
	ip.no_stdout = 1;
	ip.git_cmd = 1;
	if (run_command(&ip))
		return error(_("index-pack died"));
