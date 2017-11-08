void* getStatCache(int proc)
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    if ((proc < 0) || (proc > (MAX_PROCESSORS-1))) {
        return NULL;
    }

    if (app_data) {
        return app_data->statCache[proc];
    }

    return NULL;
}