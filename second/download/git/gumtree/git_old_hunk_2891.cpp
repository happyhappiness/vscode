#include "parse-options.h"
#include "diff.h"
#include "revision.h"
#include "gpg-interface.h"
#include "sha1-array.h"
#include "column.h"

static const char * const git_tag_usage[] = {
	N_("git tag [-a | -s | -u <key-id>] [-f] [-m <msg> | -F <file>] <tagname> [<head>]"),
	N_("git tag -d <tagname>..."),
	N_("git tag -l [-n[<num>]] [--contains <commit>] [--points-at <object>]"
		"\n\t\t[<pattern>...]"),
	N_("git tag -v <tagname>..."),
	NULL
};

#define STRCMP_SORT     0	/* must be zero */
#define VERCMP_SORT     1
#define SORT_MASK       0x7fff
#define REVERSE_SORT    0x8000

static int tag_sort;

struct tag_filter {
	const char **patterns;
	int lines;
	int sort;
	struct string_list tags;
	struct commit_list *with_commit;
};

static struct sha1_array points_at;
static unsigned int colopts;

static int match_pattern(const char **patterns, const char *ref)
{
	/* no pattern means match everything */
	if (!*patterns)
		return 1;
	for (; *patterns; patterns++)
		if (!wildmatch(*patterns, ref, 0, NULL))
			return 1;
	return 0;
}

static const unsigned char *match_points_at(const char *refname,
					    const unsigned char *sha1)
{
	const unsigned char *tagged_sha1 = NULL;
	struct object *obj;

	if (sha1_array_lookup(&points_at, sha1) >= 0)
		return sha1;
	obj = parse_object(sha1);
	if (!obj)
		die(_("malformed object at '%s'"), refname);
	if (obj->type == OBJ_TAG)
		tagged_sha1 = ((struct tag *)obj)->tagged->sha1;
	if (tagged_sha1 && sha1_array_lookup(&points_at, tagged_sha1) >= 0)
		return tagged_sha1;
	return NULL;
}

static int in_commit_list(const struct commit_list *want, struct commit *c)
{
	for (; want; want = want->next)
		if (!hashcmp(want->item->object.sha1, c->object.sha1))
			return 1;
	return 0;
}

enum contains_result {
	CONTAINS_UNKNOWN = -1,
	CONTAINS_NO = 0,
	CONTAINS_YES = 1
};

/*
 * Test whether the candidate or one of its parents is contained in the list.
 * Do not recurse to find out, though, but return -1 if inconclusive.
 */
static enum contains_result contains_test(struct commit *candidate,
			    const struct commit_list *want)
{
	/* was it previously marked as containing a want commit? */
	if (candidate->object.flags & TMP_MARK)
		return 1;
	/* or marked as not possibly containing a want commit? */
	if (candidate->object.flags & UNINTERESTING)
		return 0;
	/* or are we it? */
	if (in_commit_list(want, candidate)) {
		candidate->object.flags |= TMP_MARK;
		return 1;
	}

	if (parse_commit(candidate) < 0)
		return 0;

	return -1;
}

/*
 * Mimicking the real stack, this stack lives on the heap, avoiding stack
 * overflows.
 *
 * At each recursion step, the stack items points to the commits whose
 * ancestors are to be inspected.
 */
struct stack {
	int nr, alloc;
	struct stack_entry {
		struct commit *commit;
		struct commit_list *parents;
	} *stack;
};

static void push_to_stack(struct commit *candidate, struct stack *stack)
{
	int index = stack->nr++;
	ALLOC_GROW(stack->stack, stack->nr, stack->alloc);
	stack->stack[index].commit = candidate;
	stack->stack[index].parents = candidate->parents;
}

