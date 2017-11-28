static time_t readTime(const char *user_key, const char *sub_key)
{
    char keybuffer[TQ_BUFFERSIZE];
    DBT key, data;
    time_t t = 0;

    if ( strlen(user_key) + 1 + strlen(sub_key) + 1 > sizeof(keybuffer) ) {
        log_error("key too long (%s,%s)\n", user_key, sub_key);
    } else {
        snprintf(keybuffer, sizeof(keybuffer), "%s-%s", user_key, sub_key);

        key.data = (void *)keybuffer;
        key.size = strlen(keybuffer);
        if (db->get(db, &key, &data, 0) == 0) {
            if (data.size != sizeof(t)) {
                log_error("CORRUPTED DATABASE (%s)\n", keybuffer);
            } else {
                memcpy(&t, data.data, sizeof(t));
            }
        }
        log_debug("readTime(\"%s\")=%d\n", keybuffer, t);
    }

    return t;
}