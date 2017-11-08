static void compile_submodule_options(const char **argv,
				      const struct dir_struct *dir,
				      int show_tag)
{
	if (line_terminator == '\0')
		argv_array_push(&submodule_options, "-z");
	if (show_tag)
		argv_array_push(&submodule_options, "-t");
	if (show_valid_bit)
		argv_array_push(&submodule_options, "-v");
	if (show_cached)
		argv_array_push(&submodule_options, "--cached");
	if (show_eol)
		argv_array_push(&submodule_options, "--eol");
	if (debug_mode)
		argv_array_push(&submodule_options, "--debug");

	/* Add Pathspecs */
	argv_array_push(&submodule_options, "--");
	for (; *argv; argv++)
		argv_array_push(&submodule_options, *argv);
}