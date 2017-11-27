static int sensors_feature_name_to_type(const char *name) {
  /* Yes, this is slow, but it's only ever done during initialization, so
   * it's a one time cost.. */
  for (int i = 0; i < known_features_num; i++)
    if (strcasecmp(known_features[i].label, name) == 0)
      return (known_features[i].type);

  return (SENSOR_TYPE_UNKNOWN);
}