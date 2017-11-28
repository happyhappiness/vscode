static void shutdown_db(void)
{
    db->close(db);
}