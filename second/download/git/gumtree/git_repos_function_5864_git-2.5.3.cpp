static int bin_find(mstate m, mchunkptr x) {
  size_t size = chunksize(x);
  if (is_small(size)) {
    bindex_t sidx = small_index(size);
    sbinptr b = smallbin_at(m, sidx);
    if (smallmap_is_marked(m, sidx)) {
      mchunkptr p = b;
      do {
	if (p == x)
	  return 1;
      } while ((p = p->fd) != b);
    }
  }
  else {
    bindex_t tidx;
    compute_tree_index(size, tidx);
    if (treemap_is_marked(m, tidx)) {
      tchunkptr t = *treebin_at(m, tidx);
      size_t sizebits = size << leftshift_for_tree_index(tidx);
      while (t != 0 && chunksize(t) != size) {
	t = t->child[(sizebits >> (SIZE_T_BITSIZE-SIZE_T_ONE)) & 1];
	sizebits <<= 1;
      }
      if (t != 0) {
	tchunkptr u = t;
	do {
	  if (u == (tchunkptr)x)
	    return 1;
	} while ((u = u->fd) != t);
      }
    }
  }
  return 0;
}