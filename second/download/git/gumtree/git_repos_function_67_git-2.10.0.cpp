void list_common_cmds_help(void)
{
	int i, longest = 0;
	int current_grp = -1;

	for (i = 0; i < ARRAY_SIZE(common_cmds); i++) {
		if (longest < strlen(common_cmds[i].name))
			longest = strlen(common_cmds[i].name);
	}

	qsort(common_cmds, ARRAY_SIZE(common_cmds),
		sizeof(common_cmds[0]), cmd_group_cmp);

	puts(_("These are common Git commands used in various situations:"));

	for (i = 0; i < ARRAY_SIZE(common_cmds); i++) {
		if (common_cmds[i].group != current_grp) {
			printf("\n%s\n", _(common_cmd_groups[common_cmds[i].group]));
			current_grp = common_cmds[i].group;
		}

		printf("   %s   ", common_cmds[i].name);
		mput_char(' ', longest - strlen(common_cmds[i].name));
		puts(_(common_cmds[i].help));
	}
}