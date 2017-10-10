#include "tree-walk.h"
#include "commit.h"
#include "tag.h"
#include "fsck.h"
#include "refs.h"
#include "utf8.h"

static int fsck_walk_tree(struct tree *tree, fsck_walk_func walk, void *data)
{
	struct tree_desc desc;
	struct name_entry entry;
	int res = 0;

	if (parse_tree(tree))
