static void list_common_guides_help(void)
{
	int i, longest = 0;

	for (i = 0; i < ARRAY_SIZE(common_guides); i++) {
		if (longest < strlen(common_guides[i].name))
			longest = strlen(common_guides[i].name);
	}

	puts(_("The common Git guides are:\n"));
	for (i = 0; i < ARRAY_SIZE(common_guides); i++) {
		printf("   %s   ", common_guides[i].name);
		mput_char(' ', longest - strlen(common_guides[i].name));
		puts(_(common_guides[i].help));
	}
	putchar('\n');
}