}

static int is_tag_in_date_range(struct object *tag, struct rev_info *revs)
{
	unsigned long size;
	enum object_type type;
	char *buf, *line, *lineend;
	unsigned long date;

	if (revs->max_age == -1 && revs->min_age == -1)
		return 1;

	buf = read_sha1_file(tag->sha1, &type, &size);
	if (!buf)
		return 1;
	line = memmem(buf, size, "\ntagger ", 8);
	if (!line++)
		return 1;
	lineend = memchr(line, '\n', buf + size - line);
	line = memchr(line, '>', lineend ? lineend - line : buf + size - line);
	if (!line++)
		return 1;
	date = strtoul(line, NULL, 10);
	free(buf);
	return (revs->max_age == -1 || revs->max_age < date) &&
		(revs->min_age == -1 || revs->min_age > date);
}

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
