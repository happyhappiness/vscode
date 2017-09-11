                }else{
                    // right then left,
                    TSplitCond cond = nodes[ nid ].split_cond();
                    fprintf( fo, "%d:[f%u>%f] yes=%d,no=%d\n", nid, 
                             nodes[ nid ].split_index(), float(cond), nodes[ nid ].cright(), nodes[ nid ].cleft() );
                    this->Dump( nodes[ nid ].cright(), fo, depth+1 );
                    this->Dump( nodes[ nid ].cleft(), fo, depth+1 );
                }                
            } 
        };
