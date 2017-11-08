static void update_entry(struct stage_data *entry,
			 struct diff_filespec *o,
			 struct diff_filespec *a,
			 struct diff_filespec *b)
{
	entry->processed = 0;
	entry->stages[1].mode = o->mode;
	entry->stages[2].mode = a->mode;
	entry->stages[3].mode = b->mode;
	hashcpy(entry->stages[1].sha, o->sha1);
	hashcpy(entry->stages[2].sha, a->sha1);
	hashcpy(entry->stages[3].sha, b->sha1);
}