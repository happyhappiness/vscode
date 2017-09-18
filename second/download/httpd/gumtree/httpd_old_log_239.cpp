r(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL, 
            "dont_fiddle_headers=%d use_rvsa=%d ua_supports_trans=%d "
            "send_alternates=%d, may_choose=%d",
            neg->dont_fiddle_headers, neg->use_rvsa,  
            neg->ua_supports_trans, neg->send_alternates, neg->may_choose);