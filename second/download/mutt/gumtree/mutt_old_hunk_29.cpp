      if (b->parts->filename)
      {
	state_mark_attach (s);
	state_printf (s, _("[-- name: %s --]\n"), b->parts->filename);
      }

      mutt_copy_hdr (s->fpin, s->fpout, ftell (s->fpin), b->parts->offset,
		     (option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) |
		     CH_DECODE , NULL);
    }
  }
  else if(expiration && expire < time(NULL))
  {
