int register_NLM(void *NLMHandle)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    NXLock(gLibLock);
    if (!app_data) {
        app_data = (APP_DATA*)library_malloc(gLibHandle, sizeof(APP_DATA));

        if (app_data) {
            memset (app_data, 0, sizeof(APP_DATA));
            set_app_data(gLibId, app_data);
            app_data->gs_nlmhandle = NLMHandle;
        }
    }

    if (app_data && (!app_data->initialized)) {
        app_data->initialized = 1;
        NXUnlock(gLibLock);
        return 0;
    }

    NXUnlock(gLibLock);
    return 1;
}