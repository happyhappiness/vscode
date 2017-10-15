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

