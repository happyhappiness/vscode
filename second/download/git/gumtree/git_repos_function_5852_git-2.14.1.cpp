static void fmt_merge_msg_sigs(struct strbuf *out)
{
	int i, tag_number = 0, first_tag = 0;
	struct strbuf tagbuf = STRBUF_INIT;

	for (i = 0; i < origins.nr; i++) {
		unsigned char *sha1 = origins.items[i].util;
		enum object_type type;
		unsigned long size, len;
		char *buf = read_sha1_file(sha1, &type, &size);
		struct strbuf sig = STRBUF_INIT;

		if (!buf || type != OBJ_TAG)
			goto next;
		len = parse_signature(buf, size);

		if (size == len)
			; /* merely annotated */
		else if (verify_signed_buffer(buf, len, buf + len, size - len, &sig, NULL)) {
			if (!sig.len)
				strbuf_addstr(&sig, "gpg verification failed.\n");
		}

		if (!tag_number++) {
			fmt_tag_signature(&tagbuf, &sig, buf, len);
			first_tag = i;
		} else {
			if (tag_number == 2) {
				struct strbuf tagline = STRBUF_INIT;
				strbuf_addch(&tagline, '\n');
				strbuf_add_commented_lines(&tagline,
						origins.items[first_tag].string,
						strlen(origins.items[first_tag].string));
				strbuf_insert(&tagbuf, 0, tagline.buf,
					      tagline.len);
				strbuf_release(&tagline);
			}
			strbuf_addch(&tagbuf, '\n');
			strbuf_add_commented_lines(&tagbuf,
					origins.items[i].string,
					strlen(origins.items[i].string));
			fmt_tag_signature(&tagbuf, &sig, buf, len);
		}
		strbuf_release(&sig);
	next:
		free(buf);
	}
	if (tagbuf.len) {
		strbuf_addch(out, '\n');
		strbuf_addbuf(out, &tagbuf);
	}
	strbuf_release(&tagbuf);
}