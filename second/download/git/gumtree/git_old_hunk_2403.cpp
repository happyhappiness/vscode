	return 0;
}

static void get_patch_ids(struct rev_info *rev, struct patch_ids *ids)
{
	struct rev_info check_rev;
	struct commit *commit;
	struct object *o1, *o2;
	unsigned flags1, flags2;

	if (rev->pending.nr != 2)
		die(_("Need exactly one range."));

	o1 = rev->pending.objects[0].item;
	flags1 = o1->flags;
	o2 = rev->pending.objects[1].item;
	flags2 = o2->flags;

	if ((flags1 & UNINTERESTING) == (flags2 & UNINTERESTING))
		die(_("Not a range."));

	init_patch_ids(ids);

