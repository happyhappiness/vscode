inline void LoadText( FILE *fi ){
                this->Clear();
                int ninst;
                while( fscanf( fi, "%d", &ninst ) == 1 ){
                    std::vector<booster::bst_uint>  findex;
                    std::vector<booster::bst_float> fvalue;
                    while(  ninst -- ){
                        unsigned index; float value;
                        utils::Assert( fscanf( fi, "%u:%f", &index, &value ) == 2, "load Text" );
                        findex.push_back( index ); fvalue.push_back( value );
                    }
                    this->AddRow( findex, fvalue );                    
                }
                // initialize column support as well
                this->InitData();
            }