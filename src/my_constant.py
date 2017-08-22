#-*-coding: utf-8 -*-
"""
@ involve : constant definition
"""
USER = 'Kitware'
REPOS = 'CMake'
# USER = 'bftpd'
# REPOS = 'bftpd'

"""
stroed file name prefix
"""
# parent
BASE_DIR = '/usr/info/code/cpp/LogMonitor/LogMonitor'
OLD_NEW_PARENT_DIR = 'second/download/' + REPOS + '/' + REPOS + '-old-new/'
REPOS_PARENT_DIR = 'second/download/' + REPOS + '/' + REPOS + '/'
# old new
OLD_NEW_JOERN_DIR = OLD_NEW_PARENT_DIR + REPOS + '-old-new-joern/'
# repos
REPOS_DIR = REPOS_PARENT_DIR + REPOS + '/'
REPOS_JOERN_DIR = REPOS_PARENT_DIR + REPOS + '-joern/'
# gumtree
GUMTREE_DIR = 'second/download/' + REPOS + '/' + REPOS + '-gumtree/'
# source file and patch file
DOWNLOAD_OLD_FILE = OLD_NEW_PARENT_DIR + REPOS + '-old-new/' + USER + '_' + REPOS + '_old_file_'
DOWNLOAD_NEW_FILE = OLD_NEW_PARENT_DIR + REPOS + '-old-new/' + USER + '_' + REPOS + '_new_file_'
DOWNLOAD_PATCH_FILE = OLD_NEW_PARENT_DIR + REPOS + '-old-new/' + USER + '_' + REPOS + '_patch_'
# hunk
DOWNLOAD_OLD_HUNK = GUMTREE_DIR + USER + '_' + REPOS + '_old_hunk_'
DOWNLOAD_NEW_HUNK = GUMTREE_DIR + USER + '_' + REPOS + '_new_hunk_'
# log
SAVE_REPOS_LOG = GUMTREE_DIR + USER + '_' + REPOS + '_repos_log_'
SAVE_OLD_NEW_OLD_LOG = GUMTREE_DIR + USER + '_' + REPOS + '_old_new_old_log_'
SAVE_OLD_NEW_NEW_LOG = GUMTREE_DIR + USER + '_' + REPOS + '_old_new_new_log_'
# block
SAVE_REPOS_BASIC_BLOCK_BLOCK = GUMTREE_DIR + USER + '_' + REPOS + '_repos_basic_block_block_'
SAVE_REPOS_LOG_BLOCK = GUMTREE_DIR + USER + '_' + REPOS + '_repos_log_block_'
SAVE_OLD_NEW_BLOCK = GUMTREE_DIR + USER + '_' + REPOS + '_old_new_block_'
# function
SAVE_REPOS_FUNCTION = REPOS_JOERN_DIR + USER + '_' + REPOS + '_repos_function_'
SAVE_OLD_NEW_FUNCTION = OLD_NEW_JOERN_DIR + USER + '_' + REPOS + '_old_new_function_'

"""
file name
"""
LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_func_similarity.csv'
FETCH_PATCH_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_patch_fetch.csv'
FETCH_HUNK_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_hunk_fetch.csv'
FETCH_LOG_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_log_fetch.csv'
ANALYZE_OLD_NEW_GUMTREE_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_gumtree_analyze.csv'
ANALYZE_REPOS_LOG_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_log_analyze.csv'
ANALYZE_REPOS_BASIC_BLOCK_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_basic_block_analyze.csv'
ANALYZE_OLD_NEW_JOERN_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_joern_analyze.csv'
ANALYZE_CLONE_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_seek_clone.csv'
STATISTICS_CLONE_NUM_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_clone_statistics.csv'
STATISTICS_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_statistics.csv'
CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_cluster.csv'
ANALYZE_REPOS_CLASS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_class.csv'
REPOS_SIMILARITY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_similarity.csv'
NODE_DICT_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_node_dict.csv'

"""
fetch patch file title and index
"""
FETCH_PATCH_TITLE = ['sha', 'message', 'issue', 'file_name', 'old_file', 'new_file', 'patch_file']
FETCH_PATCH_PATCH_FILE = FETCH_PATCH_TITLE.index('patch_file')


