static procstat_t *ps_list_register(const char *name, const char *regexp) {
  procstat_t *new;
  procstat_t *ptr;
  int status;

  new = calloc(1, sizeof(*new));
  if (new == NULL) {
    ERROR("processes plugin: ps_list_register: calloc failed.");
    return NULL;
  }
  sstrncpy(new->name, name, sizeof(new->name));

  new->io_rchar = -1;
  new->io_wchar = -1;
  new->io_syscr = -1;
  new->io_syscw = -1;
  new->io_diskr = -1;
  new->io_diskw = -1;
  new->cswitch_vol = -1;
  new->cswitch_invol = -1;

  new->report_fd_num = report_fd_num;
  new->report_maps_num = report_maps_num;
  new->report_ctx_switch = report_ctx_switch;

#if HAVE_REGEX_H
  if (regexp != NULL) {
    DEBUG("ProcessMatch: adding \"%s\" as criteria to process %s.", regexp,
          name);
    new->re = malloc(sizeof(*new->re));
    if (new->re == NULL) {
      ERROR("processes plugin: ps_list_register: malloc failed.");
      sfree(new);
      return NULL;
    }

    status = regcomp(new->re, regexp, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
      DEBUG("ProcessMatch: compiling the regular expression \"%s\" failed.",
            regexp);
      sfree(new->re);
      sfree(new);
      return NULL;
    }
  }
#else
  if (regexp != NULL) {
    ERROR("processes plugin: ps_list_register: "
          "Regular expression \"%s\" found in config "
          "file, but support for regular expressions "
          "has been disabled at compile time.",
          regexp);
    sfree(new);
    return NULL;
  }
#endif

  for (ptr = list_head_g; ptr != NULL; ptr = ptr->next) {
    if (strcmp(ptr->name, name) == 0) {
      WARNING("processes plugin: You have configured more "
              "than one `Process' or "
              "`ProcessMatch' with the same name. "
              "All but the first setting will be "
              "ignored.");
#if HAVE_REGEX_H
      sfree(new->re);
#endif
      sfree(new);
      return NULL;
    }

    if (ptr->next == NULL)
      break;
  }

  if (ptr == NULL)
    list_head_g = new;
  else
    ptr->next = new;

  return new;
}