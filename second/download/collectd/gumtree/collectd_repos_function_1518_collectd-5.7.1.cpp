static char *format_labels(char *buffer, size_t buffer_size,
                           Io__Prometheus__Client__Metric const *m) {
  /* our metrics always have at least one and at most three labels. */
  assert(m->n_label >= 1);
  assert(m->n_label <= 3);

#define LABEL_KEY_SIZE DATA_MAX_NAME_LEN
#define LABEL_VALUE_SIZE (2 * DATA_MAX_NAME_LEN - 1)
#define LABEL_BUFFER_SIZE (LABEL_KEY_SIZE + LABEL_VALUE_SIZE + 4)

  char *labels[3] = {
      (char[LABEL_BUFFER_SIZE]){0}, (char[LABEL_BUFFER_SIZE]){0},
      (char[LABEL_BUFFER_SIZE]){0},
  };

  /* N.B.: the label *names* are hard-coded by this plugin and therefore we
   * know that they are sane. */
  for (size_t i = 0; i < m->n_label; i++) {
    char value[LABEL_VALUE_SIZE];
    ssnprintf(labels[i], LABEL_BUFFER_SIZE, "%s=\"%s\"", m->label[i]->name,
              escape_label_value(value, sizeof(value), m->label[i]->value));
  }

  strjoin(buffer, buffer_size, labels, m->n_label, ",");
  return buffer;
}