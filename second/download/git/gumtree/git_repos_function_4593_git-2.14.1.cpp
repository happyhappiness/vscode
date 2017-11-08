static int has_non_crud(const char *str)
{
	for (; *str; str++) {
		if (!crud(*str))
			return 1;
	}
	return 0;
}