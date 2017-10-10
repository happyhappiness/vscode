		strbuf_attach(&last_blob.data, buf, size, size);
		last_blob.depth = oe->depth;
	} else
		free(buf);
}

static void parse_cat_blob(const char *p)
{
	struct object_entry *oe = oe;
	unsigned char sha1[20];

	/* cat-blob SP <object> LF */
