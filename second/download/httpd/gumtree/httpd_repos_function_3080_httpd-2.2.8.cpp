static int wsa_cleanup_with_handle (void *handle)
{
    APP_DATA *app_data;
    
    if (!(app_data = (APP_DATA*) get_app_data(gLibId)))
        return APR_EGENERAL;

    return WSACleanupRTag(app_data->gs_startup_rtag);
}