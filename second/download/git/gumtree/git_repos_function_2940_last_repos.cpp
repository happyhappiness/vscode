static inline void
do_ungetc (int c)
{
  if (c != EOF)
    ungetc (c, stdin);
}