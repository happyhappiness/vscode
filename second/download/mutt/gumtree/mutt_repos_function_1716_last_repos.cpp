static int ci_previous_undeleted (int msgno)
{
  int i;

  for (i=msgno-1; i>=0; i--)
    if (! Context->hdrs[Context->v2r[i]]->deleted)
      return (i);
  return (-1);
}