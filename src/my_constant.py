#-*-coding: utf-8 -*-
"""
@ involve : constant definition
"""
USER = 'Kitware'
REPOS = 'CMake'
# USER = 'bftpd'
# REPOS = 'bftpd'

"""
file name
"""
LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_func_similarity.csv'
FETCH_HUNK_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_hunk_fetch.csv'
FETCH_LOG_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_log_fetch.csv'
ANALYZE_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_analyze.csv'
ANALYZE_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_analyze.csv'
ANALYZE_CLONE_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_seek_clone.csv'
STATISTICS_CLONE_NUM_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_clone_statistics.csv'
STATISTICS_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_statistics.csv'
CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_cluster.csv'
REPOS_SIMILARITY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_similarity.csv'
NODE_DICT_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_node_dict.csv'

"""
fetch hunk file title and index
"""
FETCH_HUNK_TITLE = ['hunk', 'flag', 'logs', 'old_hunk_loc', 'new_hunk_loc']
FETCH_HUNK_HUNK = FETCH_HUNK_TITLE.index('hunk')
FETCH_HUNK_FLAG = FETCH_HUNK_TITLE.index('flag')
FETCH_HUNK_LOGS = FETCH_HUNK_TITLE.index('logs')
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')

"""
fetch log file title and index
"""
FETCH_LOG_TITLE = ['commit_sha', 'issue_address', 'commit_message', 'file_name', 'change_type', \
                'log_statement', 'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name']
FETCH_LOG_COMMIT_SHA = FETCH_LOG_TITLE.index('issue_address')
FETCH_LOG_ISSUE_ADDRESS = FETCH_LOG_TITLE.index('commit_sha')
FETCH_LOG_COMMIT_MESSAGE = FETCH_LOG_TITLE.index('commit_message')
FETCH_LOG_FILE = FETCH_LOG_TITLE.index('file_name')
FETCH_LOG_CHANGE_TYPE = FETCH_LOG_TITLE.index('change_type')
FETCH_LOG_LOG = FETCH_LOG_TITLE.index('log_statement')
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_log_loc')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_store_name')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_log_loc')
FETCH_LOG_NEW_FILE = FETCH_LOG_TITLE.index('new_store_name')

"""
analyze old new title and index
"""
ANALYZE_OLD_NEW_TITLE = ['identity', 'old_block_file', 'old_block_location',\
        'old_block_condition_feature', 'old_block_statement_feature', 'old_block_vector',\
        'new_block_file', 'new_block_location', \
        'new_block_condition_feature', 'new_block_statement_feature', 'new_block_vector', \
        'commit_sha', 'issue_address', 'commit_message', 'file_name', 'log_info']
ANALYZE_OLD_NEW_OLD_BLOCK_VECTOR = ANALYZE_OLD_NEW_TITLE.index('old_block_vector')
ANALYZE_OLD_NEW_NEW_BLOCK_VECTOR = ANALYZE_OLD_NEW_TITLE.index('new_block_vector')
ANALYZE_OLD_NEW_LOG_INFO = ANALYZE_OLD_NEW_TITLE.index('log_info')


"""
analyze repos / cluster repos title and index
"""
ANALYZE_REPOS_TITLE = ['identity', 'file', 'location', 'condition_feature',\
                                                         'statement_feature', 'vector']
CLUSTER_REPOS_TITLE = ['identity', 'file', 'location', 'condition_feature',\
                                        'statement_feature', 'vector', 'cluster_index']
ANALYZE_REPOS_VECTOR = ANALYZE_REPOS_TITLE.index('vector')

"""
analyze clone title
"""
ANALYZE_CLONE_TITLE = ['identity', 'old_block_file', 'old_block_location',\
        'old_block_condition_feature', 'old_block_statement_feature', 'old_block_vector',\
        'new_block_file', 'new_block_location', \
        'new_block_condition_feature', 'new_block_statement_feature', 'new_block_vector', \
        'commit_sha', 'issue_address', 'commit_message', 'file_name', 'log_info', \
        \
        'identity', 'file', 'location', 'condition_feature', 'statement_feature', 'vector']

"""
flag type && log type
"""
FLAG_LOG_DELETE = -2
FLAG_DELETE = -1
FLAG_LOG_DELETE_CONTINUE = -3
FLAG_NO_CHANGE = 0
FLAG_ADD = 1
FLAG_LOG_ADD = 2
FLAG_LOG_ADD_CONTINUE = 3

LOG_ADD = 0
LOG_DELETE = 1
LOG_MOVE = 2
LOG_MODIFY = 3
LOG_COCHANGE = 4

"""
split string for statement to get tokens
"""
SPLIT_STR = r'[\W\s_]'


"""
pre issue address
"""
ISSUE_ADDRESS = 'https://gitlab.kitware.com/cmake/cmake/issues/'

"""
class path for java
"""
JAVA_CLASS_PATH = '.:/usr/info/code/cpp/LogMonitor/LogMonitor/java/:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/annotations-2.0.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/antlr-3.5.2.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/antlr-runtime-3.5.2.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/aopalliance-1.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/app-1.3.200-v20130910-1609.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/asm-3.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/cglib-2.2.1-v20090111.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/client.diff-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/client-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/common-3.6.200-v20130402-1505.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/commons-codec-1.10.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/commons-io-2.0.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/commons-lang3-3.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/commons-logging-1.2.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/contenttype-3.4.200-v20140207-1251.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/core-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-antlr-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-json-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-php-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-r-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.antlr3-xml-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.c-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.css-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.jdt-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.js-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.ruby-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gen.srcml-2.1.0-SNAPSHOT.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/gson-2.4.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/guava-18.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/guice-3.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/javassist-3.18.2-GA.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/javax.inject-1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/javax.servlet-api-3.1.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-http-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-io-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-security-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-server-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-servlet-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-util-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-webapp-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jetty-xml-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jobs-3.6.0-v20140424-0053.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jrubyparser-0.5.3.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jsr305-3.0.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/jtidy-r938.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/junit-4.8.2.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/org.eclipse.core.resources-3.10.0.v20150423-0755.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/org.eclipse.jdt.core-3.11.0.v20150602-1242.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/osgi-3.10.0-v20140606-1445.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/ph-commons-8.3.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/ph-css-5.0.1.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/preferences-3.5.200-v20140224-1527.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/reflections-0.9.10.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/registry-3.5.400-v20140428-1507.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/rendersnake-1.9.0.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/rhino-1.7.7.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/runtime-3.10.0-v20140318-2214.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/simmetrics-core-3.2.3.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/slf4j-api-1.7.21.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spark-core-2.5.2.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-aop-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-beans-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-context-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-core-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-expression-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-web-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/spring-webmvc-4.1.6.RELEASE.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/ST4-4.0.8.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/trove4j-3.0.3.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/websocket-api-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/websocket-client-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/websocket-common-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/websocket-server-9.3.6.v20151106.jar:/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT/lib/websocket-servlet-9.3.6.v20151106.jar'
