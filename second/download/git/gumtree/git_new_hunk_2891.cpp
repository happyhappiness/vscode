#include "parse-options.h"
#include "diff.h"
#include "revision.h"
#include "gpg-interface.h"
#include "sha1-array.h"
#include "column.h"
#include "ref-filter.h"

static const char * const git_tag_usage[] = {
	N_("git tag [-a | -s | -u <key-id>] [-f] [-m <msg> | -F <file>] <tagname> [<head>]"),
	N_("git tag -d <tagname>..."),
	N_("git tag -l [-n[<num>]] [--contains <commit>] [--points-at <object>]"
		"\n\t\t[--format=<format>] [--[no-]merged [<commit>]] [<pattern>...]"),
	N_("git tag -v <tagname>..."),
	NULL
};

static unsigned int colopts;

static int list_tags(struct ref_filter *filter, struct ref_sorting *sorting, const char *format)
{
	struct ref_array array;
	char *to_free = NULL;
	int i;

	memset(&array, 0, sizeof(array));

	if (filter->lines == -1)
		filter->lines = 0;

	if (!format) {
		if (filter->lines) {
			to_free = xstrfmt("%s %%(contents:lines=%d)",
					  "%(align:15)%(refname:short)%(end)",
					  filter->lines);
			format = to_free;
		} else
			format = "%(refname:short)";
	}

	verify_ref_format(format);
	filter->with_commit_tag_algo = 1;
	filter_refs(&array, filter, FILTER_REFS_TAGS);
	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++)
		show_ref_array_item(array.items[i], format, 0);
	ref_array_clear(&array);
	free(to_free);

	return 0;
}

typedef int (*each_tag_name_fn)(const char *name, const char *ref,
				const unsigned char *sha1);

