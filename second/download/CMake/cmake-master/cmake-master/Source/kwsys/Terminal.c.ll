; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/Terminal.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [15 x i8] c"CLICOLOR_FORCE\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"EMACS\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"TERM\00", align 1
@kwsysTerminalVT100Names = internal global [53 x i8*] [i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.23, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.28, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.30, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.34, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.35, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.37, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.40, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.41, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.42, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.43, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.44, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.45, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.47, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.48, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.49, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.50, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.51, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.52, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.53, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.54, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.55, i32 0, i32 0), i8* null], align 16
@.str.4 = private unnamed_addr constant [6 x i8] c"Eterm\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"ansi\00", align 1
@.str.6 = private unnamed_addr constant [12 x i8] c"color-xterm\00", align 1
@.str.7 = private unnamed_addr constant [10 x i8] c"con132x25\00", align 1
@.str.8 = private unnamed_addr constant [10 x i8] c"con132x30\00", align 1
@.str.9 = private unnamed_addr constant [10 x i8] c"con132x43\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"con132x60\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"con80x25\00", align 1
@.str.12 = private unnamed_addr constant [9 x i8] c"con80x28\00", align 1
@.str.13 = private unnamed_addr constant [9 x i8] c"con80x30\00", align 1
@.str.14 = private unnamed_addr constant [9 x i8] c"con80x43\00", align 1
@.str.15 = private unnamed_addr constant [9 x i8] c"con80x50\00", align 1
@.str.16 = private unnamed_addr constant [9 x i8] c"con80x60\00", align 1
@.str.17 = private unnamed_addr constant [7 x i8] c"cons25\00", align 1
@.str.18 = private unnamed_addr constant [8 x i8] c"console\00", align 1
@.str.19 = private unnamed_addr constant [7 x i8] c"cygwin\00", align 1
@.str.20 = private unnamed_addr constant [7 x i8] c"dtterm\00", align 1
@.str.21 = private unnamed_addr constant [12 x i8] c"eterm-color\00", align 1
@.str.22 = private unnamed_addr constant [6 x i8] c"gnome\00", align 1
@.str.23 = private unnamed_addr constant [15 x i8] c"gnome-256color\00", align 1
@.str.24 = private unnamed_addr constant [8 x i8] c"konsole\00", align 1
@.str.25 = private unnamed_addr constant [17 x i8] c"konsole-256color\00", align 1
@.str.26 = private unnamed_addr constant [6 x i8] c"kterm\00", align 1
@.str.27 = private unnamed_addr constant [6 x i8] c"linux\00", align 1
@.str.28 = private unnamed_addr constant [5 x i8] c"msys\00", align 1
@.str.29 = private unnamed_addr constant [8 x i8] c"linux-c\00", align 1
@.str.30 = private unnamed_addr constant [11 x i8] c"mach-color\00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"mlterm\00", align 1
@.str.32 = private unnamed_addr constant [6 x i8] c"putty\00", align 1
@.str.33 = private unnamed_addr constant [15 x i8] c"putty-256color\00", align 1
@.str.34 = private unnamed_addr constant [5 x i8] c"rxvt\00", align 1
@.str.35 = private unnamed_addr constant [14 x i8] c"rxvt-256color\00", align 1
@.str.36 = private unnamed_addr constant [12 x i8] c"rxvt-cygwin\00", align 1
@.str.37 = private unnamed_addr constant [19 x i8] c"rxvt-cygwin-native\00", align 1
@.str.38 = private unnamed_addr constant [13 x i8] c"rxvt-unicode\00", align 1
@.str.39 = private unnamed_addr constant [22 x i8] c"rxvt-unicode-256color\00", align 1
@.str.40 = private unnamed_addr constant [7 x i8] c"screen\00", align 1
@.str.41 = private unnamed_addr constant [16 x i8] c"screen-256color\00", align 1
@.str.42 = private unnamed_addr constant [20 x i8] c"screen-256color-bce\00", align 1
@.str.43 = private unnamed_addr constant [11 x i8] c"screen-bce\00", align 1
@.str.44 = private unnamed_addr constant [9 x i8] c"screen-w\00", align 1
@.str.45 = private unnamed_addr constant [13 x i8] c"screen.linux\00", align 1
@.str.46 = private unnamed_addr constant [5 x i8] c"tmux\00", align 1
@.str.47 = private unnamed_addr constant [14 x i8] c"tmux-256color\00", align 1
@.str.48 = private unnamed_addr constant [6 x i8] c"vt100\00", align 1
@.str.49 = private unnamed_addr constant [6 x i8] c"xterm\00", align 1
@.str.50 = private unnamed_addr constant [14 x i8] c"xterm-16color\00", align 1
@.str.51 = private unnamed_addr constant [15 x i8] c"xterm-256color\00", align 1
@.str.52 = private unnamed_addr constant [14 x i8] c"xterm-88color\00", align 1
@.str.53 = private unnamed_addr constant [12 x i8] c"xterm-color\00", align 1
@.str.54 = private unnamed_addr constant [13 x i8] c"xterm-debian\00", align 1
@.str.55 = private unnamed_addr constant [14 x i8] c"xterm-termite\00", align 1
@.str.56 = private unnamed_addr constant [5 x i8] c"\1B[0m\00", align 1
@.str.57 = private unnamed_addr constant [6 x i8] c"\1B[30m\00", align 1
@.str.58 = private unnamed_addr constant [6 x i8] c"\1B[31m\00", align 1
@.str.59 = private unnamed_addr constant [6 x i8] c"\1B[32m\00", align 1
@.str.60 = private unnamed_addr constant [6 x i8] c"\1B[33m\00", align 1
@.str.61 = private unnamed_addr constant [6 x i8] c"\1B[34m\00", align 1
@.str.62 = private unnamed_addr constant [6 x i8] c"\1B[35m\00", align 1
@.str.63 = private unnamed_addr constant [6 x i8] c"\1B[36m\00", align 1
@.str.64 = private unnamed_addr constant [6 x i8] c"\1B[37m\00", align 1
@.str.65 = private unnamed_addr constant [6 x i8] c"\1B[40m\00", align 1
@.str.66 = private unnamed_addr constant [6 x i8] c"\1B[41m\00", align 1
@.str.67 = private unnamed_addr constant [6 x i8] c"\1B[42m\00", align 1
@.str.68 = private unnamed_addr constant [6 x i8] c"\1B[43m\00", align 1
@.str.69 = private unnamed_addr constant [6 x i8] c"\1B[44m\00", align 1
@.str.70 = private unnamed_addr constant [6 x i8] c"\1B[45m\00", align 1
@.str.71 = private unnamed_addr constant [6 x i8] c"\1B[46m\00", align 1
@.str.72 = private unnamed_addr constant [6 x i8] c"\1B[47m\00", align 1
@.str.73 = private unnamed_addr constant [5 x i8] c"\1B[1m\00", align 1

