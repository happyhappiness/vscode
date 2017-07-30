; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_ar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.ar_w = type { i64, i64, i32, i32, i8, i8* }

@.str = private unnamed_addr constant [32 x i8] c"archive_write_set_format_ar_bsd\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"ar (BSD)\00", align 1
@.str.2 = private unnamed_addr constant [33 x i8] c"archive_write_set_format_ar_svr4\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"ar (GNU/SVR4)\00", align 1
@.str.4 = private unnamed_addr constant [23 x i8] c"Can't allocate ar data\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"ar\00", align 1
@.str.6 = private unnamed_addr constant [17 x i8] c"Invalid filename\00", align 1
@.str.7 = private unnamed_addr constant [9 x i8] c"!<arch>\0A\00", align 1
@.str.8 = private unnamed_addr constant [3 x i8] c"`\0A\00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"__.SYMDEF\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"//\00", align 1
@.str.12 = private unnamed_addr constant [24 x i8] c"Can't find string table\00", align 1
@.str.13 = private unnamed_addr constant [31 x i8] c"Can't allocate filename buffer\00", align 1
@.str.14 = private unnamed_addr constant [3 x i8] c"/\0A\00", align 1
@.str.15 = private unnamed_addr constant [21 x i8] c"Invalid string table\00", align 1
@.str.16 = private unnamed_addr constant [30 x i8] c"string table offset too large\00", align 1
@.str.17 = private unnamed_addr constant [4 x i8] c"#1/\00", align 1
@.str.18 = private unnamed_addr constant [19 x i8] c"File name too long\00", align 1
@.str.19 = private unnamed_addr constant [33 x i8] c"File modification time too large\00", align 1
@.str.20 = private unnamed_addr constant [26 x i8] c"Numeric user ID too large\00", align 1
@.str.21 = private unnamed_addr constant [27 x i8] c"Numeric group ID too large\00", align 1
@.str.22 = private unnamed_addr constant [23 x i8] c"Numeric mode too large\00", align 1
@.str.23 = private unnamed_addr constant [44 x i8] c"Regular file required for non-pseudo member\00", align 1
@.str.24 = private unnamed_addr constant [23 x i8] c"File size out of range\00", align 1
@.str.25 = private unnamed_addr constant [34 x i8] c"More than one string tables exist\00", align 1
@.str.26 = private unnamed_addr constant [29 x i8] c"Can't allocate strtab buffer\00", align 1
@.str.27 = private unnamed_addr constant [36 x i8] c"Entry remaining bytes larger than 0\00", align 1
@.str.28 = private unnamed_addr constant [41 x i8] c"Padding wrong size: %ju should be 1 or 0\00", align 1
@.str.29 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_ar_bsd(%struct.archive* %_a) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !223, metadata !224), !dbg !225
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !226, metadata !224), !dbg !227
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !228
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !229
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !227
  call void @llvm.dbg.declare(metadata i32* %r, metadata !230, metadata !224), !dbg !231
  br label %do.body, !dbg !232

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !233, metadata !224), !dbg !235
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !236
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str, i32 0, i32 0)), !dbg !236
  store i32 %call, i32* %magic_test, align 4, !dbg !236
  %3 = load i32, i32* %magic_test, align 4, !dbg !236
  %cmp = icmp eq i32 %3, -30, !dbg !236
  br i1 %cmp, label %if.then, label %if.end, !dbg !236

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !238
  br label %return, !dbg !238

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !241

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !243
  %call1 = call i32 @archive_write_set_format_ar(%struct.archive_write* %4), !dbg !244
  store i32 %call1, i32* %r, align 4, !dbg !245
  %5 = load i32, i32* %r, align 4, !dbg !246
  %cmp2 = icmp eq i32 %5, 0, !dbg !248
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !249

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !250
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !252
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !253
  store i32 458754, i32* %archive_format, align 8, !dbg !254
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !255
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !256
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive4, i32 0, i32 4, !dbg !257
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !258
  br label %if.end5, !dbg !259

if.end5:                                          ; preds = %if.then3, %do.end
  %8 = load i32, i32* %r, align 4, !dbg !260
  store i32 %8, i32* %retval, align 4, !dbg !261
  br label %return, !dbg !261

return:                                           ; preds = %if.end5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !262
  ret i32 %9, !dbg !262
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_set_format_ar(%struct.archive_write* %a) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %ar = alloca %struct.ar_w*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !263, metadata !224), !dbg !264
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !265, metadata !224), !dbg !266
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !267
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 22, !dbg !269
  %1 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !269
  %cmp = icmp ne i32 (%struct.archive_write*)* %1, null, !dbg !270
  br i1 %cmp, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !272
  %format_free1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 22, !dbg !273
  %3 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free1, align 8, !dbg !273
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !274
  %call = call i32 %3(%struct.archive_write* %4), !dbg !275
  br label %if.end, !dbg !275

if.end:                                           ; preds = %if.then, %entry
  %call2 = call noalias i8* @calloc(i64 1, i64 40) #6, !dbg !276
  %5 = bitcast i8* %call2 to %struct.ar_w*, !dbg !277
  store %struct.ar_w* %5, %struct.ar_w** %ar, align 8, !dbg !278
  %6 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !279
  %cmp3 = icmp eq %struct.ar_w* %6, null, !dbg !281
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !282

if.then4:                                         ; preds = %if.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !283
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !285
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0)), !dbg !286
  store i32 -30, i32* %retval, align 4, !dbg !287
  br label %return, !dbg !287

if.end5:                                          ; preds = %if.end
  %8 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !288
  %9 = bitcast %struct.ar_w* %8 to i8*, !dbg !288
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !289
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 14, !dbg !290
  store i8* %9, i8** %format_data, align 8, !dbg !291
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !292
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 15, !dbg !293
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i32 0, i32 0), i8** %format_name, align 8, !dbg !294
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !295
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 19, !dbg !296
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_ar_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !297
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !298
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 20, !dbg !299
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_ar_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !300
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !301
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 21, !dbg !302
  store i32 (%struct.archive_write*)* @archive_write_ar_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !303
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !304
  %format_free6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 22, !dbg !305
  store i32 (%struct.archive_write*)* @archive_write_ar_free, i32 (%struct.archive_write*)** %format_free6, align 8, !dbg !306
  %16 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !307
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 18, !dbg !308
  store i32 (%struct.archive_write*)* @archive_write_ar_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !309
  store i32 0, i32* %retval, align 4, !dbg !310
  br label %return, !dbg !310

return:                                           ; preds = %if.end5, %if.then4
  %17 = load i32, i32* %retval, align 4, !dbg !311
  ret i32 %17, !dbg !311
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_ar_svr4(%struct.archive* %_a) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !312, metadata !224), !dbg !313
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !314, metadata !224), !dbg !315
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !316
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !317
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !315
  call void @llvm.dbg.declare(metadata i32* %r, metadata !318, metadata !224), !dbg !319
  br label %do.body, !dbg !320

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !321, metadata !224), !dbg !323
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !324
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0)), !dbg !324
  store i32 %call, i32* %magic_test, align 4, !dbg !324
  %3 = load i32, i32* %magic_test, align 4, !dbg !324
  %cmp = icmp eq i32 %3, -30, !dbg !324
  br i1 %cmp, label %if.then, label %if.end, !dbg !324

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !326
  br label %return, !dbg !326

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !329

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !331
  %call1 = call i32 @archive_write_set_format_ar(%struct.archive_write* %4), !dbg !332
  store i32 %call1, i32* %r, align 4, !dbg !333
  %5 = load i32, i32* %r, align 4, !dbg !334
  %cmp2 = icmp eq i32 %5, 0, !dbg !336
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !337

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !338
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !340
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !341
  store i32 458753, i32* %archive_format, align 8, !dbg !342
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !343
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !344
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive4, i32 0, i32 4, !dbg !345
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !346
  br label %if.end5, !dbg !347

if.end5:                                          ; preds = %if.then3, %do.end
  %8 = load i32, i32* %r, align 4, !dbg !348
  store i32 %8, i32* %retval, align 4, !dbg !349
  br label %return, !dbg !349

return:                                           ; preds = %if.end5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !350
  ret i32 %9, !dbg !350
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ar_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ret = alloca i32, align 4
  %append_fn = alloca i32, align 4
  %buff = alloca [60 x i8], align 16
  %ss = alloca i8*, align 8
  %se = alloca i8*, align 8
  %ar = alloca %struct.ar_w*, align 8
  %pathname = alloca i8*, align 8
  %filename = alloca i8*, align 8
  %size = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !351, metadata !224), !dbg !352
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !353, metadata !224), !dbg !354
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !355, metadata !224), !dbg !356
  call void @llvm.dbg.declare(metadata i32* %append_fn, metadata !357, metadata !224), !dbg !358
  call void @llvm.dbg.declare(metadata [60 x i8]* %buff, metadata !359, metadata !224), !dbg !363
  call void @llvm.dbg.declare(metadata i8** %ss, metadata !364, metadata !224), !dbg !365
  call void @llvm.dbg.declare(metadata i8** %se, metadata !366, metadata !224), !dbg !367
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !368, metadata !224), !dbg !369
  call void @llvm.dbg.declare(metadata i8** %pathname, metadata !370, metadata !224), !dbg !371
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !372, metadata !224), !dbg !373
  call void @llvm.dbg.declare(metadata i64* %size, metadata !374, metadata !224), !dbg !375
  store i32 0, i32* %append_fn, align 4, !dbg !376
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !377
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !378
  %1 = load i8*, i8** %format_data, align 8, !dbg !378
  %2 = bitcast i8* %1 to %struct.ar_w*, !dbg !379
  store %struct.ar_w* %2, %struct.ar_w** %ar, align 8, !dbg !380
  %3 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !381
  %is_strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %3, i32 0, i32 2, !dbg !382
  store i32 0, i32* %is_strtab, align 8, !dbg !383
  store i8* null, i8** %filename, align 8, !dbg !384
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !385
  %call = call i64 @archive_entry_size(%struct.archive_entry* %4), !dbg !386
  store i64 %call, i64* %size, align 8, !dbg !387
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !388
  %call2 = call i8* @archive_entry_pathname(%struct.archive_entry* %5), !dbg !389
  store i8* %call2, i8** %pathname, align 8, !dbg !390
  %6 = load i8*, i8** %pathname, align 8, !dbg !391
  %cmp = icmp eq i8* %6, null, !dbg !393
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !394

lor.lhs.false:                                    ; preds = %entry
  %7 = load i8*, i8** %pathname, align 8, !dbg !395
  %8 = load i8, i8* %7, align 1, !dbg !397
  %conv = sext i8 %8 to i32, !dbg !397
  %cmp3 = icmp eq i32 %conv, 0, !dbg !398
  br i1 %cmp3, label %if.then, label %if.end, !dbg !399

if.then:                                          ; preds = %lor.lhs.false, %entry
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !400
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !402
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.6, i32 0, i32 0)), !dbg !403
  store i32 -20, i32* %retval, align 4, !dbg !404
  br label %return, !dbg !404

if.end:                                           ; preds = %lor.lhs.false
  %10 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !405
  %wrote_global_header = getelementptr inbounds %struct.ar_w, %struct.ar_w* %10, i32 0, i32 4, !dbg !407
  %11 = load i8, i8* %wrote_global_header, align 8, !dbg !407
  %tobool = icmp ne i8 %11, 0, !dbg !405
  br i1 %tobool, label %if.end8, label %if.then5, !dbg !408

if.then5:                                         ; preds = %if.end
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !409
  %call6 = call i32 @__archive_write_output(%struct.archive_write* %12, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.7, i32 0, i32 0), i64 8), !dbg !411
  %13 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !412
  %wrote_global_header7 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %13, i32 0, i32 4, !dbg !413
  store i8 1, i8* %wrote_global_header7, align 8, !dbg !414
  br label %if.end8, !dbg !415

if.end8:                                          ; preds = %if.then5, %if.end
  %arraydecay = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !416
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 32, i64 60, i32 16, i1 false), !dbg !416
  %arrayidx = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 58, !dbg !417
  %call9 = call i8* @strncpy(i8* %arrayidx, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.8, i32 0, i32 0), i64 2) #6, !dbg !418
  %14 = load i8*, i8** %pathname, align 8, !dbg !419
  %call10 = call i32 @strcmp(i8* %14, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i32 0, i32 0)) #7, !dbg !421
  %cmp11 = icmp eq i32 %call10, 0, !dbg !422
  br i1 %cmp11, label %if.then13, label %if.end15, !dbg !423

if.then13:                                        ; preds = %if.end8
  %arrayidx14 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 0, !dbg !424
  store i8 47, i8* %arrayidx14, align 16, !dbg !426
  br label %stat, !dbg !427

if.end15:                                         ; preds = %if.end8
  %15 = load i8*, i8** %pathname, align 8, !dbg !428
  %call16 = call i32 @strcmp(i8* %15, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0)) #7, !dbg !430
  %cmp17 = icmp eq i32 %call16, 0, !dbg !431
  br i1 %cmp17, label %if.then19, label %if.end22, !dbg !432

if.then19:                                        ; preds = %if.end15
  %arraydecay20 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !433
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay20, i64 0, !dbg !435
  %call21 = call i8* @strncpy(i8* %add.ptr, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i64 9) #6, !dbg !436
  br label %stat, !dbg !437

if.end22:                                         ; preds = %if.end15
  %16 = load i8*, i8** %pathname, align 8, !dbg !438
  %call23 = call i32 @strcmp(i8* %16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0)) #7, !dbg !440
  %cmp24 = icmp eq i32 %call23, 0, !dbg !441
  br i1 %cmp24, label %if.then26, label %if.end30, !dbg !442

if.then26:                                        ; preds = %if.end22
  %17 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !443
  %is_strtab27 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %17, i32 0, i32 2, !dbg !445
  store i32 1, i32* %is_strtab27, align 8, !dbg !446
  %arrayidx28 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 1, !dbg !447
  store i8 47, i8* %arrayidx28, align 1, !dbg !448
  %arrayidx29 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 0, !dbg !449
  store i8 47, i8* %arrayidx29, align 16, !dbg !450
  br label %size164, !dbg !451

if.end30:                                         ; preds = %if.end22
  %18 = load i8*, i8** %pathname, align 8, !dbg !452
  %call31 = call i8* @ar_basename(i8* %18), !dbg !454
  store i8* %call31, i8** %filename, align 8, !dbg !455
  %cmp32 = icmp eq i8* %call31, null, !dbg !456
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !457

if.then34:                                        ; preds = %if.end30
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !458
  %archive35 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !460
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive35, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.6, i32 0, i32 0)), !dbg !461
  store i32 -20, i32* %retval, align 4, !dbg !462
  br label %return, !dbg !462

if.end36:                                         ; preds = %if.end30
  %20 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !463
  %archive37 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 0, !dbg !465
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive37, i32 0, i32 3, !dbg !466
  %21 = load i32, i32* %archive_format, align 8, !dbg !466
  %cmp38 = icmp eq i32 %21, 458753, !dbg !467
  br i1 %cmp38, label %if.then40, label %if.else85, !dbg !468

if.then40:                                        ; preds = %if.end36
  %22 = load i8*, i8** %filename, align 8, !dbg !469
  %call41 = call i64 @strlen(i8* %22) #7, !dbg !472
  %cmp42 = icmp ule i64 %call41, 15, !dbg !473
  br i1 %cmp42, label %if.then44, label %if.else, !dbg !474

if.then44:                                        ; preds = %if.then40
  %arrayidx45 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 0, !dbg !475
  %23 = load i8*, i8** %filename, align 8, !dbg !477
  %24 = load i8*, i8** %filename, align 8, !dbg !478
  %call46 = call i64 @strlen(i8* %24) #7, !dbg !479
  %call47 = call i8* @strncpy(i8* %arrayidx45, i8* %23, i64 %call46) #6, !dbg !480
  %25 = load i8*, i8** %filename, align 8, !dbg !481
  %call48 = call i64 @strlen(i8* %25) #7, !dbg !482
  %add = add i64 0, %call48, !dbg !483
  %arrayidx49 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 %add, !dbg !484
  store i8 47, i8* %arrayidx49, align 1, !dbg !485
  br label %if.end84, !dbg !486

if.else:                                          ; preds = %if.then40
  %26 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !487
  %has_strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %26, i32 0, i32 3, !dbg !490
  %27 = load i32, i32* %has_strtab, align 4, !dbg !490
  %cmp50 = icmp sle i32 %27, 0, !dbg !491
  br i1 %cmp50, label %if.then52, label %if.end54, !dbg !492

