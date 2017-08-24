{
				lha->birthtime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->birthtime_tv_nsec);
				extdheader += sizeof(uint64_t);
				lha->mtime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->mtime_tv_nsec);
				extdheader += sizeof(uint64_t);
				lha->atime = lha_win_time(
				    archive_le64dec(extdheader),
				    &lha->atime_tv_nsec);
				lha->setflag |= BIRTHTIME_IS_SET |
				    ATIME_IS_SET;
			}