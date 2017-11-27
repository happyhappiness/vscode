static void gauge_submit(const char *type, const char *type_instance,
                         gauge_t value, mysql_database_t *db) {
  submit(type, type_instance, &(value_t){.gauge = value}, 1, db);
}