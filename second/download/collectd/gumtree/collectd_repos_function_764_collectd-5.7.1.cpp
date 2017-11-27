static int direct_list_insert(const char *config) {
  regmatch_t pmatch[3];
  size_t nmatch = 3;
  direct_access_element_t *element;

  DEBUG("onewire plugin: direct_list_insert <%s>", config);

  element = malloc(sizeof(*element));
  if (element == NULL) {
    ERROR("onewire plugin: direct_list_insert - cannot allocate element");
    return 1;
  }
  element->path = NULL;
  element->address = NULL;
  element->file = NULL;

  element->path = strdup(config);
  if (element->path == NULL) {
    ERROR("onewire plugin: direct_list_insert - cannot allocate path");
    direct_list_element_free(element);
    return 1;
  }

  DEBUG("onewire plugin: direct_list_insert - about to match %s", config);

  if (!regex_direct_initialized) {
    if (regcomp(&regex_direct, regexp_to_match, REG_EXTENDED)) {
      ERROR("onewire plugin: Cannot compile regex");
      direct_list_element_free(element);
      return (1);
    }
    regex_direct_initialized = 1;
    DEBUG("onewire plugin: Compiled regex!!");
  }

  if (regexec(&regex_direct, config, nmatch, pmatch, 0)) {
    ERROR("onewire plugin: direct_list_insert - no regex  match");
    direct_list_element_free(element);
    return 1;
  }

  if (pmatch[1].rm_so < 0) {
    ERROR("onewire plugin: direct_list_insert - no address regex match");
    direct_list_element_free(element);
    return 1;
  }
  element->address =
      strndup(config + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
  if (element->address == NULL) {
    ERROR("onewire plugin: direct_list_insert - cannot allocate address");
    direct_list_element_free(element);
    return 1;
  }
  DEBUG("onewire plugin: direct_list_insert - found address <%s>",
        element->address);

  if (pmatch[2].rm_so < 0) {
    ERROR("onewire plugin: direct_list_insert - no file regex match");
    direct_list_element_free(element);
    return 1;
  }
  element->file =
      strndup(config + pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
  if (element->file == NULL) {
    ERROR("onewire plugin: direct_list_insert - cannot allocate file");
    direct_list_element_free(element);
    return 1;
  }
  DEBUG("onewire plugin: direct_list_insert - found file <%s>", element->file);

  element->next = direct_list;
  direct_list = element;

  return 0;
}