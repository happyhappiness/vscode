lt_dlvtable *
get_vtable (lt_user_data loader_data)
{
  if (!vtable)
    {
      vtable = (lt_dlvtable *) lt__zalloc (sizeof *vtable);
      iface_id = lt_dlinterface_register ("ltdl loadlibrary", NULL);
    }

  if (vtable && !vtable->name)
    {
      vtable->name		= "lt_loadlibrary";
      vtable->module_open	= vm_open;
      vtable->module_close	= vm_close;
      vtable->find_sym		= vm_sym;
      vtable->dlloader_exit	= vl_exit;
      vtable->dlloader_data	= loader_data;
      vtable->priority		= LT_DLLOADER_APPEND;
    }

  if (vtable && (vtable->dlloader_data != loader_data))
    {
      LT__SETERROR (INIT_LOADER);
      return 0;
    }

  return vtable;
}