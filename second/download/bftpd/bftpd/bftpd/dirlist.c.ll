; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.hidegroup = type { i32, %struct.hidegroup* }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.group = type { i8*, i8*, i32, i8** }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }
%struct.__dirstream = type opaque
%struct.dirent = type { i64, i64, i16, i8, [256 x i8] }

@hidegroups = global %struct.hidegroup* null, align 8
@add_to_hidegroups.tmp = internal global %struct.hidegroup* null, align 8
@.str = private unnamed_addr constant [11 x i8] c"HIDE_GROUP\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.3 = private unnamed_addr constant [16 x i8] c"213-Error: %s.\0A\00", align 1
@.str.4 = private unnamed_addr constant [11 x i8] c"lrwxrwxrwx\00", align 1
@.str.5 = private unnamed_addr constant [7 x i8] c" -> %s\00", align 1
@.str.6 = private unnamed_addr constant [11 x i8] c"----------\00", align 1
@.str.7 = private unnamed_addr constant [10 x i8] c"%b %d  %G\00", align 1
@passwdfile = external global %struct._IO_FILE*, align 8
@groupfile = external global %struct._IO_FILE*, align 8
@.str.8 = private unnamed_addr constant [32 x i8] c"%s %3i %-8s %-8s %llu %s %s%s\0D\0A\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"%s\0D\0A\00", align 1
@.str.10 = private unnamed_addr constant [18 x i8] c"SHOW_HIDDEN_FILES\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"yes\00", align 1
@.str.12 = private unnamed_addr constant [7 x i8] c"always\00", align 1
@.str.13 = private unnamed_addr constant [23 x i8] c"SHOW_NONREADABLE_FILES\00", align 1
@.str.14 = private unnamed_addr constant [3 x i8] c"/.\00", align 1
@.str.15 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.16 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@configpath = common global i8* null, align 8
@daemonmode = common global i32 0, align 4
@pre_write_script = common global i8* null, align 8
@post_write_script = common global i8* null, align 8

; Function Attrs: nounwind uwtable
define void @add_to_hidegroups(i32 %gid) #0 !dbg !49 {
entry:
  %gid.addr = alloca i32, align 4
  store i32 %gid, i32* %gid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %gid.addr, metadata !141, metadata !142), !dbg !143
  %0 = load %struct.hidegroup*, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !144
  %tobool = icmp ne %struct.hidegroup* %0, null, !dbg !144
  br i1 %tobool, label %if.then, label %if.else, !dbg !146

if.then:                                          ; preds = %entry
  %call = call noalias i8* @malloc(i64 16) #7, !dbg !147
  %1 = bitcast i8* %call to %struct.hidegroup*, !dbg !147
  %2 = load %struct.hidegroup*, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !148
  %next = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %2, i32 0, i32 1, !dbg !149
  store %struct.hidegroup* %1, %struct.hidegroup** %next, align 8, !dbg !150
  store %struct.hidegroup* %1, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !151
  br label %if.end, !dbg !152

if.else:                                          ; preds = %entry
  %call1 = call noalias i8* @malloc(i64 16) #7, !dbg !153
  %3 = bitcast i8* %call1 to %struct.hidegroup*, !dbg !153
  store %struct.hidegroup* %3, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !154
  store %struct.hidegroup* %3, %struct.hidegroup** @hidegroups, align 8, !dbg !155
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %4 = load %struct.hidegroup*, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !156
  %tobool2 = icmp ne %struct.hidegroup* %4, null, !dbg !156
  br i1 %tobool2, label %if.then3, label %if.end5, !dbg !158

if.then3:                                         ; preds = %if.end
  %5 = load %struct.hidegroup*, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !159
  %next4 = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %5, i32 0, i32 1, !dbg !161
  store %struct.hidegroup* null, %struct.hidegroup** %next4, align 8, !dbg !162
  %6 = load i32, i32* %gid.addr, align 4, !dbg !163
  %7 = load %struct.hidegroup*, %struct.hidegroup** @add_to_hidegroups.tmp, align 8, !dbg !164
  %data = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %7, i32 0, i32 0, !dbg !165
  store i32 %6, i32* %data, align 8, !dbg !166
  br label %if.end5, !dbg !167

if.end5:                                          ; preds = %if.then3, %if.end
  ret void, !dbg !168
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define void @hidegroups_init() #0 !dbg !53 {
entry:
  %foo = alloca i8*, align 8
  %foo_save = alloca i8*, align 8
  %bar = alloca i8*, align 8
  %tmpgrp = alloca %struct.group*, align 8
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !169, metadata !142), !dbg !170
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0)), !dbg !171
  %call1 = call noalias i8* @strdup(i8* %call) #7, !dbg !172
  store i8* %call1, i8** %foo, align 8, !dbg !170
  call void @llvm.dbg.declare(metadata i8** %foo_save, metadata !174, metadata !142), !dbg !175
  %0 = load i8*, i8** %foo, align 8, !dbg !176
  store i8* %0, i8** %foo_save, align 8, !dbg !175
  call void @llvm.dbg.declare(metadata i8** %bar, metadata !177, metadata !142), !dbg !178
  call void @llvm.dbg.declare(metadata %struct.group** %tmpgrp, metadata !179, metadata !142), !dbg !189
  br label %while.cond, !dbg !190

while.cond:                                       ; preds = %if.end15, %entry
  %1 = load i8*, i8** %foo, align 8, !dbg !191
  %call2 = call i8* @strtok(i8* %1, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0)) #7, !dbg !192
  store i8* %call2, i8** %bar, align 8, !dbg !193
  %tobool = icmp ne i8* %call2, null, !dbg !194
  br i1 %tobool, label %while.body, label %while.end, !dbg !194

while.body:                                       ; preds = %while.cond
  store i8* null, i8** %foo, align 8, !dbg !195
  %2 = load i8*, i8** %bar, align 8, !dbg !197
  %call3 = call i32 @strcmp(i8* %2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)) #8, !dbg !199
  %tobool4 = icmp ne i32 %call3, 0, !dbg !199
  br i1 %tobool4, label %land.lhs.true, label %if.else, !dbg !200

land.lhs.true:                                    ; preds = %while.body
  %3 = load i8*, i8** %bar, align 8, !dbg !201
  %call5 = call i64 @strtoul(i8* %3, i8** null, i32 10) #7, !dbg !203
  %tobool6 = icmp ne i64 %call5, 0, !dbg !203
  br i1 %tobool6, label %if.else, label %if.then, !dbg !204

if.then:                                          ; preds = %land.lhs.true
  %4 = load i8*, i8** %bar, align 8, !dbg !205
  %call7 = call %struct.group* @getgrnam(i8* %4), !dbg !208
  store %struct.group* %call7, %struct.group** %tmpgrp, align 8, !dbg !209
  %tobool8 = icmp ne %struct.group* %call7, null, !dbg !209
  br i1 %tobool8, label %if.then9, label %if.end, !dbg !210

if.then9:                                         ; preds = %if.then
  %5 = load %struct.group*, %struct.group** %tmpgrp, align 8, !dbg !211
  %gr_gid = getelementptr inbounds %struct.group, %struct.group* %5, i32 0, i32 2, !dbg !212
  %6 = load i32, i32* %gr_gid, align 8, !dbg !212
  call void @add_to_hidegroups(i32 %6), !dbg !213
  br label %if.end, !dbg !213

if.end:                                           ; preds = %if.then9, %if.then
  br label %if.end15, !dbg !214

if.else:                                          ; preds = %land.lhs.true, %while.body
  %7 = load i8*, i8** %bar, align 8, !dbg !215
  %call10 = call i64 @strtoul(i8* %7, i8** null, i32 10) #7, !dbg !217
  %tobool11 = icmp ne i64 %call10, 0, !dbg !217
  br i1 %tobool11, label %if.then12, label %if.end14, !dbg !218

if.then12:                                        ; preds = %if.else
  %8 = load i8*, i8** %bar, align 8, !dbg !219
  %call13 = call i64 @strtoul(i8* %8, i8** null, i32 10) #7, !dbg !220
  %conv = trunc i64 %call13 to i32, !dbg !220
  call void @add_to_hidegroups(i32 %conv), !dbg !221
  br label %if.end14, !dbg !223

if.end14:                                         ; preds = %if.then12, %if.else
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.end
  br label %while.cond, !dbg !224

while.end:                                        ; preds = %while.cond
  %9 = load i8*, i8** %foo_save, align 8, !dbg !226
  call void @free(i8* %9) #7, !dbg !227
  ret void, !dbg !228
}

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

declare i8* @config_getoption(i8*) #3

; Function Attrs: nounwind
declare i8* @strtok(i8*, i8*) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #2

declare %struct.group* @getgrnam(i8*) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define void @hidegroups_end() #0 !dbg !56 {
entry:
  %tmp = alloca %struct.hidegroup*, align 8
  call void @llvm.dbg.declare(metadata %struct.hidegroup** %tmp, metadata !229, metadata !142), !dbg !230
  %0 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !231
  store %struct.hidegroup* %0, %struct.hidegroup** %tmp, align 8, !dbg !230
  %1 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !232
  %tobool = icmp ne %struct.hidegroup* %1, null, !dbg !232
  br i1 %tobool, label %if.then, label %if.end, !dbg !234

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !235

while.cond:                                       ; preds = %while.body, %if.then
  %2 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !236
  %next = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %2, i32 0, i32 1, !dbg !238
  %3 = load %struct.hidegroup*, %struct.hidegroup** %next, align 8, !dbg !238
  %tobool1 = icmp ne %struct.hidegroup* %3, null, !dbg !239
  br i1 %tobool1, label %while.body, label %while.end, !dbg !239

while.body:                                       ; preds = %while.cond
  %4 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !240
  %next2 = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %4, i32 0, i32 1, !dbg !242
  %5 = load %struct.hidegroup*, %struct.hidegroup** %next2, align 8, !dbg !242
  store %struct.hidegroup* %5, %struct.hidegroup** %tmp, align 8, !dbg !243
  %6 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !244
  %7 = bitcast %struct.hidegroup* %6 to i8*, !dbg !244
  call void @free(i8* %7) #7, !dbg !245
  %8 = load %struct.hidegroup*, %struct.hidegroup** %tmp, align 8, !dbg !246
  store %struct.hidegroup* %8, %struct.hidegroup** @hidegroups, align 8, !dbg !247
  br label %while.cond, !dbg !248

while.end:                                        ; preds = %while.cond
  br label %if.end, !dbg !250

if.end:                                           ; preds = %while.end, %entry
  ret void, !dbg !252
}

; Function Attrs: nounwind uwtable
define void @bftpd_stat(i8* %name, %struct._IO_FILE* %client) #0 !dbg !57 {
entry:
  %name.addr = alloca i8*, align 8
  %client.addr = alloca %struct._IO_FILE*, align 8
  %statbuf = alloca %struct.stat, align 8
  %temp = alloca [258 x i8], align 16
  %linktarget = alloca [260 x i8], align 16
  %perm = alloca [11 x i8], align 1
  %timestr = alloca [17 x i8], align 16
  %uid = alloca [31 x i8], align 16
  %gid = alloca [31 x i8], align 16
  %filetime = alloca %struct.tm, align 8
  %tea_time = alloca %struct.tm*, align 8
  %local_time = alloca %struct.tm*, align 8
  %t = alloca i64, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !253, metadata !142), !dbg !254
  store %struct._IO_FILE* %client, %struct._IO_FILE** %client.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %client.addr, metadata !255, metadata !142), !dbg !256
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !257, metadata !142), !dbg !258
  call void @llvm.dbg.declare(metadata [258 x i8]* %temp, metadata !259, metadata !142), !dbg !263
  call void @llvm.dbg.declare(metadata [260 x i8]* %linktarget, metadata !264, metadata !142), !dbg !268
  call void @llvm.dbg.declare(metadata [11 x i8]* %perm, metadata !269, metadata !142), !dbg !273
  call void @llvm.dbg.declare(metadata [17 x i8]* %timestr, metadata !274, metadata !142), !dbg !278
  call void @llvm.dbg.declare(metadata [31 x i8]* %uid, metadata !279, metadata !142), !dbg !283
  call void @llvm.dbg.declare(metadata [31 x i8]* %gid, metadata !284, metadata !142), !dbg !285
  call void @llvm.dbg.declare(metadata %struct.tm* %filetime, metadata !286, metadata !142), !dbg !302
  call void @llvm.dbg.declare(metadata %struct.tm** %tea_time, metadata !303, metadata !142), !dbg !305
  call void @llvm.dbg.declare(metadata %struct.tm** %local_time, metadata !306, metadata !142), !dbg !307
  call void @llvm.dbg.declare(metadata i64* %t, metadata !308, metadata !142), !dbg !310
  %0 = load i8*, i8** %name.addr, align 8, !dbg !311
  %call = call i32 @lstat64(i8* %0, %struct.stat* %statbuf) #7, !dbg !313
  %cmp = icmp eq i32 %call, -1, !dbg !314
  br i1 %cmp, label %if.then, label %if.end, !dbg !315

