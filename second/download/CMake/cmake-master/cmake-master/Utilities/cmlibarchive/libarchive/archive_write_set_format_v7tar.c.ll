; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_v7tar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.v7tar = type { i64, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }

@.str = private unnamed_addr constant [31 x i8] c"archive_write_set_format_v7tar\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"Can't allocate v7tar data\00", align 1
@.str.2 = private unnamed_addr constant [16 x i8] c"tar (non-POSIX)\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.4 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.5 = private unnamed_addr constant [48 x i8] c"Can't record entry in tar file without pathname\00", align 1
@template_header = internal constant [512 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00000000 \00000000 \00000000 \0000000000000 00000000000         \00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.6 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.7 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.8 = private unnamed_addr constant [18 x i8] c"Pathname too long\00", align 1
@.str.9 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.10 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.11 = private unnamed_addr constant [23 x i8] c"Link contents too long\00", align 1
@.str.12 = private unnamed_addr constant [23 x i8] c"Numeric mode too large\00", align 1
@.str.13 = private unnamed_addr constant [26 x i8] c"Numeric user ID too large\00", align 1
@.str.14 = private unnamed_addr constant [27 x i8] c"Numeric group ID too large\00", align 1
@.str.15 = private unnamed_addr constant [23 x i8] c"File size out of range\00", align 1
@.str.16 = private unnamed_addr constant [33 x i8] c"File modification time too large\00", align 1
@.str.17 = private unnamed_addr constant [43 x i8] c"tar format cannot archive character device\00", align 1
@.str.18 = private unnamed_addr constant [39 x i8] c"tar format cannot archive block device\00", align 1
@.str.19 = private unnamed_addr constant [31 x i8] c"tar format cannot archive fifo\00", align 1
@.str.20 = private unnamed_addr constant [33 x i8] c"tar format cannot archive socket\00", align 1
@.str.21 = private unnamed_addr constant [43 x i8] c"tar format cannot archive this (mode=0%lo)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_v7tar(%struct.archive* %_a) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %v7tar = alloca %struct.v7tar*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !230, metadata !231), !dbg !232
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !233, metadata !231), !dbg !234
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !235
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !236
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !234
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !237, metadata !231), !dbg !238
  br label %do.body, !dbg !239

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !240, metadata !231), !dbg !242
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !243
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !243
  store i32 %call, i32* %magic_test, align 4, !dbg !243
  %3 = load i32, i32* %magic_test, align 4, !dbg !243
  %cmp = icmp eq i32 %3, -30, !dbg !243
  br i1 %cmp, label %if.then, label %if.end, !dbg !243

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !245
  br label %return, !dbg !245

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !248

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !250
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !252
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !252
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !253
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !254

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !255
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !256
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !256
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !257
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !258
  br label %if.end5, !dbg !258

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 40) #7, !dbg !259
  %9 = bitcast i8* %call6 to %struct.v7tar*, !dbg !260
  store %struct.v7tar* %9, %struct.v7tar** %v7tar, align 8, !dbg !261
  %10 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !262
  %cmp7 = icmp eq %struct.v7tar* %10, null, !dbg !264
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !265

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !266
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !268
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !269
  store i32 -30, i32* %retval, align 4, !dbg !270
  br label %return, !dbg !270

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !271
  %13 = bitcast %struct.v7tar* %12 to i8*, !dbg !271
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !272
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 14, !dbg !273
  store i8* %13, i8** %format_data, align 8, !dbg !274
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !275
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 15, !dbg !276
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !277
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !278
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 17, !dbg !279
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_v7tar_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !280
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !281
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 19, !dbg !282
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_v7tar_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !283
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !284
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 20, !dbg !285
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_v7tar_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !286
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !287
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 21, !dbg !288
  store i32 (%struct.archive_write*)* @archive_write_v7tar_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !289
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !290
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 22, !dbg !291
  store i32 (%struct.archive_write*)* @archive_write_v7tar_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !292
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !293
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 18, !dbg !294
  store i32 (%struct.archive_write*)* @archive_write_v7tar_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !295
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !296
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 0, !dbg !297
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !298
  store i32 196608, i32* %archive_format, align 8, !dbg !299
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !300
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !301
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !302
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !303
  store i32 0, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !305
  ret i32 %24, !dbg !305
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_v7tar_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %v7tar = alloca %struct.v7tar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !306, metadata !231), !dbg !307
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !308, metadata !231), !dbg !309
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !310, metadata !231), !dbg !311
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !312, metadata !231), !dbg !313
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !314
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !315
  %1 = load i8*, i8** %format_data, align 8, !dbg !315
  %2 = bitcast i8* %1 to %struct.v7tar*, !dbg !316
  store %struct.v7tar* %2, %struct.v7tar** %v7tar, align 8, !dbg !313
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !317, metadata !231), !dbg !318
  store i32 -25, i32* %ret, align 4, !dbg !318
  %3 = load i8*, i8** %key.addr, align 8, !dbg !319
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !321
  %cmp = icmp eq i32 %call, 0, !dbg !322
  br i1 %cmp, label %if.then, label %if.end13, !dbg !323

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !324
  %cmp1 = icmp eq i8* %4, null, !dbg !327
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !328

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !329
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !329
  %6 = load i8, i8* %arrayidx, align 1, !dbg !329
  %conv = sext i8 %6 to i32, !dbg !329
  %cmp2 = icmp eq i32 %conv, 0, !dbg !331
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !332

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !333
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !334
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !335
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !336
  %9 = load i8*, i8** %format_name, align 8, !dbg !336
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.4, i32 0, i32 0), i8* %9), !dbg !337
  br label %if.end12, !dbg !337

if.else:                                          ; preds = %lor.lhs.false
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !338
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !340
  %11 = load i8*, i8** %val.addr, align 8, !dbg !341
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive5, i8* %11, i32 0), !dbg !342
  %12 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !343
  %opt_sconv = getelementptr inbounds %struct.v7tar, %struct.v7tar* %12, i32 0, i32 2, !dbg !344
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !345
  %13 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !346
  %opt_sconv7 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %13, i32 0, i32 2, !dbg !348
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !348
  %cmp8 = icmp ne %struct.archive_string_conv* %14, null, !dbg !349
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !350

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !351
  br label %if.end, !dbg !352

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !353
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %15 = load i32, i32* %ret, align 4, !dbg !354
  store i32 %15, i32* %retval, align 4, !dbg !355
  br label %return, !dbg !355

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !356
  br label %return, !dbg !356

return:                                           ; preds = %if.end13, %if.end12
  %16 = load i32, i32* %retval, align 4, !dbg !357
  ret i32 %16, !dbg !357
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_v7tar_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %buff = alloca [512 x i8], align 16
  %ret = alloca i32, align 4
  %ret2 = alloca i32, align 4
  %v7tar = alloca %struct.v7tar*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %p = alloca i8*, align 8
  %path_length = alloca i64, align 8
  %as = alloca %struct.archive_string, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !358, metadata !231), !dbg !359
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !360, metadata !231), !dbg !361
  call void @llvm.dbg.declare(metadata [512 x i8]* %buff, metadata !362, metadata !231), !dbg !364
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !365, metadata !231), !dbg !366
  call void @llvm.dbg.declare(metadata i32* %ret2, metadata !367, metadata !231), !dbg !368
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !369, metadata !231), !dbg !370
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !371, metadata !231), !dbg !372
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !373, metadata !231), !dbg !374
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !375
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !376
  %1 = load i8*, i8** %format_data, align 8, !dbg !376
  %2 = bitcast i8* %1 to %struct.v7tar*, !dbg !377
  store %struct.v7tar* %2, %struct.v7tar** %v7tar, align 8, !dbg !378
  %3 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !379
  %opt_sconv = getelementptr inbounds %struct.v7tar, %struct.v7tar* %3, i32 0, i32 2, !dbg !381
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !381
  %cmp = icmp eq %struct.archive_string_conv* %4, null, !dbg !382
  br i1 %cmp, label %if.then, label %if.else, !dbg !383

if.then:                                          ; preds = %entry
  %5 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !384
  %init_default_conversion = getelementptr inbounds %struct.v7tar, %struct.v7tar* %5, i32 0, i32 4, !dbg !387
  %6 = load i32, i32* %init_default_conversion, align 8, !dbg !387
  %tobool = icmp ne i32 %6, 0, !dbg !384
  br i1 %tobool, label %if.end, label %if.then2, !dbg !388

if.then2:                                         ; preds = %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !389
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !391
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !392
  %8 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !393
  %sconv_default = getelementptr inbounds %struct.v7tar, %struct.v7tar* %8, i32 0, i32 3, !dbg !394
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !395
  %9 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !396
  %init_default_conversion3 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %9, i32 0, i32 4, !dbg !397
  store i32 1, i32* %init_default_conversion3, align 8, !dbg !398
  br label %if.end, !dbg !399

if.end:                                           ; preds = %if.then2, %if.then
  %10 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !400
  %sconv_default4 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %10, i32 0, i32 3, !dbg !401
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default4, align 8, !dbg !401
  store %struct.archive_string_conv* %11, %struct.archive_string_conv** %sconv, align 8, !dbg !402
  br label %if.end6, !dbg !403

if.else:                                          ; preds = %entry
  %12 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !404
  %opt_sconv5 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %12, i32 0, i32 2, !dbg !405
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv5, align 8, !dbg !405
  store %struct.archive_string_conv* %13, %struct.archive_string_conv** %sconv, align 8, !dbg !406
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.end
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !407
  %call7 = call i8* @archive_entry_pathname(%struct.archive_entry* %14), !dbg !409
  %cmp8 = icmp eq i8* %call7, null, !dbg !410
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !411

if.then9:                                         ; preds = %if.end6
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !412
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 0, !dbg !414
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.5, i32 0, i32 0)), !dbg !415
  store i32 -25, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

if.end11:                                         ; preds = %if.end6
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !417
  %call12 = call i8* @archive_entry_hardlink(%struct.archive_entry* %16), !dbg !419
  %cmp13 = icmp ne i8* %call12, null, !dbg !420
  br i1 %cmp13, label %if.then19, label %lor.lhs.false, !dbg !421

lor.lhs.false:                                    ; preds = %if.end11
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !422
  %call14 = call i8* @archive_entry_symlink(%struct.archive_entry* %17), !dbg !423
  %cmp15 = icmp ne i8* %call14, null, !dbg !424
  br i1 %cmp15, label %if.then19, label %lor.lhs.false16, !dbg !425

lor.lhs.false16:                                  ; preds = %lor.lhs.false
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !426
  %call17 = call i32 @archive_entry_filetype(%struct.archive_entry* %18), !dbg !427
  %cmp18 = icmp eq i32 %call17, 32768, !dbg !428
  br i1 %cmp18, label %if.end20, label %if.then19, !dbg !429

if.then19:                                        ; preds = %lor.lhs.false16, %lor.lhs.false, %if.end11
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !431
  call void @archive_entry_set_size(%struct.archive_entry* %19, i64 0), !dbg !432
  br label %if.end20, !dbg !432

if.end20:                                         ; preds = %if.then19, %lor.lhs.false16
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !433
  %call21 = call i32 @archive_entry_filetype(%struct.archive_entry* %20), !dbg !435
  %cmp22 = icmp eq i32 16384, %call21, !dbg !436
  br i1 %cmp22, label %if.then23, label %if.end42, !dbg !437

if.then23:                                        ; preds = %if.end20
  call void @llvm.dbg.declare(metadata i8** %p, metadata !438, metadata !231), !dbg !440
  call void @llvm.dbg.declare(metadata i64* %path_length, metadata !441, metadata !231), !dbg !442
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !443
  %call24 = call i8* @archive_entry_pathname(%struct.archive_entry* %21), !dbg !444
  store i8* %call24, i8** %p, align 8, !dbg !445
  %22 = load i8*, i8** %p, align 8, !dbg !446
  %cmp25 = icmp ne i8* %22, null, !dbg !448
  br i1 %cmp25, label %land.lhs.true, label %if.end41, !dbg !449

land.lhs.true:                                    ; preds = %if.then23
  %23 = load i8*, i8** %p, align 8, !dbg !450
  %call26 = call i64 @strlen(i8* %23) #8, !dbg !452
  %sub = sub i64 %call26, 1, !dbg !453
  %24 = load i8*, i8** %p, align 8, !dbg !454
  %arrayidx = getelementptr inbounds i8, i8* %24, i64 %sub, !dbg !454
  %25 = load i8, i8* %arrayidx, align 1, !dbg !454
  %conv = sext i8 %25 to i32, !dbg !454
  %cmp27 = icmp ne i32 %conv, 47, !dbg !455
  br i1 %cmp27, label %if.then29, label %if.end41, !dbg !456

if.then29:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !457, metadata !231), !dbg !459
  br label %do.body, !dbg !460

do.body:                                          ; preds = %if.then29
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !461
  store i8* null, i8** %s, align 8, !dbg !461
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !461
  store i64 0, i64* %length, align 8, !dbg !461
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !461
  store i64 0, i64* %buffer_length, align 8, !dbg !461
  br label %do.end, !dbg !461

do.end:                                           ; preds = %do.body
  %26 = load i8*, i8** %p, align 8, !dbg !464
  %call30 = call i64 @strlen(i8* %26) #8, !dbg !465
  store i64 %call30, i64* %path_length, align 8, !dbg !466
  %27 = load i64, i64* %path_length, align 8, !dbg !467
  %add = add i64 %27, 2, !dbg !469
  %call31 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %as, i64 %add), !dbg !470
  %cmp32 = icmp eq %struct.archive_string* %call31, null, !dbg !471
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !472

if.then34:                                        ; preds = %do.end
  %28 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !473
  %archive35 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 0, !dbg !475
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive35, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !476
  call void @archive_string_free(%struct.archive_string* %as), !dbg !477
  store i32 -30, i32* %retval, align 4, !dbg !478
  br label %return, !dbg !478

if.end36:                                         ; preds = %do.end
  %length37 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !479
  store i64 0, i64* %length37, align 8, !dbg !479
  %29 = load i8*, i8** %p, align 8, !dbg !479
  %30 = load i64, i64* %path_length, align 8, !dbg !479
  %call38 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %29, i64 %30), !dbg !479
  %call39 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 47), !dbg !480
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !481
  %s40 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !482
  %32 = load i8*, i8** %s40, align 8, !dbg !482
  call void @archive_entry_copy_pathname(%struct.archive_entry* %31, i8* %32), !dbg !483
  call void @archive_string_free(%struct.archive_string* %as), !dbg !484
  br label %if.end41, !dbg !485

if.end41:                                         ; preds = %if.end36, %land.lhs.true, %if.then23
  br label %if.end42, !dbg !486

if.end42:                                         ; preds = %if.end41, %if.end20
  store %struct.archive_entry* null, %struct.archive_entry** %entry_main, align 8, !dbg !487
  %33 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !488
  %arraydecay = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !489
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !490
  %35 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !491
  %call43 = call i32 @format_header_v7tar(%struct.archive_write* %33, i8* %arraydecay, %struct.archive_entry* %34, i32 1, %struct.archive_string_conv* %35), !dbg !492
  store i32 %call43, i32* %ret, align 4, !dbg !493
  %36 = load i32, i32* %ret, align 4, !dbg !494
  %cmp44 = icmp slt i32 %36, -20, !dbg !496
  br i1 %cmp44, label %if.then46, label %if.end50, !dbg !497

if.then46:                                        ; preds = %if.end42
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !498
  %tobool47 = icmp ne %struct.archive_entry* %37, null, !dbg !498
  br i1 %tobool47, label %if.then48, label %if.end49, !dbg !501

