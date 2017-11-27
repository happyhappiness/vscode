static Io__Prometheus__Client__MetricFamily *
metric_family_get(data_set_t const *ds, value_list_t const *vl, size_t ds_index,
                  _Bool allocate) {
  char *name = metric_family_name(ds, vl, ds_index);
  if (name == NULL) {
    ERROR("write_prometheus plugin: Allocating metric family name failed.");
    return NULL;
  }

  Io__Prometheus__Client__MetricFamily *fam = NULL;
  if (c_avl_get(metrics, name, (void *)&fam) == 0) {
    sfree(name);
    assert(fam != NULL);
    return fam;
  }

  if (!allocate) {
    sfree(name);
    return NULL;
  }

  fam = metric_family_create(name, ds, vl, ds_index);
  if (fam == NULL) {
    ERROR("write_prometheus plugin: Allocating metric family failed.");
    sfree(name);
    return NULL;
  }

  /* If successful, "name" is owned by "fam", i.e. don't free it here. */
  DEBUG("write_prometheus plugin: metric family \"%s\" has been created.",
        name);
  name = NULL;

  int status = c_avl_insert(metrics, fam->name, fam);
  if (status != 0) {
    ERROR("write_prometheus plugin: Adding \"%s\" failed.", name);
    metric_family_destroy(fam);
    return NULL;
  }

  return fam;
}