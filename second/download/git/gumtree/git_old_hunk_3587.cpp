 * header).  Read hunks that belong to this patch into fragments and hang
 * them to the given patch structure.
 *
 * The (fragment->patch, fragment->size) pair points into the memory given
 * by the caller, not a copy, when we return.
 */
static int parse_single_patch(const char *line, unsigned long size, struct patch *patch)
{
	unsigned long offset = 0;
	unsigned long oldlines = 0, newlines = 0, context = 0;
	struct fragment **fragp = &patch->fragments;

	while (size > 4 && !memcmp(line, "@@ -", 4)) {
		struct fragment *fragment;
		int len;

		fragment = xcalloc(1, sizeof(*fragment));
		fragment->linenr = linenr;
		len = parse_fragment(line, size, patch, fragment);
		if (len <= 0)
			die(_("corrupt patch at line %d"), linenr);
		fragment->patch = line;
		fragment->size = len;
		oldlines += fragment->oldlines;
		newlines += fragment->newlines;
		context += fragment->leading + fragment->trailing;

