; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_shar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.shar = type { i32, i32, %struct.archive_entry*, i32, i8*, [45 x i8], i64, i32, %struct.archive_string, %struct.archive_string }

@.str = private unnamed_addr constant [30 x i8] c"archive_write_set_format_shar\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate shar data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"shar\00", align 1
@.str.3 = private unnamed_addr constant [10 x i8] c"shar dump\00", align 1
@.str.4 = private unnamed_addr constant [11 x i8] c"#!/bin/sh\0A\00", align 1
@.str.5 = private unnamed_addr constant [27 x i8] c"# This is a shell archive\0A\00", align 1
@.str.6 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.7 = private unnamed_addr constant [3 x i8] c"./\00", align 1
@.str.8 = private unnamed_addr constant [32 x i8] c"shar format cannot archive this\00", align 1
@.str.9 = private unnamed_addr constant [11 x i8] c"echo x %s\0A\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"mkdir -p \00", align 1
@.str.11 = private unnamed_addr constant [19 x i8] c" > /dev/null 2>&1\0A\00", align 1
@.str.12 = private unnamed_addr constant [7 x i8] c"ln -f \00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c" %s\0A\00", align 1
@.str.14 = private unnamed_addr constant [8 x i8] c"ln -fs \00", align 1
@.str.15 = private unnamed_addr constant [25 x i8] c"test -e \22%s\22 || :> \22%s\22\0A\00", align 1
@.str.16 = private unnamed_addr constant [32 x i8] c"uudecode -p > %s << 'SHAR_END'\0A\00", align 1
@.str.17 = private unnamed_addr constant [10 x i8] c"begin %o \00", align 1
@.str.18 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.19 = private unnamed_addr constant [33 x i8] c"sed 's/^X//' > %s << 'SHAR_END'\0A\00", align 1
@.str.20 = private unnamed_addr constant [30 x i8] c"mkdir -p %s > /dev/null 2>&1\0A\00", align 1
@.str.21 = private unnamed_addr constant [11 x i8] c"mkfifo %s\0A\00", align 1
@.str.22 = private unnamed_addr constant [20 x i8] c"mknod %s c %ju %ju\0A\00", align 1
@.str.23 = private unnamed_addr constant [20 x i8] c"mknod %s b %ju %ju\0A\00", align 1
@shar_quote.meta = internal constant [26 x i8] c"\0A \09'`\22;&<>()|*?{}[]\5C$!#^~\00", align 16
@.str.24 = private unnamed_addr constant [4 x i8] c"\22\0A\22\00", align 1
@.str.25 = private unnamed_addr constant [3 x i8] c"\5Cn\00", align 1
@archive_write_shar_data_sed.ensured = internal constant i64 65533, align 8
@.str.26 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.27 = private unnamed_addr constant [16 x i8] c"Buffer overflow\00", align 1
@.str.28 = private unnamed_addr constant [7 x i8] c"`\0Aend\0A\00", align 1
@.str.29 = private unnamed_addr constant [10 x i8] c"SHAR_END\0A\00", align 1
@.str.30 = private unnamed_addr constant [10 x i8] c"chmod %o \00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"chown \00", align 1
@.str.32 = private unnamed_addr constant [2 x i8] c":\00", align 1
@.str.33 = private unnamed_addr constant [2 x i8] c" \00", align 1
@.str.34 = private unnamed_addr constant [12 x i8] c"chflags %s \00", align 1
@.str.35 = private unnamed_addr constant [6 x i8] c"exit\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_shar(%struct.archive* %_a) #0 !dbg !213 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %shar = alloca %struct.shar*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !241, metadata !242), !dbg !243
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !244, metadata !242), !dbg !245
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !246
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !247
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !245
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !248, metadata !242), !dbg !249
  br label %do.body, !dbg !250

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !251, metadata !242), !dbg !253
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !254
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !254
  store i32 %call, i32* %magic_test, align 4, !dbg !254
  %3 = load i32, i32* %magic_test, align 4, !dbg !254
  %cmp = icmp eq i32 %3, -30, !dbg !254
  br i1 %cmp, label %if.then, label %if.end, !dbg !254

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !256
  br label %return, !dbg !256

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !259

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !261
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !263
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !263
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !264
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !265

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !266
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !267
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !267
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !268
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !269
  br label %if.end5, !dbg !269

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 144) #6, !dbg !270
  %9 = bitcast i8* %call6 to %struct.shar*, !dbg !271
  store %struct.shar* %9, %struct.shar** %shar, align 8, !dbg !272
  %10 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !273
  %cmp7 = icmp eq %struct.shar* %10, null, !dbg !275
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !276

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !277
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !279
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !280
  store i32 -30, i32* %retval, align 4, !dbg !281
  br label %return, !dbg !281

if.end9:                                          ; preds = %if.end5
  br label %do.body10, !dbg !282

do.body10:                                        ; preds = %if.end9
  %12 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !283
  %work = getelementptr inbounds %struct.shar, %struct.shar* %12, i32 0, i32 8, !dbg !283
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work, i32 0, i32 0, !dbg !283
  store i8* null, i8** %s, align 8, !dbg !283
  %13 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !283
  %work11 = getelementptr inbounds %struct.shar, %struct.shar* %13, i32 0, i32 8, !dbg !283
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work11, i32 0, i32 1, !dbg !283
  store i64 0, i64* %length, align 8, !dbg !283
  %14 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !283
  %work12 = getelementptr inbounds %struct.shar, %struct.shar* %14, i32 0, i32 8, !dbg !283
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work12, i32 0, i32 2, !dbg !283
  store i64 0, i64* %buffer_length, align 8, !dbg !283
  br label %do.end13, !dbg !283

do.end13:                                         ; preds = %do.body10
  br label %do.body14, !dbg !286

do.body14:                                        ; preds = %do.end13
  %15 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !287
  %quoted_name = getelementptr inbounds %struct.shar, %struct.shar* %15, i32 0, i32 9, !dbg !287
  %s15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name, i32 0, i32 0, !dbg !287
  store i8* null, i8** %s15, align 8, !dbg !287
  %16 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !287
  %quoted_name16 = getelementptr inbounds %struct.shar, %struct.shar* %16, i32 0, i32 9, !dbg !287
  %length17 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name16, i32 0, i32 1, !dbg !287
  store i64 0, i64* %length17, align 8, !dbg !287
  %17 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !287
  %quoted_name18 = getelementptr inbounds %struct.shar, %struct.shar* %17, i32 0, i32 9, !dbg !287
  %buffer_length19 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name18, i32 0, i32 2, !dbg !287
  store i64 0, i64* %buffer_length19, align 8, !dbg !287
  br label %do.end20, !dbg !287

do.end20:                                         ; preds = %do.body14
  %18 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !290
  %19 = bitcast %struct.shar* %18 to i8*, !dbg !290
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !291
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 14, !dbg !292
  store i8* %19, i8** %format_data, align 8, !dbg !293
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !294
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 15, !dbg !295
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !296
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !297
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 19, !dbg !298
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_shar_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !299
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !300
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 21, !dbg !301
  store i32 (%struct.archive_write*)* @archive_write_shar_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !302
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !303
  %format_free21 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 22, !dbg !304
  store i32 (%struct.archive_write*)* @archive_write_shar_free, i32 (%struct.archive_write*)** %format_free21, align 8, !dbg !305
  %25 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !306
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 20, !dbg !307
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_shar_data_sed, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !308
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !309
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 18, !dbg !310
  store i32 (%struct.archive_write*)* @archive_write_shar_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !311
  %27 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !312
  %archive22 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 0, !dbg !313
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive22, i32 0, i32 3, !dbg !314
  store i32 131073, i32* %archive_format, align 8, !dbg !315
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !316
  %archive23 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 0, !dbg !317
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive23, i32 0, i32 4, !dbg !318
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !319
  store i32 0, i32* %retval, align 4, !dbg !320
  br label %return, !dbg !320

return:                                           ; preds = %do.end20, %if.then8, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !321
  ret i32 %29, !dbg !321
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_shar_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname = alloca i8*, align 8
  %name = alloca i8*, align 8
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  %shar = alloca %struct.shar*, align 8
  %mode = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !322, metadata !242), !dbg !323
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !324, metadata !242), !dbg !325
  call void @llvm.dbg.declare(metadata i8** %linkname, metadata !326, metadata !242), !dbg !327
  call void @llvm.dbg.declare(metadata i8** %name, metadata !328, metadata !242), !dbg !329
  call void @llvm.dbg.declare(metadata i8** %p, metadata !330, metadata !242), !dbg !331
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !332, metadata !242), !dbg !333
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !334, metadata !242), !dbg !335
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !336
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !337
  %1 = load i8*, i8** %format_data, align 8, !dbg !337
  %2 = bitcast i8* %1 to %struct.shar*, !dbg !338
  store %struct.shar* %2, %struct.shar** %shar, align 8, !dbg !339
  %3 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !340
  %wrote_header = getelementptr inbounds %struct.shar, %struct.shar* %3, i32 0, i32 7, !dbg !342
  %4 = load i32, i32* %wrote_header, align 8, !dbg !342
  %tobool = icmp ne i32 %4, 0, !dbg !340
  br i1 %tobool, label %if.end, label %if.then, !dbg !343

if.then:                                          ; preds = %entry
  %5 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !344
  %work = getelementptr inbounds %struct.shar, %struct.shar* %5, i32 0, i32 8, !dbg !346
  %call = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.4, i32 0, i32 0)), !dbg !347
  %6 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !348
  %work2 = getelementptr inbounds %struct.shar, %struct.shar* %6, i32 0, i32 8, !dbg !349
  %call3 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work2, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.5, i32 0, i32 0)), !dbg !350
  %7 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !351
  %wrote_header4 = getelementptr inbounds %struct.shar, %struct.shar* %7, i32 0, i32 7, !dbg !352
  store i32 1, i32* %wrote_header4, align 8, !dbg !353
  br label %if.end, !dbg !354

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !355
  %entry5 = getelementptr inbounds %struct.shar, %struct.shar* %8, i32 0, i32 2, !dbg !357
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry5, align 8, !dbg !357
  %tobool6 = icmp ne %struct.archive_entry* %9, null, !dbg !355
  br i1 %tobool6, label %if.then7, label %if.end9, !dbg !358

if.then7:                                         ; preds = %if.end
  %10 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !359
  %entry8 = getelementptr inbounds %struct.shar, %struct.shar* %10, i32 0, i32 2, !dbg !360
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry8, align 8, !dbg !360
  call void @archive_entry_free(%struct.archive_entry* %11), !dbg !361
  br label %if.end9, !dbg !361

if.end9:                                          ; preds = %if.then7, %if.end
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !362
  %call10 = call %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %12), !dbg !363
  %13 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !364
  %entry11 = getelementptr inbounds %struct.shar, %struct.shar* %13, i32 0, i32 2, !dbg !365
  store %struct.archive_entry* %call10, %struct.archive_entry** %entry11, align 8, !dbg !366
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !367
  %call12 = call i8* @archive_entry_pathname(%struct.archive_entry* %14), !dbg !368
  store i8* %call12, i8** %name, align 8, !dbg !369
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !370
  %call13 = call i32 @archive_entry_filetype(%struct.archive_entry* %15), !dbg !371
  switch i32 %call13, label %sw.default [
    i32 32768, label %sw.bb
    i32 16384, label %sw.bb14
    i32 4096, label %sw.bb20
    i32 8192, label %sw.bb20
    i32 24576, label %sw.bb20
  ], !dbg !372

sw.bb:                                            ; preds = %if.end9
  br label %sw.epilog, !dbg !373

sw.bb14:                                          ; preds = %if.end9
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !375
  call void @archive_entry_set_size(%struct.archive_entry* %16, i64 0), !dbg !376
  %17 = load i8*, i8** %name, align 8, !dbg !377
  %call15 = call i32 @strcmp(i8* %17, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0)) #7, !dbg !379
  %cmp = icmp eq i32 %call15, 0, !dbg !380
  br i1 %cmp, label %if.then18, label %lor.lhs.false, !dbg !381

lor.lhs.false:                                    ; preds = %sw.bb14
  %18 = load i8*, i8** %name, align 8, !dbg !382
  %call16 = call i32 @strcmp(i8* %18, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.7, i32 0, i32 0)) #7, !dbg !384
  %cmp17 = icmp eq i32 %call16, 0, !dbg !385
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !386

if.then18:                                        ; preds = %lor.lhs.false, %sw.bb14
  store i32 0, i32* %retval, align 4, !dbg !387
  br label %return, !dbg !387

if.end19:                                         ; preds = %lor.lhs.false
  br label %sw.epilog, !dbg !388

sw.bb20:                                          ; preds = %if.end9, %if.end9, %if.end9
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !389
  call void @archive_entry_set_size(%struct.archive_entry* %19, i64 0), !dbg !390
  br label %sw.epilog, !dbg !391

sw.default:                                       ; preds = %if.end9
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !392
  call void @archive_entry_set_size(%struct.archive_entry* %20, i64 0), !dbg !393
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !394
  %call21 = call i8* @archive_entry_hardlink(%struct.archive_entry* %21), !dbg !396
  %cmp22 = icmp eq i8* %call21, null, !dbg !397
  br i1 %cmp22, label %land.lhs.true, label %if.end26, !dbg !398

land.lhs.true:                                    ; preds = %sw.default
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !399
  %call23 = call i8* @archive_entry_symlink(%struct.archive_entry* %22), !dbg !400
  %cmp24 = icmp eq i8* %call23, null, !dbg !401
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !402

if.then25:                                        ; preds = %land.lhs.true
  %23 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !404
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !406
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.8, i32 0, i32 0)), !dbg !407
  store i32 -20, i32* %retval, align 4, !dbg !408
  br label %return, !dbg !408

if.end26:                                         ; preds = %land.lhs.true, %sw.default
  br label %sw.epilog, !dbg !409

sw.epilog:                                        ; preds = %if.end26, %sw.bb20, %if.end19, %sw.bb
  %24 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !410
  %quoted_name = getelementptr inbounds %struct.shar, %struct.shar* %24, i32 0, i32 9, !dbg !410
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name, i32 0, i32 1, !dbg !410
  store i64 0, i64* %length, align 8, !dbg !410
  %25 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !411
  %quoted_name27 = getelementptr inbounds %struct.shar, %struct.shar* %25, i32 0, i32 9, !dbg !412
  %26 = load i8*, i8** %name, align 8, !dbg !413
  call void @shar_quote(%struct.archive_string* %quoted_name27, i8* %26, i32 1), !dbg !414
  %27 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !415
  %work28 = getelementptr inbounds %struct.shar, %struct.shar* %27, i32 0, i32 8, !dbg !416
  %28 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !417
  %quoted_name29 = getelementptr inbounds %struct.shar, %struct.shar* %28, i32 0, i32 9, !dbg !418
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name29, i32 0, i32 0, !dbg !419
  %29 = load i8*, i8** %s, align 8, !dbg !419
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work28, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i32 0, i32 0), i8* %29), !dbg !420
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !421
  %call30 = call i32 @archive_entry_filetype(%struct.archive_entry* %30), !dbg !423
  %cmp31 = icmp ne i32 %call30, 16384, !dbg !424
  br i1 %cmp31, label %if.then32, label %if.end77, !dbg !425

if.then32:                                        ; preds = %sw.epilog
  %31 = load i8*, i8** %name, align 8, !dbg !426
  %call33 = call noalias i8* @strdup(i8* %31) #6, !dbg !428
  store i8* %call33, i8** %p, align 8, !dbg !429
  %32 = load i8*, i8** %p, align 8, !dbg !430
  %call34 = call i8* @strrchr(i8* %32, i32 47) #7, !dbg !431
  store i8* %call34, i8** %pp, align 8, !dbg !432
  %33 = load i8*, i8** %pp, align 8, !dbg !433
  %cmp35 = icmp ne i8* %33, null, !dbg !435
  br i1 %cmp35, label %if.then36, label %if.else75, !dbg !436

if.then36:                                        ; preds = %if.then32
  %34 = load i8*, i8** %pp, align 8, !dbg !437
  store i8 0, i8* %34, align 1, !dbg !439
  %35 = load i8*, i8** %p, align 8, !dbg !440
  %call37 = call i32 @strcmp(i8* %35, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0)) #7, !dbg !442
  %cmp38 = icmp eq i32 %call37, 0, !dbg !443
  br i1 %cmp38, label %if.then39, label %if.else, !dbg !444

if.then39:                                        ; preds = %if.then36
  %36 = load i8*, i8** %p, align 8, !dbg !445
  call void @free(i8* %36) #6, !dbg !447
  br label %if.end74, !dbg !448

if.else:                                          ; preds = %if.then36
  %37 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !449
  %last_dir = getelementptr inbounds %struct.shar, %struct.shar* %37, i32 0, i32 4, !dbg !452
  %38 = load i8*, i8** %last_dir, align 8, !dbg !452
  %cmp40 = icmp eq i8* %38, null, !dbg !453
  br i1 %cmp40, label %if.then41, label %if.else48, !dbg !449

if.then41:                                        ; preds = %if.else
  %39 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !454
  %work42 = getelementptr inbounds %struct.shar, %struct.shar* %39, i32 0, i32 8, !dbg !456
  %call43 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work42, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0)), !dbg !457
  %40 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !458
  %work44 = getelementptr inbounds %struct.shar, %struct.shar* %40, i32 0, i32 8, !dbg !459
  %41 = load i8*, i8** %p, align 8, !dbg !460
  call void @shar_quote(%struct.archive_string* %work44, i8* %41, i32 1), !dbg !461
  %42 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !462
  %work45 = getelementptr inbounds %struct.shar, %struct.shar* %42, i32 0, i32 8, !dbg !463
  %call46 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work45, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.11, i32 0, i32 0)), !dbg !464
  %43 = load i8*, i8** %p, align 8, !dbg !465
  %44 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !466
  %last_dir47 = getelementptr inbounds %struct.shar, %struct.shar* %44, i32 0, i32 4, !dbg !467
  store i8* %43, i8** %last_dir47, align 8, !dbg !468
  br label %if.end73, !dbg !469

if.else48:                                        ; preds = %if.else
  %45 = load i8*, i8** %p, align 8, !dbg !470
  %46 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !473
  %last_dir49 = getelementptr inbounds %struct.shar, %struct.shar* %46, i32 0, i32 4, !dbg !474
  %47 = load i8*, i8** %last_dir49, align 8, !dbg !474
  %call50 = call i32 @strcmp(i8* %45, i8* %47) #7, !dbg !475
  %cmp51 = icmp eq i32 %call50, 0, !dbg !476
  br i1 %cmp51, label %if.then52, label %if.else53, !dbg !475

if.then52:                                        ; preds = %if.else48
  %48 = load i8*, i8** %p, align 8, !dbg !477
  call void @free(i8* %48) #6, !dbg !479
  br label %if.end72, !dbg !480

if.else53:                                        ; preds = %if.else48
  %49 = load i8*, i8** %p, align 8, !dbg !481
  %call54 = call i64 @strlen(i8* %49) #7, !dbg !484
  %50 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !485
  %last_dir55 = getelementptr inbounds %struct.shar, %struct.shar* %50, i32 0, i32 4, !dbg !486
  %51 = load i8*, i8** %last_dir55, align 8, !dbg !486
  %call56 = call i64 @strlen(i8* %51) #7, !dbg !487
  %cmp57 = icmp ult i64 %call54, %call56, !dbg !489
  br i1 %cmp57, label %land.lhs.true58, label %if.else64, !dbg !490

land.lhs.true58:                                  ; preds = %if.else53
  %52 = load i8*, i8** %p, align 8, !dbg !491
  %53 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !492
  %last_dir59 = getelementptr inbounds %struct.shar, %struct.shar* %53, i32 0, i32 4, !dbg !493
  %54 = load i8*, i8** %last_dir59, align 8, !dbg !493
  %55 = load i8*, i8** %p, align 8, !dbg !494
  %call60 = call i64 @strlen(i8* %55) #7, !dbg !495
  %call61 = call i32 @strncmp(i8* %52, i8* %54, i64 %call60) #7, !dbg !496
  %cmp62 = icmp eq i32 %call61, 0, !dbg !497
  br i1 %cmp62, label %if.then63, label %if.else64, !dbg !498

if.then63:                                        ; preds = %land.lhs.true58
  %56 = load i8*, i8** %p, align 8, !dbg !500
  call void @free(i8* %56) #6, !dbg !502
  br label %if.end71, !dbg !503

if.else64:                                        ; preds = %land.lhs.true58, %if.else53
  %57 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !504
  %work65 = getelementptr inbounds %struct.shar, %struct.shar* %57, i32 0, i32 8, !dbg !506
  %call66 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work65, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0)), !dbg !507
  %58 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !508
  %work67 = getelementptr inbounds %struct.shar, %struct.shar* %58, i32 0, i32 8, !dbg !509
  %59 = load i8*, i8** %p, align 8, !dbg !510
  call void @shar_quote(%struct.archive_string* %work67, i8* %59, i32 1), !dbg !511
  %60 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !512
  %work68 = getelementptr inbounds %struct.shar, %struct.shar* %60, i32 0, i32 8, !dbg !513
  %call69 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work68, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.11, i32 0, i32 0)), !dbg !514
  %61 = load i8*, i8** %p, align 8, !dbg !515
  %62 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !516
  %last_dir70 = getelementptr inbounds %struct.shar, %struct.shar* %62, i32 0, i32 4, !dbg !517
  store i8* %61, i8** %last_dir70, align 8, !dbg !518
  br label %if.end71

if.end71:                                         ; preds = %if.else64, %if.then63
  br label %if.end72

if.end72:                                         ; preds = %if.end71, %if.then52
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.then41
  br label %if.end74

if.end74:                                         ; preds = %if.end73, %if.then39
  br label %if.end76, !dbg !519

if.else75:                                        ; preds = %if.then32
  %63 = load i8*, i8** %p, align 8, !dbg !520
  call void @free(i8* %63) #6, !dbg !522
  br label %if.end76

if.end76:                                         ; preds = %if.else75, %if.end74
  br label %if.end77, !dbg !523

if.end77:                                         ; preds = %if.end76, %sw.epilog
  %64 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !524
  %has_data = getelementptr inbounds %struct.shar, %struct.shar* %64, i32 0, i32 3, !dbg !525
  store i32 0, i32* %has_data, align 8, !dbg !526
  %65 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !527
  %call78 = call i8* @archive_entry_hardlink(%struct.archive_entry* %65), !dbg !529
  store i8* %call78, i8** %linkname, align 8, !dbg !530
  %cmp79 = icmp ne i8* %call78, null, !dbg !531
  br i1 %cmp79, label %if.then80, label %if.else87, !dbg !532

if.then80:                                        ; preds = %if.end77
  %66 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !533
  %work81 = getelementptr inbounds %struct.shar, %struct.shar* %66, i32 0, i32 8, !dbg !535
  %call82 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work81, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.12, i32 0, i32 0)), !dbg !536
  %67 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !537
  %work83 = getelementptr inbounds %struct.shar, %struct.shar* %67, i32 0, i32 8, !dbg !538
  %68 = load i8*, i8** %linkname, align 8, !dbg !539
  call void @shar_quote(%struct.archive_string* %work83, i8* %68, i32 1), !dbg !540
  %69 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !541
  %work84 = getelementptr inbounds %struct.shar, %struct.shar* %69, i32 0, i32 8, !dbg !542
  %70 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !543
  %quoted_name85 = getelementptr inbounds %struct.shar, %struct.shar* %70, i32 0, i32 9, !dbg !544
  %s86 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name85, i32 0, i32 0, !dbg !545
  %71 = load i8*, i8** %s86, align 8, !dbg !545
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work84, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i8* %71), !dbg !546
  br label %if.end164, !dbg !547

if.else87:                                        ; preds = %if.end77
  %72 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !548
  %call88 = call i8* @archive_entry_symlink(%struct.archive_entry* %72), !dbg !551
  store i8* %call88, i8** %linkname, align 8, !dbg !552
  %cmp89 = icmp ne i8* %call88, null, !dbg !553
  br i1 %cmp89, label %if.then90, label %if.else97, !dbg !554

if.then90:                                        ; preds = %if.else87
  %73 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !555
  %work91 = getelementptr inbounds %struct.shar, %struct.shar* %73, i32 0, i32 8, !dbg !557
  %call92 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work91, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.14, i32 0, i32 0)), !dbg !558
  %74 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !559
  %work93 = getelementptr inbounds %struct.shar, %struct.shar* %74, i32 0, i32 8, !dbg !560
  %75 = load i8*, i8** %linkname, align 8, !dbg !561
  call void @shar_quote(%struct.archive_string* %work93, i8* %75, i32 1), !dbg !562
  %76 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !563
  %work94 = getelementptr inbounds %struct.shar, %struct.shar* %76, i32 0, i32 8, !dbg !564
  %77 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !565
  %quoted_name95 = getelementptr inbounds %struct.shar, %struct.shar* %77, i32 0, i32 9, !dbg !566
  %s96 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name95, i32 0, i32 0, !dbg !567
  %78 = load i8*, i8** %s96, align 8, !dbg !567
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work94, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i8* %78), !dbg !568
  br label %if.end163, !dbg !569

