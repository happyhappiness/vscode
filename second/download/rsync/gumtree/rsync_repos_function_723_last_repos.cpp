int main (void)
{
	char buf1[1024];
	char buf2[1024];
	char *buf3;
	char *fp_fmt[] = {
		"%1.1f",
		"%-1.5f",
		"%1.5f",
		"%123.9f",
		"%10.5f",
		"% 10.5f",
		"%+22.9f",
		"%+4.9f",
		"%01.3f",
		"%4f",
		"%3.1f",
		"%3.2f",
		"%.0f",
		"%f",
		"%-8.8f",
		"%-9.9f",
		NULL
	};
	double fp_nums[] = { 6442452944.1234, -1.5, 134.21, 91340.2, 341.1234, 203.9, 0.96, 0.996, 
			     0.9996, 1.996, 4.136, 5.030201, 0.00205,
			     /* END LIST */ 0};
	char *int_fmt[] = {
		"%-1.5d",
		"%1.5d",
		"%123.9d",
		"%5.5d",
		"%10.5d",
		"% 10.5d",
		"%+22.33d",
		"%01.3d",
		"%4d",
		"%d",
		NULL
	};
	long int_nums[] = { -1, 134, 91340, 341, 0203, 1234567890, 0};
	char *str_fmt[] = {
		"%10.5s",
		"%-10.5s",
		"%5.10s",
		"%-5.10s",
		"%10.1s",
		"%0.10s",
		"%10.0s",
		"%1.10s",
		"%s",
		"%.1s",
		"%.10s",
		"%10s",
		NULL
	};
	char *str_vals[] = {"hello", "a", "", "a longer string", NULL};
#ifdef HAVE_LONG_LONG
	char *ll_fmt[] = {
		"%llu",
		NULL
	};
	LLONG ll_nums[] = { 134, 91340, 341, 0203, 1234567890, 128006186140000000LL, 0};
#endif
	int x, y;
	int fail = 0;
	int num = 0;
	int l1, l2;
	char *ss_fmt[] = {
		"%zd",
		"%zu",
		NULL
	};
	size_t ss_nums[] = {134, 91340, 123456789, 0203, 1234567890, 0};

	printf ("Testing snprintf format codes against system sprintf...\n");

	for (x = 0; fp_fmt[x] ; x++) {
		for (y = 0; fp_nums[y] != 0 ; y++) {
			buf1[0] = buf2[0] = '\0';
			l1 = snprintf(buf1, sizeof(buf1), fp_fmt[x], fp_nums[y]);
			l2 = sprintf (buf2, fp_fmt[x], fp_nums[y]);
			buf1[1023] = buf2[1023] = '\0';
			if (strcmp (buf1, buf2) || (l1 != l2)) {
				printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n", 
				       fp_fmt[x], l1, buf1, l2, buf2);
				fail++;
			}
			num++;
		}
	}

	for (x = 0; int_fmt[x] ; x++) {
		for (y = 0; int_nums[y] != 0 ; y++) {
			buf1[0] = buf2[0] = '\0';
			l1 = snprintf(buf1, sizeof(buf1), int_fmt[x], int_nums[y]);
			l2 = sprintf (buf2, int_fmt[x], int_nums[y]);
			buf1[1023] = buf2[1023] = '\0';
			if (strcmp (buf1, buf2) || (l1 != l2)) {
				printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n", 
				       int_fmt[x], l1, buf1, l2, buf2);
				fail++;
			}
			num++;
		}
	}

	for (x = 0; str_fmt[x] ; x++) {
		for (y = 0; str_vals[y] != 0 ; y++) {
			buf1[0] = buf2[0] = '\0';
			l1 = snprintf(buf1, sizeof(buf1), str_fmt[x], str_vals[y]);
			l2 = sprintf (buf2, str_fmt[x], str_vals[y]);
			buf1[1023] = buf2[1023] = '\0';
			if (strcmp (buf1, buf2) || (l1 != l2)) {
				printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n", 
				       str_fmt[x], l1, buf1, l2, buf2);
				fail++;
			}
			num++;
		}
	}

