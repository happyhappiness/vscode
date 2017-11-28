static void init_db(void)
{
    struct stat st_buf;

    if (db_path) {
        if (!stat(db_path, &st_buf)) {
            if (S_ISDIR (st_buf.st_mode)) {
                /* If directory then open database environment. This prevents sync problems
                    between different processes. Otherwise fallback to single file */
                db_env_create(&db_env, 0);
                if (db_env->open(db_env, db_path, DB_CREATE | DB_INIT_MPOOL | DB_INIT_LOCK , 0666)) {
                    fprintf(stderr, "FATAL: %s: Failed to open database environment in '%s'\n", program_name, db_path);
                    db_env->close(db_env, 0);
                    exit(1);
                }
                db_create(&db, db_env, 0);
            }
        }
    }

    if (db_env) {
        if (db->open(db, NULL, "session", NULL, DB_BTREE, DB_CREATE, 0666)) {
            fprintf(stderr, "FATAL: %s: Failed to open db file '%s' in dir '%s'\n",
                    program_name, "session", db_path);
            db_env->close(db_env, 0);
            exit(1);
        }
    } else {
        db_create(&db, NULL, 0);
        if (db->open(db, NULL, db_path, NULL, DB_BTREE, DB_CREATE, 0666)) {
            fprintf(stderr, "FATAL: %s: Failed to open session db '%s'\n", program_name, db_path);
            exit(1);
        }
    }
}