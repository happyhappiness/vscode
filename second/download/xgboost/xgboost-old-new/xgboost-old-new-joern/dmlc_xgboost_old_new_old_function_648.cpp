void Dump( int nid, FILE *fo, int depth ){
                for( int  i = 0;  i < depth; ++ i ){
                    fprintf( fo, "\t" );
                }
                if( nodes[ nid ].is_leaf() ){
                    fprintf( fo, "%d:leaf=%f\n", nid, nodes[ nid ].leaf_value() );
                }else{
                    // right then left,
                    TSplitCond cond = nodes[ nid ].split_cond();
                    fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d\n", nid, 
                             nodes[ nid ].split_index(), float(cond), nodes[ nid ].cleft(), nodes[ nid ].cright() );
                    this->Dump( nodes[ nid ].cleft(), fo, depth+1 );
                    this->Dump( nodes[ nid ].cright(), fo, depth+1 );
                }                
            }