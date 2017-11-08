static void check_ref_valid(struct object_id *object,
			    struct object_id *prev,
			    struct strbuf *ref,
			    int force)
{
	strbuf_reset(ref);
	strbuf_addf(ref, "%s%s", git_replace_ref_base, oid_to_hex(object));
	if (check_refname_format(ref->buf, 0))
		die("'%s' is not a valid ref name.", ref->buf);

	if (read_ref(ref->buf, prev->hash))
		oidclr(prev);
	else if (!force)
		die("replace ref '%s' already exists", ref->buf);
}