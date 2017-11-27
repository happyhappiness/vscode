static void derive_submit(const char *type, const char *type_instance,
                          derive_t value, mysql_database_t *db) {
  submit(type, type_instance, &(value_t){.derive = value}, 1, db);
}