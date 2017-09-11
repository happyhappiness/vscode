inline void vskip( std::vector<Header> &vec ){
  for( size_t i = 0; i < vec.size(); i ++ ){
    if( !vec[i].is_dense ){
      utils::Assert( fscanf( vec[i].fi, "%*d%*[^\n]\n" ) >= 0, "sparse" );
    }else{
      utils::Assert( fscanf( vec[i].fi, "%*f\n" ) >= 0, "dense" );
    }
  }
}