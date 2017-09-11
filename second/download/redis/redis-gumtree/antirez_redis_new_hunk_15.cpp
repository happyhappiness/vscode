    serverLogRaw(level,msg);
}

/* Produces a log message to the standard Redis log, the format accepts
 * printf-alike specifiers, while level is a string describing the log
 * level to use when emitting the log, and must be one of the following:
 *
