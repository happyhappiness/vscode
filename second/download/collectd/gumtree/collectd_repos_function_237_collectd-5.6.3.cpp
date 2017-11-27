static void exec_child(program_list_t *pl, int uid,
                                                 int gid, int egid) /* {{{ */
{
  int status;
  char errbuf[1024];

#if HAVE_SETGROUPS
  if (getuid() == 0) {
    gid_t glist[2];
    size_t glist_len;

    glist[0] = gid;
    glist_len = 1;

    if ((gid != egid) && (egid != -1)) {
      glist[1] = egid;
      glist_len = 2;
    }

    setgroups(glist_len, glist);
  }
#endif /* HAVE_SETGROUPS */

  status = setgid(gid);
  if (status != 0) {
    ERROR("exec plugin: setgid (%i) failed: %s", gid,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    exit(-1);
  }

  if (egid != -1) {
    status = setegid(egid);
    if (status != 0) {
      ERROR("exec plugin: setegid (%i) failed: %s", egid,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      exit(-1);
    }
  }

  status = setuid(uid);
  if (status != 0) {
    ERROR("exec plugin: setuid (%i) failed: %s", uid,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    exit(-1);
  }

  execvp(pl->exec, pl->argv);

  ERROR("exec plugin: Failed to execute ``%s'': %s", pl->exec,
        sstrerror(errno, errbuf, sizeof(errbuf)));
  exit(-1);
}