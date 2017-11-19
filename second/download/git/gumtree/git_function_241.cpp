static int find_header(struct apply_state *state,
		       const char *line,
		       unsigned long size,
		       int *hdrsize,
		       struct patch *patch)
{
	unsigned long offset, len;

	patch->is_toplevel_relative = 0;
	patch->is_rename = patch->is_copy = 0;
	patch->is_new = patch->is_delete = -1;
	patch->old_mode = patch->new_mode = 0;
	patch->old_name = patch->new_name = NULL;
	for (offset = 0; size > 0; offset += len, size -= len, line += len, state->linenr++) {
		unsigned long nextlen;

		len = linelen(line, size);
		if (!len)
			break;

		/* Testing this early allows us to take a few shortcuts.. */
		if (len < 6)
			continue;

		/*
		 * Make sure we don't find any unconnected patch fragments.
		 * That's a sign that we didn't find a header, and that a
		 * patch has become corrupted/broken up.
		 */
		if (!memcmp("@@ -", line, 4)) {
			struct fragment dummy;
			if (parse_fragment_header(line, len, &dummy) < 0)
				continue;
			die(_("patch fragment without header at line %d: %.*s"),
			    state->linenr, (int)len-1, line);
		}

		if (size < len + 6)
			break;

		/*
		 * Git patch? It might not have a real patch, just a rename
		 * or mode change, so we handle that specially
		 */
		if (!memcmp("diff --git ", line, 11)) {
			int git_hdr_len = parse_git_header(state, line, len, size, patch);
			if (git_hdr_len <= len)
				continue;
			if (!patch->old_name && !patch->new_name) {
				if (!patch->def_name)
					die(Q_("git diff header lacks filename information when removing "
					       "%d leading pathname component (line %d)",
					       "git diff header lacks filename information when removing "
					       "%d leading pathname components (line %d)",
					       state->p_value),
					    state->p_value, state->linenr);
				patch->old_name = xstrdup(patch->def_name);
				patch->new_name = xstrdup(patch->def_name);
			}
			if (!patch->is_delete && !patch->new_name)
				die("git diff header lacks filename information "
				    "(line %d)", state->linenr);
			patch->is_toplevel_relative = 1;
			*hdrsize = git_hdr_len;
			return offset;
		}

		/* --- followed by +++ ? */
		if (memcmp("--- ", line,  4) || memcmp("+++ ", line + len, 4))
			continue;

		/*
		 * We only accept unified patches, so we want it to
		 * at least have "@@ -a,b +c,d @@\n", which is 14 chars
		 * minimum ("@@ -0,0 +1 @@\n" is the shortest).
		 */
		nextlen = linelen(line + len, size - len);
		if (size < nextlen + 14 || memcmp("@@ -", line + len + nextlen, 4))
			continue;

		/* Ok, we'll consider it a patch */
		parse_traditional_patch(state, line, line+len, patch);
		*hdrsize = len + nextlen;
		state->linenr += 2;
		return offset;
	}
	return -1;
}