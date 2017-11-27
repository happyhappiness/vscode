void
argz_stringify (char *argz, size_t argz_len, int sep)
{
  assert ((argz && argz_len) || (!argz && !argz_len));

  if (sep)
    {
      --argz_len;		/* don't stringify the terminating EOS */
      while (--argz_len > 0)
	{
	  if (argz[argz_len] == EOS_CHAR)
	    argz[argz_len] = sep;
	}
    }
}