                backgroundRewriteDoneHandler(exitcode,bysignal);
            } else {
                serverLog(LL_WARNING,
                    "Warning, detected child with unmatched pid: %ld",
                    (long)pid);
            }
            updateDictResizePolicy();
