m_canvas->print(2, pos, "Trackers: [Key: %08x] [%s %s %s]",
                  tl->key(),
                  tc->is_requesting() ? "req" : "   ",
                  tc->is_promiscuous_mode() ? "prom" : "    ",
                  tc->is_failure_mode() ? "fail" : "    ");