#include "commit-slab.h"
#include "dir.h"
#include "cache-tree.h"

volatile show_early_output_fn_t show_early_output;

char *path_name(const struct name_path *path, const char *name)
{
	const struct name_path *p;
	char *n, *m;
	int nlen = strlen(name);
	int len = nlen + 1;

	for (p = path; p; p = p->up) {
		if (p->elem_len)
			len += p->elem_len + 1;
	}
	n = xmalloc(len);
	m = n + len - (nlen + 1);
	strcpy(m, name);
	for (p = path; p; p = p->up) {
		if (p->elem_len) {
			m -= p->elem_len + 1;
			memcpy(m, p->elem, p->elem_len);
			m[p->elem_len] = '/';
		}
	}
	return n;
}

static int show_path_component_truncated(FILE *out, const char *name, int len)
{
	int cnt;
	for (cnt = 0; cnt < len; cnt++) {
		int ch = name[cnt];
		if (!ch || ch == '\n')
			return -1;
		fputc(ch, out);
	}
	return len;
}

static int show_path_truncated(FILE *out, const struct name_path *path)
{
	int emitted, ours;

	if (!path)
		return 0;
	emitted = show_path_truncated(out, path->up);
	if (emitted < 0)
		return emitted;
	if (emitted)
		fputc('/', out);
	ours = show_path_component_truncated(out, path->elem, path->elem_len);
	if (ours < 0)
		return ours;
	return ours || emitted;
}

void show_object_with_name(FILE *out, struct object *obj,
			   const struct name_path *path, const char *component)
{
	struct name_path leaf;
	leaf.up = (struct name_path *)path;
	leaf.elem = component;
	leaf.elem_len = strlen(component);

	fprintf(out, "%s ", sha1_to_hex(obj->sha1));
	show_path_truncated(out, &leaf);
	fputc('\n', out);
}

static void mark_blob_uninteresting(struct blob *blob)
{
	if (!blob)
