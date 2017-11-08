static void env_replace(struct argv_array *env, const char *key, const char *val)
{
	argv_array_pushf(env, "%s=%s", key, val);
}