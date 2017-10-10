#include "builtin.h"
#include "blob.h"
#include "quote.h"
#include "parse-options.h"
#include "exec_cmd.h"

static void hash_fd(int fd, const char *type, int write_object, const char *path)
{
	struct stat st;
	unsigned char sha1[20];
	unsigned flags = (HASH_FORMAT_CHECK |
			  (write_object ? HASH_WRITE_OBJECT : 0));

	if (fstat(fd, &st) < 0 ||
	    index_fd(sha1, fd, &st, type_from_string(type), path, flags))
		die(write_object
		    ? "Unable to add %s to database"
		    : "Unable to hash %s", path);
	printf("%s\n", sha1_to_hex(sha1));
	maybe_flush_or_die(stdout, "hash to stdout");
}

static void hash_object(const char *path, const char *type, int write_object,
			const char *vpath)
{
	int fd;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die_errno("Cannot open '%s'", path);
	hash_fd(fd, type, write_object, vpath);
}

static int no_filters;

static void hash_stdin_paths(const char *type, int write_objects)
{
	struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

	while (strbuf_getline(&buf, stdin, '\n') != EOF) {
		if (buf.buf[0] == '"') {
			strbuf_reset(&nbuf);
			if (unquote_c_style(&nbuf, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &nbuf);
		}
		hash_object(buf.buf, type, write_objects,
		    no_filters ? NULL : buf.buf);
	}
	strbuf_release(&buf);
	strbuf_release(&nbuf);
}

static const char * const hash_object_usage[] = {
	N_("git hash-object [-t <type>] [-w] [--path=<file>|--no-filters] [--stdin] [--] <file>..."),
	N_("git hash-object  --stdin-paths < <list-of-paths>"),
	NULL
};

static const char *type;
static int write_object;
static int hashstdin;
static int stdin_paths;
static const char *vpath;

static const struct option hash_object_options[] = {
	OPT_STRING('t', NULL, &type, N_("type"), N_("object type")),
	OPT_BOOL('w', NULL, &write_object, N_("write the object into the object database")),
	OPT_COUNTUP( 0 , "stdin", &hashstdin, N_("read the object from stdin")),
	OPT_BOOL( 0 , "stdin-paths", &stdin_paths, N_("read file names from stdin")),
	OPT_BOOL( 0 , "no-filters", &no_filters, N_("store file as is without filters")),
	OPT_STRING( 0 , "path", &vpath, N_("file"), N_("process file as it were from this path")),
	OPT_END()
};

int cmd_hash_object(int argc, const char **argv, const char *prefix)
{
	int i;
	int prefix_length = -1;
	const char *errstr = NULL;

	type = blob_type;

	argc = parse_options(argc, argv, NULL, hash_object_options,
			     hash_object_usage, 0);

	if (write_object) {
		prefix = setup_git_directory();
		prefix_length = prefix ? strlen(prefix) : 0;
		if (vpath && prefix)
			vpath = prefix_filename(prefix, prefix_length, vpath);
	}

