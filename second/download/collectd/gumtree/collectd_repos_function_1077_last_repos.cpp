static int parse_memory_info(FILE *p_file, mcelog_memory_rec_t *memory_record) {
  char buf[DATA_MAX_NAME_LEN] = {0};
  while (fgets(buf, sizeof(buf), p_file)) {
    /* Got empty line or "done" */
    if ((!strncmp("\n", buf, strlen(buf))) ||
        (!strncmp(buf, "done\n", strlen(buf))))
      return 1;
    if (strlen(buf) < 5)
      continue;
    if (!strncmp(buf, MCELOG_SOCKET_STR, strlen(MCELOG_SOCKET_STR))) {
      sstrncpy(memory_record->location, buf, strlen(buf));
      /* replace spaces with '_' */
      for (size_t i = 0; i < strlen(memory_record->location); i++)
        if (memory_record->location[i] == ' ')
          memory_record->location[i] = '_';
      DEBUG(MCELOG_PLUGIN ": Got SOCKET INFO %s", memory_record->location);
    }
    if (!strncmp(buf, MCELOG_DIMM_NAME, strlen(MCELOG_DIMM_NAME))) {
      char *name = NULL;
      char *saveptr = NULL;
      name = strtok_r(buf, "\"", &saveptr);
      if (name != NULL && saveptr != NULL) {
        name = strtok_r(NULL, "\"", &saveptr);
        if (name != NULL) {
          sstrncpy(memory_record->dimm_name, name,
                   sizeof(memory_record->dimm_name));
          DEBUG(MCELOG_PLUGIN ": Got DIMM NAME %s", memory_record->dimm_name);
        }
      }
    }
    if (!strncmp(buf, MCELOG_CORRECTED_ERR, strlen(MCELOG_CORRECTED_ERR))) {
      /* Get next line*/
      if (fgets(buf, sizeof(buf), p_file) != NULL) {
        sscanf(buf, "\t%d total", &(memory_record->corrected_err_total));
        DEBUG(MCELOG_PLUGIN ": Got corrected error total %d",
              memory_record->corrected_err_total);
      }
      if (fgets(buf, sizeof(buf), p_file) != NULL) {
        sscanf(buf, "\t%d in %s", &(memory_record->corrected_err_timed),
               memory_record->corrected_err_timed_period);
        DEBUG(MCELOG_PLUGIN ": Got timed corrected errors %d in %s",
              memory_record->corrected_err_total,
              memory_record->corrected_err_timed_period);
      }
    }
    if (!strncmp(buf, MCELOG_UNCORRECTED_ERR, strlen(MCELOG_UNCORRECTED_ERR))) {
      if (fgets(buf, sizeof(buf), p_file) != NULL) {
        sscanf(buf, "\t%d total", &(memory_record->uncorrected_err_total));
        DEBUG(MCELOG_PLUGIN ": Got uncorrected error total %d",
              memory_record->uncorrected_err_total);
      }
      if (fgets(buf, sizeof(buf), p_file) != NULL) {
        sscanf(buf, "\t%d in %s", &(memory_record->uncorrected_err_timed),
               memory_record->uncorrected_err_timed_period);
        DEBUG(MCELOG_PLUGIN ": Got timed uncorrected errors %d in %s",
              memory_record->uncorrected_err_total,
              memory_record->uncorrected_err_timed_period);
      }
    }
    memset(buf, 0, sizeof(buf));
  }
  /* parsing definitely finished */
  return 0;
}