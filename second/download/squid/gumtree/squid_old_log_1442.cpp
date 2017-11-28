httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
                              old_base64_encode(request->login));