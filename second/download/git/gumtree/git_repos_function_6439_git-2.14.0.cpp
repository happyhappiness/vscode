static int check_old_oid(struct ref_update *update, struct object_id *oid,
			 struct strbuf *err)
{
	if (!(update->flags & REF_HAVE_OLD) ||
		   !oidcmp(oid, &update->old_oid))
		return 0;

	if (is_null_oid(&update->old_oid))
		strbuf_addf(err, "cannot lock ref '%s': "
			    "reference already exists",
			    original_update_refname(update));
	else if (is_null_oid(oid))
		strbuf_addf(err, "cannot lock ref '%s': "
			    "reference is missing but expected %s",
			    original_update_refname(update),
			    oid_to_hex(&update->old_oid));
	else
		strbuf_addf(err, "cannot lock ref '%s': "
			    "is at %s but expected %s",
			    original_update_refname(update),
			    oid_to_hex(oid),
			    oid_to_hex(&update->old_oid));

	return -1;
}