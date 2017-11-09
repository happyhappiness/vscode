void enable_delayed_checkout(struct checkout *state)
{
	if (!state->delayed_checkout) {
		state->delayed_checkout = xmalloc(sizeof(*state->delayed_checkout));
		state->delayed_checkout->state = CE_CAN_DELAY;
		string_list_init(&state->delayed_checkout->filters, 0);
		string_list_init(&state->delayed_checkout->paths, 0);
	}
}