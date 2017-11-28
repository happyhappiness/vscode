httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
                              base64_encode(orig_request->peer_login));