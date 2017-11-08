static void write_state_text(const struct am_state *state,
			     const char *name, const char *string)
{
	write_file(am_path(state, name), "%s", string);
}