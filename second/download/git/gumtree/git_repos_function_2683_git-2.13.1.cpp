static struct commit_info *get_commit_info(struct commit *commit,
		struct commit_info_lifo *lifo, int pop)
{
	int i;
	for (i = 0; i < lifo->nr; i++)
		if (lifo->items[i].commit == commit) {
			struct commit_info *result = &lifo->items[i];
			if (pop) {
				if (i + 1 < lifo->nr)
					memmove(lifo->items + i,
						lifo->items + i + 1,
						(lifo->nr - i) *
						sizeof(struct commit_info));
				lifo->nr--;
			}
			return result;
		}
	return NULL;
}