
    DBusError error;
    DBusConnection *con;

    dbus_error_init(&error);

    if (!(con = dbus_bus_get(DBUS_BUS_SYSTEM, &error)) ) {
        goto bailout_nobus;
    }

    ctx = libhal_ctx_new();
    libhal_ctx_set_dbus_connection(ctx, con);

    if (!libhal_ctx_init(ctx, &error)) {
        goto bailout;
    }

    if (!libhal_device_property_exists(ctx,
                                       UUID_PATH,
                                       UUID_PROPERTY,
                                       &error)) {
        goto bailout;
    }

    char *uuid  = libhal_device_get_property_string(ctx,
                                                    UUID_PATH,
                                                    UUID_PROPERTY,
                                                    &error);
    if (looks_like_a_uuid (uuid)) {
        return uuid;
    }

 bailout:
    {
        DBusError ctxerror;
        dbus_error_init(&ctxerror);
        if (!(libhal_ctx_shutdown(ctx, &ctxerror))) {
            dbus_error_free(&ctxerror);
        }
    }

    libhal_ctx_free(ctx);
    //dbus_connection_unref(con);

 bailout_nobus:
    if (dbus_error_is_set(&error)) {
        /*printf("Error %s\n", error.name);*/
        dbus_error_free(&error);
    }
    return NULL;
}
#endif

static char *
uuid_get_from_file(const char *path)
{
    FILE *file;
    char uuid[UUID_PRINTABLE_NORMAL_LENGTH + 1] = "";

    file = fopen (path, "r");
    if (file == NULL)
        return NULL;

    if (!fgets(uuid, sizeof(uuid), file)) {
        fclose(file);
        return NULL;
    }
    fclose(file);
    strstripnewline (uuid);

    return strdup (uuid);
}

static char *
uuid_get_local(void)
{
    char *uuid;

    /* Check /etc/uuid / UUIDFile before any other method. */
    if ((uuid = uuid_get_from_file(uuidfile ? uuidfile : "/etc/uuid")) != NULL){
        return uuid;
    }

#if HAVE_LIBHAL
    if ((uuid = uuid_get_from_hal()) != NULL) {
        return uuid;
    }
#endif

    if ((uuid = uuid_get_from_dmidecode()) != NULL) {
        return uuid;
    }

    if ((uuid = uuid_get_from_file("/sys/hypervisor/uuid")) != NULL) {
        return uuid;
    }

    return NULL;
}

static int
uuid_config (const char *key, const char *value)
{
    if (strcasecmp (key, "UUIDFile") == 0) {
        char *tmp = strdup (value);
        if (tmp == NULL)
            return -1;
        sfree (uuidfile);
        uuidfile = tmp;
    } else {
        return 1;
    }

    return 0;
}

static int
uuid_init (void)
{
    char *uuid = uuid_get_local ();

    if (uuid) {
        sstrncpy (hostname_g, uuid, DATA_MAX_NAME_LEN);
        sfree (uuid);
        return 0;
    }

    WARNING ("uuid: could not read UUID using any known method");
    return 0;
}

void module_register (void)
{
    plugin_register_config ("uuid", uuid_config,
            config_keys, STATIC_ARRAY_SIZE (config_keys));
