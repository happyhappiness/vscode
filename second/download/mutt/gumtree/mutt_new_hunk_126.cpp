}

/* 
 * Implementation of `encrypted_handler'.
 */

/* MIME handler for pgp/mime encrypted messages.
 * This handler is passed the application/octet-stream directly.
 * The caller must propagate a->goodsig to its parent.
 */
int pgp_gpgme_encrypted_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fpout;
  BODY *tattach;
  int is_signed;
  int rc = 0;
  
  dprint (2, (debugfile, "Entering pgp_encrypted handler\n"));

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fpout = safe_fopen (tempfile, "w+")))
    {
      if (s->flags & M_DISPLAY)
        state_attach_puts (_("[-- Error: could not create temporary file! "