if.then52:                                        ; preds = %if.else
  %28 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !493
  %archive53 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 0, !dbg !495
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive53, i32 22, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.12, i32 0, i32 0)), !dbg !496
  store i32 -20, i32* %retval, align 4, !dbg !497
  br label %return, !dbg !497

if.end54:                                         ; preds = %if.else
  %29 = load i8*, i8** %filename, align 8, !dbg !498
  %call55 = call i64 @strlen(i8* %29) #7, !dbg !499
  %add56 = add i64 %call55, 3, !dbg !500
  %call57 = call noalias i8* @malloc(i64 %add56) #6, !dbg !501
  store i8* %call57, i8** %se, align 8, !dbg !503
  %30 = load i8*, i8** %se, align 8, !dbg !504
  %cmp58 = icmp eq i8* %30, null, !dbg !506
  br i1 %cmp58, label %if.then60, label %if.end62, !dbg !507

if.then60:                                        ; preds = %if.end54
  %31 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !508
  %archive61 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 0, !dbg !510
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive61, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.13, i32 0, i32 0)), !dbg !511
  store i32 -30, i32* %retval, align 4, !dbg !512
  br label %return, !dbg !512

if.end62:                                         ; preds = %if.end54
  %32 = load i8*, i8** %se, align 8, !dbg !513
  %33 = load i8*, i8** %filename, align 8, !dbg !514
  %34 = load i8*, i8** %filename, align 8, !dbg !515
  %call63 = call i64 @strlen(i8* %34) #7, !dbg !516
  %call64 = call i8* @strncpy(i8* %32, i8* %33, i64 %call63) #6, !dbg !517
  %35 = load i8*, i8** %se, align 8, !dbg !518
  %36 = load i8*, i8** %filename, align 8, !dbg !519
  %call65 = call i64 @strlen(i8* %36) #7, !dbg !520
  %add.ptr66 = getelementptr inbounds i8, i8* %35, i64 %call65, !dbg !521
  %call67 = call i8* @strcpy(i8* %add.ptr66, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.14, i32 0, i32 0)) #6, !dbg !522
  %37 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !523
  %strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %37, i32 0, i32 5, !dbg !524
  %38 = load i8*, i8** %strtab, align 8, !dbg !524
  %39 = load i8*, i8** %se, align 8, !dbg !525
  %call68 = call i8* @strstr(i8* %38, i8* %39) #7, !dbg !526
  store i8* %call68, i8** %ss, align 8, !dbg !527
  %40 = load i8*, i8** %se, align 8, !dbg !528
  call void @free(i8* %40) #6, !dbg !529
  %41 = load i8*, i8** %ss, align 8, !dbg !530
  %cmp69 = icmp eq i8* %41, null, !dbg !532
  br i1 %cmp69, label %if.then71, label %if.end73, !dbg !533

if.then71:                                        ; preds = %if.end62
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !534
  %archive72 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %42, i32 0, i32 0, !dbg !536
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive72, i32 22, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.15, i32 0, i32 0)), !dbg !537
  store i32 -20, i32* %retval, align 4, !dbg !538
  br label %return, !dbg !538

if.end73:                                         ; preds = %if.end62
  %arrayidx74 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 0, !dbg !539
  store i8 47, i8* %arrayidx74, align 16, !dbg !540
  %43 = load i8*, i8** %ss, align 8, !dbg !541
  %44 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !543
  %strtab75 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %44, i32 0, i32 5, !dbg !544
  %45 = load i8*, i8** %strtab75, align 8, !dbg !544
  %sub.ptr.lhs.cast = ptrtoint i8* %43 to i64, !dbg !545
  %sub.ptr.rhs.cast = ptrtoint i8* %45 to i64, !dbg !545
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !545
  %arraydecay76 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !546
  %add.ptr77 = getelementptr inbounds i8, i8* %arraydecay76, i64 0, !dbg !547
  %add.ptr78 = getelementptr inbounds i8, i8* %add.ptr77, i64 1, !dbg !548
  %call79 = call i32 @format_decimal(i64 %sub.ptr.sub, i8* %add.ptr78, i32 15), !dbg !549
  %tobool80 = icmp ne i32 %call79, 0, !dbg !549
  br i1 %tobool80, label %if.then81, label %if.end83, !dbg !550

if.then81:                                        ; preds = %if.end73
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !551
  %archive82 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %46, i32 0, i32 0, !dbg !553
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive82, i32 34, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.16, i32 0, i32 0)), !dbg !554
  store i32 -20, i32* %retval, align 4, !dbg !555
  br label %return, !dbg !555

if.end83:                                         ; preds = %if.end73
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.then44
  br label %if.end121, !dbg !556

if.else85:                                        ; preds = %if.end36
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !557
  %archive86 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %47, i32 0, i32 0, !dbg !560
  %archive_format87 = getelementptr inbounds %struct.archive, %struct.archive* %archive86, i32 0, i32 3, !dbg !561
  %48 = load i32, i32* %archive_format87, align 8, !dbg !561
  %cmp88 = icmp eq i32 %48, 458754, !dbg !562
  br i1 %cmp88, label %if.then90, label %if.end120, !dbg !557

if.then90:                                        ; preds = %if.else85
  %49 = load i8*, i8** %filename, align 8, !dbg !563
  %call91 = call i64 @strlen(i8* %49) #7, !dbg !566
  %cmp92 = icmp ule i64 %call91, 16, !dbg !567
  br i1 %cmp92, label %land.lhs.true, label %if.else104, !dbg !568

land.lhs.true:                                    ; preds = %if.then90
  %50 = load i8*, i8** %filename, align 8, !dbg !569
  %call94 = call i8* @strchr(i8* %50, i32 32) #7, !dbg !571
  %cmp95 = icmp eq i8* %call94, null, !dbg !572
  br i1 %cmp95, label %if.then97, label %if.else104, !dbg !573

if.then97:                                        ; preds = %land.lhs.true
  %arrayidx98 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 0, !dbg !574
  %51 = load i8*, i8** %filename, align 8, !dbg !576
  %52 = load i8*, i8** %filename, align 8, !dbg !577
  %call99 = call i64 @strlen(i8* %52) #7, !dbg !578
  %call100 = call i8* @strncpy(i8* %arrayidx98, i8* %51, i64 %call99) #6, !dbg !579
  %53 = load i8*, i8** %filename, align 8, !dbg !581
  %call101 = call i64 @strlen(i8* %53) #7, !dbg !582
  %add102 = add i64 0, %call101, !dbg !583
  %arrayidx103 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i64 0, i64 %add102, !dbg !584
  store i8 32, i8* %arrayidx103, align 1, !dbg !585
  br label %if.end119, !dbg !586

if.else104:                                       ; preds = %land.lhs.true, %if.then90
  %arraydecay105 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !587
  %add.ptr106 = getelementptr inbounds i8, i8* %arraydecay105, i64 0, !dbg !589
  %call107 = call i8* @strncpy(i8* %add.ptr106, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.17, i32 0, i32 0), i64 3) #6, !dbg !590
  %54 = load i8*, i8** %filename, align 8, !dbg !591
  %call108 = call i64 @strlen(i8* %54) #7, !dbg !593
  %arraydecay109 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !594
  %add.ptr110 = getelementptr inbounds i8, i8* %arraydecay109, i64 0, !dbg !595
  %add.ptr111 = getelementptr inbounds i8, i8* %add.ptr110, i64 3, !dbg !596
  %call112 = call i32 @format_decimal(i64 %call108, i8* %add.ptr111, i32 13), !dbg !597
  %tobool113 = icmp ne i32 %call112, 0, !dbg !599
  br i1 %tobool113, label %if.then114, label %if.end116, !dbg !600

if.then114:                                       ; preds = %if.else104
  %55 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !601
  %archive115 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %55, i32 0, i32 0, !dbg !603
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive115, i32 34, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.18, i32 0, i32 0)), !dbg !604
  store i32 -20, i32* %retval, align 4, !dbg !605
  br label %return, !dbg !605

if.end116:                                        ; preds = %if.else104
  store i32 1, i32* %append_fn, align 4, !dbg !606
  %56 = load i8*, i8** %filename, align 8, !dbg !607
  %call117 = call i64 @strlen(i8* %56) #7, !dbg !608
  %57 = load i64, i64* %size, align 8, !dbg !609
  %add118 = add i64 %57, %call117, !dbg !609
  store i64 %add118, i64* %size, align 8, !dbg !609
  br label %if.end119

if.end119:                                        ; preds = %if.end116, %if.then97
  br label %if.end120, !dbg !610

if.end120:                                        ; preds = %if.end119, %if.else85
  br label %if.end121

if.end121:                                        ; preds = %if.end120, %if.end84
  br label %stat, !dbg !611

stat:                                             ; preds = %if.end121, %if.then19, %if.then13
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !613
  %call122 = call i64 @archive_entry_mtime(%struct.archive_entry* %58), !dbg !615
  %arraydecay123 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !616
  %add.ptr124 = getelementptr inbounds i8, i8* %arraydecay123, i64 16, !dbg !617
  %call125 = call i32 @format_decimal(i64 %call122, i8* %add.ptr124, i32 12), !dbg !618
  %tobool126 = icmp ne i32 %call125, 0, !dbg !620
  br i1 %tobool126, label %if.then127, label %if.end129, !dbg !621

if.then127:                                       ; preds = %stat
  %59 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !622
  %archive128 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %59, i32 0, i32 0, !dbg !624
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive128, i32 34, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.19, i32 0, i32 0)), !dbg !625
  store i32 -20, i32* %retval, align 4, !dbg !626
  br label %return, !dbg !626

if.end129:                                        ; preds = %stat
  %60 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !627
  %call130 = call i64 @archive_entry_uid(%struct.archive_entry* %60), !dbg !629
  %arraydecay131 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !630
  %add.ptr132 = getelementptr inbounds i8, i8* %arraydecay131, i64 28, !dbg !631
  %call133 = call i32 @format_decimal(i64 %call130, i8* %add.ptr132, i32 6), !dbg !632
  %tobool134 = icmp ne i32 %call133, 0, !dbg !634
  br i1 %tobool134, label %if.then135, label %if.end137, !dbg !635

if.then135:                                       ; preds = %if.end129
  %61 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !636
  %archive136 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %61, i32 0, i32 0, !dbg !638
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive136, i32 34, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.20, i32 0, i32 0)), !dbg !639
  store i32 -20, i32* %retval, align 4, !dbg !640
  br label %return, !dbg !640

if.end137:                                        ; preds = %if.end129
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !641
  %call138 = call i64 @archive_entry_gid(%struct.archive_entry* %62), !dbg !643
  %arraydecay139 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !644
  %add.ptr140 = getelementptr inbounds i8, i8* %arraydecay139, i64 34, !dbg !645
  %call141 = call i32 @format_decimal(i64 %call138, i8* %add.ptr140, i32 6), !dbg !646
  %tobool142 = icmp ne i32 %call141, 0, !dbg !648
  br i1 %tobool142, label %if.then143, label %if.end145, !dbg !649

if.then143:                                       ; preds = %if.end137
  %63 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !650
  %archive144 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %63, i32 0, i32 0, !dbg !652
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive144, i32 34, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.21, i32 0, i32 0)), !dbg !653
  store i32 -20, i32* %retval, align 4, !dbg !654
  br label %return, !dbg !654

if.end145:                                        ; preds = %if.end137
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !655
  %call146 = call i32 @archive_entry_mode(%struct.archive_entry* %64), !dbg !657
  %conv147 = zext i32 %call146 to i64, !dbg !657
  %arraydecay148 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !658
  %add.ptr149 = getelementptr inbounds i8, i8* %arraydecay148, i64 40, !dbg !659
  %call150 = call i32 @format_octal(i64 %conv147, i8* %add.ptr149, i32 8), !dbg !660
  %tobool151 = icmp ne i32 %call150, 0, !dbg !662
  br i1 %tobool151, label %if.then152, label %if.end154, !dbg !663

if.then152:                                       ; preds = %if.end145
  %65 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !664
  %archive153 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %65, i32 0, i32 0, !dbg !666
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive153, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.22, i32 0, i32 0)), !dbg !667
  store i32 -20, i32* %retval, align 4, !dbg !668
  br label %return, !dbg !668

if.end154:                                        ; preds = %if.end145
  %66 = load i8*, i8** %filename, align 8, !dbg !669
  %cmp155 = icmp ne i8* %66, null, !dbg !671
  br i1 %cmp155, label %land.lhs.true157, label %if.end163, !dbg !672

land.lhs.true157:                                 ; preds = %if.end154
  %67 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !673
  %call158 = call i32 @archive_entry_filetype(%struct.archive_entry* %67), !dbg !675
  %cmp159 = icmp ne i32 %call158, 32768, !dbg !676
  br i1 %cmp159, label %if.then161, label %if.end163, !dbg !677

if.then161:                                       ; preds = %land.lhs.true157
  %68 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !678
  %archive162 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %68, i32 0, i32 0, !dbg !680
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive162, i32 22, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.23, i32 0, i32 0)), !dbg !681
  store i32 -20, i32* %retval, align 4, !dbg !682
  br label %return, !dbg !682

if.end163:                                        ; preds = %land.lhs.true157, %if.end154
  br label %size164, !dbg !683

size164:                                          ; preds = %if.end163, %if.then26
  %69 = load i64, i64* %size, align 8, !dbg !685
  %arraydecay165 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !687
  %add.ptr166 = getelementptr inbounds i8, i8* %arraydecay165, i64 48, !dbg !688
  %call167 = call i32 @format_decimal(i64 %69, i8* %add.ptr166, i32 10), !dbg !689
  %tobool168 = icmp ne i32 %call167, 0, !dbg !689
  br i1 %tobool168, label %if.then169, label %if.end171, !dbg !690

if.then169:                                       ; preds = %size164
  %70 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !691
  %archive170 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %70, i32 0, i32 0, !dbg !693
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive170, i32 34, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.24, i32 0, i32 0)), !dbg !694
  store i32 -20, i32* %retval, align 4, !dbg !695
  br label %return, !dbg !695

if.end171:                                        ; preds = %size164
  %71 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !696
  %arraydecay172 = getelementptr inbounds [60 x i8], [60 x i8]* %buff, i32 0, i32 0, !dbg !697
  %call173 = call i32 @__archive_write_output(%struct.archive_write* %71, i8* %arraydecay172, i64 60), !dbg !698
  store i32 %call173, i32* %ret, align 4, !dbg !699
  %72 = load i32, i32* %ret, align 4, !dbg !700
  %cmp174 = icmp ne i32 %72, 0, !dbg !702
  br i1 %cmp174, label %if.then176, label %if.end177, !dbg !703

if.then176:                                       ; preds = %if.end171
  %73 = load i32, i32* %ret, align 4, !dbg !704
  store i32 %73, i32* %retval, align 4, !dbg !705
  br label %return, !dbg !705

if.end177:                                        ; preds = %if.end171
  %74 = load i64, i64* %size, align 8, !dbg !706
  %75 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !707
  %entry_bytes_remaining = getelementptr inbounds %struct.ar_w, %struct.ar_w* %75, i32 0, i32 0, !dbg !708
  store i64 %74, i64* %entry_bytes_remaining, align 8, !dbg !709
  %76 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !710
  %entry_bytes_remaining178 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %76, i32 0, i32 0, !dbg !711
  %77 = load i64, i64* %entry_bytes_remaining178, align 8, !dbg !711
  %rem = urem i64 %77, 2, !dbg !712
  %78 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !713
  %entry_padding = getelementptr inbounds %struct.ar_w, %struct.ar_w* %78, i32 0, i32 1, !dbg !714
  store i64 %rem, i64* %entry_padding, align 8, !dbg !715
  %79 = load i32, i32* %append_fn, align 4, !dbg !716
  %cmp179 = icmp sgt i32 %79, 0, !dbg !718
  br i1 %cmp179, label %if.then181, label %if.end190, !dbg !719

