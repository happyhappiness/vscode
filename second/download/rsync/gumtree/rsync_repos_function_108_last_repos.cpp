static id_t id_parse(const char *num_str)
{
	id_t tmp, num = 0;
	const char *cp = num_str;

	while (*cp) {
		if (!isDigit(cp)) {
		  invalid_num:
			rprintf(FERROR, "Invalid ID number: %s\n", num_str);
			exit_cleanup(RERR_SYNTAX);
		}
		tmp = num * 10 + *cp++ - '0';
		if (tmp < num)
			goto invalid_num;
		num = tmp;
	}

	return num;
}