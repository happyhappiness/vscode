}

#else
#define ll_find_deltas(l, s, w, d, p)	find_deltas(l, &s, w, d, p)
#endif

static int add_ref_tag(const char *path, const struct object_id *oid, int flag, void *cb_data)
{
	struct object_id peeled;

	if (starts_with(path, "refs/tags/") && /* is a tag? */
	    !peel_ref(path, peeled.hash)    && /* peelable? */
	    packlist_find(&to_pack, peeled.hash, NULL))      /* object packed? */
		add_object_entry(oid->hash, OBJ_TAG, NULL, 0);
	return 0;
}

static void prepare_pack(int window, int depth)
{
	struct object_entry **delta_list;
