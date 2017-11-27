static void md_process (const int minor, const char *path)
{
  char errbuf[1024];
  int fd;
  struct stat st;
  mdu_array_info_t array;
  gauge_t disks_missing;

  fd = open (path, O_RDONLY);
  if (fd < 0)
  {
    WARNING ("md: open(%s): %s", path,
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return;
  }

  if (fstat (fd, &st) < 0)
  {
    WARNING ("md: Unable to fstat file descriptor for %s: %s", path,
        sstrerror (errno, errbuf, sizeof (errbuf)));
    close (fd);
    return;
  }

  if (! S_ISBLK (st.st_mode))
  {
    WARNING ("md: %s is no block device", path);
    close (fd);
    return;
  }

  if (st.st_rdev != makedev (MD_MAJOR, minor))
  {
    WARNING ("md: Major/minor of %s are %i:%i, should be %i:%i",
        path, (int)major(st.st_rdev), (int)minor(st.st_rdev),
        (int)MD_MAJOR, minor);
    close (fd);
    return;
  }

  /* Retrieve md information */
  if (ioctl (fd, GET_ARRAY_INFO, &array) < 0) {
    WARNING ("md: Unable to retrieve array info from %s: %s", path,
        sstrerror (errno, errbuf, sizeof (errbuf)));
    close (fd);
    return;
  }

  close (fd);

  /*
   * The mdu_array_info_t structure contains numbers of disks in the array.
   * However, disks are accounted for more than once:
   *
   * active:  Number of active (in sync) disks.
   * spare:   Number of stand-by disks.
   * working: Number of working disks. (active + sync)
   * failed:  Number of failed disks.
   * nr:      Number of physically present disks. (working + failed)
   * raid:    Number of disks in the RAID. This may be larger than "nr" if
   *          disks are missing and smaller than "nr" when spare disks are
   *          around.
   */
  md_submit (minor, "active",  (gauge_t) array.active_disks);
  md_submit (minor, "failed",  (gauge_t) array.failed_disks);
  md_submit (minor, "spare",   (gauge_t) array.spare_disks);

  disks_missing = 0.0;
  if (array.raid_disks > array.nr_disks)
    disks_missing = (gauge_t) (array.raid_disks - array.nr_disks);
  md_submit (minor, "missing", disks_missing);
}