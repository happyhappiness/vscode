local int inflate_trees_dynamic(nl, nd, c, bl, bd, tl, td, z)
uInt nl;                /* number of literal/length codes */
uInt nd;                /* number of distance codes */
uIntf *c;               /* that many (total) code lengths */
uIntf *bl;              /* literal desired/actual bit depth */
uIntf *bd;              /* distance desired/actual bit depth */
inflate_huft * FAR *tl; /* literal/length tree result */
inflate_huft * FAR *td; /* distance tree result */
z_stream *z;            /* for zfree function */
{
  int r;

  /* build literal/length tree */
  if ((r = huft_build(c, nl, 257, cplens, cplext, tl, bl, z)) != Z_OK)
  {
    if (r == Z_DATA_ERROR)
      z->msg = "oversubscribed literal/length tree";
    else if (r == Z_BUF_ERROR)
    {
      inflate_trees_free(*tl, z);
      z->msg = "incomplete literal/length tree";
      r = Z_DATA_ERROR;
    }
    return r;
  }

  /* build distance tree */
  if ((r = huft_build(c + nl, nd, 0, cpdist, cpdext, td, bd, z)) != Z_OK)
  {
    if (r == Z_DATA_ERROR)
      z->msg = "oversubscribed literal/length tree";
    else if (r == Z_BUF_ERROR) {
#ifdef PKZIP_BUG_WORKAROUND
      r = Z_OK;
    }
#else
      inflate_trees_free(*td, z);
      z->msg = "incomplete literal/length tree";
      r = Z_DATA_ERROR;
    }
    inflate_trees_free(*tl, z);
    return r;
#endif
  }