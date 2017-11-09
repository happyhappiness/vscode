void blame_sort_final(struct blame_scoreboard *sb)
{
	sb->ent = llist_mergesort(sb->ent, get_next_blame, set_next_blame,
				  compare_blame_final);
}