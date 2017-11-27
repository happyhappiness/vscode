int getpwnam_r (const char *name, struct passwd *pwbuf, char *buf,
		size_t buflen, struct passwd **pwbufp)
{
	int status = 0;
	struct passwd *pw;

	memset (pwbuf, '\0', sizeof (struct passwd));

	pthread_mutex_lock (&getpwnam_r_lock);

	do
	{
		pw = getpwnam (name);
		if (pw == NULL)
		{
			status = (errno != 0) ? errno : ENOENT;
			break;
		}

#define GETPWNAM_COPY_MEMBER(member) \
		if (pw->member != NULL) \
		{ \
			int len = strlen (pw->member); \
			if (len >= buflen) \
			{ \
				status = ENOMEM; \
				break; \
			} \
			sstrncpy (buf, pw->member, buflen); \
			pwbuf->member = buf; \
			buf    += (len + 1); \
			buflen -= (len + 1); \
		}
		GETPWNAM_COPY_MEMBER(pw_name);
		GETPWNAM_COPY_MEMBER(pw_passwd);
		GETPWNAM_COPY_MEMBER(pw_gecos);
		GETPWNAM_COPY_MEMBER(pw_dir);
		GETPWNAM_COPY_MEMBER(pw_shell);

		pwbuf->pw_uid = pw->pw_uid;
		pwbuf->pw_gid = pw->pw_gid;

		if (pwbufp != NULL)
			*pwbufp = pwbuf;
	} while (0);

	pthread_mutex_unlock (&getpwnam_r_lock);

	return (status);
}