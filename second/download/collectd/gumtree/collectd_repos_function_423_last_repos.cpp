static int nut_shutdown(void) {
#if HAVE_UPSCLI_INIT
  upscli_cleanup();
#endif

  return 0;
}