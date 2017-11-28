storeAppendPrintf(sentry, "\tNot-Modified Replies: %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.not_modified_replies5[i] / fct,
                          stats.not_modified_replies60[i] / fct);