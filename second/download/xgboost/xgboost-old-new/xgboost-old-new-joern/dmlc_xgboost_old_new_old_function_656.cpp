inline void ChangeToLeaf( int rid, float value ){
                utils::Assert( nodes[ nodes[rid].left  ].is_leaf(), "can not delete a non termial child");
                utils::Assert( nodes[ nodes[rid].right ].is_leaf(), "can not delete a non termial child");
                this->DeleteNode( nodes[ rid ].left ); 
                this->DeleteNode( nodes[ rid ].right );
                nodes[ rid ].set_leaf( value );
            }