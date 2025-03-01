static int
has_library_ext (const char *filename)
{
  const char *	ext     = 0;

  assert (filename);

  ext = strrchr (filename, '.');

  if (ext && ((streq (ext, archive_ext))
#if defined(LT_MODULE_EXT)
	     || (streq (ext, shlib_ext))
#endif
#if defined(LT_SHARED_EXT)
	     || (streq (ext, shared_ext))
#endif
    ))
    {
      return 1;
    }

  return 0;
}