if.else97:                                        ; preds = %if.else87
  %79 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !570
  %call98 = call i32 @archive_entry_filetype(%struct.archive_entry* %79), !dbg !572
  switch i32 %call98, label %sw.default161 [
    i32 32768, label %sw.bb99
    i32 16384, label %sw.bb126
    i32 4096, label %sw.bb145
    i32 8192, label %sw.bb149
    i32 24576, label %sw.bb155
  ], !dbg !573

sw.bb99:                                          ; preds = %if.else97
  %80 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !574
  %call100 = call i64 @archive_entry_size(%struct.archive_entry* %80), !dbg !577
  %cmp101 = icmp eq i64 %call100, 0, !dbg !578
  br i1 %cmp101, label %if.then102, label %if.else108, !dbg !579

if.then102:                                       ; preds = %sw.bb99
  %81 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !580
  %work103 = getelementptr inbounds %struct.shar, %struct.shar* %81, i32 0, i32 8, !dbg !582
  %82 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !583
  %quoted_name104 = getelementptr inbounds %struct.shar, %struct.shar* %82, i32 0, i32 9, !dbg !584
  %s105 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name104, i32 0, i32 0, !dbg !585
  %83 = load i8*, i8** %s105, align 8, !dbg !585
  %84 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !586
  %quoted_name106 = getelementptr inbounds %struct.shar, %struct.shar* %84, i32 0, i32 9, !dbg !587
  %s107 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name106, i32 0, i32 0, !dbg !588
  %85 = load i8*, i8** %s107, align 8, !dbg !588
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work103, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.15, i32 0, i32 0), i8* %83, i8* %85), !dbg !589
  br label %if.end125, !dbg !590

if.else108:                                       ; preds = %sw.bb99
  %86 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !591
  %dump = getelementptr inbounds %struct.shar, %struct.shar* %86, i32 0, i32 0, !dbg !594
  %87 = load i32, i32* %dump, align 8, !dbg !594
  %tobool109 = icmp ne i32 %87, 0, !dbg !591
  br i1 %tobool109, label %if.then110, label %if.else119, !dbg !595

if.then110:                                       ; preds = %if.else108
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !596, metadata !242), !dbg !598
  %88 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !599
  %call111 = call i32 @archive_entry_mode(%struct.archive_entry* %88), !dbg !600
  %and = and i32 %call111, 511, !dbg !601
  store i32 %and, i32* %mode, align 4, !dbg !598
  %89 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !602
  %work112 = getelementptr inbounds %struct.shar, %struct.shar* %89, i32 0, i32 8, !dbg !603
  %90 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !604
  %quoted_name113 = getelementptr inbounds %struct.shar, %struct.shar* %90, i32 0, i32 9, !dbg !605
  %s114 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name113, i32 0, i32 0, !dbg !606
  %91 = load i8*, i8** %s114, align 8, !dbg !606
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work112, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.16, i32 0, i32 0), i8* %91), !dbg !607
  %92 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !608
  %work115 = getelementptr inbounds %struct.shar, %struct.shar* %92, i32 0, i32 8, !dbg !609
  %93 = load i32, i32* %mode, align 4, !dbg !610
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work115, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.17, i32 0, i32 0), i32 %93), !dbg !611
  %94 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !612
  %work116 = getelementptr inbounds %struct.shar, %struct.shar* %94, i32 0, i32 8, !dbg !613
  %95 = load i8*, i8** %name, align 8, !dbg !614
  call void @shar_quote(%struct.archive_string* %work116, i8* %95, i32 0), !dbg !615
  %96 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !616
  %work117 = getelementptr inbounds %struct.shar, %struct.shar* %96, i32 0, i32 8, !dbg !617
  %call118 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work117, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0)), !dbg !618
  br label %if.end123, !dbg !619

if.else119:                                       ; preds = %if.else108
  %97 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !620
  %work120 = getelementptr inbounds %struct.shar, %struct.shar* %97, i32 0, i32 8, !dbg !622
  %98 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !623
  %quoted_name121 = getelementptr inbounds %struct.shar, %struct.shar* %98, i32 0, i32 9, !dbg !624
  %s122 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name121, i32 0, i32 0, !dbg !625
  %99 = load i8*, i8** %s122, align 8, !dbg !625
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work120, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.19, i32 0, i32 0), i8* %99), !dbg !626
  br label %if.end123

if.end123:                                        ; preds = %if.else119, %if.then110
  %100 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !627
  %has_data124 = getelementptr inbounds %struct.shar, %struct.shar* %100, i32 0, i32 3, !dbg !628
  store i32 1, i32* %has_data124, align 8, !dbg !629
  %101 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !630
  %end_of_line = getelementptr inbounds %struct.shar, %struct.shar* %101, i32 0, i32 1, !dbg !631
  store i32 1, i32* %end_of_line, align 4, !dbg !632
  %102 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !633
  %outpos = getelementptr inbounds %struct.shar, %struct.shar* %102, i32 0, i32 6, !dbg !634
  store i64 0, i64* %outpos, align 8, !dbg !635
  br label %if.end125

if.end125:                                        ; preds = %if.end123, %if.then102
  br label %sw.epilog162, !dbg !636

sw.bb126:                                         ; preds = %if.else97
  %103 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !637
  %work127 = getelementptr inbounds %struct.shar, %struct.shar* %103, i32 0, i32 8, !dbg !638
  %104 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !639
  %quoted_name128 = getelementptr inbounds %struct.shar, %struct.shar* %104, i32 0, i32 9, !dbg !640
  %s129 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name128, i32 0, i32 0, !dbg !641
  %105 = load i8*, i8** %s129, align 8, !dbg !641
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work127, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.20, i32 0, i32 0), i8* %105), !dbg !642
  %106 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !643
  %last_dir130 = getelementptr inbounds %struct.shar, %struct.shar* %106, i32 0, i32 4, !dbg !645
  %107 = load i8*, i8** %last_dir130, align 8, !dbg !645
  %cmp131 = icmp ne i8* %107, null, !dbg !646
  br i1 %cmp131, label %if.then132, label %if.end134, !dbg !647

if.then132:                                       ; preds = %sw.bb126
  %108 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !648
  %last_dir133 = getelementptr inbounds %struct.shar, %struct.shar* %108, i32 0, i32 4, !dbg !649
  %109 = load i8*, i8** %last_dir133, align 8, !dbg !649
  call void @free(i8* %109) #6, !dbg !650
  br label %if.end134, !dbg !650

if.end134:                                        ; preds = %if.then132, %sw.bb126
  %110 = load i8*, i8** %name, align 8, !dbg !651
  %call135 = call noalias i8* @strdup(i8* %110) #6, !dbg !652
  %111 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !653
  %last_dir136 = getelementptr inbounds %struct.shar, %struct.shar* %111, i32 0, i32 4, !dbg !654
  store i8* %call135, i8** %last_dir136, align 8, !dbg !655
  %112 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !656
  %last_dir137 = getelementptr inbounds %struct.shar, %struct.shar* %112, i32 0, i32 4, !dbg !657
  %113 = load i8*, i8** %last_dir137, align 8, !dbg !657
  %call138 = call i8* @strrchr(i8* %113, i32 47) #7, !dbg !658
  store i8* %call138, i8** %pp, align 8, !dbg !659
  %114 = load i8*, i8** %pp, align 8, !dbg !660
  %cmp139 = icmp ne i8* %114, null, !dbg !662
  br i1 %cmp139, label %land.lhs.true140, label %if.end144, !dbg !663

land.lhs.true140:                                 ; preds = %if.end134
  %115 = load i8*, i8** %pp, align 8, !dbg !664
  %arrayidx = getelementptr inbounds i8, i8* %115, i64 1, !dbg !664
  %116 = load i8, i8* %arrayidx, align 1, !dbg !664
  %conv = sext i8 %116 to i32, !dbg !664
  %cmp141 = icmp eq i32 %conv, 0, !dbg !666
  br i1 %cmp141, label %if.then143, label %if.end144, !dbg !667

if.then143:                                       ; preds = %land.lhs.true140
  %117 = load i8*, i8** %pp, align 8, !dbg !668
  store i8 0, i8* %117, align 1, !dbg !669
  br label %if.end144, !dbg !670

if.end144:                                        ; preds = %if.then143, %land.lhs.true140, %if.end134
  br label %sw.epilog162, !dbg !671

sw.bb145:                                         ; preds = %if.else97
  %118 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !672
  %work146 = getelementptr inbounds %struct.shar, %struct.shar* %118, i32 0, i32 8, !dbg !673
  %119 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !674
  %quoted_name147 = getelementptr inbounds %struct.shar, %struct.shar* %119, i32 0, i32 9, !dbg !675
  %s148 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name147, i32 0, i32 0, !dbg !676
  %120 = load i8*, i8** %s148, align 8, !dbg !676
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work146, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.21, i32 0, i32 0), i8* %120), !dbg !677
  br label %sw.epilog162, !dbg !678

sw.bb149:                                         ; preds = %if.else97
  %121 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !679
  %work150 = getelementptr inbounds %struct.shar, %struct.shar* %121, i32 0, i32 8, !dbg !680
  %122 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !681
  %quoted_name151 = getelementptr inbounds %struct.shar, %struct.shar* %122, i32 0, i32 9, !dbg !682
  %s152 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name151, i32 0, i32 0, !dbg !683
  %123 = load i8*, i8** %s152, align 8, !dbg !683
  %124 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !684
  %call153 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %124), !dbg !685
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !686
  %call154 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %125), !dbg !687
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work150, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.22, i32 0, i32 0), i8* %123, i64 %call153, i64 %call154), !dbg !688
  br label %sw.epilog162, !dbg !689

sw.bb155:                                         ; preds = %if.else97
  %126 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !690
  %work156 = getelementptr inbounds %struct.shar, %struct.shar* %126, i32 0, i32 8, !dbg !691
  %127 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !692
  %quoted_name157 = getelementptr inbounds %struct.shar, %struct.shar* %127, i32 0, i32 9, !dbg !693
  %s158 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %quoted_name157, i32 0, i32 0, !dbg !694
  %128 = load i8*, i8** %s158, align 8, !dbg !694
  %129 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !695
  %call159 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %129), !dbg !696
  %130 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !697
  %call160 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %130), !dbg !698
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work156, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.23, i32 0, i32 0), i8* %128, i64 %call159, i64 %call160), !dbg !699
  br label %sw.epilog162, !dbg !700

sw.default161:                                    ; preds = %if.else97
  store i32 -20, i32* %retval, align 4, !dbg !701
  br label %return, !dbg !701

sw.epilog162:                                     ; preds = %sw.bb155, %sw.bb149, %sw.bb145, %if.end144, %if.end125
  br label %if.end163

if.end163:                                        ; preds = %sw.epilog162, %if.then90
  br label %if.end164

if.end164:                                        ; preds = %if.end163, %if.then80
  store i32 0, i32* %retval, align 4, !dbg !702
  br label %return, !dbg !702

return:                                           ; preds = %if.end164, %sw.default161, %if.then25, %if.then18
  %131 = load i32, i32* %retval, align 4, !dbg !703
  ret i32 %131, !dbg !703
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_shar_close(%struct.archive_write* %a) #0 !dbg !229 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %shar = alloca %struct.shar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !704, metadata !242), !dbg !705
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !706, metadata !242), !dbg !707
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !708, metadata !242), !dbg !709
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !710
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !711
  %1 = load i8*, i8** %format_data, align 8, !dbg !711
  %2 = bitcast i8* %1 to %struct.shar*, !dbg !712
  store %struct.shar* %2, %struct.shar** %shar, align 8, !dbg !713
  %3 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !714
  %wrote_header = getelementptr inbounds %struct.shar, %struct.shar* %3, i32 0, i32 7, !dbg !716
  %4 = load i32, i32* %wrote_header, align 8, !dbg !716
  %cmp = icmp eq i32 %4, 0, !dbg !717
  br i1 %cmp, label %if.then, label %if.end, !dbg !718

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !719
  br label %return, !dbg !719

if.end:                                           ; preds = %entry
  %5 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !720
  %work = getelementptr inbounds %struct.shar, %struct.shar* %5, i32 0, i32 8, !dbg !721
  %call = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.35, i32 0, i32 0)), !dbg !722
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !723
  %7 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !724
  %work1 = getelementptr inbounds %struct.shar, %struct.shar* %7, i32 0, i32 8, !dbg !725
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work1, i32 0, i32 0, !dbg !726
  %8 = load i8*, i8** %s, align 8, !dbg !726
  %9 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !727
  %work2 = getelementptr inbounds %struct.shar, %struct.shar* %9, i32 0, i32 8, !dbg !728
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work2, i32 0, i32 1, !dbg !729
  %10 = load i64, i64* %length, align 8, !dbg !729
  %call3 = call i32 @__archive_write_output(%struct.archive_write* %6, i8* %8, i64 %10), !dbg !730
  store i32 %call3, i32* %ret, align 4, !dbg !731
  %11 = load i32, i32* %ret, align 4, !dbg !732
  %cmp4 = icmp ne i32 %11, 0, !dbg !734
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !735

if.then5:                                         ; preds = %if.end
  store i32 -30, i32* %retval, align 4, !dbg !736
  br label %return, !dbg !736

if.end6:                                          ; preds = %if.end
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !737
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 0, !dbg !738
  %call7 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %archive, i32 1), !dbg !739
  store i32 0, i32* %retval, align 4, !dbg !740
  br label %return, !dbg !740

return:                                           ; preds = %if.end6, %if.then5, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !741
  ret i32 %13, !dbg !741
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_shar_free(%struct.archive_write* %a) #0 !dbg !230 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %shar = alloca %struct.shar*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !742, metadata !242), !dbg !743
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !744, metadata !242), !dbg !745
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !746
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !747
  %1 = load i8*, i8** %format_data, align 8, !dbg !747
  %2 = bitcast i8* %1 to %struct.shar*, !dbg !748
  store %struct.shar* %2, %struct.shar** %shar, align 8, !dbg !749
  %3 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !750
  %cmp = icmp eq %struct.shar* %3, null, !dbg !752
  br i1 %cmp, label %if.then, label %if.end, !dbg !753

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !754
  br label %return, !dbg !754

if.end:                                           ; preds = %entry
  %4 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !755
  %entry1 = getelementptr inbounds %struct.shar, %struct.shar* %4, i32 0, i32 2, !dbg !756
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !756
  call void @archive_entry_free(%struct.archive_entry* %5), !dbg !757
  %6 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !758
  %last_dir = getelementptr inbounds %struct.shar, %struct.shar* %6, i32 0, i32 4, !dbg !759
  %7 = load i8*, i8** %last_dir, align 8, !dbg !759
  call void @free(i8* %7) #6, !dbg !760
  %8 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !761
  %work = getelementptr inbounds %struct.shar, %struct.shar* %8, i32 0, i32 8, !dbg !762
  call void @archive_string_free(%struct.archive_string* %work), !dbg !763
  %9 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !764
  %quoted_name = getelementptr inbounds %struct.shar, %struct.shar* %9, i32 0, i32 9, !dbg !765
  call void @archive_string_free(%struct.archive_string* %quoted_name), !dbg !766
  %10 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !767
  %11 = bitcast %struct.shar* %10 to i8*, !dbg !767
  call void @free(i8* %11) #6, !dbg !768
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !769
  %format_data2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 14, !dbg !770
  store i8* null, i8** %format_data2, align 8, !dbg !771
  store i32 0, i32* %retval, align 4, !dbg !772
  br label %return, !dbg !772

return:                                           ; preds = %if.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !773
  ret i32 %13, !dbg !773
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_shar_data_sed(%struct.archive_write* %a, i8* %buff, i64 %n) #0 !dbg !220 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %shar = alloca %struct.shar*, align 8
  %src = alloca i8*, align 8
  %buf = alloca i8*, align 8
  %buf_end = alloca i8*, align 8
  %ret = alloca i32, align 4
  %written = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !774, metadata !242), !dbg !775
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !776, metadata !242), !dbg !777
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !778, metadata !242), !dbg !779
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !780, metadata !242), !dbg !781
  call void @llvm.dbg.declare(metadata i8** %src, metadata !782, metadata !242), !dbg !783
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !784, metadata !242), !dbg !785
  call void @llvm.dbg.declare(metadata i8** %buf_end, metadata !786, metadata !242), !dbg !787
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !788, metadata !242), !dbg !789
  call void @llvm.dbg.declare(metadata i64* %written, metadata !790, metadata !242), !dbg !791
  %0 = load i64, i64* %n.addr, align 8, !dbg !792
  store i64 %0, i64* %written, align 8, !dbg !791
  %1 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !793
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %1, i32 0, i32 14, !dbg !794
  %2 = load i8*, i8** %format_data, align 8, !dbg !794
  %3 = bitcast i8* %2 to %struct.shar*, !dbg !795
  store %struct.shar* %3, %struct.shar** %shar, align 8, !dbg !796
  %4 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !797
  %has_data = getelementptr inbounds %struct.shar, %struct.shar* %4, i32 0, i32 3, !dbg !799
  %5 = load i32, i32* %has_data, align 8, !dbg !799
  %tobool = icmp ne i32 %5, 0, !dbg !797
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !800

lor.lhs.false:                                    ; preds = %entry
  %6 = load i64, i64* %n.addr, align 8, !dbg !801
  %cmp = icmp eq i64 %6, 0, !dbg !803
  br i1 %cmp, label %if.then, label %if.end, !dbg !804

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i64 0, i64* %retval, align 8, !dbg !805
  br label %return, !dbg !805

if.end:                                           ; preds = %lor.lhs.false
  %7 = load i8*, i8** %buff.addr, align 8, !dbg !806
  store i8* %7, i8** %src, align 8, !dbg !807
  %8 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !808
  %work = getelementptr inbounds %struct.shar, %struct.shar* %8, i32 0, i32 8, !dbg !810
  %call = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %work, i64 65536), !dbg !811
  %cmp1 = icmp eq %struct.archive_string* %call, null, !dbg !812
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !813

if.then2:                                         ; preds = %if.end
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !814
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !816
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.26, i32 0, i32 0)), !dbg !817
  store i64 -30, i64* %retval, align 8, !dbg !818
  br label %return, !dbg !818

if.end3:                                          ; preds = %if.end
  %10 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !819
  %work4 = getelementptr inbounds %struct.shar, %struct.shar* %10, i32 0, i32 8, !dbg !821
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work4, i32 0, i32 1, !dbg !822
  %11 = load i64, i64* %length, align 8, !dbg !822
  %cmp5 = icmp ugt i64 %11, 65533, !dbg !823
  br i1 %cmp5, label %if.then6, label %if.end16, !dbg !824

if.then6:                                         ; preds = %if.end3
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !825
  %13 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !827
  %work7 = getelementptr inbounds %struct.shar, %struct.shar* %13, i32 0, i32 8, !dbg !828
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work7, i32 0, i32 0, !dbg !829
  %14 = load i8*, i8** %s, align 8, !dbg !829
  %15 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !830
  %work8 = getelementptr inbounds %struct.shar, %struct.shar* %15, i32 0, i32 8, !dbg !831
  %length9 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work8, i32 0, i32 1, !dbg !832
  %16 = load i64, i64* %length9, align 8, !dbg !832
  %call10 = call i32 @__archive_write_output(%struct.archive_write* %12, i8* %14, i64 %16), !dbg !833
  store i32 %call10, i32* %ret, align 4, !dbg !834
  %17 = load i32, i32* %ret, align 4, !dbg !835
  %cmp11 = icmp ne i32 %17, 0, !dbg !837
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !838

if.then12:                                        ; preds = %if.then6
  store i64 -30, i64* %retval, align 8, !dbg !839
  br label %return, !dbg !839

if.end13:                                         ; preds = %if.then6
  %18 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !840
  %work14 = getelementptr inbounds %struct.shar, %struct.shar* %18, i32 0, i32 8, !dbg !840
  %length15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work14, i32 0, i32 1, !dbg !840
  store i64 0, i64* %length15, align 8, !dbg !840
  br label %if.end16, !dbg !841

if.end16:                                         ; preds = %if.end13, %if.end3
  %19 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !842
  %work17 = getelementptr inbounds %struct.shar, %struct.shar* %19, i32 0, i32 8, !dbg !843
  %s18 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work17, i32 0, i32 0, !dbg !844
  %20 = load i8*, i8** %s18, align 8, !dbg !844
  %21 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !845
  %work19 = getelementptr inbounds %struct.shar, %struct.shar* %21, i32 0, i32 8, !dbg !846
  %length20 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work19, i32 0, i32 1, !dbg !847
  %22 = load i64, i64* %length20, align 8, !dbg !847
  %add.ptr = getelementptr inbounds i8, i8* %20, i64 %22, !dbg !848
  store i8* %add.ptr, i8** %buf, align 8, !dbg !849
  %23 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !850
  %work21 = getelementptr inbounds %struct.shar, %struct.shar* %23, i32 0, i32 8, !dbg !851
  %s22 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work21, i32 0, i32 0, !dbg !852
  %24 = load i8*, i8** %s22, align 8, !dbg !852
  %add.ptr23 = getelementptr inbounds i8, i8* %24, i64 65533, !dbg !853
  store i8* %add.ptr23, i8** %buf_end, align 8, !dbg !854
  %25 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !855
  %end_of_line = getelementptr inbounds %struct.shar, %struct.shar* %25, i32 0, i32 1, !dbg !857
  %26 = load i32, i32* %end_of_line, align 4, !dbg !857
  %tobool24 = icmp ne i32 %26, 0, !dbg !855
  br i1 %tobool24, label %if.then25, label %if.end27, !dbg !858

if.then25:                                        ; preds = %if.end16
  %27 = load i8*, i8** %buf, align 8, !dbg !859
  %incdec.ptr = getelementptr inbounds i8, i8* %27, i32 1, !dbg !859
  store i8* %incdec.ptr, i8** %buf, align 8, !dbg !859
  store i8 88, i8* %27, align 1, !dbg !861
  %28 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !862
  %end_of_line26 = getelementptr inbounds %struct.shar, %struct.shar* %28, i32 0, i32 1, !dbg !863
  store i32 0, i32* %end_of_line26, align 4, !dbg !864
  br label %if.end27, !dbg !865

if.end27:                                         ; preds = %if.then25, %if.end16
  br label %while.cond, !dbg !866

while.cond:                                       ; preds = %if.end61, %if.end27
  %29 = load i64, i64* %n.addr, align 8, !dbg !867
  %dec = add i64 %29, -1, !dbg !867
  store i64 %dec, i64* %n.addr, align 8, !dbg !867
  %cmp28 = icmp ne i64 %29, 0, !dbg !869
  br i1 %cmp28, label %while.body, label %while.end, !dbg !870

while.body:                                       ; preds = %while.cond
  %30 = load i8*, i8** %src, align 8, !dbg !871
  %incdec.ptr29 = getelementptr inbounds i8, i8* %30, i32 1, !dbg !871
  store i8* %incdec.ptr29, i8** %src, align 8, !dbg !871
  %31 = load i8, i8* %30, align 1, !dbg !874
  %32 = load i8*, i8** %buf, align 8, !dbg !875
  %incdec.ptr30 = getelementptr inbounds i8, i8* %32, i32 1, !dbg !875
  store i8* %incdec.ptr30, i8** %buf, align 8, !dbg !875
  store i8 %31, i8* %32, align 1, !dbg !876
  %conv = sext i8 %31 to i32, !dbg !877
  %cmp31 = icmp eq i32 %conv, 10, !dbg !878
  br i1 %cmp31, label %if.then33, label %if.end40, !dbg !879

if.then33:                                        ; preds = %while.body
  %33 = load i64, i64* %n.addr, align 8, !dbg !880
  %cmp34 = icmp eq i64 %33, 0, !dbg !883
  br i1 %cmp34, label %if.then36, label %if.else, !dbg !884

if.then36:                                        ; preds = %if.then33
  %34 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !885
  %end_of_line37 = getelementptr inbounds %struct.shar, %struct.shar* %34, i32 0, i32 1, !dbg !886
  store i32 1, i32* %end_of_line37, align 4, !dbg !887
  br label %if.end39, !dbg !885

if.else:                                          ; preds = %if.then33
  %35 = load i8*, i8** %buf, align 8, !dbg !888
  %incdec.ptr38 = getelementptr inbounds i8, i8* %35, i32 1, !dbg !888
  store i8* %incdec.ptr38, i8** %buf, align 8, !dbg !888
  store i8 88, i8* %35, align 1, !dbg !889
  br label %if.end39

if.end39:                                         ; preds = %if.else, %if.then36
  br label %if.end40, !dbg !890

if.end40:                                         ; preds = %if.end39, %while.body
  %36 = load i8*, i8** %buf, align 8, !dbg !891
  %37 = load i8*, i8** %buf_end, align 8, !dbg !893
  %cmp41 = icmp uge i8* %36, %37, !dbg !894
  br i1 %cmp41, label %if.then43, label %if.end61, !dbg !895

