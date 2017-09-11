    for( size_t i = 0; i < vec.size(); i ++ ){
      if( !vec[i].is_dense ) { 
        for( int j = 0; j < vec[i].tmp_num; j ++ ){
          utils::Assert( fscanf ( vec[i].fi, "%u:%f", &e.findex, &e.fvalue ) == 2, "Error when load feat" );  
          vec[i].CheckBase( e.findex );
          e.findex += vec[i].base;
          feats.push_back(e);
        }
      }else{
        utils::Assert( fscanf ( vec[i].fi, "%f", &e.fvalue ) == 1, "load feat" );  
        e.findex = vec[i].base;
        feats.push_back(e);
      }
    }
