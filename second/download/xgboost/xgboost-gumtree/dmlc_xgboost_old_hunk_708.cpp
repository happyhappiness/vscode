             * \brief get a booster to update
             * \return the booster created
             */
            inline booster::IBooster *GetUpdateBooster(void){
                if (tparam.reupdate_booster != -1){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                    this->ConfigBooster(boosters[bid]);
                    return boosters[bid];
                }

                if (mparam.do_reboost == 0 || boosters.size() == 0){
                    mparam.num_boosters += 1;
                    boosters.push_back(booster::CreateBooster<FMatrixS>(mparam.booster_type));
                    booster_info.push_back(0);
                    this->ConfigBooster(boosters.back());
                    boosters.back()->InitModel();
                }
