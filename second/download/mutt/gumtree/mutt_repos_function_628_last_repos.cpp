crypt_module_specs_t crypto_module_lookup (int identifier)
{
  crypt_module_t module = modules;

  while (module && (module->specs->identifier != identifier))
    module = module->next;

  return module ? module->specs : NULL;
}