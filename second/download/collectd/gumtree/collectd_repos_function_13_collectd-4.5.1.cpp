static void
argz_stringify (argz, argz_len, sep)
     char *argz;
     size_t argz_len;
     int sep;
{
  assert ((argz && argz_len) || (!argz && !argz_len));

  if (sep)
    {
      --argz_len;		/* don't stringify the terminating EOS */
      while (--argz_len > 0)
	{
	  if (argz[argz_len] == LT_EOS_CHAR)
	    argz[argz_len] = sep;
	}
    }
}