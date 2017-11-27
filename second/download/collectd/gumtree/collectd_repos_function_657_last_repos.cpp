static int cjni_config_add_jvm_arg(oconfig_item_t *ci) /* {{{ */
{
  char **tmp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("java plugin: `JVMArg' needs exactly one string argument.");
    return -1;
  }

  if (jvm != NULL) {
    ERROR("java plugin: All `JVMArg' options MUST appear before all "
          "`LoadPlugin' options! The JVM is already started and I have to "
          "ignore this argument: %s",
          ci->values[0].value.string);
    return -1;
  }

  tmp = realloc(jvm_argv, sizeof(char *) * (jvm_argc + 1));
  if (tmp == NULL) {
    ERROR("java plugin: realloc failed.");
    return -1;
  }
  jvm_argv = tmp;

  jvm_argv[jvm_argc] = strdup(ci->values[0].value.string);
  if (jvm_argv[jvm_argc] == NULL) {
    ERROR("java plugin: strdup failed.");
    return -1;
  }
  jvm_argc++;

  return 0;
}