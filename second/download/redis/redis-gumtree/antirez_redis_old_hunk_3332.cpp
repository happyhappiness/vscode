    if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
}

/* Redis generally does not try to recover from out of memory conditions
 * when allocating objects or strings, it is not clear if it will be possible
 * to report this condition to the client since the networking layer itself
