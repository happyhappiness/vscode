                
                utils::FileStream fs(utils::FopenCheck(fname, "wb"));
                data.SaveBinary(fs);
                utils::Assert( info.labels.size() == data.NumRow(), "label size is not consistent with feature matrix size" );
                fs.Write(&info.labels[0], sizeof(float) * data.NumRow());
                {// write out group ptr
                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );                    
                    fs.Write(&ngptr, sizeof(unsigned) );
                    fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
                }
                fs.Close();
                if (!silent){
                    printf("%ux%u matrix with %lu entries is saved to %s\n",
                       (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                    if( info.group_ptr.size() != 0 ){
                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
                    }
                }
            }
            /*!
