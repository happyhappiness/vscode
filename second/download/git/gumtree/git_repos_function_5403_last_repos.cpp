static void write_state_count(const struct am_state *state,
			      const char *name, int value)
{
	write_file(am_path(state, name), "%d", value);
}