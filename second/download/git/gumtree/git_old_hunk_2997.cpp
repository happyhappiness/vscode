/* if rerere_enabled == -1, fall back to detection of .git/rr-cache */
static int rerere_enabled = -1;

/* automatically update cleanly resolved paths to the index */
static int rerere_autoupdate;

const char *rerere_path(const char *hex, const char *file)
{
	return git_path("rr-cache/%s/%s", hex, file);
}

static int has_rerere_resolution(const char *hex)
{
	struct stat st;
	return !stat(rerere_path(hex, "postimage"), &st);
}

static void read_rr(struct string_list *rr)
{
	unsigned char sha1[20];
	char buf[PATH_MAX];
	FILE *in = fopen(git_path_merge_rr(), "r");
	if (!in)
		return;
	while (fread(buf, 40, 1, in) == 1) {
		int i;
		char *name;
		if (get_sha1_hex(buf, sha1))
			die("corrupt MERGE_RR");
		buf[40] = '\0';
		name = xstrdup(buf);
		if (fgetc(in) != '\t')
			die("corrupt MERGE_RR");
		for (i = 0; i < sizeof(buf); i++) {
			int c = fgetc(in);
			if (c < 0)
				die("corrupt MERGE_RR");
			buf[i] = c;
			if (c == 0)
				 break;
		}
		if (i == sizeof(buf))
			die("filename too long");
		string_list_insert(rr, buf)->util = name;
	}
	fclose(in);
}

static struct lock_file write_lock;

static int write_rr(struct string_list *rr, int out_fd)
{
	int i;
	for (i = 0; i < rr->nr; i++) {
		const char *path;
		int length;
		if (!rr->items[i].util)
			continue;
		path = rr->items[i].string;
		length = strlen(path) + 1;
		if (write_in_full(out_fd, rr->items[i].util, 40) != 40 ||
		    write_str_in_full(out_fd, "\t") != 1 ||
		    write_in_full(out_fd, path, length) != length)
			die("unable to write rerere record");
	}
	if (commit_lock_file(&write_lock) != 0)
		die("unable to write rerere record");
	return 0;
}

static void ferr_write(const void *p, size_t count, FILE *fp, int *err)
{
	if (!count || *err)
		return;
	if (fwrite(p, count, 1, fp) != 1)
		*err = errno;
