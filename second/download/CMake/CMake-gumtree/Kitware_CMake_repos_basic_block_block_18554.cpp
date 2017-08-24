{
  int rc = 0;
  char mon_file_write_string[RDWR_BUF_SIZE];
  char mon_file[PATH_MAX];
  int file_is_directory = 0; /* -1 == NO, 0 == YES  */

  /* Create monitor file name for object */
  file_is_directory = uv__path_is_a_directory((char*)filename);

  if (file_is_directory == 0)
    sprintf(mon_file, "/aha/fs/modDir.monFactory");
  else
    sprintf(mon_file, "/aha/fs/modFile.monFactory");

  if ((strlen(mon_file) + strlen(filename) + 5) > PATH_MAX)
    return -ENAMETOOLONG;

  /* Make the necessary subdirectories for the monitor file */
  rc = uv__make_subdirs_p(filename);
  if (rc == -1 && errno != EEXIST)
    return rc;

  strcat(mon_file, filename);
  strcat(mon_file, ".mon");

  *fd = 0; errno = 0;

  /* Open the monitor file, creating it if necessary */
  *fd = open(mon_file, O_CREAT|O_RDWR);
  if (*fd < 0)
    return -errno;

  /* Write out the monitoring specifications.
   * In this case, we are monitoring for a state change event type
   *    CHANGED=YES
   * We will be waiting in select call, rather than a read:
   *    WAIT_TYPE=WAIT_IN_SELECT
   * We only want minimal information for files:
   *      INFO_LVL=1
   * For directories, we want more information to track what file
   * caused the change
   *      INFO_LVL=2
   */

  if (file_is_directory == 0)
    sprintf(mon_file_write_string, "CHANGED=YES;WAIT_TYPE=WAIT_IN_SELECT;INFO_LVL=2");
  else
    sprintf(mon_file_write_string, "CHANGED=YES;WAIT_TYPE=WAIT_IN_SELECT;INFO_LVL=1");

  rc = write(*fd, mon_file_write_string, strlen(mon_file_write_string)+1);
  if (rc < 0)
    return -errno;

  return 0;
}