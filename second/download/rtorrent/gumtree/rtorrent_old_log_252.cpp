m_canvas->print(x, y, "%c/%c%c/%c%c",
                    p.is_incoming() ? 'r' : 'l',
                    p.is_remote_choked() ? 'c' : 'u',
                    p.is_remote_interested() ? 'i' : 'n',
                    p.is_local_choked() ? 'c' : 'u',
                    p.is_local_interested() ? 'i' : 'n');