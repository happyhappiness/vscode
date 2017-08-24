{
				lha->compsize = archive_le64dec(extdheader);
				extdheader += sizeof(uint64_t);
				lha->origsize = archive_le64dec(extdheader);
			}