void check_for_new_submodule_commits(struct object_id *oid)
{
	if (!initialized_fetch_ref_tips) {
		for_each_ref(append_oid_to_array, &ref_tips_before_fetch);
		initialized_fetch_ref_tips = 1;
	}

	oid_array_append(&ref_tips_after_fetch, oid);
}