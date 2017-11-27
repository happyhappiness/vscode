              le->key, status);
    }

    le = le->next;
  }

  return (0);
} /* int plugin_dispatch_notification */

void plugin_log(int level, const char *format, ...) {
  char msg[1024];
  va_list ap;
  llentry_t *le;