if.then43:                                        ; preds = %if.end40
  %38 = load i8*, i8** %buf, align 8, !dbg !896
  %39 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !898
  %work44 = getelementptr inbounds %struct.shar, %struct.shar* %39, i32 0, i32 8, !dbg !899
  %s45 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work44, i32 0, i32 0, !dbg !900
  %40 = load i8*, i8** %s45, align 8, !dbg !900
  %sub.ptr.lhs.cast = ptrtoint i8* %38 to i64, !dbg !901
  %sub.ptr.rhs.cast = ptrtoint i8* %40 to i64, !dbg !901
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !901
  %41 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !902
  %work46 = getelementptr inbounds %struct.shar, %struct.shar* %41, i32 0, i32 8, !dbg !903
  %length47 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work46, i32 0, i32 1, !dbg !904
  store i64 %sub.ptr.sub, i64* %length47, align 8, !dbg !905
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !906
  %43 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !907
  %work48 = getelementptr inbounds %struct.shar, %struct.shar* %43, i32 0, i32 8, !dbg !908
  %s49 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work48, i32 0, i32 0, !dbg !909
  %44 = load i8*, i8** %s49, align 8, !dbg !909
  %45 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !910
  %work50 = getelementptr inbounds %struct.shar, %struct.shar* %45, i32 0, i32 8, !dbg !911
  %length51 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work50, i32 0, i32 1, !dbg !912
  %46 = load i64, i64* %length51, align 8, !dbg !912
  %call52 = call i32 @__archive_write_output(%struct.archive_write* %42, i8* %44, i64 %46), !dbg !913
  store i32 %call52, i32* %ret, align 4, !dbg !914
  %47 = load i32, i32* %ret, align 4, !dbg !915
  %cmp53 = icmp ne i32 %47, 0, !dbg !917
  br i1 %cmp53, label %if.then55, label %if.end56, !dbg !918

if.then55:                                        ; preds = %if.then43
  store i64 -30, i64* %retval, align 8, !dbg !919
  br label %return, !dbg !919

if.end56:                                         ; preds = %if.then43
  %48 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !920
  %work57 = getelementptr inbounds %struct.shar, %struct.shar* %48, i32 0, i32 8, !dbg !920
  %length58 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work57, i32 0, i32 1, !dbg !920
  store i64 0, i64* %length58, align 8, !dbg !920
  %49 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !921
  %work59 = getelementptr inbounds %struct.shar, %struct.shar* %49, i32 0, i32 8, !dbg !922
  %s60 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work59, i32 0, i32 0, !dbg !923
  %50 = load i8*, i8** %s60, align 8, !dbg !923
  store i8* %50, i8** %buf, align 8, !dbg !924
  br label %if.end61, !dbg !925

if.end61:                                         ; preds = %if.end56, %if.end40
  br label %while.cond, !dbg !926

while.end:                                        ; preds = %while.cond
  %51 = load i8*, i8** %buf, align 8, !dbg !928
  %52 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !929
  %work62 = getelementptr inbounds %struct.shar, %struct.shar* %52, i32 0, i32 8, !dbg !930
  %s63 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work62, i32 0, i32 0, !dbg !931
  %53 = load i8*, i8** %s63, align 8, !dbg !931
  %sub.ptr.lhs.cast64 = ptrtoint i8* %51 to i64, !dbg !932
  %sub.ptr.rhs.cast65 = ptrtoint i8* %53 to i64, !dbg !932
  %sub.ptr.sub66 = sub i64 %sub.ptr.lhs.cast64, %sub.ptr.rhs.cast65, !dbg !932
  %54 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !933
  %work67 = getelementptr inbounds %struct.shar, %struct.shar* %54, i32 0, i32 8, !dbg !934
  %length68 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work67, i32 0, i32 1, !dbg !935
  store i64 %sub.ptr.sub66, i64* %length68, align 8, !dbg !936
  %55 = load i64, i64* %written, align 8, !dbg !937
  store i64 %55, i64* %retval, align 8, !dbg !938
  br label %return, !dbg !938

return:                                           ; preds = %while.end, %if.then55, %if.then12, %if.then2, %if.then
  %56 = load i64, i64* %retval, align 8, !dbg !939
  ret i64 %56, !dbg !939
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_shar_finish_entry(%struct.archive_write* %a) #0 !dbg !228 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %g = alloca i8*, align 8
  %p = alloca i8*, align 8
  %u = alloca i8*, align 8
  %shar = alloca %struct.shar*, align 8
  %ret = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !940, metadata !242), !dbg !941
  call void @llvm.dbg.declare(metadata i8** %g, metadata !942, metadata !242), !dbg !943
  call void @llvm.dbg.declare(metadata i8** %p, metadata !944, metadata !242), !dbg !945
  call void @llvm.dbg.declare(metadata i8** %u, metadata !946, metadata !242), !dbg !947
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !948, metadata !242), !dbg !949
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !950, metadata !242), !dbg !951
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !952
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !953
  %1 = load i8*, i8** %format_data, align 8, !dbg !953
  %2 = bitcast i8* %1 to %struct.shar*, !dbg !954
  store %struct.shar* %2, %struct.shar** %shar, align 8, !dbg !955
  %3 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !956
  %entry1 = getelementptr inbounds %struct.shar, %struct.shar* %3, i32 0, i32 2, !dbg !958
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !958
  %cmp = icmp eq %struct.archive_entry* %4, null, !dbg !959
  br i1 %cmp, label %if.then, label %if.end, !dbg !960

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !961
  br label %return, !dbg !961

if.end:                                           ; preds = %entry
  %5 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !962
  %dump = getelementptr inbounds %struct.shar, %struct.shar* %5, i32 0, i32 0, !dbg !964
  %6 = load i32, i32* %dump, align 8, !dbg !964
  %tobool = icmp ne i32 %6, 0, !dbg !962
  br i1 %tobool, label %if.then2, label %if.else, !dbg !965

if.then2:                                         ; preds = %if.end
  %7 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !966
  %has_data = getelementptr inbounds %struct.shar, %struct.shar* %7, i32 0, i32 3, !dbg !969
  %8 = load i32, i32* %has_data, align 8, !dbg !969
  %tobool3 = icmp ne i32 %8, 0, !dbg !966
  br i1 %tobool3, label %if.then4, label %if.end15, !dbg !970

if.then4:                                         ; preds = %if.then2
  %9 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !971
  %outpos = getelementptr inbounds %struct.shar, %struct.shar* %9, i32 0, i32 6, !dbg !974
  %10 = load i64, i64* %outpos, align 8, !dbg !974
  %cmp5 = icmp ugt i64 %10, 0, !dbg !975
  br i1 %cmp5, label %if.then6, label %if.end11, !dbg !976

if.then6:                                         ; preds = %if.then4
  br label %do.body, !dbg !977

do.body:                                          ; preds = %if.then6
  call void @llvm.dbg.declare(metadata i32* %r, metadata !978, metadata !242), !dbg !980
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !981
  %12 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !981
  %13 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !981
  %outbuff = getelementptr inbounds %struct.shar, %struct.shar* %13, i32 0, i32 5, !dbg !981
  %arraydecay = getelementptr inbounds [45 x i8], [45 x i8]* %outbuff, i32 0, i32 0, !dbg !981
  %14 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !981
  %outpos7 = getelementptr inbounds %struct.shar, %struct.shar* %14, i32 0, i32 6, !dbg !981
  %15 = load i64, i64* %outpos7, align 8, !dbg !981
  %call = call i32 @_uuencode_line(%struct.archive_write* %11, %struct.shar* %12, i8* %arraydecay, i64 %15), !dbg !981
  store i32 %call, i32* %r, align 4, !dbg !981
  %16 = load i32, i32* %r, align 4, !dbg !981
  %cmp8 = icmp ne i32 %16, 0, !dbg !981
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !981

if.then9:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !983
  br label %return, !dbg !983

if.end10:                                         ; preds = %do.body
  br label %do.end, !dbg !986

do.end:                                           ; preds = %if.end10
  br label %if.end11, !dbg !988

if.end11:                                         ; preds = %do.end, %if.then4
  %17 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !990
  %work = getelementptr inbounds %struct.shar, %struct.shar* %17, i32 0, i32 8, !dbg !991
  %call12 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.28, i32 0, i32 0)), !dbg !992
  %18 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !993
  %work13 = getelementptr inbounds %struct.shar, %struct.shar* %18, i32 0, i32 8, !dbg !994
  %call14 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work13, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.29, i32 0, i32 0)), !dbg !995
  br label %if.end15, !dbg !996

if.end15:                                         ; preds = %if.end11, %if.then2
  %19 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !997
  %work16 = getelementptr inbounds %struct.shar, %struct.shar* %19, i32 0, i32 8, !dbg !998
  %20 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !999
  %entry17 = getelementptr inbounds %struct.shar, %struct.shar* %20, i32 0, i32 2, !dbg !1000
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry17, align 8, !dbg !1000
  %call18 = call i32 @archive_entry_mode(%struct.archive_entry* %21), !dbg !1001
  %and = and i32 %call18, 4095, !dbg !1002
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work16, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.30, i32 0, i32 0), i32 %and), !dbg !1003
  %22 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1004
  %work19 = getelementptr inbounds %struct.shar, %struct.shar* %22, i32 0, i32 8, !dbg !1005
  %23 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1006
  %entry20 = getelementptr inbounds %struct.shar, %struct.shar* %23, i32 0, i32 2, !dbg !1007
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry20, align 8, !dbg !1007
  %call21 = call i8* @archive_entry_pathname(%struct.archive_entry* %24), !dbg !1008
  call void @shar_quote(%struct.archive_string* %work19, i8* %call21, i32 1), !dbg !1009
  %25 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1011
  %work22 = getelementptr inbounds %struct.shar, %struct.shar* %25, i32 0, i32 8, !dbg !1012
  %call23 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work22, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0)), !dbg !1013
  %26 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1014
  %entry24 = getelementptr inbounds %struct.shar, %struct.shar* %26, i32 0, i32 2, !dbg !1015
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry24, align 8, !dbg !1015
  %call25 = call i8* @archive_entry_uname(%struct.archive_entry* %27), !dbg !1016
  store i8* %call25, i8** %u, align 8, !dbg !1017
  %28 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1018
  %entry26 = getelementptr inbounds %struct.shar, %struct.shar* %28, i32 0, i32 2, !dbg !1019
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry26, align 8, !dbg !1019
  %call27 = call i8* @archive_entry_gname(%struct.archive_entry* %29), !dbg !1020
  store i8* %call27, i8** %g, align 8, !dbg !1021
  %30 = load i8*, i8** %u, align 8, !dbg !1022
  %cmp28 = icmp ne i8* %30, null, !dbg !1024
  br i1 %cmp28, label %if.then30, label %lor.lhs.false, !dbg !1025

lor.lhs.false:                                    ; preds = %if.end15
  %31 = load i8*, i8** %g, align 8, !dbg !1026
  %cmp29 = icmp ne i8* %31, null, !dbg !1028
  br i1 %cmp29, label %if.then30, label %if.end50, !dbg !1029

if.then30:                                        ; preds = %lor.lhs.false, %if.end15
  %32 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1030
  %work31 = getelementptr inbounds %struct.shar, %struct.shar* %32, i32 0, i32 8, !dbg !1032
  %call32 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work31, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i32 0, i32 0)), !dbg !1033
  %33 = load i8*, i8** %u, align 8, !dbg !1034
  %cmp33 = icmp ne i8* %33, null, !dbg !1036
  br i1 %cmp33, label %if.then34, label %if.end36, !dbg !1037

if.then34:                                        ; preds = %if.then30
  %34 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1038
  %work35 = getelementptr inbounds %struct.shar, %struct.shar* %34, i32 0, i32 8, !dbg !1039
  %35 = load i8*, i8** %u, align 8, !dbg !1040
  call void @shar_quote(%struct.archive_string* %work35, i8* %35, i32 1), !dbg !1041
  br label %if.end36, !dbg !1041

if.end36:                                         ; preds = %if.then34, %if.then30
  %36 = load i8*, i8** %g, align 8, !dbg !1042
  %cmp37 = icmp ne i8* %36, null, !dbg !1044
  br i1 %cmp37, label %if.then38, label %if.end42, !dbg !1045

if.then38:                                        ; preds = %if.end36
  %37 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1046
  %work39 = getelementptr inbounds %struct.shar, %struct.shar* %37, i32 0, i32 8, !dbg !1048
  %call40 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work39, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.32, i32 0, i32 0)), !dbg !1049
  %38 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1050
  %work41 = getelementptr inbounds %struct.shar, %struct.shar* %38, i32 0, i32 8, !dbg !1051
  %39 = load i8*, i8** %g, align 8, !dbg !1052
  call void @shar_quote(%struct.archive_string* %work41, i8* %39, i32 1), !dbg !1053
  br label %if.end42, !dbg !1054

if.end42:                                         ; preds = %if.then38, %if.end36
  %40 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1055
  %work43 = getelementptr inbounds %struct.shar, %struct.shar* %40, i32 0, i32 8, !dbg !1056
  %call44 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work43, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.33, i32 0, i32 0)), !dbg !1057
  %41 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1058
  %work45 = getelementptr inbounds %struct.shar, %struct.shar* %41, i32 0, i32 8, !dbg !1059
  %42 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1060
  %entry46 = getelementptr inbounds %struct.shar, %struct.shar* %42, i32 0, i32 2, !dbg !1061
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry46, align 8, !dbg !1061
  %call47 = call i8* @archive_entry_pathname(%struct.archive_entry* %43), !dbg !1062
  call void @shar_quote(%struct.archive_string* %work45, i8* %call47, i32 1), !dbg !1063
  %44 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1064
  %work48 = getelementptr inbounds %struct.shar, %struct.shar* %44, i32 0, i32 8, !dbg !1065
  %call49 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work48, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0)), !dbg !1066
  br label %if.end50, !dbg !1067

if.end50:                                         ; preds = %if.end42, %lor.lhs.false
  %45 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1068
  %entry51 = getelementptr inbounds %struct.shar, %struct.shar* %45, i32 0, i32 2, !dbg !1070
  %46 = load %struct.archive_entry*, %struct.archive_entry** %entry51, align 8, !dbg !1070
  %call52 = call i8* @archive_entry_fflags_text(%struct.archive_entry* %46), !dbg !1071
  store i8* %call52, i8** %p, align 8, !dbg !1072
  %cmp53 = icmp ne i8* %call52, null, !dbg !1073
  br i1 %cmp53, label %if.then54, label %if.end61, !dbg !1074

if.then54:                                        ; preds = %if.end50
  %47 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1075
  %work55 = getelementptr inbounds %struct.shar, %struct.shar* %47, i32 0, i32 8, !dbg !1077
  %48 = load i8*, i8** %p, align 8, !dbg !1078
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %work55, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.34, i32 0, i32 0), i8* %48), !dbg !1079
  %49 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1080
  %work56 = getelementptr inbounds %struct.shar, %struct.shar* %49, i32 0, i32 8, !dbg !1081
  %50 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1082
  %entry57 = getelementptr inbounds %struct.shar, %struct.shar* %50, i32 0, i32 2, !dbg !1083
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry57, align 8, !dbg !1083
  %call58 = call i8* @archive_entry_pathname(%struct.archive_entry* %51), !dbg !1084
  call void @shar_quote(%struct.archive_string* %work56, i8* %call58, i32 1), !dbg !1085
  %52 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1086
  %work59 = getelementptr inbounds %struct.shar, %struct.shar* %52, i32 0, i32 8, !dbg !1087
  %call60 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work59, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0)), !dbg !1088
  br label %if.end61, !dbg !1089

if.end61:                                         ; preds = %if.then54, %if.end50
  br label %if.end73, !dbg !1090

if.else:                                          ; preds = %if.end
  %53 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1091
  %has_data62 = getelementptr inbounds %struct.shar, %struct.shar* %53, i32 0, i32 3, !dbg !1094
  %54 = load i32, i32* %has_data62, align 8, !dbg !1094
  %tobool63 = icmp ne i32 %54, 0, !dbg !1091
  br i1 %tobool63, label %if.then64, label %if.end72, !dbg !1095

if.then64:                                        ; preds = %if.else
  %55 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1096
  %end_of_line = getelementptr inbounds %struct.shar, %struct.shar* %55, i32 0, i32 1, !dbg !1099
  %56 = load i32, i32* %end_of_line, align 4, !dbg !1099
  %tobool65 = icmp ne i32 %56, 0, !dbg !1096
  br i1 %tobool65, label %if.end69, label %if.then66, !dbg !1100

if.then66:                                        ; preds = %if.then64
  %57 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1101
  %work67 = getelementptr inbounds %struct.shar, %struct.shar* %57, i32 0, i32 8, !dbg !1102
  %call68 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %work67, i8 signext 10), !dbg !1103
  br label %if.end69, !dbg !1103

if.end69:                                         ; preds = %if.then66, %if.then64
  %58 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1104
  %work70 = getelementptr inbounds %struct.shar, %struct.shar* %58, i32 0, i32 8, !dbg !1105
  %call71 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %work70, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.29, i32 0, i32 0)), !dbg !1106
  br label %if.end72, !dbg !1107

if.end72:                                         ; preds = %if.end69, %if.else
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.end61
  %59 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1108
  %entry74 = getelementptr inbounds %struct.shar, %struct.shar* %59, i32 0, i32 2, !dbg !1109
  %60 = load %struct.archive_entry*, %struct.archive_entry** %entry74, align 8, !dbg !1109
  call void @archive_entry_free(%struct.archive_entry* %60), !dbg !1110
  %61 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1111
  %entry75 = getelementptr inbounds %struct.shar, %struct.shar* %61, i32 0, i32 2, !dbg !1112
  store %struct.archive_entry* null, %struct.archive_entry** %entry75, align 8, !dbg !1113
  %62 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1114
  %work76 = getelementptr inbounds %struct.shar, %struct.shar* %62, i32 0, i32 8, !dbg !1116
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work76, i32 0, i32 1, !dbg !1117
  %63 = load i64, i64* %length, align 8, !dbg !1117
  %cmp77 = icmp ult i64 %63, 65536, !dbg !1118
  br i1 %cmp77, label %if.then78, label %if.end79, !dbg !1119

if.then78:                                        ; preds = %if.end73
  store i32 0, i32* %retval, align 4, !dbg !1120
  br label %return, !dbg !1120

if.end79:                                         ; preds = %if.end73
  %64 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1121
  %65 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1122
  %work80 = getelementptr inbounds %struct.shar, %struct.shar* %65, i32 0, i32 8, !dbg !1123
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work80, i32 0, i32 0, !dbg !1124
  %66 = load i8*, i8** %s, align 8, !dbg !1124
  %67 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1125
  %work81 = getelementptr inbounds %struct.shar, %struct.shar* %67, i32 0, i32 8, !dbg !1126
  %length82 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work81, i32 0, i32 1, !dbg !1127
  %68 = load i64, i64* %length82, align 8, !dbg !1127
  %call83 = call i32 @__archive_write_output(%struct.archive_write* %64, i8* %66, i64 %68), !dbg !1128
  store i32 %call83, i32* %ret, align 4, !dbg !1129
  %69 = load i32, i32* %ret, align 4, !dbg !1130
  %cmp84 = icmp ne i32 %69, 0, !dbg !1132
  br i1 %cmp84, label %if.then85, label %if.end86, !dbg !1133

if.then85:                                        ; preds = %if.end79
  store i32 -30, i32* %retval, align 4, !dbg !1134
  br label %return, !dbg !1134

if.end86:                                         ; preds = %if.end79
  %70 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1135
  %work87 = getelementptr inbounds %struct.shar, %struct.shar* %70, i32 0, i32 8, !dbg !1135
  %length88 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work87, i32 0, i32 1, !dbg !1135
  store i64 0, i64* %length88, align 8, !dbg !1135
  store i32 0, i32* %retval, align 4, !dbg !1136
  br label %return, !dbg !1136

return:                                           ; preds = %if.end86, %if.then85, %if.then78, %if.then9, %if.then
  %71 = load i32, i32* %retval, align 4, !dbg !1137
  ret i32 %71, !dbg !1137
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_shar_dump(%struct.archive* %_a) #0 !dbg !214 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %shar = alloca %struct.shar*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1138, metadata !242), !dbg !1139
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !1140, metadata !242), !dbg !1141
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1142
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !1143
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !1141
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !1144, metadata !242), !dbg !1145
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1146
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1147
  %call = call i32 @archive_write_set_format_shar(%struct.archive* %archive), !dbg !1148
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1149
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 14, !dbg !1150
  %4 = load i8*, i8** %format_data, align 8, !dbg !1150
  %5 = bitcast i8* %4 to %struct.shar*, !dbg !1151
  store %struct.shar* %5, %struct.shar** %shar, align 8, !dbg !1152
  %6 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1153
  %dump = getelementptr inbounds %struct.shar, %struct.shar* %6, i32 0, i32 0, !dbg !1154
  store i32 1, i32* %dump, align 8, !dbg !1155
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1156
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 20, !dbg !1157
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_shar_data_uuencode, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !1158
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1159
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !1160
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 3, !dbg !1161
  store i32 131074, i32* %archive_format, align 8, !dbg !1162
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !1163
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !1164
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !1165
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !1166
  ret i32 0, !dbg !1167
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_shar_data_uuencode(%struct.archive_write* %a, i8* %buff, i64 %length) #0 !dbg !221 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %shar = alloca %struct.shar*, align 8
  %src = alloca i8*, align 8
  %n = alloca i64, align 8
  %ret = alloca i32, align 4
  %r = alloca i32, align 4
  %r23 = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1168, metadata !242), !dbg !1169
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1170, metadata !242), !dbg !1171
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !1172, metadata !242), !dbg !1173
  call void @llvm.dbg.declare(metadata %struct.shar** %shar, metadata !1174, metadata !242), !dbg !1175
  call void @llvm.dbg.declare(metadata i8** %src, metadata !1176, metadata !242), !dbg !1177
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1178, metadata !242), !dbg !1179
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1180, metadata !242), !dbg !1181
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1182
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1183
  %1 = load i8*, i8** %format_data, align 8, !dbg !1183
  %2 = bitcast i8* %1 to %struct.shar*, !dbg !1184
  store %struct.shar* %2, %struct.shar** %shar, align 8, !dbg !1185
  %3 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1186
  %has_data = getelementptr inbounds %struct.shar, %struct.shar* %3, i32 0, i32 3, !dbg !1188
  %4 = load i32, i32* %has_data, align 8, !dbg !1188
  %tobool = icmp ne i32 %4, 0, !dbg !1186
  br i1 %tobool, label %if.end, label %if.then, !dbg !1189

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !1190
  br label %return, !dbg !1190

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %buff.addr, align 8, !dbg !1191
  store i8* %5, i8** %src, align 8, !dbg !1192
  %6 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1193
  %outpos = getelementptr inbounds %struct.shar, %struct.shar* %6, i32 0, i32 6, !dbg !1195
  %7 = load i64, i64* %outpos, align 8, !dbg !1195
  %cmp = icmp ne i64 %7, 0, !dbg !1196
  br i1 %cmp, label %if.then1, label %if.else, !dbg !1197

if.then1:                                         ; preds = %if.end
  %8 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1198
  %outpos2 = getelementptr inbounds %struct.shar, %struct.shar* %8, i32 0, i32 6, !dbg !1200
  %9 = load i64, i64* %outpos2, align 8, !dbg !1200
  %sub = sub i64 45, %9, !dbg !1201
  store i64 %sub, i64* %n, align 8, !dbg !1202
  %10 = load i64, i64* %n, align 8, !dbg !1203
  %11 = load i64, i64* %length.addr, align 8, !dbg !1205
  %cmp3 = icmp ugt i64 %10, %11, !dbg !1206
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1207

if.then4:                                         ; preds = %if.then1
  %12 = load i64, i64* %length.addr, align 8, !dbg !1208
  store i64 %12, i64* %n, align 8, !dbg !1209
  br label %if.end5, !dbg !1210

if.end5:                                          ; preds = %if.then4, %if.then1
  %13 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1211
  %outbuff = getelementptr inbounds %struct.shar, %struct.shar* %13, i32 0, i32 5, !dbg !1212
  %arraydecay = getelementptr inbounds [45 x i8], [45 x i8]* %outbuff, i32 0, i32 0, !dbg !1211
  %14 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1213
  %outpos6 = getelementptr inbounds %struct.shar, %struct.shar* %14, i32 0, i32 6, !dbg !1214
  %15 = load i64, i64* %outpos6, align 8, !dbg !1214
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %15, !dbg !1215
  %16 = load i8*, i8** %src, align 8, !dbg !1216
  %17 = load i64, i64* %n, align 8, !dbg !1217
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %16, i64 %17, i32 1, i1 false), !dbg !1218
  %18 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1219
  %outpos7 = getelementptr inbounds %struct.shar, %struct.shar* %18, i32 0, i32 6, !dbg !1221
  %19 = load i64, i64* %outpos7, align 8, !dbg !1221
  %20 = load i64, i64* %n, align 8, !dbg !1222
  %add = add i64 %19, %20, !dbg !1223
  %cmp8 = icmp ult i64 %add, 45, !dbg !1224
  br i1 %cmp8, label %if.then9, label %if.end12, !dbg !1225

if.then9:                                         ; preds = %if.end5
  %21 = load i64, i64* %n, align 8, !dbg !1226
  %22 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1228
  %outpos10 = getelementptr inbounds %struct.shar, %struct.shar* %22, i32 0, i32 6, !dbg !1229
  %23 = load i64, i64* %outpos10, align 8, !dbg !1230
  %add11 = add i64 %23, %21, !dbg !1230
  store i64 %add11, i64* %outpos10, align 8, !dbg !1230
  %24 = load i64, i64* %length.addr, align 8, !dbg !1231
  store i64 %24, i64* %retval, align 8, !dbg !1232
  br label %return, !dbg !1232

