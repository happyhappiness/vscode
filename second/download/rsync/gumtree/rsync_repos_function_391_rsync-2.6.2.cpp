int inflate_blocks_sync_point(s)
inflate_blocks_statef *s;
{
  return s->mode == LENS;
}