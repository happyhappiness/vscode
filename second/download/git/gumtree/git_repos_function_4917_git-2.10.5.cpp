static void write_state_bool(const struct am_state *state,
			     const char *name, int value)
{
	write_state_text(state, name, value ? "t" : "f");
}