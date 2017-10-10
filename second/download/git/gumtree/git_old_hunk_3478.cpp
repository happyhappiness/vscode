#include "strbuf.h"

static int input_error(struct line_buffer *file)
{
	if (!buffer_ferror(file))
		return error("delta preimage ends early");
	return error("cannot read delta preimage: %s", strerror(errno));
}

static int skip_or_whine(struct line_buffer *file, off_t gap)
{
	if (buffer_skip_bytes(file, gap) != gap)
		return input_error(file);