if.then:                                          ; preds = %entry
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %client.addr, align 8, !dbg !316
  %call1 = call i32* @__errno_location() #1, !dbg !318
  %2 = load i32, i32* %call1, align 4, !dbg !318
  %call2 = call i8* @strerror(i32 %2) #7, !dbg !319
  %call3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i32 0, i32 0), i8* %call2), !dbg !321
  br label %return, !dbg !323

if.end:                                           ; preds = %entry
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !324
  %3 = load i32, i32* %st_mode, align 8, !dbg !324
  %and = and i32 %3, 61440, !dbg !324
  %cmp4 = icmp eq i32 %and, 40960, !dbg !324
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !326

if.then5:                                         ; preds = %if.end
  %arraydecay = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i32 0, i32 0, !dbg !327
  %call6 = call i8* @strcpy(i8* %arraydecay, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.4, i32 0, i32 0)) #7, !dbg !329
  %4 = load i8*, i8** %name.addr, align 8, !dbg !330
  %arraydecay7 = getelementptr inbounds [258 x i8], [258 x i8]* %temp, i32 0, i32 0, !dbg !331
  %call8 = call i64 @readlink(i8* %4, i8* %arraydecay7, i64 257) #7, !dbg !332
  %arrayidx = getelementptr inbounds [258 x i8], [258 x i8]* %temp, i64 0, i64 %call8, !dbg !333
  store i8 0, i8* %arrayidx, align 1, !dbg !334
  %arraydecay9 = getelementptr inbounds [260 x i8], [260 x i8]* %linktarget, i32 0, i32 0, !dbg !335
  %arraydecay10 = getelementptr inbounds [258 x i8], [258 x i8]* %temp, i32 0, i32 0, !dbg !336
  %call11 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay9, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0), i8* %arraydecay10) #7, !dbg !337
  br label %if.end74, !dbg !338

if.else:                                          ; preds = %if.end
  %arraydecay12 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i32 0, i32 0, !dbg !339
  %call13 = call i8* @strcpy(i8* %arraydecay12, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.6, i32 0, i32 0)) #7, !dbg !341
  %st_mode14 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !342
  %5 = load i32, i32* %st_mode14, align 8, !dbg !342
  %and15 = and i32 %5, 61440, !dbg !342
  %cmp16 = icmp eq i32 %and15, 16384, !dbg !342
  br i1 %cmp16, label %if.then17, label %if.end19, !dbg !344

if.then17:                                        ; preds = %if.else
  %arrayidx18 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 0, !dbg !345
  store i8 100, i8* %arrayidx18, align 1, !dbg !346
  br label %if.end19, !dbg !345

if.end19:                                         ; preds = %if.then17, %if.else
  %st_mode20 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !347
  %6 = load i32, i32* %st_mode20, align 8, !dbg !347
  %and21 = and i32 %6, 256, !dbg !349
  %tobool = icmp ne i32 %and21, 0, !dbg !349
  br i1 %tobool, label %if.then22, label %if.end24, !dbg !350

if.then22:                                        ; preds = %if.end19
  %arrayidx23 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 1, !dbg !351
  store i8 114, i8* %arrayidx23, align 1, !dbg !352
  br label %if.end24, !dbg !351

if.end24:                                         ; preds = %if.then22, %if.end19
  %st_mode25 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !353
  %7 = load i32, i32* %st_mode25, align 8, !dbg !353
  %and26 = and i32 %7, 128, !dbg !355
  %tobool27 = icmp ne i32 %and26, 0, !dbg !355
  br i1 %tobool27, label %if.then28, label %if.end30, !dbg !356

if.then28:                                        ; preds = %if.end24
  %arrayidx29 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 2, !dbg !357
  store i8 119, i8* %arrayidx29, align 1, !dbg !358
  br label %if.end30, !dbg !357

if.end30:                                         ; preds = %if.then28, %if.end24
  %st_mode31 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !359
  %8 = load i32, i32* %st_mode31, align 8, !dbg !359
  %and32 = and i32 %8, 64, !dbg !361
  %tobool33 = icmp ne i32 %and32, 0, !dbg !361
  br i1 %tobool33, label %if.then34, label %if.end36, !dbg !362

if.then34:                                        ; preds = %if.end30
  %arrayidx35 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 3, !dbg !363
  store i8 120, i8* %arrayidx35, align 1, !dbg !364
  br label %if.end36, !dbg !363

if.end36:                                         ; preds = %if.then34, %if.end30
  %st_mode37 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !365
  %9 = load i32, i32* %st_mode37, align 8, !dbg !365
  %and38 = and i32 %9, 32, !dbg !367
  %tobool39 = icmp ne i32 %and38, 0, !dbg !367
  br i1 %tobool39, label %if.then40, label %if.end42, !dbg !368

if.then40:                                        ; preds = %if.end36
  %arrayidx41 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 4, !dbg !369
  store i8 114, i8* %arrayidx41, align 1, !dbg !370
  br label %if.end42, !dbg !369

if.end42:                                         ; preds = %if.then40, %if.end36
  %st_mode43 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !371
  %10 = load i32, i32* %st_mode43, align 8, !dbg !371
  %and44 = and i32 %10, 16, !dbg !373
  %tobool45 = icmp ne i32 %and44, 0, !dbg !373
  br i1 %tobool45, label %if.then46, label %if.end48, !dbg !374

if.then46:                                        ; preds = %if.end42
  %arrayidx47 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 5, !dbg !375
  store i8 119, i8* %arrayidx47, align 1, !dbg !376
  br label %if.end48, !dbg !375

if.end48:                                         ; preds = %if.then46, %if.end42
  %st_mode49 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !377
  %11 = load i32, i32* %st_mode49, align 8, !dbg !377
  %and50 = and i32 %11, 8, !dbg !379
  %tobool51 = icmp ne i32 %and50, 0, !dbg !379
  br i1 %tobool51, label %if.then52, label %if.end54, !dbg !380

if.then52:                                        ; preds = %if.end48
  %arrayidx53 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 6, !dbg !381
  store i8 120, i8* %arrayidx53, align 1, !dbg !382
  br label %if.end54, !dbg !381

if.end54:                                         ; preds = %if.then52, %if.end48
  %st_mode55 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !383
  %12 = load i32, i32* %st_mode55, align 8, !dbg !383
  %and56 = and i32 %12, 4, !dbg !385
  %tobool57 = icmp ne i32 %and56, 0, !dbg !385
  br i1 %tobool57, label %if.then58, label %if.end60, !dbg !386

if.then58:                                        ; preds = %if.end54
  %arrayidx59 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 7, !dbg !387
  store i8 114, i8* %arrayidx59, align 1, !dbg !388
  br label %if.end60, !dbg !387

if.end60:                                         ; preds = %if.then58, %if.end54
  %st_mode61 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !389
  %13 = load i32, i32* %st_mode61, align 8, !dbg !389
  %and62 = and i32 %13, 2, !dbg !391
  %tobool63 = icmp ne i32 %and62, 0, !dbg !391
  br i1 %tobool63, label %if.then64, label %if.end66, !dbg !392

if.then64:                                        ; preds = %if.end60
  %arrayidx65 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 8, !dbg !393
  store i8 119, i8* %arrayidx65, align 1, !dbg !394
  br label %if.end66, !dbg !393

if.end66:                                         ; preds = %if.then64, %if.end60
  %st_mode67 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 3, !dbg !395
  %14 = load i32, i32* %st_mode67, align 8, !dbg !395
  %and68 = and i32 %14, 1, !dbg !397
  %tobool69 = icmp ne i32 %and68, 0, !dbg !397
  br i1 %tobool69, label %if.then70, label %if.end72, !dbg !398

if.then70:                                        ; preds = %if.end66
  %arrayidx71 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i64 0, i64 9, !dbg !399
  store i8 120, i8* %arrayidx71, align 1, !dbg !400
  br label %if.end72, !dbg !399

if.end72:                                         ; preds = %if.then70, %if.end66
  %arrayidx73 = getelementptr inbounds [260 x i8], [260 x i8]* %linktarget, i64 0, i64 0, !dbg !401
  store i8 0, i8* %arrayidx73, align 16, !dbg !402
  br label %if.end74

if.end74:                                         ; preds = %if.end72, %if.then5
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 12, !dbg !403
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !403
  %call75 = call %struct.tm* @localtime(i64* %tv_sec) #7, !dbg !404
  store %struct.tm* %call75, %struct.tm** %local_time, align 8, !dbg !405
  %15 = load %struct.tm*, %struct.tm** %local_time, align 8, !dbg !406
  %tobool76 = icmp ne %struct.tm* %15, null, !dbg !406
  br i1 %tobool76, label %if.end78, label %if.then77, !dbg !408

if.then77:                                        ; preds = %if.end74
  br label %return, !dbg !409

if.end78:                                         ; preds = %if.end74
  %16 = bitcast %struct.tm* %filetime to i8*, !dbg !411
  %17 = load %struct.tm*, %struct.tm** %local_time, align 8, !dbg !412
  %18 = bitcast %struct.tm* %17 to i8*, !dbg !411
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %18, i64 56, i32 8, i1 false), !dbg !411
  %call79 = call i64 @time(i64* %t) #7, !dbg !413
  %call80 = call %struct.tm* @localtime(i64* %t) #7, !dbg !414
  store %struct.tm* %call80, %struct.tm** %tea_time, align 8, !dbg !415
  %19 = load %struct.tm*, %struct.tm** %tea_time, align 8, !dbg !416
  %tobool81 = icmp ne %struct.tm* %19, null, !dbg !416
  br i1 %tobool81, label %if.end83, label %if.then82, !dbg !418

if.then82:                                        ; preds = %if.end78
  br label %return, !dbg !419

if.end83:                                         ; preds = %if.end78
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %filetime, i32 0, i32 5, !dbg !421
  %20 = load i32, i32* %tm_year, align 4, !dbg !421
  %21 = load %struct.tm*, %struct.tm** %tea_time, align 8, !dbg !423
  %tm_year84 = getelementptr inbounds %struct.tm, %struct.tm* %21, i32 0, i32 5, !dbg !424
  %22 = load i32, i32* %tm_year84, align 4, !dbg !424
  %cmp85 = icmp eq i32 %20, %22, !dbg !425
  br i1 %cmp85, label %if.then86, label %if.else91, !dbg !426

if.then86:                                        ; preds = %if.end83
  %arraydecay87 = getelementptr inbounds [17 x i8], [17 x i8]* %timestr, i32 0, i32 0, !dbg !427
  %st_mtim88 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 12, !dbg !428
  %tv_sec89 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim88, i32 0, i32 0, !dbg !428
  %call90 = call i8* @ctime(i64* %tv_sec89) #7, !dbg !429
  %add.ptr = getelementptr inbounds i8, i8* %call90, i64 4, !dbg !430
  call void @mystrncpy(i8* %arraydecay87, i8* %add.ptr, i32 12), !dbg !431
  br label %if.end94, !dbg !433

if.else91:                                        ; preds = %if.end83
  %arraydecay92 = getelementptr inbounds [17 x i8], [17 x i8]* %timestr, i32 0, i32 0, !dbg !434
  %call93 = call i64 @strftime(i8* %arraydecay92, i64 17, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0), %struct.tm* %filetime) #7, !dbg !435
  br label %if.end94

