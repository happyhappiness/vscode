				 * in the output; otherwise we would
				 * end up triggering "empty bundle"
				 * error.
				 */
				obj = parse_object_or_die(sha1, e->name);
				obj->flags |= SHOWN;
				add_pending_object(&revs, obj, e->name);
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
	if (!ref_count)
		die(_("Refusing to create empty bundle."));

	/* end header */
	write_or_die(bundle_fd, "\n", 1);

	/* write pack */
	memset(&rls, 0, sizeof(rls));
	argv_array_pushl(&rls.args,
			 "pack-objects", "--all-progress-implied",
			 "--stdout", "--thin", "--delta-base-offset",
			 NULL);
	rls.in = -1;
	rls.out = bundle_fd;
	rls.git_cmd = 1;
	if (start_command(&rls))
		return error(_("Could not spawn pack-objects"));

	/*
	 * start_command closed bundle_fd if it was > 1
	 * so set the lock fd to -1 so commit_lock_file()
	 * won't fail trying to close it.
	 */
	lock.fd = -1;

	for (i = 0; i < revs.pending.nr; i++) {
		struct object *object = revs.pending.objects[i].item;
		if (object->flags & UNINTERESTING)
			write_or_die(rls.in, "^", 1);
		write_or_die(rls.in, sha1_to_hex(object->sha1), 40);
		write_or_die(rls.in, "\n", 1);
	}
	close(rls.in);
	if (finish_command(&rls))
		return error(_("pack-objects died"));
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
	struct child_process ip;

	if (flags & BUNDLE_VERBOSE)
		argv_index_pack[3] = "-v";

	if (verify_bundle(header, 0))
		return -1;
	memset(&ip, 0, sizeof(ip));
	ip.argv = argv_index_pack;
	ip.in = bundle_fd;
	ip.no_stdout = 1;
	ip.git_cmd = 1;
	if (run_command(&ip))
		return error(_("index-pack died"));
