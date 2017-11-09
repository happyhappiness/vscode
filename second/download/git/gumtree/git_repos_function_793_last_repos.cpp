int display_progress(struct progress *progress, unsigned n)
{
	return progress ? display(progress, n, NULL) : 0;
}