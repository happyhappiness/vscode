#include "dir.h"
#include "builtin.h"
#include "parse-options.h"

static unsigned long garbage;
static off_t size_garbage;
static int verbose;
static unsigned long loose, packed, packed_loose;
static off_t loose_size;

static void real_report_garbage(const char *desc, const char *path)
{
	struct stat st;
	if (!stat(path, &st))
		size_garbage += st.st_size;
	warning("%s: %s", desc, path);
	garbage++;
}

static void loose_garbage(const char *path)
{
	if (verbose)
		report_garbage("garbage found", path);
}

static int count_loose(const unsigned char *sha1, const char *path, void *data)
{
	struct stat st;

	if (lstat(path, &st) || !S_ISREG(st.st_mode))
		loose_garbage(path);
	else {
		loose_size += on_disk_bytes(st);
		loose++;
		if (verbose && has_sha1_pack(sha1))
			packed_loose++;
	}
	return 0;
}

static int count_cruft(const char *basename, const char *path, void *data)
{
	loose_garbage(path);
	return 0;
}

static char const * const count_objects_usage[] = {
	N_("git count-objects [-v] [-H | --human-readable]"),
	NULL
};

int cmd_count_objects(int argc, const char **argv, const char *prefix)
{
	int human_readable = 0;
	struct option opts[] = {
		OPT__VERBOSE(&verbose, N_("be verbose")),
		OPT_BOOL('H', "human-readable", &human_readable,
			 N_("print sizes in human readable format")),
		OPT_END(),
	};
