static int users_read (void)
{
#if HAVE_GETUTXENT
	unsigned int users = 0;
	struct utmpx *entry = NULL;

	/* according to the *utent(3) man page none of the functions sets errno
	   in case of an error, so we cannot do any error-checking here */
	setutxent();

	while (NULL != (entry = getutxent())) {
		if (USER_PROCESS == entry->ut_type) {
			++users;
		}
	}
	endutxent();

	users_submit (users);
/* #endif HAVE_GETUTXENT */
	
#elif HAVE_GETUTENT
	unsigned int users = 0;
	struct utmp *entry = NULL;

	/* according to the *utent(3) man page none of the functions sets errno
	   in case of an error, so we cannot do any error-checking here */
	setutent();

	while (NULL != (entry = getutent())) {
		if (USER_PROCESS == entry->ut_type) {
			++users;
		}
	}
	endutent();

	users_submit (users);
/* #endif HAVE_GETUTENT */

#elif HAVE_LIBSTATGRAB
	sg_user_stats *us;

	us = sg_get_user_stats ();
	if (us == NULL)
		return (-1);   

	users_submit ((gauge_t) us->num_entries);
/* #endif HAVE_LIBSTATGRAB */

#else
# error "No applicable input method."
#endif

	return (0);
}