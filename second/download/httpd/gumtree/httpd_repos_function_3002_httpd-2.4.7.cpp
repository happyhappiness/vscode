static void am_register_hooks(apr_pool_t * p)
{
  ap_hook_access_checker(am_check_access, NULL, NULL, APR_HOOK_REALLY_FIRST);
}