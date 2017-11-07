static int
dotlock_init_privs (void)
{

# ifdef USE_SETGID
  
  UserGid = getgid ();
  MailGid = getegid ();

  if (SETEGID (UserGid) != 0)
    return -1;

# endif

  return 0;
}