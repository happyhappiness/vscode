
        while( fscanf( fp, "%f", &label ) == 1 ){            
            if( ngleft == 0 && fgroup != NULL ){
                utils::Assert( fscanf( fgroup, "%u", &ngleft ) == 1 );                
            }
            ngleft -= 1; ngacc += 1;

            int pass = 1;
