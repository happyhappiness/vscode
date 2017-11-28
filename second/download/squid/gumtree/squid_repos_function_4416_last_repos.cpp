static void session_login(const char *details, size_t len)
{
    DBT key = {0};
    DBT data = {0};
    key.data = (void *)details;
    key.size = len;
    time_t now = time(NULL);
    data.data = &now;
    data.size = sizeof(now);
    db->put(db, NULL, &key, &data, 0);
}