(i = 0; i < numInStreamsTotal; i++) {
			unsigned j;
			for (j = 0; j < f->numBindPairs; j++) {
				if (f->bindPairs[j].inIndex == i)
					break;
			}
			if (j == f->numBindPairs)
				break;
		}