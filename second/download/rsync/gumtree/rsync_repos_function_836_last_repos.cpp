static int doliteral(const uchar *s, const uchar *text, const uchar*const *a)
{
    for ( ; *s != '\0'; text++, s++) {
	while (*text == '\0') {
	    if ((text = *a++) == NULL)
		return FALSE;
	}
	if (*text != *s)
	    return FALSE;
    }

    do {
	if (*text)
	    return FALSE;
    } while ((text = *a++) != NULL);

    return TRUE;
}