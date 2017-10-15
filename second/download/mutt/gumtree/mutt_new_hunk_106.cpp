	return -1;
    }
    fprintf (f, "\n--%s--\n", boundary);
    return (ferror (f) ? -1 : 0);
  }

  /* This is pretty gross, but it's the best solution for now... */
  if ((WithCrypto & APPLICATION_PGP)
      && a->type == TYPEAPPLICATION
      && mutt_strcmp (a->subtype, "pgp-encrypted") == 0)
  {
    fputs ("Version: 1\n", f);
    return 0;
  }

  if ((fpin = fopen (a->filename, "r")) == NULL)
  {
    dprint(1,(debugfile, "write_mime_body: %s no longer exists!\n",a->filename));
    mutt_error (_("%s no longer exists!"), a->filename);
    return -1;
  }

  if (a->type == TYPETEXT && (!a->noconv))
    fc = fgetconv_open (fpin, a->charset,
			mutt_get_body_charset (send_charset, sizeof (send_charset), a),
			0);
  else
    fc = fgetconv_open (fpin, 0, 0, 0);

  if (a->encoding == ENCQUOTEDPRINTABLE)
    encode_quoted (fc, f, write_as_text_part (a));
  else if (a->encoding == ENCBASE64)
    encode_base64 (fc, f, write_as_text_part (a));
  else if (a->type == TYPETEXT && (!a->noconv))
    encode_8bit (fc, f, write_as_text_part (a));
  else
    mutt_copy_stream (fpin, f);

  fgetconv_close (&fc);
  safe_fclose (&fpin);

  return (ferror (f) ? -1 : 0);
}

#undef write_as_text_part

#define BOUNDARYLEN 16
void mutt_generate_boundary (PARAMETER **parm)
{
  char rs[BOUNDARYLEN + 1];
  char *p = rs;
  int i;

  rs[BOUNDARYLEN] = 0;
  for (i=0;i<BOUNDARYLEN;i++)
    *p++ = B64Chars[LRAND() % sizeof (B64Chars)];
  *p = 0;

  mutt_set_parameter ("boundary", rs, parm);
}

typedef struct
{
  int from;
