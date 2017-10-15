m_canvas->print(84, pos, "%i - %i %c%c",
                    e->range().first,
                    e->range().first != e->range().second ? (e->range().second - 1) : e->range().second,
                    e->is_created() ? 'E' : 'M',
                    e->is_correct_size() ? 'C' : 'W');