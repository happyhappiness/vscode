static void traffic_submit(derive_t rx, derive_t tx, mysql_database_t *db) {
  value_t values[] = {
      {.derive = rx}, {.derive = tx},
  };

  submit("mysql_octets", NULL, values, STATIC_ARRAY_SIZE(values), db);
}