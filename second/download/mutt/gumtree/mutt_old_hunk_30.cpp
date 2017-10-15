      state_mark_attach (s);
      state_printf (s, _("[-- This %s/%s attachment is not included, --]\n"),
		    TYPE(b->parts), b->parts->subtype);
      state_attach_puts (_("[-- and the indicated external source has --]\n"
			   "[-- expired. --]\n"), s);

      mutt_copy_hdr(s->fpin, s->fpout, ftell (s->fpin), b->parts->offset,
		    (option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) |
		    CH_DECODE, NULL);
    }
  }
  else
  {
    if (s->flags & M_DISPLAY)
    {
