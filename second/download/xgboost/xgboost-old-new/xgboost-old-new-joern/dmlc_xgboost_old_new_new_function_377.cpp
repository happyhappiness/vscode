inline void Load( std::vector<SparseBatch::Entry> &feats, std::vector<Header> &vec ){
    SparseBatch::Entry e;
    for( size_t i = 0; i < vec.size(); i ++ ){
      if( !vec[i].is_dense ) { 
        for( int j = 0; j < vec[i].tmp_num; j ++ ){
          utils::Assert( fscanf ( vec[i].fi, "%u:%f", &e.index, &e.fvalue ) == 2, "Error when load feat" );  
          vec[i].CheckBase( e.index );
          e.index += vec[i].base;
          feats.push_back(e);
        }
      }else{
        utils::Assert( fscanf ( vec[i].fi, "%f", &e.fvalue ) == 1, "load feat" );  
        e.index = vec[i].base;
        feats.push_back(e);
      }
    }
  }