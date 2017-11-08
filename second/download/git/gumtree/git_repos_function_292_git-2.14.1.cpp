int copy_note_for_rewrite(struct notes_rewrite_cfg *c,
			  const struct object_id *from_obj, const struct object_id *to_obj)
{
	int ret = 0;
	int i;
	for (i = 0; c->trees[i]; i++)
		ret = copy_note(c->trees[i], from_obj, to_obj, 1, c->combine) || ret;
	return ret;
}