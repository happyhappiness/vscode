static REMAILER **mix_type2_list (size_t *l)
{
  FILE *fp;
  pid_t mm_pid;
  int devnull;

  char cmd[HUGE_STRING + _POSIX_PATH_MAX];
  char line[HUGE_STRING];
  char *t;
  
  REMAILER **type2_list = NULL, *p;
  size_t slots = 0, used = 0;

  if (!l)
    return NULL;
  
  if ((devnull = open ("/dev/null", O_RDWR)) == -1)
    return NULL;
  
  snprintf (cmd, sizeof (cmd), "%s -T", Mixmaster);
  
  if ((mm_pid = mutt_create_filter_fd (cmd, NULL, &fp, NULL, devnull, -1, devnull)) == -1)
  {
    close (devnull);
    return NULL;
  }

  /* first, generate the "random" remailer */
  
  p = mix_new_remailer ();
  p->shortname = safe_strdup ("<random>");
  mix_add_entry (&type2_list, p, &slots, &used);
  
  while (fgets (line, sizeof (line), fp))
  {
    p = mix_new_remailer ();
    
    if (!(t = strtok (line, " \t\n")))
      goto problem;
    
    p->shortname = safe_strdup (t);
    
    if (!(t = strtok (NULL, " \t\n")))
      goto problem;

    p->addr = safe_strdup (t);
    
    if (!(t = strtok (NULL, " \t\n")))
      goto problem;

    if (!(t = strtok (NULL, " \t\n")))
      goto problem;

    p->ver = safe_strdup (t);
    
    if (!(t = strtok (NULL, " \t\n")))
      goto problem;

    p->caps = mix_get_caps (t);
    
    mix_add_entry (&type2_list, p, &slots, &used);
    continue;
    
    problem:
    mix_free_remailer (&p);
  }
  
  *l = used;

  mix_add_entry (&type2_list, NULL, &slots, &used);
  mutt_wait_filter (mm_pid);

  close (devnull);
  
  return type2_list;
}