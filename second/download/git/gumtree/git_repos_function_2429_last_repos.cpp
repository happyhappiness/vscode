const char **prepare_git_cmd(struct argv_array *out, const char **argv)
{
	argv_array_push(out, "git");
	argv_array_pushv(out, argv);
	return out->argv;
}