#ifdef HAVE_LONG_LONG
	for (x = 0; ll_fmt[x] ; x++) {
		for (y = 0; ll_nums[y] != 0 ; y++) {
			buf1[0] = buf2[0] = '\0';
			l1 = snprintf(buf1, sizeof(buf1), ll_fmt[x], ll_nums[y]);
			l2 = sprintf (buf2, ll_fmt[x], ll_nums[y]);
			buf1[1023] = buf2[1023] = '\0';
			if (strcmp (buf1, buf2) || (l1 != l2)) {
				printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n", 
				       ll_fmt[x], l1, buf1, l2, buf2);
				fail++;
			}
			num++;
		}
	}
#endif

#define BUFSZ 2048

	buf1[0] = buf2[0] = '\0';
	if ((buf3 = malloc(BUFSZ)) == NULL) {
		fail++;
	} else {
		num++;
		memset(buf3, 'a', BUFSZ);
		snprintf(buf1, sizeof(buf1), "%.*s", 1, buf3);
		buf1[1023] = '\0';
		if (strcmp(buf1, "a") != 0) {
			printf("length limit buf1 '%s' expected 'a'\n", buf1);
			fail++;
		}
        }

	buf1[0] = buf2[0] = '\0';
	l1 = snprintf(buf1, sizeof(buf1), "%4$*1$d %2$s %3$*1$.*1$f", 3, "pos test", 12.3456, 9);
	l2 = sprintf(buf2, "%4$*1$d %2$s %3$*1$.*1$f", 3, "pos test", 12.3456, 9);
	buf1[1023] = buf2[1023] = '\0';
	if (strcmp(buf1, buf2) || (l1 != l2)) {
		printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n",
				"%4$*1$d %2$s %3$*1$.*1$f", l1, buf1, l2, buf2);
		fail++;
	}

	buf1[0] = buf2[0] = '\0';
	l1 = snprintf(buf1, sizeof(buf1), "%4$*4$d %2$s %3$*4$.*4$f", 3, "pos test", 12.3456, 9);
	l2 = sprintf(buf2, "%4$*4$d %2$s %3$*4$.*4$f", 3, "pos test", 12.3456, 9);
	buf1[1023] = buf2[1023] = '\0';
	if (strcmp(buf1, buf2)) {
		printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n",
				"%4$*1$d %2$s %3$*1$.*1$f", l1, buf1, l2, buf2);
		fail++;
	}

	for (x = 0; ss_fmt[x] ; x++) {
		for (y = 0; ss_nums[y] != 0 ; y++) {
			buf1[0] = buf2[0] = '\0';
			l1 = snprintf(buf1, sizeof(buf1), ss_fmt[x], ss_nums[y]);
			l2 = sprintf (buf2, ss_fmt[x], ss_nums[y]);
			buf1[1023] = buf2[1023] = '\0';
			if (strcmp (buf1, buf2) || (l1 != l2)) {
				printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n", 
				       ss_fmt[x], l1, buf1, l2, buf2);
				fail++;
			}
			num++;
		}
	}
#if 0
	buf1[0] = buf2[0] = '\0';
	l1 = snprintf(buf1, sizeof(buf1), "%lld", (LLONG)1234567890);
	l2 = sprintf(buf2, "%lld", (LLONG)1234567890);
	buf1[1023] = buf2[1023] = '\0';
	if (strcmp(buf1, buf2)) {
		printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n",
				"%lld", l1, buf1, l2, buf2);
		fail++;
	}

	buf1[0] = buf2[0] = '\0';
	l1 = snprintf(buf1, sizeof(buf1), "%Lf", (LDOUBLE)890.1234567890123);
	l2 = sprintf(buf2, "%Lf", (LDOUBLE)890.1234567890123);
	buf1[1023] = buf2[1023] = '\0';
	if (strcmp(buf1, buf2)) {
		printf("snprintf doesn't match Format: %s\n\tsnprintf(%d) = [%s]\n\t sprintf(%d) = [%s]\n",
				"%Lf", l1, buf1, l2, buf2);
		fail++;
	}
#endif
	printf ("%d tests failed out of %d.\n", fail, num);

	printf("seeing how many digits we support\n");
	{
		double v0 = 0.12345678901234567890123456789012345678901;
		for (x=0; x<100; x++) {
			double p = pow(10, x); 
			double r = v0*p;
			snprintf(buf1, sizeof(buf1), "%1.1f", r);
			sprintf(buf2,                "%1.1f", r);
			if (strcmp(buf1, buf2)) {
				printf("we seem to support %d digits\n", x-1);
				break;
			}
		}
	}

	return 0;
}