"""
fetch hunk file title and index
"""
FETCH_HUNK_TITLE = FETCH_PATCH_TITLE + ['old_hunk_file', 'new_hunk_file', 'old_hunk_loc', 'new_hunk_loc', \
'old_log_loc', 'new_log_loc']
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')
FETCH_HUNK_OLD_LOG_LOC = FETCH_HUNK_TITLE.index('old_log_loc')
FETCH_HUNK_NEW_LOG_LOC = FETCH_HUNK_TITLE.index('new_log_loc')
FETCH_HUNK_OLD_HUNK_FILE = FETCH_HUNK_TITLE.index('old_hunk_file')
FETCH_HUNK_NEW_HUNK_FILE = FETCH_HUNK_TITLE.index('new_hunk_file')

"""
fetch log file title and index
"""
FETCH_LOG_TITLE = FETCH_PATCH_TITLE + ['old_hunk_file', 'new_hunk_file', 'old_hunk_loc', 'new_hunk_loc',\
 'old_loc', 'new_loc', 'old_log', 'new_log', 'action_type']
FETCH_LOG_SHA = FETCH_LOG_TITLE.index('sha')
FETCH_LOG_ISSUE = FETCH_LOG_TITLE.index('issue')
FETCH_LOG_MESSAGE = FETCH_LOG_TITLE.index('message')
FETCH_LOG_FILE = FETCH_LOG_TITLE.index('file_name')
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_loc')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_loc')
FETCH_LOG_OLD_LOG = FETCH_LOG_TITLE.index('old_log')
FETCH_LOG_NEW_LOG = FETCH_LOG_TITLE.index('new_log')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_file')
FETCH_LOG_ACTION_TYPE = FETCH_LOG_TITLE.index('action_type')

"""
analyze old new title and index
"""
ANALYZE_OLD_NEW_GUMTREE_TITLE = FETCH_LOG_TITLE + ['old_log_file', 'new_log_file', 'old_block', 'old_block_file', 'old_block_feature', 'old_function_file', 'old_fucntion_loc']
ANALYZE_OLD_NEW_OLD_FUNCTION_FILE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_function_file')
ANALYZE_OLD_NEW_OLD_FUNCTION_LOC = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_fucntion_loc')
# ANALYZE_OLD_NEW_SHA = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('sha')
# ANALYZE_OLD_NEW_OLD_LOG_FILE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_log_file')
# ANALYZE_OLD_NEW_NEW_LOG_FILE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('new_log_file')
# ANALYZE_OLD_NEW_OLD_BLOCK_FILE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_block_file')
# ANALYZE_OLD_NEW_OLD_BLOCK_FEATURE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_block_feature')
# ANALYZE_OLD_NEW_FILE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('file_name')
# ANALYZE_OLD_NEW_OLD_LOG = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('old_log')
# ANALYZE_OLD_NEW_NEW_LOG = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('new_log')

"""
analyze old new title and index
"""
ANALYZE_OLD_NEW_JOERN_TITLE = ANALYZE_OLD_NEW_GUMTREE_TITLE + ['old_ddg_feature', 'old_cdg_feature']
ANALYZE_OLD_NEW_SHA = ANALYZE_OLD_NEW_JOERN_TITLE.index('sha')
ANALYZE_OLD_NEW_OLD_LOG_FILE = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_log_file')
ANALYZE_OLD_NEW_NEW_LOG_FILE = ANALYZE_OLD_NEW_JOERN_TITLE.index('new_log_file')
ANALYZE_OLD_NEW_OLD_BLOCK_FILE = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_block_file')
ANALYZE_OLD_NEW_OLD_BLOCK_FEATURE = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_block_feature')
ANALYZE_OLD_NEW_OLD_DDG_FEATURE = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_ddg_feature')
ANALYZE_OLD_NEW_OLD_CDG_FEATURE = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_cdg_feature')
ANALYZE_OLD_NEW_FILE = ANALYZE_OLD_NEW_JOERN_TITLE.index('file_name')
ANALYZE_OLD_NEW_OLD_LOG = ANALYZE_OLD_NEW_JOERN_TITLE.index('old_log')
ANALYZE_OLD_NEW_NEW_LOG = ANALYZE_OLD_NEW_JOERN_TITLE.index('new_log')


STATISTICS_OLD_NEW_TITLE = ANALYZE_OLD_NEW_JOERN_TITLE + ['old_log_type', 'old_log_time', 'old_log_author', 'cluster']


"""
analyze repos / cluster repos title and index
"""
ANALYZE_REPOS_LOG_TITLE = ['file', 'loc', 'block', 'block_file', 'block_feature',\
                             'log', 'log_file', 'ddg_feature', 'condition_info', \
                             'normalized_condition', 'cdg_z3_feature', 'class_index']
