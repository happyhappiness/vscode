static void update_store_new_sha1(struct ref_update *update,
				  const char *newvalue)
{
	if (*newvalue && get_sha1(newvalue, update->new_sha1))
		die("invalid new value for ref %s: %s",
		    update->ref_name, newvalue);
}