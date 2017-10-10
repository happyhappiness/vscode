		strbuf_attach(&last_blob.data, buf, size, size);
		last_blob.depth = oe->depth;
	} else
		free(buf);
}

static void parse_get_mark(const char *p)
{
	struct object_entry *oe = oe;
	char output[42];

	/* get-mark SP <object> LF */
	if (*p != ':')
		die("Not a mark: %s", p);

	oe = find_mark(parse_mark_ref_eol(p));
	if (!oe)
		die("Unknown mark: %s", command_buf.buf);

	snprintf(output, sizeof(output), "%s\n", sha1_to_hex(oe->idx.sha1));
	cat_blob_write(output, 41);
}

static void parse_cat_blob(const char *p)
{
	struct object_entry *oe = oe;
	unsigned char sha1[20];

	/* cat-blob SP <object> LF */
