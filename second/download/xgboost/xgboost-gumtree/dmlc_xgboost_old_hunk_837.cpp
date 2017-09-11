                    const unsigned split_index = nodes[ nid ].split_index();

                    if( split_index < fmap.size() ){
                        if( fmap.type(split_index) == utils::FeatMap::kIndicator ){
                            int nyes = nodes[ nid ].default_left()?nodes[nid].cright():nodes[nid].cleft();
                            fprintf( fo, "%d:[%s] yes=%d,no=%d", 
                                     nid, fmap.name( split_index ),
                                     nyes, nodes[nid].cdefault() );                            
                        }else{
                            fprintf( fo, "%d:[%s<%f] yes=%d,no=%d,missing=%d", 
                                     nid, fmap.name(split_index), float(cond), 
                                     nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                     nodes[ nid ].cdefault() );
                        }
                    }else{
                        fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d,missing=%d", 