if.end94:                                         ; preds = %if.else91, %if.then86
  %st_uid = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 4, !dbg !436
  %23 = load i32, i32* %st_uid, align 4, !dbg !436
  %24 = load %struct._IO_FILE*, %struct._IO_FILE** @passwdfile, align 8, !dbg !437
  %arraydecay95 = getelementptr inbounds [31 x i8], [31 x i8]* %uid, i32 0, i32 0, !dbg !438
  %call96 = call i8* @mygetpwuid(i32 %23, %struct._IO_FILE* %24, i8* %arraydecay95), !dbg !439
  %arrayidx97 = getelementptr inbounds i8, i8* %call96, i64 8, !dbg !439
  store i8 0, i8* %arrayidx97, align 1, !dbg !440
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 5, !dbg !441
  %25 = load i32, i32* %st_gid, align 8, !dbg !441
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** @groupfile, align 8, !dbg !442
  %arraydecay98 = getelementptr inbounds [31 x i8], [31 x i8]* %gid, i32 0, i32 0, !dbg !443
  %call99 = call i8* @mygetpwuid(i32 %25, %struct._IO_FILE* %26, i8* %arraydecay98), !dbg !444
  %arrayidx100 = getelementptr inbounds i8, i8* %call99, i64 8, !dbg !444
  store i8 0, i8* %arrayidx100, align 1, !dbg !445
  %27 = load %struct._IO_FILE*, %struct._IO_FILE** %client.addr, align 8, !dbg !446
  %arraydecay101 = getelementptr inbounds [11 x i8], [11 x i8]* %perm, i32 0, i32 0, !dbg !447
  %st_nlink = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 2, !dbg !448
  %28 = load i64, i64* %st_nlink, align 8, !dbg !448
  %conv = trunc i64 %28 to i32, !dbg !449
  %arraydecay102 = getelementptr inbounds [31 x i8], [31 x i8]* %uid, i32 0, i32 0, !dbg !450
  %arraydecay103 = getelementptr inbounds [31 x i8], [31 x i8]* %gid, i32 0, i32 0, !dbg !451
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !452
  %29 = load i64, i64* %st_size, align 8, !dbg !452
  %arraydecay104 = getelementptr inbounds [17 x i8], [17 x i8]* %timestr, i32 0, i32 0, !dbg !453
  %30 = load i8*, i8** %name.addr, align 8, !dbg !454
  %arraydecay105 = getelementptr inbounds [260 x i8], [260 x i8]* %linktarget, i32 0, i32 0, !dbg !455
  %call106 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %27, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.8, i32 0, i32 0), i8* %arraydecay101, i32 %conv, i8* %arraydecay102, i8* %arraydecay103, i64 %29, i8* %arraydecay104, i8* %30, i8* %arraydecay105), !dbg !456
  br label %return, !dbg !457

return:                                           ; preds = %if.end94, %if.then82, %if.then77, %if.then
  ret void, !dbg !458
}

; Function Attrs: nounwind
declare i32 @lstat64(i8*, %struct.stat*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

; Function Attrs: nounwind
declare i8* @strerror(i32) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

; Function Attrs: nounwind
declare i64 @readlink(i8*, i8*, i64) #2

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #2

; Function Attrs: nounwind
declare %struct.tm* @localtime(i64*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind
declare i64 @time(i64*) #2

declare void @mystrncpy(i8*, i8*, i32) #3

; Function Attrs: nounwind
declare i8* @ctime(i64*) #2

; Function Attrs: nounwind
declare i64 @strftime(i8*, i64, i8*, %struct.tm*) #2

declare i8* @mygetpwuid(i32, %struct._IO_FILE*, i8*) #3

; Function Attrs: nounwind uwtable
define void @dirlist_one_file(i8* %name, %struct._IO_FILE* %client, i8 signext %verbose) #0 !dbg !118 {
entry:
  %name.addr = alloca i8*, align 8
  %client.addr = alloca %struct._IO_FILE*, align 8
  %verbose.addr = alloca i8, align 1
  %statbuf = alloca %struct.stat, align 8
  %tmp = alloca %struct.hidegroup*, align 8
  %filename_index = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !460, metadata !142), !dbg !461
  store %struct._IO_FILE* %client, %struct._IO_FILE** %client.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %client.addr, metadata !462, metadata !142), !dbg !463
  store i8 %verbose, i8* %verbose.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %verbose.addr, metadata !464, metadata !142), !dbg !465
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !466, metadata !142), !dbg !467
  call void @llvm.dbg.declare(metadata %struct.hidegroup** %tmp, metadata !468, metadata !142), !dbg !469
  %0 = load %struct.hidegroup*, %struct.hidegroup** @hidegroups, align 8, !dbg !470
  store %struct.hidegroup* %0, %struct.hidegroup** %tmp, align 8, !dbg !469
  call void @llvm.dbg.declare(metadata i8** %filename_index, metadata !471, metadata !142), !dbg !472
  %1 = load i8*, i8** %name.addr, align 8, !dbg !473
  %call = call i32 @stat64(i8* %1, %struct.stat* %statbuf) #7, !dbg !475
  %tobool = icmp ne i32 %call, 0, !dbg !475
  br i1 %tobool, label %if.end7, label %if.then, !dbg !476

if.then:                                          ; preds = %entry
  %2 = load %struct.hidegroup*, %struct.hidegroup** %tmp, align 8, !dbg !477
  %tobool2 = icmp ne %struct.hidegroup* %2, null, !dbg !477
  br i1 %tobool2, label %if.then3, label %if.end6, !dbg !480

if.then3:                                         ; preds = %if.then
  br label %do.body, !dbg !481

do.body:                                          ; preds = %do.cond, %if.then3
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 5, !dbg !482
  %3 = load i32, i32* %st_gid, align 8, !dbg !482
  %4 = load %struct.hidegroup*, %struct.hidegroup** %tmp, align 8, !dbg !485
  %data = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %4, i32 0, i32 0, !dbg !486
  %5 = load i32, i32* %data, align 8, !dbg !486
  %cmp = icmp eq i32 %3, %5, !dbg !487
  br i1 %cmp, label %if.then4, label %if.end, !dbg !488

if.then4:                                         ; preds = %do.body
  br label %if.end16, !dbg !489

if.end:                                           ; preds = %do.body
  br label %do.cond, !dbg !490

do.cond:                                          ; preds = %if.end
  %6 = load %struct.hidegroup*, %struct.hidegroup** %tmp, align 8, !dbg !491
  %next = getelementptr inbounds %struct.hidegroup, %struct.hidegroup* %6, i32 0, i32 1, !dbg !493
  %7 = load %struct.hidegroup*, %struct.hidegroup** %next, align 8, !dbg !493
  store %struct.hidegroup* %7, %struct.hidegroup** %tmp, align 8, !dbg !494
  %tobool5 = icmp ne %struct.hidegroup* %7, null, !dbg !495
  br i1 %tobool5, label %do.body, label %do.end, !dbg !495

do.end:                                           ; preds = %do.cond
  br label %if.end6, !dbg !496

if.end6:                                          ; preds = %do.end, %if.then
  br label %if.end7, !dbg !498

if.end7:                                          ; preds = %if.end6, %entry
  %8 = load i8*, i8** %name.addr, align 8, !dbg !499
  %call8 = call i8* @strrchr(i8* %8, i32 47) #8, !dbg !500
  store i8* %call8, i8** %filename_index, align 8, !dbg !501
  %9 = load i8*, i8** %filename_index, align 8, !dbg !502
  %tobool9 = icmp ne i8* %9, null, !dbg !502
  br i1 %tobool9, label %if.then10, label %if.else, !dbg !504

if.then10:                                        ; preds = %if.end7
  %10 = load i8*, i8** %filename_index, align 8, !dbg !505
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 1, !dbg !505
  store i8* %incdec.ptr, i8** %filename_index, align 8, !dbg !505
  br label %if.end11, !dbg !506

if.else:                                          ; preds = %if.end7
  %11 = load i8*, i8** %name.addr, align 8, !dbg !507
  store i8* %11, i8** %filename_index, align 8, !dbg !508
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then10
  %12 = load i8, i8* %verbose.addr, align 1, !dbg !509
  %tobool12 = icmp ne i8 %12, 0, !dbg !509
  br i1 %tobool12, label %if.then13, label %if.else14, !dbg !511

if.then13:                                        ; preds = %if.end11
  %13 = load i8*, i8** %name.addr, align 8, !dbg !512
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %client.addr, align 8, !dbg !513
  call void @bftpd_stat(i8* %13, %struct._IO_FILE* %14), !dbg !514
  br label %if.end16, !dbg !514

if.else14:                                        ; preds = %if.end11
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %client.addr, align 8, !dbg !515
  %16 = load i8*, i8** %filename_index, align 8, !dbg !516
  %call15 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %15, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0), i8* %16), !dbg !517
  br label %if.end16

if.end16:                                         ; preds = %if.then4, %if.else14, %if.then13
  ret void, !dbg !518
}

; Function Attrs: nounwind
declare i32 @stat64(i8*, %struct.stat*) #2

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #4

; Function Attrs: nounwind uwtable
define void @dirlist(i8* %name, %struct._IO_FILE* %client, i8 signext %verbose, i32 %show_hidden) #0 !dbg !121 {
entry:
  %name.addr = alloca i8*, align 8
  %client.addr = alloca %struct._IO_FILE*, align 8
  %verbose.addr = alloca i8, align 1
  %show_hidden.addr = alloca i32, align 4
  %directory = alloca %struct.__dirstream*, align 8
  %can_see_file = alloca %struct._IO_FILE*, align 8
  %show_nonreadable_files = alloca i32, align 4
  %show_hidden_files = alloca i32, align 4
  %skip_file = alloca i32, align 4
  %file_is_hidden = alloca i32, align 4
  %local_cwd = alloca i8*, align 8
  %pattern = alloca i8*, align 8
  %short_pattern = alloca i8*, align 8
  %dir_entry = alloca %struct.dirent*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !519, metadata !142), !dbg !520
  store %struct._IO_FILE* %client, %struct._IO_FILE** %client.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %client.addr, metadata !521, metadata !142), !dbg !522
  store i8 %verbose, i8* %verbose.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %verbose.addr, metadata !523, metadata !142), !dbg !524
  store i32 %show_hidden, i32* %show_hidden.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %show_hidden.addr, metadata !525, metadata !142), !dbg !526
  call void @llvm.dbg.declare(metadata %struct.__dirstream** %directory, metadata !527, metadata !142), !dbg !532
  store %struct.__dirstream* null, %struct.__dirstream** %directory, align 8, !dbg !532
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %can_see_file, metadata !533, metadata !142), !dbg !534
  call void @llvm.dbg.declare(metadata i32* %show_nonreadable_files, metadata !535, metadata !142), !dbg !536
  store i32 0, i32* %show_nonreadable_files, align 4, !dbg !536
  call void @llvm.dbg.declare(metadata i32* %show_hidden_files, metadata !537, metadata !142), !dbg !538
  store i32 0, i32* %show_hidden_files, align 4, !dbg !538
  call void @llvm.dbg.declare(metadata i32* %skip_file, metadata !539, metadata !142), !dbg !540
  call void @llvm.dbg.declare(metadata i32* %file_is_hidden, metadata !541, metadata !142), !dbg !542
  call void @llvm.dbg.declare(metadata i8** %local_cwd, metadata !543, metadata !142), !dbg !544
  store i8* null, i8** %local_cwd, align 8, !dbg !544
  call void @llvm.dbg.declare(metadata i8** %pattern, metadata !545, metadata !142), !dbg !546
  store i8* null, i8** %pattern, align 8, !dbg !546
  call void @llvm.dbg.declare(metadata i8** %short_pattern, metadata !547, metadata !142), !dbg !548
  call void @llvm.dbg.declare(metadata %struct.dirent** %dir_entry, metadata !549, metadata !142), !dbg !564
  %0 = load i32, i32* %show_hidden.addr, align 4, !dbg !565
  %tobool = icmp ne i32 %0, 0, !dbg !567
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !568

land.lhs.true:                                    ; preds = %entry
  %call = call i8* @config_getoption(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.10, i32 0, i32 0)), !dbg !569
  %call1 = call i32 @strcasecmp(i8* %call, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !570
  %tobool2 = icmp ne i32 %call1, 0, !dbg !572
  br i1 %tobool2, label %if.end, label %if.then, !dbg !573

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* %show_hidden_files, align 4, !dbg !575
  br label %if.end, !dbg !576

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %call3 = call i8* @config_getoption(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.10, i32 0, i32 0)), !dbg !577
  %call4 = call i32 @strcasecmp(i8* %call3, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.12, i32 0, i32 0)) #8, !dbg !579
  %tobool5 = icmp ne i32 %call4, 0, !dbg !581
  br i1 %tobool5, label %if.end7, label %if.then6, !dbg !582

if.then6:                                         ; preds = %if.end
  store i32 1, i32* %show_hidden_files, align 4, !dbg !583
  br label %if.end7, !dbg !584

if.end7:                                          ; preds = %if.then6, %if.end
  %call8 = call i8* @config_getoption(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.13, i32 0, i32 0)), !dbg !585
  %call9 = call i32 @strcasecmp(i8* %call8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !587
  %tobool10 = icmp ne i32 %call9, 0, !dbg !589
  br i1 %tobool10, label %if.end12, label %if.then11, !dbg !590

if.then11:                                        ; preds = %if.end7
  store i32 1, i32* %show_nonreadable_files, align 4, !dbg !591
  br label %if.end12, !dbg !592

if.end12:                                         ; preds = %if.then11, %if.end7
  %1 = load i8*, i8** %name.addr, align 8, !dbg !593
  %call13 = call i8* @strstr(i8* %1, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.14, i32 0, i32 0)) #8, !dbg !595
  %tobool14 = icmp ne i8* %call13, null, !dbg !595
  br i1 %tobool14, label %land.lhs.true15, label %if.end19, !dbg !596

