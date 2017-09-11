             */
            inline void LoadModel( utils::IStream &fi ){
                utils::Assert( fi.Read( &param, sizeof(Param) ) > 0, "TreeModel" );
                nodes.resize( param.num_nodes );
                utils::Assert( fi.Read( &nodes[0], sizeof(Node) * nodes.size() ) > 0, "TreeModel::Node" );
                
                deleted_nodes.resize( 0 );
                for( int i = param.num_roots; i < param.num_nodes; i ++ ){
                    if( nodes[i].is_root() ) deleted_nodes.push_back( i );
