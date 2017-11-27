char *ssnprintf_alloc (char const *format, ...) /* {{{ */
{
	char static_buffer[1024] = "";
	char *alloc_buffer;
	size_t alloc_buffer_size;
	int status;
	va_list ap;

	/* Try printing into the static buffer. In many cases it will be
	 * sufficiently large and we can simply return a strdup() of this
	 * buffer. */
	va_start (ap, format);
	status = vsnprintf (static_buffer, sizeof (static_buffer), format, ap);
	va_end (ap);
	if (status < 0)
		return (NULL);

	/* "status" does not include the null byte. */
	alloc_buffer_size = (size_t) (status + 1);
	if (alloc_buffer_size <= sizeof (static_buffer))
		return (strdup (static_buffer));

	/* Allocate a buffer large enough to hold the string. */
	alloc_buffer = malloc (alloc_buffer_size);
	if (alloc_buffer == NULL)
		return (NULL);
	memset (alloc_buffer, 0, alloc_buffer_size);

	/* Print again into this new buffer. */
	va_start (ap, format);
	status = vsnprintf (alloc_buffer, alloc_buffer_size, format, ap);
	va_end (ap);
	if (status < 0)
	{
		sfree (alloc_buffer);
		return (NULL);
	}

	return (alloc_buffer);
}