static int parse_single_patch(struct apply_state *state,
			      const char *line,
			      unsigned long size,
			      struct patch *patch)
{
	unsigned long offset = 0;
	unsigned long oldlines = 0, newlines = 0, context = 0;
	struct fragment **fragp = &patch->fragments;

	while (size > 4 && !memcmp(line, "@@ -", 4)) {
		struct fragment *fragment;
		int len;

		fragment = xcalloc(1, sizeof(*fragment));
		fragment->linenr = state->linenr;
		len = parse_fragment(state, line, size, patch, fragment);
		if (len <= 0) {
			free(fragment);
			return error(_("corrupt patch at line %d"), state->linenr);
		}
		fragment->patch = line;
		fragment->size = len;
		oldlines += fragment->oldlines;
		newlines += fragment->newlines;
		context += fragment->leading + fragment->trailing;

		*fragp = fragment;
		fragp = &fragment->next;

		offset += len;
		line += len;
		size -= len;
	}

	/*
	 * If something was removed (i.e. we have old-lines) it cannot
	 * be creation, and if something was added it cannot be
	 * deletion.  However, the reverse is not true; --unified=0
	 * patches that only add are not necessarily creation even
	 * though they do not have any old lines, and ones that only
	 * delete are not necessarily deletion.
	 *
	 * Unfortunately, a real creation/deletion patch do _not_ have
	 * any context line by definition, so we cannot safely tell it
	 * apart with --unified=0 insanity.  At least if the patch has
	 * more than one hunk it is not creation or deletion.
	 */
	if (patch->is_new < 0 &&
	    (oldlines || (patch->fragments && patch->fragments->next)))
		patch->is_new = 0;
	if (patch->is_delete < 0 &&
	    (newlines || (patch->fragments && patch->fragments->next)))
		patch->is_delete = 0;

	if (0 < patch->is_new && oldlines)
		return error(_("new file %s depends on old contents"), patch->new_name);
	if (0 < patch->is_delete && newlines)
		return error(_("deleted file %s still has contents"), patch->old_name);
	if (!patch->is_delete && !newlines && context && state->apply_verbosity > verbosity_silent)
		fprintf_ln(stderr,
			   _("** warning: "
			     "file %s becomes empty but is not deleted"),
			   patch->new_name);

	return offset;
}