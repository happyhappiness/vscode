static int fetch_with_import(struct transport *transport,
			     int nr_heads, struct ref **to_fetch)
{
	struct child_process fastimport;
	struct helper_data *data = transport->data;
	int i;
	struct ref *posn;
	struct strbuf buf = STRBUF_INIT;

	get_helper(transport);

	if (get_importer(transport, &fastimport))
		die("Couldn't run fast-import");

	for (i = 0; i < nr_heads; i++) {
		posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;

		strbuf_addf(&buf, "import %s\n",
			    posn->symref ? posn->symref : posn->name);
		sendline(data, &buf);
		strbuf_reset(&buf);
	}

	write_constant(data->helper->in, "\n");
	/*
	 * remote-helpers that advertise the bidi-import capability are required to
	 * buffer the complete batch of import commands until this newline before
	 * sending data to fast-import.
	 * These helpers read back data from fast-import on their stdin, which could
	 * be mixed with import commands, otherwise.
	 */

	if (finish_command(&fastimport))
		die("Error while running fast-import");

	/*
	 * The fast-import stream of a remote helper that advertises
	 * the "refspec" capability writes to the refs named after the
	 * right hand side of the first refspec matching each ref we
	 * were fetching.
	 *
	 * (If no "refspec" capability was specified, for historical
	 * reasons we default to the equivalent of *:*.)
	 *
	 * Store the result in to_fetch[i].old_sha1.  Callers such
	 * as "git fetch" can use the value to write feedback to the
	 * terminal, populate FETCH_HEAD, and determine what new value
	 * should be written to peer_ref if the update is a
	 * fast-forward or this is a forced update.
	 */
	for (i = 0; i < nr_heads; i++) {
		char *private, *name;
		posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;
		name = posn->symref ? posn->symref : posn->name;
		if (data->refspecs)
			private = apply_refspecs(data->refspecs, data->refspec_nr, name);
		else
			private = xstrdup(name);
		if (private) {
			if (read_ref(private, posn->old_sha1) < 0)
				die("Could not read ref %s", private);
			free(private);
		}
	}
	strbuf_release(&buf);
	return 0;
}