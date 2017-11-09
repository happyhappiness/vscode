static void remove_test_directory(void)
{
	if (mtime_dir.len)
		remove_dir_recursively(&mtime_dir, 0);
}