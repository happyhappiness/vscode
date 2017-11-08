local int inflate_trees_fixed(bl, bd, tl, td)
uIntf *bl;               /* literal desired/actual bit depth */
uIntf *bd;               /* distance desired/actual bit depth */
inflate_huft * FAR *tl;  /* literal/length tree result */
inflate_huft * FAR *td;  /* distance tree result */
{
  /* build fixed tables if not built already--lock out other instances */
#ifdef MULTI_THREADED
  while (++fixed_lock > 1)
    fixed_lock--;
#endif
  if (!fixed_built)
  {
    int k;              /* temporary variable */
    unsigned c[288];    /* length list for huft_build */
    z_stream z;         /* for falloc function */

    /* set up fake z_stream for memory routines */
    z.zalloc = falloc;
    z.zfree = ffree;
    z.opaque = Z_NULL;

    /* literal table */
    for (k = 0; k < 144; k++)
      c[k] = 8;
    for (; k < 256; k++)
      c[k] = 9;
    for (; k < 280; k++)
      c[k] = 7;
    for (; k < 288; k++)
      c[k] = 8;
    fixed_bl = 7;
    huft_build(c, 288, 257, cplens, cplext, &fixed_tl, &fixed_bl, &z);

    /* distance table */
    for (k = 0; k < 30; k++)
      c[k] = 5;
    fixed_bd = 5;
    huft_build(c, 30, 0, cpdist, cpdext, &fixed_td, &fixed_bd, &z);

    /* done */
    fixed_built = 1;
  }
#ifdef MULTI_THREADED
  fixed_lock--;
#endif
  *bl = fixed_bl;
  *bd = fixed_bd;
  *tl = fixed_tl;
  *td = fixed_td;
  return Z_OK;
}