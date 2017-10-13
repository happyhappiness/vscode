NORETURN void unable_to_lock_index_die(const char *path, int err)
{
	die("%s", unable_to_lock_message(path, err));
}