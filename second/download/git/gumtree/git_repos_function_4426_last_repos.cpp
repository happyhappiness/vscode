void free_refspec(int nr_refspec, struct refspec *refspec)
{
	int i;

	if (!refspec)
		return;

	for (i = 0; i < nr_refspec; i++) {
		free(refspec[i].src);
		free(refspec[i].dst);
	}
	free(refspec);
}