	rerere(allow_rerere_auto);
	printf(_("Automatic merge failed; "
			"fix conflicts and then commit the result.\n"));
	return 1;
}

static int evaluate_result(void)
{
	int cnt = 0;
	struct rev_info rev;

	/* Check how many files differ. */