if.then48:                                        ; preds = %if.then46
  %38 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !502
  call void @archive_entry_free(%struct.archive_entry* %38), !dbg !503
  br label %if.end49, !dbg !503

if.end49:                                         ; preds = %if.then48, %if.then46
  %39 = load i32, i32* %ret, align 4, !dbg !504
  store i32 %39, i32* %retval, align 4, !dbg !505
  br label %return, !dbg !505

if.end50:                                         ; preds = %if.end42
  %40 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !506
  %arraydecay51 = getelementptr inbounds [512 x i8], [512 x i8]* %buff, i32 0, i32 0, !dbg !507
  %call52 = call i32 @__archive_write_output(%struct.archive_write* %40, i8* %arraydecay51, i64 512), !dbg !508
  store i32 %call52, i32* %ret2, align 4, !dbg !509
  %41 = load i32, i32* %ret2, align 4, !dbg !510
  %cmp53 = icmp slt i32 %41, -20, !dbg !512
  br i1 %cmp53, label %if.then55, label %if.end59, !dbg !513

if.then55:                                        ; preds = %if.end50
  %42 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !514
  %tobool56 = icmp ne %struct.archive_entry* %42, null, !dbg !514
  br i1 %tobool56, label %if.then57, label %if.end58, !dbg !517

if.then57:                                        ; preds = %if.then55
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !518
  call void @archive_entry_free(%struct.archive_entry* %43), !dbg !519
  br label %if.end58, !dbg !519

if.end58:                                         ; preds = %if.then57, %if.then55
  %44 = load i32, i32* %ret2, align 4, !dbg !520
  store i32 %44, i32* %retval, align 4, !dbg !521
  br label %return, !dbg !521

if.end59:                                         ; preds = %if.end50
  %45 = load i32, i32* %ret2, align 4, !dbg !522
  %46 = load i32, i32* %ret, align 4, !dbg !524
  %cmp60 = icmp slt i32 %45, %46, !dbg !525
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !526

if.then62:                                        ; preds = %if.end59
  %47 = load i32, i32* %ret2, align 4, !dbg !527
  store i32 %47, i32* %ret, align 4, !dbg !528
  br label %if.end63, !dbg !529

if.end63:                                         ; preds = %if.then62, %if.end59
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !530
  %call64 = call i64 @archive_entry_size(%struct.archive_entry* %48), !dbg !531
  %49 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !532
  %entry_bytes_remaining = getelementptr inbounds %struct.v7tar, %struct.v7tar* %49, i32 0, i32 0, !dbg !533
  store i64 %call64, i64* %entry_bytes_remaining, align 8, !dbg !534
  %50 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !535
  %entry_bytes_remaining65 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %50, i32 0, i32 0, !dbg !536
  %51 = load i64, i64* %entry_bytes_remaining65, align 8, !dbg !536
  %sub66 = sub nsw i64 0, %51, !dbg !537
  %and = and i64 511, %sub66, !dbg !538
  %52 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !539
  %entry_padding = getelementptr inbounds %struct.v7tar, %struct.v7tar* %52, i32 0, i32 1, !dbg !540
  store i64 %and, i64* %entry_padding, align 8, !dbg !541
  %53 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !542
  %tobool67 = icmp ne %struct.archive_entry* %53, null, !dbg !542
  br i1 %tobool67, label %if.then68, label %if.end69, !dbg !544

if.then68:                                        ; preds = %if.end63
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !545
  call void @archive_entry_free(%struct.archive_entry* %54), !dbg !546
  br label %if.end69, !dbg !546

if.end69:                                         ; preds = %if.then68, %if.end63
  %55 = load i32, i32* %ret, align 4, !dbg !547
  store i32 %55, i32* %retval, align 4, !dbg !548
  br label %return, !dbg !548

return:                                           ; preds = %if.end69, %if.end58, %if.end49, %if.then34, %if.then9
  %56 = load i32, i32* %retval, align 4, !dbg !549
  ret i32 %56, !dbg !549
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_v7tar_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !221 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %v7tar = alloca %struct.v7tar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !550, metadata !231), !dbg !551
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !552, metadata !231), !dbg !553
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !554, metadata !231), !dbg !555
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !556, metadata !231), !dbg !557
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !558, metadata !231), !dbg !559
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !560
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !561
  %1 = load i8*, i8** %format_data, align 8, !dbg !561
  %2 = bitcast i8* %1 to %struct.v7tar*, !dbg !562
  store %struct.v7tar* %2, %struct.v7tar** %v7tar, align 8, !dbg !563
  %3 = load i64, i64* %s.addr, align 8, !dbg !564
  %4 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !566
  %entry_bytes_remaining = getelementptr inbounds %struct.v7tar, %struct.v7tar* %4, i32 0, i32 0, !dbg !567
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !567
  %cmp = icmp ugt i64 %3, %5, !dbg !568
  br i1 %cmp, label %if.then, label %if.end, !dbg !569

if.then:                                          ; preds = %entry
  %6 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !570
  %entry_bytes_remaining1 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %6, i32 0, i32 0, !dbg !571
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !571
  store i64 %7, i64* %s.addr, align 8, !dbg !572
  br label %if.end, !dbg !573

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !574
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !575
  %10 = load i64, i64* %s.addr, align 8, !dbg !576
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !577
  store i32 %call, i32* %ret, align 4, !dbg !578
  %11 = load i64, i64* %s.addr, align 8, !dbg !579
  %12 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !580
  %entry_bytes_remaining2 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %12, i32 0, i32 0, !dbg !581
  %13 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !582
  %sub = sub i64 %13, %11, !dbg !582
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !582
  %14 = load i32, i32* %ret, align 4, !dbg !583
  %cmp3 = icmp ne i32 %14, 0, !dbg !585
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !586

if.then4:                                         ; preds = %if.end
  %15 = load i32, i32* %ret, align 4, !dbg !587
  %conv = sext i32 %15 to i64, !dbg !588
  store i64 %conv, i64* %retval, align 8, !dbg !589
  br label %return, !dbg !589

if.end5:                                          ; preds = %if.end
  %16 = load i64, i64* %s.addr, align 8, !dbg !590
  store i64 %16, i64* %retval, align 8, !dbg !591
  br label %return, !dbg !591

return:                                           ; preds = %if.end5, %if.then4
  %17 = load i64, i64* %retval, align 8, !dbg !592
  ret i64 %17, !dbg !592
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_v7tar_close(%struct.archive_write* %a) #0 !dbg !218 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !593, metadata !231), !dbg !594
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !595
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %0, i64 1024), !dbg !596
  ret i32 %call, !dbg !597
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_v7tar_free(%struct.archive_write* %a) #0 !dbg !219 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %v7tar = alloca %struct.v7tar*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !598, metadata !231), !dbg !599
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !600, metadata !231), !dbg !601
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !602
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !603
  %1 = load i8*, i8** %format_data, align 8, !dbg !603
  %2 = bitcast i8* %1 to %struct.v7tar*, !dbg !604
  store %struct.v7tar* %2, %struct.v7tar** %v7tar, align 8, !dbg !605
  %3 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !606
  %4 = bitcast %struct.v7tar* %3 to i8*, !dbg !606
  call void @free(i8* %4) #7, !dbg !607
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !608
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !609
  store i8* null, i8** %format_data1, align 8, !dbg !610
  ret i32 0, !dbg !611
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_v7tar_finish_entry(%struct.archive_write* %a) #0 !dbg !220 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %v7tar = alloca %struct.v7tar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !612, metadata !231), !dbg !613
  call void @llvm.dbg.declare(metadata %struct.v7tar** %v7tar, metadata !614, metadata !231), !dbg !615
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !616, metadata !231), !dbg !617
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !618
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !619
  %1 = load i8*, i8** %format_data, align 8, !dbg !619
  %2 = bitcast i8* %1 to %struct.v7tar*, !dbg !620
  store %struct.v7tar* %2, %struct.v7tar** %v7tar, align 8, !dbg !621
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !622
  %4 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !623
  %entry_bytes_remaining = getelementptr inbounds %struct.v7tar, %struct.v7tar* %4, i32 0, i32 0, !dbg !624
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !624
  %6 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !625
  %entry_padding = getelementptr inbounds %struct.v7tar, %struct.v7tar* %6, i32 0, i32 1, !dbg !626
  %7 = load i64, i64* %entry_padding, align 8, !dbg !626
  %add = add i64 %5, %7, !dbg !627
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %3, i64 %add), !dbg !628
  store i32 %call, i32* %ret, align 4, !dbg !629
  %8 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !630
  %entry_padding1 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %8, i32 0, i32 1, !dbg !631
  store i64 0, i64* %entry_padding1, align 8, !dbg !632
  %9 = load %struct.v7tar*, %struct.v7tar** %v7tar, align 8, !dbg !633
  %entry_bytes_remaining2 = getelementptr inbounds %struct.v7tar, %struct.v7tar* %9, i32 0, i32 0, !dbg !634
  store i64 0, i64* %entry_bytes_remaining2, align 8, !dbg !635
  %10 = load i32, i32* %ret, align 4, !dbg !636
  ret i32 %10, !dbg !637
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_header_v7tar(%struct.archive_write* %a, i8* %h, %struct.archive_entry* %entry1, i32 %strict, %struct.archive_string_conv* %sconv) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %h.addr = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %strict.addr = alloca i32, align 4
  %sconv.addr = alloca %struct.archive_string_conv*, align 8
  %checksum = alloca i32, align 4
  %i = alloca i32, align 4
  %r = alloca i32, align 4
  %ret = alloca i32, align 4
  %copy_length = alloca i64, align 8
  %p = alloca i8*, align 8
  %pp = alloca i8*, align 8
  %mytartype = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !638, metadata !231), !dbg !639
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !640, metadata !231), !dbg !641
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !642, metadata !231), !dbg !643
  store i32 %strict, i32* %strict.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strict.addr, metadata !644, metadata !231), !dbg !645
  store %struct.archive_string_conv* %sconv, %struct.archive_string_conv** %sconv.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv.addr, metadata !646, metadata !231), !dbg !647
  call void @llvm.dbg.declare(metadata i32* %checksum, metadata !648, metadata !231), !dbg !649
  call void @llvm.dbg.declare(metadata i32* %i, metadata !650, metadata !231), !dbg !651
  call void @llvm.dbg.declare(metadata i32* %r, metadata !652, metadata !231), !dbg !653
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !654, metadata !231), !dbg !655
  call void @llvm.dbg.declare(metadata i64* %copy_length, metadata !656, metadata !231), !dbg !657
  call void @llvm.dbg.declare(metadata i8** %p, metadata !658, metadata !231), !dbg !659
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !660, metadata !231), !dbg !661
  call void @llvm.dbg.declare(metadata i32* %mytartype, metadata !662, metadata !231), !dbg !663
  store i32 0, i32* %ret, align 4, !dbg !664
  store i32 -1, i32* %mytartype, align 4, !dbg !665
  %0 = load i8*, i8** %h.addr, align 8, !dbg !666
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @template_header, i32 0, i32 0), i64 512, i32 1, i1 false), !dbg !667
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !668
  %2 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !669
  %call = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %1, i8** %pp, i64* %copy_length, %struct.archive_string_conv* %2), !dbg !670
  store i32 %call, i32* %r, align 4, !dbg !671
  %3 = load i32, i32* %r, align 4, !dbg !672
  %cmp = icmp ne i32 %3, 0, !dbg !674
  br i1 %cmp, label %if.then, label %if.end7, !dbg !675

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !676
  %4 = load i32, i32* %call2, align 4, !dbg !676
  %cmp3 = icmp eq i32 %4, 12, !dbg !679
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !680

if.then4:                                         ; preds = %if.then
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !681
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !683
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.6, i32 0, i32 0)), !dbg !684
  store i32 -30, i32* %retval, align 4, !dbg !685
  br label %return, !dbg !685

if.end:                                           ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !686
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !687
  %7 = load i8*, i8** %pp, align 8, !dbg !688
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !689
  %call6 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %8), !dbg !690
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.7, i32 0, i32 0), i8* %7, i8* %call6), !dbg !691
  store i32 -20, i32* %ret, align 4, !dbg !692
  br label %if.end7, !dbg !693

if.end7:                                          ; preds = %if.end, %entry
  %9 = load i32, i32* %strict.addr, align 4, !dbg !694
  %tobool = icmp ne i32 %9, 0, !dbg !694
  br i1 %tobool, label %land.lhs.true, label %if.else, !dbg !696

land.lhs.true:                                    ; preds = %if.end7
  %10 = load i64, i64* %copy_length, align 8, !dbg !697
  %cmp8 = icmp ult i64 %10, 100, !dbg !699
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !700

if.then9:                                         ; preds = %land.lhs.true
  %11 = load i8*, i8** %h.addr, align 8, !dbg !701
  %add.ptr = getelementptr inbounds i8, i8* %11, i64 0, !dbg !702
  %12 = load i8*, i8** %pp, align 8, !dbg !703
  %13 = load i64, i64* %copy_length, align 8, !dbg !704
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %12, i64 %13, i32 1, i1 false), !dbg !705
  br label %if.end18, !dbg !705

if.else:                                          ; preds = %land.lhs.true, %if.end7
  %14 = load i32, i32* %strict.addr, align 4, !dbg !706
  %tobool10 = icmp ne i32 %14, 0, !dbg !706
  br i1 %tobool10, label %if.else15, label %land.lhs.true11, !dbg !708

land.lhs.true11:                                  ; preds = %if.else
  %15 = load i64, i64* %copy_length, align 8, !dbg !709
  %cmp12 = icmp ule i64 %15, 100, !dbg !711
  br i1 %cmp12, label %if.then13, label %if.else15, !dbg !712

if.then13:                                        ; preds = %land.lhs.true11
  %16 = load i8*, i8** %h.addr, align 8, !dbg !713
  %add.ptr14 = getelementptr inbounds i8, i8* %16, i64 0, !dbg !714
  %17 = load i8*, i8** %pp, align 8, !dbg !715
  %18 = load i64, i64* %copy_length, align 8, !dbg !716
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr14, i8* %17, i64 %18, i32 1, i1 false), !dbg !717
  br label %if.end17, !dbg !717

if.else15:                                        ; preds = %land.lhs.true11, %if.else
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !718
  %archive16 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !720
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 36, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.8, i32 0, i32 0)), !dbg !721
  store i32 -25, i32* %ret, align 4, !dbg !722
  br label %if.end17

if.end17:                                         ; preds = %if.else15, %if.then13
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then9
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !723
  %21 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !724
  %call19 = call i32 @_archive_entry_hardlink_l(%struct.archive_entry* %20, i8** %p, i64* %copy_length, %struct.archive_string_conv* %21), !dbg !725
  store i32 %call19, i32* %r, align 4, !dbg !726
  %22 = load i32, i32* %r, align 4, !dbg !727
  %cmp20 = icmp ne i32 %22, 0, !dbg !729
  br i1 %cmp20, label %if.then21, label %if.end29, !dbg !730

if.then21:                                        ; preds = %if.end18
  %call22 = call i32* @__errno_location() #1, !dbg !731
  %23 = load i32, i32* %call22, align 4, !dbg !731
  %cmp23 = icmp eq i32 %23, 12, !dbg !734
  br i1 %cmp23, label %if.then24, label %if.end26, !dbg !735

