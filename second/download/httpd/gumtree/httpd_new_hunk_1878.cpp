        mpm_new_argv->nelts = mpm_new_argv->nalloc;
    }

    /* Let the main thread continue now... but hang on to the
     * signal_monitor event so we can take further action
     */
    SetEvent(ctx->service_init);

    WaitForSingleObject(ctx->service_term, INFINITE);
}


DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
{
    apr_status_t rv = APR_SUCCESS;

    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { "", service_nt_main_fn },
        { NULL, NULL }
    };

    /* ###: utf-ize */
    if (!StartServiceCtrlDispatcher(dispatchTable))
    {
        /* This is a genuine failure of the SCM. */
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "Error starting service control dispatcher");
    }

    return (rv);
}


/* The service configuration's is stored under the following trees:
 *
 * HKLM\System\CurrentControlSet\Services\[service name]
 *
 *     \DisplayName
 *     \ImagePath
 *     \Parameters\ConfigArgs
 */


apr_status_t mpm_service_set_name(apr_pool_t *p, const char **display_name,
                                  const char *set_name)
{
    char key_name[MAX_PATH];
    ap_regkey_t *key;
    apr_status_t rv;
