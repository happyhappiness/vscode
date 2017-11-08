static char *find_name_gnu(struct apply_state *state,
			   const char *line,
			   const char *def,
			   int p_value)
{
	struct strbuf name = STRBUF_INIT;
	char *cp;

	/*
	 * Proposed "new-style" GNU patch/diff format; see
	 * http://marc.info/?l=git&m=112927316408690&w=2
	 */
	if (unquote_c_style(&name, line, NULL)) {
		strbuf_release(&name);
		return NULL;
	}

	for (cp = name.buf; p_value; p_value--) {
		cp = strchr(cp, '/');
		if (!cp) {
			strbuf_release(&name);
			return NULL;
		}
		cp++;
	}

	strbuf_remove(&name, 0, cp - name.buf);
	if (state->root.len)
		strbuf_insert(&name, 0, state->root.buf, state->root.len);
	return squash_slash(strbuf_detach(&name, NULL));
}