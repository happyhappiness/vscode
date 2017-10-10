}

static int is_tag_in_date_range(struct object *tag, struct rev_info *revs)
{
	unsigned long size;
	enum object_type type;
	char *buf = NULL, *line, *lineend;
	unsigned long date;
	int result = 1;

	if (revs->max_age == -1 && revs->min_age == -1)
		goto out;

	buf = read_sha1_file(tag->sha1, &type, &size);
	if (!buf)
		goto out;
	line = memmem(buf, size, "\ntagger ", 8);
	if (!line++)
		goto out;
	lineend = memchr(line, '\n', buf + size - line);
	line = memchr(line, '>', lineend ? lineend - line : buf + size - line);
	if (!line++)
		goto out;
	date = strtoul(line, NULL, 10);
	result = (revs->max_age == -1 || revs->max_age < date) &&
		(revs->min_age == -1 || revs->min_age > date);
out:
	free(buf);
	return result;
}

static int write_pack_data(int bundle_fd, struct lock_file *lock, struct rev_info *revs)
{
	struct child_process pack_objects = CHILD_PROCESS_INIT;
	int i;

	argv_array_pushl(&pack_objects.args,
			 "pack-objects", "--all-progress-implied",
			 "--stdout", "--thin", "--delta-base-offset",
			 NULL);
	pack_objects.in = -1;
	pack_objects.out = bundle_fd;
	pack_objects.git_cmd = 1;
	if (start_command(&pack_objects))
		return error(_("Could not spawn pack-objects"));

	/*
	 * start_command closed bundle_fd if it was > 1
	 * so set the lock fd to -1 so commit_lock_file()
	 * won't fail trying to close it.
	 */
	lock->fd = -1;

	for (i = 0; i < revs->pending.nr; i++) {
		struct object *object = revs->pending.objects[i].item;
		if (object->flags & UNINTERESTING)
			write_or_die(pack_objects.in, "^", 1);
		write_or_die(pack_objects.in, sha1_to_hex(object->sha1), 40);
		write_or_die(pack_objects.in, "\n", 1);
	}
	close(pack_objects.in);
	if (finish_command(&pack_objects))
		return error(_("pack-objects died"));
	return 0;
}

static int compute_and_write_prerequisites(int bundle_fd,
					   struct rev_info *revs,
					   int argc, const char **argv)
{
	struct child_process rls = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	FILE *rls_fout;
	int i;

	argv_array_pushl(&rls.args,
			 "rev-list", "--boundary", "--pretty=oneline",
			 NULL);
	for (i = 1; i < argc; i++)
		argv_array_push(&rls.args, argv[i]);
	rls.out = -1;
