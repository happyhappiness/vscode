		find_alignment(sb, &opt);
		output(sb, opt);
		die("Baa %d!", baa);
	}
}

static unsigned parse_score(const char *arg)
{
	char *end;
	unsigned long score = strtoul(arg, &end, 10);
	if (*end)
		return 0;
