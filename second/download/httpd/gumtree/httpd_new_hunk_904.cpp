        ReportStatusToSCMgr(SERVICE_STOP_PENDING, // service state
                            NO_ERROR,             // exit code
                            30000);               // wait hint
}


apr_status_t mpm_service_install(apr_pool_t *ptemp, int argc,
                                 const char * const * argv, int reconfig)
{
    char key_name[MAX_PATH];
    char exe_path[MAX_PATH];
    char *launch_cmd;
    ap_regkey_t *key;
    apr_status_t rv;

    fprintf(stderr,reconfig ? "Reconfiguring the %s service\n"
		   : "Installing the %s service\n", mpm_display_name);

    /* ###: utf-ize */
    if (GetModuleFileName(NULL, exe_path, sizeof(exe_path)) == 0)
    {
