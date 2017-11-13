static void handle_tag(const char *name, struct tag *tag)
{
	unsigned long size;
	enum object_type type;
	char *buf;
	const char *tagger, *tagger_end, *message;
	size_t message_size = 0;
	struct object *tagged;
	int tagged_mark;
	struct commit *p;

	/* Trees have no identifier in fast-export output, thus we have no way
	 * to output tags of trees, tags of tags of trees, etc.  Simply omit
	 * such tags.
	 */
	tagged = tag->tagged;
	while (tagged->type == OBJ_TAG) {
		tagged = ((struct tag *)tagged)->tagged;
	}
	if (tagged->type == OBJ_TREE) {
		warning("Omitting tag %s,\nsince tags of trees (or tags of tags of trees, etc.) are not supported.",
			sha1_to_hex(tag->object.sha1));
		return;
	}

	buf = read_sha1_file(tag->object.sha1, &type, &size);
	if (!buf)
		die ("Could not read tag %s", sha1_to_hex(tag->object.sha1));
	message = memmem(buf, size, "\n\n", 2);
	if (message) {
		message += 2;
		message_size = strlen(message);
	}
	tagger = memmem(buf, message ? message - buf : size, "\ntagger ", 8);
	if (!tagger) {
		if (fake_missing_tagger)
			tagger = "tagger Unspecified Tagger "
				"<unspecified-tagger> 0 +0000";
		else
			tagger = "";
		tagger_end = tagger + strlen(tagger);
	} else {
		tagger++;
		tagger_end = strchrnul(tagger, '\n');
		if (anonymize)
			anonymize_ident_line(&tagger, &tagger_end);
	}

	if (anonymize) {
		name = anonymize_refname(name);
		if (message) {
			static struct hashmap tags;
			message = anonymize_mem(&tags, anonymize_tag,
						message, &message_size);
		}
	}

	/* handle signed tags */
	if (message) {
		const char *signature = strstr(message,
					       "\n-----BEGIN PGP SIGNATURE-----\n");
		if (signature)
			switch(signed_tag_mode) {
			case ABORT:
				die ("Encountered signed tag %s; use "
				     "--signed-tags=<mode> to handle it.",
				     sha1_to_hex(tag->object.sha1));
			case WARN:
				warning ("Exporting signed tag %s",
					 sha1_to_hex(tag->object.sha1));
				/* fallthru */
			case VERBATIM:
				break;
			case WARN_STRIP:
				warning ("Stripping signature from tag %s",
					 sha1_to_hex(tag->object.sha1));
				/* fallthru */
			case STRIP:
				message_size = signature + 1 - message;
				break;
			}
	}

	/* handle tag->tagged having been filtered out due to paths specified */
	tagged = tag->tagged;
	tagged_mark = get_object_mark(tagged);
	if (!tagged_mark) {
		switch(tag_of_filtered_mode) {
		case ABORT:
			die ("Tag %s tags unexported object; use "
			     "--tag-of-filtered-object=<mode> to handle it.",
			     sha1_to_hex(tag->object.sha1));
		case DROP:
			/* Ignore this tag altogether */
			return;
		case REWRITE:
			if (tagged->type != OBJ_COMMIT) {
				die ("Tag %s tags unexported %s!",
				     sha1_to_hex(tag->object.sha1),
				     typename(tagged->type));
			}
			p = (struct commit *)tagged;
			for (;;) {
				if (p->parents && p->parents->next)
					break;
				if (p->object.flags & UNINTERESTING)
					break;
				if (!(p->object.flags & TREESAME))
					break;
				if (!p->parents)
					die ("Can't find replacement commit for tag %s\n",
					     sha1_to_hex(tag->object.sha1));
				p = p->parents->item;
			}
			tagged_mark = get_object_mark(&p->object);
		}
	}

	if (starts_with(name, "refs/tags/"))
		name += 10;
	printf("tag %s\nfrom :%d\n%.*s%sdata %d\n%.*s\n",
	       name, tagged_mark,
	       (int)(tagger_end - tagger), tagger,
	       tagger == tagger_end ? "" : "\n",
	       (int)message_size, (int)message_size, message ? message : "");
}