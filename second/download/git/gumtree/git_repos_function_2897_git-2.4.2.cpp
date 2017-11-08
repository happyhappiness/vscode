void check_for_new_submodule_commits(unsigned char new_sha1[20])
{
	if (!initialized_fetch_ref_tips) {
		for_each_ref(add_sha1_to_array, &ref_tips_before_fetch);
		initialized_fetch_ref_tips = 1;
	}

	sha1_array_append(&ref_tips_after_fetch, new_sha1);
}