int setGlobalPool(void *data, int proc)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    if ((proc < 0) || (proc > (MAX_PROCESSORS-1))) {
        return 0;
    }

    NXLock(gLibLock);

    if (app_data && !app_data->gPool[proc]) {
        app_data->gPool[proc] = data;
    }

    NXUnlock(gLibLock);
    return 1;
}