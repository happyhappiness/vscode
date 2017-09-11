inline void Load( void ){
    this->Clear();
    float label, weight = 0.0f;
    
    unsigned ngleft = 0, ngacc = 0;
    if( fgroup != NULL ){
      info.group_ptr.clear(); 
      info.group_ptr.push_back(0);
    }
    
    while( fscanf( fp, "%f", &label ) == 1 ){            
      if( ngleft == 0 && fgroup != NULL ){
        utils::Assert( fscanf( fgroup, "%u", &ngleft ) == 1, "group" );
      }
      if( fweight != NULL ){
        utils::Assert( fscanf( fweight, "%f", &weight ) == 1, "weight" );
      }
      
      ngleft -= 1; ngacc += 1;
      
      int pass = 1;
      if( fwlist != NULL ){
        utils::Assert( fscanf( fwlist, "%u", &pass ) ==1, "pass" );
      }
      if( pass == 0 ){
        vskip( fheader ); ngacc -= 1;
      }else{            
        const int nfeat = readnum( fheader );
        
        std::vector<SparseBatch::Entry> feats;
        
        // pairs 
        this->Load( feats, fheader );
        utils::Assert( feats.size() == (unsigned)nfeat, "nfeat" );
        if( rescale != 0 ) this->DoRescale( feats );
        // push back data :)
        this->info.labels.push_back( label );
        // push back weight if any
        if( fweight != NULL ){
          this->info.weights.push_back( weight );                    
        }
        this->AddRow( feats );
      }             
      if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
        info.group_ptr.push_back( info.group_ptr.back() + ngacc );
        utils::Assert( info.group_ptr.back() == info.num_row(), "group size must match num rows" );
        ngacc = 0;
      }
      // linelimit
      if( linelimit >= 0 ) {
        if( -- linelimit <= 0 ) break;
      }
    }
    if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
      info.group_ptr.push_back( info.group_ptr.back() + ngacc );
      utils::Assert( info.group_ptr.back() == info.num_row(), "group size must match num rows" );
    }
  }