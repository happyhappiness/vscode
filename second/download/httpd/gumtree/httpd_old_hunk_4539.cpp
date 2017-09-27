        }
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, 
                  "link_reverse_map %s --> %s", s, ctx.s);
    return ctx.s;
}
