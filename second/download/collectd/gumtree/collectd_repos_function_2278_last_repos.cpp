static int sensors_load_conf(void) {
  static int call_once = 0;

  FILE *fh = NULL;
  featurelist_t *last_feature = NULL;

  const sensors_chip_name *chip;
  int chip_num;

  int status;

  if (call_once)
    return 0;

  call_once = 1;

  if (conffile != NULL) {
    fh = fopen(conffile, "r");
    if (fh == NULL) {
      char errbuf[1024];
      ERROR("sensors plugin: fopen(%s) failed: %s", conffile,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return -1;
    }
  }

  status = sensors_init(fh);
  if (fh)
    fclose(fh);

  if (status != 0) {
    ERROR("sensors plugin: Cannot initialize sensors. "
          "Data will not be collected.");
    return -1;
  }

#if SENSORS_API_VERSION < 0x400
  chip_num = 0;
  while ((chip = sensors_get_detected_chips(&chip_num)) != NULL) {
    int feature_num0 = 0;
    int feature_num1 = 0;

    while (42) {
      const sensors_feature_data *feature;
      int feature_type;
      featurelist_t *fl;

      feature = sensors_get_all_features(*chip, &feature_num0, &feature_num1);

      /* Check if all features have been read. */
      if (feature == NULL)
        break;

      /* "master features" only */
      if (feature->mapping != SENSORS_NO_MAPPING) {
        DEBUG("sensors plugin: sensors_load_conf: "
              "Ignoring subfeature `%s', "
              "because (feature->mapping "
              "!= SENSORS_NO_MAPPING).",
              feature->name);
        continue;
      }

      /* skip ignored in sensors.conf */
      if (sensors_get_ignored(*chip, feature->number) == 0) {
        DEBUG("sensors plugin: sensors_load_conf: "
              "Ignoring subfeature `%s', "
              "because "
              "`sensors_get_ignored' told "
              "me so.",
              feature->name);
        continue;
      }

      feature_type = sensors_feature_name_to_type(feature->name);
      if (feature_type == SENSOR_TYPE_UNKNOWN) {
        DEBUG("sensors plugin: sensors_load_conf: "
              "Ignoring subfeature `%s', "
              "because its type is "
              "unknown.",
              feature->name);
        continue;
      }

      fl = calloc(1, sizeof(*fl));
      if (fl == NULL) {
        ERROR("sensors plugin: calloc failed.");
        continue;
      }

      fl->chip = chip;
      fl->data = feature;
      fl->type = feature_type;

      if (first_feature == NULL)
        first_feature = fl;
      else
        last_feature->next = fl;
      last_feature = fl;
    } /* while sensors_get_all_features */
  }   /* while sensors_get_detected_chips */
/* #endif SENSORS_API_VERSION < 0x400 */

#elif (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500)
  chip_num = 0;
  while ((chip = sensors_get_detected_chips(NULL, &chip_num)) != NULL) {
    const sensors_feature *feature;
    int feature_num = 0;

    while ((feature = sensors_get_features(chip, &feature_num)) != NULL) {
      const sensors_subfeature *subfeature;
      int subfeature_num = 0;

      /* Only handle voltage, fanspeeds and temperatures */
      if ((feature->type != SENSORS_FEATURE_IN) &&
          (feature->type != SENSORS_FEATURE_FAN) &&
          (feature->type != SENSORS_FEATURE_TEMP) &&
#if SENSORS_API_VERSION >= 0x402
          (feature->type != SENSORS_FEATURE_CURR) &&
#endif
          (feature->type != SENSORS_FEATURE_POWER)) {
        DEBUG("sensors plugin: sensors_load_conf: "
              "Ignoring feature `%s', "
              "because its type is not "
              "supported.",
              feature->name);
        continue;
      }

      while ((subfeature = sensors_get_all_subfeatures(
                  chip, feature, &subfeature_num)) != NULL) {
        featurelist_t *fl;

        if ((subfeature->type != SENSORS_SUBFEATURE_IN_INPUT) &&
            (subfeature->type != SENSORS_SUBFEATURE_FAN_INPUT) &&
            (subfeature->type != SENSORS_SUBFEATURE_TEMP_INPUT) &&
#if SENSORS_API_VERSION >= 0x402
            (subfeature->type != SENSORS_SUBFEATURE_CURR_INPUT) &&
#endif
            (subfeature->type != SENSORS_SUBFEATURE_POWER_INPUT))
          continue;

        fl = calloc(1, sizeof(*fl));
        if (fl == NULL) {
          ERROR("sensors plugin: calloc failed.");
          continue;
        }

        fl->chip = chip;
        fl->feature = feature;
        fl->subfeature = subfeature;

        if (first_feature == NULL)
          first_feature = fl;
        else
          last_feature->next = fl;
        last_feature = fl;
      } /* while (subfeature) */
    }   /* while (feature) */
  }     /* while (chip) */
#endif /* (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500) */

  if (first_feature == NULL) {
    sensors_cleanup();
    INFO("sensors plugin: lm_sensors reports no "
         "features. Data will not be collected.");
    return -1;
  }

  return 0;
}