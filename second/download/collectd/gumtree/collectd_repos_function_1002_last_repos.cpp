static int ptarget_destroy(void **user_data) {
  return fc_destroy(FC_TARGET, user_data);
}