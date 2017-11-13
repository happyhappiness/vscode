static void update_store_ref_name(struct ref_update *update,
				  const char *ref_name)
{
	if (check_refname_format(ref_name, REFNAME_ALLOW_ONELEVEL))
		die("invalid ref format: %s", ref_name);
	update->ref_name = xstrdup(ref_name);
}