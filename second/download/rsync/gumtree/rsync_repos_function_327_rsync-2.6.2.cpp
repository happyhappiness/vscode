static void set_refuse_options(char *bp)
{
	struct poptOption *op;
	char *cp;

	while (1) {
		if ((cp = strchr(bp, ' ')) != NULL)
			*cp= '\0';
		for (op = long_options; ; op++) {
			if (!op->longName) {
				rprintf(FLOG,
				    "Unknown option %s in \"refuse options\" setting\n",
				    bp);
				break;
			}
			if (strcmp(bp, op->longName) == 0) {
				op->val = (op - long_options)+OPT_REFUSED_BASE;
				break;
			}
		}
		if (!cp)
			break;
		*cp = ' ';
		bp = cp + 1;
	}
}