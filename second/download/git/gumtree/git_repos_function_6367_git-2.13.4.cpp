static int check_old_oid(struct ref_update *update, struct object_id *oid,
			 struct strbuf *err)
{
	if (!(update->flags & REF_HAVE_OLD) ||
		   !hashcmp(oid->hash, update->old_sha1))
		return 0;

	if (is_null_sha1(update->old_sha1))
		strbuf_addf(err, "cannot lock ref '%s': "
			    "reference already exists",
			    original_update_refname(update));
	else if (is_null_oid(oid))
		strbuf_addf(err, "cannot lock ref '%s': "
			    "reference is missing but expected %s",
			    original_update_refname(update),
			    sha1_to_hex(update->old_sha1));
	else
		strbuf_addf(err, "cannot lock ref '%s': "
			    "is at %s but expected %s",
			    original_update_refname(update),
			    oid_to_hex(oid),
			    sha1_to_hex(update->old_sha1));

	return -1;
}