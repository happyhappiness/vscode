static void compile_submodule_options(const struct dir_struct *dir, int show_tag)
{
	if (line_terminator == '\0')
		argv_array_push(&submodules_options, "-z");
	if (show_tag)
		argv_array_push(&submodules_options, "-t");
	if (show_valid_bit)
		argv_array_push(&submodules_options, "-v");
	if (show_cached)
		argv_array_push(&submodules_options, "--cached");
	if (show_eol)
		argv_array_push(&submodules_options, "--eol");
	if (debug_mode)
		argv_array_push(&submodules_options, "--debug");
}