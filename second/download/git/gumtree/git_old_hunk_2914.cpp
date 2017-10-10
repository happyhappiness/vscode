						repo_encoding, path_encoding);
			} else {
				iconv_ibp	cp = (iconv_ibp)res->d_name;
				size_t inleft = namelenz;
				char *outpos = &prec_dir->dirent_nfc->d_name[0];
				size_t outsz = prec_dir->dirent_nfc->max_name_len;
				size_t cnt;
				errno = 0;
				cnt = iconv(prec_dir->ic_precompose, &cp, &inleft, &outpos, &outsz);
				if (errno || inleft) {
					/*
					 * iconv() failed and errno could be E2BIG, EILSEQ, EINVAL, EBADF
					 * MacOS X avoids illegal byte sequemces.
					 * If they occur on a mounted drive (e.g. NFS) it is not worth to
					 * die() for that, but rather let the user see the original name
