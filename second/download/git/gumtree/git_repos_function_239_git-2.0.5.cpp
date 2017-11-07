void walker_say(struct walker *walker, const char *fmt, const char *hex)
{
	if (walker->get_verbosely)
		fprintf(stderr, fmt, hex);
}