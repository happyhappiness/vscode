static void post_entry (char *s, size_t slen, MUTTMENU *menu, int entry)
{
  CONTEXT *ctx = (CONTEXT *) menu->data;

  _mutt_make_string (s, slen, NONULL (HdrFmt), ctx, ctx->hdrs[entry],
		     M_FORMAT_ARROWCURSOR);
}