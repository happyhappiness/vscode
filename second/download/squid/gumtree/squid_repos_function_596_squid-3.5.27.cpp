static int
has_library_ext (const char *filename)
{
  const char *	ext     = 0;

  assert (filename);

  ext = strrchr (filename, '.');

  if (ext && ((STREQ (ext, archive_ext))
#if defined LT_MODULE_EXT
	     || (STREQ (ext, shlib_ext))
#endif
#if defined LT_SHARED_EXT
	     || (STREQ (ext, shared_ext))
#endif
    ))
    {
      return 1;
    }

  return 0;
}