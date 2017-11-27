static int
sys_bedl_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  int errors = 0;

  if (unload_add_on ((image_id) module) != B_OK)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_CLOSE));
      ++errors;
    }

  return errors;
}