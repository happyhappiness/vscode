	if (len > (size_t) len)
		die("Cannot handle files this big");
	return (size_t)len;
}

/* in ctype.c, for kwset users */
extern const char tolower_trans_tbl[256];

/* Sane ctype - no locale, and works with signed chars */
#undef isascii
#undef isspace
#undef isdigit
#undef isalpha
