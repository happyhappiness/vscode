fprintf( fo, "%d:[%s<%d] yes=%d,no=%d,missing=%d", 
                                     nid, fmap.name(split_index), int( float(cond)+1.0f), 
                                     nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                     nodes[ nid ].cdefault() );