static int ci_next_undeleted (int msgno)
{
  int i;

  for (i=msgno+1; i < Context->vcount; i++)
    if (! Context->hdrs[Context->v2r[i]]->deleted)
      return (i);
  return (-1);
}