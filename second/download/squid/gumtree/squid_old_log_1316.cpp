httpHeaderPutStrf(hdr, HDR_X_CACHE_LOOKUP, "%s from %s:%d",
                      lookup_type ? lookup_type : "NONE",
                      getMyHostname(), getMyPort());