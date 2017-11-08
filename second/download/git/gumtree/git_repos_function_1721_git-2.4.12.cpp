static void bootstrap_attr_stack(void)
{
	struct attr_stack *elem;

	if (attr_stack)
		return;

	elem = read_attr_from_array(builtin_attr);
	elem->origin = NULL;
	elem->prev = attr_stack;
	attr_stack = elem;

	if (git_attr_system()) {
		elem = read_attr_from_file(git_etc_gitattributes(), 1);
		if (elem) {
			elem->origin = NULL;
			elem->prev = attr_stack;
			attr_stack = elem;
		}
	}

	if (!git_attributes_file)
		git_attributes_file = xdg_config_home("attributes");
	if (git_attributes_file) {
		elem = read_attr_from_file(git_attributes_file, 1);
		if (elem) {
			elem->origin = NULL;
			elem->prev = attr_stack;
			attr_stack = elem;
		}
	}

	if (!is_bare_repository() || direction == GIT_ATTR_INDEX) {
		elem = read_attr(GITATTRIBUTES_FILE, 1);
		elem->origin = xstrdup("");
		elem->originlen = 0;
		elem->prev = attr_stack;
		attr_stack = elem;
		debug_push(elem);
	}

	elem = read_attr_from_file(git_path(INFOATTRIBUTES_FILE), 1);
	if (!elem)
		elem = xcalloc(1, sizeof(*elem));
	elem->origin = NULL;
	elem->prev = attr_stack;
	attr_stack = elem;
}