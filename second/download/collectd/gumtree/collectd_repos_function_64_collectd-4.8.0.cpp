static lt_dlhandle *
find_handle (search_path, base_name, handle)
     const char *search_path;
     const char *base_name;
     lt_dlhandle *handle;
{
  if (!search_path)
    return 0;

  if (!foreach_dirinpath (search_path, base_name, find_handle_callback,
			  handle, 0))
    return 0;

  return handle;
}