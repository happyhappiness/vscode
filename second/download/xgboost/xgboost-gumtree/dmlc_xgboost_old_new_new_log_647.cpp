fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d,missing=%d", 
                                 nid, split_index, float(cond), 
                                 nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                 nodes[ nid ].cdefault() );