if.then181:                                       ; preds = %if.end177
  %80 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !720
  %81 = load i8*, i8** %filename, align 8, !dbg !722
  %82 = load i8*, i8** %filename, align 8, !dbg !723
  %call182 = call i64 @strlen(i8* %82) #7, !dbg !724
  %call183 = call i32 @__archive_write_output(%struct.archive_write* %80, i8* %81, i64 %call182), !dbg !725
  store i32 %call183, i32* %ret, align 4, !dbg !727
  %83 = load i32, i32* %ret, align 4, !dbg !728
  %cmp184 = icmp ne i32 %83, 0, !dbg !730
  br i1 %cmp184, label %if.then186, label %if.end187, !dbg !731

if.then186:                                       ; preds = %if.then181
  %84 = load i32, i32* %ret, align 4, !dbg !732
  store i32 %84, i32* %retval, align 4, !dbg !733
  br label %return, !dbg !733

if.end187:                                        ; preds = %if.then181
  %85 = load i8*, i8** %filename, align 8, !dbg !734
  %call188 = call i64 @strlen(i8* %85) #7, !dbg !735
  %86 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !736
  %entry_bytes_remaining189 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %86, i32 0, i32 0, !dbg !737
  %87 = load i64, i64* %entry_bytes_remaining189, align 8, !dbg !738
  %sub = sub i64 %87, %call188, !dbg !738
  store i64 %sub, i64* %entry_bytes_remaining189, align 8, !dbg !738
  br label %if.end190, !dbg !739

if.end190:                                        ; preds = %if.end187, %if.end177
  store i32 0, i32* %retval, align 4, !dbg !740
  br label %return, !dbg !740

return:                                           ; preds = %if.end190, %if.then186, %if.then176, %if.then169, %if.then161, %if.then152, %if.then143, %if.then135, %if.then127, %if.then114, %if.then81, %if.then71, %if.then60, %if.then52, %if.then34, %if.then
  %88 = load i32, i32* %retval, align 4, !dbg !741
  ret i32 %88, !dbg !741
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_ar_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !216 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %ar = alloca %struct.ar_w*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !742, metadata !224), !dbg !743
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !744, metadata !224), !dbg !745
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !746, metadata !224), !dbg !747
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !748, metadata !224), !dbg !749
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !750, metadata !224), !dbg !751
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !752
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !753
  %1 = load i8*, i8** %format_data, align 8, !dbg !753
  %2 = bitcast i8* %1 to %struct.ar_w*, !dbg !754
  store %struct.ar_w* %2, %struct.ar_w** %ar, align 8, !dbg !755
  %3 = load i64, i64* %s.addr, align 8, !dbg !756
  %4 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !758
  %entry_bytes_remaining = getelementptr inbounds %struct.ar_w, %struct.ar_w* %4, i32 0, i32 0, !dbg !759
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !759
  %cmp = icmp ugt i64 %3, %5, !dbg !760
  br i1 %cmp, label %if.then, label %if.end, !dbg !761

if.then:                                          ; preds = %entry
  %6 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !762
  %entry_bytes_remaining1 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %6, i32 0, i32 0, !dbg !763
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !763
  store i64 %7, i64* %s.addr, align 8, !dbg !764
  br label %if.end, !dbg !765

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !766
  %is_strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %8, i32 0, i32 2, !dbg !768
  %9 = load i32, i32* %is_strtab, align 8, !dbg !768
  %cmp2 = icmp sgt i32 %9, 0, !dbg !769
  br i1 %cmp2, label %if.then3, label %if.end15, !dbg !770

if.then3:                                         ; preds = %if.end
  %10 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !771
  %has_strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %10, i32 0, i32 3, !dbg !774
  %11 = load i32, i32* %has_strtab, align 4, !dbg !774
  %cmp4 = icmp sgt i32 %11, 0, !dbg !775
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !776

if.then5:                                         ; preds = %if.then3
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !777
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 0, !dbg !779
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.25, i32 0, i32 0)), !dbg !780
  store i64 -20, i64* %retval, align 8, !dbg !781
  br label %return, !dbg !781

if.end6:                                          ; preds = %if.then3
  %13 = load i64, i64* %s.addr, align 8, !dbg !782
  %call = call noalias i8* @malloc(i64 %13) #6, !dbg !783
  %14 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !784
  %strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %14, i32 0, i32 5, !dbg !785
  store i8* %call, i8** %strtab, align 8, !dbg !786
  %15 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !787
  %strtab7 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %15, i32 0, i32 5, !dbg !789
  %16 = load i8*, i8** %strtab7, align 8, !dbg !789
  %cmp8 = icmp eq i8* %16, null, !dbg !790
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !791

if.then9:                                         ; preds = %if.end6
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !792
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 0, !dbg !794
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 12, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.26, i32 0, i32 0)), !dbg !795
  store i64 -30, i64* %retval, align 8, !dbg !796
  br label %return, !dbg !796

if.end11:                                         ; preds = %if.end6
  %18 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !797
  %strtab12 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %18, i32 0, i32 5, !dbg !798
  %19 = load i8*, i8** %strtab12, align 8, !dbg !798
  %20 = load i8*, i8** %buff.addr, align 8, !dbg !799
  %21 = load i64, i64* %s.addr, align 8, !dbg !800
  %call13 = call i8* @strncpy(i8* %19, i8* %20, i64 %21) #6, !dbg !801
  %22 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !802
  %has_strtab14 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %22, i32 0, i32 3, !dbg !803
  store i32 1, i32* %has_strtab14, align 4, !dbg !804
  br label %if.end15, !dbg !805

if.end15:                                         ; preds = %if.end11, %if.end
  %23 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !806
  %24 = load i8*, i8** %buff.addr, align 8, !dbg !807
  %25 = load i64, i64* %s.addr, align 8, !dbg !808
  %call16 = call i32 @__archive_write_output(%struct.archive_write* %23, i8* %24, i64 %25), !dbg !809
  store i32 %call16, i32* %ret, align 4, !dbg !810
  %26 = load i32, i32* %ret, align 4, !dbg !811
  %cmp17 = icmp ne i32 %26, 0, !dbg !813
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !814

if.then18:                                        ; preds = %if.end15
  %27 = load i32, i32* %ret, align 4, !dbg !815
  %conv = sext i32 %27 to i64, !dbg !816
  store i64 %conv, i64* %retval, align 8, !dbg !817
  br label %return, !dbg !817

if.end19:                                         ; preds = %if.end15
  %28 = load i64, i64* %s.addr, align 8, !dbg !818
  %29 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !819
  %entry_bytes_remaining20 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %29, i32 0, i32 0, !dbg !820
  %30 = load i64, i64* %entry_bytes_remaining20, align 8, !dbg !821
  %sub = sub i64 %30, %28, !dbg !821
  store i64 %sub, i64* %entry_bytes_remaining20, align 8, !dbg !821
  %31 = load i64, i64* %s.addr, align 8, !dbg !822
  store i64 %31, i64* %retval, align 8, !dbg !823
  br label %return, !dbg !823

return:                                           ; preds = %if.end19, %if.then18, %if.then9, %if.then5
  %32 = load i64, i64* %retval, align 8, !dbg !824
  ret i64 %32, !dbg !824
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ar_close(%struct.archive_write* %a) #0 !dbg !217 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %ar = alloca %struct.ar_w*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !825, metadata !224), !dbg !826
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !827, metadata !224), !dbg !828
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !829, metadata !224), !dbg !830
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !831
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !832
  %1 = load i8*, i8** %format_data, align 8, !dbg !832
  %2 = bitcast i8* %1 to %struct.ar_w*, !dbg !833
  store %struct.ar_w* %2, %struct.ar_w** %ar, align 8, !dbg !834
  %3 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !835
  %wrote_global_header = getelementptr inbounds %struct.ar_w, %struct.ar_w* %3, i32 0, i32 4, !dbg !837
  %4 = load i8, i8* %wrote_global_header, align 8, !dbg !837
  %tobool = icmp ne i8 %4, 0, !dbg !835
  br i1 %tobool, label %if.end, label %if.then, !dbg !838

if.then:                                          ; preds = %entry
  %5 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !839
  %wrote_global_header1 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %5, i32 0, i32 4, !dbg !841
  store i8 1, i8* %wrote_global_header1, align 8, !dbg !842
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !843
  %call = call i32 @__archive_write_output(%struct.archive_write* %6, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.7, i32 0, i32 0), i64 8), !dbg !844
  store i32 %call, i32* %ret, align 4, !dbg !845
  %7 = load i32, i32* %ret, align 4, !dbg !846
  store i32 %7, i32* %retval, align 4, !dbg !847
  br label %return, !dbg !847

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !848
  br label %return, !dbg !848

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !849
  ret i32 %8, !dbg !849
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ar_free(%struct.archive_write* %a) #0 !dbg !218 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %ar = alloca %struct.ar_w*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !850, metadata !224), !dbg !851
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !852, metadata !224), !dbg !853
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !854
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !855
  %1 = load i8*, i8** %format_data, align 8, !dbg !855
  %2 = bitcast i8* %1 to %struct.ar_w*, !dbg !856
  store %struct.ar_w* %2, %struct.ar_w** %ar, align 8, !dbg !857
  %3 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !858
  %cmp = icmp eq %struct.ar_w* %3, null, !dbg !860
  br i1 %cmp, label %if.then, label %if.end, !dbg !861

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !862
  br label %return, !dbg !862

if.end:                                           ; preds = %entry
  %4 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !863
  %has_strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %4, i32 0, i32 3, !dbg !865
  %5 = load i32, i32* %has_strtab, align 4, !dbg !865
  %cmp1 = icmp sgt i32 %5, 0, !dbg !866
  br i1 %cmp1, label %if.then2, label %if.end4, !dbg !867

if.then2:                                         ; preds = %if.end
  %6 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !868
  %strtab = getelementptr inbounds %struct.ar_w, %struct.ar_w* %6, i32 0, i32 5, !dbg !870
  %7 = load i8*, i8** %strtab, align 8, !dbg !870
  call void @free(i8* %7) #6, !dbg !871
  %8 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !872
  %strtab3 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %8, i32 0, i32 5, !dbg !873
  store i8* null, i8** %strtab3, align 8, !dbg !874
  br label %if.end4, !dbg !875

if.end4:                                          ; preds = %if.then2, %if.end
  %9 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !876
  %10 = bitcast %struct.ar_w* %9 to i8*, !dbg !876
  call void @free(i8* %10) #6, !dbg !877
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !878
  %format_data5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 14, !dbg !879
  store i8* null, i8** %format_data5, align 8, !dbg !880
  store i32 0, i32* %retval, align 4, !dbg !881
  br label %return, !dbg !881

return:                                           ; preds = %if.end4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !882
  ret i32 %12, !dbg !882
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_ar_finish_entry(%struct.archive_write* %a) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %ar = alloca %struct.ar_w*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !883, metadata !224), !dbg !884
  call void @llvm.dbg.declare(metadata %struct.ar_w** %ar, metadata !885, metadata !224), !dbg !886
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !887, metadata !224), !dbg !888
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !889
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !890
  %1 = load i8*, i8** %format_data, align 8, !dbg !890
  %2 = bitcast i8* %1 to %struct.ar_w*, !dbg !891
  store %struct.ar_w* %2, %struct.ar_w** %ar, align 8, !dbg !892
  %3 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !893
  %entry_bytes_remaining = getelementptr inbounds %struct.ar_w, %struct.ar_w* %3, i32 0, i32 0, !dbg !895
  %4 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !895
  %cmp = icmp ne i64 %4, 0, !dbg !896
  br i1 %cmp, label %if.then, label %if.end, !dbg !897

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !898
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !900
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.27, i32 0, i32 0)), !dbg !901
  store i32 -20, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

if.end:                                           ; preds = %entry
  %6 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !903
  %entry_padding = getelementptr inbounds %struct.ar_w, %struct.ar_w* %6, i32 0, i32 1, !dbg !905
  %7 = load i64, i64* %entry_padding, align 8, !dbg !905
  %cmp1 = icmp eq i64 %7, 0, !dbg !906
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !907

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !908
  br label %return, !dbg !908

if.end3:                                          ; preds = %if.end
  %8 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !910
  %entry_padding4 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %8, i32 0, i32 1, !dbg !912
  %9 = load i64, i64* %entry_padding4, align 8, !dbg !912
  %cmp5 = icmp ne i64 %9, 1, !dbg !913
  br i1 %cmp5, label %if.then6, label %if.end9, !dbg !914

if.then6:                                         ; preds = %if.end3
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !915
  %archive7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !917
  %11 = load %struct.ar_w*, %struct.ar_w** %ar, align 8, !dbg !918
  %entry_padding8 = getelementptr inbounds %struct.ar_w, %struct.ar_w* %11, i32 0, i32 1, !dbg !919
  %12 = load i64, i64* %entry_padding8, align 8, !dbg !919
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive7, i32 -1, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.28, i32 0, i32 0), i64 %12), !dbg !920
  store i32 -20, i32* %retval, align 4, !dbg !921
  br label %return, !dbg !921

if.end9:                                          ; preds = %if.end3
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !922
  %call = call i32 @__archive_write_output(%struct.archive_write* %13, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.29, i32 0, i32 0), i64 1), !dbg !923
  store i32 %call, i32* %ret, align 4, !dbg !924
  %14 = load i32, i32* %ret, align 4, !dbg !925
  store i32 %14, i32* %retval, align 4, !dbg !926
  br label %return, !dbg !926

return:                                           ; preds = %if.end9, %if.then6, %if.then2, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !927
  ret i32 %15, !dbg !927
}

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #5

; Function Attrs: nounwind uwtable
define internal i8* @ar_basename(i8* %path) #0 !dbg !209 {
entry:
  %retval = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %endp = alloca i8*, align 8
  %startp = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !928, metadata !224), !dbg !929
  call void @llvm.dbg.declare(metadata i8** %endp, metadata !930, metadata !224), !dbg !931
  call void @llvm.dbg.declare(metadata i8** %startp, metadata !932, metadata !224), !dbg !933
  %0 = load i8*, i8** %path.addr, align 8, !dbg !934
  %1 = load i8*, i8** %path.addr, align 8, !dbg !935
  %call = call i64 @strlen(i8* %1) #7, !dbg !936
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 %call, !dbg !937
  %add.ptr1 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !938
  store i8* %add.ptr1, i8** %endp, align 8, !dbg !939
  %2 = load i8*, i8** %endp, align 8, !dbg !940
  %3 = load i8, i8* %2, align 1, !dbg !942
  %conv = sext i8 %3 to i32, !dbg !942
  %cmp = icmp eq i32 %conv, 47, !dbg !943
  br i1 %cmp, label %if.then, label %if.end, !dbg !944

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !945
  br label %return, !dbg !945

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %endp, align 8, !dbg !946
  store i8* %4, i8** %startp, align 8, !dbg !947
  br label %while.cond, !dbg !948

while.cond:                                       ; preds = %while.body, %if.end
  %5 = load i8*, i8** %startp, align 8, !dbg !949
  %6 = load i8*, i8** %path.addr, align 8, !dbg !951
  %cmp3 = icmp ugt i8* %5, %6, !dbg !952
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !953

land.rhs:                                         ; preds = %while.cond
  %7 = load i8*, i8** %startp, align 8, !dbg !954
  %add.ptr5 = getelementptr inbounds i8, i8* %7, i64 -1, !dbg !956
  %8 = load i8, i8* %add.ptr5, align 1, !dbg !957
  %conv6 = sext i8 %8 to i32, !dbg !957
  %cmp7 = icmp ne i32 %conv6, 47, !dbg !958
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %9 = phi i1 [ false, %while.cond ], [ %cmp7, %land.rhs ]
  br i1 %9, label %while.body, label %while.end, !dbg !959

while.body:                                       ; preds = %land.end
  %10 = load i8*, i8** %startp, align 8, !dbg !961
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 -1, !dbg !961
  store i8* %incdec.ptr, i8** %startp, align 8, !dbg !961
  br label %while.cond, !dbg !962

while.end:                                        ; preds = %land.end
  %11 = load i8*, i8** %startp, align 8, !dbg !964
  store i8* %11, i8** %retval, align 8, !dbg !965
  br label %return, !dbg !965

