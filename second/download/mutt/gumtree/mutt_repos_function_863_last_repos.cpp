int mutt_label_message(HEADER *hdr)
{
  char buf[LONG_STRING], *new;
  int i;
  int changed;

  if (!Context || !Context->label_hash)
    return 0;

  *buf = '\0';
  if (hdr != NULL && hdr->env->x_label != NULL) {
    strncpy(buf, hdr->env->x_label, LONG_STRING);
  }

  if (mutt_get_field("Label: ", buf, sizeof(buf), MUTT_LABEL /* | MUTT_CLEAR */) != 0)
    return 0;

  new = buf;
  SKIPWS(new);
  if (*new == '\0')
    new = NULL;

  changed = 0;
  if (hdr != NULL)
  {
    if (label_message(Context, hdr, new))
    {
      ++changed;
      mutt_set_header_color (Context, hdr);
    }
  } else {
#define HDR_OF(index) Context->hdrs[Context->v2r[(index)]]
    for (i = 0; i < Context->vcount; ++i) {
      if (HDR_OF(i)->tagged)
        if (label_message(Context, HDR_OF(i), new)) {
          ++changed;
          mutt_set_flag(Context, HDR_OF(i),
            MUTT_TAG, 0);
          /* mutt_set_flag re-evals the header color */
        }
    }
  }

  return changed;
}