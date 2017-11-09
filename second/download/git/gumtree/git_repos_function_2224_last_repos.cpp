static void rearrange_packed_git(void)
{
	packed_git = llist_mergesort(packed_git, get_next_packed_git,
				     set_next_packed_git, sort_pack);
}