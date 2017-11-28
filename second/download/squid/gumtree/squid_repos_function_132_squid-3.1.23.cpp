static void session_logout(const char *details)
{
    DBT key;
    key.data = (void *)details;
    key.size = strlen(details);
    db->del(db, &key, 0);
}