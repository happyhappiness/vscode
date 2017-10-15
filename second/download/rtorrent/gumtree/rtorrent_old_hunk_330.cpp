    if (tracker->group() == group)
      m_canvas->print(0, pos, "%2i:", group++);

    m_canvas->print(4, pos++, "%s",
                    tracker->url().c_str());

    if (pos < m_canvas->height())
      m_canvas->print(0, pos++, "%s Id: %s Counters: %uf / %us (%u) %s S/L/D: %u/%u/%u (%u/%u)",
                      tracker->is_busy() ? "req " : "    ",
                      rak::copy_escape_html(tracker->tracker_id()).c_str(),
                      tracker->failed_counter(),
                      tracker->success_counter(),
                      tracker->scrape_counter(),
                      tracker->is_usable() ? " on" : tracker->is_enabled() ? "err" : "off",
                      tracker->scrape_complete(),
                      tracker->scrape_incomplete(),
                      tracker->scrape_downloaded(),
                      tracker->latest_new_peers(),
                      tracker->latest_sum_peers());

    if (range.first == *m_focus) {
      m_canvas->set_attr(4, pos - 2, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
      m_canvas->set_attr(4, pos - 1, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
    }

