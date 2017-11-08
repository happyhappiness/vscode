static void hard_link_one(char *hlink1, char *hlink2)
{
	if (do_link(hlink1, hlink2)) {
		if (verbose) {
			rprintf(FINFO, "link %s => %s failed: %s\n",
			    hlink2, hlink1, strerror(errno));
		}
	}
	else if (verbose)
		rprintf(FINFO, "%s => %s\n", hlink2, hlink1);
}