int unregister_NLM(void *NLMHandle)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    NXLock(gLibLock);
    if (app_data) {
        app_data->initialized = 0;
        NXUnlock(gLibLock);
        return 0;
    }
    NXUnlock(gLibLock);
    return 1;
}