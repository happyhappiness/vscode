             * \brief get a booster to update
             * \return the booster created
             */
            inline booster::IBooster *GetUpdateBooster(int bst_group){
                if (tparam.reupdate_booster != -1){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                    this->ConfigBooster(boosters[bid]);
                    utils::Assert( bst_group == booster_info[bid], "booster group must match existing reupdate booster");
                    return boosters[bid];
                }

                if (mparam.do_reboost == 0 || boosters.size() == 0){
                    mparam.num_boosters += 1;
                    boosters.push_back(booster::CreateBooster<FMatrixS>(mparam.booster_type));
                    booster_info.push_back(bst_group);
                    this->ConfigBooster(boosters.back());
                    boosters.back()->InitModel();
                }
