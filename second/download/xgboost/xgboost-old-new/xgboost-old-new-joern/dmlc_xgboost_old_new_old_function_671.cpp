inline size_t AddRow( const Line &feat, unsigned fstart = 0, unsigned fend = UINT_MAX ){
                utils::Assert( feat.len >= 0, "sparse feature length can not be negative" );
                unsigned cnt = 0;
                for( unsigned i = 0; i < feat.len; i ++ ){
                    if( feat.findex[i] < fstart || feat.findex[i] >= fend ) continue;
                    findex.push_back( feat.findex[i] );
                    fvalue.push_back( feat.fvalue[i] );
                    cnt ++;
                }
                row_ptr.push_back( row_ptr.back() + cnt );
                return row_ptr.size() - 2;
            }