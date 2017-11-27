static Io__Prometheus__Client__LabelPair *
label_pair_clone(Io__Prometheus__Client__LabelPair const *orig) {
  Io__Prometheus__Client__LabelPair *copy = calloc(1, sizeof(*copy));
  if (copy == NULL)
    return NULL;
  io__prometheus__client__label_pair__init(copy);

  copy->name = strdup(orig->name);
  copy->value = strdup(orig->value);
  if ((copy->name == NULL) || (copy->value == NULL)) {
    label_pair_destroy(copy);
    return NULL;
  }

  return copy;
}