  vsnprintf(buffer, sizeof(buffer), format, ap);
  va_end(ap);

  printf("plugin_log (%i, \"%s\");\n", level, buffer);
}

void plugin_init_ctx(void) { /* nop */
}

plugin_ctx_t mock_context = {
    .interval = TIME_T_TO_CDTIME_T_STATIC(10),
};

plugin_ctx_t plugin_get_ctx(void) { return mock_context; }

plugin_ctx_t plugin_set_ctx(plugin_ctx_t ctx) {
  plugin_ctx_t prev = mock_context;
  mock_context = ctx;
  return prev;
}

cdtime_t plugin_get_interval(void) { return mock_context.interval; }

/* TODO(octo): this function is actually from filter_chain.h, but in order not
 * to tumble down that rabbit hole, we're declaring it here. A better solution
 * would be to hard-code the top-level config keys in daemon/collectd.c to avoid
 * having these references in daemon/configfile.c. */
int fc_configure(const oconfig_item_t *ci) { return ENOTSUP; }
