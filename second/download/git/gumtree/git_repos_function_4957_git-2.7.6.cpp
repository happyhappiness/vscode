static void find_unresolved_deltas(struct base_data *base)
{
	struct base_data *new_base, *prev_base = NULL;
	for (;;) {
		new_base = find_unresolved_deltas_1(base, prev_base);

		if (new_base) {
			prev_base = base;
			base = new_base;
		} else {
			free(base);
			base = prev_base;
			if (!base)
				return;
			prev_base = base->base;
		}
	}
}