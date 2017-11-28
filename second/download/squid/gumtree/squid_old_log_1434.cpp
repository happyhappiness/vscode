httpHeaderPutStrf(hdr_out, header, "Basic %s",
                      old_base64_encode(request->peer_login));