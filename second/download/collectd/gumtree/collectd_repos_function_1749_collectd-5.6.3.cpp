void module_register(void) {
  fc_register_match(
      "empty_counter",
      (match_proc_t){
          .create = mec_create, .destroy = mec_destroy, .match = mec_match,
      });
}