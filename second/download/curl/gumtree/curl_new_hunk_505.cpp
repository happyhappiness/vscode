  long alivetime;
  bool content_disposition; /* use Content-disposition filename */

  int default_node_flags; /* default flags to seach for each 'node', which is
                             basically each given URL to transfer */
  struct OutStruct *outs;
  bool xattr; /* store metadata in extended attributes */
};

#define WARN_PREFIX "Warning: "
#define WARN_TEXTWIDTH (79 - (int)strlen(WARN_PREFIX))
/* produce this text message to the user unless mute was selected */
static void warnf(struct Configurable *config, const char *fmt, ...)
