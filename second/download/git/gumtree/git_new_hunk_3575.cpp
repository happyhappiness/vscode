	return mkpath("%s/%s", state->dir, path);
}

/**
 * For convenience to call write_file()
 */
static void write_state_text(const struct am_state *state,
			     const char *name, const char *string)
{
	write_file(am_path(state, name), "%s", string);
}

static void write_state_count(const struct am_state *state,
			      const char *name, int value)
{
	write_file(am_path(state, name), "%d", value);
}

static void write_state_bool(const struct am_state *state,
			     const char *name, int value)
{
	write_state_text(state, name, value ? "t" : "f");
}

/**
 * If state->quiet is false, calls fprintf(fp, fmt, ...), and appends a newline
 * at the end.
 */
