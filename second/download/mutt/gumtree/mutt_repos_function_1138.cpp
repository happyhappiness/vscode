static int dotlock_dispatch (const char *f, int fd)
{
  char realpath[_POSIX_PATH_MAX];

  /* If dotlock_prepare () succeeds [return value == 0],
   * realpath contains the basename of f, and we have
   * successfully changed our working directory to
   * `dirname $f`.  Additionally, f has been opened for
   * reading to verify that the user has at least read
   * permissions on that file.
   * 
   * For a more detailed explanation of all this, see the
   * lengthy comment below.
   */

  if (dotlock_prepare (realpath, sizeof (realpath), f, fd) != 0)
    return DL_EX_ERROR;

  /* Actually perform the locking operation. */

  if (DotlockFlags & DL_FL_TRY)
    return dotlock_try ();
  else if (DotlockFlags & DL_FL_UNLOCK)
    return dotlock_unlock (realpath);
  else if (DotlockFlags & DL_FL_UNLINK)
    return dotlock_unlink (realpath);
  else /* lock */
    return dotlock_lock (realpath);
}