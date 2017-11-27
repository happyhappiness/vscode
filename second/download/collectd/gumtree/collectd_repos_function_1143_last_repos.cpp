static int cna_submit_volume_usage_data(const char *hostname, /* {{{ */
                                        cfg_volume_usage_t *cfg_volume,
                                        int interval) {
  for (data_volume_usage_t *v = cfg_volume->volumes; v != NULL; v = v->next) {
    char plugin_instance[DATA_MAX_NAME_LEN];

    uint64_t norm_used = v->norm_used;
    uint64_t norm_free = v->norm_free;
    uint64_t sis_saved = v->sis_saved;
    uint64_t compress_saved = v->compress_saved;
    uint64_t dedup_saved = v->dedup_saved;
    uint64_t snap_reserve_used = 0;
    uint64_t snap_reserve_free = v->snap_reserved;
    uint64_t snap_norm_used = v->snap_used;

    snprintf(plugin_instance, sizeof(plugin_instance), "volume-%s", v->name);

    if (HAS_ALL_FLAGS(v->flags,
                      HAVE_VOLUME_USAGE_SNAP_USED |
                          HAVE_VOLUME_USAGE_SNAP_RSVD)) {
      if (v->snap_reserved > v->snap_used) {
        snap_reserve_free = v->snap_reserved - v->snap_used;
        snap_reserve_used = v->snap_used;
        snap_norm_used = 0;
      } else {
        snap_reserve_free = 0;
        snap_reserve_used = v->snap_reserved;
        snap_norm_used = v->snap_used - v->snap_reserved;
      }
    }

    /* The space used by snapshots but not reserved for them is included in
     * both, norm_used and snap_norm_used. If possible, subtract this here. */
    if (HAS_ALL_FLAGS(v->flags,
                      HAVE_VOLUME_USAGE_NORM_USED |
                          HAVE_VOLUME_USAGE_SNAP_USED)) {
      if (norm_used >= snap_norm_used)
        norm_used -= snap_norm_used;
      else {
        ERROR("netapp plugin: (norm_used = %" PRIu64 ") < (snap_norm_used = "
              "%" PRIu64 ") for host %s. Invalidating both.",
              norm_used, snap_norm_used, hostname);
        v->flags &=
            ~(HAVE_VOLUME_USAGE_NORM_USED | HAVE_VOLUME_USAGE_SNAP_USED);
      }
    }

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_NORM_FREE))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "free", (double)norm_free,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_SIS_SAVED))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "sis_saved", (double)sis_saved,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_COMPRESS_SAVED))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "compression_saved", (double)compress_saved,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_DEDUP_SAVED))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "dedup_saved", (double)dedup_saved,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_NORM_USED))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "used", (double)norm_used,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_SNAP_RSVD))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "snap_reserved", (double)snap_reserve_free,
                    /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags,
                      HAVE_VOLUME_USAGE_SNAP_USED |
                          HAVE_VOLUME_USAGE_SNAP_RSVD))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "snap_reserve_used",
                    (double)snap_reserve_used, /* timestamp = */ 0, interval);

    if (HAS_ALL_FLAGS(v->flags, HAVE_VOLUME_USAGE_SNAP_USED))
      submit_double(hostname, /* plugin instance = */ plugin_instance,
                    "df_complex", "snap_normal_used", (double)snap_norm_used,
                    /* timestamp = */ 0, interval);

    /* Clear all the HAVE_* flags */
    v->flags &= ~HAVE_VOLUME_USAGE_ALL;
  } /* for (v = cfg_volume->volumes) */

  return 0;
}