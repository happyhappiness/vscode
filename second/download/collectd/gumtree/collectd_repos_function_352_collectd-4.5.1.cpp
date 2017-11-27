char *sstrerror (int errnum, char *buf, size_t buflen)
{
	buf[0] = '\0';

#if !HAVE_STRERROR_R
	{
		char *temp;

		pthread_mutex_lock (&strerror_r_lock);

		temp = strerror (errnum);
		sstrncpy (buf, temp, buflen);

		pthread_mutex_unlock (&strerror_r_lock);
	}
/* #endif !HAVE_STRERROR_R */

#elif STRERROR_R_CHAR_P
	{
		char *temp;
		temp = strerror_r (errnum, buf, buflen);
		if (buf[0] == '\0')
		{
			if ((temp != NULL) && (temp != buf) && (temp[0] != '\0'))
				sstrncpy (buf, temp, buflen);
			else
				sstrncpy (buf, "strerror_r did not return "
						"an error message", buflen);
		}
	}
/* #endif STRERROR_R_CHAR_P */

#else
	if (strerror_r (errnum, buf, buflen) != 0)
	{
		ssnprintf (buf, buflen, "Error #%i; "
				"Additionally, strerror_r failed.",
				errnum);
	}
#endif /* STRERROR_R_CHAR_P */

	return (buf);
}