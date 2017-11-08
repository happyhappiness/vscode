void* getGlobalPool()
{
    APP_DATA *app_data = (APP_DATA*) get_app_data(gLibId);

    if (app_data) {
        return app_data->gPool;
    }

    return NULL;
}