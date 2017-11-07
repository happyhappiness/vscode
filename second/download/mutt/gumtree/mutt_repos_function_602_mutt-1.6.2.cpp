void crypto_module_register (crypt_module_specs_t specs)
{
  crypt_module_t module_new = safe_malloc (sizeof (*module_new));

  module_new->specs = specs;
  module_new->next = modules;
  if (modules)
    modules->prevp = &module_new->next;
  modules = module_new;
}