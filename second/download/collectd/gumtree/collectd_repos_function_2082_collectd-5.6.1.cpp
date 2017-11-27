static char *
uuid_get_from_hal(void)
{
    LibHalContext *ctx;

    DBusError error;
    DBusConnection *con;

    dbus_error_init(&error);

    if (!(con = dbus_bus_get(DBUS_BUS_SYSTEM, &error)))
        goto bailout_nobus;

    ctx = libhal_ctx_new();
    libhal_ctx_set_dbus_connection(ctx, con);

    if (!libhal_ctx_init(ctx, &error))
        goto bailout;

    if (!libhal_device_property_exists(ctx,
                                       UUID_PATH,
                                       UUID_PROPERTY,
                                       &error))
        goto bailout;

    char *uuid  = libhal_device_get_property_string(ctx,
                                                    UUID_PATH,
                                                    UUID_PROPERTY,
                                                    &error);
    if (looks_like_a_uuid (uuid))
        return (uuid);

 bailout:
    {
        DBusError ctxerror;
        dbus_error_init(&ctxerror);
        if (!(libhal_ctx_shutdown(ctx, &ctxerror)))
            dbus_error_free(&ctxerror);
    }

    libhal_ctx_free(ctx);

 bailout_nobus:
    if (dbus_error_is_set(&error))
        dbus_error_free(&error);
    return (NULL);
}