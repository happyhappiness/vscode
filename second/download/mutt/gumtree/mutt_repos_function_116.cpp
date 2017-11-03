static int compare_subject (const void *a, const void *b)
{
  HEADER **pa = (HEADER **) a;
  HEADER **pb = (HEADER **) b;
  int rc;

  if (!(*pa)->env->real_subj)
  {
    if (!(*pb)->env->real_subj)
      rc = compare_date_sent (pa, pb);
    else
      rc = -1;
  }
  else if (!(*pb)->env->real_subj)
    rc = 1;
  else
    rc = mutt_strcasecmp ((*pa)->env->real_subj, (*pb)->env->real_subj);
  AUXSORT(rc,a,b);
  return (SORTCODE (rc));
}