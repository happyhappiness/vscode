{
	if (tree_current_is_physical_link(t))
		return (0);
	return (tree_current_is_dir(t));
}