      b->type = origType;
    }

    /* process the (decoded) body part */
    if (handler)
    {
      rc = handler (b, s);

      if (rc)
      {
	dprint (1, (debugfile, "Failed on attachment of type %s/%s.\n", TYPE(b), NONULL (b->subtype)));
      }
      
      if (decode)
      {
	b->length = tmplength;
	b->offset = tmpoffset;

	/* restore the original source stream */
	safe_fclose (&s->fpin);
	s->fpin = fp;
      }
    }
    s->flags |= M_FIRSTDONE;
  }
  /* print hint to use attachment menu for disposition == attachment
     if we're not already being called from there */
  else if ((s->flags & M_DISPLAY) || (b->disposition == DISPATTACH &&
				      !option (OPTVIEWATTACH) &&
				      option (OPTHONORDISP) &&
				      (plaintext || handler)))
  {
    state_mark_attach (s);
    if (option (OPTHONORDISP) && b->disposition == DISPATTACH)
      fputs (_("[-- This is an attachment "), s->fpout);
    else
      state_printf (s, _("[-- %s/%s is unsupported "), TYPE (b), b->subtype);
    if (!option (OPTVIEWATTACH))
    {
      char keystroke[SHORT_STRING];

      if (km_expand_key (keystroke, sizeof(keystroke),
			km_find_func (MENU_PAGER, OP_VIEW_ATTACHMENTS)))
	fprintf (s->fpout, _("(use '%s' to view this part)"), keystroke);
      else
	fputs (_("(need 'view-attachments' bound to key!)"), s->fpout);
    }
    fputs (" --]\n", s->fpout);
  }

  bail:
  s->flags = oflags | (s->flags & M_FIRSTDONE);
  if (rc)
  {
    dprint (1, (debugfile, "Bailing on attachment of type %s/%s.\n", TYPE(b), NONULL (b->subtype)));
  }

  return rc;
}
