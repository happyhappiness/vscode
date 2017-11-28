storeAppendPrintf(&e, "Writers:         %9d %6.2f%% including Appenders: %9d %6.2f%%\n",
                          writers, (100.0 * writers / locked),
                          appenders, appPerc);