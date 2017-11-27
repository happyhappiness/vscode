static void exec_child (program_list_t *pl) /* {{{ */
{
  int status;
  int uid;
  int gid;
  int egid;

  struct passwd *sp_ptr;
  struct passwd sp;
  char nambuf[2048];
  char errbuf[1024];

  sp_ptr = NULL;
  status = getpwnam_r (pl->user, &sp, nambuf, sizeof (nambuf), &sp_ptr);
  if (status != 0)
  {
    ERROR ("exec plugin: Failed to get user information for user ``%s'': %s",
	pl->user, sstrerror (errno, errbuf, sizeof (errbuf)));
    exit (-1);
  }
  if (sp_ptr == NULL)
  {
    ERROR ("exec plugin: No such user: `%s'", pl->user);
    exit (-1);
  }

  uid = sp.pw_uid;
  gid = sp.pw_gid;
  if (uid == 0)
  {
    ERROR ("exec plugin: Cowardly refusing to exec program as root.");
    exit (-1);
  }

  /* The group configured in the configfile is set as effective group, because
   * this way the forked process can (re-)gain the user's primary group. */
  egid = -1;
  if (NULL != pl->group)
  {
    if ('\0' != *pl->group) {
      struct group *gr_ptr = NULL;
      struct group gr;

      status = getgrnam_r (pl->group, &gr, nambuf, sizeof (nambuf), &gr_ptr);
      if (0 != status)
      {
	ERROR ("exec plugin: Failed to get group information "
	    "for group ``%s'': %s", pl->group,
	    sstrerror (errno, errbuf, sizeof (errbuf)));
	exit (-1);
      }
      if (NULL == gr_ptr)
      {
	ERROR ("exec plugin: No such group: `%s'", pl->group);
	exit (-1);
      }

      egid = gr.gr_gid;
    }
    else
    {
      egid = gid;
    }
  } /* if (pl->group == NULL) */

#if HAVE_SETGROUPS
  if (getuid () == 0)
  {
    gid_t  glist[2];
    size_t glist_len;

    glist[0] = gid;
    glist_len = 1;

    if ((gid != egid) && (egid != -1))
    {
      glist[1] = egid;
      glist_len = 2;
    }

    setgroups (glist_len, glist);
  }
#endif /* HAVE_SETGROUPS */

  status = setgid (gid);
  if (status != 0)
  {
    ERROR ("exec plugin: setgid (%i) failed: %s",
	gid, sstrerror (errno, errbuf, sizeof (errbuf)));
    exit (-1);
  }

  if (egid != -1)
  {
    status = setegid (egid);
    if (status != 0)
    {
      ERROR ("exec plugin: setegid (%i) failed: %s",
	  egid, sstrerror (errno, errbuf, sizeof (errbuf)));
      exit (-1);
    }
  }

  status = setuid (uid);
  if (status != 0)
  {
    ERROR ("exec plugin: setuid (%i) failed: %s",
	uid, sstrerror (errno, errbuf, sizeof (errbuf)));
    exit (-1);
  }

  status = execvp (pl->exec, pl->argv);

  ERROR ("exec plugin: Failed to execute ``%s'': %s",
      pl->exec, sstrerror (errno, errbuf, sizeof (errbuf)));
  exit (-1);
}