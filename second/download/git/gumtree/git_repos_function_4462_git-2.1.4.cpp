static void snarf_refs(int head, int remotes)
{
	if (head) {
		int orig_cnt = ref_name_cnt;
		for_each_ref(append_head_ref, NULL);
		sort_ref_range(orig_cnt, ref_name_cnt);
	}
	if (remotes) {
		int orig_cnt = ref_name_cnt;
		for_each_ref(append_remote_ref, NULL);
		sort_ref_range(orig_cnt, ref_name_cnt);
	}
}