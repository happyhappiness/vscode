static void file_checksum1(char *fname)
{
	int fd, i, was_multiple_of_64 = 1;
	struct mdfour md;
	unsigned char buf[64*1024], sum[16];
	
	fd = open(fname,O_RDONLY);
	if (fd == -1) {
		perror("fname");
		exit(1);
	}
	
	mdfour_begin(&md);

	while (1) {
		int n = read(fd, buf, sizeof(buf));
		if (n <= 0)
			break;
		was_multiple_of_64 = !(n % 64);
		mdfour_update(&md, buf, n);
	}
	if (was_multiple_of_64 && protocol_version >= 27)
		mdfour_update(&md, buf, 0);

	close(fd);

	mdfour_result(&md, sum);

	for (i=0;i<16;i++)
		printf("%02X", sum[i]);
	printf("\n");
}