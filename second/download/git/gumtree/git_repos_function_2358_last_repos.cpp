void bootstrap_attr_stack(struct attr_stack **stack)
{
	struct attr_stack *e;

	if (*stack)
		return;

	/* builtin frame */
	e = read_attr_from_array(builtin_attr);
	push_stack(stack, e, NULL, 0);

	/* system-wide frame */
	if (git_attr_system()) {
		e = read_attr_from_file(git_etc_gitattributes(), 1);
		push_stack(stack, e, NULL, 0);
	}

	/* home directory */
	if (get_home_gitattributes()) {
		e = read_attr_from_file(get_home_gitattributes(), 1);
		push_stack(stack, e, NULL, 0);
	}

	/* root directory */
	e = read_attr(GITATTRIBUTES_FILE, 1);
	push_stack(stack, e, xstrdup(""), 0);

	/* info frame */
	if (startup_info->have_repository)
		e = read_attr_from_file(git_path_info_attributes(), 1);
	else
		e = NULL;
	if (!e)
		e = xcalloc(1, sizeof(struct attr_stack));
	push_stack(stack, e, NULL, 0);
}