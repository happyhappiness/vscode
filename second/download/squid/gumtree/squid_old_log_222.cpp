httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
                                  base64_encode(loginbuf));