m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
                    rak::copy_escape_html(tracker.tracker_id()).c_str(),
                    range.first == tl->focus() ? "yes" : " no",
                    tracker.is_enabled() ? "yes" : " no",
                    tracker.is_open() ? "yes" : " no",
                    tracker.scrape_complete(),
                    tracker.scrape_incomplete());