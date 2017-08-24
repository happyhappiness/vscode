(j = 0; j < f[i].numUnpackStreams;
				    j++, di++) {
					*digestsDefined++ =
					    tmpDigests.defineds[di];
					*digests++ =
					    tmpDigests.digests[di];
				}