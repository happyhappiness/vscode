static int version_cmp(const char *a, const char *b)
{
	while (1) {
		int va, vb;

		a = find_digit_prefix(a, &va);
		b = find_digit_prefix(b, &vb);
		if (va != vb)
			return va - vb;

		while (1) {
			int ca = *a;
			int cb = *b;
			if ('0' <= ca && ca <= '9')
				ca = 0;
			if ('0' <= cb && cb <= '9')
				cb = 0;
			if (ca != cb)
				return ca - cb;
			if (!ca)
				break;
			a++;
			b++;
		}
		if (!*a && !*b)
			return 0;
	}
}