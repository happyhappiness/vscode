int commit_format_is_empty(enum cmit_fmt fmt)
{
	return fmt == CMIT_FMT_USERFORMAT && !*user_format;
}