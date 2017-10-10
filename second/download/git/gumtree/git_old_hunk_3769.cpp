#include "ll-merge.h"
#include "attr.h"
#include "merge-recursive.h"
#include "dir.h"
#include "submodule.h"

static struct tree *shift_tree_object(struct tree *one, struct tree *two,
				      const char *subtree_shift)
{
	struct object_id shifted;

	if (!*subtree_shift) {
