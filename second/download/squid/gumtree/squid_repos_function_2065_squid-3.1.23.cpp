void
storeLogOpen(void)
{
    storeLogRegisterWithCacheManager();

    if (Config.Log.store == NULL || strcmp(Config.Log.store, "none") == 0) {
        debugs(20, 1, "Store logging disabled");
        return;
    }

    storelog = logfileOpen(Config.Log.store, 0, 1);
}