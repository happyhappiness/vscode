inline void SaveModel( utils::IStream &fo ) const{
                utils::Assert( param.num_nodes == (int)nodes.size() );
                fo.Write( &param, sizeof(Param) );
                fo.Write( &nodes[0], sizeof(Node) * nodes.size() );
            }