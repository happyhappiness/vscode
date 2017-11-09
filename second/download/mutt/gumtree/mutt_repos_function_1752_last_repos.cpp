static void free_mbchar_table (mbchar_table **t)
{
  if (!t || !*t)
    return;

  FREE (&(*t)->chars);
  FREE (&(*t)->segmented_str);
  FREE (&(*t)->orig_str);
  FREE (t);		/* __FREE_CHECKED__ */
}