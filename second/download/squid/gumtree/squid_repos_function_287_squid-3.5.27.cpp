static void init_db(void)
{
    log_info("opening time quota database \"%s\".\n", db_path);
    db = dbopen(db_path, O_CREAT | O_RDWR, 0666, DB_BTREE, NULL);
    if (!db) {
        log_fatal("Failed to open time_quota db '%s'\n", db_path);
        exit(1);
    }
}