static int metric_cmp(void const *a, void const *b) {
  Io__Prometheus__Client__Metric const *m_a =
      *((Io__Prometheus__Client__Metric **)a);
  Io__Prometheus__Client__Metric const *m_b =
      *((Io__Prometheus__Client__Metric **)b);

  if (m_a->n_label < m_b->n_label)
    return -1;
  else if (m_a->n_label > m_b->n_label)
    return 1;

  /* Prometheus does not care about the order of labels. All labels in this
   * plugin are created by METRIC_ADD_LABELS(), though, and therefore always
   * appear in the same order. We take advantage of this and simplify the check
   * by making sure all labels are the same in each position.
   *
   * We also only need to check the label values, because the label names are
   * the same for all metrics in a metric family.
   *
   * 3 labels:
   * [0] $plugin="$plugin_instance" => $plugin is the same within a family
   * [1] type="$type_instance"      => "type" is a static string
   * [2] instance="$host"           => "instance" is a static string
   *
   * 2 labels, variant 1:
   * [0] $plugin="$plugin_instance" => $plugin is the same within a family
   * [1] instance="$host"           => "instance" is a static string
   *
   * 2 labels, variant 2:
   * [0] $plugin="$type_instance"   => $plugin is the same within a family
   * [1] instance="$host"           => "instance" is a static string
   *
   * 1 label:
   * [1] instance="$host"           => "instance" is a static string
   */
  for (size_t i = 0; i < m_a->n_label; i++) {
    int status = strcmp(m_a->label[i]->value, m_b->label[i]->value);
    if (status != 0)
      return status;

#if COLLECT_DEBUG
    assert(strcmp(m_a->label[i]->name, m_b->label[i]->name) == 0);
#endif
  }

  return 0;
}