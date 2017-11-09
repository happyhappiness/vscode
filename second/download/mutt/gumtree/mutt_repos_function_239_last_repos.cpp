void mutt_tag_set_flag (int flag, int bf)
{
  int j;

  for (j = 0; j < Context->vcount; j++)
    if (Context->hdrs[Context->v2r[j]]->tagged)
      mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], flag, bf);
}