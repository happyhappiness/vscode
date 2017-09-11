             */
            inline void SaveModel( utils::IStream &fo ) const{
                utils::Assert( param.num_nodes == (int)nodes.size() );
                utils::Assert( param.num_nodes == (int)stats.size() );
                fo.Write( &param, sizeof(Param) );
                fo.Write( &nodes[0], sizeof(Node) * nodes.size() );
                fo.Write( &stats[0], sizeof(NodeStat) * nodes.size() );
            }
            /*! 
             * \brief add child nodes to node
