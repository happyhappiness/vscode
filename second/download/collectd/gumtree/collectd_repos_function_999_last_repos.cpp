static int pmatch_destroy(void **user_data) {
  return fc_destroy(FC_MATCH, user_data);
}