; Function Attrs: nounwind uwtable
define void @cmsysTerminal_cfprintf(i32 %color, %struct._IO_FILE* %stream, i8* %format, ...) #0 !dbg !31 {
entry:
  %color.addr = alloca i32, align 4
  %stream.addr = alloca %struct._IO_FILE*, align 8
  %format.addr = alloca i8*, align 8
  %pipeIsConsole = alloca i32, align 4
  %pipeIsVT100 = alloca i32, align 4
  %default_vt100 = alloca i32, align 4
  %default_tty = alloca i32, align 4
  %var_args = alloca [1 x %struct.__va_list_tag], align 16
  store i32 %color, i32* %color.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %color.addr, metadata !114, metadata !115), !dbg !116
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !117, metadata !115), !dbg !118
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !119, metadata !115), !dbg !120
  call void @llvm.dbg.declare(metadata i32* %pipeIsConsole, metadata !121, metadata !115), !dbg !122
  store i32 0, i32* %pipeIsConsole, align 4, !dbg !122
  call void @llvm.dbg.declare(metadata i32* %pipeIsVT100, metadata !123, metadata !115), !dbg !124
  store i32 0, i32* %pipeIsVT100, align 4, !dbg !124
  call void @llvm.dbg.declare(metadata i32* %default_vt100, metadata !125, metadata !115), !dbg !126
  %0 = load i32, i32* %color.addr, align 4, !dbg !127
  %and = and i32 %0, 2048, !dbg !128
  store i32 %and, i32* %default_vt100, align 4, !dbg !126
  call void @llvm.dbg.declare(metadata i32* %default_tty, metadata !129, metadata !115), !dbg !130
  %1 = load i32, i32* %color.addr, align 4, !dbg !131
  %and1 = and i32 %1, 1024, !dbg !132
  store i32 %and1, i32* %default_tty, align 4, !dbg !130
  %2 = load i32, i32* %pipeIsConsole, align 4, !dbg !133
  %tobool = icmp ne i32 %2, 0, !dbg !133
  br i1 %tobool, label %if.end, label %land.lhs.true, !dbg !135

land.lhs.true:                                    ; preds = %entry
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !136
  %4 = load i32, i32* %default_vt100, align 4, !dbg !137
  %5 = load i32, i32* %default_tty, align 4, !dbg !138
  %call = call i32 @kwsysTerminalStreamIsVT100(%struct._IO_FILE* %3, i32 %4, i32 %5), !dbg !139
  %tobool2 = icmp ne i32 %call, 0, !dbg !139
  br i1 %tobool2, label %if.then, label %if.end, !dbg !140

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* %pipeIsVT100, align 4, !dbg !142
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !144
  %7 = load i32, i32* %color.addr, align 4, !dbg !145
  call void @kwsysTerminalSetVT100Color(%struct._IO_FILE* %6, i32 %7), !dbg !146
  br label %if.end, !dbg !147

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %var_args, metadata !148, metadata !115), !dbg !162
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %var_args, i32 0, i32 0, !dbg !163
  %arraydecay3 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !163
  call void @llvm.va_start(i8* %arraydecay3), !dbg !163
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !164
  %9 = load i8*, i8** %format.addr, align 8, !dbg !165
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %var_args, i32 0, i32 0, !dbg !166
  %call5 = call i32 @vfprintf(%struct._IO_FILE* %8, i8* %9, %struct.__va_list_tag* %arraydecay4), !dbg !167
  %arraydecay6 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %var_args, i32 0, i32 0, !dbg !168
  %arraydecay67 = bitcast %struct.__va_list_tag* %arraydecay6 to i8*, !dbg !168
  call void @llvm.va_end(i8* %arraydecay67), !dbg !168
  %10 = load i32, i32* %pipeIsVT100, align 4, !dbg !169
  %tobool8 = icmp ne i32 %10, 0, !dbg !169
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !171

if.then9:                                         ; preds = %if.end
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !172
  call void @kwsysTerminalSetVT100Color(%struct._IO_FILE* %11, i32 0), !dbg !174
  br label %if.end10, !dbg !175

if.end10:                                         ; preds = %if.then9, %if.end
  ret void, !dbg !176
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @kwsysTerminalStreamIsVT100(%struct._IO_FILE* %stream, i32 %default_vt100, i32 %default_tty) #0 !dbg !100 {
entry:
  %retval = alloca i32, align 4
  %stream.addr = alloca %struct._IO_FILE*, align 8
  %default_vt100.addr = alloca i32, align 4
  %default_tty.addr = alloca i32, align 4
  %clicolor_force = alloca i8*, align 8
  %emacs = alloca i8*, align 8
  %t = alloca i8**, align 8
  %term = alloca i8*, align 8
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !177, metadata !115), !dbg !178
  store i32 %default_vt100, i32* %default_vt100.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %default_vt100.addr, metadata !179, metadata !115), !dbg !180
  store i32 %default_tty, i32* %default_tty.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %default_tty.addr, metadata !181, metadata !115), !dbg !182
  call void @llvm.dbg.declare(metadata i8** %clicolor_force, metadata !183, metadata !115), !dbg !185
  %call = call i8* @getenv(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i32 0, i32 0)) #2, !dbg !186
  store i8* %call, i8** %clicolor_force, align 8, !dbg !185
  %0 = load i8*, i8** %clicolor_force, align 8, !dbg !187
  %tobool = icmp ne i8* %0, null, !dbg !187
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !189

