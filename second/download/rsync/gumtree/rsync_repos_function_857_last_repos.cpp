int main(int argc, char *argv[])
{
	FILE *f;
	int i, j;
	char output[33];
	md_context ctx;
	uchar buf[1000];
	uchar md5sum[MD5_DIGEST_LEN];

	if (argc < 2) {
		printf("\nMD5 Validation Tests:\n\n");

		for (i = 0; tests[i].str; i++) {
			char *str = tests[i].str;
			char *chk = tests[i].md5;

			printf("  Test %d ", i + 1);

			get_md5(md5sum, str, strlen(str));

			for (j = 0; j < MD5_DIGEST_LEN; j++)
				sprintf(output + j * 2, "%02x", md5sum[j]);

			if (memcmp(output, chk, 32)) {
				printf("failed!\n");
				return 1;
			}

			printf("passed.\n");
		}

		printf("\n");
		return 0;
	}

	while (--argc) {
		if (!(f = fopen(*++argv, "rb"))) {
			perror("fopen");
			return 1;
		}

		md5_begin(&ctx);

		while ((i = fread(buf, 1, sizeof buf, f)) > 0)
			md5_update(&ctx, buf, i);

		md5_result(&ctx, md5sum);

		for (j = 0; j < MD5_DIGEST_LEN; j++)
			printf("%02x", md5sum[j]);

		printf("  %s\n", *argv);
	}

	return 0;
}