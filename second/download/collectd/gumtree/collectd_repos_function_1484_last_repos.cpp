static int notify_email_config(const char *key, const char *value) {
  if (strcasecmp(key, "Recipient") == 0) {
    char **tmp;

    tmp = realloc(recipients, (recipients_len + 1) * sizeof(char *));
    if (tmp == NULL) {
      ERROR("notify_email: realloc failed.");
      return -1;
    }

    recipients = tmp;
    recipients[recipients_len] = strdup(value);
    if (recipients[recipients_len] == NULL) {
      ERROR("notify_email: strdup failed.");
      return -1;
    }
    recipients_len++;
  } else if (0 == strcasecmp(key, "SMTPServer")) {
    sfree(smtp_host);
    smtp_host = strdup(value);
  } else if (0 == strcasecmp(key, "SMTPPort")) {
    int port_tmp = atoi(value);
    if (port_tmp < 1 || port_tmp > 65535) {
      WARNING("notify_email plugin: Invalid SMTP port: %i", port_tmp);
      return 1;
    }
    smtp_port = port_tmp;
  } else if (0 == strcasecmp(key, "SMTPUser")) {
    sfree(smtp_user);
    smtp_user = strdup(value);
  } else if (0 == strcasecmp(key, "SMTPPassword")) {
    sfree(smtp_password);
    smtp_password = strdup(value);
  } else if (0 == strcasecmp(key, "From")) {
    sfree(email_from);
    email_from = strdup(value);
  } else if (0 == strcasecmp(key, "Subject")) {
    sfree(email_subject);
    email_subject = strdup(value);
  } else {
    return -1;
  }
  return 0;
}