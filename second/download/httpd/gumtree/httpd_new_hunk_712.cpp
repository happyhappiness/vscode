{ "ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF, TAKE1,
  "Number of threads each child creates" },
{ NULL }
};


/*
 * Signalling Apache on NT.
 *
 * Under Unix, Apache can be told to shutdown or restart by sending various
 * signals (HUP, USR, TERM). On NT we don't have easy access to signals, so
 * we use "events" instead. The parent apache process goes into a loop
