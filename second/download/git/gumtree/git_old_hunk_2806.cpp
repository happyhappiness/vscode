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
