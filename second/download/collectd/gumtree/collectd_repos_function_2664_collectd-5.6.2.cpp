static int my_notify(const notification_t *notif, user_data_t *ud) {
  char time_str[32] = "";
  struct tm *tm = NULL;

  int n = 0;

  if (NULL == (tm = localtime(&notif->time)))
    time_str[0] = '\0';

  n = strftime(time_str, 32, "%F %T", tm);
  if (n >= 32)
    n = 31;
  time_str[n] = '\0';

  printf("NOTIF (%s): %i - ", time_str, notif->severity);

  if ('\0' != *notif->host)
    printf("%s: ", notif->host);

  if ('\0' != *notif->plugin)
    printf("%s: ", notif->plugin);

  if ('\0' != *notif->plugin_instance)
    printf("%s: ", notif->plugin_instance);

  if ('\0' != *notif->type)
    printf("%s: ", notif->type);

  if ('\0' != *notif->type_instance)
    printf("%s: ", notif->type_instance);

  printf("%s\n", notif->message);
  return 0;
}