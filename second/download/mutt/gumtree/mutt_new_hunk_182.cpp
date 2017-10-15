  else
  {
    struct hdr_format_info hfi;
    hfi.ctx = Context;
    hfi.pager_progress = ExtPagerProgress;
    hfi.hdr = cur;
    mutt_make_string_info (buf, sizeof (buf), MuttIndexWindow->cols, NONULL(PagerFmt), &hfi, MUTT_FORMAT_MAKEPRINT);
    fputs (buf, fpout);
    fputs ("\n\n", fpout);
  }

  res = mutt_copy_message (fpout, Context, cur, cmflags,
       	(option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) | CH_DECODE | CH_FROM | CH_DISPLAY);
