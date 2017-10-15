m_canvas->print(x, y, "%c%c/%c%c/%c%c",
                    p->is_encrypted() ? (p->is_incoming() ? 'R' : 'L') : (p->is_incoming() ? 'r' : 'l'),
                    peerType,
                    p->is_down_choked() ? std::tolower(remoteChoked) : remoteChoked,

                    p->is_down_interested() ? 'i' : 'n',
                    p->is_up_choked() ? 'c' : 'u',
                    p->is_up_interested() ? 'i' : 'n');