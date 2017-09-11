/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

int	buferror(char *buf, size_t buflen);
uintmax_t	malloc_strtoumax(const char *nptr, char **endptr, int base);
void	malloc_write(const char *s);

/*
