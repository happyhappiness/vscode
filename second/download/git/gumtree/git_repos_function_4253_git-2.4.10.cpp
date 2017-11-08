static void emit(const char *cp, const char *ep)
{
	while (*cp && (!ep || cp < ep)) {
		if (*cp == '%') {
			if (cp[1] == '%')
				cp++;
			else {
				int ch = hex2(cp + 1);
				if (0 <= ch) {
					putchar(ch);
					cp += 3;
					continue;
				}
			}
		}
		putchar(*cp);
		cp++;
	}
}