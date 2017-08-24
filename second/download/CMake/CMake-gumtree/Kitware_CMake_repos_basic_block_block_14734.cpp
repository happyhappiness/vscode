(fe->mac_metadata != NULL) {
				memcpy(fe->mac_metadata, metadata,
				    metadata_size);
				fe->mac_metadata_size = metadata_size;
				fe->fixup |= TODO_MAC_METADATA;
			}