land.lhs.true:                                    ; preds = %entry
  %1 = load i8*, i8** %clicolor_force, align 8, !dbg !190
  %2 = load i8, i8* %1, align 1, !dbg !192
  %conv = sext i8 %2 to i32, !dbg !192
  %tobool1 = icmp ne i32 %conv, 0, !dbg !192
  br i1 %tobool1, label %land.lhs.true2, label %if.end, !dbg !193

land.lhs.true2:                                   ; preds = %land.lhs.true
  %3 = load i8*, i8** %clicolor_force, align 8, !dbg !194
  %call3 = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0)) #6, !dbg !195
  %cmp = icmp ne i32 %call3, 0, !dbg !196
  br i1 %cmp, label %if.then, label %if.end, !dbg !197

if.then:                                          ; preds = %land.lhs.true2
  store i32 1, i32* %retval, align 4, !dbg !199
  br label %return, !dbg !199

if.end:                                           ; preds = %land.lhs.true2, %land.lhs.true, %entry
  call void @llvm.dbg.declare(metadata i8** %emacs, metadata !201, metadata !115), !dbg !203
  %call5 = call i8* @getenv(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0)) #2, !dbg !204
  store i8* %call5, i8** %emacs, align 8, !dbg !203
  %4 = load i8*, i8** %emacs, align 8, !dbg !205
  %tobool6 = icmp ne i8* %4, null, !dbg !205
  br i1 %tobool6, label %land.lhs.true7, label %if.end12, !dbg !207

land.lhs.true7:                                   ; preds = %if.end
  %5 = load i8*, i8** %emacs, align 8, !dbg !208
  %6 = load i8, i8* %5, align 1, !dbg !210
  %conv8 = sext i8 %6 to i32, !dbg !210
  %cmp9 = icmp eq i32 %conv8, 116, !dbg !211
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !212

if.then11:                                        ; preds = %land.lhs.true7
  store i32 0, i32* %retval, align 4, !dbg !213
  br label %return, !dbg !213

if.end12:                                         ; preds = %land.lhs.true7, %if.end
  %7 = load i32, i32* %default_vt100.addr, align 4, !dbg !215
  %tobool13 = icmp ne i32 %7, 0, !dbg !215
  br i1 %tobool13, label %if.end28, label %if.then14, !dbg !217

if.then14:                                        ; preds = %if.end12
  call void @llvm.dbg.declare(metadata i8*** %t, metadata !218, metadata !115), !dbg !221
  store i8** null, i8*** %t, align 8, !dbg !221
  call void @llvm.dbg.declare(metadata i8** %term, metadata !222, metadata !115), !dbg !223
  %call15 = call i8* @getenv(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0)) #2, !dbg !224
  store i8* %call15, i8** %term, align 8, !dbg !223
  %8 = load i8*, i8** %term, align 8, !dbg !225
  %tobool16 = icmp ne i8* %8, null, !dbg !225
  br i1 %tobool16, label %if.then17, label %if.end22, !dbg !227

if.then17:                                        ; preds = %if.then14
  store i8** getelementptr inbounds ([53 x i8*], [53 x i8*]* @kwsysTerminalVT100Names, i32 0, i32 0), i8*** %t, align 8, !dbg !228
  br label %for.cond, !dbg !231

for.cond:                                         ; preds = %for.inc, %if.then17
  %9 = load i8**, i8*** %t, align 8, !dbg !232
  %10 = load i8*, i8** %9, align 8, !dbg !235
  %tobool18 = icmp ne i8* %10, null, !dbg !235
  br i1 %tobool18, label %land.rhs, label %land.end, !dbg !236

land.rhs:                                         ; preds = %for.cond
  %11 = load i8*, i8** %term, align 8, !dbg !237
  %12 = load i8**, i8*** %t, align 8, !dbg !239
  %13 = load i8*, i8** %12, align 8, !dbg !240
  %call19 = call i32 @strcmp(i8* %11, i8* %13) #6, !dbg !241
  %cmp20 = icmp ne i32 %call19, 0, !dbg !242
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %14 = phi i1 [ false, %for.cond ], [ %cmp20, %land.rhs ]
  br i1 %14, label %for.body, label %for.end, !dbg !243

for.body:                                         ; preds = %land.end
  br label %for.inc, !dbg !245

for.inc:                                          ; preds = %for.body
  %15 = load i8**, i8*** %t, align 8, !dbg !247
  %incdec.ptr = getelementptr inbounds i8*, i8** %15, i32 1, !dbg !247
  store i8** %incdec.ptr, i8*** %t, align 8, !dbg !247
  br label %for.cond, !dbg !249

for.end:                                          ; preds = %land.end
  br label %if.end22, !dbg !250

if.end22:                                         ; preds = %for.end, %if.then14
  %16 = load i8**, i8*** %t, align 8, !dbg !251
  %tobool23 = icmp ne i8** %16, null, !dbg !251
  br i1 %tobool23, label %land.lhs.true24, label %if.then26, !dbg !253

land.lhs.true24:                                  ; preds = %if.end22
  %17 = load i8**, i8*** %t, align 8, !dbg !254
  %18 = load i8*, i8** %17, align 8, !dbg !256
  %tobool25 = icmp ne i8* %18, null, !dbg !256
  br i1 %tobool25, label %if.end27, label %if.then26, !dbg !257

if.then26:                                        ; preds = %land.lhs.true24, %if.end22
  store i32 0, i32* %retval, align 4, !dbg !258
  br label %return, !dbg !258

if.end27:                                         ; preds = %land.lhs.true24
  br label %if.end28, !dbg !260

if.end28:                                         ; preds = %if.end27, %if.end12
  %19 = load i32, i32* %default_tty.addr, align 4, !dbg !261
  %20 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !262
  %call29 = call i32 @fileno(%struct._IO_FILE* %20) #2, !dbg !263
  %call30 = call i32 @isatty(i32 %call29) #2, !dbg !264
  %tobool31 = icmp ne i32 %call30, 0, !dbg !266
  %cond = select i1 %tobool31, i32 1, i32 0, !dbg !266
  store i32 %cond, i32* %retval, align 4, !dbg !267
  br label %return, !dbg !267

