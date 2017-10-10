							   o,
							   NULL,
							   NULL);
			}
		}
	}
	string_list_clear(&a_by_dst, 0);
	string_list_clear(&b_by_dst, 0);

	return clean_merge;
}

static unsigned char *stage_sha(const unsigned char *sha, unsigned mode)
{
	return (is_null_sha1(sha) || mode == 0) ? NULL: (unsigned char *)sha;
}

static int read_sha1_strbuf(const unsigned char *sha1, struct strbuf *dst)
{
	void *buf;
	enum object_type type;
	unsigned long size;
	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error(_("cannot read object %s"), sha1_to_hex(sha1));
	if (type != OBJ_BLOB) {
		free(buf);
		return error(_("object %s is not a blob"), sha1_to_hex(sha1));
	}
	strbuf_attach(dst, buf, size, size + 1);
	return 0;
}

static int blob_unchanged(const unsigned char *o_sha,
			  unsigned o_mode,
			  const unsigned char *a_sha,
			  unsigned a_mode,
			  int renormalize, const char *path)
{
	struct strbuf o = STRBUF_INIT;
	struct strbuf a = STRBUF_INIT;
	int ret = 0; /* assume changed for safety */

	if (a_mode != o_mode)
		return 0;
	if (sha_eq(o_sha, a_sha))
		return 1;
	if (!renormalize)
		return 0;

	assert(o_sha && a_sha);
	if (read_sha1_strbuf(o_sha, &o) || read_sha1_strbuf(a_sha, &a))
		goto error_return;
	/*
	 * Note: binary | is used so that both renormalizations are
	 * performed.  Comparison can be skipped if both files are
	 * unchanged since their sha1s have already been compared.
	 */
