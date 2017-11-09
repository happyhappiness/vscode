const char *get_log_output_encoding(void)
{
	return git_log_output_encoding ? git_log_output_encoding
		: get_commit_output_encoding();
}