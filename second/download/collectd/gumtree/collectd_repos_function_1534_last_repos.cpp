static void label_pair_destroy(Io__Prometheus__Client__LabelPair *msg) {
  if (msg == NULL)
    return;

  sfree(msg->name);
  sfree(msg->value);

  sfree(msg);
}