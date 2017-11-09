static int add_ref_tag(const char *path, const struct object_id *oid, int flag, void *cb_data)
{
	struct object_id peeled;

	if (starts_with(path, "refs/tags/") && /* is a tag? */
	    !peel_ref(path, peeled.hash)    && /* peelable? */
	    packlist_find(&to_pack, peeled.hash, NULL))      /* object packed? */
		add_tag_chain(oid);
	return 0;
}