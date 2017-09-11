inline size_t AddRow( const std::vector<bst_uint> &findex, 
                                  const std::vector<bst_float> &fvalue,
                                  unsigned fstart = 0, unsigned fend = UINT_MAX ){
                utils::Assert( findex.size() == fvalue.size() );
                unsigned cnt = 0;
                for( size_t i = 0; i < findex.size(); i ++ ){
                    if( findex[i] < fstart || findex[i] >= fend ) continue;
                    REntry e; e.findex = findex[i]; e.fvalue = fvalue[i];
                    row_data_.push_back( e );
                    cnt ++;
                }
                row_ptr_.push_back( row_ptr_.back() + cnt );
                return row_ptr_.size() - 2;
            }