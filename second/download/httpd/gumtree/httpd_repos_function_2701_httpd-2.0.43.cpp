int setStatCache(void *data, int proc)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    if ((proc < 0) || (proc > (MAX_PROCESSORS-1))) {
        return 0;
    }

    NXLock(gLibLock);

    if (app_data && !app_data->statCache[proc]) {
        app_data->statCache[proc] = data;
    }

    NXUnlock(gLibLock);
    return 1;
}