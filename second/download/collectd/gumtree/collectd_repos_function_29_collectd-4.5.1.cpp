static lt_module
sys_bedl_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  image_id image = 0;

  if (filename)
    {
      image = load_add_on (filename);
    }
  else
    {
      image_info info;
      int32 cookie = 0;
      if (get_next_image_info (0, &cookie, &info) == B_OK)
	image = load_add_on (info.name);
    }

  if (image <= 0)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_OPEN));
      image = 0;
    }

  return (lt_module) image;
}