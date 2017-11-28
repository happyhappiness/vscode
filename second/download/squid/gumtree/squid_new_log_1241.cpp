storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                          name,
                          head->pattern.flags&REG_ICASE ? " -i" : null_string,
                          head->pattern.c_str(),
                          (int) head->min / 60,
                          (int) (100.0 * head->pct + 0.5),
                          (int) head->max / 60);