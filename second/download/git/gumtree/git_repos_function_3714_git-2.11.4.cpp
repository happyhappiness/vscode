const char **tmp_objdir_env(const struct tmp_objdir *t)
{
	if (!t)
		return NULL;
	return t->env.argv;
}