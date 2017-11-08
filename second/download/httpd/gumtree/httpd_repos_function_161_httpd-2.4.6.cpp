static void ExportRegisterHooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(TestOptionalFn);
}