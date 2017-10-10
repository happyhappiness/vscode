							   o,
							   NULL,
							   NULL);
			}
		}
	}
cleanup_and_return:
	string_list_clear(&a_by_dst, 0);
	string_list_clear(&b_by_dst, 0);

	return clean_merge;
}

static struct object_id *stage_oid(const struct object_id *oid, unsigned mode)
{
	return (is_null_oid(oid) || mode == 0) ? NULL: (struct object_id *)oid;
}

static int read_oid_strbuf(struct merge_options *o,
	const struct object_id *oid, struct strbuf *dst)
{
	void *buf;
	enum object_type type;
	unsigned long size;
	buf = read_sha1_file(oid->hash, &type, &size);
	if (!buf)
		return err(o, _("cannot read object %s"), oid_to_hex(oid));
	if (type != OBJ_BLOB) {
		free(buf);
		return err(o, _("object %s is not a blob"), oid_to_hex(oid));
	}
	strbuf_attach(dst, buf, size, size + 1);
	return 0;
}

static int blob_unchanged(struct merge_options *opt,
			  const struct object_id *o_oid,
			  unsigned o_mode,
			  const struct object_id *a_oid,
			  unsigned a_mode,
			  int renormalize, const char *path)
{
	struct strbuf o = STRBUF_INIT;
	struct strbuf a = STRBUF_INIT;
	int ret = 0; /* assume changed for safety */

	if (a_mode != o_mode)
		return 0;
	if (oid_eq(o_oid, a_oid))
		return 1;
	if (!renormalize)
		return 0;

	assert(o_oid && a_oid);
	if (read_oid_strbuf(opt, o_oid, &o) || read_oid_strbuf(opt, a_oid, &a))
		goto error_return;
	/*
	 * Note: binary | is used so that both renormalizations are
	 * performed.  Comparison can be skipped if both files are
	 * unchanged since their sha1s have already been compared.
	 */