if.then24:                                        ; preds = %if.then21
  %24 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !736
  %archive25 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 0, !dbg !738
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.9, i32 0, i32 0)), !dbg !739
  store i32 -30, i32* %retval, align 4, !dbg !740
  br label %return, !dbg !740

if.end26:                                         ; preds = %if.then21
  %25 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !741
  %archive27 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 0, !dbg !742
  %26 = load i8*, i8** %p, align 8, !dbg !743
  %27 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !744
  %call28 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %27), !dbg !745
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive27, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.10, i32 0, i32 0), i8* %26, i8* %call28), !dbg !746
  store i32 -20, i32* %ret, align 4, !dbg !747
  br label %if.end29, !dbg !748

if.end29:                                         ; preds = %if.end26, %if.end18
  %28 = load i64, i64* %copy_length, align 8, !dbg !749
  %cmp30 = icmp ugt i64 %28, 0, !dbg !751
  br i1 %cmp30, label %if.then31, label %if.else32, !dbg !752

if.then31:                                        ; preds = %if.end29
  store i32 49, i32* %mytartype, align 4, !dbg !753
  br label %if.end44, !dbg !754

if.else32:                                        ; preds = %if.end29
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !755
  %30 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !757
  %call33 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %29, i8** %p, i64* %copy_length, %struct.archive_string_conv* %30), !dbg !758
  store i32 %call33, i32* %r, align 4, !dbg !759
  %31 = load i32, i32* %r, align 4, !dbg !760
  %cmp34 = icmp ne i32 %31, 0, !dbg !762
  br i1 %cmp34, label %if.then35, label %if.end43, !dbg !763

if.then35:                                        ; preds = %if.else32
  %call36 = call i32* @__errno_location() #1, !dbg !764
  %32 = load i32, i32* %call36, align 4, !dbg !764
  %cmp37 = icmp eq i32 %32, 12, !dbg !767
  br i1 %cmp37, label %if.then38, label %if.end40, !dbg !768

if.then38:                                        ; preds = %if.then35
  %33 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !769
  %archive39 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %33, i32 0, i32 0, !dbg !771
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive39, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.9, i32 0, i32 0)), !dbg !772
  store i32 -30, i32* %retval, align 4, !dbg !773
  br label %return, !dbg !773

if.end40:                                         ; preds = %if.then35
  %34 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !774
  %archive41 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %34, i32 0, i32 0, !dbg !775
  %35 = load i8*, i8** %p, align 8, !dbg !776
  %36 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !777
  %call42 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %36), !dbg !778
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive41, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.10, i32 0, i32 0), i8* %35, i8* %call42), !dbg !779
  store i32 -20, i32* %ret, align 4, !dbg !780
  br label %if.end43, !dbg !781

if.end43:                                         ; preds = %if.end40, %if.else32
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then31
  %37 = load i64, i64* %copy_length, align 8, !dbg !782
  %cmp45 = icmp ugt i64 %37, 0, !dbg !784
  br i1 %cmp45, label %if.then46, label %if.end52, !dbg !785

if.then46:                                        ; preds = %if.end44
  %38 = load i64, i64* %copy_length, align 8, !dbg !786
  %cmp47 = icmp uge i64 %38, 100, !dbg !789
  br i1 %cmp47, label %if.then48, label %if.end50, !dbg !790

if.then48:                                        ; preds = %if.then46
  %39 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !791
  %archive49 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 0, !dbg !793
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive49, i32 36, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.11, i32 0, i32 0)), !dbg !794
  store i32 -25, i32* %ret, align 4, !dbg !795
  store i64 100, i64* %copy_length, align 8, !dbg !796
  br label %if.end50, !dbg !797

if.end50:                                         ; preds = %if.then48, %if.then46
  %40 = load i8*, i8** %h.addr, align 8, !dbg !798
  %add.ptr51 = getelementptr inbounds i8, i8* %40, i64 157, !dbg !799
  %41 = load i8*, i8** %p, align 8, !dbg !800
  %42 = load i64, i64* %copy_length, align 8, !dbg !801
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr51, i8* %41, i64 %42, i32 1, i1 false), !dbg !802
  br label %if.end52, !dbg !803

if.end52:                                         ; preds = %if.end50, %if.end44
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !804
  %call53 = call i32 @archive_entry_mode(%struct.archive_entry* %43), !dbg !806
  %and = and i32 %call53, 4095, !dbg !807
  %conv = zext i32 %and to i64, !dbg !806
  %44 = load i8*, i8** %h.addr, align 8, !dbg !808
  %add.ptr54 = getelementptr inbounds i8, i8* %44, i64 100, !dbg !809
  %45 = load i32, i32* %strict.addr, align 4, !dbg !810
  %call55 = call i32 @format_number(i64 %conv, i8* %add.ptr54, i32 6, i32 8, i32 %45), !dbg !811
  %tobool56 = icmp ne i32 %call55, 0, !dbg !813
  br i1 %tobool56, label %if.then57, label %if.end59, !dbg !814

if.then57:                                        ; preds = %if.end52
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !815
  %archive58 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %46, i32 0, i32 0, !dbg !817
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive58, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.12, i32 0, i32 0)), !dbg !818
  store i32 -25, i32* %ret, align 4, !dbg !819
  br label %if.end59, !dbg !820

if.end59:                                         ; preds = %if.then57, %if.end52
  %47 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !821
  %call60 = call i64 @archive_entry_uid(%struct.archive_entry* %47), !dbg !823
  %48 = load i8*, i8** %h.addr, align 8, !dbg !824
  %add.ptr61 = getelementptr inbounds i8, i8* %48, i64 108, !dbg !825
  %49 = load i32, i32* %strict.addr, align 4, !dbg !826
  %call62 = call i32 @format_number(i64 %call60, i8* %add.ptr61, i32 6, i32 8, i32 %49), !dbg !827
  %tobool63 = icmp ne i32 %call62, 0, !dbg !829
  br i1 %tobool63, label %if.then64, label %if.end66, !dbg !830

if.then64:                                        ; preds = %if.end59
  %50 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !831
  %archive65 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %50, i32 0, i32 0, !dbg !833
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive65, i32 34, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.13, i32 0, i32 0)), !dbg !834
  store i32 -25, i32* %ret, align 4, !dbg !835
  br label %if.end66, !dbg !836

if.end66:                                         ; preds = %if.then64, %if.end59
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !837
  %call67 = call i64 @archive_entry_gid(%struct.archive_entry* %51), !dbg !839
  %52 = load i8*, i8** %h.addr, align 8, !dbg !840
  %add.ptr68 = getelementptr inbounds i8, i8* %52, i64 116, !dbg !841
  %53 = load i32, i32* %strict.addr, align 4, !dbg !842
  %call69 = call i32 @format_number(i64 %call67, i8* %add.ptr68, i32 6, i32 8, i32 %53), !dbg !843
  %tobool70 = icmp ne i32 %call69, 0, !dbg !845
  br i1 %tobool70, label %if.then71, label %if.end73, !dbg !846

if.then71:                                        ; preds = %if.end66
  %54 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !847
  %archive72 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %54, i32 0, i32 0, !dbg !849
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive72, i32 34, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.14, i32 0, i32 0)), !dbg !850
  store i32 -25, i32* %ret, align 4, !dbg !851
  br label %if.end73, !dbg !852

if.end73:                                         ; preds = %if.then71, %if.end66
  %55 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !853
  %call74 = call i64 @archive_entry_size(%struct.archive_entry* %55), !dbg !855
  %56 = load i8*, i8** %h.addr, align 8, !dbg !856
  %add.ptr75 = getelementptr inbounds i8, i8* %56, i64 124, !dbg !857
  %57 = load i32, i32* %strict.addr, align 4, !dbg !858
  %call76 = call i32 @format_number(i64 %call74, i8* %add.ptr75, i32 11, i32 12, i32 %57), !dbg !859
  %tobool77 = icmp ne i32 %call76, 0, !dbg !861
  br i1 %tobool77, label %if.then78, label %if.end80, !dbg !862

if.then78:                                        ; preds = %if.end73
  %58 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !863
  %archive79 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %58, i32 0, i32 0, !dbg !865
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive79, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.15, i32 0, i32 0)), !dbg !866
  store i32 -25, i32* %ret, align 4, !dbg !867
  br label %if.end80, !dbg !868

if.end80:                                         ; preds = %if.then78, %if.end73
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !869
  %call81 = call i64 @archive_entry_mtime(%struct.archive_entry* %59), !dbg !871
  %60 = load i8*, i8** %h.addr, align 8, !dbg !872
  %add.ptr82 = getelementptr inbounds i8, i8* %60, i64 136, !dbg !873
  %61 = load i32, i32* %strict.addr, align 4, !dbg !874
  %call83 = call i32 @format_number(i64 %call81, i8* %add.ptr82, i32 11, i32 12, i32 %61), !dbg !875
  %tobool84 = icmp ne i32 %call83, 0, !dbg !877
  br i1 %tobool84, label %if.then85, label %if.end87, !dbg !878

if.then85:                                        ; preds = %if.end80
  %62 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !879
  %archive86 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %62, i32 0, i32 0, !dbg !881
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive86, i32 34, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.16, i32 0, i32 0)), !dbg !882
  store i32 -25, i32* %ret, align 4, !dbg !883
  br label %if.end87, !dbg !884

if.end87:                                         ; preds = %if.then85, %if.end80
  %63 = load i32, i32* %mytartype, align 4, !dbg !885
  %cmp88 = icmp sge i32 %63, 0, !dbg !887
  br i1 %cmp88, label %if.then90, label %if.else92, !dbg !888

if.then90:                                        ; preds = %if.end87
  %64 = load i32, i32* %mytartype, align 4, !dbg !889
  %conv91 = trunc i32 %64 to i8, !dbg !889
  %65 = load i8*, i8** %h.addr, align 8, !dbg !891
  %arrayidx = getelementptr inbounds i8, i8* %65, i64 156, !dbg !891
  store i8 %conv91, i8* %arrayidx, align 1, !dbg !892
  br label %if.end107, !dbg !893

if.else92:                                        ; preds = %if.end87
  %66 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !894
  %call93 = call i32 @archive_entry_filetype(%struct.archive_entry* %66), !dbg !896
  switch i32 %call93, label %sw.default [
    i32 32768, label %sw.bb
    i32 16384, label %sw.bb
    i32 40960, label %sw.bb94
    i32 8192, label %sw.bb96
    i32 24576, label %sw.bb98
    i32 4096, label %sw.bb100
    i32 49152, label %sw.bb102
  ], !dbg !897

sw.bb:                                            ; preds = %if.else92, %if.else92
  br label %sw.epilog, !dbg !898

sw.bb94:                                          ; preds = %if.else92
  %67 = load i8*, i8** %h.addr, align 8, !dbg !900
  %arrayidx95 = getelementptr inbounds i8, i8* %67, i64 156, !dbg !900
  store i8 50, i8* %arrayidx95, align 1, !dbg !901
  br label %sw.epilog, !dbg !902

sw.bb96:                                          ; preds = %if.else92
  %68 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !903
  %archive97 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %68, i32 0, i32 0, !dbg !904
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive97, i32 84, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.17, i32 0, i32 0)), !dbg !905
  store i32 -25, i32* %retval, align 4, !dbg !906
  br label %return, !dbg !906

sw.bb98:                                          ; preds = %if.else92
  %69 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !907
  %archive99 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %69, i32 0, i32 0, !dbg !908
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive99, i32 84, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.18, i32 0, i32 0)), !dbg !909
  store i32 -25, i32* %retval, align 4, !dbg !910
  br label %return, !dbg !910

sw.bb100:                                         ; preds = %if.else92
  %70 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !911
  %archive101 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %70, i32 0, i32 0, !dbg !912
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive101, i32 84, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.19, i32 0, i32 0)), !dbg !913
  store i32 -25, i32* %retval, align 4, !dbg !914
  br label %return, !dbg !914

sw.bb102:                                         ; preds = %if.else92
  %71 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !915
  %archive103 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %71, i32 0, i32 0, !dbg !916
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive103, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.20, i32 0, i32 0)), !dbg !917
  store i32 -25, i32* %retval, align 4, !dbg !918
  br label %return, !dbg !918

sw.default:                                       ; preds = %if.else92
  %72 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !919
  %archive104 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %72, i32 0, i32 0, !dbg !920
  %73 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !921
  %call105 = call i32 @archive_entry_mode(%struct.archive_entry* %73), !dbg !922
  %conv106 = zext i32 %call105 to i64, !dbg !923
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive104, i32 84, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.21, i32 0, i32 0), i64 %conv106), !dbg !924
  store i32 -25, i32* %ret, align 4, !dbg !925
  br label %sw.epilog, !dbg !926

sw.epilog:                                        ; preds = %sw.default, %sw.bb94, %sw.bb
  br label %if.end107

if.end107:                                        ; preds = %sw.epilog, %if.then90
  store i32 0, i32* %checksum, align 4, !dbg !927
  store i32 0, i32* %i, align 4, !dbg !928
  br label %for.cond, !dbg !930

for.cond:                                         ; preds = %for.inc, %if.end107
  %74 = load i32, i32* %i, align 4, !dbg !931
  %cmp108 = icmp slt i32 %74, 512, !dbg !934
  br i1 %cmp108, label %for.body, label %for.end, !dbg !935

for.body:                                         ; preds = %for.cond
  %75 = load i32, i32* %i, align 4, !dbg !936
  %idxprom = sext i32 %75 to i64, !dbg !937
  %76 = load i8*, i8** %h.addr, align 8, !dbg !937
  %arrayidx110 = getelementptr inbounds i8, i8* %76, i64 %idxprom, !dbg !937
  %77 = load i8, i8* %arrayidx110, align 1, !dbg !937
  %conv111 = sext i8 %77 to i32, !dbg !938
  %and112 = and i32 255, %conv111, !dbg !939
  %78 = load i32, i32* %checksum, align 4, !dbg !940
  %add = add i32 %78, %and112, !dbg !940
  store i32 %add, i32* %checksum, align 4, !dbg !940
  br label %for.inc, !dbg !941

for.inc:                                          ; preds = %for.body
  %79 = load i32, i32* %i, align 4, !dbg !942
  %inc = add nsw i32 %79, 1, !dbg !942
  store i32 %inc, i32* %i, align 4, !dbg !942
  br label %for.cond, !dbg !944

for.end:                                          ; preds = %for.cond
  %80 = load i32, i32* %checksum, align 4, !dbg !945
  %conv113 = zext i32 %80 to i64, !dbg !945
  %81 = load i8*, i8** %h.addr, align 8, !dbg !946
  %add.ptr114 = getelementptr inbounds i8, i8* %81, i64 148, !dbg !947
  %call115 = call i32 @format_octal(i64 %conv113, i8* %add.ptr114, i32 6), !dbg !948
  %82 = load i8*, i8** %h.addr, align 8, !dbg !949
  %arrayidx116 = getelementptr inbounds i8, i8* %82, i64 154, !dbg !949
  store i8 0, i8* %arrayidx116, align 1, !dbg !950
  %83 = load i32, i32* %ret, align 4, !dbg !951
  store i32 %83, i32* %retval, align 4, !dbg !952
  br label %return, !dbg !952

return:                                           ; preds = %for.end, %sw.bb102, %sw.bb100, %sw.bb98, %sw.bb96, %if.then38, %if.then24, %if.then4
  %84 = load i32, i32* %retval, align 4, !dbg !953
  ret i32 %84, !dbg !953
}

declare void @archive_entry_free(%struct.archive_entry*) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

