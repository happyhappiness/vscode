httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                                  request->GetHost(),
                                  (int) request->port);