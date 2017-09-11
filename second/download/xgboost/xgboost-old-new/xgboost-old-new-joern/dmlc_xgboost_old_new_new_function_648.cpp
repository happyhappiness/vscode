void Dump( int nid, FILE *fo, const utils::FeatMap& fmap, int depth, bool with_stats ){
                for( int  i = 0;  i < depth; ++ i ){
                    fprintf( fo, "\t" );
                }
                if( nodes[ nid ].is_leaf() ){
                    fprintf( fo, "%d:leaf=%f ", nid, nodes[ nid ].leaf_value() );
                    if( with_stats ){
                        stat( nid ).Print( fo, true );
                    }
                    fprintf( fo, "\n" );
                }else{
                    // right then left,
                    TSplitCond cond = nodes[ nid ].split_cond();
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
                                 nid, split_index, float(cond), 
                                 nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                 nodes[ nid ].cdefault() );
                    }
                    if( with_stats ){
                        fprintf( fo, " ");
                        stat( nid ).Print( fo, false );
                    }
                    fprintf( fo, "\n" );
                    this->Dump( nodes[ nid ].cleft(), fo, fmap, depth+1, with_stats );
                    this->Dump( nodes[ nid ].cright(), fo, fmap, depth+1, with_stats );
                }                
            }