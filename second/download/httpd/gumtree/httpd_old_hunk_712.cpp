{ "ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF, TAKE1,
  "Number of threads each child creates" },
{ NULL }
};


AP_DECLARE(void) mpm_recycle_completion_context(PCOMP_CONTEXT context)
{
    /* Recycle the completion context.
     * - clear the ptrans pool
     * - put the context on the queue to be consumed by the accept thread
     * Note: 
     * context->accept_socket may be in a disconnected but reusable 
     * state so -don't- close it.
     */
    if (context) {
        apr_pool_clear(context->ptrans);
        context->next = NULL;
        ResetEvent(context->Overlapped.hEvent);
        apr_thread_mutex_lock(qlock);
        if (qtail)
            qtail->next = context;
        else
            qhead = context;
        qtail = context;
        apr_thread_mutex_unlock(qlock);
    }
}

AP_DECLARE(PCOMP_CONTEXT) mpm_get_completion_context(void)
{
    apr_status_t rv;
    PCOMP_CONTEXT context = NULL;

    /* Grab a context off the queue */
    apr_thread_mutex_lock(qlock);
    if (qhead) {
        context = qhead;
        qhead = qhead->next;
        if (!qhead)
            qtail = NULL;
    }
    apr_thread_mutex_unlock(qlock);

    /* If we failed to grab a context off the queue, alloc one out of 
     * the child pool. There may be up to ap_threads_per_child contexts
     * in the system at once.
     */
    if (!context) {
        if (num_completion_contexts >= ap_threads_per_child) {
            static int reported = 0;
            if (!reported) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                             "Server ran out of threads to serve requests. Consider "
                             "raising the ThreadsPerChild setting");
                reported = 1;
            }
            return NULL;
        }
        /* Note:
         * Multiple failures in the next two steps will cause the pchild pool
         * to 'leak' storage. I don't think this is worth fixing...
         */
        context = (PCOMP_CONTEXT) apr_pcalloc(pchild, sizeof(COMP_CONTEXT));

        context->Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (context->Overlapped.hEvent == NULL) {
            /* Hopefully this is a temporary condition ... */
            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_os_error(), ap_server_conf,
                         "mpm_get_completion_context: CreateEvent failed.");
            return NULL;
        }

        /* Create the tranaction pool */
        if ((rv = apr_pool_create(&context->ptrans, pchild)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK,APLOG_WARNING, rv, ap_server_conf,
                         "mpm_get_completion_context: Failed to create the transaction pool.");
            CloseHandle(context->Overlapped.hEvent);
            return NULL;
        }
        apr_pool_tag(context->ptrans, "ptrans");

        context->accept_socket = INVALID_SOCKET;
        context->ba = apr_bucket_alloc_create(pchild);
        apr_atomic_inc(&num_completion_contexts);
    }

    return context;
}

AP_DECLARE(apr_status_t) mpm_post_completion_context(PCOMP_CONTEXT context, 
                                                     io_state_e state)
{
    LPOVERLAPPED pOverlapped;
    if (context)
        pOverlapped = &context->Overlapped;
    else
        pOverlapped = NULL;

    PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, state, pOverlapped);
    return APR_SUCCESS;
}

/* This is the helper code to resolve late bound entry points 
 * missing from one or more releases of the Win32 API...
 * but it sure would be nice if we didn't duplicate this code
 * from the APR ;-)
 */
static const char* const lateDllName[DLL_defined] = {
    "kernel32", "advapi32", "mswsock",  "ws2_32"  };
static HMODULE lateDllHandle[DLL_defined] = {
    NULL,       NULL,       NULL,       NULL      };

FARPROC ap_load_dll_func(ap_dlltoken_e fnLib, char* fnName, int ordinal)
{
    if (!lateDllHandle[fnLib]) { 
        lateDllHandle[fnLib] = LoadLibrary(lateDllName[fnLib]);
        if (!lateDllHandle[fnLib])
            return NULL;
    }
    if (ordinal)
        return GetProcAddress(lateDllHandle[fnLib], (char *) ordinal);
    else
        return GetProcAddress(lateDllHandle[fnLib], fnName);
}

/* To share the semaphores with other processes, we need a NULL ACL
 * Code from MS KB Q106387
 */
static PSECURITY_ATTRIBUTES GetNullACL()
{
    PSECURITY_DESCRIPTOR pSD;
    PSECURITY_ATTRIBUTES sa;

    sa  = (PSECURITY_ATTRIBUTES) LocalAlloc(LPTR, sizeof(SECURITY_ATTRIBUTES));
    sa->nLength = sizeof(sizeof(SECURITY_ATTRIBUTES));

    pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
    sa->lpSecurityDescriptor = pSD;

    if (pSD == NULL || sa == NULL) {
        return NULL;
    }
    apr_set_os_error(0);
    if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)
	|| apr_get_os_error()) {
        LocalFree( pSD );
        LocalFree( sa );
        return NULL;
    }
    if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE)
	|| apr_get_os_error()) {
        LocalFree( pSD );
        LocalFree( sa );
        return NULL;
    }

    sa->bInheritHandle = TRUE;
    return sa;
}

static void CleanNullACL( void *sa ) {
    if( sa ) {
        LocalFree( ((PSECURITY_ATTRIBUTES)sa)->lpSecurityDescriptor);
        LocalFree( sa );
    }
}

/*
 * The Win32 call WaitForMultipleObjects will only allow you to wait for 
 * a maximum of MAXIMUM_WAIT_OBJECTS (current 64).  Since the threading 
 * model in the multithreaded version of apache wants to use this call, 
 * we are restricted to a maximum of 64 threads.  This is a simplistic 
 * routine that will increase this size.
 */
static DWORD wait_for_many_objects(DWORD nCount, CONST HANDLE *lpHandles, 
                                   DWORD dwSeconds)
{
    time_t tStopTime;
    DWORD dwRet = WAIT_TIMEOUT;
    DWORD dwIndex=0;
    BOOL bFirst = TRUE;
  
    tStopTime = time(NULL) + dwSeconds;
  
    do {
        if (!bFirst)
            Sleep(1000);
        else
            bFirst = FALSE;
          
        for (dwIndex = 0; dwIndex * MAXIMUM_WAIT_OBJECTS < nCount; dwIndex++) {
            dwRet = WaitForMultipleObjects( 
                min(MAXIMUM_WAIT_OBJECTS, nCount - (dwIndex * MAXIMUM_WAIT_OBJECTS)),
                lpHandles + (dwIndex * MAXIMUM_WAIT_OBJECTS), 
                0, 0);
                                           
            if (dwRet != WAIT_TIMEOUT) {                                          
              break;
            }
        }
    } while((time(NULL) < tStopTime) && (dwRet == WAIT_TIMEOUT));
    
    return dwRet;
}

/*
 * Signalling Apache on NT.
 *
 * Under Unix, Apache can be told to shutdown or restart by sending various
 * signals (HUP, USR, TERM). On NT we don't have easy access to signals, so
 * we use "events" instead. The parent apache process goes into a loop
