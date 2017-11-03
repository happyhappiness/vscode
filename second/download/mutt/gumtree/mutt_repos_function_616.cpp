int wcwidth (wchar_t wc)
{
  if (!Charset_is_utf8)
  {
    if (!charset_is_ja)
    {
      /* 8-bit case */
      if (!wc)
	return 0;
      else if ((0 <= wc && wc < 256) && IsPrint (wc))
	return 1;
      else
	return -1;
    }
    else
    {
      /* Japanese */
      int k = wcwidth_ja (wc);
      if (k != -1)
	return k;
    }
  }
  return wcwidth_ucs (wc);
}