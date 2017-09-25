ap_fputstrs(output, bb,
                  "<D:status>HTTP/1.1 ",
                  ap_get_status_line(response->status),
                  "</D:status>" DEBUG_CR,
                  NULL);