declare i32 @_archive_entry_hardlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_number(i64 %v, i8* %p, i32 %s, i32 %maxsize, i32 %strict) #0 !dbg !211 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %maxsize.addr = alloca i32, align 4
  %strict.addr = alloca i32, align 4
  %limit = alloca i64, align 8
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !954, metadata !231), !dbg !955
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !956, metadata !231), !dbg !957
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !958, metadata !231), !dbg !959
  store i32 %maxsize, i32* %maxsize.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %maxsize.addr, metadata !960, metadata !231), !dbg !961
  store i32 %strict, i32* %strict.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strict.addr, metadata !962, metadata !231), !dbg !963
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !964, metadata !231), !dbg !965
  %0 = load i32, i32* %s.addr, align 4, !dbg !966
  %mul = mul nsw i32 %0, 3, !dbg !967
  %sh_prom = zext i32 %mul to i64, !dbg !968
  %shl = shl i64 1, %sh_prom, !dbg !968
  store i64 %shl, i64* %limit, align 8, !dbg !969
  %1 = load i32, i32* %strict.addr, align 4, !dbg !970
  %tobool = icmp ne i32 %1, 0, !dbg !970
  br i1 %tobool, label %if.then, label %if.end, !dbg !972

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !973
  %3 = load i8*, i8** %p.addr, align 8, !dbg !974
  %4 = load i32, i32* %s.addr, align 4, !dbg !975
  %call = call i32 @format_octal(i64 %2, i8* %3, i32 %4), !dbg !976
  store i32 %call, i32* %retval, align 4, !dbg !977
  br label %return, !dbg !977

if.end:                                           ; preds = %entry
  %5 = load i64, i64* %v.addr, align 8, !dbg !978
  %cmp = icmp sge i64 %5, 0, !dbg !980
  br i1 %cmp, label %if.then1, label %if.end8, !dbg !981

if.then1:                                         ; preds = %if.end
  br label %while.cond, !dbg !982

while.cond:                                       ; preds = %if.end6, %if.then1
  %6 = load i32, i32* %s.addr, align 4, !dbg !984
  %7 = load i32, i32* %maxsize.addr, align 4, !dbg !986
  %cmp2 = icmp sle i32 %6, %7, !dbg !987
  br i1 %cmp2, label %while.body, label %while.end, !dbg !988

while.body:                                       ; preds = %while.cond
  %8 = load i64, i64* %v.addr, align 8, !dbg !989
  %9 = load i64, i64* %limit, align 8, !dbg !992
  %cmp3 = icmp slt i64 %8, %9, !dbg !993
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !994

if.then4:                                         ; preds = %while.body
  %10 = load i64, i64* %v.addr, align 8, !dbg !995
  %11 = load i8*, i8** %p.addr, align 8, !dbg !996
  %12 = load i32, i32* %s.addr, align 4, !dbg !997
  %call5 = call i32 @format_octal(i64 %10, i8* %11, i32 %12), !dbg !998
  store i32 %call5, i32* %retval, align 4, !dbg !999
  br label %return, !dbg !999

if.end6:                                          ; preds = %while.body
  %13 = load i32, i32* %s.addr, align 4, !dbg !1000
  %inc = add nsw i32 %13, 1, !dbg !1000
  store i32 %inc, i32* %s.addr, align 4, !dbg !1000
  %14 = load i64, i64* %limit, align 8, !dbg !1001
  %shl7 = shl i64 %14, 3, !dbg !1001
  store i64 %shl7, i64* %limit, align 8, !dbg !1001
  br label %while.cond, !dbg !1002

while.end:                                        ; preds = %while.cond
  br label %if.end8, !dbg !1004

if.end8:                                          ; preds = %while.end, %if.end
  %15 = load i64, i64* %v.addr, align 8, !dbg !1005
  %16 = load i8*, i8** %p.addr, align 8, !dbg !1006
  %17 = load i32, i32* %maxsize.addr, align 4, !dbg !1007
  %call9 = call i32 @format_256(i64 %15, i8* %16, i32 %17), !dbg !1008
  store i32 %call9, i32* %retval, align 4, !dbg !1009
  br label %return, !dbg !1009

return:                                           ; preds = %if.end8, %if.then4, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !1010
  ret i32 %18, !dbg !1010
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_octal(i64 %v, i8* %p, i32 %s) #0 !dbg !217 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %len = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1011, metadata !231), !dbg !1012
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1013, metadata !231), !dbg !1014
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1015, metadata !231), !dbg !1016
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1017, metadata !231), !dbg !1018
  %0 = load i32, i32* %s.addr, align 4, !dbg !1019
  store i32 %0, i32* %len, align 4, !dbg !1020
  %1 = load i64, i64* %v.addr, align 8, !dbg !1021
  %cmp = icmp slt i64 %1, 0, !dbg !1023
  br i1 %cmp, label %if.then, label %if.end, !dbg !1024

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !1025

while.cond:                                       ; preds = %while.body, %if.then
  %2 = load i32, i32* %len, align 4, !dbg !1027
  %dec = add nsw i32 %2, -1, !dbg !1027
  store i32 %dec, i32* %len, align 4, !dbg !1027
  %cmp1 = icmp sgt i32 %2, 0, !dbg !1029
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1030

while.body:                                       ; preds = %while.cond
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1031
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !1031
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1031
  store i8 48, i8* %3, align 1, !dbg !1032
  br label %while.cond, !dbg !1033

while.end:                                        ; preds = %while.cond
  store i32 -1, i32* %retval, align 4, !dbg !1035
  br label %return, !dbg !1035

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %s.addr, align 4, !dbg !1036
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1037
  %idx.ext = sext i32 %4 to i64, !dbg !1037
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 %idx.ext, !dbg !1037
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1037
  br label %while.cond2, !dbg !1038

while.cond2:                                      ; preds = %while.body5, %if.end
  %6 = load i32, i32* %s.addr, align 4, !dbg !1039
  %dec3 = add nsw i32 %6, -1, !dbg !1039
  store i32 %dec3, i32* %s.addr, align 4, !dbg !1039
  %cmp4 = icmp sgt i32 %6, 0, !dbg !1041
  br i1 %cmp4, label %while.body5, label %while.end7, !dbg !1042

while.body5:                                      ; preds = %while.cond2
  %7 = load i64, i64* %v.addr, align 8, !dbg !1043
  %and = and i64 %7, 7, !dbg !1045
  %add = add nsw i64 48, %and, !dbg !1046
  %conv = trunc i64 %add to i8, !dbg !1047
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1048
  %incdec.ptr6 = getelementptr inbounds i8, i8* %8, i32 -1, !dbg !1048
  store i8* %incdec.ptr6, i8** %p.addr, align 8, !dbg !1048
  store i8 %conv, i8* %incdec.ptr6, align 1, !dbg !1049
  %9 = load i64, i64* %v.addr, align 8, !dbg !1050
  %shr = ashr i64 %9, 3, !dbg !1050
  store i64 %shr, i64* %v.addr, align 8, !dbg !1050
  br label %while.cond2, !dbg !1051

while.end7:                                       ; preds = %while.cond2
  %10 = load i64, i64* %v.addr, align 8, !dbg !1053
  %cmp8 = icmp eq i64 %10, 0, !dbg !1055
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !1056

if.then10:                                        ; preds = %while.end7
  store i32 0, i32* %retval, align 4, !dbg !1057
  br label %return, !dbg !1057

if.end11:                                         ; preds = %while.end7
  br label %while.cond12, !dbg !1058

while.cond12:                                     ; preds = %while.body16, %if.end11
  %11 = load i32, i32* %len, align 4, !dbg !1059
  %dec13 = add nsw i32 %11, -1, !dbg !1059
  store i32 %dec13, i32* %len, align 4, !dbg !1059
  %cmp14 = icmp sgt i32 %11, 0, !dbg !1060
  br i1 %cmp14, label %while.body16, label %while.end18, !dbg !1061

while.body16:                                     ; preds = %while.cond12
  %12 = load i8*, i8** %p.addr, align 8, !dbg !1062
  %incdec.ptr17 = getelementptr inbounds i8, i8* %12, i32 1, !dbg !1062
  store i8* %incdec.ptr17, i8** %p.addr, align 8, !dbg !1062
  store i8 55, i8* %12, align 1, !dbg !1063
  br label %while.cond12, !dbg !1064

while.end18:                                      ; preds = %while.cond12
  store i32 -1, i32* %retval, align 4, !dbg !1065
  br label %return, !dbg !1065

return:                                           ; preds = %while.end18, %if.then10, %while.end
  %13 = load i32, i32* %retval, align 4, !dbg !1066
  ret i32 %13, !dbg !1066
}

; Function Attrs: nounwind uwtable
define internal i32 @format_256(i64 %v, i8* %p, i32 %s) #0 !dbg !214 {
entry:
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1067, metadata !231), !dbg !1068
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1069, metadata !231), !dbg !1070
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1071, metadata !231), !dbg !1072
  %0 = load i32, i32* %s.addr, align 4, !dbg !1073
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1074
  %idx.ext = sext i32 %0 to i64, !dbg !1074
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !1074
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1074
  br label %while.cond, !dbg !1075

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i32, i32* %s.addr, align 4, !dbg !1076
  %dec = add nsw i32 %2, -1, !dbg !1076
  store i32 %dec, i32* %s.addr, align 4, !dbg !1076
  %cmp = icmp sgt i32 %2, 0, !dbg !1078
  br i1 %cmp, label %while.body, label %while.end, !dbg !1079

while.body:                                       ; preds = %while.cond
  %3 = load i64, i64* %v.addr, align 8, !dbg !1080
  %and = and i64 %3, 255, !dbg !1082
  %conv = trunc i64 %and to i8, !dbg !1083
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1084
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 -1, !dbg !1084
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1084
  store i8 %conv, i8* %incdec.ptr, align 1, !dbg !1085
  %5 = load i64, i64* %v.addr, align 8, !dbg !1086
  %shr = ashr i64 %5, 8, !dbg !1086
  store i64 %shr, i64* %v.addr, align 8, !dbg !1086
  br label %while.cond, !dbg !1087

while.end:                                        ; preds = %while.cond
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1089
  %7 = load i8, i8* %6, align 1, !dbg !1090
  %conv1 = sext i8 %7 to i32, !dbg !1090
  %or = or i32 %conv1, 128, !dbg !1090
  %conv2 = trunc i32 %or to i8, !dbg !1090
  store i8 %conv2, i8* %6, align 1, !dbg !1090
  ret i32 0, !dbg !1091
}

