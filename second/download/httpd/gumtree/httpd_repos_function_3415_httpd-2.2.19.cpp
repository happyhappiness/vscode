int setGlobalPool(void *data)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    NXLock(gLibLock);

    if (app_data && !app_data->gPool) {
        app_data->gPool = data;
    }

    NXUnlock(gLibLock);
    return 1;
}