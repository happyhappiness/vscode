static const uchar *trailing_N_elements(const uchar*const **a_ptr, int count)
{
    const uchar*const *a = *a_ptr;
    const uchar*const *first_a = a;

    while (*a)
	    a++;

    while (a != first_a) {
	const uchar *s = *--a;
	s += strlen((char*)s);
	while (--s >= *a) {
	    if (*s == '/' && !--count) {
		*a_ptr = a+1;
		return s+1;
	    }
	}
    }

    if (count == 1) {
	*a_ptr = a+1;
	return *a;
    }

    return NULL;
}