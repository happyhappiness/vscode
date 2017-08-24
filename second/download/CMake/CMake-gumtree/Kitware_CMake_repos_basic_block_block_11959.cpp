{
				lha->mode = archive_le16dec(extdheader);
				lha->setflag |= UNIX_MODE_IS_SET;
			}