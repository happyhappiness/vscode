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
