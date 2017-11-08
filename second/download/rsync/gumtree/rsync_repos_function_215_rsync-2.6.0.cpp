void strlower(char *s)
{
	while (*s) {
		if (isupper(* (unsigned char *) s))
			*s = tolower(* (unsigned char *) s);
		s++;
	}
}