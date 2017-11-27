 
   plugin_log (severity, "%s", c_str);
 
   (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_message, c_str);
 } /* }}} void cjni_api_log */
 
+static jstring JNICALL cjni_api_get_hostname (JNIEnv *jvm_env, jobject this)
+{
+    return ctoj_output_string(jvm_env, hostname_g);
+}
+
 /* List of ``native'' functions, i. e. C-functions that can be called from
  * Java. */
 static JNINativeMethod jni_api_functions[] = /* {{{ */
 {
   { "dispatchValues",
     "(Lorg/collectd/api/ValueList;)I",
