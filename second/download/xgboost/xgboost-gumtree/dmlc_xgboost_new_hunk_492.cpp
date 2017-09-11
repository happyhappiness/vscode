      }             
      if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
        info.group_ptr.push_back( info.group_ptr.back() + ngacc );
        utils::Assert( info.group_ptr.back() == info.num_row(), "group size must match num rows" );
        ngacc = 0;
      }
      // linelimit
