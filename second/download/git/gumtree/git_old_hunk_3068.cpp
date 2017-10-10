
	strbuf_addf(&buf2, "refs/heads/test:refs/remotes/%s/test", name);
	if (!valid_fetch_refspec(buf2.buf))
		die(_("'%s' is not a valid remote name"), name);

	strbuf_addf(&buf, "remote.%s.url", name);
	if (git_config_set(buf.buf, url))
		return 1;

	if (!mirror || mirror & MIRROR_FETCH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.fetch", name);
		if (track.nr == 0)
			string_list_append(&track, "*");
		for (i = 0; i < track.nr; i++) {
			if (add_branch(buf.buf, track.items[i].string,
				       name, mirror, &buf2))
				return 1;
		}
	}

	if (mirror & MIRROR_PUSH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.mirror", name);
		if (git_config_set(buf.buf, "true"))
			return 1;
	}

	if (fetch_tags != TAGS_DEFAULT) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.tagopt", name);
		if (git_config_set(buf.buf,
			fetch_tags == TAGS_SET ? "--tags" : "--no-tags"))
			return 1;
	}

	if (fetch && fetch_remote(name))
		return 1;

	if (master) {
