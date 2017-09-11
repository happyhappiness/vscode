                labels.resize( data.NumRow() );
                utils::Assert( fs.Read( &labels[0], sizeof(float) * data.NumRow() ) != 0, "DMatrix LoadBinary" );
                fs.Close();
                this->UpdateInfo();
                if( !silent ){
                    printf("%ux%u matrix with %lu entries is loaded from %s\n", 
                        (unsigned)labels.size(), num_feature, (unsigned long)data.NumEntry(), fname );
                }
                return true;
            }
