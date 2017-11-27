#include "plugin.h"

#include "utils_cache.h"
#include "utils_cmd_listval.h"
#include "utils_parse_option.h"

#define free_everything_and_return(status)                                     \
  do {                                                                         \
    for (size_t j = 0; j < number; j++) {                                      \
      sfree(names[j]);                                                         \
      names[j] = NULL;                                                         \
    }                                                                          \
