(i = 0; i < ci->numFolders; i++) {
		ci->folders[i].digest_defined = digest.defineds[i];
		ci->folders[i].digest = digest.digests[i];
	}