return:                                           ; preds = %if.end28, %if.then26, %if.then11, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !268
  ret i32 %21, !dbg !268
}

; Function Attrs: nounwind uwtable
define internal void @kwsysTerminalSetVT100Color(%struct._IO_FILE* %stream, i32 %color) #0 !dbg !103 {
entry:
  %stream.addr = alloca %struct._IO_FILE*, align 8
  %color.addr = alloca i32, align 4
  store %struct._IO_FILE* %stream, %struct._IO_FILE** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %stream.addr, metadata !269, metadata !115), !dbg !270
  store i32 %color, i32* %color.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %color.addr, metadata !271, metadata !115), !dbg !272
  %0 = load i32, i32* %color.addr, align 4, !dbg !273
  %cmp = icmp eq i32 %0, 0, !dbg !275
  br i1 %cmp, label %if.then, label %if.end, !dbg !276

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !277
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.56, i32 0, i32 0)), !dbg !279
  br label %if.end39, !dbg !280

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %color.addr, align 4, !dbg !281
  %and = and i32 %2, 15, !dbg !282
  switch i32 %and, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb2
    i32 2, label %sw.bb4
    i32 3, label %sw.bb6
    i32 4, label %sw.bb8
    i32 5, label %sw.bb10
    i32 6, label %sw.bb12
    i32 7, label %sw.bb14
    i32 8, label %sw.bb16
  ], !dbg !283

sw.bb:                                            ; preds = %if.end
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !284
  %call1 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.56, i32 0, i32 0)), !dbg !286
  br label %sw.epilog, !dbg !287

sw.bb2:                                           ; preds = %if.end
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !288
  %call3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.57, i32 0, i32 0)), !dbg !289
  br label %sw.epilog, !dbg !290

sw.bb4:                                           ; preds = %if.end
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !291
  %call5 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.58, i32 0, i32 0)), !dbg !292
  br label %sw.epilog, !dbg !293

sw.bb6:                                           ; preds = %if.end
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !294
  %call7 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.59, i32 0, i32 0)), !dbg !295
  br label %sw.epilog, !dbg !296

sw.bb8:                                           ; preds = %if.end
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !297
  %call9 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %7, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.60, i32 0, i32 0)), !dbg !298
  br label %sw.epilog, !dbg !299

sw.bb10:                                          ; preds = %if.end
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !300
  %call11 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %8, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.61, i32 0, i32 0)), !dbg !301
  br label %sw.epilog, !dbg !302

sw.bb12:                                          ; preds = %if.end
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !303
  %call13 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %9, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.62, i32 0, i32 0)), !dbg !304
  br label %sw.epilog, !dbg !305

sw.bb14:                                          ; preds = %if.end
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !306
  %call15 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %10, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.63, i32 0, i32 0)), !dbg !307
  br label %sw.epilog, !dbg !308

sw.bb16:                                          ; preds = %if.end
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !309
  %call17 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %11, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.64, i32 0, i32 0)), !dbg !310
  br label %sw.epilog, !dbg !311

sw.epilog:                                        ; preds = %if.end, %sw.bb16, %sw.bb14, %sw.bb12, %sw.bb10, %sw.bb8, %sw.bb6, %sw.bb4, %sw.bb2, %sw.bb
  %12 = load i32, i32* %color.addr, align 4, !dbg !312
  %and18 = and i32 %12, 240, !dbg !313
  switch i32 %and18, label %sw.epilog35 [
    i32 16, label %sw.bb19
    i32 32, label %sw.bb21
    i32 48, label %sw.bb23
    i32 64, label %sw.bb25
    i32 80, label %sw.bb27
    i32 96, label %sw.bb29
    i32 112, label %sw.bb31
    i32 128, label %sw.bb33
  ], !dbg !314

sw.bb19:                                          ; preds = %sw.epilog
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !315
  %call20 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.65, i32 0, i32 0)), !dbg !317
  br label %sw.epilog35, !dbg !318

sw.bb21:                                          ; preds = %sw.epilog
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !319
  %call22 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %14, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.66, i32 0, i32 0)), !dbg !320
  br label %sw.epilog35, !dbg !321

sw.bb23:                                          ; preds = %sw.epilog
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !322
  %call24 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %15, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.67, i32 0, i32 0)), !dbg !323
  br label %sw.epilog35, !dbg !324

sw.bb25:                                          ; preds = %sw.epilog
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !325
  %call26 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %16, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.68, i32 0, i32 0)), !dbg !326
  br label %sw.epilog35, !dbg !327

sw.bb27:                                          ; preds = %sw.epilog
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !328
  %call28 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %17, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.69, i32 0, i32 0)), !dbg !329
  br label %sw.epilog35, !dbg !330

sw.bb29:                                          ; preds = %sw.epilog
  %18 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !331
  %call30 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %18, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.70, i32 0, i32 0)), !dbg !332
  br label %sw.epilog35, !dbg !333

sw.bb31:                                          ; preds = %sw.epilog
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !334
  %call32 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %19, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.71, i32 0, i32 0)), !dbg !335
  br label %sw.epilog35, !dbg !336

sw.bb33:                                          ; preds = %sw.epilog
  %20 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !337
  %call34 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %20, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.72, i32 0, i32 0)), !dbg !338
  br label %sw.epilog35, !dbg !339

sw.epilog35:                                      ; preds = %sw.epilog, %sw.bb33, %sw.bb31, %sw.bb29, %sw.bb27, %sw.bb25, %sw.bb23, %sw.bb21, %sw.bb19
  %21 = load i32, i32* %color.addr, align 4, !dbg !340
  %and36 = and i32 %21, 256, !dbg !342
  %tobool = icmp ne i32 %and36, 0, !dbg !342
  br i1 %tobool, label %if.then37, label %if.end39, !dbg !343

