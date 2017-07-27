fprintf(fout, "cmake_policy(SET CMP0065 %s)\n",
            this->Makefile->GetPolicyStatus(cmPolicies::CMP0065) ==
                cmPolicies::NEW
              ? "NEW"
              : "OLD")