#include "parse-options.h"

static int show_merge_base(struct commit **rev, int rev_nr, int show_all)
{
	struct commit_list *result;

	result = get_merge_bases_many_dirty(rev[0], rev_nr - 1, rev + 1);

	if (!result)
		return 1;

	while (result) {
		printf("%s\n", sha1_to_hex(result->item->object.sha1));
