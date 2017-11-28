httpHeaderPutStrf(hdr, Http::HdrType::X_CACHE, "%s from %s",
                      is_hit ? "HIT" : "MISS", getMyHostname());