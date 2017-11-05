static int ExportLogTransaction(request_rec *r)
{
    return ap_run_optional_hook_test(r->the_request);
}