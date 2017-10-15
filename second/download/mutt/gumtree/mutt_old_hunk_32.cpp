      b->type = origType;
    }

    /* process the (decoded) body part */
    if (handler)
    {
      handler (b, s);

      if (decode)
      {
	b->length = tmplength;
	b->offset = tmpoffset;

	/* restore the original source stream */
	fclose (s->fpin);
	s->fpin = fp;
      }
    }
  }
  else if (s->flags & M_DISPLAY)
  {
    state_mark_attach (s);
    state_printf (s, _("[-- %s/%s is unsupported "), TYPE (b), b->subtype);
    if (!option (OPTVIEWATTACH))
    {
      if (km_expand_key (type, sizeof(type),
			km_find_func (MENU_PAGER, OP_VIEW_ATTACHMENTS)))
	fprintf (s->fpout, _("(use '%s' to view this part)"), type);
      else
	fputs (_("(need 'view-attachments' bound to key!)"), s->fpout);
    }
    fputs (" --]\n", s->fpout);
  }
  
  bail:
  s->flags = oflags;
}
