	last = env->userhdrs = mutt_new_list ();
      last->data = safe_strdup (uh->data);
    }
  }
}

void mutt_forward_intro (FILE *fp, HEADER *cur)
{
  char buffer[STRING];
  
  fputs ("----- Forwarded message from ", fp);
  buffer[0] = 0;
  rfc822_write_address (buffer, sizeof (buffer), cur->env->from, 1);
  fputs (buffer, fp);
  fputs (" -----\n\n", fp);
}

void mutt_forward_trailer (FILE *fp)
{
  fputs ("\n----- End forwarded message -----\n", fp);
}


static int include_forward (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  int chflags = CH_DECODE, cmflags = 0;
