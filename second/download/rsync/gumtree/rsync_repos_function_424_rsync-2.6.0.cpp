int inflate_flush(s, z, r)
inflate_blocks_statef *s;
z_streamp z;
int r;
{
  uInt n;
  Bytef *p;
  Bytef *q;

  /* local copies of source and destination pointers */
  p = z->next_out;
  q = s->read;

  /* compute number of bytes to copy as far as end of window */
  n = (uInt)((q <= s->write ? s->write : s->end) - q);
  if (n > z->avail_out) n = z->avail_out;
  if (n && r == Z_BUF_ERROR) r = Z_OK;

  /* update counters */
  z->avail_out -= n;
  z->total_out += n;

  /* update check information */
  if (s->checkfn != Z_NULL)
    z->adler = s->check = (*s->checkfn)(s->check, q, n);

  /* copy as far as end of window */
  zmemcpy(p, q, n);
  p += n;
  q += n;

  /* see if more to copy at beginning of window */
  if (q == s->end)
  {
    /* wrap pointers */
    q = s->window;
    if (s->write == s->end)
      s->write = s->window;

    /* compute bytes to copy */
    n = (uInt)(s->write - q);
    if (n > z->avail_out) n = z->avail_out;
    if (n && r == Z_BUF_ERROR) r = Z_OK;

    /* update counters */
    z->avail_out -= n;
    z->total_out += n;

    /* update check information */
    if (s->checkfn != Z_NULL)
      z->adler = s->check = (*s->checkfn)(s->check, q, n);

    /* copy */
    zmemcpy(p, q, n);
    p += n;
    q += n;
  }

  /* update pointers */
  z->next_out = p;
  s->read = q;

  /* done */
  return r;
}