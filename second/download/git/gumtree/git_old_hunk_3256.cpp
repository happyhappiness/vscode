			printf("Would set upstream of '%s' to '%s' of '%s'\n",
				localname + 11, remotename + 11,
				transport->remote->name);
	}
}

static const char *rsync_url(const char *url)
{
	if (!starts_with(url, "rsync://"))
		skip_prefix(url, "rsync:", &url);
	return url;
}

static struct ref *get_refs_via_rsync(struct transport *transport, int for_push)
{
	struct strbuf buf = STRBUF_INIT, temp_dir = STRBUF_INIT;
	struct ref dummy = {NULL}, *tail = &dummy;
	struct child_process rsync = CHILD_PROCESS_INIT;
	const char *args[5];
	int temp_dir_len;

	if (for_push)
		return NULL;

	/* copy the refs to the temporary directory */

	strbuf_addstr(&temp_dir, git_path("rsync-refs-XXXXXX"));
	if (!mkdtemp(temp_dir.buf))
		die_errno ("Could not make temporary directory");
	temp_dir_len = temp_dir.len;

	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addstr(&buf, "/refs");

	rsync.argv = args;
	rsync.stdout_to_stderr = 1;
	args[0] = "rsync";
	args[1] = (transport->verbose > 1) ? "-rv" : "-r";
	args[2] = buf.buf;
	args[3] = temp_dir.buf;
	args[4] = NULL;

	if (run_command(&rsync))
		die ("Could not run rsync to get refs");

	strbuf_reset(&buf);
	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addstr(&buf, "/packed-refs");

	args[2] = buf.buf;

	if (run_command(&rsync))
		die ("Could not run rsync to get refs");

	/* read the copied refs */

	strbuf_addstr(&temp_dir, "/refs");
	read_loose_refs(&temp_dir, temp_dir_len + 1, &tail);
	strbuf_setlen(&temp_dir, temp_dir_len);

	tail = &dummy;
	strbuf_addstr(&temp_dir, "/packed-refs");
	insert_packed_refs(temp_dir.buf, &tail);
	strbuf_setlen(&temp_dir, temp_dir_len);

	if (remove_dir_recursively(&temp_dir, 0))
		warning ("Error removing temporary directory %s.",
				temp_dir.buf);

	strbuf_release(&buf);
	strbuf_release(&temp_dir);

	return dummy.next;
}

static int fetch_objs_via_rsync(struct transport *transport,
				int nr_objs, struct ref **to_fetch)
{
	struct child_process rsync = CHILD_PROCESS_INIT;

	rsync.stdout_to_stderr = 1;
	argv_array_push(&rsync.args, "rsync");
	argv_array_push(&rsync.args, (transport->verbose > 1) ? "-rv" : "-r");
	argv_array_push(&rsync.args, "--ignore-existing");
	argv_array_push(&rsync.args, "--exclude");
	argv_array_push(&rsync.args, "info");
	argv_array_pushf(&rsync.args, "%s/objects/", rsync_url(transport->url));
	argv_array_push(&rsync.args, get_object_directory());

	/* NEEDSWORK: handle one level of alternates */
	return run_command(&rsync);
}

static int write_one_ref(const char *name, const struct object_id *oid,
			 int flags, void *data)
{
	struct strbuf *buf = data;
	int len = buf->len;

	/* when called via for_each_ref(), flags is non-zero */
	if (flags && !starts_with(name, "refs/heads/") &&
			!starts_with(name, "refs/tags/"))
		return 0;

	strbuf_addstr(buf, name);
	if (safe_create_leading_directories(buf->buf) ||
	    write_file_gently(buf->buf, "%s", oid_to_hex(oid)))
		return error("problems writing temporary file %s: %s",
			     buf->buf, strerror(errno));
	strbuf_setlen(buf, len);
	return 0;
}

static int write_refs_to_temp_dir(struct strbuf *temp_dir,
				  int refspec_nr, const char **refspec)
{
	int i;

	for (i = 0; i < refspec_nr; i++) {
		struct object_id oid;
		char *ref;

		if (dwim_ref(refspec[i], strlen(refspec[i]), oid.hash, &ref) != 1)
			return error("Could not get ref %s", refspec[i]);

		if (write_one_ref(ref, &oid, 0, temp_dir)) {
			free(ref);
			return -1;
		}
		free(ref);
	}
	return 0;
}

static int rsync_transport_push(struct transport *transport,
		int refspec_nr, const char **refspec, int flags)
{
	struct strbuf buf = STRBUF_INIT, temp_dir = STRBUF_INIT;
	int result = 0, i;
	struct child_process rsync = CHILD_PROCESS_INIT;
	const char *args[10];

	if (flags & TRANSPORT_PUSH_MIRROR)
		return error("rsync transport does not support mirror mode");

	/* first push the objects */

	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addch(&buf, '/');

	rsync.argv = args;
	rsync.stdout_to_stderr = 1;
	i = 0;
	args[i++] = "rsync";
	args[i++] = "-a";
	if (flags & TRANSPORT_PUSH_DRY_RUN)
		args[i++] = "--dry-run";
	if (transport->verbose > 1)
		args[i++] = "-v";
	args[i++] = "--ignore-existing";
	args[i++] = "--exclude";
	args[i++] = "info";
	args[i++] = get_object_directory();
	args[i++] = buf.buf;
	args[i++] = NULL;

	if (run_command(&rsync))
		return error("Could not push objects to %s",
				rsync_url(transport->url));

	/* copy the refs to the temporary directory; they could be packed. */

	strbuf_addstr(&temp_dir, git_path("rsync-refs-XXXXXX"));
	if (!mkdtemp(temp_dir.buf))
		die_errno ("Could not make temporary directory");
	strbuf_addch(&temp_dir, '/');

	if (flags & TRANSPORT_PUSH_ALL) {
		if (for_each_ref(write_one_ref, &temp_dir))
			return -1;
	} else if (write_refs_to_temp_dir(&temp_dir, refspec_nr, refspec))
		return -1;

	i = 2;
	if (flags & TRANSPORT_PUSH_DRY_RUN)
		args[i++] = "--dry-run";
	if (!(flags & TRANSPORT_PUSH_FORCE))
		args[i++] = "--ignore-existing";
	args[i++] = temp_dir.buf;
	args[i++] = rsync_url(transport->url);
	args[i++] = NULL;
	if (run_command(&rsync))
		result = error("Could not push to %s",
				rsync_url(transport->url));

	if (remove_dir_recursively(&temp_dir, 0))
		warning ("Could not remove temporary directory %s.",
				temp_dir.buf);

	strbuf_release(&buf);
	strbuf_release(&temp_dir);

	return result;
}

struct bundle_transport_data {
	int fd;
	struct bundle_header header;
};

static struct ref *get_refs_from_bundle(struct transport *transport, int for_push)
