 *      because 16-bit word addressed copies were faster?)  Anyhow, it should

 *      have been ripped out long ago.

 */

static int copy_ar(CF* cfp, off_t size)

{

  static char pad = '\n';

  off_t sz = size;

  size_t nr, nw;

  char buf[8 * 1024];



  if (sz == 0)

    return 0;



  FILE* from = cfp->rFile;

  FILE* to = cfp->wFile;

  while (sz &&

         (nr = fread(buf, 1, sz < static_cast<off_t>(sizeof(buf))

                       ? static_cast<size_t>(sz)

                       : sizeof(buf),

                     from)) > 0) {

    sz -= nr;

    for (size_t off = 0; off < nr; nr -= off, off += nw)

      if ((nw = fwrite(buf + off, 1, nr, to)) < nr)

        return -1;

  }

  if (sz)

    return -2;



  if (cfp->flags & WPAD && (size + ar_already_written) & 1 &&

      fwrite(&pad, 1, 1, to) != 1)

    return -4;



  return 0;

}



/* put_arobj --  Write an archive member to a file. */

static int put_arobj(CF* cfp, struct stat* sb)

{

  int result = 0;

  struct ar_hdr* hdr;



  /* If passed an sb structure, reading a file from disk.  Get stat(2)

   * information, build a name and construct a header.  (Files are named

   * by their last component in the archive.) */

  const char* name = ar_rname(cfp->rname);

  (void)stat(cfp->rname, sb);



  /* If not truncating names and the name is too long or contains

   * a space, use extended format 1.   */

  size_t lname = strlen(name);

  uid_t uid = sb->st_uid;

  gid_t gid = sb->st_gid;

  if (uid > USHRT_MAX) {

    uid = USHRT_MAX;

  }

  if (gid > USHRT_MAX) {

    gid = USHRT_MAX;

  }

  if (lname > sizeof(hdr->ar_name) || strchr(name, ' '))

    (void)sprintf(ar_hb, HDR1, AR_EFMT1, (int)lname, (long int)sb->st_mtime,

                  (unsigned)uid, (unsigned)gid, (unsigned)sb->st_mode,

                  (long long)sb->st_size + lname, ARFMAG);

  else {

    lname = 0;

    (void)sprintf(ar_hb, HDR2, name, (long int)sb->st_mtime, (unsigned)uid,

                  (unsigned)gid, (unsigned)sb->st_mode, (long long)sb->st_size,

                  ARFMAG);

  }

  off_t size = sb->st_size;



  if (fwrite(ar_hb, 1, sizeof(HDR), cfp->wFile) != sizeof(HDR))

    return -1;

