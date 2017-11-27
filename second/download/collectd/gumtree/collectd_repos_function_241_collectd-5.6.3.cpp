static int fork_child(program_list_t *pl, int *fd_in, int *fd_out,
                      int *fd_err) /* {{{ */
{
  int fd_pipe_in[2] = {-1, -1};
  int fd_pipe_out[2] = {-1, -1};
  int fd_pipe_err[2] = {-1, -1};
  char errbuf[1024];
  int status;
  int pid;

  int uid;
  int gid;
  int egid;

  struct passwd *sp_ptr;
  struct passwd sp;

  if (pl->pid != 0)
    return (-1);

  long int nambuf_size = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (nambuf_size <= 0)
    nambuf_size = sysconf(_SC_PAGESIZE);
  if (nambuf_size <= 0)
    nambuf_size = 4096;
  char nambuf[nambuf_size];

  if ((create_pipe(fd_pipe_in) == -1) || (create_pipe(fd_pipe_out) == -1) ||
      (create_pipe(fd_pipe_err) == -1))
    goto failed;

  sp_ptr = NULL;
  status = getpwnam_r(pl->user, &sp, nambuf, sizeof(nambuf), &sp_ptr);
  if (status != 0) {
    ERROR("exec plugin: Failed to get user information for user ``%s'': %s",
          pl->user, sstrerror(status, errbuf, sizeof(errbuf)));
    goto failed;
  }

  if (sp_ptr == NULL) {
    ERROR("exec plugin: No such user: `%s'", pl->user);
    goto failed;
  }

  uid = sp.pw_uid;
  gid = sp.pw_gid;
  if (uid == 0) {
    ERROR("exec plugin: Cowardly refusing to exec program as root.");
    goto failed;
  }

  /* The group configured in the configfile is set as effective group, because
   * this way the forked process can (re-)gain the user's primary group. */
  egid = -1;
  if (NULL != pl->group) {
    if ('\0' != *pl->group) {
      struct group *gr_ptr = NULL;
      struct group gr;

      long int grbuf_size = sysconf(_SC_GETGR_R_SIZE_MAX);
      if (grbuf_size <= 0)
        grbuf_size = sysconf(_SC_PAGESIZE);
      if (grbuf_size <= 0)
        grbuf_size = 4096;
      char grbuf[grbuf_size];

      status = getgrnam_r(pl->group, &gr, grbuf, sizeof(grbuf), &gr_ptr);
      if (0 != status) {
        ERROR("exec plugin: Failed to get group information "
              "for group ``%s'': %s",
              pl->group, sstrerror(status, errbuf, sizeof(errbuf)));
        goto failed;
      }
      if (NULL == gr_ptr) {
        ERROR("exec plugin: No such group: `%s'", pl->group);
        goto failed;
      }

      egid = gr.gr_gid;
    } else {
      egid = gid;
    }
  } /* if (pl->group == NULL) */

  pid = fork();
  if (pid < 0) {
    ERROR("exec plugin: fork failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    goto failed;
  } else if (pid == 0) {
    int fd_num;

    /* Close all file descriptors but the pipe end we need. */
    fd_num = getdtablesize();
    for (int fd = 0; fd < fd_num; fd++) {
      if ((fd == fd_pipe_in[0]) || (fd == fd_pipe_out[1]) ||
          (fd == fd_pipe_err[1]))
        continue;
      close(fd);
    }

    /* Connect the `in' pipe to STDIN */
    if (fd_pipe_in[0] != STDIN_FILENO) {
      dup2(fd_pipe_in[0], STDIN_FILENO);
      close(fd_pipe_in[0]);
    }

    /* Now connect the `out' pipe to STDOUT */
    if (fd_pipe_out[1] != STDOUT_FILENO) {
      dup2(fd_pipe_out[1], STDOUT_FILENO);
      close(fd_pipe_out[1]);
    }

    /* Now connect the `err' pipe to STDERR */
    if (fd_pipe_err[1] != STDERR_FILENO) {
      dup2(fd_pipe_err[1], STDERR_FILENO);
      close(fd_pipe_err[1]);
    }

    set_environment();

    /* Unblock all signals */
    reset_signal_mask();

    exec_child(pl, uid, gid, egid);
    /* does not return */
  }

  close(fd_pipe_in[0]);
  close(fd_pipe_out[1]);
  close(fd_pipe_err[1]);

  if (fd_in != NULL)
    *fd_in = fd_pipe_in[1];
  else
    close(fd_pipe_in[1]);

  if (fd_out != NULL)
    *fd_out = fd_pipe_out[0];
  else
    close(fd_pipe_out[0]);

  if (fd_err != NULL)
    *fd_err = fd_pipe_err[0];
  else
    close(fd_pipe_err[0]);

  return (pid);

failed:
  close_pipe(fd_pipe_in);
  close_pipe(fd_pipe_out);
  close_pipe(fd_pipe_err);

  return (-1);
}