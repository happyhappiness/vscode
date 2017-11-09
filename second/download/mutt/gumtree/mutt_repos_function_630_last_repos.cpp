int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s symbol <textfile >textfile.c\n", argv[0]);
		return 2;
	}

	txt2c(argv[1], stdin);
	return 0;
}