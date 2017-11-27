#include "plugin.h"

#include "utils_cache.h"
#include "utils_cmd_getval.h"
#include "utils_parse_option.h"

cmd_status_t cmd_parse_getval(size_t argc, char **argv,
                              cmd_getval_t *ret_getval,
                              const cmd_options_t *opts,
                              cmd_error_handler_t *err) {
  char *identifier_copy;
  int status;

  if ((ret_getval == NULL) || (opts == NULL)) {
    errno = EINVAL;
    cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_getval.");
    return (CMD_ERROR);
  }

  if (argc != 1) {
    if (argc == 0)
      cmd_error(CMD_PARSE_ERROR, err, "Missing identifier.");
    else
      cmd_error(CMD_PARSE_ERROR, err, "Garbage after identifier: `%s'.",
                argv[1]);
    return (CMD_PARSE_ERROR);
  }

  /* parse_identifier() modifies its first argument,
   * returning pointers into it */
  identifier_copy = sstrdup(argv[0]);

  status = parse_identifier(
      argv[0], &ret_getval->identifier.host, &ret_getval->identifier.plugin,
      &ret_getval->identifier.plugin_instance, &ret_getval->identifier.type,
      &ret_getval->identifier.type_instance, opts->identifier_default_host);
  if (status != 0) {
    DEBUG("cmd_parse_getval: Cannot parse identifier `%s'.", identifier_copy);
    cmd_error(CMD_PARSE_ERROR, err, "Cannot parse identifier `%s'.",
              identifier_copy);
    sfree(identifier_copy);
    return (CMD_PARSE_ERROR);
  }

  ret_getval->raw_identifier = identifier_copy;
  return (CMD_OK);
} /* cmd_status_t cmd_parse_getval */

#define print_to_socket(fh, ...)                                               \
  do {                                                                         \
    if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
      char errbuf[1024];                                                       \
      WARNING("cmd_handle_getval: failed to write to socket #%i: %s",          \
              fileno(fh), sstrerror(errno, errbuf, sizeof(errbuf)));           \
      return -1;                                                               \
    }                                                                          \
    fflush(fh);                                                                \
  } while (0)

cmd_status_t cmd_handle_getval(FILE *fh, char *buffer) {
  cmd_error_handler_t err = {cmd_error_fh, fh};
  cmd_status_t status;
  cmd_t cmd;

  gauge_t *values;
  size_t values_num;

  const data_set_t *ds;

  if ((fh == NULL) || (buffer == NULL))
    return (-1);

  DEBUG("utils_cmd_getval: cmd_handle_getval (fh = %p, buffer = %s);",
        (void *)fh, buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return (status);
  if (cmd.type != CMD_GETVAL) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    cmd_destroy(&cmd);
    return (CMD_UNKNOWN_COMMAND);
  }

  ds = plugin_get_ds(cmd.cmd.getval.identifier.type);
  if (ds == NULL) {
    DEBUG("cmd_handle_getval: plugin_get_ds (%s) == NULL;",
          cmd.cmd.getval.identifier.type);
    cmd_error(CMD_ERROR, &err, "Type `%s' is unknown.\n",
              cmd.cmd.getval.identifier.type);
    cmd_destroy(&cmd);
    return (-1);
  }

  values = NULL;
  values_num = 0;
  status =
      uc_get_rate_by_name(cmd.cmd.getval.raw_identifier, &values, &values_num);
  if (status != 0) {
    cmd_error(CMD_ERROR, &err, "No such value.");
    cmd_destroy(&cmd);
    return (CMD_ERROR);
  }

  if (ds->ds_num != values_num) {
    ERROR("ds[%s]->ds_num = %zu, "
          "but uc_get_rate_by_name returned %zu values.",
          ds->type, ds->ds_num, values_num);
    cmd_error(CMD_ERROR, &err, "Error reading value from cache.");
    sfree(values);
    cmd_destroy(&cmd);
    return (CMD_ERROR);
  }

  print_to_socket(fh, "%zu Value%s found\n", values_num,
                  (values_num == 1) ? "" : "s");
  for (size_t i = 0; i < values_num; i++) {
    print_to_socket(fh, "%s=", ds->ds[i].name);
