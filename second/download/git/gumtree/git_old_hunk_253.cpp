 */
#include "cache.h"
#include "diff.h"
#include "diffcore.h"
#include "tree.h"

static void show_entry(struct diff_options *opt, const char *prefix,
		       struct tree_desc *desc, struct strbuf *base);

static int compare_tree_entry(struct tree_desc *t1, struct tree_desc *t2,
			      struct strbuf *base, struct diff_options *opt)
{
	unsigned mode1, mode2;
	const char *path1, *path2;
	const unsigned char *sha1, *sha2;
	int cmp, pathlen1, pathlen2;
	int old_baselen = base->len;

	sha1 = tree_entry_extract(t1, &path1, &mode1);
	sha2 = tree_entry_extract(t2, &path2, &mode2);

	pathlen1 = tree_entry_len(&t1->entry);
	pathlen2 = tree_entry_len(&t2->entry);
	cmp = base_name_compare(path1, pathlen1, mode1, path2, pathlen2, mode2);
	if (cmp < 0) {
		show_entry(opt, "-", t1, base);
		return -1;
	}
	if (cmp > 0) {
		show_entry(opt, "+", t2, base);
		return 1;
	}
	if (!DIFF_OPT_TST(opt, FIND_COPIES_HARDER) && !hashcmp(sha1, sha2) && mode1 == mode2)
		return 0;

	/*
	 * If the filemode has changed to/from a directory from/to a regular
	 * file, we need to consider it a remove and an add.
	 */
	if (S_ISDIR(mode1) != S_ISDIR(mode2)) {
		show_entry(opt, "-", t1, base);
		show_entry(opt, "+", t2, base);
		return 0;
	}

	strbuf_add(base, path1, pathlen1);
	if (DIFF_OPT_TST(opt, RECURSIVE) && S_ISDIR(mode1)) {
		if (DIFF_OPT_TST(opt, TREE_IN_RECURSIVE)) {
			opt->change(opt, mode1, mode2,
				    sha1, sha2, 1, 1, base->buf, 0, 0);
		}
		strbuf_addch(base, '/');
		diff_tree_sha1(sha1, sha2, base->buf, opt);
	} else {
		opt->change(opt, mode1, mode2, sha1, sha2, 1, 1, base->buf, 0, 0);
	}
	strbuf_setlen(base, old_baselen);
	return 0;
}

/* A whole sub-tree went away or appeared */
static void show_tree(struct diff_options *opt, const char *prefix,
		      struct tree_desc *desc, struct strbuf *base)
{
	enum interesting match = entry_not_interesting;
	for (; desc->size; update_tree_entry(desc)) {
		if (match != all_entries_interesting) {
			match = tree_entry_interesting(&desc->entry, base, 0,
						       &opt->pathspec);
			if (match == all_entries_not_interesting)
				break;
			if (match == entry_not_interesting)
				continue;
		}
		show_entry(opt, prefix, desc, base);
	}
}

/* A file entry went away or appeared */
static void show_entry(struct diff_options *opt, const char *prefix,
		       struct tree_desc *desc, struct strbuf *base)
{
	unsigned mode;
	const char *path;
	const unsigned char *sha1 = tree_entry_extract(desc, &path, &mode);
	int pathlen = tree_entry_len(&desc->entry);
	int old_baselen = base->len;

	strbuf_add(base, path, pathlen);
	if (DIFF_OPT_TST(opt, RECURSIVE) && S_ISDIR(mode)) {
		enum object_type type;
		struct tree_desc inner;
		void *tree;
		unsigned long size;

		tree = read_sha1_file(sha1, &type, &size);
		if (!tree || type != OBJ_TREE)
			die("corrupt tree sha %s", sha1_to_hex(sha1));

		if (DIFF_OPT_TST(opt, TREE_IN_RECURSIVE))
			opt->add_remove(opt, *prefix, mode, sha1, 1, base->buf, 0);

		strbuf_addch(base, '/');

		init_tree_desc(&inner, tree, size);
		show_tree(opt, prefix, &inner, base);
		free(tree);
	} else
		opt->add_remove(opt, prefix[0], mode, sha1, 1, base->buf, 0);

	strbuf_setlen(base, old_baselen);
}

static void skip_uninteresting(struct tree_desc *t, struct strbuf *base,
			       struct diff_options *opt,
			       enum interesting *match)
{
	while (t->size) {
		*match = tree_entry_interesting(&t->entry, base, 0, &opt->pathspec);
		if (*match) {
			if (*match == all_entries_not_interesting)
				t->size = 0;
			break;
		}
		update_tree_entry(t);
	}
}

int diff_tree(struct tree_desc *t1, struct tree_desc *t2,
	      const char *base_str, struct diff_options *opt)
{
	struct strbuf base;
	int baselen = strlen(base_str);
	enum interesting t1_match = entry_not_interesting;
	enum interesting t2_match = entry_not_interesting;

	/* Enable recursion indefinitely */
	opt->pathspec.recursive = DIFF_OPT_TST(opt, RECURSIVE);

	strbuf_init(&base, PATH_MAX);
	strbuf_add(&base, base_str, baselen);

	for (;;) {
		if (diff_can_quit_early(opt))
			break;
		if (opt->pathspec.nr) {
			skip_uninteresting(t1, &base, opt, &t1_match);
			skip_uninteresting(t2, &base, opt, &t2_match);
		}
		if (!t1->size) {
			if (!t2->size)
				break;
			show_entry(opt, "+", t2, &base);
			update_tree_entry(t2);
			continue;
		}
		if (!t2->size) {
			show_entry(opt, "-", t1, &base);
			update_tree_entry(t1);
			continue;
		}
		switch (compare_tree_entry(t1, t2, &base, opt)) {
		case -1:
			update_tree_entry(t1);
			continue;
		case 0:
			update_tree_entry(t1);
			/* Fallthrough */
		case 1:
			update_tree_entry(t2);
			continue;
		}
		die("git diff-tree: internal error");
	}

	strbuf_release(&base);
	return 0;
}

/*
 * Does it look like the resulting diff might be due to a rename?
 *  - single entry
 *  - not a valid previous file
