#include "plugin.h"

#include "utils_cache.h"
#include "utils_cmd_listval.h"
#include "utils_parse_option.h"

cmd_status_t cmd_parse_listval(size_t argc, char **argv,
                               cmd_listval_t *ret_listval
                               __attribute__((unused)),
                               const cmd_options_t *opts
                               __attribute__((unused)),
                               cmd_error_handler_t *err) {
  if (argc != 0) {
    cmd_error(CMD_PARSE_ERROR, err, "Garbage after end of command: `%s'.",
              argv[0]);
    return (CMD_PARSE_ERROR);
  }

  return (CMD_OK);
} /* cmd_status_t cmd_parse_listval */

#define free_everything_and_return(status)                                     \
  do {                                                                         \
    for (size_t j = 0; j < number; j++) {                                      \
      sfree(names[j]);                                                         \
      names[j] = NULL;                                                         \
    }                                                                          \
