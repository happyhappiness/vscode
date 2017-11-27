static lt_module
vm_open (lt_user_data LT__UNUSED loader_data, const char *filename,
         lt_dladvise LT__UNUSED advise)
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
      LT__SETERROR (CANNOT_OPEN);
      image = 0;
    }

  return (lt_module) image;
}