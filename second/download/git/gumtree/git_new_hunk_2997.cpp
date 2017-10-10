/* if rerere_enabled == -1, fall back to detection of .git/rr-cache */
static int rerere_enabled = -1;

/* automatically update cleanly resolved paths to the index */
static int rerere_autoupdate;

static void free_rerere_id(struct string_list_item *item)
{
	free(item->util);
}

static const char *rerere_id_hex(const struct rerere_id *id)
{
	return id->hex;
}

const char *rerere_path(const struct rerere_id *id, const char *file)
{
	if (!file)
		return git_path("rr-cache/%s", rerere_id_hex(id));

	return git_path("rr-cache/%s/%s", rerere_id_hex(id), file);
}

static int has_rerere_resolution(const struct rerere_id *id)
{
	struct stat st;

	return !stat(rerere_path(id, "postimage"), &st);
}

static struct rerere_id *new_rerere_id_hex(char *hex)
{
	struct rerere_id *id = xmalloc(sizeof(*id));
	strcpy(id->hex, hex);
	return id;
}

static struct rerere_id *new_rerere_id(unsigned char *sha1)
{
	return new_rerere_id_hex(sha1_to_hex(sha1));
}

/*
 * $GIT_DIR/MERGE_RR file is a collection of records, each of which is
 * "conflict ID", a HT and pathname, terminated with a NUL, and is
 * used to keep track of the set of paths that "rerere" may need to
 * work on (i.e. what is left by the previous invocation of "git
 * rerere" during the current conflict resolution session).
 */
static void read_rr(struct string_list *rr)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *in = fopen(git_path_merge_rr(), "r");

	if (!in)
		return;
	while (!strbuf_getwholeline(&buf, in, '\0')) {
		char *path;
		unsigned char sha1[20];
		struct rerere_id *id;

		/* There has to be the hash, tab, path and then NUL */
		if (buf.len < 42 || get_sha1_hex(buf.buf, sha1))
			die("corrupt MERGE_RR");

		if (buf.buf[40] != '\t')
			die("corrupt MERGE_RR");
		buf.buf[40] = '\0';
		path = buf.buf + 41;
		id = new_rerere_id_hex(buf.buf);
		string_list_insert(rr, path)->util = id;
	}
	strbuf_release(&buf);
	fclose(in);
}

static struct lock_file write_lock;

static int write_rr(struct string_list *rr, int out_fd)
{
	int i;
	for (i = 0; i < rr->nr; i++) {
		struct strbuf buf = STRBUF_INIT;
		struct rerere_id *id;

		assert(rr->items[i].util != RERERE_RESOLVED);

		id = rr->items[i].util;
		if (!id)
			continue;
		strbuf_addf(&buf, "%s\t%s%c",
			    rerere_id_hex(id),
			    rr->items[i].string, 0);
		if (write_in_full(out_fd, buf.buf, buf.len) != buf.len)
			die("unable to write rerere record");

		strbuf_release(&buf);
	}
	if (commit_lock_file(&write_lock) != 0)
		die("unable to write rerere record");
	return 0;
}

/*
 * "rerere" interacts with conflicted file contents using this I/O
 * abstraction.  It reads a conflicted contents from one place via
 * "getline()" method, and optionally can write it out after
 * normalizing the conflicted hunks to the "output".  Subclasses of
 * rerere_io embed this structure at the beginning of their own
 * rerere_io object.
 */
struct rerere_io {
	int (*getline)(struct strbuf *, struct rerere_io *);
	FILE *output;
	int wrerror;
	/* some more stuff */
};

static void ferr_write(const void *p, size_t count, FILE *fp, int *err)
{
	if (!count || *err)
		return;
	if (fwrite(p, count, 1, fp) != 1)
		*err = errno;
