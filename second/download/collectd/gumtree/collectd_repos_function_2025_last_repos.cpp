static int ntpd_do_query(int req_code, int req_items, int req_size,
                         char *req_data, int *res_items, int *res_size,
                         char **res_data, int res_item_size) {
  int status;

  status = ntpd_send_request(req_code, req_items, req_size, req_data);
  if (status != 0)
    return status;

  status = ntpd_receive_response(res_items, res_size, res_data, res_item_size);
  return status;
}