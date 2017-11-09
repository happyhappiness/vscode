static int ok_to_give_up(void)
{
	int i;

	if (!have_obj.nr)
		return 0;

	for (i = 0; i < want_obj.nr; i++) {
		struct object *want = want_obj.objects[i].item;

		if (want->flags & COMMON_KNOWN)
			continue;
		want = deref_tag(want, "a want line", 0);
		if (!want || want->type != OBJ_COMMIT) {
			/* no way to tell if this is reachable by
			 * looking at the ancestry chain alone, so
			 * leave a note to ourselves not to worry about
			 * this object anymore.
			 */
			want_obj.objects[i].item->flags |= COMMON_KNOWN;
			continue;
		}
		if (!reachable((struct commit *)want))
			return 0;
	}
	return 1;
}