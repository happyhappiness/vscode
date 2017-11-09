int index_color (int index_no)
{
  HEADER *h = Context->hdrs[Context->v2r[index_no]];

  if (h && h->pair)
    return h->pair;

  mutt_set_header_color (Context, h);
  return h->pair;
}