ANALYZE_REPOS_LOG_FILE = ANALYZE_REPOS_LOG_TITLE.index('log_file')
ANALYZE_REPOS_BLOCK_FILE = ANALYZE_REPOS_LOG_TITLE.index('block_file')
ANALYZE_REPOS_BLOCK_FEATURE = ANALYZE_REPOS_LOG_TITLE.index('block_feature')
ANALYZE_REPOS_CONDITION_INFO = ANALYZE_REPOS_LOG_TITLE.index('condition_info')
# ANALYZE_REPOS_LOG_FILE = ANALYZE_REPOS_TITLE.index('log_file')
# ANALYZE_REPOS_BLOCK_FILE = ANALYZE_REPOS_TITLE.index('block_file')
# ANALYZE_REPOS_BLOCK_FEATURE = ANALYZE_REPOS_TITLE.index('block_feature')
# CLUSTER_REPOS_TITLE = ['file', 'loc', 'log', 'log_file', 'block', 'block_file', 'block_feature', 'cluster_index']


"""
analyze repos / cluster repos title and index
"""
ANALYZE_REPOS_BASIC_BLOCK_TITLE = ['file', 'loc', 'block', 'block_file', 'block_feature', \
                'condition_info', 'normalized_condition']
ANALYZE_REPOS_BASIC_BLOCK_FILE = ANALYZE_REPOS_BASIC_BLOCK_TITLE.index('file')
ANALYZE_REPOS_BASIC_BLOCK_LOC = ANALYZE_REPOS_BASIC_BLOCK_TITLE.index('loc')
ANALYZE_REPOS_BASIC_BLOCK_CONDITION_IFNO = ANALYZE_REPOS_BASIC_BLOCK_TITLE.index('condition_info')
ANALYZE_REPOS_BASIC_BLOCK_NORMALIZED_CONDITION = ANALYZE_REPOS_BASIC_BLOCK_TITLE.index('normalized_condition')
CLUSTER_REPOS_TITLE = ANALYZE_REPOS_BASIC_BLOCK_TITLE + ['cdg_z3_feature', 'class_index']

ANALYZE_REPOS_CLASS_TITLE = ANALYZE_REPOS_BASIC_BLOCK_TITLE + ['cdg_z3_feature', 'class_index', 'class_size']
ANALYZE_REPOS_CLASS_INDEX = ANALYZE_REPOS_CLASS_TITLE.index('class_index')
ANALYZE_REPOS_CLASS_SIZE = ANALYZE_REPOS_CLASS_TITLE.index('class_size')


"""
analyze clone title
"""
ANALYZE_CLONE_TITLE = ANALYZE_OLD_NEW_JOERN_TITLE + ['class_index', 'class_size']#ANALYZE_REPOS_BASIC_BLOCK_TITLE

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
LOG_UPDATE = 3
LOG_COCHANGE = 4

LOG_FEATURE_MODIFY = 4
LOG_OTHER_LOG_FEATURE_MODIFY = 6
LOG_OTHER_LOG_MODIFY = 2
LOG_NO_MODIFY = 0
LOG_LOG_MODIFY = 3
LOG_LOG_FEATURE_MODIFY = 7

HUNK_LOGS_MODIFY = 2
HUNK_FEATURE_MODIFY = 4

LOG_OVER_MODIFY = -1
LOG_NO_MODIFY = 0
LOG_MODIFY = 1


"""
joern result format
"""
JOERN_DEFALUT = 0
JOERN_ID = 0
JOERN_CODE = 1
JOERN_TYPE = 2
JOERN_FILE = 2
JOERN_LOCATION = 3
JOERN_OPERATOR = 3
JOERN_BOOL_OPERATOR = ['AndExpression', 'OrExpression', 'RelationalExpression', 'EqualityExpression']
JOERN_ADDRESS_OPERATOR = ['ArrayIndexing', 'PtrMemberAccess', 'MemberAccess']
JOERN_BIT_OPERATOR = ['BitAndExpression', 'BitOrExpression']
JOERN_UNARY_OPERATOR = 'UnaryOp'
JOERN_ASSIGN_OPERATOR = 'AssignmentExpr'
# variable types
JOERN_CALLEE_FLAG = '_ret'
JOERN_NULL = 'null'
JOERN_UNKNOWN = 'unkown'
JOERN_MEMEBER = 'member'
JOERN_BOOL = 'bool'

"""
split string for statement to get tokens
"""
SPLIT_STR = r'[\W\s_]'
SPLIT_ALGORITHM = r'[+-\*/%=]'


