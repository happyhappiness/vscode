static int qp_lookahead_eol(mime_encoder_state *st, int ateof, size_t n)
{
  n += st->bufbeg;
  if(n >= st->bufend && ateof)
    return 1;
  if(n + 2 > st->bufend)
    return ateof? 0: -1;
  if(qp_class[st->buf[n] & 0xFF] == QP_CR &&
     qp_class[st->buf[n + 1] & 0xFF] == QP_LF)
    return 1;
  return 0;
}