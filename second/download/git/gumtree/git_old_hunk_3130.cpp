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

