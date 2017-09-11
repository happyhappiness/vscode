                backgroundRewriteDoneHandler(exitcode,bysignal);
            } else {
                serverLog(LL_WARNING,
                    "Warning, detected child with unmatched pid: %ld"
                    " (EVAL forked debugging session?)",
                    (long)pid);
            }
            updateDictResizePolicy();
