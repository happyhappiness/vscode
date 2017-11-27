static void statsd_metric_free (statsd_metric_t *metric) /* {{{ */
{
  if (metric == NULL)
    return;

  if (metric->latency != NULL)
  {
    latency_counter_destroy (metric->latency);
    metric->latency = NULL;
  }

  if (metric->set != NULL)
  {
    void *key;
    void *value;

    while (c_avl_pick (metric->set, &key, &value) == 0)
    {
      sfree (key);
      assert (value == NULL);
    }

    c_avl_destroy (metric->set);
    metric->set = NULL;
  }

  sfree (metric);
}