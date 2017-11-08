static void format_note(struct notes_tree *t, const unsigned char *object_sha1,
			struct strbuf *sb, const char *output_encoding, int raw)
{
	static const char utf8[] = "utf-8";
	const unsigned char *sha1;
	char *msg, *msg_p;
	unsigned long linelen, msglen;
	enum object_type type;

	if (!t)
		t = &default_notes_tree;
	if (!t->initialized)
		init_notes(t, NULL, NULL, 0);

	sha1 = get_note(t, object_sha1);
	if (!sha1)
		return;

	if (!(msg = read_sha1_file(sha1, &type, &msglen)) || type != OBJ_BLOB) {
		free(msg);
		return;
	}

	if (output_encoding && *output_encoding &&
	    !is_encoding_utf8(output_encoding)) {
		char *reencoded = reencode_string(msg, output_encoding, utf8);
		if (reencoded) {
			free(msg);
			msg = reencoded;
			msglen = strlen(msg);
		}
	}

	/* we will end the annotation by a newline anyway */
	if (msglen && msg[msglen - 1] == '\n')
		msglen--;

	if (!raw) {
		const char *ref = t->ref;
		if (!ref || !strcmp(ref, GIT_NOTES_DEFAULT_REF)) {
			strbuf_addstr(sb, "\nNotes:\n");
		} else {
			if (starts_with(ref, "refs/"))
				ref += 5;
			if (starts_with(ref, "notes/"))
				ref += 6;
			strbuf_addf(sb, "\nNotes (%s):\n", ref);
		}
	}

	for (msg_p = msg; msg_p < msg + msglen; msg_p += linelen + 1) {
		linelen = strchrnul(msg_p, '\n') - msg_p;

		if (!raw)
			strbuf_addstr(sb, "    ");
		strbuf_add(sb, msg_p, linelen);
		strbuf_addch(sb, '\n');
	}

	free(msg);
}