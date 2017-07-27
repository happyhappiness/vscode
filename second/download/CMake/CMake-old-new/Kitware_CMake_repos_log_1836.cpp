len += snprintf(buf + len, GSS_LOG_BUFFER_LEN - len,
                      "%.*s. ", (int)status_string.length,
                      (char *)status_string.value);