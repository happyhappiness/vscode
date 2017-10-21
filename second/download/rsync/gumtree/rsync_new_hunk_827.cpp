
#include "rsync.h"
#include "zlib/zlib.h"

extern int do_compression;
extern int module_id;
extern int def_compress_level;

static int compression_level, per_file_default_level;

/* determine the compression level based on a wildcard filename list */
void set_compression(char *fname)
{
	static char *match_list;
	char *s;

	if (!do_compression)
		return;

	if (!match_list) {
		char *t, *f = lp_dont_compress(module_id);
		int len = strlen(f);
		if (!(match_list = t = new_array(char, len + 2)))
			out_of_memory("set_compression");
		while (*f) {
			if (*f == ' ') {
				f++;
				continue;
			}
			do {
				if (isupper(*(unsigned char *)f))
					*t++ = tolower(*(unsigned char *)f);
				else
					*t++ = *f;
			} while (*++f != ' ' && *f);
			*t++ = '\0';
		}
		/* Optimize a match-string of "*". */
		if (t - match_list == 2 && match_list[0] == '*') {
			t = match_list;
			per_file_default_level = 0;
		} else
			per_file_default_level = def_compress_level;
		*t++ = '\0';
	}

	compression_level = per_file_default_level;

	if (!*match_list)
		return;

	if ((s = strrchr(fname, '/')) != NULL)
		fname = s + 1;

	for (s = match_list; *s; s += strlen(s) + 1) {
		if (iwildmatch(s, fname)) {
			compression_level = 0;
			break;
		}
	}
}

/* non-compressing recv token */
static int32 simple_recv_token(int f, char **data)
{
	static int32 residue;
