static yajl_gen_status ovs_yajl_gen_tstring(yajl_gen hander,
                                            const char *string) {
  return yajl_gen_string(hander, (const unsigned char *)string, strlen(string));
}