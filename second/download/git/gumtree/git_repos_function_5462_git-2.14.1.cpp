static void show_result(void)
{
	struct merge_list *walk;

	walk = merge_result;
	while (walk) {
		show_result_list(walk);
		show_diff(walk);
		walk = walk->next;
	}
}