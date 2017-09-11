                utils::Assert( info.labels.size() == data.NumRow(), "label size is not consistent with feature matrix size" );
                fs.Write(&info.labels[0], sizeof(float) * data.NumRow());
                {// write out group ptr
                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );                    
                    fs.Write(&ngptr, sizeof(unsigned) );
                    fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
                }