if.then37:                                        ; preds = %sw.epilog35
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %stream.addr, align 8, !dbg !344
  %call38 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %22, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.73, i32 0, i32 0)), !dbg !346
  br label %if.end39, !dbg !347

if.end39:                                         ; preds = %if.then, %if.then37, %sw.epilog35
  ret void, !dbg !348
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

declare i32 @vfprintf(%struct._IO_FILE*, i8*, %struct.__va_list_tag*) #3

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

; Function Attrs: nounwind
declare i8* @getenv(i8*) #4

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #5

; Function Attrs: nounwind
declare i32 @isatty(i32) #4

; Function Attrs: nounwind
declare i32 @fileno(%struct._IO_FILE*) #4

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!111, !112}
!llvm.ident = !{!113}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !30, globals: !106)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/Terminal.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "cmsysTerminal_Color_e", file: !4, line: 96, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/cmsys/Terminal.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29}
!6 = !DIEnumerator(name: "cmsysTerminal_Color_Normal", value: 0)
!7 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBlack", value: 1)
!8 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundRed", value: 2)
!9 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundGreen", value: 3)
!10 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundYellow", value: 4)
!11 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBlue", value: 5)
!12 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundMagenta", value: 6)
!13 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundCyan", value: 7)
!14 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundWhite", value: 8)
!15 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundMask", value: 15)
!16 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBlack", value: 16)
!17 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundRed", value: 32)
!18 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundGreen", value: 48)
!19 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundYellow", value: 64)
!20 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBlue", value: 80)
!21 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundMagenta", value: 96)
!22 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundCyan", value: 112)
!23 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundWhite", value: 128)
!24 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundMask", value: 240)
!25 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBold", value: 256)
!26 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBold", value: 512)
!27 = !DIEnumerator(name: "cmsysTerminal_Color_AssumeTTY", value: 1024)
!28 = !DIEnumerator(name: "cmsysTerminal_Color_AssumeVT100", value: 2048)
!29 = !DIEnumerator(name: "cmsysTerminal_Color_AttributeMask", value: 3840)
!30 = !{!31, !100, !103}
!31 = distinct !DISubprogram(name: "cmsysTerminal_cfprintf", scope: !1, file: !1, line: 47, type: !32, isLocal: false, isDefinition: true, scopeLine: 48, flags: DIFlagPrototyped, isOptimized: false, variables: !99)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !34, !35, !97, null}
!34 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !37, line: 48, baseType: !38)
!37 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!38 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !39, line: 245, size: 1728, align: 64, elements: !40)
!39 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!40 = !{!41, !42, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !63, !64, !65, !66, !70, !72, !74, !78, !81, !83, !85, !86, !87, !88, !92, !93}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !38, file: !39, line: 246, baseType: !34, size: 32, align: 32)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !38, file: !39, line: 251, baseType: !43, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !38, file: !39, line: 252, baseType: !43, size: 64, align: 64, offset: 128)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !38, file: !39, line: 253, baseType: !43, size: 64, align: 64, offset: 192)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !38, file: !39, line: 254, baseType: !43, size: 64, align: 64, offset: 256)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !38, file: !39, line: 255, baseType: !43, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !38, file: !39, line: 256, baseType: !43, size: 64, align: 64, offset: 384)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !38, file: !39, line: 257, baseType: !43, size: 64, align: 64, offset: 448)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !38, file: !39, line: 258, baseType: !43, size: 64, align: 64, offset: 512)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !38, file: !39, line: 260, baseType: !43, size: 64, align: 64, offset: 576)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !38, file: !39, line: 261, baseType: !43, size: 64, align: 64, offset: 640)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !38, file: !39, line: 262, baseType: !43, size: 64, align: 64, offset: 704)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !38, file: !39, line: 264, baseType: !56, size: 64, align: 64, offset: 768)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !39, line: 160, size: 192, align: 64, elements: !58)
!58 = !{!59, !60, !62}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !57, file: !39, line: 161, baseType: !56, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !57, file: !39, line: 162, baseType: !61, size: 64, align: 64, offset: 64)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !57, file: !39, line: 166, baseType: !34, size: 32, align: 32, offset: 128)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !38, file: !39, line: 266, baseType: !61, size: 64, align: 64, offset: 832)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !38, file: !39, line: 268, baseType: !34, size: 32, align: 32, offset: 896)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !38, file: !39, line: 272, baseType: !34, size: 32, align: 32, offset: 928)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !38, file: !39, line: 274, baseType: !67, size: 64, align: 64, offset: 960)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !68, line: 131, baseType: !69)
!68 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!69 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !38, file: !39, line: 278, baseType: !71, size: 16, align: 16, offset: 1024)
!71 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !38, file: !39, line: 279, baseType: !73, size: 8, align: 8, offset: 1040)
!73 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !38, file: !39, line: 280, baseType: !75, size: 8, align: 8, offset: 1048)
!75 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 8, align: 8, elements: !76)
!76 = !{!77}
!77 = !DISubrange(count: 1)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !38, file: !39, line: 284, baseType: !79, size: 64, align: 64, offset: 1088)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !39, line: 154, baseType: null)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !38, file: !39, line: 293, baseType: !82, size: 64, align: 64, offset: 1152)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !68, line: 132, baseType: !69)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !38, file: !39, line: 302, baseType: !84, size: 64, align: 64, offset: 1216)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !38, file: !39, line: 303, baseType: !84, size: 64, align: 64, offset: 1280)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !38, file: !39, line: 304, baseType: !84, size: 64, align: 64, offset: 1344)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !38, file: !39, line: 305, baseType: !84, size: 64, align: 64, offset: 1408)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !38, file: !39, line: 306, baseType: !89, size: 64, align: 64, offset: 1472)
!89 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !90, line: 62, baseType: !91)
!90 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!91 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !38, file: !39, line: 308, baseType: !34, size: 32, align: 32, offset: 1536)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !38, file: !39, line: 310, baseType: !94, size: 160, align: 8, offset: 1568)
!94 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 160, align: 8, elements: !95)
!95 = !{!96}
!96 = !DISubrange(count: 20)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !44)
!99 = !{}
!100 = distinct !DISubprogram(name: "kwsysTerminalStreamIsVT100", scope: !1, file: !1, line: 160, type: !101, isLocal: true, isDefinition: true, scopeLine: 162, flags: DIFlagPrototyped, isOptimized: false, variables: !99)
!101 = !DISubroutineType(types: !102)
!102 = !{!34, !35, !34, !34}
!103 = distinct !DISubprogram(name: "kwsysTerminalSetVT100Color", scope: !1, file: !1, line: 234, type: !104, isLocal: true, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !99)
!104 = !DISubroutineType(types: !105)
!105 = !{null, !35, !34}
!106 = !{!107}
!107 = !DIGlobalVariable(name: "kwsysTerminalVT100Names", scope: !0, file: !1, line: 105, type: !108, isLocal: true, isDefinition: true, variable: [53 x i8*]* @kwsysTerminalVT100Names)
!108 = !DICompositeType(tag: DW_TAG_array_type, baseType: !97, size: 3392, align: 64, elements: !109)
!109 = !{!110}
!110 = !DISubrange(count: 53)
!111 = !{i32 2, !"Dwarf Version", i32 4}
!112 = !{i32 2, !"Debug Info Version", i32 3}
!113 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!114 = !DILocalVariable(name: "color", arg: 1, scope: !31, file: !1, line: 47, type: !34)
!115 = !DIExpression()
!116 = !DILocation(line: 47, column: 33, scope: !31)
!117 = !DILocalVariable(name: "stream", arg: 2, scope: !31, file: !1, line: 47, type: !35)
!118 = !DILocation(line: 47, column: 46, scope: !31)
!119 = !DILocalVariable(name: "format", arg: 3, scope: !31, file: !1, line: 47, type: !97)
!120 = !DILocation(line: 47, column: 66, scope: !31)
!121 = !DILocalVariable(name: "pipeIsConsole", scope: !31, file: !1, line: 50, type: !34)
!122 = !DILocation(line: 50, column: 7, scope: !31)
!123 = !DILocalVariable(name: "pipeIsVT100", scope: !31, file: !1, line: 51, type: !34)
!124 = !DILocation(line: 51, column: 7, scope: !31)
!125 = !DILocalVariable(name: "default_vt100", scope: !31, file: !1, line: 52, type: !34)
!126 = !DILocation(line: 52, column: 7, scope: !31)
!127 = !DILocation(line: 52, column: 23, scope: !31)
!128 = !DILocation(line: 52, column: 29, scope: !31)
!129 = !DILocalVariable(name: "default_tty", scope: !31, file: !1, line: 53, type: !34)
!130 = !DILocation(line: 53, column: 7, scope: !31)
!131 = !DILocation(line: 53, column: 21, scope: !31)
!132 = !DILocation(line: 53, column: 27, scope: !31)
!133 = !DILocation(line: 62, column: 8, scope: !134)
!134 = distinct !DILexicalBlock(scope: !31, file: !1, line: 62, column: 7)
!135 = !DILocation(line: 62, column: 22, scope: !134)
!136 = !DILocation(line: 63, column: 34, scope: !134)
!137 = !DILocation(line: 63, column: 42, scope: !134)
!138 = !DILocation(line: 63, column: 57, scope: !134)
!139 = !DILocation(line: 63, column: 7, scope: !134)
!140 = !DILocation(line: 62, column: 7, scope: !141)
!141 = !DILexicalBlockFile(scope: !31, file: !1, discriminator: 1)
!142 = !DILocation(line: 64, column: 17, scope: !143)
!143 = distinct !DILexicalBlock(scope: !134, file: !1, line: 63, column: 71)
!144 = !DILocation(line: 65, column: 32, scope: !143)
!145 = !DILocation(line: 65, column: 40, scope: !143)
!146 = !DILocation(line: 65, column: 5, scope: !143)
!147 = !DILocation(line: 66, column: 3, scope: !143)
!148 = !DILocalVariable(name: "var_args", scope: !149, file: !1, line: 70, type: !150)
!149 = distinct !DILexicalBlock(scope: !31, file: !1, line: 69, column: 3)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !37, line: 79, baseType: !151)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !152, line: 50, baseType: !153)
!152 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 70, baseType: !154)
!154 = !DICompositeType(tag: DW_TAG_array_type, baseType: !155, size: 192, align: 64, elements: !76)
!155 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 70, size: 192, align: 64, elements: !156)
!156 = !{!157, !159, !160, !161}
!157 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !155, file: !1, line: 70, baseType: !158, size: 32, align: 32)
!158 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !155, file: !1, line: 70, baseType: !158, size: 32, align: 32, offset: 32)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !155, file: !1, line: 70, baseType: !84, size: 64, align: 64, offset: 64)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !155, file: !1, line: 70, baseType: !84, size: 64, align: 64, offset: 128)
!162 = !DILocation(line: 70, column: 13, scope: !149)
!163 = !DILocation(line: 71, column: 5, scope: !149)
!164 = !DILocation(line: 72, column: 14, scope: !149)
!165 = !DILocation(line: 72, column: 22, scope: !149)
!166 = !DILocation(line: 72, column: 30, scope: !149)
!167 = !DILocation(line: 72, column: 5, scope: !149)
!168 = !DILocation(line: 73, column: 5, scope: !149)
!169 = !DILocation(line: 83, column: 7, scope: !170)
!170 = distinct !DILexicalBlock(scope: !31, file: !1, line: 83, column: 7)
!171 = !DILocation(line: 83, column: 7, scope: !31)
!172 = !DILocation(line: 84, column: 32, scope: !173)
!173 = distinct !DILexicalBlock(scope: !170, file: !1, line: 83, column: 20)
!174 = !DILocation(line: 84, column: 5, scope: !173)
!175 = !DILocation(line: 85, column: 3, scope: !173)
!176 = !DILocation(line: 86, column: 1, scope: !31)
!177 = !DILocalVariable(name: "stream", arg: 1, scope: !100, file: !1, line: 160, type: !35)
!178 = !DILocation(line: 160, column: 45, scope: !100)
!179 = !DILocalVariable(name: "default_vt100", arg: 2, scope: !100, file: !1, line: 160, type: !34)
!180 = !DILocation(line: 160, column: 57, scope: !100)
!181 = !DILocalVariable(name: "default_tty", arg: 3, scope: !100, file: !1, line: 161, type: !34)
!182 = !DILocation(line: 161, column: 43, scope: !100)
!183 = !DILocalVariable(name: "clicolor_force", scope: !184, file: !1, line: 165, type: !97)
!184 = distinct !DILexicalBlock(scope: !100, file: !1, line: 164, column: 3)
!185 = !DILocation(line: 165, column: 17, scope: !184)
!186 = !DILocation(line: 165, column: 34, scope: !184)
!187 = !DILocation(line: 166, column: 9, scope: !188)
!188 = distinct !DILexicalBlock(scope: !184, file: !1, line: 166, column: 9)
!189 = !DILocation(line: 166, column: 24, scope: !188)
!190 = !DILocation(line: 166, column: 28, scope: !191)
!191 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 1)
!192 = !DILocation(line: 166, column: 27, scope: !191)
!193 = !DILocation(line: 166, column: 43, scope: !191)
!194 = !DILocation(line: 167, column: 16, scope: !188)
!195 = !DILocation(line: 167, column: 9, scope: !188)
!196 = !DILocation(line: 167, column: 37, scope: !188)
!197 = !DILocation(line: 166, column: 9, scope: !198)
!198 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 2)
!199 = !DILocation(line: 168, column: 7, scope: !200)
!200 = distinct !DILexicalBlock(scope: !188, file: !1, line: 167, column: 43)
!201 = !DILocalVariable(name: "emacs", scope: !202, file: !1, line: 176, type: !97)
!202 = distinct !DILexicalBlock(scope: !100, file: !1, line: 175, column: 3)
!203 = !DILocation(line: 176, column: 17, scope: !202)
!204 = !DILocation(line: 176, column: 25, scope: !202)
!205 = !DILocation(line: 177, column: 9, scope: !206)
!206 = distinct !DILexicalBlock(scope: !202, file: !1, line: 177, column: 9)
!207 = !DILocation(line: 177, column: 15, scope: !206)
!208 = !DILocation(line: 177, column: 19, scope: !209)
!209 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!210 = !DILocation(line: 177, column: 18, scope: !209)
!211 = !DILocation(line: 177, column: 25, scope: !209)
!212 = !DILocation(line: 177, column: 9, scope: !209)
!213 = !DILocation(line: 178, column: 7, scope: !214)
!214 = distinct !DILexicalBlock(scope: !206, file: !1, line: 177, column: 33)
!215 = !DILocation(line: 183, column: 8, scope: !216)
!216 = distinct !DILexicalBlock(scope: !100, file: !1, line: 183, column: 7)
!217 = !DILocation(line: 183, column: 7, scope: !100)
!218 = !DILocalVariable(name: "t", scope: !219, file: !1, line: 184, type: !220)
!219 = distinct !DILexicalBlock(scope: !216, file: !1, line: 183, column: 23)
!220 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!221 = !DILocation(line: 184, column: 18, scope: !219)
!222 = !DILocalVariable(name: "term", scope: !219, file: !1, line: 185, type: !97)
!223 = !DILocation(line: 185, column: 17, scope: !219)
!224 = !DILocation(line: 185, column: 24, scope: !219)
!225 = !DILocation(line: 186, column: 9, scope: !226)
!226 = distinct !DILexicalBlock(scope: !219, file: !1, line: 186, column: 9)
!227 = !DILocation(line: 186, column: 9, scope: !219)
!228 = !DILocation(line: 187, column: 14, scope: !229)
!229 = distinct !DILexicalBlock(scope: !230, file: !1, line: 187, column: 7)
!230 = distinct !DILexicalBlock(scope: !226, file: !1, line: 186, column: 15)
!231 = !DILocation(line: 187, column: 12, scope: !229)
!232 = !DILocation(line: 187, column: 42, scope: !233)
!233 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 1)
!234 = distinct !DILexicalBlock(scope: !229, file: !1, line: 187, column: 7)
!235 = !DILocation(line: 187, column: 41, scope: !233)
!236 = !DILocation(line: 187, column: 44, scope: !233)
!237 = !DILocation(line: 187, column: 54, scope: !238)
!238 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 2)
!239 = !DILocation(line: 187, column: 61, scope: !238)
!240 = !DILocation(line: 187, column: 60, scope: !238)
!241 = !DILocation(line: 187, column: 47, scope: !238)
!242 = !DILocation(line: 187, column: 64, scope: !238)
!243 = !DILocation(line: 187, column: 7, scope: !244)
!244 = !DILexicalBlockFile(scope: !229, file: !1, discriminator: 3)
!245 = !DILocation(line: 188, column: 7, scope: !246)
!246 = distinct !DILexicalBlock(scope: !234, file: !1, line: 187, column: 75)
!247 = !DILocation(line: 187, column: 70, scope: !248)
!248 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 4)
!249 = !DILocation(line: 187, column: 7, scope: !248)
!250 = !DILocation(line: 189, column: 5, scope: !230)
!251 = !DILocation(line: 190, column: 11, scope: !252)
!252 = distinct !DILexicalBlock(scope: !219, file: !1, line: 190, column: 9)
!253 = !DILocation(line: 190, column: 13, scope: !252)
!254 = !DILocation(line: 190, column: 17, scope: !255)
!255 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 1)
!256 = !DILocation(line: 190, column: 16, scope: !255)
!257 = !DILocation(line: 190, column: 9, scope: !255)
!258 = !DILocation(line: 191, column: 7, scope: !259)
!259 = distinct !DILexicalBlock(scope: !252, file: !1, line: 190, column: 21)
!260 = !DILocation(line: 193, column: 3, scope: !219)
!261 = !DILocation(line: 197, column: 9, scope: !100)
!262 = !DILocation(line: 198, column: 24, scope: !100)
!263 = !DILocation(line: 198, column: 17, scope: !100)
!264 = !DILocation(line: 198, column: 10, scope: !265)
!265 = !DILexicalBlockFile(scope: !100, file: !1, discriminator: 1)
!266 = !DILocation(line: 198, column: 10, scope: !100)
!267 = !DILocation(line: 198, column: 3, scope: !100)
!268 = !DILocation(line: 208, column: 1, scope: !100)
!269 = !DILocalVariable(name: "stream", arg: 1, scope: !103, file: !1, line: 234, type: !35)
!270 = !DILocation(line: 234, column: 46, scope: !103)
!271 = !DILocalVariable(name: "color", arg: 2, scope: !103, file: !1, line: 234, type: !34)
!272 = !DILocation(line: 234, column: 58, scope: !103)
!273 = !DILocation(line: 236, column: 7, scope: !274)
!274 = distinct !DILexicalBlock(scope: !103, file: !1, line: 236, column: 7)
!275 = !DILocation(line: 236, column: 13, scope: !274)
!276 = !DILocation(line: 236, column: 7, scope: !103)
!277 = !DILocation(line: 237, column: 13, scope: !278)
!278 = distinct !DILexicalBlock(scope: !274, file: !1, line: 236, column: 44)
!279 = !DILocation(line: 237, column: 5, scope: !278)
!280 = !DILocation(line: 238, column: 5, scope: !278)
!281 = !DILocation(line: 241, column: 11, scope: !103)
!282 = !DILocation(line: 241, column: 17, scope: !103)
!283 = !DILocation(line: 241, column: 3, scope: !103)
!284 = !DILocation(line: 243, column: 15, scope: !285)
!285 = distinct !DILexicalBlock(scope: !103, file: !1, line: 241, column: 55)
!286 = !DILocation(line: 243, column: 7, scope: !285)
!287 = !DILocation(line: 244, column: 7, scope: !285)
!288 = !DILocation(line: 246, column: 15, scope: !285)
!289 = !DILocation(line: 246, column: 7, scope: !285)
!290 = !DILocation(line: 247, column: 7, scope: !285)
!291 = !DILocation(line: 249, column: 15, scope: !285)
!292 = !DILocation(line: 249, column: 7, scope: !285)
!293 = !DILocation(line: 250, column: 7, scope: !285)
!294 = !DILocation(line: 252, column: 15, scope: !285)
!295 = !DILocation(line: 252, column: 7, scope: !285)
!296 = !DILocation(line: 253, column: 7, scope: !285)
!297 = !DILocation(line: 255, column: 15, scope: !285)
!298 = !DILocation(line: 255, column: 7, scope: !285)
!299 = !DILocation(line: 256, column: 7, scope: !285)
!300 = !DILocation(line: 258, column: 15, scope: !285)
!301 = !DILocation(line: 258, column: 7, scope: !285)
!302 = !DILocation(line: 259, column: 7, scope: !285)
!303 = !DILocation(line: 261, column: 15, scope: !285)
!304 = !DILocation(line: 261, column: 7, scope: !285)
!305 = !DILocation(line: 262, column: 7, scope: !285)
!306 = !DILocation(line: 264, column: 15, scope: !285)
!307 = !DILocation(line: 264, column: 7, scope: !285)
!308 = !DILocation(line: 265, column: 7, scope: !285)
!309 = !DILocation(line: 267, column: 15, scope: !285)
!310 = !DILocation(line: 267, column: 7, scope: !285)
!311 = !DILocation(line: 268, column: 7, scope: !285)
!312 = !DILocation(line: 270, column: 11, scope: !103)
!313 = !DILocation(line: 270, column: 17, scope: !103)
!314 = !DILocation(line: 270, column: 3, scope: !103)
!315 = !DILocation(line: 272, column: 15, scope: !316)
!316 = distinct !DILexicalBlock(scope: !103, file: !1, line: 270, column: 55)
!317 = !DILocation(line: 272, column: 7, scope: !316)
!318 = !DILocation(line: 273, column: 7, scope: !316)
!319 = !DILocation(line: 275, column: 15, scope: !316)
!320 = !DILocation(line: 275, column: 7, scope: !316)
!321 = !DILocation(line: 276, column: 7, scope: !316)
!322 = !DILocation(line: 278, column: 15, scope: !316)
!323 = !DILocation(line: 278, column: 7, scope: !316)
!324 = !DILocation(line: 279, column: 7, scope: !316)
!325 = !DILocation(line: 281, column: 15, scope: !316)
!326 = !DILocation(line: 281, column: 7, scope: !316)
!327 = !DILocation(line: 282, column: 7, scope: !316)
!328 = !DILocation(line: 284, column: 15, scope: !316)
!329 = !DILocation(line: 284, column: 7, scope: !316)
!330 = !DILocation(line: 285, column: 7, scope: !316)
!331 = !DILocation(line: 287, column: 15, scope: !316)
!332 = !DILocation(line: 287, column: 7, scope: !316)
!333 = !DILocation(line: 288, column: 7, scope: !316)
!334 = !DILocation(line: 290, column: 15, scope: !316)
!335 = !DILocation(line: 290, column: 7, scope: !316)
!336 = !DILocation(line: 291, column: 7, scope: !316)
!337 = !DILocation(line: 293, column: 15, scope: !316)
!338 = !DILocation(line: 293, column: 7, scope: !316)
!339 = !DILocation(line: 294, column: 7, scope: !316)
!340 = !DILocation(line: 296, column: 7, scope: !341)
!341 = distinct !DILexicalBlock(scope: !103, file: !1, line: 296, column: 7)
!342 = !DILocation(line: 296, column: 13, scope: !341)
!343 = !DILocation(line: 296, column: 7, scope: !103)
!344 = !DILocation(line: 297, column: 13, scope: !345)
!345 = distinct !DILexicalBlock(scope: !341, file: !1, line: 296, column: 51)
!346 = !DILocation(line: 297, column: 5, scope: !345)
!347 = !DILocation(line: 298, column: 3, scope: !345)
!348 = !DILocation(line: 299, column: 1, scope: !103)
