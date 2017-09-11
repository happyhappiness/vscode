inline size_t AddRow( const std::vector<bst_uint> &findex, 
                                  const std::vector<bst_float> &fvalue ){
                FMatrixS::Line l;
                utils::Assert( findex.size() == fvalue.size() );
                l.findex = &findex[0];
                l.fvalue = &fvalue[0];
                l.len = static_cast<bst_uint>( findex.size() );
                return this->AddRow( l );
            }