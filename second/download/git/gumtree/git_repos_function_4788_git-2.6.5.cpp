static inline const char *am_path(const struct am_state *state, const char *path)
{
	return mkpath("%s/%s", state->dir, path);
}