return:                                           ; preds = %while.end, %if.then
  %12 = load i8*, i8** %retval, align 8, !dbg !966
  ret i8* %12, !dbg !966
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #5

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #5

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @format_decimal(i64 %v, i8* %p, i32 %s) #0 !dbg !212 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %len = alloca i32, align 4
  %h = alloca i8*, align 8
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !967, metadata !224), !dbg !968
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !969, metadata !224), !dbg !970
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !971, metadata !224), !dbg !972
  call void @llvm.dbg.declare(metadata i32* %len, metadata !973, metadata !224), !dbg !974
  call void @llvm.dbg.declare(metadata i8** %h, metadata !975, metadata !224), !dbg !976
  %0 = load i32, i32* %s.addr, align 4, !dbg !977
  store i32 %0, i32* %len, align 4, !dbg !978
  %1 = load i8*, i8** %p.addr, align 8, !dbg !979
  store i8* %1, i8** %h, align 8, !dbg !980
  %2 = load i64, i64* %v.addr, align 8, !dbg !981
  %cmp = icmp slt i64 %2, 0, !dbg !983
  br i1 %cmp, label %if.then, label %if.end, !dbg !984

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !985

while.cond:                                       ; preds = %while.body, %if.then
  %3 = load i32, i32* %len, align 4, !dbg !987
  %dec = add nsw i32 %3, -1, !dbg !987
  store i32 %dec, i32* %len, align 4, !dbg !987
  %cmp1 = icmp sgt i32 %3, 0, !dbg !989
  br i1 %cmp1, label %while.body, label %while.end, !dbg !990

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %p.addr, align 8, !dbg !991
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !991
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !991
  store i8 48, i8* %4, align 1, !dbg !992
  br label %while.cond, !dbg !993

while.end:                                        ; preds = %while.cond
  store i32 -1, i32* %retval, align 4, !dbg !995
  br label %return, !dbg !995

if.end:                                           ; preds = %entry
  %5 = load i32, i32* %s.addr, align 4, !dbg !996
  %6 = load i8*, i8** %p.addr, align 8, !dbg !997
  %idx.ext = sext i32 %5 to i64, !dbg !997
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %idx.ext, !dbg !997
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !997
  br label %do.body, !dbg !998

do.body:                                          ; preds = %land.end, %if.end
  %7 = load i64, i64* %v.addr, align 8, !dbg !999
  %rem = srem i64 %7, 10, !dbg !1001
  %add = add nsw i64 48, %rem, !dbg !1002
  %conv = trunc i64 %add to i8, !dbg !1003
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1004
  %incdec.ptr2 = getelementptr inbounds i8, i8* %8, i32 -1, !dbg !1004
  store i8* %incdec.ptr2, i8** %p.addr, align 8, !dbg !1004
  store i8 %conv, i8* %incdec.ptr2, align 1, !dbg !1005
  %9 = load i64, i64* %v.addr, align 8, !dbg !1006
  %div = sdiv i64 %9, 10, !dbg !1006
  store i64 %div, i64* %v.addr, align 8, !dbg !1006
  br label %do.cond, !dbg !1007

do.cond:                                          ; preds = %do.body
  %10 = load i32, i32* %s.addr, align 4, !dbg !1008
  %dec3 = add nsw i32 %10, -1, !dbg !1008
  store i32 %dec3, i32* %s.addr, align 4, !dbg !1008
  %cmp4 = icmp sgt i32 %dec3, 0, !dbg !1010
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !1011

land.rhs:                                         ; preds = %do.cond
  %11 = load i64, i64* %v.addr, align 8, !dbg !1012
  %cmp6 = icmp sgt i64 %11, 0, !dbg !1014
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %12 = phi i1 [ false, %do.cond ], [ %cmp6, %land.rhs ]
  br i1 %12, label %do.body, label %do.end, !dbg !1015

do.end:                                           ; preds = %land.end
  %13 = load i64, i64* %v.addr, align 8, !dbg !1017
  %cmp8 = icmp eq i64 %13, 0, !dbg !1019
  br i1 %cmp8, label %if.then10, label %if.end23, !dbg !1020

if.then10:                                        ; preds = %do.end
  %14 = load i8*, i8** %h, align 8, !dbg !1021
  %15 = load i8*, i8** %p.addr, align 8, !dbg !1023
  %16 = load i32, i32* %len, align 4, !dbg !1024
  %17 = load i32, i32* %s.addr, align 4, !dbg !1025
  %sub = sub nsw i32 %16, %17, !dbg !1026
  %conv11 = sext i32 %sub to i64, !dbg !1024
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %14, i8* %15, i64 %conv11, i32 1, i1 false), !dbg !1027
  %18 = load i8*, i8** %h, align 8, !dbg !1028
  %19 = load i32, i32* %len, align 4, !dbg !1029
  %idx.ext12 = sext i32 %19 to i64, !dbg !1030
  %add.ptr13 = getelementptr inbounds i8, i8* %18, i64 %idx.ext12, !dbg !1030
  %20 = load i32, i32* %s.addr, align 4, !dbg !1031
  %idx.ext14 = sext i32 %20 to i64, !dbg !1032
  %idx.neg = sub i64 0, %idx.ext14, !dbg !1032
  %add.ptr15 = getelementptr inbounds i8, i8* %add.ptr13, i64 %idx.neg, !dbg !1032
  store i8* %add.ptr15, i8** %p.addr, align 8, !dbg !1033
  br label %while.cond16, !dbg !1034

while.cond16:                                     ; preds = %while.body20, %if.then10
  %21 = load i32, i32* %s.addr, align 4, !dbg !1035
  %dec17 = add nsw i32 %21, -1, !dbg !1035
  store i32 %dec17, i32* %s.addr, align 4, !dbg !1035
  %cmp18 = icmp sgt i32 %21, 0, !dbg !1037
  br i1 %cmp18, label %while.body20, label %while.end22, !dbg !1038

while.body20:                                     ; preds = %while.cond16
  %22 = load i8*, i8** %p.addr, align 8, !dbg !1039
  %incdec.ptr21 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !1039
  store i8* %incdec.ptr21, i8** %p.addr, align 8, !dbg !1039
  store i8 32, i8* %22, align 1, !dbg !1040
  br label %while.cond16, !dbg !1041

while.end22:                                      ; preds = %while.cond16
  store i32 0, i32* %retval, align 4, !dbg !1043
  br label %return, !dbg !1043

if.end23:                                         ; preds = %do.end
  br label %while.cond24, !dbg !1044

while.cond24:                                     ; preds = %while.body28, %if.end23
  %23 = load i32, i32* %len, align 4, !dbg !1045
  %dec25 = add nsw i32 %23, -1, !dbg !1045
  store i32 %dec25, i32* %len, align 4, !dbg !1045
  %cmp26 = icmp sgt i32 %23, 0, !dbg !1046
  br i1 %cmp26, label %while.body28, label %while.end30, !dbg !1047

while.body28:                                     ; preds = %while.cond24
  %24 = load i8*, i8** %p.addr, align 8, !dbg !1048
  %incdec.ptr29 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !1048
  store i8* %incdec.ptr29, i8** %p.addr, align 8, !dbg !1048
  store i8 57, i8* %24, align 1, !dbg !1049
  br label %while.cond24, !dbg !1050

while.end30:                                      ; preds = %while.cond24
  store i32 -1, i32* %retval, align 4, !dbg !1051
  br label %return, !dbg !1051

return:                                           ; preds = %while.end30, %while.end22, %while.end
  %25 = load i32, i32* %retval, align 4, !dbg !1052
  ret i32 %25, !dbg !1052
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #5

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @format_octal(i64 %v, i8* %p, i32 %s) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  %len = alloca i32, align 4
  %h = alloca i8*, align 8
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1053, metadata !224), !dbg !1054
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1055, metadata !224), !dbg !1056
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1057, metadata !224), !dbg !1058
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1059, metadata !224), !dbg !1060
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1061, metadata !224), !dbg !1062
  %0 = load i32, i32* %s.addr, align 4, !dbg !1063
  store i32 %0, i32* %len, align 4, !dbg !1064
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1065
  store i8* %1, i8** %h, align 8, !dbg !1066
  %2 = load i64, i64* %v.addr, align 8, !dbg !1067
  %cmp = icmp slt i64 %2, 0, !dbg !1069
  br i1 %cmp, label %if.then, label %if.end, !dbg !1070

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !1071

while.cond:                                       ; preds = %while.body, %if.then
  %3 = load i32, i32* %len, align 4, !dbg !1073
  %dec = add nsw i32 %3, -1, !dbg !1073
  store i32 %dec, i32* %len, align 4, !dbg !1073
  %cmp1 = icmp sgt i32 %3, 0, !dbg !1075
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1076

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1077
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !1077
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1077
  store i8 48, i8* %4, align 1, !dbg !1078
  br label %while.cond, !dbg !1079

while.end:                                        ; preds = %while.cond
  store i32 -1, i32* %retval, align 4, !dbg !1081
  br label %return, !dbg !1081

if.end:                                           ; preds = %entry
  %5 = load i32, i32* %s.addr, align 4, !dbg !1082
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1083
  %idx.ext = sext i32 %5 to i64, !dbg !1083
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %idx.ext, !dbg !1083
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1083
  br label %do.body, !dbg !1084

do.body:                                          ; preds = %land.end, %if.end
  %7 = load i64, i64* %v.addr, align 8, !dbg !1085
  %and = and i64 %7, 7, !dbg !1087
  %add = add nsw i64 48, %and, !dbg !1088
  %conv = trunc i64 %add to i8, !dbg !1089
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1090
  %incdec.ptr2 = getelementptr inbounds i8, i8* %8, i32 -1, !dbg !1090
  store i8* %incdec.ptr2, i8** %p.addr, align 8, !dbg !1090
  store i8 %conv, i8* %incdec.ptr2, align 1, !dbg !1091
  %9 = load i64, i64* %v.addr, align 8, !dbg !1092
  %shr = ashr i64 %9, 3, !dbg !1092
  store i64 %shr, i64* %v.addr, align 8, !dbg !1092
  br label %do.cond, !dbg !1093

do.cond:                                          ; preds = %do.body
  %10 = load i32, i32* %s.addr, align 4, !dbg !1094
  %dec3 = add nsw i32 %10, -1, !dbg !1094
  store i32 %dec3, i32* %s.addr, align 4, !dbg !1094
  %cmp4 = icmp sgt i32 %dec3, 0, !dbg !1096
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !1097

land.rhs:                                         ; preds = %do.cond
  %11 = load i64, i64* %v.addr, align 8, !dbg !1098
  %cmp6 = icmp sgt i64 %11, 0, !dbg !1100
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %12 = phi i1 [ false, %do.cond ], [ %cmp6, %land.rhs ]
  br i1 %12, label %do.body, label %do.end, !dbg !1101

do.end:                                           ; preds = %land.end
  %13 = load i64, i64* %v.addr, align 8, !dbg !1103
  %cmp8 = icmp eq i64 %13, 0, !dbg !1105
  br i1 %cmp8, label %if.then10, label %if.end23, !dbg !1106

if.then10:                                        ; preds = %do.end
  %14 = load i8*, i8** %h, align 8, !dbg !1107
  %15 = load i8*, i8** %p.addr, align 8, !dbg !1109
  %16 = load i32, i32* %len, align 4, !dbg !1110
  %17 = load i32, i32* %s.addr, align 4, !dbg !1111
  %sub = sub nsw i32 %16, %17, !dbg !1112
  %conv11 = sext i32 %sub to i64, !dbg !1110
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %14, i8* %15, i64 %conv11, i32 1, i1 false), !dbg !1113
  %18 = load i8*, i8** %h, align 8, !dbg !1114
  %19 = load i32, i32* %len, align 4, !dbg !1115
  %idx.ext12 = sext i32 %19 to i64, !dbg !1116
  %add.ptr13 = getelementptr inbounds i8, i8* %18, i64 %idx.ext12, !dbg !1116
  %20 = load i32, i32* %s.addr, align 4, !dbg !1117
  %idx.ext14 = sext i32 %20 to i64, !dbg !1118
  %idx.neg = sub i64 0, %idx.ext14, !dbg !1118
  %add.ptr15 = getelementptr inbounds i8, i8* %add.ptr13, i64 %idx.neg, !dbg !1118
  store i8* %add.ptr15, i8** %p.addr, align 8, !dbg !1119
  br label %while.cond16, !dbg !1120

while.cond16:                                     ; preds = %while.body20, %if.then10
  %21 = load i32, i32* %s.addr, align 4, !dbg !1121
  %dec17 = add nsw i32 %21, -1, !dbg !1121
  store i32 %dec17, i32* %s.addr, align 4, !dbg !1121
  %cmp18 = icmp sgt i32 %21, 0, !dbg !1123
  br i1 %cmp18, label %while.body20, label %while.end22, !dbg !1124

while.body20:                                     ; preds = %while.cond16
  %22 = load i8*, i8** %p.addr, align 8, !dbg !1125
  %incdec.ptr21 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !1125
  store i8* %incdec.ptr21, i8** %p.addr, align 8, !dbg !1125
  store i8 32, i8* %22, align 1, !dbg !1126
  br label %while.cond16, !dbg !1127

while.end22:                                      ; preds = %while.cond16
  store i32 0, i32* %retval, align 4, !dbg !1129
  br label %return, !dbg !1129

if.end23:                                         ; preds = %do.end
  br label %while.cond24, !dbg !1130

while.cond24:                                     ; preds = %while.body28, %if.end23
  %23 = load i32, i32* %len, align 4, !dbg !1131
  %dec25 = add nsw i32 %23, -1, !dbg !1131
  store i32 %dec25, i32* %len, align 4, !dbg !1131
  %cmp26 = icmp sgt i32 %23, 0, !dbg !1132
  br i1 %cmp26, label %while.body28, label %while.end30, !dbg !1133

while.body28:                                     ; preds = %while.cond24
  %24 = load i8*, i8** %p.addr, align 8, !dbg !1134
  %incdec.ptr29 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !1134
  store i8* %incdec.ptr29, i8** %p.addr, align 8, !dbg !1134
  store i8 55, i8* %24, align 1, !dbg !1135
  br label %while.cond24, !dbg !1136

while.end30:                                      ; preds = %while.cond24
  store i32 -1, i32* %retval, align 4, !dbg !1137
  br label %return, !dbg !1137

