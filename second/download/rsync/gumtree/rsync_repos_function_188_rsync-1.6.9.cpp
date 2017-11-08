local int inflate_trees_bits(c, bb, tb, z)
uIntf *c;               /* 19 code lengths */
uIntf *bb;              /* bits tree desired/actual depth */
inflate_huft * FAR *tb; /* bits tree result */
z_stream *z;            /* for zfree function */
{
  int r;

  r = huft_build(c, 19, 19, (uIntf*)Z_NULL, (uIntf*)Z_NULL, tb, bb, z);
  if (r == Z_DATA_ERROR)
    z->msg = "oversubscribed dynamic bit lengths tree";
  else if (r == Z_BUF_ERROR)
  {
    inflate_trees_free(*tb, z);
    z->msg = "incomplete dynamic bit lengths tree";
    r = Z_DATA_ERROR;
  }
  return r;
}