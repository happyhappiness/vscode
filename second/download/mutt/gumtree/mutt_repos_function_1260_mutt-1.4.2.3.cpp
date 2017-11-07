static const char *
get_charset_aliases ()
{
  const char *cp;

  cp = charset_aliases;
  if (cp == NULL)
    {
#ifndef WIN32
      FILE *fp;
      const char *dir = LIBDIR;
      const char *base = "charset.alias";
      char *file_name;

      /* Concatenate dir and base into freshly allocated file_name.  */
      {
	size_t dir_len = strlen (dir);
	size_t base_len = strlen (base);
	int add_slash = (dir_len > 0 && !ISSLASH (dir[dir_len - 1]));
	file_name = (char *) malloc (dir_len + add_slash + base_len + 1);
	if (file_name != NULL)
	  {
	    memcpy (file_name, dir, dir_len);
	    if (add_slash)
	      file_name[dir_len] = DIRECTORY_SEPARATOR;
	    memcpy (file_name + dir_len + add_slash, base, base_len + 1);
	  }
      }

      if (file_name == NULL || (fp = fopen (file_name, "r")) == NULL)
	/* Out of memory or file not found, treat it as empty.  */
	cp = "";
      else
	{
	  /* Parse the file's contents.  */
	  int c;
	  char buf1[50+1];
	  char buf2[50+1];
	  char *res_ptr = NULL;
	  size_t res_size = 0;
	  size_t l1, l2;

	  for (;;)
	    {
	      c = getc (fp);
	      if (c == EOF)
		break;
	      if (c == '\n' || c == ' ' || c == '\t')
		continue;
	      if (c == '#')
		{
		  /* Skip comment, to end of line.  */
		  do
		    c = getc (fp);
		  while (!(c == EOF || c == '\n'));
		  if (c == EOF)
		    break;
		  continue;
		}
	      ungetc (c, fp);
	      if (fscanf(fp, "%50s %50s", buf1, buf2) < 2)
		break;
	      l1 = strlen (buf1);
	      l2 = strlen (buf2);
	      if (res_size == 0)
		{
		  res_size = l1 + 1 + l2 + 1;
		  res_ptr = malloc (res_size + 1);
		}
	      else
		{
		  res_size += l1 + 1 + l2 + 1;
		  res_ptr = realloc (res_ptr, res_size + 1);
		}
	      if (res_ptr == NULL)
		{
		  /* Out of memory. */
		  res_size = 0;
		  break;
		}
	      strcpy (res_ptr + res_size - (l2 + 1) - (l1 + 1), buf1);
	      strcpy (res_ptr + res_size - (l2 + 1), buf2);
	    }
	  fclose (fp);
	  if (res_size == 0)
	    cp = "";
	  else
	    {
	      *(res_ptr + res_size) = '\0';
	      cp = res_ptr;
	    }
	}

      if (file_name != NULL)
	free (file_name);

#else /* WIN32 */

      /* To avoid the troubles of installing a separate file in the same
	 directory as the DLL and of retrieving the DLL's directory at
	 runtime, simply inline the aliases here.  */

      cp = "CP936" "\0" "GBK" "\0"
	   "CP1361" "\0" "JOHAB" "\0";
#endif

      charset_aliases = cp;
    }

  return cp;
}