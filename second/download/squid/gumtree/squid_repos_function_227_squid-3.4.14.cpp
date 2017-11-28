static void writeTime(const char *user_key, const char *sub_key, time_t t)
{
    char keybuffer[TQ_BUFFERSIZE];
    DBT key, data;

    if ( strlen(user_key) + strlen(sub_key) + 1 + 1 > sizeof(keybuffer) ) {
        log_error("key too long (%s,%s)\n", user_key, sub_key);
    } else {
        snprintf(keybuffer, sizeof(keybuffer), "%s-%s", user_key, sub_key);

        key.data = (void *)keybuffer;
        key.size = strlen(keybuffer);
        data.data = &t;
        data.size = sizeof(t);
        db->put(db, &key, &data, 0);
        log_debug("writeTime(\"%s\", %d)\n", keybuffer, t);
    }
}