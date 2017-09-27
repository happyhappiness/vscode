                /* none selected yet or this one has preference */
                protocol = p;
            }
        }
    }
    if (APLOGcdebug(c)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03157)
                      "selected protocol=%s", 
                      protocol? protocol : "(none)");
    }

    return protocol;
}

