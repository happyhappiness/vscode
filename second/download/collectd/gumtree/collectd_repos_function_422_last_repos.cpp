static int nut_init(void) {
#if HAVE_UPSCLI_INIT
  if (verify_peer == 1 && force_ssl == 0) {
    WARNING("nut plugin: nut_connect: VerifyPeer true but ForceSSL "
            "false. Setting ForceSSL to true.");
    force_ssl = 1;
  }

  if (verify_peer == 1 && ca_path == NULL) {
    ERROR("nut plugin: nut_connect: VerifyPeer true but missing "
          "CAPath value.");
    plugin_unregister_read_group("nut");
    return -1;
  }

  if (verify_peer == 1 || force_ssl == 1) {
    int status = upscli_init(verify_peer, ca_path, NULL, NULL);

    if (status != 1) {
      ERROR("nut plugin: upscli_init (%i, %s) failed", verify_peer, ca_path);
      upscli_cleanup();
      plugin_unregister_read_group("nut");
      return -1;
    }
  } /* if (verify_peer == 1) */

  if (verify_peer == 1)
    ssl_flags = (UPSCLI_CONN_REQSSL | UPSCLI_CONN_CERTVERIF);
  else if (force_ssl == 1)
    ssl_flags = UPSCLI_CONN_REQSSL;

#else /* #if HAVE_UPSCLI_INIT */
  if (verify_peer == 1 || ca_path != NULL) {
    WARNING("nut plugin: nut_connect: Dependency libupsclient version "
            "insufficient (<2.7) for VerifyPeer support. Ignoring VerifyPeer "
            "and CAPath.");
    verify_peer = 0;
  }

  if (force_ssl == 1)
    ssl_flags = UPSCLI_CONN_REQSSL;
#endif

  if (connect_timeout <= 0)
    connect_timeout = (long)CDTIME_T_TO_MS(plugin_get_interval());

  return 0;
}