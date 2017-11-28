static int session_active(const char *details, size_t len)
{
    DBT key = {0};
    DBT data = {0};
    key.data = (void *)details;
    key.size = len;
    if (db->get(db, NULL, &key, &data, 0) == 0) {
        time_t timestamp;
        if (data.size != sizeof(timestamp)) {
            fprintf(stderr, "ERROR: %s: CORRUPTED DATABASE (%s)\n", program_name, details);
            db->del(db, NULL, &key, 0);
            return 0;
        }
        memcpy(&timestamp, data.data, sizeof(timestamp));
        if (timestamp + session_ttl >= time(NULL))
            return 1;
    }
    return 0;
}