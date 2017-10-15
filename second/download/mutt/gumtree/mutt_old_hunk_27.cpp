      
      state_mark_attach (s);
      state_printf (s, _("[-- Type: %s/%s, Encoding: %s, Size: %s --]\n"),
		    TYPE (p), p->subtype, ENCODING (p->encoding), length);
      if (!option (OPTWEED))
      {
	fseek (s->fpin, p->hdr_offset, 0);
	mutt_copy_bytes(s->fpin, s->fpout, p->offset-p->hdr_offset);
      }
      else
	state_putc ('\n', s);
    }
    else
    {
      if (p->description && mutt_can_decode (p))
	state_printf (s, "Content-Description: %s\n", p->description);

      if (p->form_name)
	state_printf(s, "%s: \n", p->form_name);

    }
    mutt_body_handler (p, s);
    state_putc ('\n', s);
  }

  if (a->encoding == ENCBASE64 || a->encoding == ENCQUOTEDPRINTABLE ||
      a->encoding == ENCUUENCODED)
    mutt_free_body (&b);
}

void autoview_handler (BODY *a, STATE *s)
{
  rfc1524_entry *entry = rfc1524_new_entry ();
  char buffer[LONG_STRING];
  char type[STRING];
  char command[LONG_STRING];
  char tempfile[_POSIX_PATH_MAX] = "";
  char *fname;
  FILE *fpin = NULL;
  FILE *fpout = NULL;
  FILE *fperr = NULL;
  int piped = FALSE;
  pid_t thepid;

  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  rfc1524_mailcap_lookup (a, type, entry, M_AUTOVIEW);

  fname = safe_strdup (a->filename);
  mutt_sanitize_filename (fname, 1);
