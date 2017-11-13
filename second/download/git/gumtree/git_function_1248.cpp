static void compile_submodule_options(const struct grep_opt *opt,
				      const char **argv,
				      int cached, int untracked,
				      int opt_exclude, int use_index,
				      int pattern_type_arg)
{
	struct grep_pat *pattern;

	if (recurse_submodules)
		argv_array_push(&submodule_options, "--recurse-submodules");

	if (cached)
		argv_array_push(&submodule_options, "--cached");
	if (!use_index)
		argv_array_push(&submodule_options, "--no-index");
	if (untracked)
		argv_array_push(&submodule_options, "--untracked");
	if (opt_exclude > 0)
		argv_array_push(&submodule_options, "--exclude-standard");

	if (opt->invert)
		argv_array_push(&submodule_options, "-v");
	if (opt->ignore_case)
		argv_array_push(&submodule_options, "-i");
	if (opt->word_regexp)
		argv_array_push(&submodule_options, "-w");
	switch (opt->binary) {
	case GREP_BINARY_NOMATCH:
		argv_array_push(&submodule_options, "-I");
		break;
	case GREP_BINARY_TEXT:
		argv_array_push(&submodule_options, "-a");
		break;
	default:
		break;
	}
	if (opt->allow_textconv)
		argv_array_push(&submodule_options, "--textconv");
	if (opt->max_depth != -1)
		argv_array_pushf(&submodule_options, "--max-depth=%d",
				 opt->max_depth);
	if (opt->linenum)
		argv_array_push(&submodule_options, "-n");
	if (!opt->pathname)
		argv_array_push(&submodule_options, "-h");
	if (!opt->relative)
		argv_array_push(&submodule_options, "--full-name");
	if (opt->name_only)
		argv_array_push(&submodule_options, "-l");
	if (opt->unmatch_name_only)
		argv_array_push(&submodule_options, "-L");
	if (opt->null_following_name)
		argv_array_push(&submodule_options, "-z");
	if (opt->count)
		argv_array_push(&submodule_options, "-c");
	if (opt->file_break)
		argv_array_push(&submodule_options, "--break");
	if (opt->heading)
		argv_array_push(&submodule_options, "--heading");
	if (opt->pre_context)
		argv_array_pushf(&submodule_options, "--before-context=%d",
				 opt->pre_context);
	if (opt->post_context)
		argv_array_pushf(&submodule_options, "--after-context=%d",
				 opt->post_context);
	if (opt->funcname)
		argv_array_push(&submodule_options, "-p");
	if (opt->funcbody)
		argv_array_push(&submodule_options, "-W");
	if (opt->all_match)
		argv_array_push(&submodule_options, "--all-match");
	if (opt->debug)
		argv_array_push(&submodule_options, "--debug");
	if (opt->status_only)
		argv_array_push(&submodule_options, "-q");

	switch (pattern_type_arg) {
	case GREP_PATTERN_TYPE_BRE:
		argv_array_push(&submodule_options, "-G");
		break;
	case GREP_PATTERN_TYPE_ERE:
		argv_array_push(&submodule_options, "-E");
		break;
	case GREP_PATTERN_TYPE_FIXED:
		argv_array_push(&submodule_options, "-F");
		break;
	case GREP_PATTERN_TYPE_PCRE:
		argv_array_push(&submodule_options, "-P");
		break;
	case GREP_PATTERN_TYPE_UNSPECIFIED:
		break;
	default:
		die("BUG: Added a new grep pattern type without updating switch statement");
	}

	for (pattern = opt->pattern_list; pattern != NULL;
	     pattern = pattern->next) {
		switch (pattern->token) {
		case GREP_PATTERN:
			argv_array_pushf(&submodule_options, "-e%s",
					 pattern->pattern);
			break;
		case GREP_AND:
		case GREP_OPEN_PAREN:
		case GREP_CLOSE_PAREN:
		case GREP_NOT:
		case GREP_OR:
			argv_array_push(&submodule_options, pattern->pattern);
			break;
		/* BODY and HEAD are not used by git-grep */
		case GREP_PATTERN_BODY:
		case GREP_PATTERN_HEAD:
			break;
		}
	}

	/*
	 * Limit number of threads for child process to use.
	 * This is to prevent potential fork-bomb behavior of git-grep as each
	 * submodule process has its own thread pool.
	 */
	argv_array_pushf(&submodule_options, "--threads=%d",
			 DIV_ROUND_UP(num_threads, 2));

	/* Add Pathspecs */
	argv_array_push(&submodule_options, "--");
	for (; *argv; argv++)
		argv_array_push(&submodule_options, *argv);
}