static void numstat_patch_list(struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		const char *name;
		name = patch->new_name ? patch->new_name : patch->old_name;
		if (patch->is_binary)
			printf("-\t-\t");
		else
			printf("%d\t%d\t", patch->lines_added, patch->lines_deleted);
		write_name_quoted(name, stdout, line_termination);
	}
}