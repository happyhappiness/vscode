static void output_itemized_counts(const char *prefix, int *counts)
{
	static char *labels[] = { "reg", "dir", "link", "dev", "special" };
	char buf[1024], *pre = " (";
	int j, len = 0;
	int total = counts[0];
	if (total) {
		counts[0] -= counts[1] + counts[2] + counts[3] + counts[4];
		for (j = 0; j < 5; j++) {
			if (counts[j]) {
				len += snprintf(buf+len, sizeof buf - len - 2,
					"%s%s: %s",
					pre, labels[j], comma_num(counts[j]));
				pre = ", ";
			}
		}
		buf[len++] = ')';
	}
	buf[len] = '\0';
	rprintf(FINFO, "%s: %s%s\n", prefix, comma_num(total), buf);
}