static enum contains_result contains(struct commit *candidate,
		const struct commit_list *want)
{
	struct stack stack = { 0, 0, NULL };
	int result = contains_test(candidate, want);

	if (result != CONTAINS_UNKNOWN)
		return result;

	push_to_stack(candidate, &stack);
	while (stack.nr) {
		struct stack_entry *entry = &stack.stack[stack.nr - 1];
		struct commit *commit = entry->commit;
		struct commit_list *parents = entry->parents;

		if (!parents) {
			commit->object.flags |= UNINTERESTING;
			stack.nr--;
		}
		/*
		 * If we just popped the stack, parents->item has been marked,
		 * therefore contains_test will return a meaningful 0 or 1.
		 */
		else switch (contains_test(parents->item, want)) {
		case CONTAINS_YES:
			commit->object.flags |= TMP_MARK;
			stack.nr--;
			break;
		case CONTAINS_NO:
			entry->parents = parents->next;
			break;
		case CONTAINS_UNKNOWN:
			push_to_stack(parents->item, &stack);
			break;
		}
	}
	free(stack.stack);
	return contains_test(candidate, want);
}

static void show_tag_lines(const struct object_id *oid, int lines)
{
	int i;
	unsigned long size;
	enum object_type type;
	char *buf, *sp, *eol;
	size_t len;

	buf = read_sha1_file(oid->hash, &type, &size);
	if (!buf)
		die_errno("unable to read object %s", oid_to_hex(oid));
	if (type != OBJ_COMMIT && type != OBJ_TAG)
		goto free_return;
	if (!size)
		die("an empty %s object %s?",
		    typename(type), oid_to_hex(oid));

	/* skip header */
	sp = strstr(buf, "\n\n");
	if (!sp)
		goto free_return;

	/* only take up to "lines" lines, and strip the signature from a tag */
	if (type == OBJ_TAG)
		size = parse_signature(buf, size);
	for (i = 0, sp += 2; i < lines && sp < buf + size; i++) {
		if (i)
			printf("\n    ");
		eol = memchr(sp, '\n', size - (sp - buf));
		len = eol ? eol - sp : size - (sp - buf);
		fwrite(sp, len, 1, stdout);
		if (!eol)
			break;
		sp = eol + 1;
	}
free_return:
	free(buf);
}

static int show_reference(const char *refname, const struct object_id *oid,
			  int flag, void *cb_data)
{
	struct tag_filter *filter = cb_data;

	if (match_pattern(filter->patterns, refname)) {
		if (filter->with_commit) {
			struct commit *commit;

			commit = lookup_commit_reference_gently(oid->hash, 1);
			if (!commit)
				return 0;
			if (!contains(commit, filter->with_commit))
				return 0;
		}

		if (points_at.nr && !match_points_at(refname, oid->hash))
			return 0;

		if (!filter->lines) {
			if (filter->sort)
				string_list_append(&filter->tags, refname);
			else
				printf("%s\n", refname);
			return 0;
		}
		printf("%-15s ", refname);
		show_tag_lines(oid, filter->lines);
		putchar('\n');
	}

	return 0;
}

static int sort_by_version(const void *a_, const void *b_)
{
	const struct string_list_item *a = a_;
	const struct string_list_item *b = b_;
	return versioncmp(a->string, b->string);
}

static int list_tags(const char **patterns, int lines,
		     struct commit_list *with_commit, int sort)
{
	struct tag_filter filter;

	filter.patterns = patterns;
	filter.lines = lines;
	filter.sort = sort;
	filter.with_commit = with_commit;
	memset(&filter.tags, 0, sizeof(filter.tags));
	filter.tags.strdup_strings = 1;

	for_each_tag_ref(show_reference, (void *)&filter);
	if (sort) {
		int i;
		if ((sort & SORT_MASK) == VERCMP_SORT)
			qsort(filter.tags.items, filter.tags.nr,
			      sizeof(struct string_list_item), sort_by_version);
		if (sort & REVERSE_SORT)
			for (i = filter.tags.nr - 1; i >= 0; i--)
				printf("%s\n", filter.tags.items[i].string);
		else
			for (i = 0; i < filter.tags.nr; i++)
				printf("%s\n", filter.tags.items[i].string);
		string_list_clear(&filter.tags, 0);
	}
	return 0;
}

typedef int (*each_tag_name_fn)(const char *name, const char *ref,
				const unsigned char *sha1);

