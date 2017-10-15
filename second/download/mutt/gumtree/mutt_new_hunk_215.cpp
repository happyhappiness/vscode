		     (option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) |
		     CH_DECODE , NULL);
    }
  }
  else if(expiration && expire < time(NULL))
  {
    if (s->flags & MUTT_DISPLAY)
    {
      state_mark_attach (s);
      state_printf (s, _("[-- This %s/%s attachment is not included, --]\n"),
		    TYPE(b->parts), b->parts->subtype);
      state_attach_puts (_("[-- and the indicated external source has --]\n"
			   "[-- expired. --]\n"), s);
