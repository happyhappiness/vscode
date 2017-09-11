inline void Load( void ){
        this->data.Clear();
        float label;

        unsigned ngleft = 0, ngacc = 0;
        if( fgroup != NULL ){
            info.group_ptr.clear(); 
            info.group_ptr.push_back(0);
        }

        while( fscanf( fp, "%f", &label ) == 1 ){            
            if( ngleft == 0 && fgroup != NULL ){
                utils::Assert( fscanf( fgroup, "%u", &ngleft ) == 1 );                
            }
            ngleft -= 1; ngacc += 1;

            int pass = 1;
            if( fwlist != NULL ){
                utils::Assert( fscanf( fwlist, "%u", &pass ) ==1 );
            }
            if( pass == 0 ){
                vskip( fheader ); ngacc -= 1;
            }else{            
                const int nfeat = readnum( fheader );
                std::vector<unsigned> findex;
                std::vector<float> fvalue;
                // pairs 
                this->Load( findex, fvalue, fheader );
                utils::Assert( findex.size() == (unsigned)nfeat );
                if( rescale != 0 ) this->DoRescale( fvalue );
                // push back data :)
                this->info.labels.push_back( label );
                this->data.AddRow( findex, fvalue );
            }             
            if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
                info.group_ptr.push_back( info.group_ptr.back() + ngacc );
                utils::Assert( info.group_ptr.back() == data.NumRow(), "group size must match num rows" );
                ngacc = 0;
            }
            // linelimit
            if( linelimit >= 0 ) {
                if( -- linelimit <= 0 ) break;
            }
        }
        if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
            info.group_ptr.push_back( info.group_ptr.back() + ngacc );
            utils::Assert( info.group_ptr.back() == data.NumRow(), "group size must match num rows" );
        }
        this->data.InitData();
    }