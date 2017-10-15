  {
    fprintf (out, "Content-Length: " OFF_T_FMT "\n", h->content->length);
    if (h->lines != 0 || h->content->length == 0)
      fprintf (out, "Lines: %d\n", h->lines);
  }

  if (flags & CH_UPDATE_LABEL)
  {
    h->xlabel_changed = 0;
    if (h->env->x_label != NULL)
      if (fprintf(out, "X-Label: %s\n", h->env->x_label) !=
		  10 + strlen(h->env->x_label))
        return -1;
  }

  if ((flags & CH_NONEWLINE) == 0)
  {
    if (flags & CH_PREFIX)
      fputs(prefix, out);
    fputc ('\n', out); /* add header terminator */
  }