if.end12:                                         ; preds = %if.end5
  br label %do.body, !dbg !1233

do.body:                                          ; preds = %if.end12
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1234, metadata !242), !dbg !1236
  %25 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1237
  %26 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1237
  %27 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1237
  %outbuff13 = getelementptr inbounds %struct.shar, %struct.shar* %27, i32 0, i32 5, !dbg !1237
  %arraydecay14 = getelementptr inbounds [45 x i8], [45 x i8]* %outbuff13, i32 0, i32 0, !dbg !1237
  %call = call i32 @_uuencode_line(%struct.archive_write* %25, %struct.shar* %26, i8* %arraydecay14, i64 45), !dbg !1237
  store i32 %call, i32* %r, align 4, !dbg !1237
  %28 = load i32, i32* %r, align 4, !dbg !1237
  %cmp15 = icmp ne i32 %28, 0, !dbg !1237
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !1237

if.then16:                                        ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !1239
  br label %return, !dbg !1239

if.end17:                                         ; preds = %do.body
  br label %do.end, !dbg !1242

do.end:                                           ; preds = %if.end17
  %29 = load i64, i64* %n, align 8, !dbg !1244
  %30 = load i8*, i8** %src, align 8, !dbg !1245
  %add.ptr18 = getelementptr inbounds i8, i8* %30, i64 %29, !dbg !1245
  store i8* %add.ptr18, i8** %src, align 8, !dbg !1245
  %31 = load i64, i64* %length.addr, align 8, !dbg !1246
  %32 = load i64, i64* %n, align 8, !dbg !1247
  %sub19 = sub i64 %31, %32, !dbg !1248
  store i64 %sub19, i64* %n, align 8, !dbg !1249
  br label %if.end20, !dbg !1250

if.else:                                          ; preds = %if.end
  %33 = load i64, i64* %length.addr, align 8, !dbg !1251
  store i64 %33, i64* %n, align 8, !dbg !1253
  br label %if.end20

if.end20:                                         ; preds = %if.else, %do.end
  br label %while.cond, !dbg !1254

while.cond:                                       ; preds = %if.end41, %if.then33, %if.end20
  %34 = load i64, i64* %n, align 8, !dbg !1255
  %cmp21 = icmp uge i64 %34, 45, !dbg !1257
  br i1 %cmp21, label %while.body, label %while.end, !dbg !1258

while.body:                                       ; preds = %while.cond
  br label %do.body22, !dbg !1259

do.body22:                                        ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %r23, metadata !1261, metadata !242), !dbg !1263
  %35 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1264
  %36 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1264
  %37 = load i8*, i8** %src, align 8, !dbg !1264
  %call24 = call i32 @_uuencode_line(%struct.archive_write* %35, %struct.shar* %36, i8* %37, i64 45), !dbg !1264
  store i32 %call24, i32* %r23, align 4, !dbg !1264
  %38 = load i32, i32* %r23, align 4, !dbg !1264
  %cmp25 = icmp ne i32 %38, 0, !dbg !1264
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !1264

if.then26:                                        ; preds = %do.body22
  store i64 -30, i64* %retval, align 8, !dbg !1266
  br label %return, !dbg !1266

if.end27:                                         ; preds = %do.body22
  br label %do.end28, !dbg !1269

do.end28:                                         ; preds = %if.end27
  %39 = load i8*, i8** %src, align 8, !dbg !1271
  %add.ptr29 = getelementptr inbounds i8, i8* %39, i64 45, !dbg !1271
  store i8* %add.ptr29, i8** %src, align 8, !dbg !1271
  %40 = load i64, i64* %n, align 8, !dbg !1272
  %sub30 = sub i64 %40, 45, !dbg !1272
  store i64 %sub30, i64* %n, align 8, !dbg !1272
  %41 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1273
  %work = getelementptr inbounds %struct.shar, %struct.shar* %41, i32 0, i32 8, !dbg !1275
  %length31 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work, i32 0, i32 1, !dbg !1276
  %42 = load i64, i64* %length31, align 8, !dbg !1276
  %cmp32 = icmp ult i64 %42, 65536, !dbg !1277
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !1278

if.then33:                                        ; preds = %do.end28
  br label %while.cond, !dbg !1279

if.end34:                                         ; preds = %do.end28
  %43 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1280
  %44 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1281
  %work35 = getelementptr inbounds %struct.shar, %struct.shar* %44, i32 0, i32 8, !dbg !1282
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work35, i32 0, i32 0, !dbg !1283
  %45 = load i8*, i8** %s, align 8, !dbg !1283
  %46 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1284
  %work36 = getelementptr inbounds %struct.shar, %struct.shar* %46, i32 0, i32 8, !dbg !1285
  %length37 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work36, i32 0, i32 1, !dbg !1286
  %47 = load i64, i64* %length37, align 8, !dbg !1286
  %call38 = call i32 @__archive_write_output(%struct.archive_write* %43, i8* %45, i64 %47), !dbg !1287
  store i32 %call38, i32* %ret, align 4, !dbg !1288
  %48 = load i32, i32* %ret, align 4, !dbg !1289
  %cmp39 = icmp ne i32 %48, 0, !dbg !1291
  br i1 %cmp39, label %if.then40, label %if.end41, !dbg !1292

if.then40:                                        ; preds = %if.end34
  store i64 -30, i64* %retval, align 8, !dbg !1293
  br label %return, !dbg !1293

if.end41:                                         ; preds = %if.end34
  %49 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1294
  %work42 = getelementptr inbounds %struct.shar, %struct.shar* %49, i32 0, i32 8, !dbg !1294
  %length43 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work42, i32 0, i32 1, !dbg !1294
  store i64 0, i64* %length43, align 8, !dbg !1294
  br label %while.cond, !dbg !1295

while.end:                                        ; preds = %while.cond
  %50 = load i64, i64* %n, align 8, !dbg !1297
  %cmp44 = icmp ne i64 %50, 0, !dbg !1299
  br i1 %cmp44, label %if.then45, label %if.end49, !dbg !1300

if.then45:                                        ; preds = %while.end
  %51 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1301
  %outbuff46 = getelementptr inbounds %struct.shar, %struct.shar* %51, i32 0, i32 5, !dbg !1303
  %arraydecay47 = getelementptr inbounds [45 x i8], [45 x i8]* %outbuff46, i32 0, i32 0, !dbg !1304
  %52 = load i8*, i8** %src, align 8, !dbg !1305
  %53 = load i64, i64* %n, align 8, !dbg !1306
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay47, i8* %52, i64 %53, i32 1, i1 false), !dbg !1304
  %54 = load i64, i64* %n, align 8, !dbg !1307
  %55 = load %struct.shar*, %struct.shar** %shar, align 8, !dbg !1308
  %outpos48 = getelementptr inbounds %struct.shar, %struct.shar* %55, i32 0, i32 6, !dbg !1309
  store i64 %54, i64* %outpos48, align 8, !dbg !1310
  br label %if.end49, !dbg !1311

if.end49:                                         ; preds = %if.then45, %while.end
  %56 = load i64, i64* %length.addr, align 8, !dbg !1312
  store i64 %56, i64* %retval, align 8, !dbg !1313
  br label %return, !dbg !1313

return:                                           ; preds = %if.end49, %if.then40, %if.then26, %if.then16, %if.then9, %if.then
  %57 = load i64, i64* %retval, align 8, !dbg !1314
  ret i64 %57, !dbg !1314
}

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

declare %struct.archive_entry* @archive_entry_clone(%struct.archive_entry*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal void @shar_quote(%struct.archive_string* %buf, i8* %str, i32 %in_shell) #0 !dbg !216 {
entry:
  %buf.addr = alloca %struct.archive_string*, align 8
  %str.addr = alloca i8*, align 8
  %in_shell.addr = alloca i32, align 4
  %len = alloca i64, align 8
  store %struct.archive_string* %buf, %struct.archive_string** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %buf.addr, metadata !1315, metadata !242), !dbg !1316
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !1317, metadata !242), !dbg !1318
  store i32 %in_shell, i32* %in_shell.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %in_shell.addr, metadata !1319, metadata !242), !dbg !1320
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1321, metadata !242), !dbg !1322
  br label %while.cond, !dbg !1323

while.cond:                                       ; preds = %if.end18, %entry
  %0 = load i8*, i8** %str.addr, align 8, !dbg !1324
  %1 = load i8, i8* %0, align 1, !dbg !1326
  %conv = sext i8 %1 to i32, !dbg !1326
  %cmp = icmp ne i32 %conv, 0, !dbg !1327
  br i1 %cmp, label %while.body, label %while.end, !dbg !1328

while.body:                                       ; preds = %while.cond
  %2 = load i8*, i8** %str.addr, align 8, !dbg !1329
  %call = call i64 @strcspn(i8* %2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @shar_quote.meta, i32 0, i32 0)) #7, !dbg !1332
  store i64 %call, i64* %len, align 8, !dbg !1333
  %cmp2 = icmp ne i64 %call, 0, !dbg !1334
  br i1 %cmp2, label %if.then, label %if.else, !dbg !1335

if.then:                                          ; preds = %while.body
  %3 = load %struct.archive_string*, %struct.archive_string** %buf.addr, align 8, !dbg !1336
  %4 = load i8*, i8** %str.addr, align 8, !dbg !1338
  %5 = load i64, i64* %len, align 8, !dbg !1339
  %call4 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %3, i8* %4, i64 %5), !dbg !1340
  %6 = load i64, i64* %len, align 8, !dbg !1341
  %7 = load i8*, i8** %str.addr, align 8, !dbg !1342
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %6, !dbg !1342
  store i8* %add.ptr, i8** %str.addr, align 8, !dbg !1342
  br label %if.end18, !dbg !1343

if.else:                                          ; preds = %while.body
  %8 = load i8*, i8** %str.addr, align 8, !dbg !1344
  %9 = load i8, i8* %8, align 1, !dbg !1347
  %conv5 = sext i8 %9 to i32, !dbg !1347
  %cmp6 = icmp eq i32 %conv5, 10, !dbg !1348
  br i1 %cmp6, label %if.then8, label %if.else13, !dbg !1347

if.then8:                                         ; preds = %if.else
  %10 = load i32, i32* %in_shell.addr, align 4, !dbg !1349
  %tobool = icmp ne i32 %10, 0, !dbg !1349
  br i1 %tobool, label %if.then9, label %if.else11, !dbg !1352

if.then9:                                         ; preds = %if.then8
  %11 = load %struct.archive_string*, %struct.archive_string** %buf.addr, align 8, !dbg !1353
  %call10 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %11, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.24, i32 0, i32 0)), !dbg !1354
  br label %if.end, !dbg !1354

if.else11:                                        ; preds = %if.then8
  %12 = load %struct.archive_string*, %struct.archive_string** %buf.addr, align 8, !dbg !1355
  %call12 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %12, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.25, i32 0, i32 0)), !dbg !1356
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then9
  %13 = load i8*, i8** %str.addr, align 8, !dbg !1357
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !1357
  store i8* %incdec.ptr, i8** %str.addr, align 8, !dbg !1357
  br label %if.end17, !dbg !1358

if.else13:                                        ; preds = %if.else
  %14 = load %struct.archive_string*, %struct.archive_string** %buf.addr, align 8, !dbg !1359
  %call14 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %14, i8 signext 92), !dbg !1361
  %15 = load %struct.archive_string*, %struct.archive_string** %buf.addr, align 8, !dbg !1362
  %16 = load i8*, i8** %str.addr, align 8, !dbg !1363
  %17 = load i8, i8* %16, align 1, !dbg !1364
  %call15 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %15, i8 signext %17), !dbg !1365
  %18 = load i8*, i8** %str.addr, align 8, !dbg !1366
  %incdec.ptr16 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !1366
  store i8* %incdec.ptr16, i8** %str.addr, align 8, !dbg !1366
  br label %if.end17

if.end17:                                         ; preds = %if.else13, %if.end
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then
  br label %while.cond, !dbg !1367

while.end:                                        ; preds = %while.cond
  ret void, !dbg !1369
}

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #4

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #4

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strcspn(i8*, i8*) #4

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define internal i32 @_uuencode_line(%struct.archive_write* %a, %struct.shar* %shar, i8* %inbuf, i64 %len) #0 !dbg !222 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %shar.addr = alloca %struct.shar*, align 8
  %inbuf.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %buf = alloca i8*, align 8
  %alloc_len = alloca i64, align 8
  %tmp_buf = alloca [3 x i8], align 1
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1370, metadata !242), !dbg !1371
  store %struct.shar* %shar, %struct.shar** %shar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.shar** %shar.addr, metadata !1372, metadata !242), !dbg !1373
  store i8* %inbuf, i8** %inbuf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %inbuf.addr, metadata !1374, metadata !242), !dbg !1375
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1376, metadata !242), !dbg !1377
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !1378, metadata !242), !dbg !1379
  call void @llvm.dbg.declare(metadata i64* %alloc_len, metadata !1380, metadata !242), !dbg !1381
  %0 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1382
  %work = getelementptr inbounds %struct.shar, %struct.shar* %0, i32 0, i32 8, !dbg !1383
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work, i32 0, i32 1, !dbg !1384
  %1 = load i64, i64* %length, align 8, !dbg !1384
  %add = add i64 %1, 62, !dbg !1385
  store i64 %add, i64* %alloc_len, align 8, !dbg !1386
  %2 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1387
  %work1 = getelementptr inbounds %struct.shar, %struct.shar* %2, i32 0, i32 8, !dbg !1389
  %3 = load i64, i64* %alloc_len, align 8, !dbg !1390
  %call = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %work1, i64 %3), !dbg !1391
  %cmp = icmp eq %struct.archive_string* %call, null, !dbg !1392
  br i1 %cmp, label %if.then, label %if.end, !dbg !1393

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1394
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !1396
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.26, i32 0, i32 0)), !dbg !1397
  store i32 -30, i32* %retval, align 4, !dbg !1398
  br label %return, !dbg !1398

if.end:                                           ; preds = %entry
  %5 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1399
  %work2 = getelementptr inbounds %struct.shar, %struct.shar* %5, i32 0, i32 8, !dbg !1400
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work2, i32 0, i32 0, !dbg !1401
  %6 = load i8*, i8** %s, align 8, !dbg !1401
  %7 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1402
  %work3 = getelementptr inbounds %struct.shar, %struct.shar* %7, i32 0, i32 8, !dbg !1403
  %length4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work3, i32 0, i32 1, !dbg !1404
  %8 = load i64, i64* %length4, align 8, !dbg !1404
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %8, !dbg !1405
  store i8* %add.ptr, i8** %buf, align 8, !dbg !1406
  %9 = load i64, i64* %len.addr, align 8, !dbg !1407
  %cmp5 = icmp ne i64 %9, 0, !dbg !1407
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !1407

cond.true:                                        ; preds = %if.end
  %10 = load i64, i64* %len.addr, align 8, !dbg !1408
  %and = and i64 %10, 63, !dbg !1408
  %add6 = add i64 %and, 32, !dbg !1408
  br label %cond.end, !dbg !1408

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !1410

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %add6, %cond.true ], [ 96, %cond.false ], !dbg !1412
  %conv = trunc i64 %cond to i8, !dbg !1412
  %11 = load i8*, i8** %buf, align 8, !dbg !1414
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1414
  store i8* %incdec.ptr, i8** %buf, align 8, !dbg !1414
  store i8 %conv, i8* %11, align 1, !dbg !1415
  br label %while.cond, !dbg !1416

while.cond:                                       ; preds = %while.body, %cond.end
  %12 = load i64, i64* %len.addr, align 8, !dbg !1417
  %cmp7 = icmp uge i64 %12, 3, !dbg !1418
  br i1 %cmp7, label %while.body, label %while.end, !dbg !1419

while.body:                                       ; preds = %while.cond
  %13 = load i8*, i8** %inbuf.addr, align 8, !dbg !1420
  %14 = load i8*, i8** %buf, align 8, !dbg !1422
  call void @uuencode_group(i8* %13, i8* %14), !dbg !1423
  %15 = load i64, i64* %len.addr, align 8, !dbg !1424
  %sub = sub i64 %15, 3, !dbg !1424
  store i64 %sub, i64* %len.addr, align 8, !dbg !1424
  %16 = load i8*, i8** %inbuf.addr, align 8, !dbg !1425
  %add.ptr9 = getelementptr inbounds i8, i8* %16, i64 3, !dbg !1425
  store i8* %add.ptr9, i8** %inbuf.addr, align 8, !dbg !1425
  %17 = load i8*, i8** %buf, align 8, !dbg !1426
  %add.ptr10 = getelementptr inbounds i8, i8* %17, i64 4, !dbg !1426
  store i8* %add.ptr10, i8** %buf, align 8, !dbg !1426
  br label %while.cond, !dbg !1427

while.end:                                        ; preds = %while.cond
  %18 = load i64, i64* %len.addr, align 8, !dbg !1428
  %cmp11 = icmp ne i64 %18, 0, !dbg !1430
  br i1 %cmp11, label %if.then13, label %if.end24, !dbg !1431

if.then13:                                        ; preds = %while.end
  call void @llvm.dbg.declare(metadata [3 x i8]* %tmp_buf, metadata !1432, metadata !242), !dbg !1437
  %19 = load i8*, i8** %inbuf.addr, align 8, !dbg !1438
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 0, !dbg !1438
  %20 = load i8, i8* %arrayidx, align 1, !dbg !1438
  %arrayidx14 = getelementptr inbounds [3 x i8], [3 x i8]* %tmp_buf, i64 0, i64 0, !dbg !1439
  store i8 %20, i8* %arrayidx14, align 1, !dbg !1440
  %21 = load i64, i64* %len.addr, align 8, !dbg !1441
  %cmp15 = icmp eq i64 %21, 1, !dbg !1443
  br i1 %cmp15, label %if.then17, label %if.else, !dbg !1444

if.then17:                                        ; preds = %if.then13
  %arrayidx18 = getelementptr inbounds [3 x i8], [3 x i8]* %tmp_buf, i64 0, i64 1, !dbg !1445
  store i8 0, i8* %arrayidx18, align 1, !dbg !1446
  br label %if.end21, !dbg !1445

if.else:                                          ; preds = %if.then13
  %22 = load i8*, i8** %inbuf.addr, align 8, !dbg !1447
  %arrayidx19 = getelementptr inbounds i8, i8* %22, i64 1, !dbg !1447
  %23 = load i8, i8* %arrayidx19, align 1, !dbg !1447
  %arrayidx20 = getelementptr inbounds [3 x i8], [3 x i8]* %tmp_buf, i64 0, i64 1, !dbg !1448
  store i8 %23, i8* %arrayidx20, align 1, !dbg !1449
  br label %if.end21

if.end21:                                         ; preds = %if.else, %if.then17
  %arrayidx22 = getelementptr inbounds [3 x i8], [3 x i8]* %tmp_buf, i64 0, i64 2, !dbg !1450
  store i8 0, i8* %arrayidx22, align 1, !dbg !1451
  %arraydecay = getelementptr inbounds [3 x i8], [3 x i8]* %tmp_buf, i32 0, i32 0, !dbg !1452
  %24 = load i8*, i8** %buf, align 8, !dbg !1453
  call void @uuencode_group(i8* %arraydecay, i8* %24), !dbg !1454
  %25 = load i8*, i8** %buf, align 8, !dbg !1455
  %add.ptr23 = getelementptr inbounds i8, i8* %25, i64 4, !dbg !1455
  store i8* %add.ptr23, i8** %buf, align 8, !dbg !1455
  br label %if.end24, !dbg !1456

if.end24:                                         ; preds = %if.end21, %while.end
  %26 = load i8*, i8** %buf, align 8, !dbg !1457
  %incdec.ptr25 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !1457
  store i8* %incdec.ptr25, i8** %buf, align 8, !dbg !1457
  store i8 10, i8* %26, align 1, !dbg !1458
  %27 = load i8*, i8** %buf, align 8, !dbg !1459
  %28 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1461
  %work26 = getelementptr inbounds %struct.shar, %struct.shar* %28, i32 0, i32 8, !dbg !1462
  %s27 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work26, i32 0, i32 0, !dbg !1463
  %29 = load i8*, i8** %s27, align 8, !dbg !1463
  %sub.ptr.lhs.cast = ptrtoint i8* %27 to i64, !dbg !1464
  %sub.ptr.rhs.cast = ptrtoint i8* %29 to i64, !dbg !1464
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1464
  %30 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1465
  %work28 = getelementptr inbounds %struct.shar, %struct.shar* %30, i32 0, i32 8, !dbg !1466
  %length29 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work28, i32 0, i32 1, !dbg !1467
  %31 = load i64, i64* %length29, align 8, !dbg !1467
  %add30 = add i64 %31, 62, !dbg !1468
  %cmp31 = icmp sgt i64 %sub.ptr.sub, %add30, !dbg !1469
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !1470

if.then33:                                        ; preds = %if.end24
  %32 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1471
  %archive34 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %32, i32 0, i32 0, !dbg !1473
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive34, i32 -1, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.27, i32 0, i32 0)), !dbg !1474
  store i32 -30, i32* %retval, align 4, !dbg !1475
  br label %return, !dbg !1475

if.end35:                                         ; preds = %if.end24
  %33 = load i8*, i8** %buf, align 8, !dbg !1476
  %34 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1477
  %work36 = getelementptr inbounds %struct.shar, %struct.shar* %34, i32 0, i32 8, !dbg !1478
  %s37 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work36, i32 0, i32 0, !dbg !1479
  %35 = load i8*, i8** %s37, align 8, !dbg !1479
  %sub.ptr.lhs.cast38 = ptrtoint i8* %33 to i64, !dbg !1480
  %sub.ptr.rhs.cast39 = ptrtoint i8* %35 to i64, !dbg !1480
  %sub.ptr.sub40 = sub i64 %sub.ptr.lhs.cast38, %sub.ptr.rhs.cast39, !dbg !1480
  %36 = load %struct.shar*, %struct.shar** %shar.addr, align 8, !dbg !1481
  %work41 = getelementptr inbounds %struct.shar, %struct.shar* %36, i32 0, i32 8, !dbg !1482
  %length42 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %work41, i32 0, i32 1, !dbg !1483
  store i64 %sub.ptr.sub40, i64* %length42, align 8, !dbg !1484
  store i32 0, i32* %retval, align 4, !dbg !1485
  br label %return, !dbg !1485

return:                                           ; preds = %if.end35, %if.then33, %if.then
  %37 = load i32, i32* %retval, align 4, !dbg !1486
  ret i32 %37, !dbg !1486
}

; Function Attrs: nounwind uwtable
define internal void @uuencode_group(i8* %_in, i8* %out) #0 !dbg !225 {
entry:
  %_in.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %in = alloca i8*, align 8
  %t = alloca i32, align 4
  store i8* %_in, i8** %_in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_in.addr, metadata !1487, metadata !242), !dbg !1488
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !1489, metadata !242), !dbg !1490
  call void @llvm.dbg.declare(metadata i8** %in, metadata !1491, metadata !242), !dbg !1492
  %0 = load i8*, i8** %_in.addr, align 8, !dbg !1493
  store i8* %0, i8** %in, align 8, !dbg !1492
  call void @llvm.dbg.declare(metadata i32* %t, metadata !1494, metadata !242), !dbg !1495
  %1 = load i8*, i8** %in, align 8, !dbg !1496
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !1496
  %2 = load i8, i8* %arrayidx, align 1, !dbg !1496
  %conv = zext i8 %2 to i32, !dbg !1496
  %shl = shl i32 %conv, 16, !dbg !1497
  %3 = load i8*, i8** %in, align 8, !dbg !1498
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 1, !dbg !1498
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !1498
  %conv2 = zext i8 %4 to i32, !dbg !1498
  %shl3 = shl i32 %conv2, 8, !dbg !1499
  %or = or i32 %shl, %shl3, !dbg !1500
  %5 = load i8*, i8** %in, align 8, !dbg !1501
  %arrayidx4 = getelementptr inbounds i8, i8* %5, i64 2, !dbg !1501
  %6 = load i8, i8* %arrayidx4, align 1, !dbg !1501
  %conv5 = zext i8 %6 to i32, !dbg !1501
  %or6 = or i32 %or, %conv5, !dbg !1502
  store i32 %or6, i32* %t, align 4, !dbg !1503
  %7 = load i32, i32* %t, align 4, !dbg !1504
  %shr = ashr i32 %7, 18, !dbg !1504
  %and = and i32 63, %shr, !dbg !1504
  %cmp = icmp ne i32 %and, 0, !dbg !1504
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1504

cond.true:                                        ; preds = %entry
  %8 = load i32, i32* %t, align 4, !dbg !1505
  %shr8 = ashr i32 %8, 18, !dbg !1505
  %and9 = and i32 63, %shr8, !dbg !1505
  %and10 = and i32 %and9, 63, !dbg !1505
  %add = add nsw i32 %and10, 32, !dbg !1505
  br label %cond.end, !dbg !1505

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1507

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %add, %cond.true ], [ 96, %cond.false ], !dbg !1509
  %conv11 = trunc i32 %cond to i8, !dbg !1509
  %9 = load i8*, i8** %out.addr, align 8, !dbg !1511
  %arrayidx12 = getelementptr inbounds i8, i8* %9, i64 0, !dbg !1511
  store i8 %conv11, i8* %arrayidx12, align 1, !dbg !1512
  %10 = load i32, i32* %t, align 4, !dbg !1513
  %shr13 = ashr i32 %10, 12, !dbg !1513
  %and14 = and i32 63, %shr13, !dbg !1513
  %cmp15 = icmp ne i32 %and14, 0, !dbg !1513
  br i1 %cmp15, label %cond.true17, label %cond.false22, !dbg !1513

