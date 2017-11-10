int update_ref_oid(const char *msg, const char *refname,
	       const struct object_id *new_oid, const struct object_id *old_oid,
	       unsigned int flags, enum action_on_err onerr)
{
	return update_ref(msg, refname, new_oid ? new_oid->hash : NULL,
		old_oid ? old_oid->hash : NULL, flags, onerr);
}