land.lhs.true15:                                  ; preds = %if.end12
  %2 = load i8*, i8** %name.addr, align 8, !dbg !597
  %call16 = call i8* @strchr(i8* %2, i32 42) #8, !dbg !599
  %tobool17 = icmp ne i8* %call16, null, !dbg !599
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !600

if.then18:                                        ; preds = %land.lhs.true15
  br label %if.end71, !dbg !601

if.end19:                                         ; preds = %land.lhs.true15, %if.end12
  %3 = load i8*, i8** %name.addr, align 8, !dbg !602
  %call20 = call %struct.__dirstream* @opendir(i8* %3), !dbg !604
  store %struct.__dirstream* %call20, %struct.__dirstream** %directory, align 8, !dbg !605
  %tobool21 = icmp ne %struct.__dirstream* %call20, null, !dbg !605
  br i1 %tobool21, label %if.then22, label %if.else, !dbg !606

if.then22:                                        ; preds = %if.end19
  %4 = load %struct.__dirstream*, %struct.__dirstream** %directory, align 8, !dbg !607
  %call23 = call i32 @closedir(%struct.__dirstream* %4), !dbg !609
  %call24 = call i8* (...) @bftpd_cwd_getcwd(), !dbg !610
  store i8* %call24, i8** %local_cwd, align 8, !dbg !611
  %5 = load i8*, i8** %name.addr, align 8, !dbg !612
  %call25 = call i32 @chdir(i8* %5) #7, !dbg !613
  br label %if.end26, !dbg !614

if.else:                                          ; preds = %if.end19
  %6 = load i8*, i8** %name.addr, align 8, !dbg !615
  store i8* %6, i8** %pattern, align 8, !dbg !616
  br label %if.end26

if.end26:                                         ; preds = %if.else, %if.then22
  %call27 = call %struct.__dirstream* @opendir(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.15, i32 0, i32 0)), !dbg !617
  store %struct.__dirstream* %call27, %struct.__dirstream** %directory, align 8, !dbg !618
  %7 = load %struct.__dirstream*, %struct.__dirstream** %directory, align 8, !dbg !619
  %tobool28 = icmp ne %struct.__dirstream* %7, null, !dbg !619
  br i1 %tobool28, label %if.then29, label %if.end67, !dbg !621

if.then29:                                        ; preds = %if.end26
  %8 = load %struct.__dirstream*, %struct.__dirstream** %directory, align 8, !dbg !622
  %call30 = call %struct.dirent* @readdir64(%struct.__dirstream* %8), !dbg !624
  store %struct.dirent* %call30, %struct.dirent** %dir_entry, align 8, !dbg !625
  br label %while.cond, !dbg !626

while.cond:                                       ; preds = %if.end64, %if.then29
  %9 = load %struct.dirent*, %struct.dirent** %dir_entry, align 8, !dbg !627
  %tobool31 = icmp ne %struct.dirent* %9, null, !dbg !629
  br i1 %tobool31, label %while.body, label %while.end, !dbg !629

while.body:                                       ; preds = %while.cond
  %10 = load %struct.dirent*, %struct.dirent** %dir_entry, align 8, !dbg !630
  %d_name = getelementptr inbounds %struct.dirent, %struct.dirent* %10, i32 0, i32 4, !dbg !632
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %d_name, i32 0, i32 0, !dbg !630
  %call32 = call %struct._IO_FILE* @fopen64(i8* %arraydecay, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.16, i32 0, i32 0)), !dbg !633
  store %struct._IO_FILE* %call32, %struct._IO_FILE** %can_see_file, align 8, !dbg !634
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %can_see_file, align 8, !dbg !635
  %tobool33 = icmp ne %struct._IO_FILE* %11, null, !dbg !635
  br i1 %tobool33, label %if.then34, label %if.end36, !dbg !637

if.then34:                                        ; preds = %while.body
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** %can_see_file, align 8, !dbg !638
  %call35 = call i32 @fclose(%struct._IO_FILE* %12), !dbg !639
  br label %if.end36, !dbg !639

if.end36:                                         ; preds = %if.then34, %while.body
  %13 = load %struct.dirent*, %struct.dirent** %dir_entry, align 8, !dbg !640
  %d_name37 = getelementptr inbounds %struct.dirent, %struct.dirent* %13, i32 0, i32 4, !dbg !641
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %d_name37, i64 0, i64 0, !dbg !640
  %14 = load i8, i8* %arrayidx, align 1, !dbg !640
  %conv = sext i8 %14 to i32, !dbg !640
  %cmp = icmp eq i32 %conv, 46, !dbg !642
  %cond = select i1 %cmp, i32 1, i32 0, !dbg !643
  store i32 %cond, i32* %file_is_hidden, align 4, !dbg !644
  store i32 1, i32* %skip_file, align 4, !dbg !645
  %15 = load i32, i32* %file_is_hidden, align 4, !dbg !646
  %tobool39 = icmp ne i32 %15, 0, !dbg !646
  br i1 %tobool39, label %lor.lhs.false, label %if.then41, !dbg !648

lor.lhs.false:                                    ; preds = %if.end36
  %16 = load i32, i32* %show_hidden_files, align 4, !dbg !649
  %tobool40 = icmp ne i32 %16, 0, !dbg !651
  br i1 %tobool40, label %if.then41, label %if.end59, !dbg !652

if.then41:                                        ; preds = %lor.lhs.false, %if.end36
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** %can_see_file, align 8, !dbg !653
  %tobool42 = icmp ne %struct._IO_FILE* %17, null, !dbg !656
  br i1 %tobool42, label %if.then45, label %lor.lhs.false43, !dbg !657

lor.lhs.false43:                                  ; preds = %if.then41
  %18 = load i32, i32* %show_nonreadable_files, align 4, !dbg !658
  %tobool44 = icmp ne i32 %18, 0, !dbg !660
  br i1 %tobool44, label %if.then45, label %if.end58, !dbg !661

if.then45:                                        ; preds = %lor.lhs.false43, %if.then41
  %19 = load i8*, i8** %pattern, align 8, !dbg !662
  %tobool46 = icmp ne i8* %19, null, !dbg !662
  br i1 %tobool46, label %if.then47, label %if.else56, !dbg !665

if.then47:                                        ; preds = %if.then45
  %20 = load i8*, i8** %pattern, align 8, !dbg !666
  %call48 = call i8* @strrchr(i8* %20, i32 47) #8, !dbg !668
  store i8* %call48, i8** %short_pattern, align 8, !dbg !669
  %21 = load i8*, i8** %short_pattern, align 8, !dbg !670
  %tobool49 = icmp ne i8* %21, null, !dbg !670
  br i1 %tobool49, label %if.then50, label %if.else51, !dbg !672

if.then50:                                        ; preds = %if.then47
  %22 = load i8*, i8** %short_pattern, align 8, !dbg !673
  %incdec.ptr = getelementptr inbounds i8, i8* %22, i32 1, !dbg !673
  store i8* %incdec.ptr, i8** %short_pattern, align 8, !dbg !673
  br label %if.end52, !dbg !674

if.else51:                                        ; preds = %if.then47
  %23 = load i8*, i8** %pattern, align 8, !dbg !675
  store i8* %23, i8** %short_pattern, align 8, !dbg !676
  br label %if.end52

if.end52:                                         ; preds = %if.else51, %if.then50
  %24 = load i8*, i8** %short_pattern, align 8, !dbg !677
  %25 = load %struct.dirent*, %struct.dirent** %dir_entry, align 8, !dbg !678
  %d_name53 = getelementptr inbounds %struct.dirent, %struct.dirent* %25, i32 0, i32 4, !dbg !679
  %arraydecay54 = getelementptr inbounds [256 x i8], [256 x i8]* %d_name53, i32 0, i32 0, !dbg !678
  %call55 = call i32 @fnmatch(i8* %24, i8* %arraydecay54, i32 2), !dbg !680
  store i32 %call55, i32* %skip_file, align 4, !dbg !681
  br label %if.end57, !dbg !682

if.else56:                                        ; preds = %if.then45
  store i32 0, i32* %skip_file, align 4, !dbg !683
  br label %if.end57

if.end57:                                         ; preds = %if.else56, %if.end52
  br label %if.end58, !dbg !684

if.end58:                                         ; preds = %if.end57, %lor.lhs.false43
  br label %if.end59, !dbg !685

if.end59:                                         ; preds = %if.end58, %lor.lhs.false
  %26 = load i32, i32* %skip_file, align 4, !dbg !686
  %tobool60 = icmp ne i32 %26, 0, !dbg !686
  br i1 %tobool60, label %if.end64, label %if.then61, !dbg !688

if.then61:                                        ; preds = %if.end59
  %27 = load %struct.dirent*, %struct.dirent** %dir_entry, align 8, !dbg !689
  %d_name62 = getelementptr inbounds %struct.dirent, %struct.dirent* %27, i32 0, i32 4, !dbg !690
  %arraydecay63 = getelementptr inbounds [256 x i8], [256 x i8]* %d_name62, i32 0, i32 0, !dbg !689
  %28 = load %struct._IO_FILE*, %struct._IO_FILE** %client.addr, align 8, !dbg !691
  %29 = load i8, i8* %verbose.addr, align 1, !dbg !692
  call void @dirlist_one_file(i8* %arraydecay63, %struct._IO_FILE* %28, i8 signext %29), !dbg !693
  br label %if.end64, !dbg !693

if.end64:                                         ; preds = %if.then61, %if.end59
  %30 = load %struct.__dirstream*, %struct.__dirstream** %directory, align 8, !dbg !694
  %call65 = call %struct.dirent* @readdir64(%struct.__dirstream* %30), !dbg !695
  store %struct.dirent* %call65, %struct.dirent** %dir_entry, align 8, !dbg !696
  br label %while.cond, !dbg !697

while.end:                                        ; preds = %while.cond
  %31 = load %struct.__dirstream*, %struct.__dirstream** %directory, align 8, !dbg !699
  %call66 = call i32 @closedir(%struct.__dirstream* %31), !dbg !700
  br label %if.end67, !dbg !701

if.end67:                                         ; preds = %while.end, %if.end26
  %32 = load i8*, i8** %local_cwd, align 8, !dbg !702
  %tobool68 = icmp ne i8* %32, null, !dbg !702
  br i1 %tobool68, label %if.then69, label %if.end71, !dbg !704

if.then69:                                        ; preds = %if.end67
  %33 = load i8*, i8** %local_cwd, align 8, !dbg !705
  %call70 = call i32 @chdir(i8* %33) #7, !dbg !707
  %34 = load i8*, i8** %local_cwd, align 8, !dbg !708
  call void @free(i8* %34) #7, !dbg !709
  br label %if.end71, !dbg !710

if.end71:                                         ; preds = %if.then18, %if.then69, %if.end67
  ret void, !dbg !711
}

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

declare %struct.__dirstream* @opendir(i8*) #3

declare i32 @closedir(%struct.__dirstream*) #3

declare i8* @bftpd_cwd_getcwd(...) #3

; Function Attrs: nounwind
declare i32 @chdir(i8*) #2

declare %struct.dirent* @readdir64(%struct.__dirstream*) #3

declare %struct._IO_FILE* @fopen64(i8*, i8*) #3

declare i32 @fclose(%struct._IO_FILE*) #3

