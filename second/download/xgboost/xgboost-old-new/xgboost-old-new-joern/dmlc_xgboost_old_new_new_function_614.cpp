inline void LoadGroupBinary(const char* fgroup, bool silent = false){
	      //if group data exists load it in
                FILE *file_group = fopen64(fgroup, "r");
                if (file_group != NULL){
                    int group_index_size = 0;
                    utils::FileStream group_stream(file_group);
                    utils::Assert(group_stream.Read(&group_index_size, sizeof(int)) != 0, "Load group indice size");
                    group_index.resize(group_index_size);
                    utils::Assert(group_stream.Read(&group_index[0], sizeof(int) * group_index_size) != 0, "Load group indice");

                    if (!silent){
                        printf("Index info of %d groups is loaded from %s as binary\n",
                            group_index.size() - 1, fgroup);
                    }
		    fclose(file_group);
                }else{
		    if(!silent){printf("The binary file of group info not exists");}
		}
                
	    }