static struct object_entry **compute_write_order(void)
{
	unsigned int i, wo_end, last_untagged;

	struct object_entry **wo;
	struct object_entry *objects = to_pack.objects;

	for (i = 0; i < to_pack.nr_objects; i++) {
		objects[i].tagged = 0;
		objects[i].filled = 0;
		objects[i].delta_child = NULL;
		objects[i].delta_sibling = NULL;
	}

	/*
	 * Fully connect delta_child/delta_sibling network.
	 * Make sure delta_sibling is sorted in the original
	 * recency order.
	 */
	for (i = to_pack.nr_objects; i > 0;) {
		struct object_entry *e = &objects[--i];
		if (!e->delta)
			continue;
		/* Mark me as the first child */
		e->delta_sibling = e->delta->delta_child;
		e->delta->delta_child = e;
	}

	/*
	 * Mark objects that are at the tip of tags.
	 */
	for_each_tag_ref(mark_tagged, NULL);

	/*
	 * Give the objects in the original recency order until
	 * we see a tagged tip.
	 */
	ALLOC_ARRAY(wo, to_pack.nr_objects);
	for (i = wo_end = 0; i < to_pack.nr_objects; i++) {
		if (objects[i].tagged)
			break;
		add_to_write_order(wo, &wo_end, &objects[i]);
	}
	last_untagged = i;

	/*
	 * Then fill all the tagged tips.
	 */
	for (; i < to_pack.nr_objects; i++) {
		if (objects[i].tagged)
			add_to_write_order(wo, &wo_end, &objects[i]);
	}

	/*
	 * And then all remaining commits and tags.
	 */
	for (i = last_untagged; i < to_pack.nr_objects; i++) {
		if (objects[i].type != OBJ_COMMIT &&
		    objects[i].type != OBJ_TAG)
			continue;
		add_to_write_order(wo, &wo_end, &objects[i]);
	}

	/*
	 * And then all the trees.
	 */
	for (i = last_untagged; i < to_pack.nr_objects; i++) {
		if (objects[i].type != OBJ_TREE)
			continue;
		add_to_write_order(wo, &wo_end, &objects[i]);
	}

	/*
	 * Finally all the rest in really tight order
	 */
	for (i = last_untagged; i < to_pack.nr_objects; i++) {
		if (!objects[i].filled)
			add_family_to_write_order(wo, &wo_end, &objects[i]);
	}

	if (wo_end != to_pack.nr_objects)
		die("ordered %u objects, expected %"PRIu32, wo_end, to_pack.nr_objects);

	return wo;
}