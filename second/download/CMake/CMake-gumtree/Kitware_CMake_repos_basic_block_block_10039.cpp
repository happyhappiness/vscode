(retbytes > 0) {
				DWORD i, n;

				n = retbytes / sizeof(outranges[0]);
				if (n == 1 &&
				    outranges[0].FileOffset.QuadPart == 0 &&
				    outranges[0].Length.QuadPart == entry_size)
					break;/* This is not sparse. */
				for (i = 0; i < n; i++)
					archive_entry_sparse_add_entry(entry,
					    outranges[i].FileOffset.QuadPart,
						outranges[i].Length.QuadPart);
				range.FileOffset.QuadPart =
				    outranges[n-1].FileOffset.QuadPart
				    + outranges[n-1].Length.QuadPart;
				range.Length.QuadPart =
				    entry_size - range.FileOffset.QuadPart;
				if (range.Length.QuadPart > 0)
					continue;
			} else {
				/* The remaining data is hole. */
				archive_entry_sparse_add_entry(entry,
				    range.FileOffset.QuadPart,
				    range.Length.QuadPart);
			}