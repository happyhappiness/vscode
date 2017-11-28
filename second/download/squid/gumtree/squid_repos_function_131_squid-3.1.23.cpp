static void session_login(const char *details)
{
    DBT key, data;
    time_t now = time(NULL);
    key.data = (void *)details;
    key.size = strlen(details);
    data.data = &now;
    data.size = sizeof(now);
    db->put(db, &key, &data, 0);
}