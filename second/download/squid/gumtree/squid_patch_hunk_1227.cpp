 /* DEBUG: section 28    Access Control */
 
 #include "squid.h"
 #include "acl/Acl.h"
 #include "acl/Checklist.h"
 #include "acl/Gadgets.h"
+#include "acl/Options.h"
 #include "anyp/PortCfg.h"
 #include "cache_cf.h"
 #include "ConfigParser.h"
 #include "Debug.h"
-#include "dlink.h"
 #include "fatal.h"
 #include "globals.h"
 #include "profiler/Profiler.h"
+#include "sbuf/List.h"
+#include "sbuf/Stream.h"
 #include "SquidConfig.h"
 
-#include <vector>
-
-#define abortFlags(CONTENT) \
-   do { \
-    debugs(28, 0, CONTENT); \
-    self_destruct(); \
-   } while (0)
-
-const ACLFlag ACLFlags::NoFlags[1] = {ACL_F_END};
+#include <algorithm>
+#include <map>
 
 const char *AclMatchedName = NULL;
 
-ACLFlags::FlagsTokenizer::FlagsTokenizer(): tokPos(NULL) { }
+namespace Acl {
 
-ACLFlag
-ACLFlags::FlagsTokenizer::nextFlag()
-{
-    if (needNextToken()) {
-        if (!nextToken())
-            return 0;
-    } else
-        ++tokPos;
-    return *tokPos;
-}
-
-bool
-ACLFlags::FlagsTokenizer::hasParameter() const
-{
-    return tokPos && tokPos[0] && tokPos[1] == '=' && tokPos[2];
-}
+/// ACL type name comparison functor
+class TypeNameCmp {
+public:
+    bool operator()(TypeName a, TypeName b) const { return strcmp(a, b) < 0; }
+};
 
-SBuf
-ACLFlags::FlagsTokenizer::getParameter() const
-{
-    return hasParameter() ? SBuf(&tokPos[2]) : SBuf();
-}
+/// ACL makers indexed by ACL type name
+typedef std::map<TypeName, Maker, TypeNameCmp> Makers;
 
-bool
-ACLFlags::FlagsTokenizer::needNextToken() const
+/// registered ACL Makers
+static Makers &
+TheMakers()
 {
-    return !tokPos || !tokPos[0] || !tokPos[1] || tokPos[1] == '=';
-}
-
-bool
-ACLFlags::FlagsTokenizer::nextToken()
-{
-    char *t = ConfigParser::PeekAtToken();
-    if (t == NULL || t[0] != '-' || !t[1])
-        return false;
-    (void)ConfigParser::NextQuotedToken();
-    if (strcmp(t, "--") == 0)
-        return false;
-    tokPos = t + 1;
-    return true;
-}
-
-ACLFlags::~ACLFlags()
-{
-    delete delimiters_;
-}
-
-ACLFlags::Status
-ACLFlags::flagStatus(const ACLFlag f) const
-{
-    if (f == ACL_F_REGEX_CASE)
-        return noParameter;
-    if (f == ACL_F_SUBSTRING)
-        return parameterOptional;
-    if (supported_.find(f) != std::string::npos)
-        return noParameter;
-    return notSupported;
-}
-
-bool
-ACLFlags::parameterSupported(const ACLFlag f, const SBuf &val) const
-{
-    if (f == ACL_F_SUBSTRING)
-        return val.findFirstOf(CharacterSet::ALPHA + CharacterSet::DIGIT) == SBuf::npos;
-    return true;
+    static Makers Registry;
+    return Registry;
 }
 
-void
-ACLFlags::makeSet(const ACLFlag f, const SBuf &param)
-{
-    flags_ |= flagToInt(f);
-    if (!param.isEmpty())
-        flagParameters_[f].append(param);
-}
-
-void
-ACLFlags::makeUnSet(const ACLFlag f)
-{
-    flags_ &= ~flagToInt(f);
-    flagParameters_[f].clear();
-}
-
-void
-ACLFlags::parseFlags()
+/// creates an ACL object of the named (and already registered) ACL child type
+static
+ACL *
+Make(TypeName typeName)
 {
-    FlagsTokenizer tokenizer;
-    ACLFlag flag('\0');
-    while ((flag = tokenizer.nextFlag())) {
-        switch (flagStatus(flag))
-        {
-        case notSupported:
-            abortFlags("Flag '" << flag << "' not supported");
-            break;
-        case noParameter:
-            makeSet(flag);
-            break;
-        case parameterRequired:
-            if (!tokenizer.hasParameter()) {
-                abortFlags("Flag '" << flag << "' must have a parameter");
-                break;
-            }
-        case parameterOptional:
-            SBuf param;
-            if (tokenizer.hasParameter()) {
-                param = tokenizer.getParameter();
-                if (!parameterSupported(flag, param))
-                    abortFlags("Parameter '" << param << "' for flag '" << flag << "' not supported");
-            }
-            makeSet(flag, param);
-            break;
-        }
-    }
-
-    /*Regex code needs to parse -i file*/
-    if ( isSet(ACL_F_REGEX_CASE)) {
-        ConfigParser::TokenPutBack("-i");
-        makeUnSet('i');
+    const auto pos = TheMakers().find(typeName);
+    if (pos == TheMakers().end()) {
+        debugs(28, DBG_CRITICAL, "FATAL: Invalid ACL type '" << typeName << "'");
+        self_destruct();
+        assert(false); // not reached
     }
-}
 
-SBuf
-ACLFlags::parameter(const ACLFlag f) const
-{
-    assert(static_cast<uint32_t>(f - 'A') < FlagIndexMax);
-    auto p = flagParameters_.find(f);
-    return p == flagParameters_.end() ? SBuf() : p->second;
+    ACL *result = (pos->second)(pos->first);
+    debugs(28, 4, typeName << '=' << result);
+    assert(result);
+    return result;
 }
 
-const CharacterSet *
-ACLFlags::delimiters()
-{
-    if (isSet(ACL_F_SUBSTRING) && !delimiters_) {
-        static const SBuf defaultParameter(",");
-        SBuf rawParameter = parameter(ACL_F_SUBSTRING);
-        if (rawParameter.isEmpty())
-            rawParameter = defaultParameter;
-        delimiters_ = new CharacterSet("ACLFlags::delimiters", rawParameter.c_str());
-    }
-    return delimiters_;
-}
+} // namespace Acl
 
-const char *
-ACLFlags::flagsStr() const
+void
+Acl::RegisterMaker(TypeName typeName, Maker maker)
 {
-    static char buf[64];
-    if (flags_ == 0)
-        return "";
-
-    char *s = buf;
-    *s++ = '-';
-    for (ACLFlag f = 'A'; f <= 'z'; f++) {
-        // ACL_F_REGEX_CASE (-i) flag handled by ACLRegexData class, ignore
-        if (isSet(f) && f != ACL_F_REGEX_CASE)
-            *s++ = f;
-    }
-    *s = '\0';
-    return buf;
+    assert(typeName);
+    assert(*typeName);
+    TheMakers().emplace(typeName, maker);
 }
 
 void *
 ACL::operator new (size_t)
 {
     fatal ("unusable ACL::new");
