#include "ll-merge.h"
#include "attr.h"
#include "merge-recursive.h"
#include "dir.h"
#include "submodule.h"

static void flush_output(struct merge_options *o)
{
	if (o->buffer_output < 2 && o->obuf.len) {
		fputs(o->obuf.buf, stdout);
		strbuf_reset(&o->obuf);
	}
}

static int err(struct merge_options *o, const char *err, ...)
{
	va_list params;

	if (o->buffer_output < 2)
		flush_output(o);
	else {
		strbuf_complete(&o->obuf, '\n');
		strbuf_addstr(&o->obuf, "error: ");
	}
	va_start(params, err);
	strbuf_vaddf(&o->obuf, err, params);
	va_end(params);
	if (o->buffer_output > 1)
		strbuf_addch(&o->obuf, '\n');
	else {
		error("%s", o->obuf.buf);
		strbuf_reset(&o->obuf);
	}

	return -1;
}

static struct tree *shift_tree_object(struct tree *one, struct tree *two,
				      const char *subtree_shift)
{
	struct object_id shifted;

	if (!*subtree_shift) {