cond.true17:                                      ; preds = %cond.end
  %11 = load i32, i32* %t, align 4, !dbg !1514
  %shr18 = ashr i32 %11, 12, !dbg !1514
  %and19 = and i32 63, %shr18, !dbg !1514
  %and20 = and i32 %and19, 63, !dbg !1514
  %add21 = add nsw i32 %and20, 32, !dbg !1514
  br label %cond.end23, !dbg !1514

cond.false22:                                     ; preds = %cond.end
  br label %cond.end23, !dbg !1515

cond.end23:                                       ; preds = %cond.false22, %cond.true17
  %cond24 = phi i32 [ %add21, %cond.true17 ], [ 96, %cond.false22 ], !dbg !1516
  %conv25 = trunc i32 %cond24 to i8, !dbg !1516
  %12 = load i8*, i8** %out.addr, align 8, !dbg !1517
  %arrayidx26 = getelementptr inbounds i8, i8* %12, i64 1, !dbg !1517
  store i8 %conv25, i8* %arrayidx26, align 1, !dbg !1518
  %13 = load i32, i32* %t, align 4, !dbg !1519
  %shr27 = ashr i32 %13, 6, !dbg !1519
  %and28 = and i32 63, %shr27, !dbg !1519
  %cmp29 = icmp ne i32 %and28, 0, !dbg !1519
  br i1 %cmp29, label %cond.true31, label %cond.false36, !dbg !1519

cond.true31:                                      ; preds = %cond.end23
  %14 = load i32, i32* %t, align 4, !dbg !1520
  %shr32 = ashr i32 %14, 6, !dbg !1520
  %and33 = and i32 63, %shr32, !dbg !1520
  %and34 = and i32 %and33, 63, !dbg !1520
  %add35 = add nsw i32 %and34, 32, !dbg !1520
  br label %cond.end37, !dbg !1520

cond.false36:                                     ; preds = %cond.end23
  br label %cond.end37, !dbg !1521

cond.end37:                                       ; preds = %cond.false36, %cond.true31
  %cond38 = phi i32 [ %add35, %cond.true31 ], [ 96, %cond.false36 ], !dbg !1522
  %conv39 = trunc i32 %cond38 to i8, !dbg !1522
  %15 = load i8*, i8** %out.addr, align 8, !dbg !1523
  %arrayidx40 = getelementptr inbounds i8, i8* %15, i64 2, !dbg !1523
  store i8 %conv39, i8* %arrayidx40, align 1, !dbg !1524
  %16 = load i32, i32* %t, align 4, !dbg !1525
  %and41 = and i32 63, %16, !dbg !1525
  %cmp42 = icmp ne i32 %and41, 0, !dbg !1525
  br i1 %cmp42, label %cond.true44, label %cond.false48, !dbg !1525

cond.true44:                                      ; preds = %cond.end37
  %17 = load i32, i32* %t, align 4, !dbg !1526
  %and45 = and i32 63, %17, !dbg !1526
  %and46 = and i32 %and45, 63, !dbg !1526
  %add47 = add nsw i32 %and46, 32, !dbg !1526
  br label %cond.end49, !dbg !1526

cond.false48:                                     ; preds = %cond.end37
  br label %cond.end49, !dbg !1527

cond.end49:                                       ; preds = %cond.false48, %cond.true44
  %cond50 = phi i32 [ %add47, %cond.true44 ], [ 96, %cond.false48 ], !dbg !1528
  %conv51 = trunc i32 %cond50 to i8, !dbg !1528
  %18 = load i8*, i8** %out.addr, align 8, !dbg !1529
  %arrayidx52 = getelementptr inbounds i8, i8* %18, i64 3, !dbg !1529
  store i8 %conv51, i8* %arrayidx52, align 1, !dbg !1530
  ret void, !dbg !1531
}

declare i8* @archive_entry_uname(%struct.archive_entry*) #2

declare i8* @archive_entry_gname(%struct.archive_entry*) #2

declare i8* @archive_entry_fflags_text(%struct.archive_entry*) #2

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #2

