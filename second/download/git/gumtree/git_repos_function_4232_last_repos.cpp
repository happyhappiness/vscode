static int should_queue_directories(const struct archiver_args *args)
{
	return args->pathspec.has_wildcard;
}