declare i32 @__archive_write_nulls(%struct.archive_write*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!227, !228}
!llvm.ident = !{!229}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !204, globals: !222)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_v7tar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !201, !52, !47, !13, !82, !45}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !111, !112, !113, !114, !118, !119, !125, !131, !134, !135, !136, !137, !163, !164, !165, !166, !170, !174, !175, !179, !183, !184, !185, !186, !191}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !105, !106, !107, !108, !109, !110}
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
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !104, line: 36, flags: DIFlagFwdDecl)
!104 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !115, size: 64, align: 64, offset: 1472)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !117)
!117 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !120, size: 64, align: 64, offset: 1600)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !122)
!122 = !DISubroutineType(types: !123)
!123 = !{!23, !24, !124}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !126, size: 64, align: 64, offset: 1664)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !128)
!128 = !DISubroutineType(types: !129)
!129 = !{!130, !24, !124, !43, !45}
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !132, size: 64, align: 64, offset: 1728)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !122)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !124, size: 64, align: 64, offset: 1792)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !138, size: 64, align: 64, offset: 1920)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !140)
!140 = !{!141, !142, !143, !144, !148, !152, !156, !157, !158, !159, !160, !161, !162}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !139, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !139, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !139, file: !6, line: 46, baseType: !138, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !139, file: !6, line: 47, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !138, !80, !80}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !139, file: !6, line: 49, baseType: !149, size: 64, align: 64, offset: 256)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DISubroutineType(types: !151)
!151 = !{!23, !138}
!152 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !139, file: !6, line: 50, baseType: !153, size: 64, align: 64, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DISubroutineType(types: !155)
!155 = !{!23, !138, !43, !45}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !139, file: !6, line: 51, baseType: !149, size: 64, align: 64, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !139, file: !6, line: 52, baseType: !149, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !139, file: !6, line: 53, baseType: !124, size: 64, align: 64, offset: 512)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !139, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !139, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !139, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !139, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !138, size: 64, align: 64, offset: 1984)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !124, size: 64, align: 64, offset: 2048)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !167, size: 64, align: 64, offset: 2176)
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DISubroutineType(types: !169)
!169 = !{!23, !4}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !171, size: 64, align: 64, offset: 2240)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DISubroutineType(types: !173)
!173 = !{!23, !4, !80, !80}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !167, size: 64, align: 64, offset: 2304)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !176, size: 64, align: 64, offset: 2368)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{!23, !4, !30}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !180, size: 64, align: 64, offset: 2432)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{!38, !4, !43, !45}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !167, size: 64, align: 64, offset: 2496)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !167, size: 64, align: 64, offset: 2560)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !187, size: 64, align: 64, offset: 2688)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !189)
!189 = !DISubroutineType(types: !190)
!190 = !{!80, !24, !124}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !124, size: 64, align: 64, offset: 2752)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "v7tar", file: !1, line: 48, size: 320, align: 64, elements: !194)
!194 = !{!195, !197, !198, !199, !200}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 49, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !193, file: !1, line: 50, baseType: !196, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !193, file: !1, line: 52, baseType: !102, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !193, file: !1, line: 53, baseType: !102, size: 64, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !193, file: !1, line: 54, baseType: !23, size: 32, align: 32, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !202, line: 70, baseType: !203)
!202 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!204 = !{!205, !206, !207, !208, !211, !214, !217, !218, !219, !220, !221}
!205 = distinct !DISubprogram(name: "archive_write_set_format_v7tar", scope: !1, file: !1, line: 144, type: !21, isLocal: false, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!206 = distinct !DISubprogram(name: "archive_write_v7tar_options", scope: !1, file: !1, line: 184, type: !172, isLocal: true, isDefinition: true, scopeLine: 186, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!207 = distinct !DISubprogram(name: "archive_write_v7tar_header", scope: !1, file: !1, line: 213, type: !177, isLocal: true, isDefinition: true, scopeLine: 214, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!208 = distinct !DISubprogram(name: "format_header_v7tar", scope: !1, file: !1, line: 363, type: !209, isLocal: true, isDefinition: true, scopeLine: 366, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!209 = !DISubroutineType(types: !210)
!210 = !{!23, !4, !95, !30, !23, !102}
!211 = distinct !DISubprogram(name: "format_number", scope: !1, file: !1, line: 539, type: !212, isLocal: true, isDefinition: true, scopeLine: 540, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = !DISubroutineType(types: !213)
!213 = !{!23, !52, !95, !23, !23, !23}
!214 = distinct !DISubprogram(name: "format_256", scope: !1, file: !1, line: 572, type: !215, isLocal: true, isDefinition: true, scopeLine: 573, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = !DISubroutineType(types: !216)
!216 = !{!23, !52, !95, !23}
!217 = distinct !DISubprogram(name: "format_octal", scope: !1, file: !1, line: 587, type: !215, isLocal: true, isDefinition: true, scopeLine: 588, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = distinct !DISubprogram(name: "archive_write_v7tar_close", scope: !1, file: !1, line: 617, type: !168, isLocal: true, isDefinition: true, scopeLine: 618, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_v7tar_free", scope: !1, file: !1, line: 623, type: !168, isLocal: true, isDefinition: true, scopeLine: 624, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "archive_write_v7tar_finish_entry", scope: !1, file: !1, line: 634, type: !168, isLocal: true, isDefinition: true, scopeLine: 635, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_write_v7tar_data", scope: !1, file: !1, line: 647, type: !181, isLocal: true, isDefinition: true, scopeLine: 648, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !{!223}
!223 = !DIGlobalVariable(name: "template_header", scope: !0, file: !1, line: 89, type: !224, isLocal: true, isDefinition: true, variable: [512 x i8]* @template_header)
!224 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 4096, align: 8, elements: !225)
!225 = !{!226}
!226 = !DISubrange(count: 512)
!227 = !{i32 2, !"Dwarf Version", i32 4}
!228 = !{i32 2, !"Debug Info Version", i32 3}
!229 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!230 = !DILocalVariable(name: "_a", arg: 1, scope: !205, file: !1, line: 144, type: !24)
!231 = !DIExpression()
!232 = !DILocation(line: 144, column: 48, scope: !205)
!233 = !DILocalVariable(name: "a", scope: !205, file: !1, line: 146, type: !4)
!234 = !DILocation(line: 146, column: 24, scope: !205)
!235 = !DILocation(line: 146, column: 52, scope: !205)
!236 = !DILocation(line: 146, column: 28, scope: !205)
!237 = !DILocalVariable(name: "v7tar", scope: !205, file: !1, line: 147, type: !192)
!238 = !DILocation(line: 147, column: 16, scope: !205)
!239 = !DILocation(line: 149, column: 2, scope: !205)
!240 = !DILocalVariable(name: "magic_test", scope: !241, file: !1, line: 149, type: !23)
!241 = distinct !DILexicalBlock(scope: !205, file: !1, line: 149, column: 2)
!242 = !DILocation(line: 149, column: 2, scope: !241)
!243 = !DILocation(line: 149, column: 2, scope: !244)
!244 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 1)
!245 = !DILocation(line: 149, column: 2, scope: !246)
!246 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 2)
!247 = distinct !DILexicalBlock(scope: !241, file: !1, line: 149, column: 2)
!248 = !DILocation(line: 149, column: 2, scope: !249)
!249 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 3)
!250 = !DILocation(line: 153, column: 6, scope: !251)
!251 = distinct !DILexicalBlock(scope: !205, file: !1, line: 153, column: 6)
!252 = !DILocation(line: 153, column: 9, scope: !251)
!253 = !DILocation(line: 153, column: 21, scope: !251)
!254 = !DILocation(line: 153, column: 6, scope: !205)
!255 = !DILocation(line: 154, column: 4, scope: !251)
!256 = !DILocation(line: 154, column: 7, scope: !251)
!257 = !DILocation(line: 154, column: 20, scope: !251)
!258 = !DILocation(line: 154, column: 3, scope: !251)
!259 = !DILocation(line: 164, column: 26, scope: !205)
!260 = !DILocation(line: 164, column: 10, scope: !205)
!261 = !DILocation(line: 164, column: 8, scope: !205)
!262 = !DILocation(line: 165, column: 6, scope: !263)
!263 = distinct !DILexicalBlock(scope: !205, file: !1, line: 165, column: 6)
!264 = !DILocation(line: 165, column: 12, scope: !263)
!265 = !DILocation(line: 165, column: 6, scope: !205)
!266 = !DILocation(line: 166, column: 22, scope: !267)
!267 = distinct !DILexicalBlock(scope: !263, file: !1, line: 165, column: 21)
!268 = !DILocation(line: 166, column: 25, scope: !267)
!269 = !DILocation(line: 166, column: 3, scope: !267)
!270 = !DILocation(line: 168, column: 3, scope: !267)
!271 = !DILocation(line: 170, column: 19, scope: !205)
!272 = !DILocation(line: 170, column: 2, scope: !205)
!273 = !DILocation(line: 170, column: 5, scope: !205)
!274 = !DILocation(line: 170, column: 17, scope: !205)
!275 = !DILocation(line: 171, column: 2, scope: !205)
!276 = !DILocation(line: 171, column: 5, scope: !205)
!277 = !DILocation(line: 171, column: 17, scope: !205)
!278 = !DILocation(line: 172, column: 2, scope: !205)
!279 = !DILocation(line: 172, column: 5, scope: !205)
!280 = !DILocation(line: 172, column: 20, scope: !205)
!281 = !DILocation(line: 173, column: 2, scope: !205)
!282 = !DILocation(line: 173, column: 5, scope: !205)
!283 = !DILocation(line: 173, column: 25, scope: !205)
!284 = !DILocation(line: 174, column: 2, scope: !205)
!285 = !DILocation(line: 174, column: 5, scope: !205)
!286 = !DILocation(line: 174, column: 23, scope: !205)
!287 = !DILocation(line: 175, column: 2, scope: !205)
!288 = !DILocation(line: 175, column: 5, scope: !205)
!289 = !DILocation(line: 175, column: 18, scope: !205)
!290 = !DILocation(line: 176, column: 2, scope: !205)
!291 = !DILocation(line: 176, column: 5, scope: !205)
!292 = !DILocation(line: 176, column: 17, scope: !205)
!293 = !DILocation(line: 177, column: 2, scope: !205)
!294 = !DILocation(line: 177, column: 5, scope: !205)
!295 = !DILocation(line: 177, column: 25, scope: !205)
!296 = !DILocation(line: 178, column: 2, scope: !205)
!297 = !DILocation(line: 178, column: 5, scope: !205)
!298 = !DILocation(line: 178, column: 13, scope: !205)
!299 = !DILocation(line: 178, column: 28, scope: !205)
!300 = !DILocation(line: 179, column: 2, scope: !205)
!301 = !DILocation(line: 179, column: 5, scope: !205)
!302 = !DILocation(line: 179, column: 13, scope: !205)
!303 = !DILocation(line: 179, column: 33, scope: !205)
!304 = !DILocation(line: 180, column: 2, scope: !205)
!305 = !DILocation(line: 181, column: 1, scope: !205)
!306 = !DILocalVariable(name: "a", arg: 1, scope: !206, file: !1, line: 184, type: !4)
!307 = !DILocation(line: 184, column: 51, scope: !206)
!308 = !DILocalVariable(name: "key", arg: 2, scope: !206, file: !1, line: 184, type: !80)
!309 = !DILocation(line: 184, column: 66, scope: !206)
!310 = !DILocalVariable(name: "val", arg: 3, scope: !206, file: !1, line: 185, type: !80)
!311 = !DILocation(line: 185, column: 17, scope: !206)
!312 = !DILocalVariable(name: "v7tar", scope: !206, file: !1, line: 187, type: !192)
!313 = !DILocation(line: 187, column: 16, scope: !206)
!314 = !DILocation(line: 187, column: 40, scope: !206)
!315 = !DILocation(line: 187, column: 43, scope: !206)
!316 = !DILocation(line: 187, column: 24, scope: !206)
!317 = !DILocalVariable(name: "ret", scope: !206, file: !1, line: 188, type: !23)
!318 = !DILocation(line: 188, column: 6, scope: !206)
!319 = !DILocation(line: 190, column: 13, scope: !320)
!320 = distinct !DILexicalBlock(scope: !206, file: !1, line: 190, column: 6)
!321 = !DILocation(line: 190, column: 6, scope: !320)
!322 = !DILocation(line: 190, column: 33, scope: !320)
!323 = !DILocation(line: 190, column: 6, scope: !206)
!324 = !DILocation(line: 191, column: 7, scope: !325)
!325 = distinct !DILexicalBlock(scope: !326, file: !1, line: 191, column: 7)
!326 = distinct !DILexicalBlock(scope: !320, file: !1, line: 190, column: 39)
!327 = !DILocation(line: 191, column: 11, scope: !325)
!328 = !DILocation(line: 191, column: 19, scope: !325)
!329 = !DILocation(line: 191, column: 22, scope: !330)
!330 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 1)
!331 = !DILocation(line: 191, column: 29, scope: !330)
!332 = !DILocation(line: 191, column: 7, scope: !330)
!333 = !DILocation(line: 192, column: 23, scope: !325)
!334 = !DILocation(line: 192, column: 26, scope: !325)
!335 = !DILocation(line: 194, column: 8, scope: !325)
!336 = !DILocation(line: 194, column: 11, scope: !325)
!337 = !DILocation(line: 192, column: 4, scope: !325)
!338 = !DILocation(line: 197, column: 9, scope: !339)
!339 = distinct !DILexicalBlock(scope: !325, file: !1, line: 195, column: 8)
!340 = !DILocation(line: 197, column: 12, scope: !339)
!341 = !DILocation(line: 197, column: 21, scope: !339)
!342 = !DILocation(line: 196, column: 23, scope: !339)
!343 = !DILocation(line: 196, column: 4, scope: !339)
!344 = !DILocation(line: 196, column: 11, scope: !339)
!345 = !DILocation(line: 196, column: 21, scope: !339)
!346 = !DILocation(line: 198, column: 8, scope: !347)
!347 = distinct !DILexicalBlock(scope: !339, file: !1, line: 198, column: 8)
!348 = !DILocation(line: 198, column: 15, scope: !347)
!349 = !DILocation(line: 198, column: 25, scope: !347)
!350 = !DILocation(line: 198, column: 8, scope: !339)
!351 = !DILocation(line: 199, column: 9, scope: !347)
!352 = !DILocation(line: 199, column: 5, scope: !347)
!353 = !DILocation(line: 201, column: 9, scope: !347)
!354 = !DILocation(line: 203, column: 11, scope: !326)
!355 = !DILocation(line: 203, column: 3, scope: !326)
!356 = !DILocation(line: 209, column: 2, scope: !206)
!357 = !DILocation(line: 210, column: 1, scope: !206)
!358 = !DILocalVariable(name: "a", arg: 1, scope: !207, file: !1, line: 213, type: !4)
!359 = !DILocation(line: 213, column: 50, scope: !207)
!360 = !DILocalVariable(name: "entry", arg: 2, scope: !207, file: !1, line: 213, type: !30)
!361 = !DILocation(line: 213, column: 75, scope: !207)
!362 = !DILocalVariable(name: "buff", scope: !207, file: !1, line: 215, type: !363)
!363 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 4096, align: 8, elements: !225)
!364 = !DILocation(line: 215, column: 7, scope: !207)
!365 = !DILocalVariable(name: "ret", scope: !207, file: !1, line: 216, type: !23)
!366 = !DILocation(line: 216, column: 6, scope: !207)
!367 = !DILocalVariable(name: "ret2", scope: !207, file: !1, line: 216, type: !23)
!368 = !DILocation(line: 216, column: 11, scope: !207)
!369 = !DILocalVariable(name: "v7tar", scope: !207, file: !1, line: 217, type: !192)
!370 = !DILocation(line: 217, column: 16, scope: !207)
!371 = !DILocalVariable(name: "entry_main", scope: !207, file: !1, line: 218, type: !30)
!372 = !DILocation(line: 218, column: 24, scope: !207)
!373 = !DILocalVariable(name: "sconv", scope: !207, file: !1, line: 219, type: !102)
!374 = !DILocation(line: 219, column: 30, scope: !207)
!375 = !DILocation(line: 221, column: 26, scope: !207)
!376 = !DILocation(line: 221, column: 29, scope: !207)
!377 = !DILocation(line: 221, column: 10, scope: !207)
!378 = !DILocation(line: 221, column: 8, scope: !207)
!379 = !DILocation(line: 224, column: 6, scope: !380)
!380 = distinct !DILexicalBlock(scope: !207, file: !1, line: 224, column: 6)
!381 = !DILocation(line: 224, column: 13, scope: !380)
!382 = !DILocation(line: 224, column: 23, scope: !380)
!383 = !DILocation(line: 224, column: 6, scope: !207)
!384 = !DILocation(line: 225, column: 8, scope: !385)
!385 = distinct !DILexicalBlock(scope: !386, file: !1, line: 225, column: 7)
!386 = distinct !DILexicalBlock(scope: !380, file: !1, line: 224, column: 32)
!387 = !DILocation(line: 225, column: 15, scope: !385)
!388 = !DILocation(line: 225, column: 7, scope: !386)
!389 = !DILocation(line: 228, column: 7, scope: !390)
!390 = distinct !DILexicalBlock(scope: !385, file: !1, line: 225, column: 40)
!391 = !DILocation(line: 228, column: 10, scope: !390)
!392 = !DILocation(line: 227, column: 8, scope: !390)
!393 = !DILocation(line: 226, column: 4, scope: !390)
!394 = !DILocation(line: 226, column: 11, scope: !390)
!395 = !DILocation(line: 226, column: 25, scope: !390)
!396 = !DILocation(line: 229, column: 4, scope: !390)
!397 = !DILocation(line: 229, column: 11, scope: !390)
!398 = !DILocation(line: 229, column: 35, scope: !390)
!399 = !DILocation(line: 230, column: 3, scope: !390)
!400 = !DILocation(line: 231, column: 11, scope: !386)
!401 = !DILocation(line: 231, column: 18, scope: !386)
!402 = !DILocation(line: 231, column: 9, scope: !386)
!403 = !DILocation(line: 232, column: 2, scope: !386)
!404 = !DILocation(line: 233, column: 11, scope: !380)
!405 = !DILocation(line: 233, column: 18, scope: !380)
!406 = !DILocation(line: 233, column: 9, scope: !380)
!407 = !DILocation(line: 236, column: 29, scope: !408)
!408 = distinct !DILexicalBlock(scope: !207, file: !1, line: 236, column: 6)
!409 = !DILocation(line: 236, column: 6, scope: !408)
!410 = !DILocation(line: 236, column: 36, scope: !408)
!411 = !DILocation(line: 236, column: 6, scope: !207)
!412 = !DILocation(line: 237, column: 22, scope: !413)
!413 = distinct !DILexicalBlock(scope: !408, file: !1, line: 236, column: 45)
!414 = !DILocation(line: 237, column: 25, scope: !413)
!415 = !DILocation(line: 237, column: 3, scope: !413)
!416 = !DILocation(line: 239, column: 3, scope: !413)
!417 = !DILocation(line: 243, column: 29, scope: !418)
!418 = distinct !DILexicalBlock(scope: !207, file: !1, line: 243, column: 6)
!419 = !DILocation(line: 243, column: 6, scope: !418)
!420 = !DILocation(line: 243, column: 36, scope: !418)
!421 = !DILocation(line: 243, column: 44, scope: !418)
!422 = !DILocation(line: 244, column: 28, scope: !418)
!423 = !DILocation(line: 244, column: 6, scope: !418)
!424 = !DILocation(line: 244, column: 35, scope: !418)
!425 = !DILocation(line: 244, column: 43, scope: !418)
!426 = !DILocation(line: 245, column: 31, scope: !418)
!427 = !DILocation(line: 245, column: 8, scope: !418)
!428 = !DILocation(line: 245, column: 38, scope: !418)
!429 = !DILocation(line: 243, column: 6, scope: !430)
!430 = !DILexicalBlockFile(scope: !207, file: !1, discriminator: 1)
!431 = !DILocation(line: 246, column: 26, scope: !418)
!432 = !DILocation(line: 246, column: 3, scope: !418)
!433 = !DILocation(line: 248, column: 41, scope: !434)
!434 = distinct !DILexicalBlock(scope: !207, file: !1, line: 248, column: 6)
!435 = !DILocation(line: 248, column: 18, scope: !434)
!436 = !DILocation(line: 248, column: 15, scope: !434)
!437 = !DILocation(line: 248, column: 6, scope: !207)
!438 = !DILocalVariable(name: "p", scope: !439, file: !1, line: 249, type: !80)
!439 = distinct !DILexicalBlock(scope: !434, file: !1, line: 248, column: 49)
!440 = !DILocation(line: 249, column: 15, scope: !439)
!441 = !DILocalVariable(name: "path_length", scope: !439, file: !1, line: 250, type: !45)
!442 = !DILocation(line: 250, column: 10, scope: !439)
!443 = !DILocation(line: 281, column: 31, scope: !439)
!444 = !DILocation(line: 281, column: 8, scope: !439)
!445 = !DILocation(line: 281, column: 6, scope: !439)
!446 = !DILocation(line: 287, column: 7, scope: !447)
!447 = distinct !DILexicalBlock(scope: !439, file: !1, line: 287, column: 7)
!448 = !DILocation(line: 287, column: 9, scope: !447)
!449 = !DILocation(line: 287, column: 17, scope: !447)
!450 = !DILocation(line: 287, column: 29, scope: !451)
!451 = !DILexicalBlockFile(scope: !447, file: !1, discriminator: 1)
!452 = !DILocation(line: 287, column: 22, scope: !451)
!453 = !DILocation(line: 287, column: 32, scope: !451)
!454 = !DILocation(line: 287, column: 20, scope: !451)
!455 = !DILocation(line: 287, column: 37, scope: !451)
!456 = !DILocation(line: 287, column: 7, scope: !451)
!457 = !DILocalVariable(name: "as", scope: !458, file: !1, line: 288, type: !91)
!458 = distinct !DILexicalBlock(scope: !447, file: !1, line: 287, column: 45)
!459 = !DILocation(line: 288, column: 26, scope: !458)
!460 = !DILocation(line: 290, column: 4, scope: !458)
!461 = !DILocation(line: 290, column: 4, scope: !462)
!462 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 1)
!463 = distinct !DILexicalBlock(scope: !458, file: !1, line: 290, column: 4)
!464 = !DILocation(line: 291, column: 25, scope: !458)
!465 = !DILocation(line: 291, column: 18, scope: !458)
!466 = !DILocation(line: 291, column: 16, scope: !458)
!467 = !DILocation(line: 293, column: 8, scope: !468)
!468 = distinct !DILexicalBlock(scope: !458, file: !1, line: 292, column: 8)
!469 = !DILocation(line: 293, column: 20, scope: !468)
!470 = !DILocation(line: 292, column: 8, scope: !468)
!471 = !DILocation(line: 293, column: 25, scope: !468)
!472 = !DILocation(line: 292, column: 8, scope: !458)
!473 = !DILocation(line: 294, column: 24, scope: !474)
!474 = distinct !DILexicalBlock(scope: !468, file: !1, line: 293, column: 34)
!475 = !DILocation(line: 294, column: 27, scope: !474)
!476 = !DILocation(line: 294, column: 5, scope: !474)
!477 = !DILocation(line: 296, column: 5, scope: !474)
!478 = !DILocation(line: 297, column: 5, scope: !474)
!479 = !DILocation(line: 308, column: 4, scope: !458)
!480 = !DILocation(line: 309, column: 4, scope: !458)
!481 = !DILocation(line: 310, column: 32, scope: !458)
!482 = !DILocation(line: 310, column: 42, scope: !458)
!483 = !DILocation(line: 310, column: 4, scope: !458)
!484 = !DILocation(line: 311, column: 4, scope: !458)
!485 = !DILocation(line: 312, column: 3, scope: !458)
!486 = !DILocation(line: 313, column: 2, scope: !439)
!487 = !DILocation(line: 329, column: 13, scope: !207)
!488 = !DILocation(line: 331, column: 28, scope: !207)
!489 = !DILocation(line: 331, column: 31, scope: !207)
!490 = !DILocation(line: 331, column: 37, scope: !207)
!491 = !DILocation(line: 331, column: 47, scope: !207)
!492 = !DILocation(line: 331, column: 8, scope: !207)
!493 = !DILocation(line: 331, column: 6, scope: !207)
!494 = !DILocation(line: 332, column: 6, scope: !495)
!495 = distinct !DILexicalBlock(scope: !207, file: !1, line: 332, column: 6)
!496 = !DILocation(line: 332, column: 10, scope: !495)
!497 = !DILocation(line: 332, column: 6, scope: !207)
!498 = !DILocation(line: 333, column: 7, scope: !499)
!499 = distinct !DILexicalBlock(scope: !500, file: !1, line: 333, column: 7)
!500 = distinct !DILexicalBlock(scope: !495, file: !1, line: 332, column: 26)
!501 = !DILocation(line: 333, column: 7, scope: !500)
!502 = !DILocation(line: 334, column: 23, scope: !499)
!503 = !DILocation(line: 334, column: 4, scope: !499)
!504 = !DILocation(line: 335, column: 11, scope: !500)
!505 = !DILocation(line: 335, column: 3, scope: !500)
!506 = !DILocation(line: 337, column: 32, scope: !207)
!507 = !DILocation(line: 337, column: 35, scope: !207)
!508 = !DILocation(line: 337, column: 9, scope: !207)
!509 = !DILocation(line: 337, column: 7, scope: !207)
!510 = !DILocation(line: 338, column: 6, scope: !511)
!511 = distinct !DILexicalBlock(scope: !207, file: !1, line: 338, column: 6)
!512 = !DILocation(line: 338, column: 11, scope: !511)
!513 = !DILocation(line: 338, column: 6, scope: !207)
!514 = !DILocation(line: 339, column: 7, scope: !515)
!515 = distinct !DILexicalBlock(scope: !516, file: !1, line: 339, column: 7)
!516 = distinct !DILexicalBlock(scope: !511, file: !1, line: 338, column: 27)
!517 = !DILocation(line: 339, column: 7, scope: !516)
!518 = !DILocation(line: 340, column: 23, scope: !515)
!519 = !DILocation(line: 340, column: 4, scope: !515)
!520 = !DILocation(line: 341, column: 11, scope: !516)
!521 = !DILocation(line: 341, column: 3, scope: !516)
!522 = !DILocation(line: 343, column: 6, scope: !523)
!523 = distinct !DILexicalBlock(scope: !207, file: !1, line: 343, column: 6)
!524 = !DILocation(line: 343, column: 13, scope: !523)
!525 = !DILocation(line: 343, column: 11, scope: !523)
!526 = !DILocation(line: 343, column: 6, scope: !207)
!527 = !DILocation(line: 344, column: 9, scope: !523)
!528 = !DILocation(line: 344, column: 7, scope: !523)
!529 = !DILocation(line: 344, column: 3, scope: !523)
!530 = !DILocation(line: 346, column: 52, scope: !207)
!531 = !DILocation(line: 346, column: 33, scope: !207)
!532 = !DILocation(line: 346, column: 2, scope: !207)
!533 = !DILocation(line: 346, column: 9, scope: !207)
!534 = !DILocation(line: 346, column: 31, scope: !207)
!535 = !DILocation(line: 347, column: 44, scope: !207)
!536 = !DILocation(line: 347, column: 51, scope: !207)
!537 = !DILocation(line: 347, column: 34, scope: !207)
!538 = !DILocation(line: 347, column: 31, scope: !207)
!539 = !DILocation(line: 347, column: 2, scope: !207)
!540 = !DILocation(line: 347, column: 9, scope: !207)
!541 = !DILocation(line: 347, column: 23, scope: !207)
!542 = !DILocation(line: 348, column: 6, scope: !543)
!543 = distinct !DILexicalBlock(scope: !207, file: !1, line: 348, column: 6)
!544 = !DILocation(line: 348, column: 6, scope: !207)
!545 = !DILocation(line: 349, column: 22, scope: !543)
!546 = !DILocation(line: 349, column: 3, scope: !543)
!547 = !DILocation(line: 350, column: 10, scope: !207)
!548 = !DILocation(line: 350, column: 2, scope: !207)
!549 = !DILocation(line: 351, column: 1, scope: !207)
!550 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 647, type: !4)
!551 = !DILocation(line: 647, column: 48, scope: !221)
!552 = !DILocalVariable(name: "buff", arg: 2, scope: !221, file: !1, line: 647, type: !43)
!553 = !DILocation(line: 647, column: 63, scope: !221)
!554 = !DILocalVariable(name: "s", arg: 3, scope: !221, file: !1, line: 647, type: !45)
!555 = !DILocation(line: 647, column: 76, scope: !221)
!556 = !DILocalVariable(name: "v7tar", scope: !221, file: !1, line: 649, type: !192)
!557 = !DILocation(line: 649, column: 16, scope: !221)
!558 = !DILocalVariable(name: "ret", scope: !221, file: !1, line: 650, type: !23)
!559 = !DILocation(line: 650, column: 6, scope: !221)
!560 = !DILocation(line: 652, column: 26, scope: !221)
!561 = !DILocation(line: 652, column: 29, scope: !221)
!562 = !DILocation(line: 652, column: 10, scope: !221)
!563 = !DILocation(line: 652, column: 8, scope: !221)
!564 = !DILocation(line: 653, column: 6, scope: !565)
!565 = distinct !DILexicalBlock(scope: !221, file: !1, line: 653, column: 6)
!566 = !DILocation(line: 653, column: 10, scope: !565)
!567 = !DILocation(line: 653, column: 17, scope: !565)
!568 = !DILocation(line: 653, column: 8, scope: !565)
!569 = !DILocation(line: 653, column: 6, scope: !221)
!570 = !DILocation(line: 654, column: 15, scope: !565)
!571 = !DILocation(line: 654, column: 22, scope: !565)
!572 = !DILocation(line: 654, column: 5, scope: !565)
!573 = !DILocation(line: 654, column: 3, scope: !565)
!574 = !DILocation(line: 655, column: 31, scope: !221)
!575 = !DILocation(line: 655, column: 34, scope: !221)
!576 = !DILocation(line: 655, column: 40, scope: !221)
!577 = !DILocation(line: 655, column: 8, scope: !221)
!578 = !DILocation(line: 655, column: 6, scope: !221)
!579 = !DILocation(line: 656, column: 34, scope: !221)
!580 = !DILocation(line: 656, column: 2, scope: !221)
!581 = !DILocation(line: 656, column: 9, scope: !221)
!582 = !DILocation(line: 656, column: 31, scope: !221)
!583 = !DILocation(line: 657, column: 6, scope: !584)
!584 = distinct !DILexicalBlock(scope: !221, file: !1, line: 657, column: 6)
!585 = !DILocation(line: 657, column: 10, scope: !584)
!586 = !DILocation(line: 657, column: 6, scope: !221)
!587 = !DILocation(line: 658, column: 11, scope: !584)
!588 = !DILocation(line: 658, column: 10, scope: !584)
!589 = !DILocation(line: 658, column: 3, scope: !584)
!590 = !DILocation(line: 659, column: 10, scope: !221)
!591 = !DILocation(line: 659, column: 2, scope: !221)
!592 = !DILocation(line: 660, column: 1, scope: !221)
!593 = !DILocalVariable(name: "a", arg: 1, scope: !218, file: !1, line: 617, type: !4)
!594 = !DILocation(line: 617, column: 49, scope: !218)
!595 = !DILocation(line: 619, column: 32, scope: !218)
!596 = !DILocation(line: 619, column: 10, scope: !218)
!597 = !DILocation(line: 619, column: 2, scope: !218)
!598 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 623, type: !4)
!599 = !DILocation(line: 623, column: 48, scope: !219)
!600 = !DILocalVariable(name: "v7tar", scope: !219, file: !1, line: 625, type: !192)
!601 = !DILocation(line: 625, column: 16, scope: !219)
!602 = !DILocation(line: 627, column: 26, scope: !219)
!603 = !DILocation(line: 627, column: 29, scope: !219)
!604 = !DILocation(line: 627, column: 10, scope: !219)
!605 = !DILocation(line: 627, column: 8, scope: !219)
!606 = !DILocation(line: 628, column: 7, scope: !219)
!607 = !DILocation(line: 628, column: 2, scope: !219)
!608 = !DILocation(line: 629, column: 2, scope: !219)
!609 = !DILocation(line: 629, column: 5, scope: !219)
!610 = !DILocation(line: 629, column: 17, scope: !219)
!611 = !DILocation(line: 630, column: 2, scope: !219)
!612 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 634, type: !4)
!613 = !DILocation(line: 634, column: 56, scope: !220)
!614 = !DILocalVariable(name: "v7tar", scope: !220, file: !1, line: 636, type: !192)
!615 = !DILocation(line: 636, column: 16, scope: !220)
!616 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 637, type: !23)
!617 = !DILocation(line: 637, column: 6, scope: !220)
!618 = !DILocation(line: 639, column: 26, scope: !220)
!619 = !DILocation(line: 639, column: 29, scope: !220)
!620 = !DILocation(line: 639, column: 10, scope: !220)
!621 = !DILocation(line: 639, column: 8, scope: !220)
!622 = !DILocation(line: 640, column: 30, scope: !220)
!623 = !DILocation(line: 641, column: 15, scope: !220)
!624 = !DILocation(line: 641, column: 22, scope: !220)
!625 = !DILocation(line: 641, column: 46, scope: !220)
!626 = !DILocation(line: 641, column: 53, scope: !220)
!627 = !DILocation(line: 641, column: 44, scope: !220)
!628 = !DILocation(line: 640, column: 8, scope: !220)
!629 = !DILocation(line: 640, column: 6, scope: !220)
!630 = !DILocation(line: 642, column: 33, scope: !220)
!631 = !DILocation(line: 642, column: 40, scope: !220)
!632 = !DILocation(line: 642, column: 54, scope: !220)
!633 = !DILocation(line: 642, column: 2, scope: !220)
!634 = !DILocation(line: 642, column: 9, scope: !220)
!635 = !DILocation(line: 642, column: 31, scope: !220)
!636 = !DILocation(line: 643, column: 10, scope: !220)
!637 = !DILocation(line: 643, column: 2, scope: !220)
!638 = !DILocalVariable(name: "a", arg: 1, scope: !208, file: !1, line: 363, type: !4)
!639 = !DILocation(line: 363, column: 43, scope: !208)
!640 = !DILocalVariable(name: "h", arg: 2, scope: !208, file: !1, line: 363, type: !95)
!641 = !DILocation(line: 363, column: 51, scope: !208)
!642 = !DILocalVariable(name: "entry", arg: 3, scope: !208, file: !1, line: 364, type: !30)
!643 = !DILocation(line: 364, column: 27, scope: !208)
!644 = !DILocalVariable(name: "strict", arg: 4, scope: !208, file: !1, line: 364, type: !23)
!645 = !DILocation(line: 364, column: 38, scope: !208)
!646 = !DILocalVariable(name: "sconv", arg: 5, scope: !208, file: !1, line: 365, type: !102)
!647 = !DILocation(line: 365, column: 33, scope: !208)
!648 = !DILocalVariable(name: "checksum", scope: !208, file: !1, line: 367, type: !13)
!649 = !DILocation(line: 367, column: 15, scope: !208)
!650 = !DILocalVariable(name: "i", scope: !208, file: !1, line: 368, type: !23)
!651 = !DILocation(line: 368, column: 6, scope: !208)
!652 = !DILocalVariable(name: "r", scope: !208, file: !1, line: 368, type: !23)
!653 = !DILocation(line: 368, column: 9, scope: !208)
!654 = !DILocalVariable(name: "ret", scope: !208, file: !1, line: 368, type: !23)
!655 = !DILocation(line: 368, column: 12, scope: !208)
!656 = !DILocalVariable(name: "copy_length", scope: !208, file: !1, line: 369, type: !45)
!657 = !DILocation(line: 369, column: 9, scope: !208)
!658 = !DILocalVariable(name: "p", scope: !208, file: !1, line: 370, type: !80)
!659 = !DILocation(line: 370, column: 14, scope: !208)
!660 = !DILocalVariable(name: "pp", scope: !208, file: !1, line: 370, type: !80)
!661 = !DILocation(line: 370, column: 18, scope: !208)
!662 = !DILocalVariable(name: "mytartype", scope: !208, file: !1, line: 371, type: !23)
!663 = !DILocation(line: 371, column: 6, scope: !208)
!664 = !DILocation(line: 373, column: 6, scope: !208)
!665 = !DILocation(line: 374, column: 12, scope: !208)
!666 = !DILocation(line: 380, column: 9, scope: !208)
!667 = !DILocation(line: 380, column: 2, scope: !208)
!668 = !DILocation(line: 387, column: 31, scope: !208)
!669 = !DILocation(line: 387, column: 57, scope: !208)
!670 = !DILocation(line: 387, column: 6, scope: !208)
!671 = !DILocation(line: 387, column: 4, scope: !208)
!672 = !DILocation(line: 388, column: 6, scope: !673)
!673 = distinct !DILexicalBlock(scope: !208, file: !1, line: 388, column: 6)
!674 = !DILocation(line: 388, column: 8, scope: !673)
!675 = !DILocation(line: 388, column: 6, scope: !208)
!676 = !DILocation(line: 389, column: 7, scope: !677)
!677 = distinct !DILexicalBlock(scope: !678, file: !1, line: 389, column: 7)
!678 = distinct !DILexicalBlock(scope: !673, file: !1, line: 388, column: 14)
!679 = !DILocation(line: 389, column: 13, scope: !677)
!680 = !DILocation(line: 389, column: 7, scope: !678)
!681 = !DILocation(line: 390, column: 23, scope: !682)
!682 = distinct !DILexicalBlock(scope: !677, file: !1, line: 389, column: 24)
!683 = !DILocation(line: 390, column: 26, scope: !682)
!684 = !DILocation(line: 390, column: 4, scope: !682)
!685 = !DILocation(line: 392, column: 4, scope: !682)
!686 = !DILocation(line: 394, column: 22, scope: !678)
!687 = !DILocation(line: 394, column: 25, scope: !678)
!688 = !DILocation(line: 396, column: 7, scope: !678)
!689 = !DILocation(line: 396, column: 50, scope: !678)
!690 = !DILocation(line: 396, column: 11, scope: !678)
!691 = !DILocation(line: 394, column: 3, scope: !678)
!692 = !DILocation(line: 397, column: 7, scope: !678)
!693 = !DILocation(line: 398, column: 2, scope: !678)
!694 = !DILocation(line: 399, column: 6, scope: !695)
!695 = distinct !DILexicalBlock(scope: !208, file: !1, line: 399, column: 6)
!696 = !DILocation(line: 399, column: 13, scope: !695)
!697 = !DILocation(line: 399, column: 16, scope: !698)
!698 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 1)
!699 = !DILocation(line: 399, column: 28, scope: !698)
!700 = !DILocation(line: 399, column: 6, scope: !698)
!701 = !DILocation(line: 400, column: 10, scope: !695)
!702 = !DILocation(line: 400, column: 12, scope: !695)
!703 = !DILocation(line: 400, column: 33, scope: !695)
!704 = !DILocation(line: 400, column: 37, scope: !695)
!705 = !DILocation(line: 400, column: 3, scope: !695)
!706 = !DILocation(line: 401, column: 12, scope: !707)
!707 = distinct !DILexicalBlock(scope: !695, file: !1, line: 401, column: 11)
!708 = !DILocation(line: 401, column: 19, scope: !707)
!709 = !DILocation(line: 401, column: 22, scope: !710)
!710 = !DILexicalBlockFile(scope: !707, file: !1, discriminator: 1)
!711 = !DILocation(line: 401, column: 34, scope: !710)
!712 = !DILocation(line: 401, column: 11, scope: !710)
!713 = !DILocation(line: 402, column: 10, scope: !707)
!714 = !DILocation(line: 402, column: 12, scope: !707)
!715 = !DILocation(line: 402, column: 33, scope: !707)
!716 = !DILocation(line: 402, column: 37, scope: !707)
!717 = !DILocation(line: 402, column: 3, scope: !707)
!718 = !DILocation(line: 405, column: 22, scope: !719)
!719 = distinct !DILexicalBlock(scope: !707, file: !1, line: 403, column: 7)
!720 = !DILocation(line: 405, column: 25, scope: !719)
!721 = !DILocation(line: 405, column: 3, scope: !719)
!722 = !DILocation(line: 407, column: 7, scope: !719)
!723 = !DILocation(line: 410, column: 31, scope: !208)
!724 = !DILocation(line: 410, column: 56, scope: !208)
!725 = !DILocation(line: 410, column: 6, scope: !208)
!726 = !DILocation(line: 410, column: 4, scope: !208)
!727 = !DILocation(line: 411, column: 6, scope: !728)
!728 = distinct !DILexicalBlock(scope: !208, file: !1, line: 411, column: 6)
!729 = !DILocation(line: 411, column: 8, scope: !728)
!730 = !DILocation(line: 411, column: 6, scope: !208)
!731 = !DILocation(line: 412, column: 7, scope: !732)
!732 = distinct !DILexicalBlock(scope: !733, file: !1, line: 412, column: 7)
!733 = distinct !DILexicalBlock(scope: !728, file: !1, line: 411, column: 14)
!734 = !DILocation(line: 412, column: 13, scope: !732)
!735 = !DILocation(line: 412, column: 7, scope: !733)
!736 = !DILocation(line: 413, column: 23, scope: !737)
!737 = distinct !DILexicalBlock(scope: !732, file: !1, line: 412, column: 24)
!738 = !DILocation(line: 413, column: 26, scope: !737)
!739 = !DILocation(line: 413, column: 4, scope: !737)
!740 = !DILocation(line: 415, column: 4, scope: !737)
!741 = !DILocation(line: 417, column: 22, scope: !733)
!742 = !DILocation(line: 417, column: 25, scope: !733)
!743 = !DILocation(line: 420, column: 7, scope: !733)
!744 = !DILocation(line: 420, column: 49, scope: !733)
!745 = !DILocation(line: 420, column: 10, scope: !733)
!746 = !DILocation(line: 417, column: 3, scope: !733)
!747 = !DILocation(line: 421, column: 7, scope: !733)
!748 = !DILocation(line: 422, column: 2, scope: !733)
!749 = !DILocation(line: 423, column: 6, scope: !750)
!750 = distinct !DILexicalBlock(scope: !208, file: !1, line: 423, column: 6)
!751 = !DILocation(line: 423, column: 18, scope: !750)
!752 = !DILocation(line: 423, column: 6, scope: !208)
!753 = !DILocation(line: 424, column: 13, scope: !750)
!754 = !DILocation(line: 424, column: 3, scope: !750)
!755 = !DILocation(line: 426, column: 31, scope: !756)
!756 = distinct !DILexicalBlock(scope: !750, file: !1, line: 425, column: 7)
!757 = !DILocation(line: 426, column: 56, scope: !756)
!758 = !DILocation(line: 426, column: 7, scope: !756)
!759 = !DILocation(line: 426, column: 5, scope: !756)
!760 = !DILocation(line: 427, column: 7, scope: !761)
!761 = distinct !DILexicalBlock(scope: !756, file: !1, line: 427, column: 7)
!762 = !DILocation(line: 427, column: 9, scope: !761)
!763 = !DILocation(line: 427, column: 7, scope: !756)
!764 = !DILocation(line: 428, column: 8, scope: !765)
!765 = distinct !DILexicalBlock(scope: !766, file: !1, line: 428, column: 8)
!766 = distinct !DILexicalBlock(scope: !761, file: !1, line: 427, column: 15)
!767 = !DILocation(line: 428, column: 14, scope: !765)
!768 = !DILocation(line: 428, column: 8, scope: !766)
!769 = !DILocation(line: 429, column: 24, scope: !770)
!770 = distinct !DILexicalBlock(scope: !765, file: !1, line: 428, column: 25)
!771 = !DILocation(line: 429, column: 27, scope: !770)
!772 = !DILocation(line: 429, column: 5, scope: !770)
!773 = !DILocation(line: 431, column: 5, scope: !770)
!774 = !DILocation(line: 433, column: 23, scope: !766)
!775 = !DILocation(line: 433, column: 26, scope: !766)
!776 = !DILocation(line: 436, column: 8, scope: !766)
!777 = !DILocation(line: 436, column: 50, scope: !766)
!778 = !DILocation(line: 436, column: 11, scope: !766)
!779 = !DILocation(line: 433, column: 4, scope: !766)
!780 = !DILocation(line: 437, column: 8, scope: !766)
!781 = !DILocation(line: 438, column: 3, scope: !766)
!782 = !DILocation(line: 440, column: 6, scope: !783)
!783 = distinct !DILexicalBlock(scope: !208, file: !1, line: 440, column: 6)
!784 = !DILocation(line: 440, column: 18, scope: !783)
!785 = !DILocation(line: 440, column: 6, scope: !208)
!786 = !DILocation(line: 441, column: 7, scope: !787)
!787 = distinct !DILexicalBlock(scope: !788, file: !1, line: 441, column: 7)
!788 = distinct !DILexicalBlock(scope: !783, file: !1, line: 440, column: 23)
!789 = !DILocation(line: 441, column: 19, scope: !787)
!790 = !DILocation(line: 441, column: 7, scope: !788)
!791 = !DILocation(line: 442, column: 23, scope: !792)
!792 = distinct !DILexicalBlock(scope: !787, file: !1, line: 441, column: 43)
!793 = !DILocation(line: 442, column: 26, scope: !792)
!794 = !DILocation(line: 442, column: 4, scope: !792)
!795 = !DILocation(line: 444, column: 8, scope: !792)
!796 = !DILocation(line: 445, column: 16, scope: !792)
!797 = !DILocation(line: 446, column: 3, scope: !792)
!798 = !DILocation(line: 447, column: 10, scope: !788)
!799 = !DILocation(line: 447, column: 12, scope: !788)
!800 = !DILocation(line: 447, column: 37, scope: !788)
!801 = !DILocation(line: 447, column: 40, scope: !788)
!802 = !DILocation(line: 447, column: 3, scope: !788)
!803 = !DILocation(line: 448, column: 2, scope: !788)
!804 = !DILocation(line: 450, column: 39, scope: !805)
!805 = distinct !DILexicalBlock(scope: !208, file: !1, line: 450, column: 6)
!806 = !DILocation(line: 450, column: 20, scope: !805)
!807 = !DILocation(line: 450, column: 46, scope: !805)
!808 = !DILocation(line: 451, column: 6, scope: !805)
!809 = !DILocation(line: 451, column: 8, scope: !805)
!810 = !DILocation(line: 452, column: 27, scope: !805)
!811 = !DILocation(line: 450, column: 6, scope: !812)
!812 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 1)
!813 = !DILocation(line: 450, column: 6, scope: !805)
!814 = !DILocation(line: 450, column: 6, scope: !208)
!815 = !DILocation(line: 453, column: 22, scope: !816)
!816 = distinct !DILexicalBlock(scope: !805, file: !1, line: 452, column: 36)
!817 = !DILocation(line: 453, column: 25, scope: !816)
!818 = !DILocation(line: 453, column: 3, scope: !816)
!819 = !DILocation(line: 455, column: 7, scope: !816)
!820 = !DILocation(line: 456, column: 2, scope: !816)
!821 = !DILocation(line: 458, column: 38, scope: !822)
!822 = distinct !DILexicalBlock(scope: !208, file: !1, line: 458, column: 6)
!823 = !DILocation(line: 458, column: 20, scope: !822)
!824 = !DILocation(line: 459, column: 6, scope: !822)
!825 = !DILocation(line: 459, column: 8, scope: !822)
!826 = !DILocation(line: 459, column: 64, scope: !822)
!827 = !DILocation(line: 458, column: 6, scope: !828)
!828 = !DILexicalBlockFile(scope: !822, file: !1, discriminator: 1)
!829 = !DILocation(line: 458, column: 6, scope: !822)
!830 = !DILocation(line: 458, column: 6, scope: !208)
!831 = !DILocation(line: 460, column: 22, scope: !832)
!832 = distinct !DILexicalBlock(scope: !822, file: !1, line: 459, column: 73)
!833 = !DILocation(line: 460, column: 25, scope: !832)
!834 = !DILocation(line: 460, column: 3, scope: !832)
!835 = !DILocation(line: 462, column: 7, scope: !832)
!836 = !DILocation(line: 463, column: 2, scope: !832)
!837 = !DILocation(line: 465, column: 38, scope: !838)
!838 = distinct !DILexicalBlock(scope: !208, file: !1, line: 465, column: 6)
!839 = !DILocation(line: 465, column: 20, scope: !838)
!840 = !DILocation(line: 466, column: 6, scope: !838)
!841 = !DILocation(line: 466, column: 8, scope: !838)
!842 = !DILocation(line: 466, column: 64, scope: !838)
!843 = !DILocation(line: 465, column: 6, scope: !844)
!844 = !DILexicalBlockFile(scope: !838, file: !1, discriminator: 1)
!845 = !DILocation(line: 465, column: 6, scope: !838)
!846 = !DILocation(line: 465, column: 6, scope: !208)
!847 = !DILocation(line: 467, column: 22, scope: !848)
!848 = distinct !DILexicalBlock(scope: !838, file: !1, line: 466, column: 73)
!849 = !DILocation(line: 467, column: 25, scope: !848)
!850 = !DILocation(line: 467, column: 3, scope: !848)
!851 = !DILocation(line: 469, column: 7, scope: !848)
!852 = !DILocation(line: 470, column: 2, scope: !848)
!853 = !DILocation(line: 472, column: 39, scope: !854)
!854 = distinct !DILexicalBlock(scope: !208, file: !1, line: 472, column: 6)
!855 = !DILocation(line: 472, column: 20, scope: !854)
!856 = !DILocation(line: 473, column: 6, scope: !854)
!857 = !DILocation(line: 473, column: 8, scope: !854)
!858 = !DILocation(line: 474, column: 27, scope: !854)
!859 = !DILocation(line: 472, column: 6, scope: !860)
!860 = !DILexicalBlockFile(scope: !854, file: !1, discriminator: 1)
!861 = !DILocation(line: 472, column: 6, scope: !854)
!862 = !DILocation(line: 472, column: 6, scope: !208)
!863 = !DILocation(line: 475, column: 22, scope: !864)
!864 = distinct !DILexicalBlock(scope: !854, file: !1, line: 474, column: 36)
!865 = !DILocation(line: 475, column: 25, scope: !864)
!866 = !DILocation(line: 475, column: 3, scope: !864)
!867 = !DILocation(line: 477, column: 7, scope: !864)
!868 = !DILocation(line: 478, column: 2, scope: !864)
!869 = !DILocation(line: 480, column: 40, scope: !870)
!870 = distinct !DILexicalBlock(scope: !208, file: !1, line: 480, column: 6)
!871 = !DILocation(line: 480, column: 20, scope: !870)
!872 = !DILocation(line: 481, column: 6, scope: !870)
!873 = !DILocation(line: 481, column: 8, scope: !870)
!874 = !DILocation(line: 482, column: 28, scope: !870)
!875 = !DILocation(line: 480, column: 6, scope: !876)
!876 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 1)
!877 = !DILocation(line: 480, column: 6, scope: !870)
!878 = !DILocation(line: 480, column: 6, scope: !208)
!879 = !DILocation(line: 483, column: 22, scope: !880)
!880 = distinct !DILexicalBlock(scope: !870, file: !1, line: 482, column: 37)
!881 = !DILocation(line: 483, column: 25, scope: !880)
!882 = !DILocation(line: 483, column: 3, scope: !880)
!883 = !DILocation(line: 485, column: 7, scope: !880)
!884 = !DILocation(line: 486, column: 2, scope: !880)
!885 = !DILocation(line: 488, column: 6, scope: !886)
!886 = distinct !DILexicalBlock(scope: !208, file: !1, line: 488, column: 6)
!887 = !DILocation(line: 488, column: 16, scope: !886)
!888 = !DILocation(line: 488, column: 6, scope: !208)
!889 = !DILocation(line: 489, column: 30, scope: !890)
!890 = distinct !DILexicalBlock(scope: !886, file: !1, line: 488, column: 22)
!891 = !DILocation(line: 489, column: 3, scope: !890)
!892 = !DILocation(line: 489, column: 28, scope: !890)
!893 = !DILocation(line: 490, column: 2, scope: !890)
!894 = !DILocation(line: 491, column: 34, scope: !895)
!895 = distinct !DILexicalBlock(scope: !886, file: !1, line: 490, column: 9)
!896 = !DILocation(line: 491, column: 11, scope: !895)
!897 = !DILocation(line: 491, column: 3, scope: !895)
!898 = !DILocation(line: 493, column: 4, scope: !899)
!899 = distinct !DILexicalBlock(scope: !895, file: !1, line: 491, column: 42)
!900 = !DILocation(line: 495, column: 4, scope: !899)
!901 = !DILocation(line: 495, column: 29, scope: !899)
!902 = !DILocation(line: 496, column: 4, scope: !899)
!903 = !DILocation(line: 498, column: 23, scope: !899)
!904 = !DILocation(line: 498, column: 26, scope: !899)
!905 = !DILocation(line: 498, column: 4, scope: !899)
!906 = !DILocation(line: 501, column: 4, scope: !899)
!907 = !DILocation(line: 503, column: 23, scope: !899)
!908 = !DILocation(line: 503, column: 26, scope: !899)
!909 = !DILocation(line: 503, column: 4, scope: !899)
!910 = !DILocation(line: 506, column: 4, scope: !899)
!911 = !DILocation(line: 508, column: 23, scope: !899)
!912 = !DILocation(line: 508, column: 26, scope: !899)
!913 = !DILocation(line: 508, column: 4, scope: !899)
!914 = !DILocation(line: 511, column: 4, scope: !899)
!915 = !DILocation(line: 513, column: 23, scope: !899)
!916 = !DILocation(line: 513, column: 26, scope: !899)
!917 = !DILocation(line: 513, column: 4, scope: !899)
!918 = !DILocation(line: 516, column: 4, scope: !899)
!919 = !DILocation(line: 518, column: 23, scope: !899)
!920 = !DILocation(line: 518, column: 26, scope: !899)
!921 = !DILocation(line: 521, column: 42, scope: !899)
!922 = !DILocation(line: 521, column: 23, scope: !899)
!923 = !DILocation(line: 521, column: 8, scope: !899)
!924 = !DILocation(line: 518, column: 4, scope: !899)
!925 = !DILocation(line: 522, column: 8, scope: !899)
!926 = !DILocation(line: 523, column: 3, scope: !899)
!927 = !DILocation(line: 526, column: 11, scope: !208)
!928 = !DILocation(line: 527, column: 9, scope: !929)
!929 = distinct !DILexicalBlock(scope: !208, file: !1, line: 527, column: 2)
!930 = !DILocation(line: 527, column: 7, scope: !929)
!931 = !DILocation(line: 527, column: 14, scope: !932)
!932 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 1)
!933 = distinct !DILexicalBlock(scope: !929, file: !1, line: 527, column: 2)
!934 = !DILocation(line: 527, column: 16, scope: !932)
!935 = !DILocation(line: 527, column: 2, scope: !932)
!936 = !DILocation(line: 528, column: 37, scope: !933)
!937 = !DILocation(line: 528, column: 35, scope: !933)
!938 = !DILocation(line: 528, column: 21, scope: !933)
!939 = !DILocation(line: 528, column: 19, scope: !933)
!940 = !DILocation(line: 528, column: 12, scope: !933)
!941 = !DILocation(line: 528, column: 3, scope: !933)
!942 = !DILocation(line: 527, column: 24, scope: !943)
!943 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 2)
!944 = !DILocation(line: 527, column: 2, scope: !943)
!945 = !DILocation(line: 529, column: 15, scope: !208)
!946 = !DILocation(line: 529, column: 25, scope: !208)
!947 = !DILocation(line: 529, column: 27, scope: !208)
!948 = !DILocation(line: 529, column: 2, scope: !208)
!949 = !DILocation(line: 531, column: 2, scope: !208)
!950 = !DILocation(line: 531, column: 31, scope: !208)
!951 = !DILocation(line: 532, column: 10, scope: !208)
!952 = !DILocation(line: 532, column: 2, scope: !208)
!953 = !DILocation(line: 533, column: 1, scope: !208)
!954 = !DILocalVariable(name: "v", arg: 1, scope: !211, file: !1, line: 539, type: !52)
!955 = !DILocation(line: 539, column: 23, scope: !211)
!956 = !DILocalVariable(name: "p", arg: 2, scope: !211, file: !1, line: 539, type: !95)
!957 = !DILocation(line: 539, column: 32, scope: !211)
!958 = !DILocalVariable(name: "s", arg: 3, scope: !211, file: !1, line: 539, type: !23)
!959 = !DILocation(line: 539, column: 39, scope: !211)
!960 = !DILocalVariable(name: "maxsize", arg: 4, scope: !211, file: !1, line: 539, type: !23)
!961 = !DILocation(line: 539, column: 46, scope: !211)
!962 = !DILocalVariable(name: "strict", arg: 5, scope: !211, file: !1, line: 539, type: !23)
!963 = !DILocation(line: 539, column: 59, scope: !211)
!964 = !DILocalVariable(name: "limit", scope: !211, file: !1, line: 541, type: !52)
!965 = !DILocation(line: 541, column: 10, scope: !211)
!966 = !DILocation(line: 543, column: 26, scope: !211)
!967 = !DILocation(line: 543, column: 27, scope: !211)
!968 = !DILocation(line: 543, column: 22, scope: !211)
!969 = !DILocation(line: 543, column: 8, scope: !211)
!970 = !DILocation(line: 546, column: 6, scope: !971)
!971 = distinct !DILexicalBlock(scope: !211, file: !1, line: 546, column: 6)
!972 = !DILocation(line: 546, column: 6, scope: !211)
!973 = !DILocation(line: 547, column: 24, scope: !971)
!974 = !DILocation(line: 547, column: 27, scope: !971)
!975 = !DILocation(line: 547, column: 30, scope: !971)
!976 = !DILocation(line: 547, column: 11, scope: !971)
!977 = !DILocation(line: 547, column: 3, scope: !971)
!978 = !DILocation(line: 555, column: 6, scope: !979)
!979 = distinct !DILexicalBlock(scope: !211, file: !1, line: 555, column: 6)
!980 = !DILocation(line: 555, column: 8, scope: !979)
!981 = !DILocation(line: 555, column: 6, scope: !211)
!982 = !DILocation(line: 556, column: 3, scope: !983)
!983 = distinct !DILexicalBlock(scope: !979, file: !1, line: 555, column: 14)
!984 = !DILocation(line: 556, column: 10, scope: !985)
!985 = !DILexicalBlockFile(scope: !983, file: !1, discriminator: 1)
!986 = !DILocation(line: 556, column: 15, scope: !985)
!987 = !DILocation(line: 556, column: 12, scope: !985)
!988 = !DILocation(line: 556, column: 3, scope: !985)
!989 = !DILocation(line: 557, column: 8, scope: !990)
!990 = distinct !DILexicalBlock(scope: !991, file: !1, line: 557, column: 8)
!991 = distinct !DILexicalBlock(scope: !983, file: !1, line: 556, column: 24)
!992 = !DILocation(line: 557, column: 12, scope: !990)
!993 = !DILocation(line: 557, column: 10, scope: !990)
!994 = !DILocation(line: 557, column: 8, scope: !991)
!995 = !DILocation(line: 558, column: 26, scope: !990)
!996 = !DILocation(line: 558, column: 29, scope: !990)
!997 = !DILocation(line: 558, column: 32, scope: !990)
!998 = !DILocation(line: 558, column: 13, scope: !990)
!999 = !DILocation(line: 558, column: 5, scope: !990)
!1000 = !DILocation(line: 559, column: 5, scope: !991)
!1001 = !DILocation(line: 560, column: 10, scope: !991)
!1002 = !DILocation(line: 556, column: 3, scope: !1003)
!1003 = !DILexicalBlockFile(scope: !983, file: !1, discriminator: 2)
!1004 = !DILocation(line: 562, column: 2, scope: !983)
!1005 = !DILocation(line: 565, column: 21, scope: !211)
!1006 = !DILocation(line: 565, column: 24, scope: !211)
!1007 = !DILocation(line: 565, column: 27, scope: !211)
!1008 = !DILocation(line: 565, column: 10, scope: !211)
!1009 = !DILocation(line: 565, column: 2, scope: !211)
!1010 = !DILocation(line: 566, column: 1, scope: !211)
!1011 = !DILocalVariable(name: "v", arg: 1, scope: !217, file: !1, line: 587, type: !52)
!1012 = !DILocation(line: 587, column: 22, scope: !217)
!1013 = !DILocalVariable(name: "p", arg: 2, scope: !217, file: !1, line: 587, type: !95)
!1014 = !DILocation(line: 587, column: 31, scope: !217)
!1015 = !DILocalVariable(name: "s", arg: 3, scope: !217, file: !1, line: 587, type: !23)
!1016 = !DILocation(line: 587, column: 38, scope: !217)
!1017 = !DILocalVariable(name: "len", scope: !217, file: !1, line: 589, type: !23)
!1018 = !DILocation(line: 589, column: 6, scope: !217)
!1019 = !DILocation(line: 591, column: 8, scope: !217)
!1020 = !DILocation(line: 591, column: 6, scope: !217)
!1021 = !DILocation(line: 594, column: 6, scope: !1022)
!1022 = distinct !DILexicalBlock(scope: !217, file: !1, line: 594, column: 6)
!1023 = !DILocation(line: 594, column: 8, scope: !1022)
!1024 = !DILocation(line: 594, column: 6, scope: !217)
!1025 = !DILocation(line: 595, column: 3, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !1022, file: !1, line: 594, column: 13)
!1027 = !DILocation(line: 595, column: 13, scope: !1028)
!1028 = !DILexicalBlockFile(scope: !1026, file: !1, discriminator: 1)
!1029 = !DILocation(line: 595, column: 16, scope: !1028)
!1030 = !DILocation(line: 595, column: 3, scope: !1028)
!1031 = !DILocation(line: 596, column: 6, scope: !1026)
!1032 = !DILocation(line: 596, column: 9, scope: !1026)
!1033 = !DILocation(line: 595, column: 3, scope: !1034)
!1034 = !DILexicalBlockFile(scope: !1026, file: !1, discriminator: 2)
!1035 = !DILocation(line: 597, column: 3, scope: !1026)
!1036 = !DILocation(line: 600, column: 7, scope: !217)
!1037 = !DILocation(line: 600, column: 4, scope: !217)
!1038 = !DILocation(line: 601, column: 2, scope: !217)
!1039 = !DILocation(line: 601, column: 10, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 1)
!1041 = !DILocation(line: 601, column: 13, scope: !1040)
!1042 = !DILocation(line: 601, column: 2, scope: !1040)
!1043 = !DILocation(line: 602, column: 24, scope: !1044)
!1044 = distinct !DILexicalBlock(scope: !217, file: !1, line: 601, column: 18)
!1045 = !DILocation(line: 602, column: 26, scope: !1044)
!1046 = !DILocation(line: 602, column: 21, scope: !1044)
!1047 = !DILocation(line: 602, column: 10, scope: !1044)
!1048 = !DILocation(line: 602, column: 4, scope: !1044)
!1049 = !DILocation(line: 602, column: 8, scope: !1044)
!1050 = !DILocation(line: 603, column: 5, scope: !1044)
!1051 = !DILocation(line: 601, column: 2, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 2)
!1053 = !DILocation(line: 606, column: 6, scope: !1054)
!1054 = distinct !DILexicalBlock(scope: !217, file: !1, line: 606, column: 6)
!1055 = !DILocation(line: 606, column: 8, scope: !1054)
!1056 = !DILocation(line: 606, column: 6, scope: !217)
!1057 = !DILocation(line: 607, column: 3, scope: !1054)
!1058 = !DILocation(line: 610, column: 2, scope: !217)
!1059 = !DILocation(line: 610, column: 12, scope: !1040)
!1060 = !DILocation(line: 610, column: 15, scope: !1040)
!1061 = !DILocation(line: 610, column: 2, scope: !1040)
!1062 = !DILocation(line: 611, column: 5, scope: !217)
!1063 = !DILocation(line: 611, column: 8, scope: !217)
!1064 = !DILocation(line: 610, column: 2, scope: !1052)
!1065 = !DILocation(line: 613, column: 2, scope: !217)
!1066 = !DILocation(line: 614, column: 1, scope: !217)
!1067 = !DILocalVariable(name: "v", arg: 1, scope: !214, file: !1, line: 572, type: !52)
!1068 = !DILocation(line: 572, column: 20, scope: !214)
!1069 = !DILocalVariable(name: "p", arg: 2, scope: !214, file: !1, line: 572, type: !95)
!1070 = !DILocation(line: 572, column: 29, scope: !214)
!1071 = !DILocalVariable(name: "s", arg: 3, scope: !214, file: !1, line: 572, type: !23)
!1072 = !DILocation(line: 572, column: 36, scope: !214)
!1073 = !DILocation(line: 574, column: 7, scope: !214)
!1074 = !DILocation(line: 574, column: 4, scope: !214)
!1075 = !DILocation(line: 575, column: 2, scope: !214)
!1076 = !DILocation(line: 575, column: 10, scope: !1077)
!1077 = !DILexicalBlockFile(scope: !214, file: !1, discriminator: 1)
!1078 = !DILocation(line: 575, column: 13, scope: !1077)
!1079 = !DILocation(line: 575, column: 2, scope: !1077)
!1080 = !DILocation(line: 576, column: 17, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !214, file: !1, line: 575, column: 18)
!1082 = !DILocation(line: 576, column: 19, scope: !1081)
!1083 = !DILocation(line: 576, column: 10, scope: !1081)
!1084 = !DILocation(line: 576, column: 4, scope: !1081)
!1085 = !DILocation(line: 576, column: 8, scope: !1081)
!1086 = !DILocation(line: 577, column: 5, scope: !1081)
!1087 = !DILocation(line: 575, column: 2, scope: !1088)
!1088 = !DILexicalBlockFile(scope: !214, file: !1, discriminator: 2)
!1089 = !DILocation(line: 579, column: 3, scope: !214)
!1090 = !DILocation(line: 579, column: 5, scope: !214)
!1091 = !DILocation(line: 580, column: 2, scope: !214)
