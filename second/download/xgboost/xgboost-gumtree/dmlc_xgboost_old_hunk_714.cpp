                    if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                        info.group_ptr.resize( ngptr );
                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
                        utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
                    }
                }
                fs.Close();
                // initialize column support as well
                data.InitData();
                
                if (!silent){
                    printf("%ux%u matrix with %lu entries is loaded from %s\n",
