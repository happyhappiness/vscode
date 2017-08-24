{
				lha->gid = archive_le16dec(extdheader);
				lha->uid = archive_le16dec(extdheader+2);
			}