return:                                           ; preds = %while.end30, %while.end22, %while.end
  %25 = load i32, i32* %retval, align 4, !dbg !1138
  ret i32 %25, !dbg !1138
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!220, !221}
!llvm.ident = !{!222}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !204)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_ar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123, !191, !95, !201, !82, !45, !203}
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
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "ar_w", file: !1, line: 46, size: 320, align: 64, elements: !193)
!193 = !{!194, !196, !197, !198, !199, !200}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !192, file: !1, line: 47, baseType: !195, size: 64, align: 64)
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !192, file: !1, line: 48, baseType: !195, size: 64, align: 64, offset: 64)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "is_strtab", scope: !192, file: !1, line: 49, baseType: !23, size: 32, align: 32, offset: 128)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "has_strtab", scope: !192, file: !1, line: 50, baseType: !23, size: 32, align: 32, offset: 160)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "wrote_global_header", scope: !192, file: !1, line: 51, baseType: !82, size: 8, align: 8, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "strtab", scope: !192, file: !1, line: 52, baseType: !95, size: 64, align: 64, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !202)
!202 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !53, line: 135, baseType: !47)
!204 = !{!205, !206, !207, !208, !209, !212, !215, !216, !217, !218, !219}
!205 = distinct !DISubprogram(name: "archive_write_set_format_ar_bsd", scope: !1, file: !1, line: 86, type: !21, isLocal: false, isDefinition: true, scopeLine: 87, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!206 = distinct !DISubprogram(name: "archive_write_set_format_ar_svr4", scope: !1, file: !1, line: 102, type: !21, isLocal: false, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!207 = distinct !DISubprogram(name: "archive_write_set_format_ar", scope: !1, file: !1, line: 121, type: !167, isLocal: true, isDefinition: true, scopeLine: 122, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!208 = distinct !DISubprogram(name: "archive_write_ar_header", scope: !1, file: !1, line: 146, type: !176, isLocal: true, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!209 = distinct !DISubprogram(name: "ar_basename", scope: !1, file: !1, line: 545, type: !210, isLocal: true, isDefinition: true, scopeLine: 546, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!210 = !DISubroutineType(types: !211)
!211 = !{!80, !80}
!212 = distinct !DISubprogram(name: "format_decimal", scope: !1, file: !1, line: 509, type: !213, isLocal: true, isDefinition: true, scopeLine: 510, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!213 = !DISubroutineType(types: !214)
!214 = !{!23, !52, !95, !23}
!215 = distinct !DISubprogram(name: "format_octal", scope: !1, file: !1, line: 470, type: !213, isLocal: true, isDefinition: true, scopeLine: 471, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "archive_write_ar_data", scope: !1, file: !1, line: 361, type: !180, isLocal: true, isDefinition: true, scopeLine: 362, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = distinct !DISubprogram(name: "archive_write_ar_close", scope: !1, file: !1, line: 416, type: !167, isLocal: true, isDefinition: true, scopeLine: 417, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = distinct !DISubprogram(name: "archive_write_ar_free", scope: !1, file: !1, line: 396, type: !167, isLocal: true, isDefinition: true, scopeLine: 397, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_ar_finish_entry", scope: !1, file: !1, line: 436, type: !167, isLocal: true, isDefinition: true, scopeLine: 437, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = !{i32 2, !"Dwarf Version", i32 4}
!221 = !{i32 2, !"Debug Info Version", i32 3}
!222 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!223 = !DILocalVariable(name: "_a", arg: 1, scope: !205, file: !1, line: 86, type: !24)
!224 = !DIExpression()
!225 = !DILocation(line: 86, column: 49, scope: !205)
!226 = !DILocalVariable(name: "a", scope: !205, file: !1, line: 88, type: !4)
!227 = !DILocation(line: 88, column: 24, scope: !205)
!228 = !DILocation(line: 88, column: 52, scope: !205)
!229 = !DILocation(line: 88, column: 28, scope: !205)
!230 = !DILocalVariable(name: "r", scope: !205, file: !1, line: 89, type: !23)
!231 = !DILocation(line: 89, column: 6, scope: !205)
!232 = !DILocation(line: 91, column: 2, scope: !205)
!233 = !DILocalVariable(name: "magic_test", scope: !234, file: !1, line: 91, type: !23)
!234 = distinct !DILexicalBlock(scope: !205, file: !1, line: 91, column: 2)
!235 = !DILocation(line: 91, column: 2, scope: !234)
!236 = !DILocation(line: 91, column: 2, scope: !237)
!237 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 1)
!238 = !DILocation(line: 91, column: 2, scope: !239)
!239 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 2)
!240 = distinct !DILexicalBlock(scope: !234, file: !1, line: 91, column: 2)
!241 = !DILocation(line: 91, column: 2, scope: !242)
!242 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 3)
!243 = !DILocation(line: 93, column: 34, scope: !205)
!244 = !DILocation(line: 93, column: 6, scope: !205)
!245 = !DILocation(line: 93, column: 4, scope: !205)
!246 = !DILocation(line: 94, column: 6, scope: !247)
!247 = distinct !DILexicalBlock(scope: !205, file: !1, line: 94, column: 6)
!248 = !DILocation(line: 94, column: 8, scope: !247)
!249 = !DILocation(line: 94, column: 6, scope: !205)
!250 = !DILocation(line: 95, column: 3, scope: !251)
!251 = distinct !DILexicalBlock(scope: !247, file: !1, line: 94, column: 23)
!252 = !DILocation(line: 95, column: 6, scope: !251)
!253 = !DILocation(line: 95, column: 14, scope: !251)
!254 = !DILocation(line: 95, column: 29, scope: !251)
!255 = !DILocation(line: 96, column: 3, scope: !251)
!256 = !DILocation(line: 96, column: 6, scope: !251)
!257 = !DILocation(line: 96, column: 14, scope: !251)
!258 = !DILocation(line: 96, column: 34, scope: !251)
!259 = !DILocation(line: 97, column: 2, scope: !251)
!260 = !DILocation(line: 98, column: 10, scope: !205)
!261 = !DILocation(line: 98, column: 2, scope: !205)
!262 = !DILocation(line: 99, column: 1, scope: !205)
!263 = !DILocalVariable(name: "a", arg: 1, scope: !207, file: !1, line: 121, type: !4)
!264 = !DILocation(line: 121, column: 51, scope: !207)
!265 = !DILocalVariable(name: "ar", scope: !207, file: !1, line: 123, type: !191)
!266 = !DILocation(line: 123, column: 15, scope: !207)
!267 = !DILocation(line: 126, column: 6, scope: !268)
!268 = distinct !DILexicalBlock(scope: !207, file: !1, line: 126, column: 6)
!269 = !DILocation(line: 126, column: 9, scope: !268)
!270 = !DILocation(line: 126, column: 21, scope: !268)
!271 = !DILocation(line: 126, column: 6, scope: !207)
!272 = !DILocation(line: 127, column: 4, scope: !268)
!273 = !DILocation(line: 127, column: 7, scope: !268)
!274 = !DILocation(line: 127, column: 20, scope: !268)
!275 = !DILocation(line: 127, column: 3, scope: !268)
!276 = !DILocation(line: 129, column: 22, scope: !207)
!277 = !DILocation(line: 129, column: 7, scope: !207)
!278 = !DILocation(line: 129, column: 5, scope: !207)
!279 = !DILocation(line: 130, column: 6, scope: !280)
!280 = distinct !DILexicalBlock(scope: !207, file: !1, line: 130, column: 6)
!281 = !DILocation(line: 130, column: 9, scope: !280)
!282 = !DILocation(line: 130, column: 6, scope: !207)
!283 = !DILocation(line: 131, column: 22, scope: !284)
!284 = distinct !DILexicalBlock(scope: !280, file: !1, line: 130, column: 18)
!285 = !DILocation(line: 131, column: 25, scope: !284)
!286 = !DILocation(line: 131, column: 3, scope: !284)
!287 = !DILocation(line: 132, column: 3, scope: !284)
!288 = !DILocation(line: 134, column: 19, scope: !207)
!289 = !DILocation(line: 134, column: 2, scope: !207)
!290 = !DILocation(line: 134, column: 5, scope: !207)
!291 = !DILocation(line: 134, column: 17, scope: !207)
!292 = !DILocation(line: 136, column: 2, scope: !207)
!293 = !DILocation(line: 136, column: 5, scope: !207)
!294 = !DILocation(line: 136, column: 17, scope: !207)
!295 = !DILocation(line: 137, column: 2, scope: !207)
!296 = !DILocation(line: 137, column: 5, scope: !207)
!297 = !DILocation(line: 137, column: 25, scope: !207)
!298 = !DILocation(line: 138, column: 2, scope: !207)
!299 = !DILocation(line: 138, column: 5, scope: !207)
!300 = !DILocation(line: 138, column: 23, scope: !207)
!301 = !DILocation(line: 139, column: 2, scope: !207)
!302 = !DILocation(line: 139, column: 5, scope: !207)
!303 = !DILocation(line: 139, column: 18, scope: !207)
!304 = !DILocation(line: 140, column: 2, scope: !207)
!305 = !DILocation(line: 140, column: 5, scope: !207)
!306 = !DILocation(line: 140, column: 17, scope: !207)
!307 = !DILocation(line: 141, column: 2, scope: !207)
!308 = !DILocation(line: 141, column: 5, scope: !207)
!309 = !DILocation(line: 141, column: 25, scope: !207)
!310 = !DILocation(line: 142, column: 2, scope: !207)
!311 = !DILocation(line: 143, column: 1, scope: !207)
!312 = !DILocalVariable(name: "_a", arg: 1, scope: !206, file: !1, line: 102, type: !24)
!313 = !DILocation(line: 102, column: 50, scope: !206)
!314 = !DILocalVariable(name: "a", scope: !206, file: !1, line: 104, type: !4)
!315 = !DILocation(line: 104, column: 24, scope: !206)
!316 = !DILocation(line: 104, column: 52, scope: !206)
!317 = !DILocation(line: 104, column: 28, scope: !206)
!318 = !DILocalVariable(name: "r", scope: !206, file: !1, line: 105, type: !23)
!319 = !DILocation(line: 105, column: 6, scope: !206)
!320 = !DILocation(line: 107, column: 2, scope: !206)
!321 = !DILocalVariable(name: "magic_test", scope: !322, file: !1, line: 107, type: !23)
!322 = distinct !DILexicalBlock(scope: !206, file: !1, line: 107, column: 2)
!323 = !DILocation(line: 107, column: 2, scope: !322)
!324 = !DILocation(line: 107, column: 2, scope: !325)
!325 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!326 = !DILocation(line: 107, column: 2, scope: !327)
!327 = !DILexicalBlockFile(scope: !328, file: !1, discriminator: 2)
!328 = distinct !DILexicalBlock(scope: !322, file: !1, line: 107, column: 2)
!329 = !DILocation(line: 107, column: 2, scope: !330)
!330 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 3)
!331 = !DILocation(line: 109, column: 34, scope: !206)
!332 = !DILocation(line: 109, column: 6, scope: !206)
!333 = !DILocation(line: 109, column: 4, scope: !206)
!334 = !DILocation(line: 110, column: 6, scope: !335)
!335 = distinct !DILexicalBlock(scope: !206, file: !1, line: 110, column: 6)
!336 = !DILocation(line: 110, column: 8, scope: !335)
!337 = !DILocation(line: 110, column: 6, scope: !206)
!338 = !DILocation(line: 111, column: 3, scope: !339)
!339 = distinct !DILexicalBlock(scope: !335, file: !1, line: 110, column: 23)
!340 = !DILocation(line: 111, column: 6, scope: !339)
!341 = !DILocation(line: 111, column: 14, scope: !339)
!342 = !DILocation(line: 111, column: 29, scope: !339)
!343 = !DILocation(line: 112, column: 3, scope: !339)
!344 = !DILocation(line: 112, column: 6, scope: !339)
!345 = !DILocation(line: 112, column: 14, scope: !339)
!346 = !DILocation(line: 112, column: 34, scope: !339)
!347 = !DILocation(line: 113, column: 2, scope: !339)
!348 = !DILocation(line: 114, column: 10, scope: !206)
!349 = !DILocation(line: 114, column: 2, scope: !206)
!350 = !DILocation(line: 115, column: 1, scope: !206)
!351 = !DILocalVariable(name: "a", arg: 1, scope: !208, file: !1, line: 146, type: !4)
!352 = !DILocation(line: 146, column: 47, scope: !208)
!353 = !DILocalVariable(name: "entry", arg: 2, scope: !208, file: !1, line: 146, type: !30)
!354 = !DILocation(line: 146, column: 72, scope: !208)
!355 = !DILocalVariable(name: "ret", scope: !208, file: !1, line: 148, type: !23)
!356 = !DILocation(line: 148, column: 6, scope: !208)
!357 = !DILocalVariable(name: "append_fn", scope: !208, file: !1, line: 148, type: !23)
!358 = !DILocation(line: 148, column: 11, scope: !208)
!359 = !DILocalVariable(name: "buff", scope: !208, file: !1, line: 149, type: !360)
!360 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 480, align: 8, elements: !361)
!361 = !{!362}
!362 = !DISubrange(count: 60)
!363 = !DILocation(line: 149, column: 7, scope: !208)
!364 = !DILocalVariable(name: "ss", scope: !208, file: !1, line: 150, type: !95)
!365 = !DILocation(line: 150, column: 8, scope: !208)
!366 = !DILocalVariable(name: "se", scope: !208, file: !1, line: 150, type: !95)
!367 = !DILocation(line: 150, column: 13, scope: !208)
!368 = !DILocalVariable(name: "ar", scope: !208, file: !1, line: 151, type: !191)
!369 = !DILocation(line: 151, column: 15, scope: !208)
!370 = !DILocalVariable(name: "pathname", scope: !208, file: !1, line: 152, type: !80)
!371 = !DILocation(line: 152, column: 14, scope: !208)
!372 = !DILocalVariable(name: "filename", scope: !208, file: !1, line: 153, type: !80)
!373 = !DILocation(line: 153, column: 14, scope: !208)
!374 = !DILocalVariable(name: "size", scope: !208, file: !1, line: 154, type: !52)
!375 = !DILocation(line: 154, column: 10, scope: !208)
!376 = !DILocation(line: 156, column: 12, scope: !208)
!377 = !DILocation(line: 157, column: 22, scope: !208)
!378 = !DILocation(line: 157, column: 25, scope: !208)
!379 = !DILocation(line: 157, column: 7, scope: !208)
!380 = !DILocation(line: 157, column: 5, scope: !208)
!381 = !DILocation(line: 158, column: 2, scope: !208)
!382 = !DILocation(line: 158, column: 6, scope: !208)
!383 = !DILocation(line: 158, column: 16, scope: !208)
!384 = !DILocation(line: 159, column: 11, scope: !208)
!385 = !DILocation(line: 160, column: 28, scope: !208)
!386 = !DILocation(line: 160, column: 9, scope: !208)
!387 = !DILocation(line: 160, column: 7, scope: !208)
!388 = !DILocation(line: 166, column: 36, scope: !208)
!389 = !DILocation(line: 166, column: 13, scope: !208)
!390 = !DILocation(line: 166, column: 11, scope: !208)
!391 = !DILocation(line: 167, column: 6, scope: !392)
!392 = distinct !DILexicalBlock(scope: !208, file: !1, line: 167, column: 6)
!393 = !DILocation(line: 167, column: 15, scope: !392)
!394 = !DILocation(line: 167, column: 23, scope: !392)
!395 = !DILocation(line: 167, column: 27, scope: !396)
!396 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!397 = !DILocation(line: 167, column: 26, scope: !396)
!398 = !DILocation(line: 167, column: 36, scope: !396)
!399 = !DILocation(line: 167, column: 6, scope: !396)
!400 = !DILocation(line: 168, column: 22, scope: !401)
!401 = distinct !DILexicalBlock(scope: !392, file: !1, line: 167, column: 45)
!402 = !DILocation(line: 168, column: 25, scope: !401)
!403 = !DILocation(line: 168, column: 3, scope: !401)
!404 = !DILocation(line: 170, column: 3, scope: !401)
!405 = !DILocation(line: 177, column: 7, scope: !406)
!406 = distinct !DILexicalBlock(scope: !208, file: !1, line: 177, column: 6)
!407 = !DILocation(line: 177, column: 11, scope: !406)
!408 = !DILocation(line: 177, column: 6, scope: !208)
!409 = !DILocation(line: 178, column: 26, scope: !410)
!410 = distinct !DILexicalBlock(scope: !406, file: !1, line: 177, column: 32)
!411 = !DILocation(line: 178, column: 3, scope: !410)
!412 = !DILocation(line: 179, column: 3, scope: !410)
!413 = !DILocation(line: 179, column: 7, scope: !410)
!414 = !DILocation(line: 179, column: 27, scope: !410)
!415 = !DILocation(line: 180, column: 2, scope: !410)
!416 = !DILocation(line: 182, column: 2, scope: !208)
!417 = !DILocation(line: 183, column: 11, scope: !208)
!418 = !DILocation(line: 183, column: 2, scope: !208)
!419 = !DILocation(line: 185, column: 13, scope: !420)
!420 = distinct !DILexicalBlock(scope: !208, file: !1, line: 185, column: 6)
!421 = !DILocation(line: 185, column: 6, scope: !420)
!422 = !DILocation(line: 185, column: 28, scope: !420)
!423 = !DILocation(line: 185, column: 6, scope: !208)
!424 = !DILocation(line: 187, column: 3, scope: !425)
!425 = distinct !DILexicalBlock(scope: !420, file: !1, line: 185, column: 35)
!426 = !DILocation(line: 187, column: 24, scope: !425)
!427 = !DILocation(line: 188, column: 3, scope: !425)
!428 = !DILocation(line: 190, column: 13, scope: !429)
!429 = distinct !DILexicalBlock(scope: !208, file: !1, line: 190, column: 6)
!430 = !DILocation(line: 190, column: 6, scope: !429)
!431 = !DILocation(line: 190, column: 36, scope: !429)
!432 = !DILocation(line: 190, column: 6, scope: !208)
!433 = !DILocation(line: 192, column: 11, scope: !434)
!434 = distinct !DILexicalBlock(scope: !429, file: !1, line: 190, column: 42)
!435 = !DILocation(line: 192, column: 16, scope: !434)
!436 = !DILocation(line: 192, column: 3, scope: !434)
!437 = !DILocation(line: 193, column: 3, scope: !434)
!438 = !DILocation(line: 195, column: 13, scope: !439)
!439 = distinct !DILexicalBlock(scope: !208, file: !1, line: 195, column: 6)
!440 = !DILocation(line: 195, column: 6, scope: !439)
!441 = !DILocation(line: 195, column: 29, scope: !439)
!442 = !DILocation(line: 195, column: 6, scope: !208)
!443 = !DILocation(line: 200, column: 3, scope: !444)
!444 = distinct !DILexicalBlock(scope: !439, file: !1, line: 195, column: 35)
!445 = !DILocation(line: 200, column: 7, scope: !444)
!446 = !DILocation(line: 200, column: 17, scope: !444)
!447 = !DILocation(line: 201, column: 26, scope: !444)
!448 = !DILocation(line: 201, column: 51, scope: !444)
!449 = !DILocation(line: 201, column: 3, scope: !444)
!450 = !DILocation(line: 201, column: 24, scope: !444)
!451 = !DILocation(line: 206, column: 3, scope: !444)
!452 = !DILocation(line: 213, column: 30, scope: !453)
!453 = distinct !DILexicalBlock(scope: !208, file: !1, line: 213, column: 6)
!454 = !DILocation(line: 213, column: 18, scope: !453)
!455 = !DILocation(line: 213, column: 16, scope: !453)
!456 = !DILocation(line: 213, column: 41, scope: !453)
!457 = !DILocation(line: 213, column: 6, scope: !208)
!458 = !DILocation(line: 215, column: 22, scope: !459)
!459 = distinct !DILexicalBlock(scope: !453, file: !1, line: 213, column: 50)
!460 = !DILocation(line: 215, column: 25, scope: !459)
!461 = !DILocation(line: 215, column: 3, scope: !459)
!462 = !DILocation(line: 217, column: 3, scope: !459)
!463 = !DILocation(line: 220, column: 6, scope: !464)
!464 = distinct !DILexicalBlock(scope: !208, file: !1, line: 220, column: 6)
!465 = !DILocation(line: 220, column: 9, scope: !464)
!466 = !DILocation(line: 220, column: 17, scope: !464)
!467 = !DILocation(line: 220, column: 32, scope: !464)
!468 = !DILocation(line: 220, column: 6, scope: !208)
!469 = !DILocation(line: 227, column: 14, scope: !470)
!470 = distinct !DILexicalBlock(scope: !471, file: !1, line: 227, column: 7)
!471 = distinct !DILexicalBlock(scope: !464, file: !1, line: 220, column: 58)
!472 = !DILocation(line: 227, column: 7, scope: !470)
!473 = !DILocation(line: 227, column: 24, scope: !470)
!474 = !DILocation(line: 227, column: 7, scope: !471)
!475 = !DILocation(line: 228, column: 13, scope: !476)
!476 = distinct !DILexicalBlock(scope: !470, file: !1, line: 227, column: 31)
!477 = !DILocation(line: 229, column: 8, scope: !476)
!478 = !DILocation(line: 229, column: 25, scope: !476)
!479 = !DILocation(line: 229, column: 18, scope: !476)
!480 = !DILocation(line: 228, column: 4, scope: !476)
!481 = !DILocation(line: 230, column: 33, scope: !476)
!482 = !DILocation(line: 230, column: 26, scope: !476)
!483 = !DILocation(line: 230, column: 24, scope: !476)
!484 = !DILocation(line: 230, column: 4, scope: !476)
!485 = !DILocation(line: 230, column: 44, scope: !476)
!486 = !DILocation(line: 231, column: 3, scope: !476)
!487 = !DILocation(line: 238, column: 8, scope: !488)
!488 = distinct !DILexicalBlock(scope: !489, file: !1, line: 238, column: 8)
!489 = distinct !DILexicalBlock(scope: !470, file: !1, line: 231, column: 10)
!490 = !DILocation(line: 238, column: 12, scope: !488)
!491 = !DILocation(line: 238, column: 23, scope: !488)
!492 = !DILocation(line: 238, column: 8, scope: !489)
!493 = !DILocation(line: 239, column: 24, scope: !494)
!494 = distinct !DILexicalBlock(scope: !488, file: !1, line: 238, column: 29)
!495 = !DILocation(line: 239, column: 27, scope: !494)
!496 = !DILocation(line: 239, column: 5, scope: !494)
!497 = !DILocation(line: 241, column: 5, scope: !494)
!498 = !DILocation(line: 244, column: 31, scope: !489)
!499 = !DILocation(line: 244, column: 24, scope: !489)
!500 = !DILocation(line: 244, column: 41, scope: !489)
!501 = !DILocation(line: 244, column: 17, scope: !502)
!502 = !DILexicalBlockFile(scope: !489, file: !1, discriminator: 1)
!503 = !DILocation(line: 244, column: 7, scope: !489)
!504 = !DILocation(line: 245, column: 8, scope: !505)
!505 = distinct !DILexicalBlock(scope: !489, file: !1, line: 245, column: 8)
!506 = !DILocation(line: 245, column: 11, scope: !505)
!507 = !DILocation(line: 245, column: 8, scope: !489)
!508 = !DILocation(line: 246, column: 24, scope: !509)
!509 = distinct !DILexicalBlock(scope: !505, file: !1, line: 245, column: 20)
!510 = !DILocation(line: 246, column: 27, scope: !509)
!511 = !DILocation(line: 246, column: 5, scope: !509)
!512 = !DILocation(line: 248, column: 5, scope: !509)
!513 = !DILocation(line: 251, column: 12, scope: !489)
!514 = !DILocation(line: 251, column: 16, scope: !489)
!515 = !DILocation(line: 251, column: 33, scope: !489)
!516 = !DILocation(line: 251, column: 26, scope: !489)
!517 = !DILocation(line: 251, column: 4, scope: !502)
!518 = !DILocation(line: 252, column: 11, scope: !489)
!519 = !DILocation(line: 252, column: 23, scope: !489)
!520 = !DILocation(line: 252, column: 16, scope: !489)
!521 = !DILocation(line: 252, column: 14, scope: !489)
!522 = !DILocation(line: 252, column: 4, scope: !502)
!523 = !DILocation(line: 254, column: 16, scope: !489)
!524 = !DILocation(line: 254, column: 20, scope: !489)
!525 = !DILocation(line: 254, column: 28, scope: !489)
!526 = !DILocation(line: 254, column: 9, scope: !489)
!527 = !DILocation(line: 254, column: 7, scope: !489)
!528 = !DILocation(line: 255, column: 9, scope: !489)
!529 = !DILocation(line: 255, column: 4, scope: !489)
!530 = !DILocation(line: 257, column: 8, scope: !531)
!531 = distinct !DILexicalBlock(scope: !489, file: !1, line: 257, column: 8)
!532 = !DILocation(line: 257, column: 11, scope: !531)
!533 = !DILocation(line: 257, column: 8, scope: !489)
!534 = !DILocation(line: 258, column: 24, scope: !535)
!535 = distinct !DILexicalBlock(scope: !531, file: !1, line: 257, column: 20)
!536 = !DILocation(line: 258, column: 27, scope: !535)
!537 = !DILocation(line: 258, column: 5, scope: !535)
!538 = !DILocation(line: 260, column: 5, scope: !535)
!539 = !DILocation(line: 268, column: 4, scope: !489)
!540 = !DILocation(line: 268, column: 25, scope: !489)
!541 = !DILocation(line: 269, column: 23, scope: !542)
!542 = distinct !DILexicalBlock(scope: !489, file: !1, line: 269, column: 8)
!543 = !DILocation(line: 269, column: 28, scope: !542)
!544 = !DILocation(line: 269, column: 32, scope: !542)
!545 = !DILocation(line: 269, column: 26, scope: !542)
!546 = !DILocation(line: 270, column: 8, scope: !542)
!547 = !DILocation(line: 270, column: 13, scope: !542)
!548 = !DILocation(line: 270, column: 30, scope: !542)
!549 = !DILocation(line: 269, column: 8, scope: !542)
!550 = !DILocation(line: 269, column: 8, scope: !489)
!551 = !DILocation(line: 272, column: 24, scope: !552)
!552 = distinct !DILexicalBlock(scope: !542, file: !1, line: 271, column: 27)
!553 = !DILocation(line: 272, column: 27, scope: !552)
!554 = !DILocation(line: 272, column: 5, scope: !552)
!555 = !DILocation(line: 274, column: 5, scope: !552)
!556 = !DILocation(line: 277, column: 2, scope: !471)
!557 = !DILocation(line: 277, column: 13, scope: !558)
!558 = !DILexicalBlockFile(scope: !559, file: !1, discriminator: 1)
!559 = distinct !DILexicalBlock(scope: !464, file: !1, line: 277, column: 13)
!560 = !DILocation(line: 277, column: 16, scope: !558)
!561 = !DILocation(line: 277, column: 24, scope: !558)
!562 = !DILocation(line: 277, column: 39, scope: !558)
!563 = !DILocation(line: 287, column: 14, scope: !564)
!564 = distinct !DILexicalBlock(scope: !565, file: !1, line: 287, column: 7)
!565 = distinct !DILexicalBlock(scope: !559, file: !1, line: 277, column: 65)
!566 = !DILocation(line: 287, column: 7, scope: !564)
!567 = !DILocation(line: 287, column: 24, scope: !564)
!568 = !DILocation(line: 287, column: 30, scope: !564)
!569 = !DILocation(line: 287, column: 40, scope: !570)
!570 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 1)
!571 = !DILocation(line: 287, column: 33, scope: !570)
!572 = !DILocation(line: 287, column: 55, scope: !570)
!573 = !DILocation(line: 287, column: 7, scope: !570)
!574 = !DILocation(line: 288, column: 13, scope: !575)
!575 = distinct !DILexicalBlock(scope: !564, file: !1, line: 287, column: 64)
!576 = !DILocation(line: 288, column: 35, scope: !575)
!577 = !DILocation(line: 288, column: 52, scope: !575)
!578 = !DILocation(line: 288, column: 45, scope: !575)
!579 = !DILocation(line: 288, column: 4, scope: !580)
!580 = !DILexicalBlockFile(scope: !575, file: !1, discriminator: 1)
!581 = !DILocation(line: 289, column: 33, scope: !575)
!582 = !DILocation(line: 289, column: 26, scope: !575)
!583 = !DILocation(line: 289, column: 24, scope: !575)
!584 = !DILocation(line: 289, column: 4, scope: !575)
!585 = !DILocation(line: 289, column: 44, scope: !575)
!586 = !DILocation(line: 290, column: 3, scope: !575)
!587 = !DILocation(line: 292, column: 12, scope: !588)
!588 = distinct !DILexicalBlock(scope: !564, file: !1, line: 291, column: 8)
!589 = !DILocation(line: 292, column: 17, scope: !588)
!590 = !DILocation(line: 292, column: 4, scope: !588)
!591 = !DILocation(line: 293, column: 30, scope: !592)
!592 = distinct !DILexicalBlock(scope: !588, file: !1, line: 293, column: 8)
!593 = !DILocation(line: 293, column: 23, scope: !592)
!594 = !DILocation(line: 294, column: 8, scope: !592)
!595 = !DILocation(line: 294, column: 13, scope: !592)
!596 = !DILocation(line: 294, column: 30, scope: !592)
!597 = !DILocation(line: 293, column: 8, scope: !598)
!598 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 1)
!599 = !DILocation(line: 293, column: 8, scope: !592)
!600 = !DILocation(line: 293, column: 8, scope: !588)
!601 = !DILocation(line: 296, column: 24, scope: !602)
!602 = distinct !DILexicalBlock(scope: !592, file: !1, line: 295, column: 27)
!603 = !DILocation(line: 296, column: 27, scope: !602)
!604 = !DILocation(line: 296, column: 5, scope: !602)
!605 = !DILocation(line: 298, column: 5, scope: !602)
!606 = !DILocation(line: 300, column: 14, scope: !588)
!607 = !DILocation(line: 301, column: 19, scope: !588)
!608 = !DILocation(line: 301, column: 12, scope: !588)
!609 = !DILocation(line: 301, column: 9, scope: !588)
!610 = !DILocation(line: 303, column: 2, scope: !565)
!611 = !DILocation(line: 220, column: 35, scope: !612)
!612 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 1)
!613 = !DILocation(line: 306, column: 41, scope: !614)
!614 = distinct !DILexicalBlock(scope: !208, file: !1, line: 306, column: 6)
!615 = !DILocation(line: 306, column: 21, scope: !614)
!616 = !DILocation(line: 306, column: 49, scope: !614)
!617 = !DILocation(line: 306, column: 54, scope: !614)
!618 = !DILocation(line: 306, column: 6, scope: !619)
!619 = !DILexicalBlockFile(scope: !614, file: !1, discriminator: 1)
!620 = !DILocation(line: 306, column: 6, scope: !614)
!621 = !DILocation(line: 306, column: 6, scope: !208)
!622 = !DILocation(line: 307, column: 22, scope: !623)
!623 = distinct !DILexicalBlock(scope: !614, file: !1, line: 306, column: 87)
!624 = !DILocation(line: 307, column: 25, scope: !623)
!625 = !DILocation(line: 307, column: 3, scope: !623)
!626 = !DILocation(line: 309, column: 3, scope: !623)
!627 = !DILocation(line: 311, column: 39, scope: !628)
!628 = distinct !DILexicalBlock(scope: !208, file: !1, line: 311, column: 6)
!629 = !DILocation(line: 311, column: 21, scope: !628)
!630 = !DILocation(line: 311, column: 47, scope: !628)
!631 = !DILocation(line: 311, column: 52, scope: !628)
!632 = !DILocation(line: 311, column: 6, scope: !633)
!633 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 1)
!634 = !DILocation(line: 311, column: 6, scope: !628)
!635 = !DILocation(line: 311, column: 6, scope: !208)
!636 = !DILocation(line: 312, column: 22, scope: !637)
!637 = distinct !DILexicalBlock(scope: !628, file: !1, line: 311, column: 83)
!638 = !DILocation(line: 312, column: 25, scope: !637)
!639 = !DILocation(line: 312, column: 3, scope: !637)
!640 = !DILocation(line: 314, column: 3, scope: !637)
!641 = !DILocation(line: 316, column: 39, scope: !642)
!642 = distinct !DILexicalBlock(scope: !208, file: !1, line: 316, column: 6)
!643 = !DILocation(line: 316, column: 21, scope: !642)
!644 = !DILocation(line: 316, column: 47, scope: !642)
!645 = !DILocation(line: 316, column: 52, scope: !642)
!646 = !DILocation(line: 316, column: 6, scope: !647)
!647 = !DILexicalBlockFile(scope: !642, file: !1, discriminator: 1)
!648 = !DILocation(line: 316, column: 6, scope: !642)
!649 = !DILocation(line: 316, column: 6, scope: !208)
!650 = !DILocation(line: 317, column: 22, scope: !651)
!651 = distinct !DILexicalBlock(scope: !642, file: !1, line: 316, column: 83)
!652 = !DILocation(line: 317, column: 25, scope: !651)
!653 = !DILocation(line: 317, column: 3, scope: !651)
!654 = !DILocation(line: 319, column: 3, scope: !651)
!655 = !DILocation(line: 321, column: 38, scope: !656)
!656 = distinct !DILexicalBlock(scope: !208, file: !1, line: 321, column: 6)
!657 = !DILocation(line: 321, column: 19, scope: !656)
!658 = !DILocation(line: 321, column: 46, scope: !656)
!659 = !DILocation(line: 321, column: 51, scope: !656)
!660 = !DILocation(line: 321, column: 6, scope: !661)
!661 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 1)
!662 = !DILocation(line: 321, column: 6, scope: !656)
!663 = !DILocation(line: 321, column: 6, scope: !208)
!664 = !DILocation(line: 322, column: 22, scope: !665)
!665 = distinct !DILexicalBlock(scope: !656, file: !1, line: 321, column: 84)
!666 = !DILocation(line: 322, column: 25, scope: !665)
!667 = !DILocation(line: 322, column: 3, scope: !665)
!668 = !DILocation(line: 324, column: 3, scope: !665)
!669 = !DILocation(line: 330, column: 6, scope: !670)
!670 = distinct !DILexicalBlock(scope: !208, file: !1, line: 330, column: 6)
!671 = !DILocation(line: 330, column: 15, scope: !670)
!672 = !DILocation(line: 330, column: 23, scope: !670)
!673 = !DILocation(line: 330, column: 49, scope: !674)
!674 = !DILexicalBlockFile(scope: !670, file: !1, discriminator: 1)
!675 = !DILocation(line: 330, column: 26, scope: !674)
!676 = !DILocation(line: 330, column: 56, scope: !674)
!677 = !DILocation(line: 330, column: 6, scope: !674)
!678 = !DILocation(line: 331, column: 22, scope: !679)
!679 = distinct !DILexicalBlock(scope: !670, file: !1, line: 330, column: 69)
!680 = !DILocation(line: 331, column: 25, scope: !679)
!681 = !DILocation(line: 331, column: 3, scope: !679)
!682 = !DILocation(line: 333, column: 3, scope: !679)
!683 = !DILocation(line: 330, column: 59, scope: !684)
!684 = !DILexicalBlockFile(scope: !670, file: !1, discriminator: 2)
!685 = !DILocation(line: 337, column: 21, scope: !686)
!686 = distinct !DILexicalBlock(scope: !208, file: !1, line: 337, column: 6)
!687 = !DILocation(line: 337, column: 27, scope: !686)
!688 = !DILocation(line: 337, column: 32, scope: !686)
!689 = !DILocation(line: 337, column: 6, scope: !686)
!690 = !DILocation(line: 337, column: 6, scope: !208)
!691 = !DILocation(line: 338, column: 22, scope: !692)
!692 = distinct !DILexicalBlock(scope: !686, file: !1, line: 337, column: 65)
!693 = !DILocation(line: 338, column: 25, scope: !692)
!694 = !DILocation(line: 338, column: 3, scope: !692)
!695 = !DILocation(line: 340, column: 3, scope: !692)
!696 = !DILocation(line: 343, column: 31, scope: !208)
!697 = !DILocation(line: 343, column: 34, scope: !208)
!698 = !DILocation(line: 343, column: 8, scope: !208)
!699 = !DILocation(line: 343, column: 6, scope: !208)
!700 = !DILocation(line: 344, column: 6, scope: !701)
!701 = distinct !DILexicalBlock(scope: !208, file: !1, line: 344, column: 6)
!702 = !DILocation(line: 344, column: 10, scope: !701)
!703 = !DILocation(line: 344, column: 6, scope: !208)
!704 = !DILocation(line: 345, column: 11, scope: !701)
!705 = !DILocation(line: 345, column: 3, scope: !701)
!706 = !DILocation(line: 347, column: 30, scope: !208)
!707 = !DILocation(line: 347, column: 2, scope: !208)
!708 = !DILocation(line: 347, column: 6, scope: !208)
!709 = !DILocation(line: 347, column: 28, scope: !208)
!710 = !DILocation(line: 348, column: 22, scope: !208)
!711 = !DILocation(line: 348, column: 26, scope: !208)
!712 = !DILocation(line: 348, column: 48, scope: !208)
!713 = !DILocation(line: 348, column: 2, scope: !208)
!714 = !DILocation(line: 348, column: 6, scope: !208)
!715 = !DILocation(line: 348, column: 20, scope: !208)
!716 = !DILocation(line: 350, column: 6, scope: !717)
!717 = distinct !DILexicalBlock(scope: !208, file: !1, line: 350, column: 6)
!718 = !DILocation(line: 350, column: 16, scope: !717)
!719 = !DILocation(line: 350, column: 6, scope: !208)
!720 = !DILocation(line: 351, column: 32, scope: !721)
!721 = distinct !DILexicalBlock(scope: !717, file: !1, line: 350, column: 21)
!722 = !DILocation(line: 351, column: 35, scope: !721)
!723 = !DILocation(line: 351, column: 52, scope: !721)
!724 = !DILocation(line: 351, column: 45, scope: !721)
!725 = !DILocation(line: 351, column: 9, scope: !726)
!726 = !DILexicalBlockFile(scope: !721, file: !1, discriminator: 1)
!727 = !DILocation(line: 351, column: 7, scope: !721)
!728 = !DILocation(line: 352, column: 7, scope: !729)
!729 = distinct !DILexicalBlock(scope: !721, file: !1, line: 352, column: 7)
!730 = !DILocation(line: 352, column: 11, scope: !729)
!731 = !DILocation(line: 352, column: 7, scope: !721)
!732 = !DILocation(line: 353, column: 12, scope: !729)
!733 = !DILocation(line: 353, column: 4, scope: !729)
!734 = !DILocation(line: 354, column: 39, scope: !721)
!735 = !DILocation(line: 354, column: 32, scope: !721)
!736 = !DILocation(line: 354, column: 3, scope: !721)
!737 = !DILocation(line: 354, column: 7, scope: !721)
!738 = !DILocation(line: 354, column: 29, scope: !721)
!739 = !DILocation(line: 355, column: 2, scope: !721)
!740 = !DILocation(line: 357, column: 2, scope: !208)
!741 = !DILocation(line: 358, column: 1, scope: !208)
!742 = !DILocalVariable(name: "a", arg: 1, scope: !216, file: !1, line: 361, type: !4)
!743 = !DILocation(line: 361, column: 45, scope: !216)
!744 = !DILocalVariable(name: "buff", arg: 2, scope: !216, file: !1, line: 361, type: !43)
!745 = !DILocation(line: 361, column: 60, scope: !216)
!746 = !DILocalVariable(name: "s", arg: 3, scope: !216, file: !1, line: 361, type: !45)
!747 = !DILocation(line: 361, column: 73, scope: !216)
!748 = !DILocalVariable(name: "ar", scope: !216, file: !1, line: 363, type: !191)
!749 = !DILocation(line: 363, column: 15, scope: !216)
!750 = !DILocalVariable(name: "ret", scope: !216, file: !1, line: 364, type: !23)
!751 = !DILocation(line: 364, column: 6, scope: !216)
!752 = !DILocation(line: 366, column: 22, scope: !216)
!753 = !DILocation(line: 366, column: 25, scope: !216)
!754 = !DILocation(line: 366, column: 7, scope: !216)
!755 = !DILocation(line: 366, column: 5, scope: !216)
!756 = !DILocation(line: 367, column: 6, scope: !757)
!757 = distinct !DILexicalBlock(scope: !216, file: !1, line: 367, column: 6)
!758 = !DILocation(line: 367, column: 10, scope: !757)
!759 = !DILocation(line: 367, column: 14, scope: !757)
!760 = !DILocation(line: 367, column: 8, scope: !757)
!761 = !DILocation(line: 367, column: 6, scope: !216)
!762 = !DILocation(line: 368, column: 15, scope: !757)
!763 = !DILocation(line: 368, column: 19, scope: !757)
!764 = !DILocation(line: 368, column: 5, scope: !757)
!765 = !DILocation(line: 368, column: 3, scope: !757)
!766 = !DILocation(line: 370, column: 6, scope: !767)
!767 = distinct !DILexicalBlock(scope: !216, file: !1, line: 370, column: 6)
!768 = !DILocation(line: 370, column: 10, scope: !767)
!769 = !DILocation(line: 370, column: 20, scope: !767)
!770 = !DILocation(line: 370, column: 6, scope: !216)
!771 = !DILocation(line: 371, column: 7, scope: !772)
!772 = distinct !DILexicalBlock(scope: !773, file: !1, line: 371, column: 7)
!773 = distinct !DILexicalBlock(scope: !767, file: !1, line: 370, column: 25)
!774 = !DILocation(line: 371, column: 11, scope: !772)
!775 = !DILocation(line: 371, column: 22, scope: !772)
!776 = !DILocation(line: 371, column: 7, scope: !773)
!777 = !DILocation(line: 372, column: 23, scope: !778)
!778 = distinct !DILexicalBlock(scope: !772, file: !1, line: 371, column: 27)
!779 = !DILocation(line: 372, column: 26, scope: !778)
!780 = !DILocation(line: 372, column: 4, scope: !778)
!781 = !DILocation(line: 374, column: 4, scope: !778)
!782 = !DILocation(line: 377, column: 31, scope: !773)
!783 = !DILocation(line: 377, column: 24, scope: !773)
!784 = !DILocation(line: 377, column: 3, scope: !773)
!785 = !DILocation(line: 377, column: 7, scope: !773)
!786 = !DILocation(line: 377, column: 14, scope: !773)
!787 = !DILocation(line: 378, column: 7, scope: !788)
!788 = distinct !DILexicalBlock(scope: !773, file: !1, line: 378, column: 7)
!789 = !DILocation(line: 378, column: 11, scope: !788)
!790 = !DILocation(line: 378, column: 18, scope: !788)
!791 = !DILocation(line: 378, column: 7, scope: !773)
!792 = !DILocation(line: 379, column: 23, scope: !793)
!793 = distinct !DILexicalBlock(scope: !788, file: !1, line: 378, column: 27)
!794 = !DILocation(line: 379, column: 26, scope: !793)
!795 = !DILocation(line: 379, column: 4, scope: !793)
!796 = !DILocation(line: 381, column: 4, scope: !793)
!797 = !DILocation(line: 383, column: 11, scope: !773)
!798 = !DILocation(line: 383, column: 15, scope: !773)
!799 = !DILocation(line: 383, column: 23, scope: !773)
!800 = !DILocation(line: 383, column: 29, scope: !773)
!801 = !DILocation(line: 383, column: 3, scope: !773)
!802 = !DILocation(line: 384, column: 3, scope: !773)
!803 = !DILocation(line: 384, column: 7, scope: !773)
!804 = !DILocation(line: 384, column: 18, scope: !773)
!805 = !DILocation(line: 385, column: 2, scope: !773)
!806 = !DILocation(line: 387, column: 31, scope: !216)
!807 = !DILocation(line: 387, column: 34, scope: !216)
!808 = !DILocation(line: 387, column: 40, scope: !216)
!809 = !DILocation(line: 387, column: 8, scope: !216)
!810 = !DILocation(line: 387, column: 6, scope: !216)
!811 = !DILocation(line: 388, column: 6, scope: !812)
!812 = distinct !DILexicalBlock(scope: !216, file: !1, line: 388, column: 6)
!813 = !DILocation(line: 388, column: 10, scope: !812)
!814 = !DILocation(line: 388, column: 6, scope: !216)
!815 = !DILocation(line: 389, column: 11, scope: !812)
!816 = !DILocation(line: 389, column: 10, scope: !812)
!817 = !DILocation(line: 389, column: 3, scope: !812)
!818 = !DILocation(line: 391, column: 31, scope: !216)
!819 = !DILocation(line: 391, column: 2, scope: !216)
!820 = !DILocation(line: 391, column: 6, scope: !216)
!821 = !DILocation(line: 391, column: 28, scope: !216)
!822 = !DILocation(line: 392, column: 10, scope: !216)
!823 = !DILocation(line: 392, column: 2, scope: !216)
!824 = !DILocation(line: 393, column: 1, scope: !216)
!825 = !DILocalVariable(name: "a", arg: 1, scope: !217, file: !1, line: 416, type: !4)
!826 = !DILocation(line: 416, column: 46, scope: !217)
!827 = !DILocalVariable(name: "ar", scope: !217, file: !1, line: 418, type: !191)
!828 = !DILocation(line: 418, column: 15, scope: !217)
!829 = !DILocalVariable(name: "ret", scope: !217, file: !1, line: 419, type: !23)
!830 = !DILocation(line: 419, column: 6, scope: !217)
!831 = !DILocation(line: 425, column: 22, scope: !217)
!832 = !DILocation(line: 425, column: 25, scope: !217)
!833 = !DILocation(line: 425, column: 7, scope: !217)
!834 = !DILocation(line: 425, column: 5, scope: !217)
!835 = !DILocation(line: 426, column: 7, scope: !836)
!836 = distinct !DILexicalBlock(scope: !217, file: !1, line: 426, column: 6)
!837 = !DILocation(line: 426, column: 11, scope: !836)
!838 = !DILocation(line: 426, column: 6, scope: !217)
!839 = !DILocation(line: 427, column: 3, scope: !840)
!840 = distinct !DILexicalBlock(scope: !836, file: !1, line: 426, column: 32)
!841 = !DILocation(line: 427, column: 7, scope: !840)
!842 = !DILocation(line: 427, column: 27, scope: !840)
!843 = !DILocation(line: 428, column: 32, scope: !840)
!844 = !DILocation(line: 428, column: 9, scope: !840)
!845 = !DILocation(line: 428, column: 7, scope: !840)
!846 = !DILocation(line: 429, column: 11, scope: !840)
!847 = !DILocation(line: 429, column: 3, scope: !840)
!848 = !DILocation(line: 432, column: 2, scope: !217)
!849 = !DILocation(line: 433, column: 1, scope: !217)
!850 = !DILocalVariable(name: "a", arg: 1, scope: !218, file: !1, line: 396, type: !4)
!851 = !DILocation(line: 396, column: 45, scope: !218)
!852 = !DILocalVariable(name: "ar", scope: !218, file: !1, line: 398, type: !191)
!853 = !DILocation(line: 398, column: 15, scope: !218)
!854 = !DILocation(line: 400, column: 22, scope: !218)
!855 = !DILocation(line: 400, column: 25, scope: !218)
!856 = !DILocation(line: 400, column: 7, scope: !218)
!857 = !DILocation(line: 400, column: 5, scope: !218)
!858 = !DILocation(line: 402, column: 6, scope: !859)
!859 = distinct !DILexicalBlock(scope: !218, file: !1, line: 402, column: 6)
!860 = !DILocation(line: 402, column: 9, scope: !859)
!861 = !DILocation(line: 402, column: 6, scope: !218)
!862 = !DILocation(line: 403, column: 3, scope: !859)
!863 = !DILocation(line: 405, column: 6, scope: !864)
!864 = distinct !DILexicalBlock(scope: !218, file: !1, line: 405, column: 6)
!865 = !DILocation(line: 405, column: 10, scope: !864)
!866 = !DILocation(line: 405, column: 21, scope: !864)
!867 = !DILocation(line: 405, column: 6, scope: !218)
!868 = !DILocation(line: 406, column: 8, scope: !869)
!869 = distinct !DILexicalBlock(scope: !864, file: !1, line: 405, column: 26)
!870 = !DILocation(line: 406, column: 12, scope: !869)
!871 = !DILocation(line: 406, column: 3, scope: !869)
!872 = !DILocation(line: 407, column: 3, scope: !869)
!873 = !DILocation(line: 407, column: 7, scope: !869)
!874 = !DILocation(line: 407, column: 14, scope: !869)
!875 = !DILocation(line: 408, column: 2, scope: !869)
!876 = !DILocation(line: 410, column: 7, scope: !218)
!877 = !DILocation(line: 410, column: 2, scope: !218)
!878 = !DILocation(line: 411, column: 2, scope: !218)
!879 = !DILocation(line: 411, column: 5, scope: !218)
!880 = !DILocation(line: 411, column: 17, scope: !218)
!881 = !DILocation(line: 412, column: 2, scope: !218)
!882 = !DILocation(line: 413, column: 1, scope: !218)
!883 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 436, type: !4)
!884 = !DILocation(line: 436, column: 53, scope: !219)
!885 = !DILocalVariable(name: "ar", scope: !219, file: !1, line: 438, type: !191)
!886 = !DILocation(line: 438, column: 15, scope: !219)
!887 = !DILocalVariable(name: "ret", scope: !219, file: !1, line: 439, type: !23)
!888 = !DILocation(line: 439, column: 6, scope: !219)
!889 = !DILocation(line: 441, column: 22, scope: !219)
!890 = !DILocation(line: 441, column: 25, scope: !219)
!891 = !DILocation(line: 441, column: 7, scope: !219)
!892 = !DILocation(line: 441, column: 5, scope: !219)
!893 = !DILocation(line: 443, column: 6, scope: !894)
!894 = distinct !DILexicalBlock(scope: !219, file: !1, line: 443, column: 6)
!895 = !DILocation(line: 443, column: 10, scope: !894)
!896 = !DILocation(line: 443, column: 32, scope: !894)
!897 = !DILocation(line: 443, column: 6, scope: !219)
!898 = !DILocation(line: 444, column: 22, scope: !899)
!899 = distinct !DILexicalBlock(scope: !894, file: !1, line: 443, column: 38)
!900 = !DILocation(line: 444, column: 25, scope: !899)
!901 = !DILocation(line: 444, column: 3, scope: !899)
!902 = !DILocation(line: 446, column: 3, scope: !899)
!903 = !DILocation(line: 449, column: 6, scope: !904)
!904 = distinct !DILexicalBlock(scope: !219, file: !1, line: 449, column: 6)
!905 = !DILocation(line: 449, column: 10, scope: !904)
!906 = !DILocation(line: 449, column: 24, scope: !904)
!907 = !DILocation(line: 449, column: 6, scope: !219)
!908 = !DILocation(line: 450, column: 3, scope: !909)
!909 = distinct !DILexicalBlock(scope: !904, file: !1, line: 449, column: 30)
!910 = !DILocation(line: 453, column: 6, scope: !911)
!911 = distinct !DILexicalBlock(scope: !219, file: !1, line: 453, column: 6)
!912 = !DILocation(line: 453, column: 10, scope: !911)
!913 = !DILocation(line: 453, column: 24, scope: !911)
!914 = !DILocation(line: 453, column: 6, scope: !219)
!915 = !DILocation(line: 454, column: 22, scope: !916)
!916 = distinct !DILexicalBlock(scope: !911, file: !1, line: 453, column: 30)
!917 = !DILocation(line: 454, column: 25, scope: !916)
!918 = !DILocation(line: 456, column: 18, scope: !916)
!919 = !DILocation(line: 456, column: 22, scope: !916)
!920 = !DILocation(line: 454, column: 3, scope: !916)
!921 = !DILocation(line: 457, column: 3, scope: !916)
!922 = !DILocation(line: 460, column: 31, scope: !219)
!923 = !DILocation(line: 460, column: 8, scope: !219)
!924 = !DILocation(line: 460, column: 6, scope: !219)
!925 = !DILocation(line: 461, column: 10, scope: !219)
!926 = !DILocation(line: 461, column: 2, scope: !219)
!927 = !DILocation(line: 462, column: 1, scope: !219)
!928 = !DILocalVariable(name: "path", arg: 1, scope: !209, file: !1, line: 545, type: !80)
!929 = !DILocation(line: 545, column: 25, scope: !209)
!930 = !DILocalVariable(name: "endp", scope: !209, file: !1, line: 547, type: !80)
!931 = !DILocation(line: 547, column: 14, scope: !209)
!932 = !DILocalVariable(name: "startp", scope: !209, file: !1, line: 547, type: !80)
!933 = !DILocation(line: 547, column: 21, scope: !209)
!934 = !DILocation(line: 549, column: 9, scope: !209)
!935 = !DILocation(line: 549, column: 23, scope: !209)
!936 = !DILocation(line: 549, column: 16, scope: !209)
!937 = !DILocation(line: 549, column: 14, scope: !209)
!938 = !DILocation(line: 549, column: 29, scope: !209)
!939 = !DILocation(line: 549, column: 7, scope: !209)
!940 = !DILocation(line: 554, column: 7, scope: !941)
!941 = distinct !DILexicalBlock(scope: !209, file: !1, line: 554, column: 6)
!942 = !DILocation(line: 554, column: 6, scope: !941)
!943 = !DILocation(line: 554, column: 12, scope: !941)
!944 = !DILocation(line: 554, column: 6, scope: !209)
!945 = !DILocation(line: 555, column: 3, scope: !941)
!946 = !DILocation(line: 558, column: 11, scope: !209)
!947 = !DILocation(line: 558, column: 9, scope: !209)
!948 = !DILocation(line: 559, column: 2, scope: !209)
!949 = !DILocation(line: 559, column: 9, scope: !950)
!950 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 1)
!951 = !DILocation(line: 559, column: 18, scope: !950)
!952 = !DILocation(line: 559, column: 16, scope: !950)
!953 = !DILocation(line: 559, column: 23, scope: !950)
!954 = !DILocation(line: 559, column: 28, scope: !955)
!955 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 2)
!956 = !DILocation(line: 559, column: 35, scope: !955)
!957 = !DILocation(line: 559, column: 26, scope: !955)
!958 = !DILocation(line: 559, column: 40, scope: !955)
!959 = !DILocation(line: 559, column: 2, scope: !960)
!960 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 3)
!961 = !DILocation(line: 560, column: 9, scope: !209)
!962 = !DILocation(line: 559, column: 2, scope: !963)
!963 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 4)
!964 = !DILocation(line: 562, column: 10, scope: !209)
!965 = !DILocation(line: 562, column: 2, scope: !209)
!966 = !DILocation(line: 563, column: 1, scope: !209)
!967 = !DILocalVariable(name: "v", arg: 1, scope: !212, file: !1, line: 509, type: !52)
!968 = !DILocation(line: 509, column: 24, scope: !212)
!969 = !DILocalVariable(name: "p", arg: 2, scope: !212, file: !1, line: 509, type: !95)
!970 = !DILocation(line: 509, column: 33, scope: !212)
!971 = !DILocalVariable(name: "s", arg: 3, scope: !212, file: !1, line: 509, type: !23)
!972 = !DILocation(line: 509, column: 40, scope: !212)
!973 = !DILocalVariable(name: "len", scope: !212, file: !1, line: 511, type: !23)
!974 = !DILocation(line: 511, column: 6, scope: !212)
!975 = !DILocalVariable(name: "h", scope: !212, file: !1, line: 512, type: !95)
!976 = !DILocation(line: 512, column: 8, scope: !212)
!977 = !DILocation(line: 514, column: 8, scope: !212)
!978 = !DILocation(line: 514, column: 6, scope: !212)
!979 = !DILocation(line: 515, column: 6, scope: !212)
!980 = !DILocation(line: 515, column: 4, scope: !212)
!981 = !DILocation(line: 518, column: 6, scope: !982)
!982 = distinct !DILexicalBlock(scope: !212, file: !1, line: 518, column: 6)
!983 = !DILocation(line: 518, column: 8, scope: !982)
!984 = !DILocation(line: 518, column: 6, scope: !212)
!985 = !DILocation(line: 519, column: 3, scope: !986)
!986 = distinct !DILexicalBlock(scope: !982, file: !1, line: 518, column: 13)
!987 = !DILocation(line: 519, column: 13, scope: !988)
!988 = !DILexicalBlockFile(scope: !986, file: !1, discriminator: 1)
!989 = !DILocation(line: 519, column: 16, scope: !988)
!990 = !DILocation(line: 519, column: 3, scope: !988)
!991 = !DILocation(line: 520, column: 6, scope: !986)
!992 = !DILocation(line: 520, column: 9, scope: !986)
!993 = !DILocation(line: 519, column: 3, scope: !994)
!994 = !DILexicalBlockFile(scope: !986, file: !1, discriminator: 2)
!995 = !DILocation(line: 521, column: 3, scope: !986)
!996 = !DILocation(line: 524, column: 7, scope: !212)
!997 = !DILocation(line: 524, column: 4, scope: !212)
!998 = !DILocation(line: 525, column: 2, scope: !212)
!999 = !DILocation(line: 526, column: 24, scope: !1000)
!1000 = distinct !DILexicalBlock(scope: !212, file: !1, line: 525, column: 5)
!1001 = !DILocation(line: 526, column: 26, scope: !1000)
!1002 = !DILocation(line: 526, column: 21, scope: !1000)
!1003 = !DILocation(line: 526, column: 10, scope: !1000)
!1004 = !DILocation(line: 526, column: 4, scope: !1000)
!1005 = !DILocation(line: 526, column: 8, scope: !1000)
!1006 = !DILocation(line: 527, column: 5, scope: !1000)
!1007 = !DILocation(line: 528, column: 2, scope: !1000)
!1008 = !DILocation(line: 528, column: 11, scope: !1009)
!1009 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 1)
!1010 = !DILocation(line: 528, column: 15, scope: !1009)
!1011 = !DILocation(line: 528, column: 19, scope: !1009)
!1012 = !DILocation(line: 528, column: 22, scope: !1013)
!1013 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 2)
!1014 = !DILocation(line: 528, column: 24, scope: !1013)
!1015 = !DILocation(line: 528, column: 2, scope: !1016)
!1016 = !DILexicalBlockFile(scope: !1000, file: !1, discriminator: 3)
!1017 = !DILocation(line: 530, column: 6, scope: !1018)
!1018 = distinct !DILexicalBlock(scope: !212, file: !1, line: 530, column: 6)
!1019 = !DILocation(line: 530, column: 8, scope: !1018)
!1020 = !DILocation(line: 530, column: 6, scope: !212)
!1021 = !DILocation(line: 531, column: 11, scope: !1022)
!1022 = distinct !DILexicalBlock(scope: !1018, file: !1, line: 530, column: 14)
!1023 = !DILocation(line: 531, column: 14, scope: !1022)
!1024 = !DILocation(line: 531, column: 17, scope: !1022)
!1025 = !DILocation(line: 531, column: 23, scope: !1022)
!1026 = !DILocation(line: 531, column: 21, scope: !1022)
!1027 = !DILocation(line: 531, column: 3, scope: !1022)
!1028 = !DILocation(line: 532, column: 7, scope: !1022)
!1029 = !DILocation(line: 532, column: 11, scope: !1022)
!1030 = !DILocation(line: 532, column: 9, scope: !1022)
!1031 = !DILocation(line: 532, column: 17, scope: !1022)
!1032 = !DILocation(line: 532, column: 15, scope: !1022)
!1033 = !DILocation(line: 532, column: 5, scope: !1022)
!1034 = !DILocation(line: 533, column: 3, scope: !1022)
!1035 = !DILocation(line: 533, column: 11, scope: !1036)
!1036 = !DILexicalBlockFile(scope: !1022, file: !1, discriminator: 1)
!1037 = !DILocation(line: 533, column: 14, scope: !1036)
!1038 = !DILocation(line: 533, column: 3, scope: !1036)
!1039 = !DILocation(line: 534, column: 6, scope: !1022)
!1040 = !DILocation(line: 534, column: 9, scope: !1022)
!1041 = !DILocation(line: 533, column: 3, scope: !1042)
!1042 = !DILexicalBlockFile(scope: !1022, file: !1, discriminator: 2)
!1043 = !DILocation(line: 535, column: 3, scope: !1022)
!1044 = !DILocation(line: 538, column: 2, scope: !212)
!1045 = !DILocation(line: 538, column: 12, scope: !1009)
!1046 = !DILocation(line: 538, column: 15, scope: !1009)
!1047 = !DILocation(line: 538, column: 2, scope: !1009)
!1048 = !DILocation(line: 539, column: 5, scope: !212)
!1049 = !DILocation(line: 539, column: 8, scope: !212)
!1050 = !DILocation(line: 538, column: 2, scope: !1013)
!1051 = !DILocation(line: 541, column: 2, scope: !212)
!1052 = !DILocation(line: 542, column: 1, scope: !212)
!1053 = !DILocalVariable(name: "v", arg: 1, scope: !215, file: !1, line: 470, type: !52)
!1054 = !DILocation(line: 470, column: 22, scope: !215)
!1055 = !DILocalVariable(name: "p", arg: 2, scope: !215, file: !1, line: 470, type: !95)
!1056 = !DILocation(line: 470, column: 31, scope: !215)
!1057 = !DILocalVariable(name: "s", arg: 3, scope: !215, file: !1, line: 470, type: !23)
!1058 = !DILocation(line: 470, column: 38, scope: !215)
!1059 = !DILocalVariable(name: "len", scope: !215, file: !1, line: 472, type: !23)
!1060 = !DILocation(line: 472, column: 6, scope: !215)
!1061 = !DILocalVariable(name: "h", scope: !215, file: !1, line: 473, type: !95)
!1062 = !DILocation(line: 473, column: 8, scope: !215)
!1063 = !DILocation(line: 475, column: 8, scope: !215)
!1064 = !DILocation(line: 475, column: 6, scope: !215)
!1065 = !DILocation(line: 476, column: 6, scope: !215)
!1066 = !DILocation(line: 476, column: 4, scope: !215)
!1067 = !DILocation(line: 479, column: 6, scope: !1068)
!1068 = distinct !DILexicalBlock(scope: !215, file: !1, line: 479, column: 6)
!1069 = !DILocation(line: 479, column: 8, scope: !1068)
!1070 = !DILocation(line: 479, column: 6, scope: !215)
!1071 = !DILocation(line: 480, column: 3, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 479, column: 13)
!1073 = !DILocation(line: 480, column: 13, scope: !1074)
!1074 = !DILexicalBlockFile(scope: !1072, file: !1, discriminator: 1)
!1075 = !DILocation(line: 480, column: 16, scope: !1074)
!1076 = !DILocation(line: 480, column: 3, scope: !1074)
!1077 = !DILocation(line: 481, column: 6, scope: !1072)
!1078 = !DILocation(line: 481, column: 9, scope: !1072)
!1079 = !DILocation(line: 480, column: 3, scope: !1080)
!1080 = !DILexicalBlockFile(scope: !1072, file: !1, discriminator: 2)
!1081 = !DILocation(line: 482, column: 3, scope: !1072)
!1082 = !DILocation(line: 485, column: 7, scope: !215)
!1083 = !DILocation(line: 485, column: 4, scope: !215)
!1084 = !DILocation(line: 486, column: 2, scope: !215)
!1085 = !DILocation(line: 487, column: 24, scope: !1086)
!1086 = distinct !DILexicalBlock(scope: !215, file: !1, line: 486, column: 5)
!1087 = !DILocation(line: 487, column: 26, scope: !1086)
!1088 = !DILocation(line: 487, column: 21, scope: !1086)
!1089 = !DILocation(line: 487, column: 10, scope: !1086)
!1090 = !DILocation(line: 487, column: 4, scope: !1086)
!1091 = !DILocation(line: 487, column: 8, scope: !1086)
!1092 = !DILocation(line: 488, column: 5, scope: !1086)
!1093 = !DILocation(line: 489, column: 2, scope: !1086)
!1094 = !DILocation(line: 489, column: 11, scope: !1095)
!1095 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!1096 = !DILocation(line: 489, column: 15, scope: !1095)
!1097 = !DILocation(line: 489, column: 19, scope: !1095)
!1098 = !DILocation(line: 489, column: 22, scope: !1099)
!1099 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 2)
!1100 = !DILocation(line: 489, column: 24, scope: !1099)
!1101 = !DILocation(line: 489, column: 2, scope: !1102)
!1102 = !DILexicalBlockFile(scope: !1086, file: !1, discriminator: 3)
!1103 = !DILocation(line: 491, column: 6, scope: !1104)
!1104 = distinct !DILexicalBlock(scope: !215, file: !1, line: 491, column: 6)
!1105 = !DILocation(line: 491, column: 8, scope: !1104)
!1106 = !DILocation(line: 491, column: 6, scope: !215)
!1107 = !DILocation(line: 492, column: 11, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !1104, file: !1, line: 491, column: 14)
!1109 = !DILocation(line: 492, column: 14, scope: !1108)
!1110 = !DILocation(line: 492, column: 17, scope: !1108)
!1111 = !DILocation(line: 492, column: 23, scope: !1108)
!1112 = !DILocation(line: 492, column: 21, scope: !1108)
!1113 = !DILocation(line: 492, column: 3, scope: !1108)
!1114 = !DILocation(line: 493, column: 7, scope: !1108)
!1115 = !DILocation(line: 493, column: 11, scope: !1108)
!1116 = !DILocation(line: 493, column: 9, scope: !1108)
!1117 = !DILocation(line: 493, column: 17, scope: !1108)
!1118 = !DILocation(line: 493, column: 15, scope: !1108)
!1119 = !DILocation(line: 493, column: 5, scope: !1108)
!1120 = !DILocation(line: 494, column: 3, scope: !1108)
!1121 = !DILocation(line: 494, column: 11, scope: !1122)
!1122 = !DILexicalBlockFile(scope: !1108, file: !1, discriminator: 1)
!1123 = !DILocation(line: 494, column: 14, scope: !1122)
!1124 = !DILocation(line: 494, column: 3, scope: !1122)
!1125 = !DILocation(line: 495, column: 6, scope: !1108)
!1126 = !DILocation(line: 495, column: 9, scope: !1108)
!1127 = !DILocation(line: 494, column: 3, scope: !1128)
!1128 = !DILexicalBlockFile(scope: !1108, file: !1, discriminator: 2)
!1129 = !DILocation(line: 496, column: 3, scope: !1108)
!1130 = !DILocation(line: 499, column: 2, scope: !215)
!1131 = !DILocation(line: 499, column: 12, scope: !1095)
!1132 = !DILocation(line: 499, column: 15, scope: !1095)
!1133 = !DILocation(line: 499, column: 2, scope: !1095)
!1134 = !DILocation(line: 500, column: 5, scope: !215)
!1135 = !DILocation(line: 500, column: 8, scope: !215)
!1136 = !DILocation(line: 499, column: 2, scope: !1099)
!1137 = !DILocation(line: 502, column: 2, scope: !215)
!1138 = !DILocation(line: 503, column: 1, scope: !215)
