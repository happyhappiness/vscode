  // destrcutor
  virtual ~IGradBooster(void){}
};
/*!
 * \breif create a gradient booster from given name
 * \param name name of gradient booster
 */
IGradBooster* CreateGradBooster(const char *name);
}  // namespace gbm
}  // namespace xgboost
#endif  // XGBOOST_GBM_GBM_H_
