int main(int argc, char *argv[])
{
	while (--argc)
		file_checksum1(*++argv);
	return 0;
}