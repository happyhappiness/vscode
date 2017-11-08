static int fsck_tag_buffer(struct tag *tag, const char *data,
	unsigned long size, fsck_error error_func)
{
	unsigned char sha1[20];
	int ret = 0;
	const char *buffer;
	char *to_free = NULL, *eol;
	struct strbuf sb = STRBUF_INIT;

	if (data)
		buffer = data;
	else {
		enum object_type type;

		buffer = to_free =
			read_sha1_file(tag->object.sha1, &type, &size);
		if (!buffer)
			return error_func(&tag->object, FSCK_ERROR,
				"cannot read tag object");

		if (type != OBJ_TAG) {
			ret = error_func(&tag->object, FSCK_ERROR,
				"expected tag got %s",
			    typename(type));
			goto done;
		}
	}

	if (verify_headers(buffer, size, &tag->object, error_func))
		goto done;

	if (!skip_prefix(buffer, "object ", &buffer)) {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'object' line");
		goto done;
	}
	if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n') {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid 'object' line format - bad sha1");
		goto done;
	}
	buffer += 41;

	if (!skip_prefix(buffer, "type ", &buffer)) {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'type' line");
		goto done;
	}
	eol = strchr(buffer, '\n');
	if (!eol) {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - unexpected end after 'type' line");
		goto done;
	}
	if (type_from_string_gently(buffer, eol - buffer, 1) < 0)
		ret = error_func(&tag->object, FSCK_ERROR, "invalid 'type' value");
	if (ret)
		goto done;
	buffer = eol + 1;

	if (!skip_prefix(buffer, "tag ", &buffer)) {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - expected 'tag' line");
		goto done;
	}
	eol = strchr(buffer, '\n');
	if (!eol) {
		ret = error_func(&tag->object, FSCK_ERROR, "invalid format - unexpected end after 'type' line");
		goto done;
	}
	strbuf_addf(&sb, "refs/tags/%.*s", (int)(eol - buffer), buffer);
	if (check_refname_format(sb.buf, 0))
		error_func(&tag->object, FSCK_WARN, "invalid 'tag' name: %.*s",
			   (int)(eol - buffer), buffer);
	buffer = eol + 1;

	if (!skip_prefix(buffer, "tagger ", &buffer))
		/* early tags do not contain 'tagger' lines; warn only */
		error_func(&tag->object, FSCK_WARN, "invalid format - expected 'tagger' line");
	else
		ret = fsck_ident(&buffer, &tag->object, error_func);

done:
	strbuf_release(&sb);
	free(to_free);
	return ret;
}