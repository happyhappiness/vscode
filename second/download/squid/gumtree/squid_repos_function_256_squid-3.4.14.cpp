static void shutdown_db(void)
{
    db->close(db, 0);
    if (db_env) {
        db_env->close(db_env, 0);
    }
}