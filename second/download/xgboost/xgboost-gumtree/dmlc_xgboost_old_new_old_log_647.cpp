fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d\n", nid, 
                             nodes[ nid ].split_index(), float(cond), nodes[ nid ].cleft(), nodes[ nid ].cright() );