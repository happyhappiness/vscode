static void failed(char const *what, char const *where)
{
	fprintf(stderr, PROGRAM ": %s %s: %s\n",
		what, where, strerror(errno));
	exit(1);
}