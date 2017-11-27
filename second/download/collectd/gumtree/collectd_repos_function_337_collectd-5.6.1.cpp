static int zone_read (void)
{
	DIR          *procdir;
	c_avl_tree_t *tree;

	if ((procdir = opendir("/proc")) == NULL) {
		ERROR("zone plugin: cannot open /proc directory\n");
		return (-1);
	}

	tree=zone_scandir(procdir);
	closedir(procdir);
	if (tree == NULL) {
		return (-1);
	}
	zone_submit_values(tree); /* this also frees tree */
	return (0);
}