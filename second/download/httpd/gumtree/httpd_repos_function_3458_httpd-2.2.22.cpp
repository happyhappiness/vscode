static int wsa_startup_with_handle (WORD wVersionRequested, LPWSADATA data, void *handle)
{
    APP_DATA *app_data;
    
    if (!(app_data = (APP_DATA*) get_app_data(gLibId)))
        return APR_EGENERAL;

    app_data->gs_startup_rtag = AllocateResourceTag(handle, "WinSock Start-up", WS_LOAD_ENTRY_SIGNATURE);
    app_data->gs_socket_rtag  = AllocateResourceTag(handle, "WinSock socket()", WS_SKT_SIGNATURE);
    app_data->gs_lookup_rtag  = AllocateResourceTag(handle, "WinSock Look-up", WS_LOOKUP_SERVICE_SIGNATURE);
    app_data->gs_event_rtag   = AllocateResourceTag(handle, "WinSock Event", WS_WSAEVENT_SIGNATURE);
    app_data->gs_pcp_rtag     = AllocateResourceTag(handle, "WinSock C-Port", WS_CPORT_SIGNATURE);

    return WSAStartupRTags(wVersionRequested, data, 
                           app_data->gs_startup_rtag, 
                           app_data->gs_socket_rtag, 
                           app_data->gs_lookup_rtag, 
                           app_data->gs_event_rtag, 
                           app_data->gs_pcp_rtag);
}