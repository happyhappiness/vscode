static int md_read (void)
{
  FILE *fh;
  char buffer[1024];

  fh = fopen (PROC_DISKSTATS, "r");
  if (fh == NULL) {
    char errbuf[1024];
    WARNING ("md: Unable to open %s: %s",
        PROC_DISKSTATS ,
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  /* Iterate md devices */
  while (fgets (buffer, sizeof (buffer), fh) != NULL)
  {
    char path[PATH_MAX];
    char *fields[4];
    char *name;
    int major, minor;

    /* Extract interesting fields */
    if (strsplit (buffer, fields, STATIC_ARRAY_SIZE(fields)) < 3)
      continue;

    major = atoi (fields[0]);

    if (major != MD_MAJOR)
      continue;

    minor = atoi (fields[1]);
    name = fields[2];

    if (ignorelist_match (ignorelist, name))
      continue;

    /* FIXME: Don't hardcode path. Walk /dev collecting major,
     * minor and name, then use lookup table to find device.
     * Alternatively create a temporary device file with correct
     * major/minor, but that again can be tricky if the filesystem
     * with the device file is mounted using the "nodev" option.
     */
    ssnprintf (path, sizeof (path), "%s/%s", DEV_DIR, name);

    md_process (minor, path);
  }

  fclose (fh);

  return (0);
}