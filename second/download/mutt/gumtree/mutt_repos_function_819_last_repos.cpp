static unsigned long cum_attachs_size (MUTTMENU *menu)
{
  size_t s;
  unsigned short i;
  ATTACH_CONTEXT *actx = menu->data;
  ATTACHPTR **idx = actx->idx;
  CONTENT *info;
  BODY *b;
  
  for (i = 0, s = 0; i < actx->idxlen; i++)
  {
    b = idx[i]->content;

    if (!b->content)
      b->content = mutt_get_content_info (b->filename, b);

    if ((info = b->content))
    {
      switch (b->encoding)
      {
	case ENCQUOTEDPRINTABLE:
	  s += 3 * (info->lobin + info->hibin) + info->ascii + info->crlf;
	  break;
	case ENCBASE64:
	  s += (4 * (info->lobin + info->hibin + info->ascii + info->crlf)) / 3;
	  break;
	default:
	  s += info->lobin + info->hibin + info->ascii + info->crlf;
	  break;
      }
    }
  }

  return s;
}