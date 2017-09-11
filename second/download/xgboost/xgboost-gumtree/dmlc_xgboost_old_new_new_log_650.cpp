fprintf( fo, "%d:[%s<%f] yes=%d,no=%d,missing=%d", 
                                     nid, fmap.name(split_index), float(cond), 
                                     nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                     nodes[ nid ].cdefault() );