"""
pre issue address
"""
ISSUE_ADDRESS = 'https://gitlab.kitware.com/cmake/cmake/issues/'
FILE_FORMAT = r'\.(c|cpp|cc|cxx|h)$'
UNSRCML_FILE_FORMAT = r'\.(h|c|cc|cxx)$'

"""
class path for java
"""
# GUMTREE_HOME = '/opt/gumtree/dist/build/distributions/gumtree-20170722-2.1.0-SNAPSHOT'
GUMTREE_HOME = '/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT'
JAVA_CLASS_PATH = '.:/usr/info/code/cpp/LogMonitor/LogMonitor/java:' + GUMTREE_HOME + '/lib/annotations-2.0.1.jar:' + GUMTREE_HOME + '/lib/antlr-3.5.2.jar:' + GUMTREE_HOME + '/lib/antlr-runtime-3.5.2.jar:' + GUMTREE_HOME + '/lib/aopalliance-1.0.jar:' + GUMTREE_HOME + '/lib/app-1.3.200-v20130910-1609.jar:' + GUMTREE_HOME + '/lib/asm-3.1.jar:' + GUMTREE_HOME + '/lib/cglib-2.2.1-v20090111.jar:' + GUMTREE_HOME + '/lib/client.diff-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/client-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/common-3.6.200-v20130402-1505.jar:' + GUMTREE_HOME + '/lib/commons-codec-1.10.jar:' + GUMTREE_HOME + '/lib/commons-io-2.0.1.jar:' + GUMTREE_HOME + '/lib/commons-lang3-3.1.jar:' + GUMTREE_HOME + '/lib/commons-logging-1.2.jar:' + GUMTREE_HOME + '/lib/contenttype-3.4.200-v20140207-1251.jar:' + GUMTREE_HOME + '/lib/core-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-antlr-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-json-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-php-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-r-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-xml-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.c-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.css-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.jdt-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.js-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.ruby-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.srcml-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gson-2.4.jar:' + GUMTREE_HOME + '/lib/guava-18.0.jar:' + GUMTREE_HOME + '/lib/guice-3.0.jar:' + GUMTREE_HOME + '/lib/javassist-3.18.2-GA.jar:' + GUMTREE_HOME + '/lib/javax.inject-1.jar:' + GUMTREE_HOME + '/lib/javax.servlet-api-3.1.0.jar:' + GUMTREE_HOME + '/lib/jetty-http-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-io-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-security-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-server-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-servlet-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-util-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-webapp-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-xml-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jobs-3.6.0-v20140424-0053.jar:' + GUMTREE_HOME + '/lib/jrubyparser-0.5.3.jar:' + GUMTREE_HOME + '/lib/jsr305-3.0.1.jar:' + GUMTREE_HOME + '/lib/jtidy-r938.jar:' + GUMTREE_HOME + '/lib/junit-4.8.2.jar:' + GUMTREE_HOME + '/lib/org.eclipse.core.resources-3.10.0.v20150423-0755.jar:' + GUMTREE_HOME + '/lib/org.eclipse.jdt.core-3.11.0.v20150602-1242.jar:' + GUMTREE_HOME + '/lib/osgi-3.10.0-v20140606-1445.jar:' + GUMTREE_HOME + '/lib/ph-commons-8.3.0.jar:' + GUMTREE_HOME + '/lib/ph-css-5.0.1.jar:' + GUMTREE_HOME + '/lib/preferences-3.5.200-v20140224-1527.jar:' + GUMTREE_HOME + '/lib/reflections-0.9.10.jar:' + GUMTREE_HOME + '/lib/registry-3.5.400-v20140428-1507.jar:' + GUMTREE_HOME + '/lib/rendersnake-1.9.0.jar:' + GUMTREE_HOME + '/lib/rhino-1.7.7.jar:' + GUMTREE_HOME + '/lib/runtime-3.10.0-v20140318-2214.jar:' + GUMTREE_HOME + '/lib/simmetrics-core-3.2.3.jar:' + GUMTREE_HOME + '/lib/slf4j-api-1.7.21.jar:' + GUMTREE_HOME + '/lib/spark-core-2.5.2.jar:' + GUMTREE_HOME + '/lib/spring-aop-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-beans-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-context-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-core-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-expression-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-web-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-webmvc-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/ST4-4.0.8.jar:' + GUMTREE_HOME + '/lib/trove4j-3.0.3.jar:' + GUMTREE_HOME + '/lib/websocket-api-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-client-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-common-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-server-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-servlet-9.3.6.v20151106.jar'

# 149 real slow