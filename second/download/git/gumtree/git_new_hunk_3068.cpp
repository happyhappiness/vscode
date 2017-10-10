
	strbuf_addf(&buf2, "refs/heads/test:refs/remotes/%s/test", name);
	if (!valid_fetch_refspec(buf2.buf))
		die(_("'%s' is not a valid remote name"), name);

	strbuf_addf(&buf, "remote.%s.url", name);
	git_config_set(buf.buf, url);

	if (!mirror || mirror & MIRROR_FETCH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.fetch", name);
		if (track.nr == 0)
			string_list_append(&track, "*");
		for (i = 0; i < track.nr; i++) {
			add_branch(buf.buf, track.items[i].string,
				   name, mirror, &buf2);
		}
	}

	if (mirror & MIRROR_PUSH) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.mirror", name);
		git_config_set(buf.buf, "true");
	}

	if (fetch_tags != TAGS_DEFAULT) {
		strbuf_reset(&buf);
		strbuf_addf(&buf, "remote.%s.tagopt", name);
		git_config_set(buf.buf,
			       fetch_tags == TAGS_SET ? "--tags" : "--no-tags");
	}

	if (fetch && fetch_remote(name))
		return 1;

	if (master) {
