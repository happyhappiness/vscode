static void session_logout(const char *details, size_t len)
{
    DBT key = {0};
    key.data = (void *)details;
    key.size = len;
    db->del(db, NULL, &key, 0);
}