die(_("merging of trees %s and %s failed"),
			    sha1_to_hex(head->object.sha1),
			    sha1_to_hex(merge->object.sha1));