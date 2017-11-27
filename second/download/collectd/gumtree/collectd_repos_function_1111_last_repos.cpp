static int nagios_print(char const *buffer) /* {{{ */
{
  char const *file = NAGIOS_COMMAND_FILE;
  int fd;
  int status;
  struct flock lock = {0};

  if (nagios_command_file != NULL)
    file = nagios_command_file;

  fd = open(file, O_WRONLY | O_APPEND);
  if (fd < 0) {
    char errbuf[1024];
    status = errno;
    ERROR("notify_nagios plugin: Opening \"%s\" failed: %s", file,
          sstrerror(status, errbuf, sizeof(errbuf)));
    return status;
  }

  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_END;

  status = fcntl(fd, F_GETLK, &lock);
  if (status != 0) {
    char errbuf[1024];
    status = errno;
    ERROR("notify_nagios plugin: Failed to acquire write lock on \"%s\": %s",
          file, sstrerror(status, errbuf, sizeof(errbuf)));
    close(fd);
    return status;
  }

  status = (int)lseek(fd, 0, SEEK_END);
  if (status == -1) {
    char errbuf[1024];
    status = errno;
    ERROR("notify_nagios plugin: Seeking to end of \"%s\" failed: %s", file,
          sstrerror(status, errbuf, sizeof(errbuf)));
    close(fd);
    return status;
  }

  status = (int)swrite(fd, buffer, strlen(buffer));
  if (status != 0) {
    char errbuf[1024];
    status = errno;
    ERROR("notify_nagios plugin: Writing to \"%s\" failed: %s", file,
          sstrerror(status, errbuf, sizeof(errbuf)));
    close(fd);
    return status;
  }

  close(fd);
  return status;
}