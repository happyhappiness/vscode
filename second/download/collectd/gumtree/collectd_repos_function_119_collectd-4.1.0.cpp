static void exec_child (program_list_t *pl)
{
  int status;
  int uid;
  int gid;
  char *arg0;

  struct passwd *sp_ptr;
  struct passwd sp;
  char nambuf[2048];
  char errbuf[1024];

  sp_ptr = NULL;
  status = getpwnam_r (pl->user, &sp, nambuf, sizeof (nambuf), &sp_ptr);
  if (status != 0)
  {
    ERROR ("exec plugin: getpwnam_r failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    exit (-1);
  }
  if (sp_ptr == NULL)
  {
    ERROR ("exec plugin: No such user: `%s'", pl->user);
    exit (-1);
  }

  uid = sp.pw_uid;
  if (uid == 0)
  {
    ERROR ("exec plugin: Cowardly refusing to exec program as root.");
    exit (-1);
  }

  status = setuid (uid);
  if (status != 0)
  {
    ERROR ("exec plugin: setuid failed: %s",
	sstrerror (errno, errbuf, sizeof (errbuf)));
    exit (-1);
  }

  if (NULL != pl->group)
  {
    if ('\0' != *pl->group) {
      struct group *gr_ptr = NULL;
      struct group gr;

      status = getgrnam_r (pl->group, &gr, nambuf, sizeof (nambuf), &gr_ptr);
      if (0 != status)
      {
	ERROR ("exec plugin: getgrnam_r failed: %s",
	    sstrerror (errno, errbuf, sizeof (errbuf)));
	exit (-1);
      }
      if (NULL == gr_ptr)
      {
	ERROR ("exec plugin: No such group: `%s'", pl->group);
	exit (-1);
      }

      gid = gr.gr_gid;
    }
    else
    {
      gid = sp.pw_gid;
    }

    status = setgid (gid);
    if (0 != status)
    {
      ERROR ("exec plugin: setgid failed: %s",
	  sstrerror (errno, errbuf, sizeof (errbuf)));
      exit (-1);
    }
  }

  arg0 = strrchr (pl->exec, '/');
  if (arg0 != NULL)
    arg0++;
  if ((arg0 == NULL) || (*arg0 == '\0'))
    arg0 = pl->exec;

  status = execlp (pl->exec, arg0, (char *) 0);

  ERROR ("exec plugin: exec failed: %s",
      sstrerror (errno, errbuf, sizeof (errbuf)));
  exit (-1);
}