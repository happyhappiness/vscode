httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                              orig_request->GetHost(),
                              (int) orig_request->port);