static int add_ref_tag(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	unsigned char peeled[20];

	if (starts_with(path, "refs/tags/") && /* is a tag? */
	    !peel_ref(path, peeled)        && /* peelable? */
	    packlist_find(&to_pack, peeled, NULL))      /* object packed? */
		add_object_entry(sha1, OBJ_TAG, NULL, 0);
	return 0;
}