declare void @archive_string_free(%struct.archive_string*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!238, !239}
!llvm.ident = !{!240}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !212, globals: !231)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_shar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123, !191, !207, !210, !80, !211, !114, !13}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !124, !130, !133, !134, !135, !136, !162, !163, !164, !165, !169, !173, !174, !178, !182, !183, !184, !185, !190}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !125, size: 64, align: 64, offset: 1664)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !43, !45}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !131, size: 64, align: 64, offset: 1728)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !123, size: 64, align: 64, offset: 1792)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !137, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !147, !151, !155, !156, !157, !158, !159, !160, !161}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !138, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !138, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !138, file: !6, line: 46, baseType: !137, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !6, line: 47, baseType: !144, size: 64, align: 64, offset: 192)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!23, !137, !80, !80}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !138, file: !6, line: 49, baseType: !148, size: 64, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DISubroutineType(types: !150)
!150 = !{!23, !137}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !138, file: !6, line: 50, baseType: !152, size: 64, align: 64, offset: 320)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!23, !137, !43, !45}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !138, file: !6, line: 51, baseType: !148, size: 64, align: 64, offset: 384)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !138, file: !6, line: 52, baseType: !148, size: 64, align: 64, offset: 448)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !6, line: 53, baseType: !123, size: 64, align: 64, offset: 512)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !138, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !138, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !138, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !138, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !137, size: 64, align: 64, offset: 1984)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !123, size: 64, align: 64, offset: 2048)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !166, size: 64, align: 64, offset: 2176)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !4}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !170, size: 64, align: 64, offset: 2240)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!23, !4, !80, !80}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !166, size: 64, align: 64, offset: 2304)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !175, size: 64, align: 64, offset: 2368)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!23, !4, !30}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !179, size: 64, align: 64, offset: 2432)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!38, !4, !43, !45}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !166, size: 64, align: 64, offset: 2496)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !166, size: 64, align: 64, offset: 2560)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !186, size: 64, align: 64, offset: 2688)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !188)
!188 = !DISubroutineType(types: !189)
!189 = !{!80, !24, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !123, size: 64, align: 64, offset: 2752)
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "shar", file: !1, line: 46, size: 1152, align: 64, elements: !193)
!193 = !{!194, !195, !196, !197, !198, !199, !203, !204, !205, !206}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "dump", scope: !192, file: !1, line: 47, baseType: !23, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_line", scope: !192, file: !1, line: 48, baseType: !23, size: 32, align: 32, offset: 32)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !192, file: !1, line: 49, baseType: !30, size: 64, align: 64, offset: 64)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "has_data", scope: !192, file: !1, line: 50, baseType: !23, size: 32, align: 32, offset: 128)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "last_dir", scope: !192, file: !1, line: 51, baseType: !95, size: 64, align: 64, offset: 192)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "outbuff", scope: !192, file: !1, line: 54, baseType: !200, size: 360, align: 8, offset: 256)
!200 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 360, align: 8, elements: !201)
!201 = !{!202}
!202 = !DISubrange(count: 45)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "outpos", scope: !192, file: !1, line: 55, baseType: !45, size: 64, align: 64, offset: 640)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "wrote_header", scope: !192, file: !1, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !192, file: !1, line: 58, baseType: !91, size: 192, align: 64, offset: 768)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "quoted_name", scope: !192, file: !1, line: 59, baseType: !91, size: 192, align: 64, offset: 960)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !208, line: 70, baseType: !209)
!208 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!209 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !53, line: 135, baseType: !47)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "ptrdiff_t", file: !46, line: 51, baseType: !42)
!212 = !{!213, !214, !215, !216, !220, !221, !222, !225, !228, !229, !230}
!213 = distinct !DISubprogram(name: "archive_write_set_format_shar", scope: !1, file: !1, line: 104, type: !21, isLocal: false, isDefinition: true, scopeLine: 105, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!214 = distinct !DISubprogram(name: "archive_write_set_format_shar_dump", scope: !1, file: !1, line: 142, type: !21, isLocal: false, isDefinition: true, scopeLine: 143, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = distinct !DISubprogram(name: "archive_write_shar_header", scope: !1, file: !1, line: 157, type: !176, isLocal: true, isDefinition: true, scopeLine: 158, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "shar_quote", scope: !1, file: !1, line: 77, type: !217, isLocal: true, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = !DISubroutineType(types: !218)
!218 = !{null, !219, !80, !23}
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!220 = distinct !DISubprogram(name: "archive_write_shar_data_sed", scope: !1, file: !1, line: 330, type: !180, isLocal: true, isDefinition: true, scopeLine: 331, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_write_shar_data_uuencode", scope: !1, file: !1, line: 461, type: !180, isLocal: true, isDefinition: true, scopeLine: 463, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = distinct !DISubprogram(name: "_uuencode_line", scope: !1, file: !1, line: 412, type: !223, isLocal: true, isDefinition: true, scopeLine: 413, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!223 = !DISubroutineType(types: !224)
!224 = !{!23, !4, !191, !80, !45}
!225 = distinct !DISubprogram(name: "uuencode_group", scope: !1, file: !1, line: 399, type: !226, isLocal: true, isDefinition: true, scopeLine: 400, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!226 = !DISubroutineType(types: !227)
!227 = !{null, !80, !95}
!228 = distinct !DISubprogram(name: "archive_write_shar_finish_entry", scope: !1, file: !1, line: 511, type: !167, isLocal: true, isDefinition: true, scopeLine: 512, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!229 = distinct !DISubprogram(name: "archive_write_shar_close", scope: !1, file: !1, line: 589, type: !167, isLocal: true, isDefinition: true, scopeLine: 590, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!230 = distinct !DISubprogram(name: "archive_write_shar_free", scope: !1, file: !1, line: 627, type: !167, isLocal: true, isDefinition: true, scopeLine: 628, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!231 = !{!232, !236}
!232 = !DIGlobalVariable(name: "meta", scope: !216, file: !1, line: 79, type: !233, isLocal: true, isDefinition: true, variable: [26 x i8]* @shar_quote.meta)
!233 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 208, align: 8, elements: !234)
!234 = !{!235}
!235 = !DISubrange(count: 26)
!236 = !DIGlobalVariable(name: "ensured", scope: !220, file: !1, line: 332, type: !237, isLocal: true, isDefinition: true, variable: i64* @archive_write_shar_data_sed.ensured)
!237 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!238 = !{i32 2, !"Dwarf Version", i32 4}
!239 = !{i32 2, !"Debug Info Version", i32 3}
!240 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!241 = !DILocalVariable(name: "_a", arg: 1, scope: !213, file: !1, line: 104, type: !24)
!242 = !DIExpression()
!243 = !DILocation(line: 104, column: 47, scope: !213)
!244 = !DILocalVariable(name: "a", scope: !213, file: !1, line: 106, type: !4)
!245 = !DILocation(line: 106, column: 24, scope: !213)
!246 = !DILocation(line: 106, column: 52, scope: !213)
!247 = !DILocation(line: 106, column: 28, scope: !213)
!248 = !DILocalVariable(name: "shar", scope: !213, file: !1, line: 107, type: !191)
!249 = !DILocation(line: 107, column: 15, scope: !213)
!250 = !DILocation(line: 109, column: 2, scope: !213)
!251 = !DILocalVariable(name: "magic_test", scope: !252, file: !1, line: 109, type: !23)
!252 = distinct !DILexicalBlock(scope: !213, file: !1, line: 109, column: 2)
!253 = !DILocation(line: 109, column: 2, scope: !252)
!254 = !DILocation(line: 109, column: 2, scope: !255)
!255 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 1)
!256 = !DILocation(line: 109, column: 2, scope: !257)
!257 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 2)
!258 = distinct !DILexicalBlock(scope: !252, file: !1, line: 109, column: 2)
!259 = !DILocation(line: 109, column: 2, scope: !260)
!260 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 3)
!261 = !DILocation(line: 113, column: 6, scope: !262)
!262 = distinct !DILexicalBlock(scope: !213, file: !1, line: 113, column: 6)
!263 = !DILocation(line: 113, column: 9, scope: !262)
!264 = !DILocation(line: 113, column: 21, scope: !262)
!265 = !DILocation(line: 113, column: 6, scope: !213)
!266 = !DILocation(line: 114, column: 4, scope: !262)
!267 = !DILocation(line: 114, column: 7, scope: !262)
!268 = !DILocation(line: 114, column: 20, scope: !262)
!269 = !DILocation(line: 114, column: 3, scope: !262)
!270 = !DILocation(line: 116, column: 24, scope: !213)
!271 = !DILocation(line: 116, column: 9, scope: !213)
!272 = !DILocation(line: 116, column: 7, scope: !213)
!273 = !DILocation(line: 117, column: 6, scope: !274)
!274 = distinct !DILexicalBlock(scope: !213, file: !1, line: 117, column: 6)
!275 = !DILocation(line: 117, column: 11, scope: !274)
!276 = !DILocation(line: 117, column: 6, scope: !213)
!277 = !DILocation(line: 118, column: 22, scope: !278)
!278 = distinct !DILexicalBlock(scope: !274, file: !1, line: 117, column: 20)
!279 = !DILocation(line: 118, column: 25, scope: !278)
!280 = !DILocation(line: 118, column: 3, scope: !278)
!281 = !DILocation(line: 119, column: 3, scope: !278)
!282 = !DILocation(line: 121, column: 2, scope: !213)
!283 = !DILocation(line: 121, column: 2, scope: !284)
!284 = !DILexicalBlockFile(scope: !285, file: !1, discriminator: 1)
!285 = distinct !DILexicalBlock(scope: !213, file: !1, line: 121, column: 2)
!286 = !DILocation(line: 122, column: 2, scope: !213)
!287 = !DILocation(line: 122, column: 2, scope: !288)
!288 = !DILexicalBlockFile(scope: !289, file: !1, discriminator: 1)
!289 = distinct !DILexicalBlock(scope: !213, file: !1, line: 122, column: 2)
!290 = !DILocation(line: 123, column: 19, scope: !213)
!291 = !DILocation(line: 123, column: 2, scope: !213)
!292 = !DILocation(line: 123, column: 5, scope: !213)
!293 = !DILocation(line: 123, column: 17, scope: !213)
!294 = !DILocation(line: 124, column: 2, scope: !213)
!295 = !DILocation(line: 124, column: 5, scope: !213)
!296 = !DILocation(line: 124, column: 17, scope: !213)
!297 = !DILocation(line: 125, column: 2, scope: !213)
!298 = !DILocation(line: 125, column: 5, scope: !213)
!299 = !DILocation(line: 125, column: 25, scope: !213)
!300 = !DILocation(line: 126, column: 2, scope: !213)
!301 = !DILocation(line: 126, column: 5, scope: !213)
!302 = !DILocation(line: 126, column: 18, scope: !213)
!303 = !DILocation(line: 127, column: 2, scope: !213)
!304 = !DILocation(line: 127, column: 5, scope: !213)
!305 = !DILocation(line: 127, column: 17, scope: !213)
!306 = !DILocation(line: 128, column: 2, scope: !213)
!307 = !DILocation(line: 128, column: 5, scope: !213)
!308 = !DILocation(line: 128, column: 23, scope: !213)
!309 = !DILocation(line: 129, column: 2, scope: !213)
!310 = !DILocation(line: 129, column: 5, scope: !213)
!311 = !DILocation(line: 129, column: 25, scope: !213)
!312 = !DILocation(line: 130, column: 2, scope: !213)
!313 = !DILocation(line: 130, column: 5, scope: !213)
!314 = !DILocation(line: 130, column: 13, scope: !213)
!315 = !DILocation(line: 130, column: 28, scope: !213)
!316 = !DILocation(line: 131, column: 2, scope: !213)
!317 = !DILocation(line: 131, column: 5, scope: !213)
!318 = !DILocation(line: 131, column: 13, scope: !213)
!319 = !DILocation(line: 131, column: 33, scope: !213)
!320 = !DILocation(line: 132, column: 2, scope: !213)
!321 = !DILocation(line: 133, column: 1, scope: !213)
!322 = !DILocalVariable(name: "a", arg: 1, scope: !215, file: !1, line: 157, type: !4)
!323 = !DILocation(line: 157, column: 49, scope: !215)
!324 = !DILocalVariable(name: "entry", arg: 2, scope: !215, file: !1, line: 157, type: !30)
!325 = !DILocation(line: 157, column: 74, scope: !215)
!326 = !DILocalVariable(name: "linkname", scope: !215, file: !1, line: 159, type: !80)
!327 = !DILocation(line: 159, column: 14, scope: !215)
!328 = !DILocalVariable(name: "name", scope: !215, file: !1, line: 160, type: !80)
!329 = !DILocation(line: 160, column: 14, scope: !215)
!330 = !DILocalVariable(name: "p", scope: !215, file: !1, line: 161, type: !95)
!331 = !DILocation(line: 161, column: 8, scope: !215)
!332 = !DILocalVariable(name: "pp", scope: !215, file: !1, line: 161, type: !95)
!333 = !DILocation(line: 161, column: 12, scope: !215)
!334 = !DILocalVariable(name: "shar", scope: !215, file: !1, line: 162, type: !191)
!335 = !DILocation(line: 162, column: 15, scope: !215)
!336 = !DILocation(line: 164, column: 24, scope: !215)
!337 = !DILocation(line: 164, column: 27, scope: !215)
!338 = !DILocation(line: 164, column: 9, scope: !215)
!339 = !DILocation(line: 164, column: 7, scope: !215)
!340 = !DILocation(line: 165, column: 7, scope: !341)
!341 = distinct !DILexicalBlock(scope: !215, file: !1, line: 165, column: 6)
!342 = !DILocation(line: 165, column: 13, scope: !341)
!343 = !DILocation(line: 165, column: 6, scope: !215)
!344 = !DILocation(line: 166, column: 19, scope: !345)
!345 = distinct !DILexicalBlock(scope: !341, file: !1, line: 165, column: 27)
!346 = !DILocation(line: 166, column: 25, scope: !345)
!347 = !DILocation(line: 166, column: 3, scope: !345)
!348 = !DILocation(line: 167, column: 19, scope: !345)
!349 = !DILocation(line: 167, column: 25, scope: !345)
!350 = !DILocation(line: 167, column: 3, scope: !345)
!351 = !DILocation(line: 168, column: 3, scope: !345)
!352 = !DILocation(line: 168, column: 9, scope: !345)
!353 = !DILocation(line: 168, column: 22, scope: !345)
!354 = !DILocation(line: 169, column: 2, scope: !345)
!355 = !DILocation(line: 172, column: 6, scope: !356)
!356 = distinct !DILexicalBlock(scope: !215, file: !1, line: 172, column: 6)
!357 = !DILocation(line: 172, column: 12, scope: !356)
!358 = !DILocation(line: 172, column: 6, scope: !215)
!359 = !DILocation(line: 173, column: 22, scope: !356)
!360 = !DILocation(line: 173, column: 28, scope: !356)
!361 = !DILocation(line: 173, column: 3, scope: !356)
!362 = !DILocation(line: 174, column: 36, scope: !215)
!363 = !DILocation(line: 174, column: 16, scope: !215)
!364 = !DILocation(line: 174, column: 2, scope: !215)
!365 = !DILocation(line: 174, column: 8, scope: !215)
!366 = !DILocation(line: 174, column: 14, scope: !215)
!367 = !DILocation(line: 175, column: 32, scope: !215)
!368 = !DILocation(line: 175, column: 9, scope: !215)
!369 = !DILocation(line: 175, column: 7, scope: !215)
!370 = !DILocation(line: 178, column: 32, scope: !215)
!371 = !DILocation(line: 178, column: 9, scope: !215)
!372 = !DILocation(line: 178, column: 2, scope: !215)
!373 = !DILocation(line: 181, column: 3, scope: !374)
!374 = distinct !DILexicalBlock(scope: !215, file: !1, line: 178, column: 40)
!375 = !DILocation(line: 183, column: 26, scope: !374)
!376 = !DILocation(line: 183, column: 3, scope: !374)
!377 = !DILocation(line: 185, column: 14, scope: !378)
!378 = distinct !DILexicalBlock(scope: !374, file: !1, line: 185, column: 7)
!379 = !DILocation(line: 185, column: 7, scope: !378)
!380 = !DILocation(line: 185, column: 25, scope: !378)
!381 = !DILocation(line: 185, column: 31, scope: !378)
!382 = !DILocation(line: 185, column: 42, scope: !383)
!383 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!384 = !DILocation(line: 185, column: 35, scope: !383)
!385 = !DILocation(line: 185, column: 54, scope: !383)
!386 = !DILocation(line: 185, column: 7, scope: !383)
!387 = !DILocation(line: 186, column: 4, scope: !378)
!388 = !DILocation(line: 187, column: 3, scope: !374)
!389 = !DILocation(line: 192, column: 26, scope: !374)
!390 = !DILocation(line: 192, column: 3, scope: !374)
!391 = !DILocation(line: 193, column: 3, scope: !374)
!392 = !DILocation(line: 195, column: 26, scope: !374)
!393 = !DILocation(line: 195, column: 3, scope: !374)
!394 = !DILocation(line: 196, column: 30, scope: !395)
!395 = distinct !DILexicalBlock(scope: !374, file: !1, line: 196, column: 7)
!396 = !DILocation(line: 196, column: 7, scope: !395)
!397 = !DILocation(line: 196, column: 37, scope: !395)
!398 = !DILocation(line: 196, column: 45, scope: !395)
!399 = !DILocation(line: 197, column: 29, scope: !395)
!400 = !DILocation(line: 197, column: 7, scope: !395)
!401 = !DILocation(line: 197, column: 36, scope: !395)
!402 = !DILocation(line: 196, column: 7, scope: !403)
!403 = !DILexicalBlockFile(scope: !374, file: !1, discriminator: 1)
!404 = !DILocation(line: 198, column: 23, scope: !405)
!405 = distinct !DILexicalBlock(scope: !395, file: !1, line: 197, column: 45)
!406 = !DILocation(line: 198, column: 26, scope: !405)
!407 = !DILocation(line: 198, column: 4, scope: !405)
!408 = !DILocation(line: 200, column: 4, scope: !405)
!409 = !DILocation(line: 202, column: 2, scope: !374)
!410 = !DILocation(line: 204, column: 2, scope: !215)
!411 = !DILocation(line: 205, column: 14, scope: !215)
!412 = !DILocation(line: 205, column: 20, scope: !215)
!413 = !DILocation(line: 205, column: 33, scope: !215)
!414 = !DILocation(line: 205, column: 2, scope: !215)
!415 = !DILocation(line: 208, column: 26, scope: !215)
!416 = !DILocation(line: 208, column: 32, scope: !215)
!417 = !DILocation(line: 208, column: 53, scope: !215)
!418 = !DILocation(line: 208, column: 59, scope: !215)
!419 = !DILocation(line: 208, column: 71, scope: !215)
!420 = !DILocation(line: 208, column: 2, scope: !215)
!421 = !DILocation(line: 210, column: 29, scope: !422)
!422 = distinct !DILexicalBlock(scope: !215, file: !1, line: 210, column: 6)
!423 = !DILocation(line: 210, column: 6, scope: !422)
!424 = !DILocation(line: 210, column: 36, scope: !422)
!425 = !DILocation(line: 210, column: 6, scope: !215)
!426 = !DILocation(line: 212, column: 14, scope: !427)
!427 = distinct !DILexicalBlock(scope: !422, file: !1, line: 210, column: 49)
!428 = !DILocation(line: 212, column: 7, scope: !427)
!429 = !DILocation(line: 212, column: 5, scope: !427)
!430 = !DILocation(line: 213, column: 16, scope: !427)
!431 = !DILocation(line: 213, column: 8, scope: !427)
!432 = !DILocation(line: 213, column: 6, scope: !427)
!433 = !DILocation(line: 215, column: 7, scope: !434)
!434 = distinct !DILexicalBlock(scope: !427, file: !1, line: 215, column: 7)
!435 = !DILocation(line: 215, column: 10, scope: !434)
!436 = !DILocation(line: 215, column: 7, scope: !427)
!437 = !DILocation(line: 216, column: 5, scope: !438)
!438 = distinct !DILexicalBlock(scope: !434, file: !1, line: 215, column: 19)
!439 = !DILocation(line: 216, column: 8, scope: !438)
!440 = !DILocation(line: 219, column: 15, scope: !441)
!441 = distinct !DILexicalBlock(scope: !438, file: !1, line: 219, column: 8)
!442 = !DILocation(line: 219, column: 8, scope: !441)
!443 = !DILocation(line: 219, column: 23, scope: !441)
!444 = !DILocation(line: 219, column: 8, scope: !438)
!445 = !DILocation(line: 221, column: 10, scope: !446)
!446 = distinct !DILexicalBlock(scope: !441, file: !1, line: 219, column: 29)
!447 = !DILocation(line: 221, column: 5, scope: !446)
!448 = !DILocation(line: 222, column: 4, scope: !446)
!449 = !DILocation(line: 222, column: 15, scope: !450)
!450 = !DILexicalBlockFile(scope: !451, file: !1, discriminator: 1)
!451 = distinct !DILexicalBlock(scope: !441, file: !1, line: 222, column: 15)
!452 = !DILocation(line: 222, column: 21, scope: !450)
!453 = !DILocation(line: 222, column: 30, scope: !450)
!454 = !DILocation(line: 223, column: 21, scope: !455)
!455 = distinct !DILexicalBlock(scope: !451, file: !1, line: 222, column: 39)
!456 = !DILocation(line: 223, column: 27, scope: !455)
!457 = !DILocation(line: 223, column: 5, scope: !455)
!458 = !DILocation(line: 224, column: 17, scope: !455)
!459 = !DILocation(line: 224, column: 23, scope: !455)
!460 = !DILocation(line: 224, column: 29, scope: !455)
!461 = !DILocation(line: 224, column: 5, scope: !455)
!462 = !DILocation(line: 225, column: 21, scope: !455)
!463 = !DILocation(line: 225, column: 27, scope: !455)
!464 = !DILocation(line: 225, column: 5, scope: !455)
!465 = !DILocation(line: 227, column: 22, scope: !455)
!466 = !DILocation(line: 227, column: 5, scope: !455)
!467 = !DILocation(line: 227, column: 11, scope: !455)
!468 = !DILocation(line: 227, column: 20, scope: !455)
!469 = !DILocation(line: 228, column: 4, scope: !455)
!470 = !DILocation(line: 228, column: 22, scope: !471)
!471 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 1)
!472 = distinct !DILexicalBlock(scope: !451, file: !1, line: 228, column: 15)
!473 = !DILocation(line: 228, column: 25, scope: !471)
!474 = !DILocation(line: 228, column: 31, scope: !471)
!475 = !DILocation(line: 228, column: 15, scope: !471)
!476 = !DILocation(line: 228, column: 41, scope: !471)
!477 = !DILocation(line: 230, column: 10, scope: !478)
!478 = distinct !DILexicalBlock(scope: !472, file: !1, line: 228, column: 47)
!479 = !DILocation(line: 230, column: 5, scope: !478)
!480 = !DILocation(line: 231, column: 4, scope: !478)
!481 = !DILocation(line: 231, column: 22, scope: !482)
!482 = !DILexicalBlockFile(scope: !483, file: !1, discriminator: 1)
!483 = distinct !DILexicalBlock(scope: !472, file: !1, line: 231, column: 15)
!484 = !DILocation(line: 231, column: 15, scope: !482)
!485 = !DILocation(line: 231, column: 34, scope: !482)
!486 = !DILocation(line: 231, column: 40, scope: !482)
!487 = !DILocation(line: 231, column: 27, scope: !488)
!488 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 3)
!489 = !DILocation(line: 231, column: 25, scope: !482)
!490 = !DILocation(line: 231, column: 50, scope: !482)
!491 = !DILocation(line: 232, column: 16, scope: !483)
!492 = !DILocation(line: 232, column: 19, scope: !483)
!493 = !DILocation(line: 232, column: 25, scope: !483)
!494 = !DILocation(line: 232, column: 42, scope: !483)
!495 = !DILocation(line: 232, column: 35, scope: !483)
!496 = !DILocation(line: 232, column: 8, scope: !482)
!497 = !DILocation(line: 232, column: 46, scope: !483)
!498 = !DILocation(line: 231, column: 15, scope: !499)
!499 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 2)
!500 = !DILocation(line: 234, column: 10, scope: !501)
!501 = distinct !DILexicalBlock(scope: !483, file: !1, line: 232, column: 52)
!502 = !DILocation(line: 234, column: 5, scope: !501)
!503 = !DILocation(line: 235, column: 4, scope: !501)
!504 = !DILocation(line: 236, column: 21, scope: !505)
!505 = distinct !DILexicalBlock(scope: !483, file: !1, line: 235, column: 11)
!506 = !DILocation(line: 236, column: 27, scope: !505)
!507 = !DILocation(line: 236, column: 5, scope: !505)
!508 = !DILocation(line: 237, column: 17, scope: !505)
!509 = !DILocation(line: 237, column: 23, scope: !505)
!510 = !DILocation(line: 237, column: 29, scope: !505)
!511 = !DILocation(line: 237, column: 5, scope: !505)
!512 = !DILocation(line: 238, column: 21, scope: !505)
!513 = !DILocation(line: 238, column: 27, scope: !505)
!514 = !DILocation(line: 238, column: 5, scope: !505)
!515 = !DILocation(line: 240, column: 22, scope: !505)
!516 = !DILocation(line: 240, column: 5, scope: !505)
!517 = !DILocation(line: 240, column: 11, scope: !505)
!518 = !DILocation(line: 240, column: 20, scope: !505)
!519 = !DILocation(line: 242, column: 3, scope: !438)
!520 = !DILocation(line: 243, column: 9, scope: !521)
!521 = distinct !DILexicalBlock(scope: !434, file: !1, line: 242, column: 10)
!522 = !DILocation(line: 243, column: 4, scope: !521)
!523 = !DILocation(line: 245, column: 2, scope: !427)
!524 = !DILocation(line: 248, column: 2, scope: !215)
!525 = !DILocation(line: 248, column: 8, scope: !215)
!526 = !DILocation(line: 248, column: 17, scope: !215)
!527 = !DILocation(line: 249, column: 41, scope: !528)
!528 = distinct !DILexicalBlock(scope: !215, file: !1, line: 249, column: 6)
!529 = !DILocation(line: 249, column: 18, scope: !528)
!530 = !DILocation(line: 249, column: 16, scope: !528)
!531 = !DILocation(line: 249, column: 49, scope: !528)
!532 = !DILocation(line: 249, column: 6, scope: !215)
!533 = !DILocation(line: 250, column: 19, scope: !534)
!534 = distinct !DILexicalBlock(scope: !528, file: !1, line: 249, column: 58)
!535 = !DILocation(line: 250, column: 25, scope: !534)
!536 = !DILocation(line: 250, column: 3, scope: !534)
!537 = !DILocation(line: 251, column: 15, scope: !534)
!538 = !DILocation(line: 251, column: 21, scope: !534)
!539 = !DILocation(line: 251, column: 27, scope: !534)
!540 = !DILocation(line: 251, column: 3, scope: !534)
!541 = !DILocation(line: 252, column: 27, scope: !534)
!542 = !DILocation(line: 252, column: 33, scope: !534)
!543 = !DILocation(line: 253, column: 7, scope: !534)
!544 = !DILocation(line: 253, column: 13, scope: !534)
!545 = !DILocation(line: 253, column: 25, scope: !534)
!546 = !DILocation(line: 252, column: 3, scope: !534)
!547 = !DILocation(line: 254, column: 2, scope: !534)
!548 = !DILocation(line: 254, column: 47, scope: !549)
!549 = !DILexicalBlockFile(scope: !550, file: !1, discriminator: 1)
!550 = distinct !DILexicalBlock(scope: !528, file: !1, line: 254, column: 13)
!551 = !DILocation(line: 254, column: 25, scope: !549)
!552 = !DILocation(line: 254, column: 23, scope: !549)
!553 = !DILocation(line: 254, column: 55, scope: !549)
!554 = !DILocation(line: 254, column: 13, scope: !549)
!555 = !DILocation(line: 255, column: 19, scope: !556)
!556 = distinct !DILexicalBlock(scope: !550, file: !1, line: 254, column: 64)
!557 = !DILocation(line: 255, column: 25, scope: !556)
!558 = !DILocation(line: 255, column: 3, scope: !556)
!559 = !DILocation(line: 256, column: 15, scope: !556)
!560 = !DILocation(line: 256, column: 21, scope: !556)
!561 = !DILocation(line: 256, column: 27, scope: !556)
!562 = !DILocation(line: 256, column: 3, scope: !556)
!563 = !DILocation(line: 257, column: 27, scope: !556)
!564 = !DILocation(line: 257, column: 33, scope: !556)
!565 = !DILocation(line: 258, column: 7, scope: !556)
!566 = !DILocation(line: 258, column: 13, scope: !556)
!567 = !DILocation(line: 258, column: 25, scope: !556)
!568 = !DILocation(line: 257, column: 3, scope: !556)
!569 = !DILocation(line: 259, column: 2, scope: !556)
!570 = !DILocation(line: 260, column: 33, scope: !571)
!571 = distinct !DILexicalBlock(scope: !550, file: !1, line: 259, column: 9)
!572 = !DILocation(line: 260, column: 10, scope: !571)
!573 = !DILocation(line: 260, column: 3, scope: !571)
!574 = !DILocation(line: 262, column: 27, scope: !575)
!575 = distinct !DILexicalBlock(scope: !576, file: !1, line: 262, column: 8)
!576 = distinct !DILexicalBlock(scope: !571, file: !1, line: 260, column: 41)
!577 = !DILocation(line: 262, column: 8, scope: !575)
!578 = !DILocation(line: 262, column: 34, scope: !575)
!579 = !DILocation(line: 262, column: 8, scope: !576)
!580 = !DILocation(line: 264, column: 29, scope: !581)
!581 = distinct !DILexicalBlock(scope: !575, file: !1, line: 262, column: 40)
!582 = !DILocation(line: 264, column: 35, scope: !581)
!583 = !DILocation(line: 266, column: 9, scope: !581)
!584 = !DILocation(line: 266, column: 15, scope: !581)
!585 = !DILocation(line: 266, column: 27, scope: !581)
!586 = !DILocation(line: 266, column: 30, scope: !581)
!587 = !DILocation(line: 266, column: 36, scope: !581)
!588 = !DILocation(line: 266, column: 48, scope: !581)
!589 = !DILocation(line: 264, column: 5, scope: !581)
!590 = !DILocation(line: 267, column: 4, scope: !581)
!591 = !DILocation(line: 268, column: 9, scope: !592)
!592 = distinct !DILexicalBlock(scope: !593, file: !1, line: 268, column: 9)
!593 = distinct !DILexicalBlock(scope: !575, file: !1, line: 267, column: 11)
!594 = !DILocation(line: 268, column: 15, scope: !592)
!595 = !DILocation(line: 268, column: 9, scope: !593)
!596 = !DILocalVariable(name: "mode", scope: !597, file: !1, line: 269, type: !13)
!597 = distinct !DILexicalBlock(scope: !592, file: !1, line: 268, column: 21)
!598 = !DILocation(line: 269, column: 19, scope: !597)
!599 = !DILocation(line: 269, column: 45, scope: !597)
!600 = !DILocation(line: 269, column: 26, scope: !597)
!601 = !DILocation(line: 269, column: 52, scope: !597)
!602 = !DILocation(line: 270, column: 30, scope: !597)
!603 = !DILocation(line: 270, column: 36, scope: !597)
!604 = !DILocation(line: 272, column: 10, scope: !597)
!605 = !DILocation(line: 272, column: 16, scope: !597)
!606 = !DILocation(line: 272, column: 28, scope: !597)
!607 = !DILocation(line: 270, column: 6, scope: !597)
!608 = !DILocation(line: 273, column: 30, scope: !597)
!609 = !DILocation(line: 273, column: 36, scope: !597)
!610 = !DILocation(line: 274, column: 23, scope: !597)
!611 = !DILocation(line: 273, column: 6, scope: !597)
!612 = !DILocation(line: 275, column: 18, scope: !597)
!613 = !DILocation(line: 275, column: 24, scope: !597)
!614 = !DILocation(line: 275, column: 30, scope: !597)
!615 = !DILocation(line: 275, column: 6, scope: !597)
!616 = !DILocation(line: 276, column: 22, scope: !597)
!617 = !DILocation(line: 276, column: 28, scope: !597)
!618 = !DILocation(line: 276, column: 6, scope: !597)
!619 = !DILocation(line: 277, column: 5, scope: !597)
!620 = !DILocation(line: 278, column: 30, scope: !621)
!621 = distinct !DILexicalBlock(scope: !592, file: !1, line: 277, column: 12)
!622 = !DILocation(line: 278, column: 36, scope: !621)
!623 = !DILocation(line: 280, column: 10, scope: !621)
!624 = !DILocation(line: 280, column: 16, scope: !621)
!625 = !DILocation(line: 280, column: 28, scope: !621)
!626 = !DILocation(line: 278, column: 6, scope: !621)
!627 = !DILocation(line: 282, column: 5, scope: !593)
!628 = !DILocation(line: 282, column: 11, scope: !593)
!629 = !DILocation(line: 282, column: 20, scope: !593)
!630 = !DILocation(line: 283, column: 5, scope: !593)
!631 = !DILocation(line: 283, column: 11, scope: !593)
!632 = !DILocation(line: 283, column: 23, scope: !593)
!633 = !DILocation(line: 284, column: 5, scope: !593)
!634 = !DILocation(line: 284, column: 11, scope: !593)
!635 = !DILocation(line: 284, column: 18, scope: !593)
!636 = !DILocation(line: 286, column: 4, scope: !576)
!637 = !DILocation(line: 288, column: 28, scope: !576)
!638 = !DILocation(line: 288, column: 34, scope: !576)
!639 = !DILocation(line: 290, column: 8, scope: !576)
!640 = !DILocation(line: 290, column: 14, scope: !576)
!641 = !DILocation(line: 290, column: 26, scope: !576)
!642 = !DILocation(line: 288, column: 4, scope: !576)
!643 = !DILocation(line: 292, column: 8, scope: !644)
!644 = distinct !DILexicalBlock(scope: !576, file: !1, line: 292, column: 8)
!645 = !DILocation(line: 292, column: 14, scope: !644)
!646 = !DILocation(line: 292, column: 23, scope: !644)
!647 = !DILocation(line: 292, column: 8, scope: !576)
!648 = !DILocation(line: 293, column: 10, scope: !644)
!649 = !DILocation(line: 293, column: 16, scope: !644)
!650 = !DILocation(line: 293, column: 5, scope: !644)
!651 = !DILocation(line: 295, column: 28, scope: !576)
!652 = !DILocation(line: 295, column: 21, scope: !576)
!653 = !DILocation(line: 295, column: 4, scope: !576)
!654 = !DILocation(line: 295, column: 10, scope: !576)
!655 = !DILocation(line: 295, column: 19, scope: !576)
!656 = !DILocation(line: 297, column: 17, scope: !576)
!657 = !DILocation(line: 297, column: 23, scope: !576)
!658 = !DILocation(line: 297, column: 9, scope: !576)
!659 = !DILocation(line: 297, column: 7, scope: !576)
!660 = !DILocation(line: 298, column: 8, scope: !661)
!661 = distinct !DILexicalBlock(scope: !576, file: !1, line: 298, column: 8)
!662 = !DILocation(line: 298, column: 11, scope: !661)
!663 = !DILocation(line: 298, column: 19, scope: !661)
!664 = !DILocation(line: 298, column: 22, scope: !665)
!665 = !DILexicalBlockFile(scope: !661, file: !1, discriminator: 1)
!666 = !DILocation(line: 298, column: 28, scope: !665)
!667 = !DILocation(line: 298, column: 8, scope: !665)
!668 = !DILocation(line: 299, column: 6, scope: !661)
!669 = !DILocation(line: 299, column: 9, scope: !661)
!670 = !DILocation(line: 299, column: 5, scope: !661)
!671 = !DILocation(line: 304, column: 4, scope: !576)
!672 = !DILocation(line: 306, column: 28, scope: !576)
!673 = !DILocation(line: 306, column: 34, scope: !576)
!674 = !DILocation(line: 307, column: 23, scope: !576)
!675 = !DILocation(line: 307, column: 29, scope: !576)
!676 = !DILocation(line: 307, column: 41, scope: !576)
!677 = !DILocation(line: 306, column: 4, scope: !576)
!678 = !DILocation(line: 308, column: 4, scope: !576)
!679 = !DILocation(line: 310, column: 28, scope: !576)
!680 = !DILocation(line: 310, column: 34, scope: !576)
!681 = !DILocation(line: 311, column: 32, scope: !576)
!682 = !DILocation(line: 311, column: 38, scope: !576)
!683 = !DILocation(line: 311, column: 50, scope: !576)
!684 = !DILocation(line: 312, column: 43, scope: !576)
!685 = !DILocation(line: 312, column: 19, scope: !576)
!686 = !DILocation(line: 313, column: 43, scope: !576)
!687 = !DILocation(line: 313, column: 19, scope: !576)
!688 = !DILocation(line: 310, column: 4, scope: !576)
!689 = !DILocation(line: 314, column: 4, scope: !576)
!690 = !DILocation(line: 316, column: 28, scope: !576)
!691 = !DILocation(line: 316, column: 34, scope: !576)
!692 = !DILocation(line: 317, column: 32, scope: !576)
!693 = !DILocation(line: 317, column: 38, scope: !576)
!694 = !DILocation(line: 317, column: 50, scope: !576)
!695 = !DILocation(line: 318, column: 43, scope: !576)
!696 = !DILocation(line: 318, column: 19, scope: !576)
!697 = !DILocation(line: 319, column: 43, scope: !576)
!698 = !DILocation(line: 319, column: 19, scope: !576)
!699 = !DILocation(line: 316, column: 4, scope: !576)
!700 = !DILocation(line: 320, column: 4, scope: !576)
!701 = !DILocation(line: 322, column: 4, scope: !576)
!702 = !DILocation(line: 326, column: 2, scope: !215)
!703 = !DILocation(line: 327, column: 1, scope: !215)
!704 = !DILocalVariable(name: "a", arg: 1, scope: !229, file: !1, line: 589, type: !4)
!705 = !DILocation(line: 589, column: 48, scope: !229)
!706 = !DILocalVariable(name: "shar", scope: !229, file: !1, line: 591, type: !191)
!707 = !DILocation(line: 591, column: 15, scope: !229)
!708 = !DILocalVariable(name: "ret", scope: !229, file: !1, line: 592, type: !23)
!709 = !DILocation(line: 592, column: 6, scope: !229)
!710 = !DILocation(line: 599, column: 24, scope: !229)
!711 = !DILocation(line: 599, column: 27, scope: !229)
!712 = !DILocation(line: 599, column: 9, scope: !229)
!713 = !DILocation(line: 599, column: 7, scope: !229)
!714 = !DILocation(line: 607, column: 6, scope: !715)
!715 = distinct !DILexicalBlock(scope: !229, file: !1, line: 607, column: 6)
!716 = !DILocation(line: 607, column: 12, scope: !715)
!717 = !DILocation(line: 607, column: 25, scope: !715)
!718 = !DILocation(line: 607, column: 6, scope: !229)
!719 = !DILocation(line: 608, column: 3, scope: !715)
!720 = !DILocation(line: 610, column: 18, scope: !229)
!721 = !DILocation(line: 610, column: 24, scope: !229)
!722 = !DILocation(line: 610, column: 2, scope: !229)
!723 = !DILocation(line: 612, column: 31, scope: !229)
!724 = !DILocation(line: 612, column: 34, scope: !229)
!725 = !DILocation(line: 612, column: 40, scope: !229)
!726 = !DILocation(line: 612, column: 45, scope: !229)
!727 = !DILocation(line: 612, column: 48, scope: !229)
!728 = !DILocation(line: 612, column: 54, scope: !229)
!729 = !DILocation(line: 612, column: 59, scope: !229)
!730 = !DILocation(line: 612, column: 8, scope: !229)
!731 = !DILocation(line: 612, column: 6, scope: !229)
!732 = !DILocation(line: 613, column: 6, scope: !733)
!733 = distinct !DILexicalBlock(scope: !229, file: !1, line: 613, column: 6)
!734 = !DILocation(line: 613, column: 10, scope: !733)
!735 = !DILocation(line: 613, column: 6, scope: !229)
!736 = !DILocation(line: 614, column: 3, scope: !733)
!737 = !DILocation(line: 617, column: 41, scope: !229)
!738 = !DILocation(line: 617, column: 44, scope: !229)
!739 = !DILocation(line: 617, column: 2, scope: !229)
!740 = !DILocation(line: 623, column: 2, scope: !229)
!741 = !DILocation(line: 624, column: 1, scope: !229)
!742 = !DILocalVariable(name: "a", arg: 1, scope: !230, file: !1, line: 627, type: !4)
!743 = !DILocation(line: 627, column: 47, scope: !230)
!744 = !DILocalVariable(name: "shar", scope: !230, file: !1, line: 629, type: !191)
!745 = !DILocation(line: 629, column: 15, scope: !230)
!746 = !DILocation(line: 631, column: 24, scope: !230)
!747 = !DILocation(line: 631, column: 27, scope: !230)
!748 = !DILocation(line: 631, column: 9, scope: !230)
!749 = !DILocation(line: 631, column: 7, scope: !230)
!750 = !DILocation(line: 632, column: 6, scope: !751)
!751 = distinct !DILexicalBlock(scope: !230, file: !1, line: 632, column: 6)
!752 = !DILocation(line: 632, column: 11, scope: !751)
!753 = !DILocation(line: 632, column: 6, scope: !230)
!754 = !DILocation(line: 633, column: 3, scope: !751)
!755 = !DILocation(line: 635, column: 21, scope: !230)
!756 = !DILocation(line: 635, column: 27, scope: !230)
!757 = !DILocation(line: 635, column: 2, scope: !230)
!758 = !DILocation(line: 636, column: 7, scope: !230)
!759 = !DILocation(line: 636, column: 13, scope: !230)
!760 = !DILocation(line: 636, column: 2, scope: !230)
!761 = !DILocation(line: 637, column: 24, scope: !230)
!762 = !DILocation(line: 637, column: 30, scope: !230)
!763 = !DILocation(line: 637, column: 2, scope: !230)
!764 = !DILocation(line: 638, column: 24, scope: !230)
!765 = !DILocation(line: 638, column: 30, scope: !230)
!766 = !DILocation(line: 638, column: 2, scope: !230)
!767 = !DILocation(line: 639, column: 7, scope: !230)
!768 = !DILocation(line: 639, column: 2, scope: !230)
!769 = !DILocation(line: 640, column: 2, scope: !230)
!770 = !DILocation(line: 640, column: 5, scope: !230)
!771 = !DILocation(line: 640, column: 17, scope: !230)
!772 = !DILocation(line: 641, column: 2, scope: !230)
!773 = !DILocation(line: 642, column: 1, scope: !230)
!774 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 330, type: !4)
!775 = !DILocation(line: 330, column: 51, scope: !220)
!776 = !DILocalVariable(name: "buff", arg: 2, scope: !220, file: !1, line: 330, type: !43)
!777 = !DILocation(line: 330, column: 66, scope: !220)
!778 = !DILocalVariable(name: "n", arg: 3, scope: !220, file: !1, line: 330, type: !45)
!779 = !DILocation(line: 330, column: 79, scope: !220)
!780 = !DILocalVariable(name: "shar", scope: !220, file: !1, line: 333, type: !191)
!781 = !DILocation(line: 333, column: 15, scope: !220)
!782 = !DILocalVariable(name: "src", scope: !220, file: !1, line: 334, type: !80)
!783 = !DILocation(line: 334, column: 14, scope: !220)
!784 = !DILocalVariable(name: "buf", scope: !220, file: !1, line: 335, type: !95)
!785 = !DILocation(line: 335, column: 8, scope: !220)
!786 = !DILocalVariable(name: "buf_end", scope: !220, file: !1, line: 335, type: !95)
!787 = !DILocation(line: 335, column: 14, scope: !220)
!788 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 336, type: !23)
!789 = !DILocation(line: 336, column: 6, scope: !220)
!790 = !DILocalVariable(name: "written", scope: !220, file: !1, line: 337, type: !45)
!791 = !DILocation(line: 337, column: 9, scope: !220)
!792 = !DILocation(line: 337, column: 19, scope: !220)
!793 = !DILocation(line: 339, column: 24, scope: !220)
!794 = !DILocation(line: 339, column: 27, scope: !220)
!795 = !DILocation(line: 339, column: 9, scope: !220)
!796 = !DILocation(line: 339, column: 7, scope: !220)
!797 = !DILocation(line: 340, column: 7, scope: !798)
!798 = distinct !DILexicalBlock(scope: !220, file: !1, line: 340, column: 6)
!799 = !DILocation(line: 340, column: 13, scope: !798)
!800 = !DILocation(line: 340, column: 22, scope: !798)
!801 = !DILocation(line: 340, column: 25, scope: !802)
!802 = !DILexicalBlockFile(scope: !798, file: !1, discriminator: 1)
!803 = !DILocation(line: 340, column: 27, scope: !802)
!804 = !DILocation(line: 340, column: 6, scope: !802)
!805 = !DILocation(line: 341, column: 3, scope: !798)
!806 = !DILocation(line: 343, column: 22, scope: !220)
!807 = !DILocation(line: 343, column: 6, scope: !220)
!808 = !DILocation(line: 352, column: 29, scope: !809)
!809 = distinct !DILexicalBlock(scope: !220, file: !1, line: 352, column: 6)
!810 = !DILocation(line: 352, column: 35, scope: !809)
!811 = !DILocation(line: 352, column: 6, scope: !809)
!812 = !DILocation(line: 352, column: 54, scope: !809)
!813 = !DILocation(line: 352, column: 6, scope: !220)
!814 = !DILocation(line: 353, column: 22, scope: !815)
!815 = distinct !DILexicalBlock(scope: !809, file: !1, line: 352, column: 63)
!816 = !DILocation(line: 353, column: 25, scope: !815)
!817 = !DILocation(line: 353, column: 3, scope: !815)
!818 = !DILocation(line: 354, column: 3, scope: !815)
!819 = !DILocation(line: 357, column: 6, scope: !820)
!820 = distinct !DILexicalBlock(scope: !220, file: !1, line: 357, column: 6)
!821 = !DILocation(line: 357, column: 12, scope: !820)
!822 = !DILocation(line: 357, column: 17, scope: !820)
!823 = !DILocation(line: 357, column: 24, scope: !820)
!824 = !DILocation(line: 357, column: 6, scope: !220)
!825 = !DILocation(line: 358, column: 32, scope: !826)
!826 = distinct !DILexicalBlock(scope: !820, file: !1, line: 357, column: 35)
!827 = !DILocation(line: 358, column: 35, scope: !826)
!828 = !DILocation(line: 358, column: 41, scope: !826)
!829 = !DILocation(line: 358, column: 46, scope: !826)
!830 = !DILocation(line: 359, column: 7, scope: !826)
!831 = !DILocation(line: 359, column: 13, scope: !826)
!832 = !DILocation(line: 359, column: 18, scope: !826)
!833 = !DILocation(line: 358, column: 9, scope: !826)
!834 = !DILocation(line: 358, column: 7, scope: !826)
!835 = !DILocation(line: 360, column: 7, scope: !836)
!836 = distinct !DILexicalBlock(scope: !826, file: !1, line: 360, column: 7)
!837 = !DILocation(line: 360, column: 11, scope: !836)
!838 = !DILocation(line: 360, column: 7, scope: !826)
!839 = !DILocation(line: 361, column: 4, scope: !836)
!840 = !DILocation(line: 362, column: 3, scope: !826)
!841 = !DILocation(line: 363, column: 2, scope: !826)
!842 = !DILocation(line: 364, column: 8, scope: !220)
!843 = !DILocation(line: 364, column: 14, scope: !220)
!844 = !DILocation(line: 364, column: 19, scope: !220)
!845 = !DILocation(line: 364, column: 23, scope: !220)
!846 = !DILocation(line: 364, column: 29, scope: !220)
!847 = !DILocation(line: 364, column: 34, scope: !220)
!848 = !DILocation(line: 364, column: 21, scope: !220)
!849 = !DILocation(line: 364, column: 6, scope: !220)
!850 = !DILocation(line: 365, column: 12, scope: !220)
!851 = !DILocation(line: 365, column: 18, scope: !220)
!852 = !DILocation(line: 365, column: 23, scope: !220)
!853 = !DILocation(line: 365, column: 25, scope: !220)
!854 = !DILocation(line: 365, column: 10, scope: !220)
!855 = !DILocation(line: 367, column: 6, scope: !856)
!856 = distinct !DILexicalBlock(scope: !220, file: !1, line: 367, column: 6)
!857 = !DILocation(line: 367, column: 12, scope: !856)
!858 = !DILocation(line: 367, column: 6, scope: !220)
!859 = !DILocation(line: 368, column: 7, scope: !860)
!860 = distinct !DILexicalBlock(scope: !856, file: !1, line: 367, column: 25)
!861 = !DILocation(line: 368, column: 10, scope: !860)
!862 = !DILocation(line: 369, column: 3, scope: !860)
!863 = !DILocation(line: 369, column: 9, scope: !860)
!864 = !DILocation(line: 369, column: 21, scope: !860)
!865 = !DILocation(line: 370, column: 2, scope: !860)
!866 = !DILocation(line: 372, column: 2, scope: !220)
!867 = !DILocation(line: 372, column: 10, scope: !868)
!868 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 1)
!869 = !DILocation(line: 372, column: 13, scope: !868)
!870 = !DILocation(line: 372, column: 2, scope: !868)
!871 = !DILocation(line: 373, column: 21, scope: !872)
!872 = distinct !DILexicalBlock(scope: !873, file: !1, line: 373, column: 7)
!873 = distinct !DILexicalBlock(scope: !220, file: !1, line: 372, column: 19)
!874 = !DILocation(line: 373, column: 17, scope: !872)
!875 = !DILocation(line: 373, column: 12, scope: !872)
!876 = !DILocation(line: 373, column: 15, scope: !872)
!877 = !DILocation(line: 373, column: 7, scope: !872)
!878 = !DILocation(line: 373, column: 25, scope: !872)
!879 = !DILocation(line: 373, column: 7, scope: !873)
!880 = !DILocation(line: 374, column: 8, scope: !881)
!881 = distinct !DILexicalBlock(scope: !882, file: !1, line: 374, column: 8)
!882 = distinct !DILexicalBlock(scope: !872, file: !1, line: 373, column: 34)
!883 = !DILocation(line: 374, column: 10, scope: !881)
!884 = !DILocation(line: 374, column: 8, scope: !882)
!885 = !DILocation(line: 375, column: 5, scope: !881)
!886 = !DILocation(line: 375, column: 11, scope: !881)
!887 = !DILocation(line: 375, column: 23, scope: !881)
!888 = !DILocation(line: 377, column: 9, scope: !881)
!889 = !DILocation(line: 377, column: 12, scope: !881)
!890 = !DILocation(line: 378, column: 3, scope: !882)
!891 = !DILocation(line: 380, column: 7, scope: !892)
!892 = distinct !DILexicalBlock(scope: !873, file: !1, line: 380, column: 7)
!893 = !DILocation(line: 380, column: 14, scope: !892)
!894 = !DILocation(line: 380, column: 11, scope: !892)
!895 = !DILocation(line: 380, column: 7, scope: !873)
!896 = !DILocation(line: 381, column: 24, scope: !897)
!897 = distinct !DILexicalBlock(scope: !892, file: !1, line: 380, column: 23)
!898 = !DILocation(line: 381, column: 30, scope: !897)
!899 = !DILocation(line: 381, column: 36, scope: !897)
!900 = !DILocation(line: 381, column: 41, scope: !897)
!901 = !DILocation(line: 381, column: 28, scope: !897)
!902 = !DILocation(line: 381, column: 4, scope: !897)
!903 = !DILocation(line: 381, column: 10, scope: !897)
!904 = !DILocation(line: 381, column: 15, scope: !897)
!905 = !DILocation(line: 381, column: 22, scope: !897)
!906 = !DILocation(line: 382, column: 33, scope: !897)
!907 = !DILocation(line: 382, column: 36, scope: !897)
!908 = !DILocation(line: 382, column: 42, scope: !897)
!909 = !DILocation(line: 382, column: 47, scope: !897)
!910 = !DILocation(line: 383, column: 8, scope: !897)
!911 = !DILocation(line: 383, column: 14, scope: !897)
!912 = !DILocation(line: 383, column: 19, scope: !897)
!913 = !DILocation(line: 382, column: 10, scope: !897)
!914 = !DILocation(line: 382, column: 8, scope: !897)
!915 = !DILocation(line: 384, column: 8, scope: !916)
!916 = distinct !DILexicalBlock(scope: !897, file: !1, line: 384, column: 8)
!917 = !DILocation(line: 384, column: 12, scope: !916)
!918 = !DILocation(line: 384, column: 8, scope: !897)
!919 = !DILocation(line: 385, column: 5, scope: !916)
!920 = !DILocation(line: 386, column: 4, scope: !897)
!921 = !DILocation(line: 387, column: 10, scope: !897)
!922 = !DILocation(line: 387, column: 16, scope: !897)
!923 = !DILocation(line: 387, column: 21, scope: !897)
!924 = !DILocation(line: 387, column: 8, scope: !897)
!925 = !DILocation(line: 388, column: 3, scope: !897)
!926 = !DILocation(line: 372, column: 2, scope: !927)
!927 = !DILexicalBlockFile(scope: !220, file: !1, discriminator: 2)
!928 = !DILocation(line: 391, column: 22, scope: !220)
!929 = !DILocation(line: 391, column: 28, scope: !220)
!930 = !DILocation(line: 391, column: 34, scope: !220)
!931 = !DILocation(line: 391, column: 39, scope: !220)
!932 = !DILocation(line: 391, column: 26, scope: !220)
!933 = !DILocation(line: 391, column: 2, scope: !220)
!934 = !DILocation(line: 391, column: 8, scope: !220)
!935 = !DILocation(line: 391, column: 13, scope: !220)
!936 = !DILocation(line: 391, column: 20, scope: !220)
!937 = !DILocation(line: 393, column: 10, scope: !220)
!938 = !DILocation(line: 393, column: 2, scope: !220)
!939 = !DILocation(line: 394, column: 1, scope: !220)
!940 = !DILocalVariable(name: "a", arg: 1, scope: !228, file: !1, line: 511, type: !4)
!941 = !DILocation(line: 511, column: 55, scope: !228)
!942 = !DILocalVariable(name: "g", scope: !228, file: !1, line: 513, type: !80)
!943 = !DILocation(line: 513, column: 14, scope: !228)
!944 = !DILocalVariable(name: "p", scope: !228, file: !1, line: 513, type: !80)
!945 = !DILocation(line: 513, column: 18, scope: !228)
!946 = !DILocalVariable(name: "u", scope: !228, file: !1, line: 513, type: !80)
!947 = !DILocation(line: 513, column: 22, scope: !228)
!948 = !DILocalVariable(name: "shar", scope: !228, file: !1, line: 514, type: !191)
!949 = !DILocation(line: 514, column: 15, scope: !228)
!950 = !DILocalVariable(name: "ret", scope: !228, file: !1, line: 515, type: !23)
!951 = !DILocation(line: 515, column: 6, scope: !228)
!952 = !DILocation(line: 517, column: 24, scope: !228)
!953 = !DILocation(line: 517, column: 27, scope: !228)
!954 = !DILocation(line: 517, column: 9, scope: !228)
!955 = !DILocation(line: 517, column: 7, scope: !228)
!956 = !DILocation(line: 518, column: 6, scope: !957)
!957 = distinct !DILexicalBlock(scope: !228, file: !1, line: 518, column: 6)
!958 = !DILocation(line: 518, column: 12, scope: !957)
!959 = !DILocation(line: 518, column: 18, scope: !957)
!960 = !DILocation(line: 518, column: 6, scope: !228)
!961 = !DILocation(line: 519, column: 3, scope: !957)
!962 = !DILocation(line: 521, column: 6, scope: !963)
!963 = distinct !DILexicalBlock(scope: !228, file: !1, line: 521, column: 6)
!964 = !DILocation(line: 521, column: 12, scope: !963)
!965 = !DILocation(line: 521, column: 6, scope: !228)
!966 = !DILocation(line: 523, column: 7, scope: !967)
!967 = distinct !DILexicalBlock(scope: !968, file: !1, line: 523, column: 7)
!968 = distinct !DILexicalBlock(scope: !963, file: !1, line: 521, column: 18)
!969 = !DILocation(line: 523, column: 13, scope: !967)
!970 = !DILocation(line: 523, column: 7, scope: !968)
!971 = !DILocation(line: 524, column: 8, scope: !972)
!972 = distinct !DILexicalBlock(scope: !973, file: !1, line: 524, column: 8)
!973 = distinct !DILexicalBlock(scope: !967, file: !1, line: 523, column: 23)
!974 = !DILocation(line: 524, column: 14, scope: !972)
!975 = !DILocation(line: 524, column: 21, scope: !972)
!976 = !DILocation(line: 524, column: 8, scope: !973)
!977 = !DILocation(line: 525, column: 5, scope: !972)
!978 = !DILocalVariable(name: "r", scope: !979, file: !1, line: 525, type: !23)
!979 = distinct !DILexicalBlock(scope: !972, file: !1, line: 525, column: 5)
!980 = !DILocation(line: 525, column: 5, scope: !979)
!981 = !DILocation(line: 525, column: 5, scope: !982)
!982 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 1)
!983 = !DILocation(line: 525, column: 5, scope: !984)
!984 = !DILexicalBlockFile(scope: !985, file: !1, discriminator: 2)
!985 = distinct !DILexicalBlock(scope: !979, file: !1, line: 525, column: 5)
!986 = !DILocation(line: 525, column: 5, scope: !987)
!987 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 3)
!988 = !DILocation(line: 525, column: 5, scope: !989)
!989 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 4)
!990 = !DILocation(line: 527, column: 20, scope: !973)
!991 = !DILocation(line: 527, column: 26, scope: !973)
!992 = !DILocation(line: 527, column: 4, scope: !973)
!993 = !DILocation(line: 528, column: 20, scope: !973)
!994 = !DILocation(line: 528, column: 26, scope: !973)
!995 = !DILocation(line: 528, column: 4, scope: !973)
!996 = !DILocation(line: 529, column: 3, scope: !973)
!997 = !DILocation(line: 535, column: 27, scope: !968)
!998 = !DILocation(line: 535, column: 33, scope: !968)
!999 = !DILocation(line: 536, column: 41, scope: !968)
!1000 = !DILocation(line: 536, column: 47, scope: !968)
!1001 = !DILocation(line: 536, column: 22, scope: !968)
!1002 = !DILocation(line: 536, column: 54, scope: !968)
!1003 = !DILocation(line: 535, column: 3, scope: !968)
!1004 = !DILocation(line: 537, column: 15, scope: !968)
!1005 = !DILocation(line: 537, column: 21, scope: !968)
!1006 = !DILocation(line: 537, column: 50, scope: !968)
!1007 = !DILocation(line: 537, column: 56, scope: !968)
!1008 = !DILocation(line: 537, column: 27, scope: !968)
!1009 = !DILocation(line: 537, column: 3, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !968, file: !1, discriminator: 1)
!1011 = !DILocation(line: 538, column: 19, scope: !968)
!1012 = !DILocation(line: 538, column: 25, scope: !968)
!1013 = !DILocation(line: 538, column: 3, scope: !968)
!1014 = !DILocation(line: 540, column: 27, scope: !968)
!1015 = !DILocation(line: 540, column: 33, scope: !968)
!1016 = !DILocation(line: 540, column: 7, scope: !968)
!1017 = !DILocation(line: 540, column: 5, scope: !968)
!1018 = !DILocation(line: 541, column: 27, scope: !968)
!1019 = !DILocation(line: 541, column: 33, scope: !968)
!1020 = !DILocation(line: 541, column: 7, scope: !968)
!1021 = !DILocation(line: 541, column: 5, scope: !968)
!1022 = !DILocation(line: 542, column: 7, scope: !1023)
!1023 = distinct !DILexicalBlock(scope: !968, file: !1, line: 542, column: 7)
!1024 = !DILocation(line: 542, column: 9, scope: !1023)
!1025 = !DILocation(line: 542, column: 17, scope: !1023)
!1026 = !DILocation(line: 542, column: 20, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1023, file: !1, discriminator: 1)
!1028 = !DILocation(line: 542, column: 22, scope: !1027)
!1029 = !DILocation(line: 542, column: 7, scope: !1027)
!1030 = !DILocation(line: 543, column: 20, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !1023, file: !1, line: 542, column: 31)
!1032 = !DILocation(line: 543, column: 26, scope: !1031)
!1033 = !DILocation(line: 543, column: 4, scope: !1031)
!1034 = !DILocation(line: 544, column: 8, scope: !1035)
!1035 = distinct !DILexicalBlock(scope: !1031, file: !1, line: 544, column: 8)
!1036 = !DILocation(line: 544, column: 10, scope: !1035)
!1037 = !DILocation(line: 544, column: 8, scope: !1031)
!1038 = !DILocation(line: 545, column: 17, scope: !1035)
!1039 = !DILocation(line: 545, column: 23, scope: !1035)
!1040 = !DILocation(line: 545, column: 29, scope: !1035)
!1041 = !DILocation(line: 545, column: 5, scope: !1035)
!1042 = !DILocation(line: 546, column: 8, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !1031, file: !1, line: 546, column: 8)
!1044 = !DILocation(line: 546, column: 10, scope: !1043)
!1045 = !DILocation(line: 546, column: 8, scope: !1031)
!1046 = !DILocation(line: 547, column: 21, scope: !1047)
!1047 = distinct !DILexicalBlock(scope: !1043, file: !1, line: 546, column: 19)
!1048 = !DILocation(line: 547, column: 27, scope: !1047)
!1049 = !DILocation(line: 547, column: 5, scope: !1047)
!1050 = !DILocation(line: 548, column: 17, scope: !1047)
!1051 = !DILocation(line: 548, column: 23, scope: !1047)
!1052 = !DILocation(line: 548, column: 29, scope: !1047)
!1053 = !DILocation(line: 548, column: 5, scope: !1047)
!1054 = !DILocation(line: 549, column: 4, scope: !1047)
!1055 = !DILocation(line: 550, column: 20, scope: !1031)
!1056 = !DILocation(line: 550, column: 26, scope: !1031)
!1057 = !DILocation(line: 550, column: 4, scope: !1031)
!1058 = !DILocation(line: 551, column: 16, scope: !1031)
!1059 = !DILocation(line: 551, column: 22, scope: !1031)
!1060 = !DILocation(line: 552, column: 31, scope: !1031)
!1061 = !DILocation(line: 552, column: 37, scope: !1031)
!1062 = !DILocation(line: 552, column: 8, scope: !1031)
!1063 = !DILocation(line: 551, column: 4, scope: !1031)
!1064 = !DILocation(line: 553, column: 20, scope: !1031)
!1065 = !DILocation(line: 553, column: 26, scope: !1031)
!1066 = !DILocation(line: 553, column: 4, scope: !1031)
!1067 = !DILocation(line: 554, column: 3, scope: !1031)
!1068 = !DILocation(line: 556, column: 38, scope: !1069)
!1069 = distinct !DILexicalBlock(scope: !968, file: !1, line: 556, column: 7)
!1070 = !DILocation(line: 556, column: 44, scope: !1069)
!1071 = !DILocation(line: 556, column: 12, scope: !1069)
!1072 = !DILocation(line: 556, column: 10, scope: !1069)
!1073 = !DILocation(line: 556, column: 52, scope: !1069)
!1074 = !DILocation(line: 556, column: 7, scope: !968)
!1075 = !DILocation(line: 557, column: 28, scope: !1076)
!1076 = distinct !DILexicalBlock(scope: !1069, file: !1, line: 556, column: 61)
!1077 = !DILocation(line: 557, column: 34, scope: !1076)
!1078 = !DILocation(line: 557, column: 55, scope: !1076)
!1079 = !DILocation(line: 557, column: 4, scope: !1076)
!1080 = !DILocation(line: 558, column: 16, scope: !1076)
!1081 = !DILocation(line: 558, column: 22, scope: !1076)
!1082 = !DILocation(line: 559, column: 31, scope: !1076)
!1083 = !DILocation(line: 559, column: 37, scope: !1076)
!1084 = !DILocation(line: 559, column: 8, scope: !1076)
!1085 = !DILocation(line: 558, column: 4, scope: !1076)
!1086 = !DILocation(line: 560, column: 20, scope: !1076)
!1087 = !DILocation(line: 560, column: 26, scope: !1076)
!1088 = !DILocation(line: 560, column: 4, scope: !1076)
!1089 = !DILocation(line: 561, column: 3, scope: !1076)
!1090 = !DILocation(line: 565, column: 2, scope: !968)
!1091 = !DILocation(line: 566, column: 7, scope: !1092)
!1092 = distinct !DILexicalBlock(scope: !1093, file: !1, line: 566, column: 7)
!1093 = distinct !DILexicalBlock(scope: !963, file: !1, line: 565, column: 9)
!1094 = !DILocation(line: 566, column: 13, scope: !1092)
!1095 = !DILocation(line: 566, column: 7, scope: !1093)
!1096 = !DILocation(line: 568, column: 9, scope: !1097)
!1097 = distinct !DILexicalBlock(scope: !1098, file: !1, line: 568, column: 8)
!1098 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 566, column: 23)
!1099 = !DILocation(line: 568, column: 15, scope: !1097)
!1100 = !DILocation(line: 568, column: 8, scope: !1098)
!1101 = !DILocation(line: 569, column: 29, scope: !1097)
!1102 = !DILocation(line: 569, column: 35, scope: !1097)
!1103 = !DILocation(line: 569, column: 5, scope: !1097)
!1104 = !DILocation(line: 570, column: 20, scope: !1098)
!1105 = !DILocation(line: 570, column: 26, scope: !1098)
!1106 = !DILocation(line: 570, column: 4, scope: !1098)
!1107 = !DILocation(line: 571, column: 3, scope: !1098)
!1108 = !DILocation(line: 574, column: 21, scope: !228)
!1109 = !DILocation(line: 574, column: 27, scope: !228)
!1110 = !DILocation(line: 574, column: 2, scope: !228)
!1111 = !DILocation(line: 575, column: 2, scope: !228)
!1112 = !DILocation(line: 575, column: 8, scope: !228)
!1113 = !DILocation(line: 575, column: 14, scope: !228)
!1114 = !DILocation(line: 577, column: 6, scope: !1115)
!1115 = distinct !DILexicalBlock(scope: !228, file: !1, line: 577, column: 6)
!1116 = !DILocation(line: 577, column: 12, scope: !1115)
!1117 = !DILocation(line: 577, column: 17, scope: !1115)
!1118 = !DILocation(line: 577, column: 24, scope: !1115)
!1119 = !DILocation(line: 577, column: 6, scope: !228)
!1120 = !DILocation(line: 578, column: 3, scope: !1115)
!1121 = !DILocation(line: 580, column: 31, scope: !228)
!1122 = !DILocation(line: 580, column: 34, scope: !228)
!1123 = !DILocation(line: 580, column: 40, scope: !228)
!1124 = !DILocation(line: 580, column: 45, scope: !228)
!1125 = !DILocation(line: 580, column: 48, scope: !228)
!1126 = !DILocation(line: 580, column: 54, scope: !228)
!1127 = !DILocation(line: 580, column: 59, scope: !228)
!1128 = !DILocation(line: 580, column: 8, scope: !228)
!1129 = !DILocation(line: 580, column: 6, scope: !228)
!1130 = !DILocation(line: 581, column: 6, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !228, file: !1, line: 581, column: 6)
!1132 = !DILocation(line: 581, column: 10, scope: !1131)
!1133 = !DILocation(line: 581, column: 6, scope: !228)
!1134 = !DILocation(line: 582, column: 3, scope: !1131)
!1135 = !DILocation(line: 583, column: 2, scope: !228)
!1136 = !DILocation(line: 585, column: 2, scope: !228)
!1137 = !DILocation(line: 586, column: 1, scope: !228)
!1138 = !DILocalVariable(name: "_a", arg: 1, scope: !214, file: !1, line: 142, type: !24)
!1139 = !DILocation(line: 142, column: 52, scope: !214)
!1140 = !DILocalVariable(name: "a", scope: !214, file: !1, line: 144, type: !4)
!1141 = !DILocation(line: 144, column: 24, scope: !214)
!1142 = !DILocation(line: 144, column: 52, scope: !214)
!1143 = !DILocation(line: 144, column: 28, scope: !214)
!1144 = !DILocalVariable(name: "shar", scope: !214, file: !1, line: 145, type: !191)
!1145 = !DILocation(line: 145, column: 15, scope: !214)
!1146 = !DILocation(line: 147, column: 33, scope: !214)
!1147 = !DILocation(line: 147, column: 36, scope: !214)
!1148 = !DILocation(line: 147, column: 2, scope: !214)
!1149 = !DILocation(line: 148, column: 24, scope: !214)
!1150 = !DILocation(line: 148, column: 27, scope: !214)
!1151 = !DILocation(line: 148, column: 9, scope: !214)
!1152 = !DILocation(line: 148, column: 7, scope: !214)
!1153 = !DILocation(line: 149, column: 2, scope: !214)
!1154 = !DILocation(line: 149, column: 8, scope: !214)
!1155 = !DILocation(line: 149, column: 13, scope: !214)
!1156 = !DILocation(line: 150, column: 2, scope: !214)
!1157 = !DILocation(line: 150, column: 5, scope: !214)
!1158 = !DILocation(line: 150, column: 23, scope: !214)
!1159 = !DILocation(line: 151, column: 2, scope: !214)
!1160 = !DILocation(line: 151, column: 5, scope: !214)
!1161 = !DILocation(line: 151, column: 13, scope: !214)
!1162 = !DILocation(line: 151, column: 28, scope: !214)
!1163 = !DILocation(line: 152, column: 2, scope: !214)
!1164 = !DILocation(line: 152, column: 5, scope: !214)
!1165 = !DILocation(line: 152, column: 13, scope: !214)
!1166 = !DILocation(line: 152, column: 33, scope: !214)
!1167 = !DILocation(line: 153, column: 2, scope: !214)
!1168 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 461, type: !4)
!1169 = !DILocation(line: 461, column: 56, scope: !221)
!1170 = !DILocalVariable(name: "buff", arg: 2, scope: !221, file: !1, line: 461, type: !43)
!1171 = !DILocation(line: 461, column: 71, scope: !221)
!1172 = !DILocalVariable(name: "length", arg: 3, scope: !221, file: !1, line: 462, type: !45)
!1173 = !DILocation(line: 462, column: 12, scope: !221)
!1174 = !DILocalVariable(name: "shar", scope: !221, file: !1, line: 464, type: !191)
!1175 = !DILocation(line: 464, column: 15, scope: !221)
!1176 = !DILocalVariable(name: "src", scope: !221, file: !1, line: 465, type: !80)
!1177 = !DILocation(line: 465, column: 14, scope: !221)
!1178 = !DILocalVariable(name: "n", scope: !221, file: !1, line: 466, type: !45)
!1179 = !DILocation(line: 466, column: 9, scope: !221)
!1180 = !DILocalVariable(name: "ret", scope: !221, file: !1, line: 467, type: !23)
!1181 = !DILocation(line: 467, column: 6, scope: !221)
!1182 = !DILocation(line: 469, column: 24, scope: !221)
!1183 = !DILocation(line: 469, column: 27, scope: !221)
!1184 = !DILocation(line: 469, column: 9, scope: !221)
!1185 = !DILocation(line: 469, column: 7, scope: !221)
!1186 = !DILocation(line: 470, column: 7, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !221, file: !1, line: 470, column: 6)
!1188 = !DILocation(line: 470, column: 13, scope: !1187)
!1189 = !DILocation(line: 470, column: 6, scope: !221)
!1190 = !DILocation(line: 471, column: 3, scope: !1187)
!1191 = !DILocation(line: 472, column: 22, scope: !221)
!1192 = !DILocation(line: 472, column: 6, scope: !221)
!1193 = !DILocation(line: 474, column: 6, scope: !1194)
!1194 = distinct !DILexicalBlock(scope: !221, file: !1, line: 474, column: 6)
!1195 = !DILocation(line: 474, column: 12, scope: !1194)
!1196 = !DILocation(line: 474, column: 19, scope: !1194)
!1197 = !DILocation(line: 474, column: 6, scope: !221)
!1198 = !DILocation(line: 475, column: 12, scope: !1199)
!1199 = distinct !DILexicalBlock(scope: !1194, file: !1, line: 474, column: 25)
!1200 = !DILocation(line: 475, column: 18, scope: !1199)
!1201 = !DILocation(line: 475, column: 10, scope: !1199)
!1202 = !DILocation(line: 475, column: 5, scope: !1199)
!1203 = !DILocation(line: 476, column: 7, scope: !1204)
!1204 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 476, column: 7)
!1205 = !DILocation(line: 476, column: 11, scope: !1204)
!1206 = !DILocation(line: 476, column: 9, scope: !1204)
!1207 = !DILocation(line: 476, column: 7, scope: !1199)
!1208 = !DILocation(line: 477, column: 8, scope: !1204)
!1209 = !DILocation(line: 477, column: 6, scope: !1204)
!1210 = !DILocation(line: 477, column: 4, scope: !1204)
!1211 = !DILocation(line: 478, column: 10, scope: !1199)
!1212 = !DILocation(line: 478, column: 16, scope: !1199)
!1213 = !DILocation(line: 478, column: 26, scope: !1199)
!1214 = !DILocation(line: 478, column: 32, scope: !1199)
!1215 = !DILocation(line: 478, column: 24, scope: !1199)
!1216 = !DILocation(line: 478, column: 40, scope: !1199)
!1217 = !DILocation(line: 478, column: 45, scope: !1199)
!1218 = !DILocation(line: 478, column: 3, scope: !1199)
!1219 = !DILocation(line: 479, column: 7, scope: !1220)
!1220 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 479, column: 7)
!1221 = !DILocation(line: 479, column: 13, scope: !1220)
!1222 = !DILocation(line: 479, column: 22, scope: !1220)
!1223 = !DILocation(line: 479, column: 20, scope: !1220)
!1224 = !DILocation(line: 479, column: 24, scope: !1220)
!1225 = !DILocation(line: 479, column: 7, scope: !1199)
!1226 = !DILocation(line: 480, column: 20, scope: !1227)
!1227 = distinct !DILexicalBlock(scope: !1220, file: !1, line: 479, column: 30)
!1228 = !DILocation(line: 480, column: 4, scope: !1227)
!1229 = !DILocation(line: 480, column: 10, scope: !1227)
!1230 = !DILocation(line: 480, column: 17, scope: !1227)
!1231 = !DILocation(line: 481, column: 11, scope: !1227)
!1232 = !DILocation(line: 481, column: 4, scope: !1227)
!1233 = !DILocation(line: 483, column: 3, scope: !1199)
!1234 = !DILocalVariable(name: "r", scope: !1235, file: !1, line: 483, type: !23)
!1235 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 483, column: 3)
!1236 = !DILocation(line: 483, column: 3, scope: !1235)
!1237 = !DILocation(line: 483, column: 3, scope: !1238)
!1238 = !DILexicalBlockFile(scope: !1235, file: !1, discriminator: 1)
!1239 = !DILocation(line: 483, column: 3, scope: !1240)
!1240 = !DILexicalBlockFile(scope: !1241, file: !1, discriminator: 2)
!1241 = distinct !DILexicalBlock(scope: !1235, file: !1, line: 483, column: 3)
!1242 = !DILocation(line: 483, column: 3, scope: !1243)
!1243 = !DILexicalBlockFile(scope: !1235, file: !1, discriminator: 3)
!1244 = !DILocation(line: 484, column: 10, scope: !1199)
!1245 = !DILocation(line: 484, column: 7, scope: !1199)
!1246 = !DILocation(line: 485, column: 7, scope: !1199)
!1247 = !DILocation(line: 485, column: 16, scope: !1199)
!1248 = !DILocation(line: 485, column: 14, scope: !1199)
!1249 = !DILocation(line: 485, column: 5, scope: !1199)
!1250 = !DILocation(line: 486, column: 2, scope: !1199)
!1251 = !DILocation(line: 487, column: 7, scope: !1252)
!1252 = distinct !DILexicalBlock(scope: !1194, file: !1, line: 486, column: 9)
!1253 = !DILocation(line: 487, column: 5, scope: !1252)
!1254 = !DILocation(line: 490, column: 2, scope: !221)
!1255 = !DILocation(line: 490, column: 9, scope: !1256)
!1256 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 1)
!1257 = !DILocation(line: 490, column: 11, scope: !1256)
!1258 = !DILocation(line: 490, column: 2, scope: !1256)
!1259 = !DILocation(line: 491, column: 3, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !221, file: !1, line: 490, column: 18)
!1261 = !DILocalVariable(name: "r", scope: !1262, file: !1, line: 491, type: !23)
!1262 = distinct !DILexicalBlock(scope: !1260, file: !1, line: 491, column: 3)
!1263 = !DILocation(line: 491, column: 3, scope: !1262)
!1264 = !DILocation(line: 491, column: 3, scope: !1265)
!1265 = !DILexicalBlockFile(scope: !1262, file: !1, discriminator: 1)
!1266 = !DILocation(line: 491, column: 3, scope: !1267)
!1267 = !DILexicalBlockFile(scope: !1268, file: !1, discriminator: 2)
!1268 = distinct !DILexicalBlock(scope: !1262, file: !1, line: 491, column: 3)
!1269 = !DILocation(line: 491, column: 3, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1262, file: !1, discriminator: 3)
!1271 = !DILocation(line: 492, column: 7, scope: !1260)
!1272 = !DILocation(line: 493, column: 5, scope: !1260)
!1273 = !DILocation(line: 495, column: 7, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !1260, file: !1, line: 495, column: 7)
!1275 = !DILocation(line: 495, column: 13, scope: !1274)
!1276 = !DILocation(line: 495, column: 18, scope: !1274)
!1277 = !DILocation(line: 495, column: 25, scope: !1274)
!1278 = !DILocation(line: 495, column: 7, scope: !1260)
!1279 = !DILocation(line: 496, column: 4, scope: !1274)
!1280 = !DILocation(line: 497, column: 32, scope: !1260)
!1281 = !DILocation(line: 497, column: 35, scope: !1260)
!1282 = !DILocation(line: 497, column: 41, scope: !1260)
!1283 = !DILocation(line: 497, column: 46, scope: !1260)
!1284 = !DILocation(line: 498, column: 7, scope: !1260)
!1285 = !DILocation(line: 498, column: 13, scope: !1260)
!1286 = !DILocation(line: 498, column: 18, scope: !1260)
!1287 = !DILocation(line: 497, column: 9, scope: !1260)
!1288 = !DILocation(line: 497, column: 7, scope: !1260)
!1289 = !DILocation(line: 499, column: 7, scope: !1290)
!1290 = distinct !DILexicalBlock(scope: !1260, file: !1, line: 499, column: 7)
!1291 = !DILocation(line: 499, column: 11, scope: !1290)
!1292 = !DILocation(line: 499, column: 7, scope: !1260)
!1293 = !DILocation(line: 500, column: 4, scope: !1290)
!1294 = !DILocation(line: 501, column: 3, scope: !1260)
!1295 = !DILocation(line: 490, column: 2, scope: !1296)
!1296 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 2)
!1297 = !DILocation(line: 503, column: 6, scope: !1298)
!1298 = distinct !DILexicalBlock(scope: !221, file: !1, line: 503, column: 6)
!1299 = !DILocation(line: 503, column: 8, scope: !1298)
!1300 = !DILocation(line: 503, column: 6, scope: !221)
!1301 = !DILocation(line: 504, column: 10, scope: !1302)
!1302 = distinct !DILexicalBlock(scope: !1298, file: !1, line: 503, column: 14)
!1303 = !DILocation(line: 504, column: 16, scope: !1302)
!1304 = !DILocation(line: 504, column: 3, scope: !1302)
!1305 = !DILocation(line: 504, column: 25, scope: !1302)
!1306 = !DILocation(line: 504, column: 30, scope: !1302)
!1307 = !DILocation(line: 505, column: 18, scope: !1302)
!1308 = !DILocation(line: 505, column: 3, scope: !1302)
!1309 = !DILocation(line: 505, column: 9, scope: !1302)
!1310 = !DILocation(line: 505, column: 16, scope: !1302)
!1311 = !DILocation(line: 506, column: 2, scope: !1302)
!1312 = !DILocation(line: 507, column: 10, scope: !221)
!1313 = !DILocation(line: 507, column: 2, scope: !221)
!1314 = !DILocation(line: 508, column: 1, scope: !221)
!1315 = !DILocalVariable(name: "buf", arg: 1, scope: !216, file: !1, line: 77, type: !219)
!1316 = !DILocation(line: 77, column: 35, scope: !216)
!1317 = !DILocalVariable(name: "str", arg: 2, scope: !216, file: !1, line: 77, type: !80)
!1318 = !DILocation(line: 77, column: 52, scope: !216)
!1319 = !DILocalVariable(name: "in_shell", arg: 3, scope: !216, file: !1, line: 77, type: !23)
!1320 = !DILocation(line: 77, column: 61, scope: !216)
!1321 = !DILocalVariable(name: "len", scope: !216, file: !1, line: 80, type: !45)
!1322 = !DILocation(line: 80, column: 9, scope: !216)
!1323 = !DILocation(line: 82, column: 2, scope: !216)
!1324 = !DILocation(line: 82, column: 10, scope: !1325)
!1325 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 1)
!1326 = !DILocation(line: 82, column: 9, scope: !1325)
!1327 = !DILocation(line: 82, column: 14, scope: !1325)
!1328 = !DILocation(line: 82, column: 2, scope: !1325)
!1329 = !DILocation(line: 83, column: 22, scope: !1330)
!1330 = distinct !DILexicalBlock(scope: !1331, file: !1, line: 83, column: 7)
!1331 = distinct !DILexicalBlock(scope: !216, file: !1, line: 82, column: 23)
!1332 = !DILocation(line: 83, column: 14, scope: !1330)
!1333 = !DILocation(line: 83, column: 12, scope: !1330)
!1334 = !DILocation(line: 83, column: 34, scope: !1330)
!1335 = !DILocation(line: 83, column: 7, scope: !1331)
!1336 = !DILocation(line: 84, column: 20, scope: !1337)
!1337 = distinct !DILexicalBlock(scope: !1330, file: !1, line: 83, column: 40)
!1338 = !DILocation(line: 84, column: 25, scope: !1337)
!1339 = !DILocation(line: 84, column: 30, scope: !1337)
!1340 = !DILocation(line: 84, column: 4, scope: !1337)
!1341 = !DILocation(line: 85, column: 11, scope: !1337)
!1342 = !DILocation(line: 85, column: 8, scope: !1337)
!1343 = !DILocation(line: 86, column: 3, scope: !1337)
!1344 = !DILocation(line: 86, column: 15, scope: !1345)
!1345 = !DILexicalBlockFile(scope: !1346, file: !1, discriminator: 1)
!1346 = distinct !DILexicalBlock(scope: !1330, file: !1, line: 86, column: 14)
!1347 = !DILocation(line: 86, column: 14, scope: !1345)
!1348 = !DILocation(line: 86, column: 19, scope: !1345)
!1349 = !DILocation(line: 87, column: 8, scope: !1350)
!1350 = distinct !DILexicalBlock(scope: !1351, file: !1, line: 87, column: 8)
!1351 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 86, column: 28)
!1352 = !DILocation(line: 87, column: 8, scope: !1351)
!1353 = !DILocation(line: 88, column: 20, scope: !1350)
!1354 = !DILocation(line: 88, column: 5, scope: !1350)
!1355 = !DILocation(line: 90, column: 20, scope: !1350)
!1356 = !DILocation(line: 90, column: 5, scope: !1350)
!1357 = !DILocation(line: 91, column: 4, scope: !1351)
!1358 = !DILocation(line: 92, column: 3, scope: !1351)
!1359 = !DILocation(line: 93, column: 27, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 92, column: 10)
!1361 = !DILocation(line: 93, column: 4, scope: !1360)
!1362 = !DILocation(line: 94, column: 27, scope: !1360)
!1363 = !DILocation(line: 94, column: 33, scope: !1360)
!1364 = !DILocation(line: 94, column: 32, scope: !1360)
!1365 = !DILocation(line: 94, column: 4, scope: !1360)
!1366 = !DILocation(line: 95, column: 4, scope: !1360)
!1367 = !DILocation(line: 82, column: 2, scope: !1368)
!1368 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 2)
!1369 = !DILocation(line: 98, column: 1, scope: !216)
!1370 = !DILocalVariable(name: "a", arg: 1, scope: !222, file: !1, line: 412, type: !4)
!1371 = !DILocation(line: 412, column: 38, scope: !222)
!1372 = !DILocalVariable(name: "shar", arg: 2, scope: !222, file: !1, line: 412, type: !191)
!1373 = !DILocation(line: 412, column: 54, scope: !222)
!1374 = !DILocalVariable(name: "inbuf", arg: 3, scope: !222, file: !1, line: 412, type: !80)
!1375 = !DILocation(line: 412, column: 72, scope: !222)
!1376 = !DILocalVariable(name: "len", arg: 4, scope: !222, file: !1, line: 412, type: !45)
!1377 = !DILocation(line: 412, column: 86, scope: !222)
!1378 = !DILocalVariable(name: "buf", scope: !222, file: !1, line: 414, type: !95)
!1379 = !DILocation(line: 414, column: 8, scope: !222)
!1380 = !DILocalVariable(name: "alloc_len", scope: !222, file: !1, line: 415, type: !45)
!1381 = !DILocation(line: 415, column: 9, scope: !222)
!1382 = !DILocation(line: 418, column: 14, scope: !222)
!1383 = !DILocation(line: 418, column: 20, scope: !222)
!1384 = !DILocation(line: 418, column: 25, scope: !222)
!1385 = !DILocation(line: 418, column: 32, scope: !222)
!1386 = !DILocation(line: 418, column: 12, scope: !222)
!1387 = !DILocation(line: 419, column: 29, scope: !1388)
!1388 = distinct !DILexicalBlock(scope: !222, file: !1, line: 419, column: 6)
!1389 = !DILocation(line: 419, column: 35, scope: !1388)
!1390 = !DILocation(line: 419, column: 41, scope: !1388)
!1391 = !DILocation(line: 419, column: 6, scope: !1388)
!1392 = !DILocation(line: 419, column: 52, scope: !1388)
!1393 = !DILocation(line: 419, column: 6, scope: !222)
!1394 = !DILocation(line: 420, column: 22, scope: !1395)
!1395 = distinct !DILexicalBlock(scope: !1388, file: !1, line: 419, column: 61)
!1396 = !DILocation(line: 420, column: 25, scope: !1395)
!1397 = !DILocation(line: 420, column: 3, scope: !1395)
!1398 = !DILocation(line: 421, column: 3, scope: !1395)
!1399 = !DILocation(line: 424, column: 8, scope: !222)
!1400 = !DILocation(line: 424, column: 14, scope: !222)
!1401 = !DILocation(line: 424, column: 19, scope: !222)
!1402 = !DILocation(line: 424, column: 23, scope: !222)
!1403 = !DILocation(line: 424, column: 29, scope: !222)
!1404 = !DILocation(line: 424, column: 34, scope: !222)
!1405 = !DILocation(line: 424, column: 21, scope: !222)
!1406 = !DILocation(line: 424, column: 6, scope: !222)
!1407 = !DILocation(line: 425, column: 11, scope: !222)
!1408 = !DILocation(line: 425, column: 11, scope: !1409)
!1409 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 1)
!1410 = !DILocation(line: 425, column: 11, scope: !1411)
!1411 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 2)
!1412 = !DILocation(line: 425, column: 11, scope: !1413)
!1413 = !DILexicalBlockFile(scope: !222, file: !1, discriminator: 3)
!1414 = !DILocation(line: 425, column: 6, scope: !1413)
!1415 = !DILocation(line: 425, column: 9, scope: !1413)
!1416 = !DILocation(line: 426, column: 2, scope: !222)
!1417 = !DILocation(line: 426, column: 9, scope: !1409)
!1418 = !DILocation(line: 426, column: 13, scope: !1409)
!1419 = !DILocation(line: 426, column: 2, scope: !1409)
!1420 = !DILocation(line: 427, column: 18, scope: !1421)
!1421 = distinct !DILexicalBlock(scope: !222, file: !1, line: 426, column: 19)
!1422 = !DILocation(line: 427, column: 25, scope: !1421)
!1423 = !DILocation(line: 427, column: 3, scope: !1421)
!1424 = !DILocation(line: 428, column: 7, scope: !1421)
!1425 = !DILocation(line: 429, column: 9, scope: !1421)
!1426 = !DILocation(line: 430, column: 7, scope: !1421)
!1427 = !DILocation(line: 426, column: 2, scope: !1411)
!1428 = !DILocation(line: 432, column: 6, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !222, file: !1, line: 432, column: 6)
!1430 = !DILocation(line: 432, column: 10, scope: !1429)
!1431 = !DILocation(line: 432, column: 6, scope: !222)
!1432 = !DILocalVariable(name: "tmp_buf", scope: !1433, file: !1, line: 433, type: !1434)
!1433 = distinct !DILexicalBlock(scope: !1429, file: !1, line: 432, column: 16)
!1434 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 24, align: 8, elements: !1435)
!1435 = !{!1436}
!1436 = !DISubrange(count: 3)
!1437 = !DILocation(line: 433, column: 8, scope: !1433)
!1438 = !DILocation(line: 434, column: 16, scope: !1433)
!1439 = !DILocation(line: 434, column: 3, scope: !1433)
!1440 = !DILocation(line: 434, column: 14, scope: !1433)
!1441 = !DILocation(line: 435, column: 7, scope: !1442)
!1442 = distinct !DILexicalBlock(scope: !1433, file: !1, line: 435, column: 7)
!1443 = !DILocation(line: 435, column: 11, scope: !1442)
!1444 = !DILocation(line: 435, column: 7, scope: !1433)
!1445 = !DILocation(line: 436, column: 4, scope: !1442)
!1446 = !DILocation(line: 436, column: 15, scope: !1442)
!1447 = !DILocation(line: 438, column: 17, scope: !1442)
!1448 = !DILocation(line: 438, column: 4, scope: !1442)
!1449 = !DILocation(line: 438, column: 15, scope: !1442)
!1450 = !DILocation(line: 439, column: 3, scope: !1433)
!1451 = !DILocation(line: 439, column: 14, scope: !1433)
!1452 = !DILocation(line: 440, column: 18, scope: !1433)
!1453 = !DILocation(line: 440, column: 27, scope: !1433)
!1454 = !DILocation(line: 440, column: 3, scope: !1433)
!1455 = !DILocation(line: 441, column: 7, scope: !1433)
!1456 = !DILocation(line: 442, column: 2, scope: !1433)
!1457 = !DILocation(line: 443, column: 6, scope: !222)
!1458 = !DILocation(line: 443, column: 9, scope: !222)
!1459 = !DILocation(line: 444, column: 7, scope: !1460)
!1460 = distinct !DILexicalBlock(scope: !222, file: !1, line: 444, column: 6)
!1461 = !DILocation(line: 444, column: 13, scope: !1460)
!1462 = !DILocation(line: 444, column: 19, scope: !1460)
!1463 = !DILocation(line: 444, column: 24, scope: !1460)
!1464 = !DILocation(line: 444, column: 11, scope: !1460)
!1465 = !DILocation(line: 444, column: 41, scope: !1460)
!1466 = !DILocation(line: 444, column: 47, scope: !1460)
!1467 = !DILocation(line: 444, column: 52, scope: !1460)
!1468 = !DILocation(line: 444, column: 59, scope: !1460)
!1469 = !DILocation(line: 444, column: 27, scope: !1460)
!1470 = !DILocation(line: 444, column: 6, scope: !222)
!1471 = !DILocation(line: 445, column: 22, scope: !1472)
!1472 = distinct !DILexicalBlock(scope: !1460, file: !1, line: 444, column: 66)
!1473 = !DILocation(line: 445, column: 25, scope: !1472)
!1474 = !DILocation(line: 445, column: 3, scope: !1472)
!1475 = !DILocation(line: 447, column: 3, scope: !1472)
!1476 = !DILocation(line: 449, column: 22, scope: !222)
!1477 = !DILocation(line: 449, column: 28, scope: !222)
!1478 = !DILocation(line: 449, column: 34, scope: !222)
!1479 = !DILocation(line: 449, column: 39, scope: !222)
!1480 = !DILocation(line: 449, column: 26, scope: !222)
!1481 = !DILocation(line: 449, column: 2, scope: !222)
!1482 = !DILocation(line: 449, column: 8, scope: !222)
!1483 = !DILocation(line: 449, column: 13, scope: !222)
!1484 = !DILocation(line: 449, column: 20, scope: !222)
!1485 = !DILocation(line: 450, column: 2, scope: !222)
!1486 = !DILocation(line: 451, column: 1, scope: !222)
!1487 = !DILocalVariable(name: "_in", arg: 1, scope: !225, file: !1, line: 399, type: !80)
!1488 = !DILocation(line: 399, column: 27, scope: !225)
!1489 = !DILocalVariable(name: "out", arg: 2, scope: !225, file: !1, line: 399, type: !95)
!1490 = !DILocation(line: 399, column: 40, scope: !225)
!1491 = !DILocalVariable(name: "in", scope: !225, file: !1, line: 401, type: !114)
!1492 = !DILocation(line: 401, column: 23, scope: !225)
!1493 = !DILocation(line: 401, column: 51, scope: !225)
!1494 = !DILocalVariable(name: "t", scope: !225, file: !1, line: 402, type: !23)
!1495 = !DILocation(line: 402, column: 6, scope: !225)
!1496 = !DILocation(line: 404, column: 7, scope: !225)
!1497 = !DILocation(line: 404, column: 13, scope: !225)
!1498 = !DILocation(line: 404, column: 23, scope: !225)
!1499 = !DILocation(line: 404, column: 29, scope: !225)
!1500 = !DILocation(line: 404, column: 20, scope: !225)
!1501 = !DILocation(line: 404, column: 37, scope: !225)
!1502 = !DILocation(line: 404, column: 35, scope: !225)
!1503 = !DILocation(line: 404, column: 4, scope: !225)
!1504 = !DILocation(line: 405, column: 11, scope: !225)
!1505 = !DILocation(line: 405, column: 11, scope: !1506)
!1506 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 1)
!1507 = !DILocation(line: 405, column: 11, scope: !1508)
!1508 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 2)
!1509 = !DILocation(line: 405, column: 11, scope: !1510)
!1510 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 3)
!1511 = !DILocation(line: 405, column: 2, scope: !1510)
!1512 = !DILocation(line: 405, column: 9, scope: !1510)
!1513 = !DILocation(line: 406, column: 11, scope: !225)
!1514 = !DILocation(line: 406, column: 11, scope: !1506)
!1515 = !DILocation(line: 406, column: 11, scope: !1508)
!1516 = !DILocation(line: 406, column: 11, scope: !1510)
!1517 = !DILocation(line: 406, column: 2, scope: !1510)
!1518 = !DILocation(line: 406, column: 9, scope: !1510)
!1519 = !DILocation(line: 407, column: 11, scope: !225)
!1520 = !DILocation(line: 407, column: 11, scope: !1506)
!1521 = !DILocation(line: 407, column: 11, scope: !1508)
!1522 = !DILocation(line: 407, column: 11, scope: !1510)
!1523 = !DILocation(line: 407, column: 2, scope: !1510)
!1524 = !DILocation(line: 407, column: 9, scope: !1510)
!1525 = !DILocation(line: 408, column: 11, scope: !225)
!1526 = !DILocation(line: 408, column: 11, scope: !1506)
!1527 = !DILocation(line: 408, column: 11, scope: !1508)
!1528 = !DILocation(line: 408, column: 11, scope: !1510)
!1529 = !DILocation(line: 408, column: 2, scope: !1510)
!1530 = !DILocation(line: 408, column: 9, scope: !1510)
!1531 = !DILocation(line: 409, column: 1, scope: !225)
