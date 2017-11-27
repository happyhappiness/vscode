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