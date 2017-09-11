inline int BufferOffset( int buffer_index, int bst_group ) const{
                    if( buffer_index < 0 ) return -1;
                    utils::Assert( buffer_index < num_pbuffer, "buffer_indexexceed num_pbuffer" ); 
                    return buffer_index + num_pbuffer * bst_group;
                    
                }