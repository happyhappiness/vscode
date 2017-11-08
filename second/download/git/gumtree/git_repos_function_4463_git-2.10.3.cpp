static void distribute_blame(struct scoreboard *sb, struct blame_entry *blamed)
{
	blamed = blame_sort(blamed, compare_blame_suspect);
	while (blamed)
	{
		struct origin *porigin = blamed->suspect;
		struct blame_entry *suspects = NULL;
		do {
			struct blame_entry *next = blamed->next;
			blamed->next = suspects;
			suspects = blamed;
			blamed = next;
		} while (blamed && blamed->suspect == porigin);
		suspects = reverse_blame(suspects, NULL);
		queue_blames(sb, porigin, suspects);
	}
}