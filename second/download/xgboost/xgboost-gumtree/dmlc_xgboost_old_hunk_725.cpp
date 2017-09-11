                    if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                        info.group_ptr.resize( ngptr );
                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
                    }
                }
                fs.Close();
