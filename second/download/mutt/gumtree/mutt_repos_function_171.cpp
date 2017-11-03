int safe_rename (const char *src, const char *target)
{
  struct stat ssb, tsb;

  if (!src || !target)
    return -1;

  if (link (src, target) != 0)
  {

    /*
     * Coda does not allow cross-directory links, but tells
     * us it's a cross-filesystem linking attempt.
     * 
     * However, the Coda rename call is allegedly safe to use.
     * 
     * With other file systems, rename should just fail when 
     * the files reside on different file systems, so it's safe
     * to try it here.
     *
     */
    
    dprint (1, (debugfile, "safe_rename: link (%s, %s) failed: %s (%d)\n", src, target, strerror (errno), errno));

    /*
     * FUSE may return ENOSYS. VFAT may return EPERM. FreeBSD's
     * msdosfs may return EOPNOTSUPP.  ENOTSUP can also appear.
     */
    if (errno == EXDEV || errno == ENOSYS || errno == EPERM
#ifdef ENOTSUP
	|| errno == ENOTSUP
#endif
#ifdef EOPNOTSUPP
	|| errno == EOPNOTSUPP
#endif
	)
    {
      dprint (1, (debugfile, "safe_rename: trying rename...\n"));
      if (rename (src, target) == -1) 
      {
	dprint (1, (debugfile, "safe_rename: rename (%s, %s) failed: %s (%d)\n", src, target, strerror (errno), errno));
	return -1;
      }
      dprint (1, (debugfile, "safe_rename: rename succeeded.\n"));
    
      return 0;
    }

    return -1;
  }

  /*
   * Stat both links and check if they are equal.
   */
  
  if (lstat (src, &ssb) == -1)
  {
    dprint (1, (debugfile, "safe_rename: can't stat %s: %s (%d)\n",
		src, strerror (errno), errno));
    return -1;
  }
  
  if (lstat (target, &tsb) == -1)
  {
    dprint (1, (debugfile, "safe_rename: can't stat %s: %s (%d)\n",
		src, strerror (errno), errno));
    return -1;
  }

  /* 
   * pretend that the link failed because the target file
   * did already exist.
   */

  if (compare_stat (&ssb, &tsb) == -1)
  {
    dprint (1, (debugfile, "safe_rename: stat blocks for %s and %s diverge; pretending EEXIST.\n", src, target));
    errno = EEXIST;
    return -1;
  }

  /*
   * Unlink the original link.  Should we really ignore the return
   * value here? XXX
   */

  if (unlink (src) == -1) 
  {
    dprint (1, (debugfile, "safe_rename: unlink (%s) failed: %s (%d)\n",
		src, strerror (errno), errno));
  }
  

  return 0;
}