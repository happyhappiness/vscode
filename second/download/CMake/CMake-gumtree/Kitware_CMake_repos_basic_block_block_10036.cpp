(i = 0; i < n; i++)
					archive_entry_sparse_add_entry(entry,
					    outranges[i].FileOffset.QuadPart,
						outranges[i].Length.QuadPart)