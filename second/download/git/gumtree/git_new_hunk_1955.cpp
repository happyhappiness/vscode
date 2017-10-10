				putchar('.');
		}
	} else
		fputs(topath[checkout_stage], stdout);

	putchar('\t');
	write_name_quoted_relative(name, prefix, stdout, line_termination);

	for (i = 0; i < 4; i++) {
		topath[i][0] = 0;
	}
}

static int checkout_file(const char *name, const char *prefix)
{
	int namelen = strlen(name);
	int pos = cache_name_pos(name, namelen);
	int has_same_name = 0;
	int did_checkout = 0;
	int errs = 0;
