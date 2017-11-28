static void init_db(void)
{
    db = dbopen(db_path, O_CREAT | O_RDWR, 0666, DB_BTREE, NULL);
    if (!db) {
        fprintf(stderr, "%s: Failed to open session db '%s'\n", program_name, db_path);
        exit(1);
    }
}