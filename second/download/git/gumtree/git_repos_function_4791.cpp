static int write_state_bool(const struct am_state *state,
			    const char *name, int value)
{
	return write_state_text(state, name, value ? "t" : "f");
}