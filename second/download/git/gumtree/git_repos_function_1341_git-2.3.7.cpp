const char *get_commit_output_encoding(void)
{
	return git_commit_encoding ? git_commit_encoding : "UTF-8";
}