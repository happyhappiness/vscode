inline bool LoadBinary(const char* fname, const char* fgroup, bool silent = false){
				FILE *fp = fopen64(fname, "rb");
				if (fp == NULL) return false;
				utils::FileStream fs(fp);
				data.LoadBinary(fs);
				labels.resize(data.NumRow());
				utils::Assert(fs.Read(&labels[0], sizeof(float)* data.NumRow()) != 0, "DMatrix LoadBinary");
				fs.Close();
				// initialize column support as well
				data.InitData();

				if (!silent){
					printf("%ux%u matrix with %lu entries is loaded from %s\n",
						(unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
				}

				//if group data exists load it in
				FILE *file_group = fopen64(fgroup, "r");
				if (file_group != NULL){
					int group_index_size = 0;
					utils::FileStream group_stream(file_group);
					utils::Assert(group_stream.Read(&group_index_size, sizeof(int)) != 0, "Load group indice size");
					group_index.resize(group_index_size);
					utils::Assert(group_stream.Read(&group_index, sizeof(int)* group_index_size) != 0, "Load group indice");

					if (!silent){
						printf("the group index of %d groups is loaded from %s\n",
							group_index_size - 1, fgroup);
					}
				}
				return true;
			}