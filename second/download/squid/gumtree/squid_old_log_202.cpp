storeAppendPrintf(sentry, "number active: %d of %d (%d shutting down)\n",
                      hlp->n_active, hlp->n_to_start, (hlp->n_running - hlp->n_active) );