declare i32 @fnmatch(i8*, i8*, i32) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!138, !139}
!llvm.ident = !{!140}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !48, globals: !124)
!1 = !DIFile(filename: "dirlist.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4, !24, !47}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !6, line: 46, size: 1152, align: 64, elements: !7)
!6 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!7 = !{!8, !12, !14, !16, !19, !21, !23, !25, !26, !29, !31, !33, !41, !42, !43}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !5, file: !6, line: 48, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !10, line: 124, baseType: !11)
!10 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!11 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !5, file: !6, line: 53, baseType: !13, size: 64, align: 64, offset: 64)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !10, line: 127, baseType: !11)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !5, file: !6, line: 61, baseType: !15, size: 64, align: 64, offset: 128)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !10, line: 130, baseType: !11)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !5, file: !6, line: 62, baseType: !17, size: 32, align: 32, offset: 192)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !10, line: 129, baseType: !18)
!18 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !5, file: !6, line: 64, baseType: !20, size: 32, align: 32, offset: 224)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !10, line: 125, baseType: !18)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !5, file: !6, line: 65, baseType: !22, size: 32, align: 32, offset: 256)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !10, line: 126, baseType: !18)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !5, file: !6, line: 67, baseType: !24, size: 32, align: 32, offset: 288)
!24 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !5, file: !6, line: 69, baseType: !9, size: 64, align: 64, offset: 320)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !5, file: !6, line: 74, baseType: !27, size: 64, align: 64, offset: 384)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !10, line: 131, baseType: !28)
!28 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !5, file: !6, line: 78, baseType: !30, size: 64, align: 64, offset: 448)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !10, line: 153, baseType: !28)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !5, file: !6, line: 80, baseType: !32, size: 64, align: 64, offset: 512)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !10, line: 158, baseType: !28)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !5, file: !6, line: 91, baseType: !34, size: 128, align: 64, offset: 576)
!34 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !35, line: 120, size: 128, align: 64, elements: !36)
!35 = !DIFile(filename: "/usr/include/time.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!36 = !{!37, !39}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !34, file: !35, line: 122, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !10, line: 139, baseType: !28)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !34, file: !35, line: 123, baseType: !40, size: 64, align: 64, offset: 64)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !10, line: 175, baseType: !28)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !5, file: !6, line: 92, baseType: !34, size: 128, align: 64, offset: 704)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !5, file: !6, line: 93, baseType: !34, size: 128, align: 64, offset: 832)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !5, file: !6, line: 106, baseType: !44, size: 192, align: 64, offset: 960)
!44 = !DICompositeType(tag: DW_TAG_array_type, baseType: !40, size: 192, align: 64, elements: !45)
!45 = !{!46}
!46 = !DISubrange(count: 3)
!47 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !{!49, !53, !56, !57, !118, !121}
!49 = distinct !DISubprogram(name: "add_to_hidegroups", scope: !50, file: !50, line: 55, type: !51, isLocal: false, isDefinition: true, scopeLine: 56, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!50 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!51 = !DISubroutineType(types: !52)
!52 = !{null, !24}
!53 = distinct !DISubprogram(name: "hidegroups_init", scope: !50, file: !50, line: 70, type: !54, isLocal: false, isDefinition: true, scopeLine: 71, isOptimized: false, variables: !2)
!54 = !DISubroutineType(types: !55)
!55 = !{null}
!56 = distinct !DISubprogram(name: "hidegroups_end", scope: !50, file: !50, line: 90, type: !54, isLocal: false, isDefinition: true, scopeLine: 91, isOptimized: false, variables: !2)
!57 = distinct !DISubprogram(name: "bftpd_stat", scope: !50, file: !50, line: 101, type: !58, isLocal: false, isDefinition: true, scopeLine: 102, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!58 = !DISubroutineType(types: !59)
!59 = !{null, !60, !62}
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !64, line: 48, baseType: !65)
!64 = !DIFile(filename: "/usr/include/stdio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!65 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !66, line: 245, size: 1728, align: 64, elements: !67)
!66 = !DIFile(filename: "/usr/include/libio.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!67 = !{!68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !88, !89, !90, !91, !92, !94, !96, !100, !103, !105, !107, !108, !109, !110, !113, !114}
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !65, file: !66, line: 246, baseType: !24, size: 32, align: 32)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !65, file: !66, line: 251, baseType: !60, size: 64, align: 64, offset: 64)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !65, file: !66, line: 252, baseType: !60, size: 64, align: 64, offset: 128)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !65, file: !66, line: 253, baseType: !60, size: 64, align: 64, offset: 192)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !65, file: !66, line: 254, baseType: !60, size: 64, align: 64, offset: 256)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !65, file: !66, line: 255, baseType: !60, size: 64, align: 64, offset: 320)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !65, file: !66, line: 256, baseType: !60, size: 64, align: 64, offset: 384)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !65, file: !66, line: 257, baseType: !60, size: 64, align: 64, offset: 448)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !65, file: !66, line: 258, baseType: !60, size: 64, align: 64, offset: 512)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !65, file: !66, line: 260, baseType: !60, size: 64, align: 64, offset: 576)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !65, file: !66, line: 261, baseType: !60, size: 64, align: 64, offset: 640)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !65, file: !66, line: 262, baseType: !60, size: 64, align: 64, offset: 704)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !65, file: !66, line: 264, baseType: !81, size: 64, align: 64, offset: 768)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !66, line: 160, size: 192, align: 64, elements: !83)
!83 = !{!84, !85, !87}
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !82, file: !66, line: 161, baseType: !81, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !82, file: !66, line: 162, baseType: !86, size: 64, align: 64, offset: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !82, file: !66, line: 166, baseType: !24, size: 32, align: 32, offset: 128)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !65, file: !66, line: 266, baseType: !86, size: 64, align: 64, offset: 832)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !65, file: !66, line: 268, baseType: !24, size: 32, align: 32, offset: 896)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !65, file: !66, line: 272, baseType: !24, size: 32, align: 32, offset: 928)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !65, file: !66, line: 274, baseType: !27, size: 64, align: 64, offset: 960)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !65, file: !66, line: 278, baseType: !93, size: 16, align: 16, offset: 1024)
!93 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !65, file: !66, line: 279, baseType: !95, size: 8, align: 8, offset: 1040)
!95 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !65, file: !66, line: 280, baseType: !97, size: 8, align: 8, offset: 1048)
!97 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 8, align: 8, elements: !98)
!98 = !{!99}
!99 = !DISubrange(count: 1)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !65, file: !66, line: 284, baseType: !101, size: 64, align: 64, offset: 1088)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !66, line: 154, baseType: null)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !65, file: !66, line: 293, baseType: !104, size: 64, align: 64, offset: 1152)
!104 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !10, line: 132, baseType: !28)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !65, file: !66, line: 302, baseType: !106, size: 64, align: 64, offset: 1216)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !65, file: !66, line: 303, baseType: !106, size: 64, align: 64, offset: 1280)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !65, file: !66, line: 304, baseType: !106, size: 64, align: 64, offset: 1344)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !65, file: !66, line: 305, baseType: !106, size: 64, align: 64, offset: 1408)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !65, file: !66, line: 306, baseType: !111, size: 64, align: 64, offset: 1472)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !112, line: 62, baseType: !11)
!112 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!113 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !65, file: !66, line: 308, baseType: !24, size: 32, align: 32, offset: 1536)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !65, file: !66, line: 310, baseType: !115, size: 160, align: 8, offset: 1568)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 160, align: 8, elements: !116)
!116 = !{!117}
!117 = !DISubrange(count: 20)
!118 = distinct !DISubprogram(name: "dirlist_one_file", scope: !50, file: !50, line: 166, type: !119, isLocal: false, isDefinition: true, scopeLine: 167, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!119 = !DISubroutineType(types: !120)
!120 = !{null, !60, !62, !61}
!121 = distinct !DISubprogram(name: "dirlist", scope: !50, file: !50, line: 193, type: !122, isLocal: false, isDefinition: true, scopeLine: 194, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!122 = !DISubroutineType(types: !123)
!123 = !{null, !60, !62, !61, !24}
!124 = !{!125, !132, !133, !135, !136, !137}
!125 = !DIGlobalVariable(name: "hidegroups", scope: !0, file: !50, line: 53, type: !126, isLocal: false, isDefinition: true, variable: %struct.hidegroup** @hidegroups)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DICompositeType(tag: DW_TAG_structure_type, name: "hidegroup", file: !128, line: 4, size: 128, align: 64, elements: !129)
!128 = !DIFile(filename: "./dirlist.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!129 = !{!130, !131}
!130 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !127, file: !128, line: 5, baseType: !24, size: 32, align: 32)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !127, file: !128, line: 6, baseType: !126, size: 64, align: 64, offset: 64)
!132 = !DIGlobalVariable(name: "tmp", scope: !49, file: !50, line: 57, type: !126, isLocal: true, isDefinition: true, variable: %struct.hidegroup** @add_to_hidegroups.tmp)
!133 = !DIGlobalVariable(name: "configpath", scope: !0, file: !134, line: 25, type: !60, isLocal: false, isDefinition: true, variable: i8** @configpath)
!134 = !DIFile(filename: "./main.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!135 = !DIGlobalVariable(name: "daemonmode", scope: !0, file: !134, line: 26, type: !24, isLocal: false, isDefinition: true, variable: i32* @daemonmode)
!136 = !DIGlobalVariable(name: "pre_write_script", scope: !0, file: !134, line: 29, type: !60, isLocal: false, isDefinition: true, variable: i8** @pre_write_script)
!137 = !DIGlobalVariable(name: "post_write_script", scope: !0, file: !134, line: 30, type: !60, isLocal: false, isDefinition: true, variable: i8** @post_write_script)
!138 = !{i32 2, !"Dwarf Version", i32 4}
!139 = !{i32 2, !"Debug Info Version", i32 3}
!140 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!141 = !DILocalVariable(name: "gid", arg: 1, scope: !49, file: !50, line: 55, type: !24)
!142 = !DIExpression()
!143 = !DILocation(line: 55, column: 28, scope: !49)
!144 = !DILocation(line: 58, column: 9, scope: !145)
!145 = distinct !DILexicalBlock(scope: !49, file: !50, line: 58, column: 9)
!146 = !DILocation(line: 58, column: 9, scope: !49)
!147 = !DILocation(line: 59, column: 27, scope: !145)
!148 = !DILocation(line: 59, column: 15, scope: !145)
!149 = !DILocation(line: 59, column: 20, scope: !145)
!150 = !DILocation(line: 59, column: 25, scope: !145)
!151 = !DILocation(line: 59, column: 13, scope: !145)
!152 = !DILocation(line: 59, column: 9, scope: !145)
!153 = !DILocation(line: 61, column: 28, scope: !145)
!154 = !DILocation(line: 61, column: 26, scope: !145)
!155 = !DILocation(line: 61, column: 20, scope: !145)
!156 = !DILocation(line: 63, column: 9, scope: !157)
!157 = distinct !DILexicalBlock(scope: !49, file: !50, line: 63, column: 9)
!158 = !DILocation(line: 63, column: 9, scope: !49)
!159 = !DILocation(line: 65, column: 7, scope: !160)
!160 = distinct !DILexicalBlock(scope: !157, file: !50, line: 64, column: 5)
!161 = !DILocation(line: 65, column: 12, scope: !160)
!162 = !DILocation(line: 65, column: 17, scope: !160)
!163 = !DILocation(line: 66, column: 19, scope: !160)
!164 = !DILocation(line: 66, column: 7, scope: !160)
!165 = !DILocation(line: 66, column: 12, scope: !160)
!166 = !DILocation(line: 66, column: 17, scope: !160)
!167 = !DILocation(line: 67, column: 5, scope: !160)
!168 = !DILocation(line: 68, column: 1, scope: !49)
!169 = !DILocalVariable(name: "foo", scope: !53, file: !50, line: 72, type: !60)
!170 = !DILocation(line: 72, column: 11, scope: !53)
!171 = !DILocation(line: 72, column: 24, scope: !53)
!172 = !DILocation(line: 72, column: 17, scope: !173)
!173 = !DILexicalBlockFile(scope: !53, file: !50, discriminator: 1)
!174 = !DILocalVariable(name: "foo_save", scope: !53, file: !50, line: 73, type: !60)
!175 = !DILocation(line: 73, column: 11, scope: !53)
!176 = !DILocation(line: 73, column: 22, scope: !53)
!177 = !DILocalVariable(name: "bar", scope: !53, file: !50, line: 74, type: !60)
!178 = !DILocation(line: 74, column: 11, scope: !53)
!179 = !DILocalVariable(name: "tmpgrp", scope: !53, file: !50, line: 75, type: !180)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DICompositeType(tag: DW_TAG_structure_type, name: "group", file: !182, line: 42, size: 256, align: 64, elements: !183)
!182 = !DIFile(filename: "/usr/include/grp.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!183 = !{!184, !185, !186, !187}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "gr_name", scope: !181, file: !182, line: 44, baseType: !60, size: 64, align: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "gr_passwd", scope: !181, file: !182, line: 45, baseType: !60, size: 64, align: 64, offset: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "gr_gid", scope: !181, file: !182, line: 46, baseType: !22, size: 32, align: 32, offset: 128)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "gr_mem", scope: !181, file: !182, line: 47, baseType: !188, size: 64, align: 64, offset: 192)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!189 = !DILocation(line: 75, column: 19, scope: !53)
!190 = !DILocation(line: 77, column: 5, scope: !53)
!191 = !DILocation(line: 77, column: 26, scope: !173)
!192 = !DILocation(line: 77, column: 19, scope: !173)
!193 = !DILocation(line: 77, column: 17, scope: !173)
!194 = !DILocation(line: 77, column: 5, scope: !173)
!195 = !DILocation(line: 78, column: 13, scope: !196)
!196 = distinct !DILexicalBlock(scope: !53, file: !50, line: 77, column: 38)
!197 = !DILocation(line: 79, column: 21, scope: !198)
!198 = distinct !DILexicalBlock(scope: !196, file: !50, line: 79, column: 13)
!199 = !DILocation(line: 79, column: 14, scope: !198)
!200 = !DILocation(line: 79, column: 32, scope: !198)
!201 = !DILocation(line: 79, column: 45, scope: !202)
!202 = !DILexicalBlockFile(scope: !198, file: !50, discriminator: 1)
!203 = !DILocation(line: 79, column: 37, scope: !202)
!204 = !DILocation(line: 79, column: 13, scope: !202)
!205 = !DILocation(line: 81, column: 36, scope: !206)
!206 = distinct !DILexicalBlock(scope: !207, file: !50, line: 81, column: 17)
!207 = distinct !DILexicalBlock(scope: !198, file: !50, line: 79, column: 62)
!208 = !DILocation(line: 81, column: 27, scope: !206)
!209 = !DILocation(line: 81, column: 25, scope: !206)
!210 = !DILocation(line: 81, column: 17, scope: !207)
!211 = !DILocation(line: 82, column: 35, scope: !206)
!212 = !DILocation(line: 82, column: 43, scope: !206)
!213 = !DILocation(line: 82, column: 17, scope: !206)
!214 = !DILocation(line: 83, column: 9, scope: !207)
!215 = !DILocation(line: 84, column: 25, scope: !216)
!216 = distinct !DILexicalBlock(scope: !198, file: !50, line: 84, column: 17)
!217 = !DILocation(line: 84, column: 17, scope: !216)
!218 = !DILocation(line: 84, column: 17, scope: !198)
!219 = !DILocation(line: 85, column: 43, scope: !216)
!220 = !DILocation(line: 85, column: 35, scope: !216)
!221 = !DILocation(line: 85, column: 17, scope: !222)
!222 = !DILexicalBlockFile(scope: !216, file: !50, discriminator: 1)
!223 = !DILocation(line: 85, column: 17, scope: !216)
!224 = !DILocation(line: 77, column: 5, scope: !225)
!225 = !DILexicalBlockFile(scope: !53, file: !50, discriminator: 2)
!226 = !DILocation(line: 87, column: 7, scope: !53)
!227 = !DILocation(line: 87, column: 2, scope: !53)
!228 = !DILocation(line: 88, column: 1, scope: !53)
!229 = !DILocalVariable(name: "tmp", scope: !56, file: !50, line: 92, type: !126)
!230 = !DILocation(line: 92, column: 23, scope: !56)
!231 = !DILocation(line: 92, column: 29, scope: !56)
!232 = !DILocation(line: 93, column: 9, scope: !233)
!233 = distinct !DILexicalBlock(scope: !56, file: !50, line: 93, column: 9)
!234 = !DILocation(line: 93, column: 9, scope: !56)
!235 = !DILocation(line: 94, column: 9, scope: !233)
!236 = !DILocation(line: 94, column: 16, scope: !237)
!237 = !DILexicalBlockFile(scope: !233, file: !50, discriminator: 1)
!238 = !DILocation(line: 94, column: 28, scope: !237)
!239 = !DILocation(line: 94, column: 9, scope: !237)
!240 = !DILocation(line: 95, column: 19, scope: !241)
!241 = distinct !DILexicalBlock(scope: !233, file: !50, line: 94, column: 34)
!242 = !DILocation(line: 95, column: 31, scope: !241)
!243 = !DILocation(line: 95, column: 17, scope: !241)
!244 = !DILocation(line: 96, column: 18, scope: !241)
!245 = !DILocation(line: 96, column: 13, scope: !241)
!246 = !DILocation(line: 97, column: 26, scope: !241)
!247 = !DILocation(line: 97, column: 24, scope: !241)
!248 = !DILocation(line: 94, column: 9, scope: !249)
!249 = !DILexicalBlockFile(scope: !233, file: !50, discriminator: 2)
!250 = !DILocation(line: 94, column: 9, scope: !251)
!251 = !DILexicalBlockFile(scope: !233, file: !50, discriminator: 3)
!252 = !DILocation(line: 99, column: 1, scope: !56)
!253 = !DILocalVariable(name: "name", arg: 1, scope: !57, file: !50, line: 101, type: !60)
!254 = !DILocation(line: 101, column: 23, scope: !57)
!255 = !DILocalVariable(name: "client", arg: 2, scope: !57, file: !50, line: 101, type: !62)
!256 = !DILocation(line: 101, column: 36, scope: !57)
!257 = !DILocalVariable(name: "statbuf", scope: !57, file: !50, line: 103, type: !5)
!258 = !DILocation(line: 103, column: 17, scope: !57)
!259 = !DILocalVariable(name: "temp", scope: !57, file: !50, line: 104, type: !260)
!260 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 2064, align: 8, elements: !261)
!261 = !{!262}
!262 = !DISubrange(count: 258)
!263 = !DILocation(line: 104, column: 7, scope: !57)
!264 = !DILocalVariable(name: "linktarget", scope: !57, file: !50, line: 104, type: !265)
!265 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 2080, align: 8, elements: !266)
!266 = !{!267}
!267 = !DISubrange(count: 260)
!268 = !DILocation(line: 104, column: 25, scope: !57)
!269 = !DILocalVariable(name: "perm", scope: !57, file: !50, line: 104, type: !270)
!270 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 88, align: 8, elements: !271)
!271 = !{!272}
!272 = !DISubrange(count: 11)
!273 = !DILocation(line: 104, column: 49, scope: !57)
!274 = !DILocalVariable(name: "timestr", scope: !57, file: !50, line: 104, type: !275)
!275 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 136, align: 8, elements: !276)
!276 = !{!277}
!277 = !DISubrange(count: 17)
!278 = !DILocation(line: 104, column: 59, scope: !57)
!279 = !DILocalVariable(name: "uid", scope: !57, file: !50, line: 105, type: !280)
!280 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 248, align: 8, elements: !281)
!281 = !{!282}
!282 = !DISubrange(count: 31)
!283 = !DILocation(line: 105, column: 3, scope: !57)
!284 = !DILocalVariable(name: "gid", scope: !57, file: !50, line: 105, type: !280)
!285 = !DILocation(line: 105, column: 21, scope: !57)
!286 = !DILocalVariable(name: "filetime", scope: !57, file: !50, line: 106, type: !287)
!287 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !35, line: 133, size: 448, align: 64, elements: !288)
!288 = !{!289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299}
!289 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !287, file: !35, line: 135, baseType: !24, size: 32, align: 32)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !287, file: !35, line: 136, baseType: !24, size: 32, align: 32, offset: 32)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !287, file: !35, line: 137, baseType: !24, size: 32, align: 32, offset: 64)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !287, file: !35, line: 138, baseType: !24, size: 32, align: 32, offset: 96)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !287, file: !35, line: 139, baseType: !24, size: 32, align: 32, offset: 128)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !287, file: !35, line: 140, baseType: !24, size: 32, align: 32, offset: 160)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !287, file: !35, line: 141, baseType: !24, size: 32, align: 32, offset: 192)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !287, file: !35, line: 142, baseType: !24, size: 32, align: 32, offset: 224)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !287, file: !35, line: 143, baseType: !24, size: 32, align: 32, offset: 256)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !287, file: !35, line: 146, baseType: !28, size: 64, align: 64, offset: 320)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !287, file: !35, line: 147, baseType: !300, size: 64, align: 64, offset: 384)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !61)
!302 = !DILocation(line: 106, column: 15, scope: !57)
!303 = !DILocalVariable(name: "tea_time", scope: !57, file: !50, line: 107, type: !304)
!304 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!305 = !DILocation(line: 107, column: 16, scope: !57)
!306 = !DILocalVariable(name: "local_time", scope: !57, file: !50, line: 107, type: !304)
!307 = !DILocation(line: 107, column: 27, scope: !57)
!308 = !DILocalVariable(name: "t", scope: !57, file: !50, line: 108, type: !309)
!309 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !35, line: 75, baseType: !38)
!310 = !DILocation(line: 108, column: 12, scope: !57)
!311 = !DILocation(line: 110, column: 15, scope: !312)
!312 = distinct !DILexicalBlock(scope: !57, file: !50, line: 110, column: 9)
!313 = !DILocation(line: 110, column: 9, scope: !312)
!314 = !DILocation(line: 110, column: 47, scope: !312)
!315 = !DILocation(line: 110, column: 9, scope: !57)
!316 = !DILocation(line: 111, column: 17, scope: !317)
!317 = distinct !DILexicalBlock(scope: !312, file: !50, line: 110, column: 54)
!318 = !DILocation(line: 111, column: 54, scope: !317)
!319 = !DILocation(line: 111, column: 45, scope: !320)
!320 = !DILexicalBlockFile(scope: !317, file: !50, discriminator: 1)
!321 = !DILocation(line: 111, column: 9, scope: !322)
!322 = !DILexicalBlockFile(scope: !317, file: !50, discriminator: 2)
!323 = !DILocation(line: 112, column: 9, scope: !317)
!324 = !DILocation(line: 115, column: 6, scope: !325)
!325 = distinct !DILexicalBlock(scope: !57, file: !50, line: 115, column: 6)
!326 = !DILocation(line: 115, column: 6, scope: !57)
!327 = !DILocation(line: 116, column: 10, scope: !328)
!328 = distinct !DILexicalBlock(scope: !325, file: !50, line: 115, column: 32)
!329 = !DILocation(line: 116, column: 3, scope: !328)
!330 = !DILocation(line: 117, column: 17, scope: !328)
!331 = !DILocation(line: 117, column: 23, scope: !328)
!332 = !DILocation(line: 117, column: 8, scope: !328)
!333 = !DILocation(line: 117, column: 3, scope: !328)
!334 = !DILocation(line: 117, column: 48, scope: !328)
!335 = !DILocation(line: 118, column: 11, scope: !328)
!336 = !DILocation(line: 118, column: 33, scope: !328)
!337 = !DILocation(line: 118, column: 3, scope: !328)
!338 = !DILocation(line: 119, column: 2, scope: !328)
!339 = !DILocation(line: 121, column: 10, scope: !340)
!340 = distinct !DILexicalBlock(scope: !325, file: !50, line: 119, column: 9)
!341 = !DILocation(line: 121, column: 3, scope: !340)
!342 = !DILocation(line: 122, column: 7, scope: !343)
!343 = distinct !DILexicalBlock(scope: !340, file: !50, line: 122, column: 7)
!344 = !DILocation(line: 122, column: 7, scope: !340)
!345 = !DILocation(line: 123, column: 4, scope: !343)
!346 = !DILocation(line: 123, column: 12, scope: !343)
!347 = !DILocation(line: 124, column: 15, scope: !348)
!348 = distinct !DILexicalBlock(scope: !340, file: !50, line: 124, column: 7)
!349 = !DILocation(line: 124, column: 23, scope: !348)
!350 = !DILocation(line: 124, column: 7, scope: !340)
!351 = !DILocation(line: 125, column: 4, scope: !348)
!352 = !DILocation(line: 125, column: 12, scope: !348)
!353 = !DILocation(line: 126, column: 15, scope: !354)
!354 = distinct !DILexicalBlock(scope: !340, file: !50, line: 126, column: 7)
!355 = !DILocation(line: 126, column: 23, scope: !354)
!356 = !DILocation(line: 126, column: 7, scope: !340)
!357 = !DILocation(line: 127, column: 4, scope: !354)
!358 = !DILocation(line: 127, column: 12, scope: !354)
!359 = !DILocation(line: 128, column: 15, scope: !360)
!360 = distinct !DILexicalBlock(scope: !340, file: !50, line: 128, column: 7)
!361 = !DILocation(line: 128, column: 23, scope: !360)
!362 = !DILocation(line: 128, column: 7, scope: !340)
!363 = !DILocation(line: 129, column: 4, scope: !360)
!364 = !DILocation(line: 129, column: 12, scope: !360)
!365 = !DILocation(line: 130, column: 15, scope: !366)
!366 = distinct !DILexicalBlock(scope: !340, file: !50, line: 130, column: 7)
!367 = !DILocation(line: 130, column: 23, scope: !366)
!368 = !DILocation(line: 130, column: 7, scope: !340)
!369 = !DILocation(line: 131, column: 4, scope: !366)
!370 = !DILocation(line: 131, column: 12, scope: !366)
!371 = !DILocation(line: 132, column: 15, scope: !372)
!372 = distinct !DILexicalBlock(scope: !340, file: !50, line: 132, column: 7)
!373 = !DILocation(line: 132, column: 23, scope: !372)
!374 = !DILocation(line: 132, column: 7, scope: !340)
!375 = !DILocation(line: 133, column: 4, scope: !372)
!376 = !DILocation(line: 133, column: 12, scope: !372)
!377 = !DILocation(line: 134, column: 15, scope: !378)
!378 = distinct !DILexicalBlock(scope: !340, file: !50, line: 134, column: 7)
!379 = !DILocation(line: 134, column: 23, scope: !378)
!380 = !DILocation(line: 134, column: 7, scope: !340)
!381 = !DILocation(line: 135, column: 4, scope: !378)
!382 = !DILocation(line: 135, column: 12, scope: !378)
!383 = !DILocation(line: 136, column: 15, scope: !384)
!384 = distinct !DILexicalBlock(scope: !340, file: !50, line: 136, column: 7)
!385 = !DILocation(line: 136, column: 23, scope: !384)
!386 = !DILocation(line: 136, column: 7, scope: !340)
!387 = !DILocation(line: 137, column: 4, scope: !384)
!388 = !DILocation(line: 137, column: 12, scope: !384)
!389 = !DILocation(line: 138, column: 15, scope: !390)
!390 = distinct !DILexicalBlock(scope: !340, file: !50, line: 138, column: 7)
!391 = !DILocation(line: 138, column: 23, scope: !390)
!392 = !DILocation(line: 138, column: 7, scope: !340)
!393 = !DILocation(line: 139, column: 4, scope: !390)
!394 = !DILocation(line: 139, column: 12, scope: !390)
!395 = !DILocation(line: 140, column: 15, scope: !396)
!396 = distinct !DILexicalBlock(scope: !340, file: !50, line: 140, column: 7)
!397 = !DILocation(line: 140, column: 23, scope: !396)
!398 = !DILocation(line: 140, column: 7, scope: !340)
!399 = !DILocation(line: 141, column: 4, scope: !396)
!400 = !DILocation(line: 141, column: 12, scope: !396)
!401 = !DILocation(line: 142, column: 3, scope: !340)
!402 = !DILocation(line: 142, column: 17, scope: !340)
!403 = !DILocation(line: 147, column: 38, scope: !57)
!404 = !DILocation(line: 147, column: 18, scope: !57)
!405 = !DILocation(line: 147, column: 16, scope: !57)
!406 = !DILocation(line: 148, column: 11, scope: !407)
!407 = distinct !DILexicalBlock(scope: !57, file: !50, line: 148, column: 9)
!408 = !DILocation(line: 148, column: 9, scope: !57)
!409 = !DILocation(line: 148, column: 23, scope: !410)
!410 = !DILexicalBlockFile(scope: !407, file: !50, discriminator: 1)
!411 = !DILocation(line: 149, column: 5, scope: !57)
!412 = !DILocation(line: 149, column: 23, scope: !57)
!413 = !DILocation(line: 150, column: 5, scope: !57)
!414 = !DILocation(line: 151, column: 16, scope: !57)
!415 = !DILocation(line: 151, column: 14, scope: !57)
!416 = !DILocation(line: 152, column: 11, scope: !417)
!417 = distinct !DILexicalBlock(scope: !57, file: !50, line: 152, column: 9)
!418 = !DILocation(line: 152, column: 9, scope: !57)
!419 = !DILocation(line: 152, column: 21, scope: !420)
!420 = !DILexicalBlockFile(scope: !417, file: !50, discriminator: 1)
!421 = !DILocation(line: 154, column: 18, scope: !422)
!422 = distinct !DILexicalBlock(scope: !57, file: !50, line: 154, column: 9)
!423 = !DILocation(line: 154, column: 29, scope: !422)
!424 = !DILocation(line: 154, column: 39, scope: !422)
!425 = !DILocation(line: 154, column: 26, scope: !422)
!426 = !DILocation(line: 154, column: 9, scope: !57)
!427 = !DILocation(line: 155, column: 16, scope: !422)
!428 = !DILocation(line: 155, column: 41, scope: !422)
!429 = !DILocation(line: 155, column: 25, scope: !422)
!430 = !DILocation(line: 155, column: 52, scope: !422)
!431 = !DILocation(line: 155, column: 6, scope: !432)
!432 = !DILexicalBlockFile(scope: !422, file: !50, discriminator: 1)
!433 = !DILocation(line: 155, column: 6, scope: !422)
!434 = !DILocation(line: 157, column: 18, scope: !422)
!435 = !DILocation(line: 157, column: 9, scope: !422)
!436 = !DILocation(line: 158, column: 24, scope: !57)
!437 = !DILocation(line: 158, column: 32, scope: !57)
!438 = !DILocation(line: 158, column: 44, scope: !57)
!439 = !DILocation(line: 158, column: 5, scope: !57)
!440 = !DILocation(line: 158, column: 52, scope: !57)
!441 = !DILocation(line: 159, column: 24, scope: !57)
!442 = !DILocation(line: 159, column: 32, scope: !57)
!443 = !DILocation(line: 159, column: 43, scope: !57)
!444 = !DILocation(line: 159, column: 5, scope: !57)
!445 = !DILocation(line: 159, column: 51, scope: !57)
!446 = !DILocation(line: 160, column: 10, scope: !57)
!447 = !DILocation(line: 160, column: 55, scope: !57)
!448 = !DILocation(line: 161, column: 18, scope: !57)
!449 = !DILocation(line: 161, column: 4, scope: !57)
!450 = !DILocation(line: 161, column: 28, scope: !57)
!451 = !DILocation(line: 161, column: 33, scope: !57)
!452 = !DILocation(line: 162, column: 33, scope: !57)
!453 = !DILocation(line: 163, column: 4, scope: !57)
!454 = !DILocation(line: 163, column: 13, scope: !57)
!455 = !DILocation(line: 163, column: 19, scope: !57)
!456 = !DILocation(line: 160, column: 2, scope: !57)
!457 = !DILocation(line: 164, column: 1, scope: !57)
!458 = !DILocation(line: 164, column: 1, scope: !459)
!459 = !DILexicalBlockFile(scope: !57, file: !50, discriminator: 1)
!460 = !DILocalVariable(name: "name", arg: 1, scope: !118, file: !50, line: 166, type: !60)
!461 = !DILocation(line: 166, column: 29, scope: !118)
!462 = !DILocalVariable(name: "client", arg: 2, scope: !118, file: !50, line: 166, type: !62)
!463 = !DILocation(line: 166, column: 41, scope: !118)
!464 = !DILocalVariable(name: "verbose", arg: 3, scope: !118, file: !50, line: 166, type: !61)
!465 = !DILocation(line: 166, column: 54, scope: !118)
!466 = !DILocalVariable(name: "statbuf", scope: !118, file: !50, line: 168, type: !5)
!467 = !DILocation(line: 168, column: 17, scope: !118)
!468 = !DILocalVariable(name: "tmp", scope: !118, file: !50, line: 169, type: !126)
!469 = !DILocation(line: 169, column: 23, scope: !118)
!470 = !DILocation(line: 169, column: 29, scope: !118)
!471 = !DILocalVariable(name: "filename_index", scope: !118, file: !50, line: 170, type: !60)
!472 = !DILocation(line: 170, column: 11, scope: !118)
!473 = !DILocation(line: 172, column: 15, scope: !474)
!474 = distinct !DILexicalBlock(scope: !118, file: !50, line: 172, column: 9)
!475 = !DILocation(line: 172, column: 10, scope: !474)
!476 = !DILocation(line: 172, column: 9, scope: !118)
!477 = !DILocation(line: 173, column: 13, scope: !478)
!478 = distinct !DILexicalBlock(scope: !479, file: !50, line: 173, column: 13)
!479 = distinct !DILexicalBlock(scope: !474, file: !50, line: 172, column: 48)
!480 = !DILocation(line: 173, column: 13, scope: !479)
!481 = !DILocation(line: 174, column: 13, scope: !478)
!482 = !DILocation(line: 175, column: 29, scope: !483)
!483 = distinct !DILexicalBlock(scope: !484, file: !50, line: 175, column: 21)
!484 = distinct !DILexicalBlock(scope: !478, file: !50, line: 174, column: 16)
!485 = !DILocation(line: 175, column: 39, scope: !483)
!486 = !DILocation(line: 175, column: 44, scope: !483)
!487 = !DILocation(line: 175, column: 36, scope: !483)
!488 = !DILocation(line: 175, column: 21, scope: !484)
!489 = !DILocation(line: 176, column: 21, scope: !483)
!490 = !DILocation(line: 177, column: 13, scope: !484)
!491 = !DILocation(line: 177, column: 29, scope: !492)
!492 = !DILexicalBlockFile(scope: !478, file: !50, discriminator: 1)
!493 = !DILocation(line: 177, column: 34, scope: !492)
!494 = !DILocation(line: 177, column: 27, scope: !492)
!495 = !DILocation(line: 177, column: 13, scope: !492)
!496 = !DILocation(line: 177, column: 13, scope: !497)
!497 = !DILexicalBlockFile(scope: !484, file: !50, discriminator: 2)
!498 = !DILocation(line: 178, column: 5, scope: !479)
!499 = !DILocation(line: 181, column: 30, scope: !118)
!500 = !DILocation(line: 181, column: 22, scope: !118)
!501 = !DILocation(line: 181, column: 20, scope: !118)
!502 = !DILocation(line: 182, column: 9, scope: !503)
!503 = distinct !DILexicalBlock(scope: !118, file: !50, line: 182, column: 9)
!504 = !DILocation(line: 182, column: 9, scope: !118)
!505 = !DILocation(line: 183, column: 22, scope: !503)
!506 = !DILocation(line: 183, column: 8, scope: !503)
!507 = !DILocation(line: 185, column: 25, scope: !503)
!508 = !DILocation(line: 185, column: 23, scope: !503)
!509 = !DILocation(line: 187, column: 9, scope: !510)
!510 = distinct !DILexicalBlock(scope: !118, file: !50, line: 187, column: 9)
!511 = !DILocation(line: 187, column: 9, scope: !118)
!512 = !DILocation(line: 188, column: 20, scope: !510)
!513 = !DILocation(line: 188, column: 26, scope: !510)
!514 = !DILocation(line: 188, column: 9, scope: !510)
!515 = !DILocation(line: 190, column: 17, scope: !510)
!516 = !DILocation(line: 190, column: 35, scope: !510)
!517 = !DILocation(line: 190, column: 9, scope: !510)
!518 = !DILocation(line: 191, column: 1, scope: !118)
!519 = !DILocalVariable(name: "name", arg: 1, scope: !121, file: !50, line: 193, type: !60)
!520 = !DILocation(line: 193, column: 20, scope: !121)
!521 = !DILocalVariable(name: "client", arg: 2, scope: !121, file: !50, line: 193, type: !62)
!522 = !DILocation(line: 193, column: 33, scope: !121)
!523 = !DILocalVariable(name: "verbose", arg: 3, scope: !121, file: !50, line: 193, type: !61)
!524 = !DILocation(line: 193, column: 46, scope: !121)
!525 = !DILocalVariable(name: "show_hidden", arg: 4, scope: !121, file: !50, line: 193, type: !24)
!526 = !DILocation(line: 193, column: 59, scope: !121)
!527 = !DILocalVariable(name: "directory", scope: !121, file: !50, line: 195, type: !528)
!528 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !529, size: 64, align: 64)
!529 = !DIDerivedType(tag: DW_TAG_typedef, name: "DIR", file: !530, line: 127, baseType: !531)
!530 = !DIFile(filename: "/usr/include/dirent.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!531 = !DICompositeType(tag: DW_TAG_structure_type, name: "__dirstream", file: !530, line: 127, flags: DIFlagFwdDecl)
!532 = !DILocation(line: 195, column: 10, scope: !121)
!533 = !DILocalVariable(name: "can_see_file", scope: !121, file: !50, line: 196, type: !62)
!534 = !DILocation(line: 196, column: 11, scope: !121)
!535 = !DILocalVariable(name: "show_nonreadable_files", scope: !121, file: !50, line: 197, type: !24)
!536 = !DILocation(line: 197, column: 9, scope: !121)
!537 = !DILocalVariable(name: "show_hidden_files", scope: !121, file: !50, line: 198, type: !24)
!538 = !DILocation(line: 198, column: 9, scope: !121)
!539 = !DILocalVariable(name: "skip_file", scope: !121, file: !50, line: 199, type: !24)
!540 = !DILocation(line: 199, column: 9, scope: !121)
!541 = !DILocalVariable(name: "file_is_hidden", scope: !121, file: !50, line: 199, type: !24)
!542 = !DILocation(line: 199, column: 20, scope: !121)
!543 = !DILocalVariable(name: "local_cwd", scope: !121, file: !50, line: 200, type: !60)
!544 = !DILocation(line: 200, column: 11, scope: !121)
!545 = !DILocalVariable(name: "pattern", scope: !121, file: !50, line: 201, type: !60)
!546 = !DILocation(line: 201, column: 11, scope: !121)
!547 = !DILocalVariable(name: "short_pattern", scope: !121, file: !50, line: 201, type: !60)
!548 = !DILocation(line: 201, column: 28, scope: !121)
!549 = !DILocalVariable(name: "dir_entry", scope: !121, file: !50, line: 203, type: !550)
!550 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !551, size: 64, align: 64)
!551 = !DICompositeType(tag: DW_TAG_structure_type, name: "dirent", file: !552, line: 22, size: 2240, align: 64, elements: !553)
!552 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/dirent.h", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!553 = !{!554, !556, !557, !558, !560}
!554 = !DIDerivedType(tag: DW_TAG_member, name: "d_ino", scope: !551, file: !552, line: 28, baseType: !555, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino64_t", file: !10, line: 128, baseType: !11)
!556 = !DIDerivedType(tag: DW_TAG_member, name: "d_off", scope: !551, file: !552, line: 29, baseType: !104, size: 64, align: 64, offset: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "d_reclen", scope: !551, file: !552, line: 31, baseType: !93, size: 16, align: 16, offset: 128)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "d_type", scope: !551, file: !552, line: 32, baseType: !559, size: 8, align: 8, offset: 144)
!559 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "d_name", scope: !551, file: !552, line: 33, baseType: !561, size: 2048, align: 8, offset: 152)
!561 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 2048, align: 8, elements: !562)
!562 = !{!563}
!563 = !DISubrange(count: 256)
!564 = !DILocation(line: 203, column: 20, scope: !121)
!565 = !DILocation(line: 206, column: 11, scope: !566)
!566 = distinct !DILexicalBlock(scope: !121, file: !50, line: 206, column: 10)
!567 = !DILocation(line: 206, column: 10, scope: !566)
!568 = !DILocation(line: 206, column: 24, scope: !566)
!569 = !DILocation(line: 207, column: 25, scope: !566)
!570 = !DILocation(line: 207, column: 13, scope: !571)
!571 = !DILexicalBlockFile(scope: !566, file: !50, discriminator: 1)
!572 = !DILocation(line: 207, column: 13, scope: !566)
!573 = !DILocation(line: 206, column: 10, scope: !574)
!574 = !DILexicalBlockFile(scope: !121, file: !50, discriminator: 1)
!575 = !DILocation(line: 208, column: 26, scope: !566)
!576 = !DILocation(line: 208, column: 8, scope: !566)
!577 = !DILocation(line: 211, column: 23, scope: !578)
!578 = distinct !DILexicalBlock(scope: !121, file: !50, line: 211, column: 9)
!579 = !DILocation(line: 211, column: 11, scope: !580)
!580 = !DILexicalBlockFile(scope: !578, file: !50, discriminator: 1)
!581 = !DILocation(line: 211, column: 11, scope: !578)
!582 = !DILocation(line: 211, column: 9, scope: !121)
!583 = !DILocation(line: 212, column: 26, scope: !578)
!584 = !DILocation(line: 212, column: 8, scope: !578)
!585 = !DILocation(line: 214, column: 23, scope: !586)
!586 = distinct !DILexicalBlock(scope: !121, file: !50, line: 214, column: 9)
!587 = !DILocation(line: 214, column: 11, scope: !588)
!588 = !DILexicalBlockFile(scope: !586, file: !50, discriminator: 1)
!589 = !DILocation(line: 214, column: 11, scope: !586)
!590 = !DILocation(line: 214, column: 9, scope: !121)
!591 = !DILocation(line: 215, column: 31, scope: !586)
!592 = !DILocation(line: 215, column: 8, scope: !586)
!593 = !DILocation(line: 217, column: 17, scope: !594)
!594 = distinct !DILexicalBlock(scope: !121, file: !50, line: 217, column: 9)
!595 = !DILocation(line: 217, column: 10, scope: !594)
!596 = !DILocation(line: 217, column: 30, scope: !594)
!597 = !DILocation(line: 217, column: 40, scope: !598)
!598 = !DILexicalBlockFile(scope: !594, file: !50, discriminator: 1)
!599 = !DILocation(line: 217, column: 33, scope: !598)
!600 = !DILocation(line: 217, column: 9, scope: !598)
!601 = !DILocation(line: 218, column: 9, scope: !594)
!602 = !DILocation(line: 220, column: 31, scope: !603)
!603 = distinct !DILexicalBlock(scope: !121, file: !50, line: 220, column: 10)
!604 = !DILocation(line: 220, column: 23, scope: !603)
!605 = !DILocation(line: 220, column: 21, scope: !603)
!606 = !DILocation(line: 220, column: 10, scope: !121)
!607 = !DILocation(line: 222, column: 18, scope: !608)
!608 = distinct !DILexicalBlock(scope: !603, file: !50, line: 221, column: 6)
!609 = !DILocation(line: 222, column: 9, scope: !608)
!610 = !DILocation(line: 223, column: 21, scope: !608)
!611 = !DILocation(line: 223, column: 19, scope: !608)
!612 = !DILocation(line: 224, column: 15, scope: !608)
!613 = !DILocation(line: 224, column: 9, scope: !608)
!614 = !DILocation(line: 225, column: 6, scope: !608)
!615 = !DILocation(line: 227, column: 18, scope: !603)
!616 = !DILocation(line: 227, column: 16, scope: !603)
!617 = !DILocation(line: 262, column: 21, scope: !121)
!618 = !DILocation(line: 262, column: 19, scope: !121)
!619 = !DILocation(line: 263, column: 13, scope: !620)
!620 = distinct !DILexicalBlock(scope: !121, file: !50, line: 263, column: 13)
!621 = !DILocation(line: 263, column: 13, scope: !121)
!622 = !DILocation(line: 265, column: 31, scope: !623)
!623 = distinct !DILexicalBlock(scope: !620, file: !50, line: 264, column: 9)
!624 = !DILocation(line: 265, column: 23, scope: !623)
!625 = !DILocation(line: 265, column: 21, scope: !623)
!626 = !DILocation(line: 266, column: 11, scope: !623)
!627 = !DILocation(line: 266, column: 18, scope: !628)
!628 = !DILexicalBlockFile(scope: !623, file: !50, discriminator: 1)
!629 = !DILocation(line: 266, column: 11, scope: !628)
!630 = !DILocation(line: 268, column: 36, scope: !631)
!631 = distinct !DILexicalBlock(scope: !623, file: !50, line: 267, column: 11)
!632 = !DILocation(line: 268, column: 47, scope: !631)
!633 = !DILocation(line: 268, column: 30, scope: !631)
!634 = !DILocation(line: 268, column: 28, scope: !631)
!635 = !DILocation(line: 269, column: 19, scope: !636)
!636 = distinct !DILexicalBlock(scope: !631, file: !50, line: 269, column: 19)
!637 = !DILocation(line: 269, column: 19, scope: !631)
!638 = !DILocation(line: 270, column: 26, scope: !636)
!639 = !DILocation(line: 270, column: 19, scope: !636)
!640 = !DILocation(line: 271, column: 33, scope: !631)
!641 = !DILocation(line: 271, column: 44, scope: !631)
!642 = !DILocation(line: 271, column: 54, scope: !631)
!643 = !DILocation(line: 271, column: 32, scope: !631)
!644 = !DILocation(line: 271, column: 30, scope: !631)
!645 = !DILocation(line: 272, column: 25, scope: !631)
!646 = !DILocation(line: 274, column: 23, scope: !647)
!647 = distinct !DILexicalBlock(scope: !631, file: !50, line: 274, column: 20)
!648 = !DILocation(line: 274, column: 39, scope: !647)
!649 = !DILocation(line: 274, column: 43, scope: !650)
!650 = !DILexicalBlockFile(scope: !647, file: !50, discriminator: 1)
!651 = !DILocation(line: 274, column: 42, scope: !650)
!652 = !DILocation(line: 274, column: 20, scope: !650)
!653 = !DILocation(line: 276, column: 25, scope: !654)
!654 = distinct !DILexicalBlock(scope: !655, file: !50, line: 276, column: 24)
!655 = distinct !DILexicalBlock(scope: !647, file: !50, line: 275, column: 15)
!656 = !DILocation(line: 276, column: 24, scope: !654)
!657 = !DILocation(line: 276, column: 39, scope: !654)
!658 = !DILocation(line: 276, column: 43, scope: !659)
!659 = !DILexicalBlockFile(scope: !654, file: !50, discriminator: 1)
!660 = !DILocation(line: 276, column: 42, scope: !659)
!661 = !DILocation(line: 276, column: 24, scope: !659)
!662 = !DILocation(line: 278, column: 27, scope: !663)
!663 = distinct !DILexicalBlock(scope: !664, file: !50, line: 278, column: 27)
!664 = distinct !DILexicalBlock(scope: !654, file: !50, line: 277, column: 19)
!665 = !DILocation(line: 278, column: 27, scope: !664)
!666 = !DILocation(line: 281, column: 49, scope: !667)
!667 = distinct !DILexicalBlock(scope: !663, file: !50, line: 279, column: 23)
!668 = !DILocation(line: 281, column: 41, scope: !667)
!669 = !DILocation(line: 281, column: 39, scope: !667)
!670 = !DILocation(line: 282, column: 29, scope: !671)
!671 = distinct !DILexicalBlock(scope: !667, file: !50, line: 282, column: 29)
!672 = !DILocation(line: 282, column: 29, scope: !667)
!673 = !DILocation(line: 283, column: 41, scope: !671)
!674 = !DILocation(line: 283, column: 28, scope: !671)
!675 = !DILocation(line: 285, column: 44, scope: !671)
!676 = !DILocation(line: 285, column: 42, scope: !671)
!677 = !DILocation(line: 286, column: 45, scope: !667)
!678 = !DILocation(line: 286, column: 60, scope: !667)
!679 = !DILocation(line: 286, column: 71, scope: !667)
!680 = !DILocation(line: 286, column: 37, scope: !667)
!681 = !DILocation(line: 286, column: 35, scope: !667)
!682 = !DILocation(line: 288, column: 23, scope: !667)
!683 = !DILocation(line: 290, column: 35, scope: !663)
!684 = !DILocation(line: 291, column: 19, scope: !664)
!685 = !DILocation(line: 292, column: 15, scope: !655)
!686 = !DILocation(line: 293, column: 21, scope: !687)
!687 = distinct !DILexicalBlock(scope: !631, file: !50, line: 293, column: 19)
!688 = !DILocation(line: 293, column: 19, scope: !631)
!689 = !DILocation(line: 294, column: 36, scope: !687)
!690 = !DILocation(line: 294, column: 47, scope: !687)
!691 = !DILocation(line: 294, column: 55, scope: !687)
!692 = !DILocation(line: 294, column: 63, scope: !687)
!693 = !DILocation(line: 294, column: 19, scope: !687)
!694 = !DILocation(line: 296, column: 35, scope: !631)
!695 = !DILocation(line: 296, column: 27, scope: !631)
!696 = !DILocation(line: 296, column: 25, scope: !631)
!697 = !DILocation(line: 266, column: 11, scope: !698)
!698 = !DILexicalBlockFile(scope: !623, file: !50, discriminator: 2)
!699 = !DILocation(line: 298, column: 20, scope: !623)
!700 = !DILocation(line: 298, column: 11, scope: !623)
!701 = !DILocation(line: 299, column: 9, scope: !623)
!702 = !DILocation(line: 301, column: 6, scope: !703)
!703 = distinct !DILexicalBlock(scope: !121, file: !50, line: 301, column: 6)
!704 = !DILocation(line: 301, column: 6, scope: !121)
!705 = !DILocation(line: 302, column: 9, scope: !706)
!706 = distinct !DILexicalBlock(scope: !703, file: !50, line: 301, column: 17)
!707 = !DILocation(line: 302, column: 3, scope: !706)
!708 = !DILocation(line: 303, column: 8, scope: !706)
!709 = !DILocation(line: 303, column: 3, scope: !706)
!710 = !DILocation(line: 304, column: 2, scope: !706)
!711 = !DILocation(line: 305, column: 1, scope: !121)
