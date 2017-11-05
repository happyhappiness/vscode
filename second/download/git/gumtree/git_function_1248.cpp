int create_bundle(struct bundle_header *header, const char *path,
		  int argc, const char **argv)
{
	static struct lock_file lock;
	int bundle_fd = -1;
	int bundle_to_stdout;
	int i, ref_count = 0;
	struct strbuf buf = STRBUF_INIT;
	struct rev_info revs;
	struct child_process rls;
	FILE *rls_fout;

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
	memset(&rls, 0, sizeof(rls));
	argv_array_pushl(&rls.args,
			 "rev-list", "--boundary", "--pretty=oneline",
			 NULL);
	for (i = 1; i < argc; i++)
		argv_array_push(&rls.args, argv[i]);
	rls.out = -1;
	rls.git_cmd = 1;
	if (start_command(&rls))
		return -1;
	rls_fout = xfdopen(rls.out, "r");
	while (strbuf_getwholeline(&buf, rls_fout, '\n') != EOF) {
		unsigned char sha1[20];
		if (buf.len > 0 && buf.buf[0] == '-') {
			write_or_die(bundle_fd, buf.buf, buf.len);
			if (!get_sha1_hex(buf.buf + 1, sha1)) {
				struct object *object = parse_object_or_die(sha1, buf.buf);
				object->flags |= UNINTERESTING;
				add_pending_object(&revs, object, buf.buf);
			}
		} else if (!get_sha1_hex(buf.buf, sha1)) {
			struct object *object = parse_object_or_die(sha1, buf.buf);
			object->flags |= SHOWN;
		}
	}
	strbuf_release(&buf);
	fclose(rls_fout);
	if (finish_command(&rls))
		return error(_("rev-list died"));

	/* write references */
	argc = setup_revisions(argc, argv, &revs, NULL);

	if (argc > 1)
		return error(_("unrecognized argument: %s"), argv[1]);

	object_array_remove_duplicates(&revs.pending);

	for (i = 0; i < revs.pending.nr; i++) {
		struct object_array_entry *e = revs.pending.objects + i;
		unsigned char sha1[20];
		char *ref;
		const char *display_ref;
		int flag;

		if (e->item->flags & UNINTERESTING)
			continue;
		if (dwim_ref(e->name, strlen(e->name), sha1, &ref) != 1)
			continue;
		if (read_ref_full(e->name, sha1, 1, &flag))
			flag = 0;
		display_ref = (flag & REF_ISSYMREF) ? e->name : ref;

		if (e->item->type == OBJ_TAG &&
				!is_tag_in_date_range(e->item, &revs)) {
			e->item->flags |= UNINTERESTING;
			continue;
		}

		/*
		 * Make sure the refs we wrote out is correct; --max-count and
		 * other limiting options could have prevented all the tips
		 * from getting output.
		 *
		 * Non commit objects such as tags and blobs do not have
		 * this issue as they are not affected by those extra
		 * constraints.
		 */
		if (!(e->item->flags & SHOWN) && e->item->type == OBJ_COMMIT) {
			warning(_("ref '%s' is excluded by the rev-list options"),
				e->name);
			free(ref);
			continue;
		}
		/*
		 * If you run "git bundle create bndl v1.0..v2.0", the
		 * name of the positive ref is "v2.0" but that is the
		 * commit that is referenced by the tag, and not the tag
		 * itself.
		 */
		if (hashcmp(sha1, e->item->sha1)) {
			/*
			 * Is this the positive end of a range expressed
			 * in terms of a tag (e.g. v2.0 from the range
			 * "v1.0..v2.0")?
			 */
			struct commit *one = lookup_commit_reference(sha1);
			struct object *obj;

			if (e->item == &(one->object)) {
				/*
				 * Need to include e->name as an
				 * independent ref to the pack-objects
				 * input, so that the tag is included
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