; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_cpio_newc.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.cpio = type { i64, i32, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }

@.str = private unnamed_addr constant [35 x i8] c"archive_write_set_format_cpio_newc\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate cpio data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"cpio\00", align 1
@.str.3 = private unnamed_addr constant [16 x i8] c"SVR4 cpio nocrc\00", align 1
@.str.4 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.5 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"Filetype required\00", align 1
@.str.7 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.8 = private unnamed_addr constant [18 x i8] c"Pathname required\00", align 1
@.str.9 = private unnamed_addr constant [14 x i8] c"Size required\00", align 1
@.str.10 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.11 = private unnamed_addr constant [29 x i8] c"large inode number truncated\00", align 1
@.str.12 = private unnamed_addr constant [34 x i8] c"Can't allocate memory for Likname\00", align 1
@.str.13 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.14 = private unnamed_addr constant [35 x i8] c"File is too large for this format.\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] zeroinitializer, align 1
@.str.16 = private unnamed_addr constant [17 x i8] c"0123456789abcdef\00", align 1
@.str.17 = private unnamed_addr constant [11 x i8] c"TRAILER!!!\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_cpio_newc(%struct.archive* %_a) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !225, metadata !226), !dbg !227
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !228, metadata !226), !dbg !229
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !230
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !231
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !229
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !232, metadata !226), !dbg !233
  br label %do.body, !dbg !234

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !235, metadata !226), !dbg !237
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !238
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str, i32 0, i32 0)), !dbg !238
  store i32 %call, i32* %magic_test, align 4, !dbg !238
  %3 = load i32, i32* %magic_test, align 4, !dbg !238
  %cmp = icmp eq i32 %3, -30, !dbg !238
  br i1 %cmp, label %if.then, label %if.end, !dbg !238

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !240
  br label %return, !dbg !240

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !243

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !245
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !247
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !247
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !248
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !249

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !250
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !251
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !251
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !252
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !253
  br label %if.end5, !dbg !253

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 40) #7, !dbg !254
  %9 = bitcast i8* %call6 to %struct.cpio*, !dbg !255
  store %struct.cpio* %9, %struct.cpio** %cpio, align 8, !dbg !256
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !257
  %cmp7 = icmp eq %struct.cpio* %10, null, !dbg !259
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !260

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !261
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !263
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !264
  store i32 -30, i32* %retval, align 4, !dbg !265
  br label %return, !dbg !265

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !266
  %13 = bitcast %struct.cpio* %12 to i8*, !dbg !266
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !267
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 14, !dbg !268
  store i8* %13, i8** %format_data, align 8, !dbg !269
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !270
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 15, !dbg !271
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !272
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !273
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 17, !dbg !274
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_newc_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !275
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !276
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 19, !dbg !277
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_newc_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !278
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !279
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 20, !dbg !280
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_newc_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !281
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !282
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 18, !dbg !283
  store i32 (%struct.archive_write*)* @archive_write_newc_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !284
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !285
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 21, !dbg !286
  store i32 (%struct.archive_write*)* @archive_write_newc_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !287
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !288
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 22, !dbg !289
  store i32 (%struct.archive_write*)* @archive_write_newc_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !290
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !291
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 0, !dbg !292
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !293
  store i32 65540, i32* %archive_format, align 8, !dbg !294
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !295
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !296
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !297
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !298
  store i32 0, i32* %retval, align 4, !dbg !299
  br label %return, !dbg !299

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !300
  ret i32 %24, !dbg !300
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_newc_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !301, metadata !226), !dbg !302
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !303, metadata !226), !dbg !304
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !305, metadata !226), !dbg !306
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !307, metadata !226), !dbg !308
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !309
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !310
  %1 = load i8*, i8** %format_data, align 8, !dbg !310
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !311
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !308
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !312, metadata !226), !dbg !313
  store i32 -25, i32* %ret, align 4, !dbg !313
  %3 = load i8*, i8** %key.addr, align 8, !dbg !314
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.4, i32 0, i32 0)) #8, !dbg !316
  %cmp = icmp eq i32 %call, 0, !dbg !317
  br i1 %cmp, label %if.then, label %if.end13, !dbg !318

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !319
  %cmp1 = icmp eq i8* %4, null, !dbg !322
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !323

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !324
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !324
  %6 = load i8, i8* %arrayidx, align 1, !dbg !324
  %conv = sext i8 %6 to i32, !dbg !324
  %cmp2 = icmp eq i32 %conv, 0, !dbg !326
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !327

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !328
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !329
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !330
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !331
  %9 = load i8*, i8** %format_name, align 8, !dbg !331
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.5, i32 0, i32 0), i8* %9), !dbg !332
  br label %if.end12, !dbg !332

if.else:                                          ; preds = %lor.lhs.false
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !333
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !335
  %11 = load i8*, i8** %val.addr, align 8, !dbg !336
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive5, i8* %11, i32 0), !dbg !337
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !338
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 2, !dbg !339
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !340
  %13 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !341
  %opt_sconv7 = getelementptr inbounds %struct.cpio, %struct.cpio* %13, i32 0, i32 2, !dbg !343
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !343
  %cmp8 = icmp ne %struct.archive_string_conv* %14, null, !dbg !344
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !345

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !346
  br label %if.end, !dbg !347

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !348
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %15 = load i32, i32* %ret, align 4, !dbg !349
  store i32 %15, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !351
  br label %return, !dbg !351

return:                                           ; preds = %if.end13, %if.end12
  %16 = load i32, i32* %retval, align 4, !dbg !352
  ret i32 %16, !dbg !352
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_newc_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %path = alloca i8*, align 8
  %len = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !353, metadata !226), !dbg !354
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !355, metadata !226), !dbg !356
  call void @llvm.dbg.declare(metadata i8** %path, metadata !357, metadata !226), !dbg !358
  call void @llvm.dbg.declare(metadata i64* %len, metadata !359, metadata !226), !dbg !360
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !361
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %0), !dbg !363
  %cmp = icmp eq i32 %call, 0, !dbg !364
  br i1 %cmp, label %if.then, label %if.end, !dbg !365

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !366
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %1, i32 0, i32 0, !dbg !368
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0)), !dbg !369
  store i32 -25, i32* %retval, align 4, !dbg !370
  br label %return, !dbg !370

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !371
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !373
  %call2 = call %struct.archive_string_conv* @get_sconv(%struct.archive_write* %3), !dbg !374
  %call3 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %2, i8** %path, i64* %len, %struct.archive_string_conv* %call2), !dbg !375
  %cmp4 = icmp ne i32 %call3, 0, !dbg !377
  br i1 %cmp4, label %land.lhs.true, label %if.end9, !dbg !378

land.lhs.true:                                    ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !379
  %4 = load i32, i32* %call5, align 4, !dbg !379
  %cmp6 = icmp eq i32 %4, 12, !dbg !381
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !382

if.then7:                                         ; preds = %land.lhs.true
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !384
  %archive8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !386
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive8, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !387
  store i32 -30, i32* %retval, align 4, !dbg !388
  br label %return, !dbg !388

if.end9:                                          ; preds = %land.lhs.true, %if.end
  %6 = load i64, i64* %len, align 8, !dbg !389
  %cmp10 = icmp eq i64 %6, 0, !dbg !391
  br i1 %cmp10, label %if.then15, label %lor.lhs.false, !dbg !392

lor.lhs.false:                                    ; preds = %if.end9
  %7 = load i8*, i8** %path, align 8, !dbg !393
  %cmp11 = icmp eq i8* %7, null, !dbg !395
  br i1 %cmp11, label %if.then15, label %lor.lhs.false12, !dbg !396

lor.lhs.false12:                                  ; preds = %lor.lhs.false
  %8 = load i8*, i8** %path, align 8, !dbg !397
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 0, !dbg !397
  %9 = load i8, i8* %arrayidx, align 1, !dbg !397
  %conv = sext i8 %9 to i32, !dbg !397
  %cmp13 = icmp eq i32 %conv, 0, !dbg !399
  br i1 %cmp13, label %if.then15, label %if.end17, !dbg !400

if.then15:                                        ; preds = %lor.lhs.false12, %lor.lhs.false, %if.end9
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !401
  %archive16 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !403
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.8, i32 0, i32 0)), !dbg !404
  store i32 -25, i32* %retval, align 4, !dbg !405
  br label %return, !dbg !405

if.end17:                                         ; preds = %lor.lhs.false12
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !406
  %call18 = call i8* @archive_entry_hardlink(%struct.archive_entry* %11), !dbg !408
  %cmp19 = icmp eq i8* %call18, null, !dbg !409
  br i1 %cmp19, label %land.lhs.true21, label %if.end29, !dbg !410

land.lhs.true21:                                  ; preds = %if.end17
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !411
  %call22 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %12), !dbg !413
  %tobool = icmp ne i32 %call22, 0, !dbg !413
  br i1 %tobool, label %lor.lhs.false23, label %if.then27, !dbg !414

lor.lhs.false23:                                  ; preds = %land.lhs.true21
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !415
  %call24 = call i64 @archive_entry_size(%struct.archive_entry* %13), !dbg !417
  %cmp25 = icmp slt i64 %call24, 0, !dbg !418
  br i1 %cmp25, label %if.then27, label %if.end29, !dbg !419

if.then27:                                        ; preds = %lor.lhs.false23, %land.lhs.true21
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !420
  %archive28 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 0, !dbg !422
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive28, i32 -1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0)), !dbg !423
  store i32 -25, i32* %retval, align 4, !dbg !424
  br label %return, !dbg !424

if.end29:                                         ; preds = %lor.lhs.false23, %if.end17
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !425
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !426
  %call30 = call i32 @write_header(%struct.archive_write* %15, %struct.archive_entry* %16), !dbg !427
  store i32 %call30, i32* %retval, align 4, !dbg !428
  br label %return, !dbg !428

return:                                           ; preds = %if.end29, %if.then27, %if.then15, %if.then7, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !429
  ret i32 %17, !dbg !429
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_newc_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !218 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %cpio = alloca %struct.cpio*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !430, metadata !226), !dbg !431
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !432, metadata !226), !dbg !433
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !434, metadata !226), !dbg !435
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !436, metadata !226), !dbg !437
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !438, metadata !226), !dbg !439
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !440
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !441
  %1 = load i8*, i8** %format_data, align 8, !dbg !441
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !442
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !443
  %3 = load i64, i64* %s.addr, align 8, !dbg !444
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !446
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 0, !dbg !447
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !447
  %cmp = icmp ugt i64 %3, %5, !dbg !448
  br i1 %cmp, label %if.then, label %if.end, !dbg !449

if.then:                                          ; preds = %entry
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !450
  %entry_bytes_remaining1 = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 0, !dbg !451
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !451
  store i64 %7, i64* %s.addr, align 8, !dbg !452
  br label %if.end, !dbg !453

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !454
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !455
  %10 = load i64, i64* %s.addr, align 8, !dbg !456
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !457
  store i32 %call, i32* %ret, align 4, !dbg !458
  %11 = load i64, i64* %s.addr, align 8, !dbg !459
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !460
  %entry_bytes_remaining2 = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 0, !dbg !461
  %13 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !462
  %sub = sub i64 %13, %11, !dbg !462
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !462
  %14 = load i32, i32* %ret, align 4, !dbg !463
  %cmp3 = icmp sge i32 %14, 0, !dbg !465
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !466

if.then4:                                         ; preds = %if.end
  %15 = load i64, i64* %s.addr, align 8, !dbg !467
  store i64 %15, i64* %retval, align 8, !dbg !468
  br label %return, !dbg !468

if.else:                                          ; preds = %if.end
  %16 = load i32, i32* %ret, align 4, !dbg !469
  %conv = sext i32 %16 to i64, !dbg !470
  store i64 %conv, i64* %retval, align 8, !dbg !471
  br label %return, !dbg !471

return:                                           ; preds = %if.else, %if.then4
  %17 = load i64, i64* %retval, align 8, !dbg !472
  ret i64 %17, !dbg !472
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_newc_finish_entry(%struct.archive_write* %a) #0 !dbg !221 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !473, metadata !226), !dbg !474
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !475, metadata !226), !dbg !476
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !477
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !478
  %1 = load i8*, i8** %format_data, align 8, !dbg !478
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !479
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !480
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !481
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !482
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 0, !dbg !483
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !483
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !484
  %padding = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 1, !dbg !485
  %7 = load i32, i32* %padding, align 8, !dbg !485
  %conv = sext i32 %7 to i64, !dbg !484
  %add = add i64 %5, %conv, !dbg !486
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %3, i64 %add), !dbg !487
  ret i32 %call, !dbg !488
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_newc_close(%struct.archive_write* %a) #0 !dbg !219 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %er = alloca i32, align 4
  %trailer = alloca %struct.archive_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !489, metadata !226), !dbg !490
  call void @llvm.dbg.declare(metadata i32* %er, metadata !491, metadata !226), !dbg !492
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %trailer, metadata !493, metadata !226), !dbg !494
  %call = call %struct.archive_entry* @archive_entry_new(), !dbg !495
  store %struct.archive_entry* %call, %struct.archive_entry** %trailer, align 8, !dbg !496
  %0 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !497
  call void @archive_entry_set_nlink(%struct.archive_entry* %0, i32 1), !dbg !498
  %1 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !499
  call void @archive_entry_set_size(%struct.archive_entry* %1, i64 0), !dbg !500
  %2 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !501
  call void @archive_entry_set_pathname(%struct.archive_entry* %2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.17, i32 0, i32 0)), !dbg !502
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !503
  %4 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !504
  %call1 = call i32 @write_header(%struct.archive_write* %3, %struct.archive_entry* %4), !dbg !505
  store i32 %call1, i32* %er, align 4, !dbg !506
  %5 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !507
  call void @archive_entry_free(%struct.archive_entry* %5), !dbg !508
  %6 = load i32, i32* %er, align 4, !dbg !509
  ret i32 %6, !dbg !510
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_newc_free(%struct.archive_write* %a) #0 !dbg !220 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !511, metadata !226), !dbg !512
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !513, metadata !226), !dbg !514
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !515
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !516
  %1 = load i8*, i8** %format_data, align 8, !dbg !516
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !517
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !518
  %3 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !519
  %4 = bitcast %struct.cpio* %3 to i8*, !dbg !519
  call void @free(i8* %4) #7, !dbg !520
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !521
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !522
  store i8* null, i8** %format_data1, align 8, !dbg !523
  ret i32 0, !dbg !524
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal %struct.archive_string_conv* @get_sconv(%struct.archive_write* %a) #0 !dbg !208 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !525, metadata !226), !dbg !526
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !527, metadata !226), !dbg !528
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !529, metadata !226), !dbg !530
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !531
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !532
  %1 = load i8*, i8** %format_data, align 8, !dbg !532
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !533
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !534
  %3 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !535
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %3, i32 0, i32 2, !dbg !536
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !536
  store %struct.archive_string_conv* %4, %struct.archive_string_conv** %sconv, align 8, !dbg !537
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !538
  %cmp = icmp eq %struct.archive_string_conv* %5, null, !dbg !540
  br i1 %cmp, label %if.then, label %if.end4, !dbg !541

if.then:                                          ; preds = %entry
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !542
  %init_default_conversion = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 4, !dbg !545
  %7 = load i32, i32* %init_default_conversion, align 8, !dbg !545
  %tobool = icmp ne i32 %7, 0, !dbg !542
  br i1 %tobool, label %if.end, label %if.then1, !dbg !546

if.then1:                                         ; preds = %if.then
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !547
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !549
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !550
  %9 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !551
  %sconv_default = getelementptr inbounds %struct.cpio, %struct.cpio* %9, i32 0, i32 3, !dbg !552
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !553
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !554
  %init_default_conversion2 = getelementptr inbounds %struct.cpio, %struct.cpio* %10, i32 0, i32 4, !dbg !555
  store i32 1, i32* %init_default_conversion2, align 8, !dbg !556
  br label %if.end, !dbg !557

if.end:                                           ; preds = %if.then1, %if.then
  %11 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !558
  %sconv_default3 = getelementptr inbounds %struct.cpio, %struct.cpio* %11, i32 0, i32 3, !dbg !559
  %12 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default3, align 8, !dbg !559
  store %struct.archive_string_conv* %12, %struct.archive_string_conv** %sconv, align 8, !dbg !560
  br label %if.end4, !dbg !561

if.end4:                                          ; preds = %if.end, %entry
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !562
  ret %struct.archive_string_conv* %13, !dbg !563
}

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

declare i32 @archive_entry_size_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @write_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !211 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ino = alloca i64, align 8
  %cpio = alloca %struct.cpio*, align 8
  %p = alloca i8*, align 8
  %path = alloca i8*, align 8
  %pathlength = alloca i32, align 4
  %ret = alloca i32, align 4
  %ret_final = alloca i32, align 4
  %h = alloca [110 x i8], align 16
  %sconv = alloca %struct.archive_string_conv*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %len = alloca i64, align 8
  %pad = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !564, metadata !226), !dbg !565
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !566, metadata !226), !dbg !567
  call void @llvm.dbg.declare(metadata i64* %ino, metadata !568, metadata !226), !dbg !569
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !570, metadata !226), !dbg !571
  call void @llvm.dbg.declare(metadata i8** %p, metadata !572, metadata !226), !dbg !573
  call void @llvm.dbg.declare(metadata i8** %path, metadata !574, metadata !226), !dbg !575
  call void @llvm.dbg.declare(metadata i32* %pathlength, metadata !576, metadata !226), !dbg !577
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !578, metadata !226), !dbg !579
  call void @llvm.dbg.declare(metadata i32* %ret_final, metadata !580, metadata !226), !dbg !581
  call void @llvm.dbg.declare(metadata [110 x i8]* %h, metadata !582, metadata !226), !dbg !586
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !587, metadata !226), !dbg !588
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !589, metadata !226), !dbg !590
  call void @llvm.dbg.declare(metadata i64* %len, metadata !591, metadata !226), !dbg !592
  call void @llvm.dbg.declare(metadata i32* %pad, metadata !593, metadata !226), !dbg !594
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !595
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !596
  %1 = load i8*, i8** %format_data, align 8, !dbg !596
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !597
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !598
  store i32 0, i32* %ret_final, align 4, !dbg !599
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !600
  %call = call %struct.archive_string_conv* @get_sconv(%struct.archive_write* %3), !dbg !601
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv, align 8, !dbg !602
  store %struct.archive_entry* null, %struct.archive_entry** %entry_main, align 8, !dbg !603
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !604
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !605
  %call2 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %4, i8** %path, i64* %len, %struct.archive_string_conv* %5), !dbg !606
  store i32 %call2, i32* %ret, align 4, !dbg !607
  %6 = load i32, i32* %ret, align 4, !dbg !608
  %cmp = icmp ne i32 %6, 0, !dbg !610
  br i1 %cmp, label %if.then, label %if.end9, !dbg !611

if.then:                                          ; preds = %entry
  %call3 = call i32* @__errno_location() #1, !dbg !612
  %7 = load i32, i32* %call3, align 4, !dbg !612
  %cmp4 = icmp eq i32 %7, 12, !dbg !615
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !616

if.then5:                                         ; preds = %if.then
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !617
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !619
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !620
  store i32 -30, i32* %ret_final, align 4, !dbg !621
  br label %exit_write_header, !dbg !622

if.end:                                           ; preds = %if.then
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !623
  %archive6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !624
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !625
  %call7 = call i8* @archive_entry_pathname(%struct.archive_entry* %10), !dbg !626
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !627
  %call8 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %11), !dbg !628
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.10, i32 0, i32 0), i8* %call7, i8* %call8), !dbg !629
  store i32 -20, i32* %ret_final, align 4, !dbg !630
  br label %if.end9, !dbg !631

if.end9:                                          ; preds = %if.end, %entry
  %12 = load i64, i64* %len, align 8, !dbg !632
  %conv = trunc i64 %12 to i32, !dbg !633
  %add = add nsw i32 %conv, 1, !dbg !634
  store i32 %add, i32* %pathlength, align 4, !dbg !635
  %arraydecay = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !636
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 110, i32 16, i1 false), !dbg !636
  %arraydecay10 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !637
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay10, i64 0, !dbg !638
  %call11 = call i32 @format_hex(i64 460545, i8* %add.ptr, i32 6), !dbg !639
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !640
  %call12 = call i64 @archive_entry_devmajor(%struct.archive_entry* %13), !dbg !641
  %arraydecay13 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !642
  %add.ptr14 = getelementptr inbounds i8, i8* %arraydecay13, i64 62, !dbg !643
  %call15 = call i32 @format_hex(i64 %call12, i8* %add.ptr14, i32 8), !dbg !644
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !646
  %call16 = call i64 @archive_entry_devminor(%struct.archive_entry* %14), !dbg !647
  %arraydecay17 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !648
  %add.ptr18 = getelementptr inbounds i8, i8* %arraydecay17, i64 70, !dbg !649
  %call19 = call i32 @format_hex(i64 %call16, i8* %add.ptr18, i32 8), !dbg !650
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !651
  %call20 = call i64 @archive_entry_ino64(%struct.archive_entry* %15), !dbg !652
  store i64 %call20, i64* %ino, align 8, !dbg !653
  %16 = load i64, i64* %ino, align 8, !dbg !654
  %cmp21 = icmp sgt i64 %16, 4294967295, !dbg !656
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !657

if.then23:                                        ; preds = %if.end9
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !658
  %archive24 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 0, !dbg !660
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive24, i32 34, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.11, i32 0, i32 0)), !dbg !661
  store i32 -20, i32* %ret_final, align 4, !dbg !662
  br label %if.end25, !dbg !663

if.end25:                                         ; preds = %if.then23, %if.end9
  %18 = load i64, i64* %ino, align 8, !dbg !664
  %and = and i64 %18, 4294967295, !dbg !665
  %arraydecay26 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !666
  %add.ptr27 = getelementptr inbounds i8, i8* %arraydecay26, i64 6, !dbg !667
  %call28 = call i32 @format_hex(i64 %and, i8* %add.ptr27, i32 8), !dbg !668
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !669
  %call29 = call i32 @archive_entry_mode(%struct.archive_entry* %19), !dbg !670
  %conv30 = zext i32 %call29 to i64, !dbg !670
  %arraydecay31 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !671
  %add.ptr32 = getelementptr inbounds i8, i8* %arraydecay31, i64 14, !dbg !672
  %call33 = call i32 @format_hex(i64 %conv30, i8* %add.ptr32, i32 8), !dbg !673
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !674
  %call34 = call i64 @archive_entry_uid(%struct.archive_entry* %20), !dbg !675
  %arraydecay35 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !676
  %add.ptr36 = getelementptr inbounds i8, i8* %arraydecay35, i64 22, !dbg !677
  %call37 = call i32 @format_hex(i64 %call34, i8* %add.ptr36, i32 8), !dbg !678
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !679
  %call38 = call i64 @archive_entry_gid(%struct.archive_entry* %21), !dbg !680
  %arraydecay39 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !681
  %add.ptr40 = getelementptr inbounds i8, i8* %arraydecay39, i64 30, !dbg !682
  %call41 = call i32 @format_hex(i64 %call38, i8* %add.ptr40, i32 8), !dbg !683
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !684
  %call42 = call i32 @archive_entry_nlink(%struct.archive_entry* %22), !dbg !685
  %conv43 = zext i32 %call42 to i64, !dbg !685
  %arraydecay44 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !686
  %add.ptr45 = getelementptr inbounds i8, i8* %arraydecay44, i64 38, !dbg !687
  %call46 = call i32 @format_hex(i64 %conv43, i8* %add.ptr45, i32 8), !dbg !688
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !689
  %call47 = call i32 @archive_entry_filetype(%struct.archive_entry* %23), !dbg !691
  %cmp48 = icmp eq i32 %call47, 24576, !dbg !692
  br i1 %cmp48, label %if.then53, label %lor.lhs.false, !dbg !693

lor.lhs.false:                                    ; preds = %if.end25
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !694
  %call50 = call i32 @archive_entry_filetype(%struct.archive_entry* %24), !dbg !696
  %cmp51 = icmp eq i32 %call50, 8192, !dbg !697
  br i1 %cmp51, label %if.then53, label %if.else, !dbg !698

if.then53:                                        ; preds = %lor.lhs.false, %if.end25
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !699
  %call54 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %25), !dbg !701
  %arraydecay55 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !702
  %add.ptr56 = getelementptr inbounds i8, i8* %arraydecay55, i64 78, !dbg !703
  %call57 = call i32 @format_hex(i64 %call54, i8* %add.ptr56, i32 8), !dbg !704
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !706
  %call58 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %26), !dbg !707
  %arraydecay59 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !708
  %add.ptr60 = getelementptr inbounds i8, i8* %arraydecay59, i64 86, !dbg !709
  %call61 = call i32 @format_hex(i64 %call58, i8* %add.ptr60, i32 8), !dbg !710
  br label %if.end68, !dbg !711

if.else:                                          ; preds = %lor.lhs.false
  %arraydecay62 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !712
  %add.ptr63 = getelementptr inbounds i8, i8* %arraydecay62, i64 78, !dbg !714
  %call64 = call i32 @format_hex(i64 0, i8* %add.ptr63, i32 8), !dbg !715
  %arraydecay65 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !716
  %add.ptr66 = getelementptr inbounds i8, i8* %arraydecay65, i64 86, !dbg !717
  %call67 = call i32 @format_hex(i64 0, i8* %add.ptr66, i32 8), !dbg !718
  br label %if.end68

if.end68:                                         ; preds = %if.else, %if.then53
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !719
  %call69 = call i64 @archive_entry_mtime(%struct.archive_entry* %27), !dbg !720
  %arraydecay70 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !721
  %add.ptr71 = getelementptr inbounds i8, i8* %arraydecay70, i64 46, !dbg !722
  %call72 = call i32 @format_hex(i64 %call69, i8* %add.ptr71, i32 8), !dbg !723
  %28 = load i32, i32* %pathlength, align 4, !dbg !724
  %conv73 = sext i32 %28 to i64, !dbg !724
  %arraydecay74 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !725
  %add.ptr75 = getelementptr inbounds i8, i8* %arraydecay74, i64 94, !dbg !726
  %call76 = call i32 @format_hex(i64 %conv73, i8* %add.ptr75, i32 8), !dbg !727
  %arraydecay77 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !728
  %add.ptr78 = getelementptr inbounds i8, i8* %arraydecay77, i64 102, !dbg !729
  %call79 = call i32 @format_hex(i64 0, i8* %add.ptr78, i32 8), !dbg !730
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !731
  %call80 = call i32 @archive_entry_filetype(%struct.archive_entry* %29), !dbg !733
  %cmp81 = icmp ne i32 %call80, 32768, !dbg !734
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !735

if.then83:                                        ; preds = %if.end68
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !736
  call void @archive_entry_set_size(%struct.archive_entry* %30, i64 0), !dbg !737
  br label %if.end84, !dbg !737

if.end84:                                         ; preds = %if.then83, %if.end68
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !738
  %32 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !739
  %call85 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %31, i8** %p, i64* %len, %struct.archive_string_conv* %32), !dbg !740
  store i32 %call85, i32* %ret, align 4, !dbg !741
  %33 = load i32, i32* %ret, align 4, !dbg !742
  %cmp86 = icmp ne i32 %33, 0, !dbg !744
  br i1 %cmp86, label %if.then88, label %if.end98, !dbg !745

if.then88:                                        ; preds = %if.end84
  %call89 = call i32* @__errno_location() #1, !dbg !746
  %34 = load i32, i32* %call89, align 4, !dbg !746
  %cmp90 = icmp eq i32 %34, 12, !dbg !749
  br i1 %cmp90, label %if.then92, label %if.end94, !dbg !750

if.then92:                                        ; preds = %if.then88
  %35 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !751
  %archive93 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %35, i32 0, i32 0, !dbg !753
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive93, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.12, i32 0, i32 0)), !dbg !754
  store i32 -30, i32* %ret_final, align 4, !dbg !755
  br label %exit_write_header, !dbg !756

if.end94:                                         ; preds = %if.then88
  %36 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !757
  %archive95 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %36, i32 0, i32 0, !dbg !758
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !759
  %call96 = call i8* @archive_entry_symlink(%struct.archive_entry* %37), !dbg !760
  %38 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !761
  %call97 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %38), !dbg !762
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive95, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.13, i32 0, i32 0), i8* %call96, i8* %call97), !dbg !763
  store i32 -20, i32* %ret_final, align 4, !dbg !764
  br label %if.end98, !dbg !765

if.end98:                                         ; preds = %if.end94, %if.end84
  %39 = load i64, i64* %len, align 8, !dbg !766
  %cmp99 = icmp ugt i64 %39, 0, !dbg !768
  br i1 %cmp99, label %land.lhs.true, label %if.else112, !dbg !769

land.lhs.true:                                    ; preds = %if.end98
  %40 = load i8*, i8** %p, align 8, !dbg !770
  %cmp101 = icmp ne i8* %40, null, !dbg !772
  br i1 %cmp101, label %land.lhs.true103, label %if.else112, !dbg !773

land.lhs.true103:                                 ; preds = %land.lhs.true
  %41 = load i8*, i8** %p, align 8, !dbg !774
  %42 = load i8, i8* %41, align 1, !dbg !776
  %conv104 = sext i8 %42 to i32, !dbg !776
  %cmp105 = icmp ne i32 %conv104, 0, !dbg !777
  br i1 %cmp105, label %if.then107, label %if.else112, !dbg !778

if.then107:                                       ; preds = %land.lhs.true103
  %43 = load i8*, i8** %p, align 8, !dbg !779
  %call108 = call i64 @strlen(i8* %43) #8, !dbg !780
  %arraydecay109 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !781
  %add.ptr110 = getelementptr inbounds i8, i8* %arraydecay109, i64 54, !dbg !782
  %call111 = call i32 @format_hex(i64 %call108, i8* %add.ptr110, i32 8), !dbg !783
  store i32 %call111, i32* %ret, align 4, !dbg !784
  br label %if.end117, !dbg !785

if.else112:                                       ; preds = %land.lhs.true103, %land.lhs.true, %if.end98
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !786
  %call113 = call i64 @archive_entry_size(%struct.archive_entry* %44), !dbg !787
  %arraydecay114 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !788
  %add.ptr115 = getelementptr inbounds i8, i8* %arraydecay114, i64 54, !dbg !789
  %call116 = call i32 @format_hex(i64 %call113, i8* %add.ptr115, i32 8), !dbg !790
  store i32 %call116, i32* %ret, align 4, !dbg !791
  br label %if.end117

if.end117:                                        ; preds = %if.else112, %if.then107
  %45 = load i32, i32* %ret, align 4, !dbg !792
  %tobool = icmp ne i32 %45, 0, !dbg !792
  br i1 %tobool, label %if.then118, label %if.end120, !dbg !794

if.then118:                                       ; preds = %if.end117
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !795
  %archive119 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %46, i32 0, i32 0, !dbg !797
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive119, i32 34, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.14, i32 0, i32 0)), !dbg !798
  store i32 -25, i32* %ret_final, align 4, !dbg !799
  br label %exit_write_header, !dbg !800

if.end120:                                        ; preds = %if.end117
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !801
  %arraydecay121 = getelementptr inbounds [110 x i8], [110 x i8]* %h, i32 0, i32 0, !dbg !802
  %call122 = call i32 @__archive_write_output(%struct.archive_write* %47, i8* %arraydecay121, i64 110), !dbg !803
  store i32 %call122, i32* %ret, align 4, !dbg !804
  %48 = load i32, i32* %ret, align 4, !dbg !805
  %cmp123 = icmp ne i32 %48, 0, !dbg !807
  br i1 %cmp123, label %if.then125, label %if.end126, !dbg !808

if.then125:                                       ; preds = %if.end120
  store i32 -30, i32* %ret_final, align 4, !dbg !809
  br label %exit_write_header, !dbg !811

if.end126:                                        ; preds = %if.end120
  %49 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !812
  %50 = load i8*, i8** %path, align 8, !dbg !813
  %51 = load i32, i32* %pathlength, align 4, !dbg !814
  %conv127 = sext i32 %51 to i64, !dbg !814
  %call128 = call i32 @__archive_write_output(%struct.archive_write* %49, i8* %50, i64 %conv127), !dbg !815
  store i32 %call128, i32* %ret, align 4, !dbg !816
  %52 = load i32, i32* %ret, align 4, !dbg !817
  %cmp129 = icmp ne i32 %52, 0, !dbg !819
  br i1 %cmp129, label %if.then131, label %if.end132, !dbg !820

if.then131:                                       ; preds = %if.end126
  store i32 -30, i32* %ret_final, align 4, !dbg !821
  br label %exit_write_header, !dbg !823

if.end132:                                        ; preds = %if.end126
  %53 = load i32, i32* %pathlength, align 4, !dbg !824
  %add133 = add nsw i32 %53, 110, !dbg !824
  %neg = xor i32 %add133, -1, !dbg !824
  %add134 = add nsw i32 1, %neg, !dbg !824
  %and135 = and i32 3, %add134, !dbg !824
  store i32 %and135, i32* %pad, align 4, !dbg !825
  %54 = load i32, i32* %pad, align 4, !dbg !826
  %tobool136 = icmp ne i32 %54, 0, !dbg !826
  br i1 %tobool136, label %if.then137, label %if.end144, !dbg !828

if.then137:                                       ; preds = %if.end132
  %55 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !829
  %56 = load i32, i32* %pad, align 4, !dbg !831
  %conv138 = sext i32 %56 to i64, !dbg !831
  %call139 = call i32 @__archive_write_output(%struct.archive_write* %55, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0), i64 %conv138), !dbg !832
  store i32 %call139, i32* %ret, align 4, !dbg !833
  %57 = load i32, i32* %ret, align 4, !dbg !834
  %cmp140 = icmp ne i32 %57, 0, !dbg !836
  br i1 %cmp140, label %if.then142, label %if.end143, !dbg !837

if.then142:                                       ; preds = %if.then137
  store i32 -30, i32* %ret_final, align 4, !dbg !838
  br label %exit_write_header, !dbg !840

if.end143:                                        ; preds = %if.then137
  br label %if.end144, !dbg !841

if.end144:                                        ; preds = %if.end143, %if.end132
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !842
  %call145 = call i64 @archive_entry_size(%struct.archive_entry* %58), !dbg !843
  %59 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !844
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %59, i32 0, i32 0, !dbg !845
  store i64 %call145, i64* %entry_bytes_remaining, align 8, !dbg !846
  %60 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !847
  %entry_bytes_remaining146 = getelementptr inbounds %struct.cpio, %struct.cpio* %60, i32 0, i32 0, !dbg !847
  %61 = load i64, i64* %entry_bytes_remaining146, align 8, !dbg !847
  %neg147 = xor i64 %61, -1, !dbg !847
  %add148 = add i64 1, %neg147, !dbg !847
  %and149 = and i64 3, %add148, !dbg !847
  %conv150 = trunc i64 %and149 to i32, !dbg !848
  %62 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !849
  %padding = getelementptr inbounds %struct.cpio, %struct.cpio* %62, i32 0, i32 1, !dbg !850
  store i32 %conv150, i32* %padding, align 8, !dbg !851
  %63 = load i8*, i8** %p, align 8, !dbg !852
  %cmp151 = icmp ne i8* %63, null, !dbg !854
  br i1 %cmp151, label %land.lhs.true153, label %if.end175, !dbg !855

land.lhs.true153:                                 ; preds = %if.end144
  %64 = load i8*, i8** %p, align 8, !dbg !856
  %65 = load i8, i8* %64, align 1, !dbg !858
  %conv154 = sext i8 %65 to i32, !dbg !858
  %cmp155 = icmp ne i32 %conv154, 0, !dbg !859
  br i1 %cmp155, label %if.then157, label %if.end175, !dbg !860

if.then157:                                       ; preds = %land.lhs.true153
  %66 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !861
  %67 = load i8*, i8** %p, align 8, !dbg !863
  %68 = load i8*, i8** %p, align 8, !dbg !864
  %call158 = call i64 @strlen(i8* %68) #8, !dbg !865
  %call159 = call i32 @__archive_write_output(%struct.archive_write* %66, i8* %67, i64 %call158), !dbg !866
  store i32 %call159, i32* %ret, align 4, !dbg !868
  %69 = load i32, i32* %ret, align 4, !dbg !869
  %cmp160 = icmp ne i32 %69, 0, !dbg !871
  br i1 %cmp160, label %if.then162, label %if.end163, !dbg !872

if.then162:                                       ; preds = %if.then157
  store i32 -30, i32* %ret_final, align 4, !dbg !873
  br label %exit_write_header, !dbg !875

if.end163:                                        ; preds = %if.then157
  %70 = load i8*, i8** %p, align 8, !dbg !876
  %call164 = call i64 @strlen(i8* %70) #8, !dbg !876
  %neg165 = xor i64 %call164, -1, !dbg !876
  %add166 = add i64 1, %neg165, !dbg !876
  %and167 = and i64 3, %add166, !dbg !876
  %conv168 = trunc i64 %and167 to i32, !dbg !876
  store i32 %conv168, i32* %pad, align 4, !dbg !877
  %71 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !878
  %72 = load i32, i32* %pad, align 4, !dbg !879
  %conv169 = sext i32 %72 to i64, !dbg !879
  %call170 = call i32 @__archive_write_output(%struct.archive_write* %71, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0), i64 %conv169), !dbg !880
  store i32 %call170, i32* %ret, align 4, !dbg !881
  %73 = load i32, i32* %ret, align 4, !dbg !882
  %cmp171 = icmp ne i32 %73, 0, !dbg !884
  br i1 %cmp171, label %if.then173, label %if.end174, !dbg !885

if.then173:                                       ; preds = %if.end163
  store i32 -30, i32* %ret_final, align 4, !dbg !886
  br label %exit_write_header, !dbg !888

if.end174:                                        ; preds = %if.end163
  br label %if.end175, !dbg !889

if.end175:                                        ; preds = %if.end174, %land.lhs.true153, %if.end144
  br label %exit_write_header, !dbg !890

exit_write_header:                                ; preds = %if.end175, %if.then173, %if.then162, %if.then142, %if.then131, %if.then125, %if.then118, %if.then92, %if.then5
  %74 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !892
  %tobool176 = icmp ne %struct.archive_entry* %74, null, !dbg !892
  br i1 %tobool176, label %if.then177, label %if.end178, !dbg !894

if.then177:                                       ; preds = %exit_write_header
  %75 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !895
  call void @archive_entry_free(%struct.archive_entry* %75), !dbg !896
  br label %if.end178, !dbg !896

if.end178:                                        ; preds = %if.then177, %exit_write_header
  %76 = load i32, i32* %ret_final, align 4, !dbg !897
  ret i32 %76, !dbg !898
}

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @format_hex(i64 %v, i8* %p, i32 %digits) #0 !dbg !212 {
entry:
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %digits.addr = alloca i32, align 4
  %max = alloca i64, align 8
  %ret = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !899, metadata !226), !dbg !900
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !901, metadata !226), !dbg !902
  store i32 %digits, i32* %digits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %digits.addr, metadata !903, metadata !226), !dbg !904
  call void @llvm.dbg.declare(metadata i64* %max, metadata !905, metadata !226), !dbg !906
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !907, metadata !226), !dbg !908
  %0 = load i32, i32* %digits.addr, align 4, !dbg !909
  %mul = mul nsw i32 %0, 4, !dbg !910
  %sh_prom = zext i32 %mul to i64, !dbg !911
  %shl = shl i64 1, %sh_prom, !dbg !911
  %sub = sub nsw i64 %shl, 1, !dbg !912
  store i64 %sub, i64* %max, align 8, !dbg !913
  %1 = load i64, i64* %v.addr, align 8, !dbg !914
  %cmp = icmp sge i64 %1, 0, !dbg !916
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !917

land.lhs.true:                                    ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !918
  %3 = load i64, i64* %max, align 8, !dbg !920
  %cmp1 = icmp sle i64 %2, %3, !dbg !921
  br i1 %cmp1, label %if.then, label %if.else, !dbg !922

if.then:                                          ; preds = %land.lhs.true
  %4 = load i64, i64* %v.addr, align 8, !dbg !923
  %5 = load i8*, i8** %p.addr, align 8, !dbg !925
  %6 = load i32, i32* %digits.addr, align 4, !dbg !926
  %call = call i64 @format_hex_recursive(i64 %4, i8* %5, i32 %6), !dbg !927
  store i32 0, i32* %ret, align 4, !dbg !928
  br label %if.end, !dbg !929

if.else:                                          ; preds = %land.lhs.true, %entry
  %7 = load i64, i64* %max, align 8, !dbg !930
  %8 = load i8*, i8** %p.addr, align 8, !dbg !932
  %9 = load i32, i32* %digits.addr, align 4, !dbg !933
  %call2 = call i64 @format_hex_recursive(i64 %7, i8* %8, i32 %9), !dbg !934
  store i32 -1, i32* %ret, align 4, !dbg !935
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %ret, align 4, !dbg !936
  ret i32 %10, !dbg !937
}

declare i64 @archive_entry_devmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_devminor(%struct.archive_entry*) #2

declare i64 @archive_entry_ino64(%struct.archive_entry*) #2

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare i32 @archive_entry_nlink(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i64 @format_hex_recursive(i64 %v, i8* %p, i32 %s) #0 !dbg !215 {
entry:
  %retval = alloca i64, align 8
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !938, metadata !226), !dbg !939
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !940, metadata !226), !dbg !941
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !942, metadata !226), !dbg !943
  %0 = load i32, i32* %s.addr, align 4, !dbg !944
  %cmp = icmp eq i32 %0, 0, !dbg !946
  br i1 %cmp, label %if.then, label %if.end, !dbg !947

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %v.addr, align 8, !dbg !948
  store i64 %1, i64* %retval, align 8, !dbg !949
  br label %return, !dbg !949

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !950
  %3 = load i8*, i8** %p.addr, align 8, !dbg !951
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 1, !dbg !952
  %4 = load i32, i32* %s.addr, align 4, !dbg !953
  %sub = sub nsw i32 %4, 1, !dbg !954
  %call = call i64 @format_hex_recursive(i64 %2, i8* %add.ptr, i32 %sub), !dbg !955
  store i64 %call, i64* %v.addr, align 8, !dbg !956
  %5 = load i64, i64* %v.addr, align 8, !dbg !957
  %and = and i64 %5, 15, !dbg !958
  %arrayidx = getelementptr inbounds [17 x i8], [17 x i8]* @.str.16, i64 0, i64 %and, !dbg !959
  %6 = load i8, i8* %arrayidx, align 1, !dbg !959
  %7 = load i8*, i8** %p.addr, align 8, !dbg !960
  store i8 %6, i8* %7, align 1, !dbg !961
  %8 = load i64, i64* %v.addr, align 8, !dbg !962
  %shr = ashr i64 %8, 4, !dbg !963
  store i64 %shr, i64* %retval, align 8, !dbg !964
  br label %return, !dbg !964

return:                                           ; preds = %if.end, %if.then
  %9 = load i64, i64* %retval, align 8, !dbg !965
  ret i64 %9, !dbg !965
}

declare %struct.archive_entry* @archive_entry_new() #2

declare void @archive_entry_set_nlink(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_pathname(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i32 @__archive_write_nulls(%struct.archive_write*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!222, !223}
!llvm.ident = !{!224}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !204)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_cpio_newc.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !23, !201, !52, !95, !45}
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
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "cpio", file: !1, line: 61, size: 320, align: 64, elements: !194)
!194 = !{!195, !197, !198, !199, !200}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 62, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "padding", scope: !193, file: !1, line: 63, baseType: !23, size: 32, align: 32, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !193, file: !1, line: 65, baseType: !102, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !193, file: !1, line: 66, baseType: !102, size: 64, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !193, file: !1, line: 67, baseType: !23, size: 32, align: 32, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !202, line: 70, baseType: !203)
!202 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!204 = !{!205, !206, !207, !208, !211, !212, !215, !218, !219, !220, !221}
!205 = distinct !DISubprogram(name: "archive_write_set_format_cpio_newc", scope: !1, file: !1, line: 107, type: !21, isLocal: false, isDefinition: true, scopeLine: 108, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!206 = distinct !DISubprogram(name: "archive_write_newc_options", scope: !1, file: !1, line: 138, type: !172, isLocal: true, isDefinition: true, scopeLine: 140, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!207 = distinct !DISubprogram(name: "archive_write_newc_header", scope: !1, file: !1, line: 187, type: !177, isLocal: true, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!208 = distinct !DISubprogram(name: "get_sconv", scope: !1, file: !1, line: 167, type: !209, isLocal: true, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!209 = !DISubroutineType(types: !210)
!210 = !{!102, !4}
!211 = distinct !DISubprogram(name: "write_header", scope: !1, file: !1, line: 217, type: !177, isLocal: true, isDefinition: true, scopeLine: 218, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = distinct !DISubprogram(name: "format_hex", scope: !1, file: !1, line: 396, type: !213, isLocal: true, isDefinition: true, scopeLine: 397, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!213 = !DISubroutineType(types: !214)
!214 = !{!23, !52, !124, !23}
!215 = distinct !DISubprogram(name: "format_hex_recursive", scope: !1, file: !1, line: 413, type: !216, isLocal: true, isDefinition: true, scopeLine: 414, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = !DISubroutineType(types: !217)
!217 = !{!52, !52, !95, !23}
!218 = distinct !DISubprogram(name: "archive_write_newc_data", scope: !1, file: !1, line: 375, type: !181, isLocal: true, isDefinition: true, scopeLine: 376, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_newc_close", scope: !1, file: !1, line: 423, type: !168, isLocal: true, isDefinition: true, scopeLine: 424, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "archive_write_newc_free", scope: !1, file: !1, line: 439, type: !168, isLocal: true, isDefinition: true, scopeLine: 440, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_write_newc_finish_entry", scope: !1, file: !1, line: 450, type: !168, isLocal: true, isDefinition: true, scopeLine: 451, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !{i32 2, !"Dwarf Version", i32 4}
!223 = !{i32 2, !"Debug Info Version", i32 3}
!224 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!225 = !DILocalVariable(name: "_a", arg: 1, scope: !205, file: !1, line: 107, type: !24)
!226 = !DIExpression()
!227 = !DILocation(line: 107, column: 52, scope: !205)
!228 = !DILocalVariable(name: "a", scope: !205, file: !1, line: 109, type: !4)
!229 = !DILocation(line: 109, column: 24, scope: !205)
!230 = !DILocation(line: 109, column: 52, scope: !205)
!231 = !DILocation(line: 109, column: 28, scope: !205)
!232 = !DILocalVariable(name: "cpio", scope: !205, file: !1, line: 110, type: !192)
!233 = !DILocation(line: 110, column: 15, scope: !205)
!234 = !DILocation(line: 112, column: 2, scope: !205)
!235 = !DILocalVariable(name: "magic_test", scope: !236, file: !1, line: 112, type: !23)
!236 = distinct !DILexicalBlock(scope: !205, file: !1, line: 112, column: 2)
!237 = !DILocation(line: 112, column: 2, scope: !236)
!238 = !DILocation(line: 112, column: 2, scope: !239)
!239 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 1)
!240 = !DILocation(line: 112, column: 2, scope: !241)
!241 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!242 = distinct !DILexicalBlock(scope: !236, file: !1, line: 112, column: 2)
!243 = !DILocation(line: 112, column: 2, scope: !244)
!244 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 3)
!245 = !DILocation(line: 116, column: 6, scope: !246)
!246 = distinct !DILexicalBlock(scope: !205, file: !1, line: 116, column: 6)
!247 = !DILocation(line: 116, column: 9, scope: !246)
!248 = !DILocation(line: 116, column: 21, scope: !246)
!249 = !DILocation(line: 116, column: 6, scope: !205)
!250 = !DILocation(line: 117, column: 4, scope: !246)
!251 = !DILocation(line: 117, column: 7, scope: !246)
!252 = !DILocation(line: 117, column: 20, scope: !246)
!253 = !DILocation(line: 117, column: 3, scope: !246)
!254 = !DILocation(line: 119, column: 24, scope: !205)
!255 = !DILocation(line: 119, column: 9, scope: !205)
!256 = !DILocation(line: 119, column: 7, scope: !205)
!257 = !DILocation(line: 120, column: 6, scope: !258)
!258 = distinct !DILexicalBlock(scope: !205, file: !1, line: 120, column: 6)
!259 = !DILocation(line: 120, column: 11, scope: !258)
!260 = !DILocation(line: 120, column: 6, scope: !205)
!261 = !DILocation(line: 121, column: 22, scope: !262)
!262 = distinct !DILexicalBlock(scope: !258, file: !1, line: 120, column: 20)
!263 = !DILocation(line: 121, column: 25, scope: !262)
!264 = !DILocation(line: 121, column: 3, scope: !262)
!265 = !DILocation(line: 122, column: 3, scope: !262)
!266 = !DILocation(line: 124, column: 19, scope: !205)
!267 = !DILocation(line: 124, column: 2, scope: !205)
!268 = !DILocation(line: 124, column: 5, scope: !205)
!269 = !DILocation(line: 124, column: 17, scope: !205)
!270 = !DILocation(line: 125, column: 2, scope: !205)
!271 = !DILocation(line: 125, column: 5, scope: !205)
!272 = !DILocation(line: 125, column: 17, scope: !205)
!273 = !DILocation(line: 126, column: 2, scope: !205)
!274 = !DILocation(line: 126, column: 5, scope: !205)
!275 = !DILocation(line: 126, column: 20, scope: !205)
!276 = !DILocation(line: 127, column: 2, scope: !205)
!277 = !DILocation(line: 127, column: 5, scope: !205)
!278 = !DILocation(line: 127, column: 25, scope: !205)
!279 = !DILocation(line: 128, column: 2, scope: !205)
!280 = !DILocation(line: 128, column: 5, scope: !205)
!281 = !DILocation(line: 128, column: 23, scope: !205)
!282 = !DILocation(line: 129, column: 2, scope: !205)
!283 = !DILocation(line: 129, column: 5, scope: !205)
!284 = !DILocation(line: 129, column: 25, scope: !205)
!285 = !DILocation(line: 130, column: 2, scope: !205)
!286 = !DILocation(line: 130, column: 5, scope: !205)
!287 = !DILocation(line: 130, column: 18, scope: !205)
!288 = !DILocation(line: 131, column: 2, scope: !205)
!289 = !DILocation(line: 131, column: 5, scope: !205)
!290 = !DILocation(line: 131, column: 17, scope: !205)
!291 = !DILocation(line: 132, column: 2, scope: !205)
!292 = !DILocation(line: 132, column: 5, scope: !205)
!293 = !DILocation(line: 132, column: 13, scope: !205)
!294 = !DILocation(line: 132, column: 28, scope: !205)
!295 = !DILocation(line: 133, column: 2, scope: !205)
!296 = !DILocation(line: 133, column: 5, scope: !205)
!297 = !DILocation(line: 133, column: 13, scope: !205)
!298 = !DILocation(line: 133, column: 33, scope: !205)
!299 = !DILocation(line: 134, column: 2, scope: !205)
!300 = !DILocation(line: 135, column: 1, scope: !205)
!301 = !DILocalVariable(name: "a", arg: 1, scope: !206, file: !1, line: 138, type: !4)
!302 = !DILocation(line: 138, column: 50, scope: !206)
!303 = !DILocalVariable(name: "key", arg: 2, scope: !206, file: !1, line: 138, type: !80)
!304 = !DILocation(line: 138, column: 65, scope: !206)
!305 = !DILocalVariable(name: "val", arg: 3, scope: !206, file: !1, line: 139, type: !80)
!306 = !DILocation(line: 139, column: 17, scope: !206)
!307 = !DILocalVariable(name: "cpio", scope: !206, file: !1, line: 141, type: !192)
!308 = !DILocation(line: 141, column: 15, scope: !206)
!309 = !DILocation(line: 141, column: 37, scope: !206)
!310 = !DILocation(line: 141, column: 40, scope: !206)
!311 = !DILocation(line: 141, column: 22, scope: !206)
!312 = !DILocalVariable(name: "ret", scope: !206, file: !1, line: 142, type: !23)
!313 = !DILocation(line: 142, column: 6, scope: !206)
!314 = !DILocation(line: 144, column: 13, scope: !315)
!315 = distinct !DILexicalBlock(scope: !206, file: !1, line: 144, column: 6)
!316 = !DILocation(line: 144, column: 6, scope: !315)
!317 = !DILocation(line: 144, column: 33, scope: !315)
!318 = !DILocation(line: 144, column: 6, scope: !206)
!319 = !DILocation(line: 145, column: 7, scope: !320)
!320 = distinct !DILexicalBlock(scope: !321, file: !1, line: 145, column: 7)
!321 = distinct !DILexicalBlock(scope: !315, file: !1, line: 144, column: 39)
!322 = !DILocation(line: 145, column: 11, scope: !320)
!323 = !DILocation(line: 145, column: 19, scope: !320)
!324 = !DILocation(line: 145, column: 22, scope: !325)
!325 = !DILexicalBlockFile(scope: !320, file: !1, discriminator: 1)
!326 = !DILocation(line: 145, column: 29, scope: !325)
!327 = !DILocation(line: 145, column: 7, scope: !325)
!328 = !DILocation(line: 146, column: 23, scope: !320)
!329 = !DILocation(line: 146, column: 26, scope: !320)
!330 = !DILocation(line: 148, column: 8, scope: !320)
!331 = !DILocation(line: 148, column: 11, scope: !320)
!332 = !DILocation(line: 146, column: 4, scope: !320)
!333 = !DILocation(line: 151, column: 9, scope: !334)
!334 = distinct !DILexicalBlock(scope: !320, file: !1, line: 149, column: 8)
!335 = !DILocation(line: 151, column: 12, scope: !334)
!336 = !DILocation(line: 151, column: 21, scope: !334)
!337 = !DILocation(line: 150, column: 22, scope: !334)
!338 = !DILocation(line: 150, column: 4, scope: !334)
!339 = !DILocation(line: 150, column: 10, scope: !334)
!340 = !DILocation(line: 150, column: 20, scope: !334)
!341 = !DILocation(line: 152, column: 8, scope: !342)
!342 = distinct !DILexicalBlock(scope: !334, file: !1, line: 152, column: 8)
!343 = !DILocation(line: 152, column: 14, scope: !342)
!344 = !DILocation(line: 152, column: 24, scope: !342)
!345 = !DILocation(line: 152, column: 8, scope: !334)
!346 = !DILocation(line: 153, column: 9, scope: !342)
!347 = !DILocation(line: 153, column: 5, scope: !342)
!348 = !DILocation(line: 155, column: 9, scope: !342)
!349 = !DILocation(line: 157, column: 11, scope: !321)
!350 = !DILocation(line: 157, column: 3, scope: !321)
!351 = !DILocation(line: 163, column: 2, scope: !206)
!352 = !DILocation(line: 164, column: 1, scope: !206)
!353 = !DILocalVariable(name: "a", arg: 1, scope: !207, file: !1, line: 187, type: !4)
!354 = !DILocation(line: 187, column: 49, scope: !207)
!355 = !DILocalVariable(name: "entry", arg: 2, scope: !207, file: !1, line: 187, type: !30)
!356 = !DILocation(line: 187, column: 74, scope: !207)
!357 = !DILocalVariable(name: "path", scope: !207, file: !1, line: 189, type: !80)
!358 = !DILocation(line: 189, column: 14, scope: !207)
!359 = !DILocalVariable(name: "len", scope: !207, file: !1, line: 190, type: !45)
!360 = !DILocation(line: 190, column: 9, scope: !207)
!361 = !DILocation(line: 192, column: 29, scope: !362)
!362 = distinct !DILexicalBlock(scope: !207, file: !1, line: 192, column: 6)
!363 = !DILocation(line: 192, column: 6, scope: !362)
!364 = !DILocation(line: 192, column: 36, scope: !362)
!365 = !DILocation(line: 192, column: 6, scope: !207)
!366 = !DILocation(line: 193, column: 22, scope: !367)
!367 = distinct !DILexicalBlock(scope: !362, file: !1, line: 192, column: 42)
!368 = !DILocation(line: 193, column: 25, scope: !367)
!369 = !DILocation(line: 193, column: 3, scope: !367)
!370 = !DILocation(line: 194, column: 3, scope: !367)
!371 = !DILocation(line: 197, column: 31, scope: !372)
!372 = distinct !DILexicalBlock(scope: !207, file: !1, line: 197, column: 6)
!373 = !DILocation(line: 197, column: 61, scope: !372)
!374 = !DILocation(line: 197, column: 51, scope: !372)
!375 = !DILocation(line: 197, column: 6, scope: !376)
!376 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 2)
!377 = !DILocation(line: 197, column: 65, scope: !372)
!378 = !DILocation(line: 198, column: 6, scope: !372)
!379 = !DILocation(line: 198, column: 9, scope: !380)
!380 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 1)
!381 = !DILocation(line: 198, column: 15, scope: !380)
!382 = !DILocation(line: 197, column: 6, scope: !383)
!383 = !DILexicalBlockFile(scope: !207, file: !1, discriminator: 1)
!384 = !DILocation(line: 199, column: 22, scope: !385)
!385 = distinct !DILexicalBlock(scope: !372, file: !1, line: 198, column: 26)
!386 = !DILocation(line: 199, column: 25, scope: !385)
!387 = !DILocation(line: 199, column: 3, scope: !385)
!388 = !DILocation(line: 201, column: 3, scope: !385)
!389 = !DILocation(line: 203, column: 6, scope: !390)
!390 = distinct !DILexicalBlock(scope: !207, file: !1, line: 203, column: 6)
!391 = !DILocation(line: 203, column: 10, scope: !390)
!392 = !DILocation(line: 203, column: 15, scope: !390)
!393 = !DILocation(line: 203, column: 18, scope: !394)
!394 = !DILexicalBlockFile(scope: !390, file: !1, discriminator: 1)
!395 = !DILocation(line: 203, column: 23, scope: !394)
!396 = !DILocation(line: 203, column: 31, scope: !394)
!397 = !DILocation(line: 203, column: 34, scope: !398)
!398 = !DILexicalBlockFile(scope: !390, file: !1, discriminator: 2)
!399 = !DILocation(line: 203, column: 42, scope: !398)
!400 = !DILocation(line: 203, column: 6, scope: !398)
!401 = !DILocation(line: 204, column: 22, scope: !402)
!402 = distinct !DILexicalBlock(scope: !390, file: !1, line: 203, column: 51)
!403 = !DILocation(line: 204, column: 25, scope: !402)
!404 = !DILocation(line: 204, column: 3, scope: !402)
!405 = !DILocation(line: 205, column: 3, scope: !402)
!406 = !DILocation(line: 208, column: 29, scope: !407)
!407 = distinct !DILexicalBlock(scope: !207, file: !1, line: 208, column: 6)
!408 = !DILocation(line: 208, column: 6, scope: !407)
!409 = !DILocation(line: 208, column: 36, scope: !407)
!410 = !DILocation(line: 209, column: 6, scope: !407)
!411 = !DILocation(line: 209, column: 37, scope: !412)
!412 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 1)
!413 = !DILocation(line: 209, column: 11, scope: !412)
!414 = !DILocation(line: 209, column: 44, scope: !412)
!415 = !DILocation(line: 209, column: 66, scope: !416)
!416 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 2)
!417 = !DILocation(line: 209, column: 47, scope: !416)
!418 = !DILocation(line: 209, column: 73, scope: !416)
!419 = !DILocation(line: 208, column: 6, scope: !383)
!420 = !DILocation(line: 210, column: 22, scope: !421)
!421 = distinct !DILexicalBlock(scope: !407, file: !1, line: 209, column: 79)
!422 = !DILocation(line: 210, column: 25, scope: !421)
!423 = !DILocation(line: 210, column: 3, scope: !421)
!424 = !DILocation(line: 211, column: 3, scope: !421)
!425 = !DILocation(line: 213, column: 22, scope: !207)
!426 = !DILocation(line: 213, column: 25, scope: !207)
!427 = !DILocation(line: 213, column: 9, scope: !207)
!428 = !DILocation(line: 213, column: 2, scope: !207)
!429 = !DILocation(line: 214, column: 1, scope: !207)
!430 = !DILocalVariable(name: "a", arg: 1, scope: !218, file: !1, line: 375, type: !4)
!431 = !DILocation(line: 375, column: 47, scope: !218)
!432 = !DILocalVariable(name: "buff", arg: 2, scope: !218, file: !1, line: 375, type: !43)
!433 = !DILocation(line: 375, column: 62, scope: !218)
!434 = !DILocalVariable(name: "s", arg: 3, scope: !218, file: !1, line: 375, type: !45)
!435 = !DILocation(line: 375, column: 75, scope: !218)
!436 = !DILocalVariable(name: "cpio", scope: !218, file: !1, line: 377, type: !192)
!437 = !DILocation(line: 377, column: 15, scope: !218)
!438 = !DILocalVariable(name: "ret", scope: !218, file: !1, line: 378, type: !23)
!439 = !DILocation(line: 378, column: 6, scope: !218)
!440 = !DILocation(line: 380, column: 24, scope: !218)
!441 = !DILocation(line: 380, column: 27, scope: !218)
!442 = !DILocation(line: 380, column: 9, scope: !218)
!443 = !DILocation(line: 380, column: 7, scope: !218)
!444 = !DILocation(line: 381, column: 6, scope: !445)
!445 = distinct !DILexicalBlock(scope: !218, file: !1, line: 381, column: 6)
!446 = !DILocation(line: 381, column: 10, scope: !445)
!447 = !DILocation(line: 381, column: 16, scope: !445)
!448 = !DILocation(line: 381, column: 8, scope: !445)
!449 = !DILocation(line: 381, column: 6, scope: !218)
!450 = !DILocation(line: 382, column: 15, scope: !445)
!451 = !DILocation(line: 382, column: 21, scope: !445)
!452 = !DILocation(line: 382, column: 5, scope: !445)
!453 = !DILocation(line: 382, column: 3, scope: !445)
!454 = !DILocation(line: 384, column: 31, scope: !218)
!455 = !DILocation(line: 384, column: 34, scope: !218)
!456 = !DILocation(line: 384, column: 40, scope: !218)
!457 = !DILocation(line: 384, column: 8, scope: !218)
!458 = !DILocation(line: 384, column: 6, scope: !218)
!459 = !DILocation(line: 385, column: 33, scope: !218)
!460 = !DILocation(line: 385, column: 2, scope: !218)
!461 = !DILocation(line: 385, column: 8, scope: !218)
!462 = !DILocation(line: 385, column: 30, scope: !218)
!463 = !DILocation(line: 386, column: 6, scope: !464)
!464 = distinct !DILexicalBlock(scope: !218, file: !1, line: 386, column: 6)
!465 = !DILocation(line: 386, column: 10, scope: !464)
!466 = !DILocation(line: 386, column: 6, scope: !218)
!467 = !DILocation(line: 387, column: 11, scope: !464)
!468 = !DILocation(line: 387, column: 3, scope: !464)
!469 = !DILocation(line: 389, column: 11, scope: !464)
!470 = !DILocation(line: 389, column: 10, scope: !464)
!471 = !DILocation(line: 389, column: 3, scope: !464)
!472 = !DILocation(line: 390, column: 1, scope: !218)
!473 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 450, type: !4)
!474 = !DILocation(line: 450, column: 55, scope: !221)
!475 = !DILocalVariable(name: "cpio", scope: !221, file: !1, line: 452, type: !192)
!476 = !DILocation(line: 452, column: 15, scope: !221)
!477 = !DILocation(line: 454, column: 24, scope: !221)
!478 = !DILocation(line: 454, column: 27, scope: !221)
!479 = !DILocation(line: 454, column: 9, scope: !221)
!480 = !DILocation(line: 454, column: 7, scope: !221)
!481 = !DILocation(line: 455, column: 32, scope: !221)
!482 = !DILocation(line: 456, column: 11, scope: !221)
!483 = !DILocation(line: 456, column: 17, scope: !221)
!484 = !DILocation(line: 456, column: 41, scope: !221)
!485 = !DILocation(line: 456, column: 47, scope: !221)
!486 = !DILocation(line: 456, column: 39, scope: !221)
!487 = !DILocation(line: 455, column: 10, scope: !221)
!488 = !DILocation(line: 455, column: 2, scope: !221)
!489 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 423, type: !4)
!490 = !DILocation(line: 423, column: 48, scope: !219)
!491 = !DILocalVariable(name: "er", scope: !219, file: !1, line: 425, type: !23)
!492 = !DILocation(line: 425, column: 6, scope: !219)
!493 = !DILocalVariable(name: "trailer", scope: !219, file: !1, line: 426, type: !30)
!494 = !DILocation(line: 426, column: 24, scope: !219)
!495 = !DILocation(line: 428, column: 12, scope: !219)
!496 = !DILocation(line: 428, column: 10, scope: !219)
!497 = !DILocation(line: 429, column: 26, scope: !219)
!498 = !DILocation(line: 429, column: 2, scope: !219)
!499 = !DILocation(line: 430, column: 25, scope: !219)
!500 = !DILocation(line: 430, column: 2, scope: !219)
!501 = !DILocation(line: 431, column: 29, scope: !219)
!502 = !DILocation(line: 431, column: 2, scope: !219)
!503 = !DILocation(line: 433, column: 20, scope: !219)
!504 = !DILocation(line: 433, column: 23, scope: !219)
!505 = !DILocation(line: 433, column: 7, scope: !219)
!506 = !DILocation(line: 433, column: 5, scope: !219)
!507 = !DILocation(line: 434, column: 21, scope: !219)
!508 = !DILocation(line: 434, column: 2, scope: !219)
!509 = !DILocation(line: 435, column: 10, scope: !219)
!510 = !DILocation(line: 435, column: 2, scope: !219)
!511 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 439, type: !4)
!512 = !DILocation(line: 439, column: 47, scope: !220)
!513 = !DILocalVariable(name: "cpio", scope: !220, file: !1, line: 441, type: !192)
!514 = !DILocation(line: 441, column: 15, scope: !220)
!515 = !DILocation(line: 443, column: 24, scope: !220)
!516 = !DILocation(line: 443, column: 27, scope: !220)
!517 = !DILocation(line: 443, column: 9, scope: !220)
!518 = !DILocation(line: 443, column: 7, scope: !220)
!519 = !DILocation(line: 444, column: 7, scope: !220)
!520 = !DILocation(line: 444, column: 2, scope: !220)
!521 = !DILocation(line: 445, column: 2, scope: !220)
!522 = !DILocation(line: 445, column: 5, scope: !220)
!523 = !DILocation(line: 445, column: 17, scope: !220)
!524 = !DILocation(line: 446, column: 2, scope: !220)
!525 = !DILocalVariable(name: "a", arg: 1, scope: !208, file: !1, line: 167, type: !4)
!526 = !DILocation(line: 167, column: 33, scope: !208)
!527 = !DILocalVariable(name: "cpio", scope: !208, file: !1, line: 169, type: !192)
!528 = !DILocation(line: 169, column: 15, scope: !208)
!529 = !DILocalVariable(name: "sconv", scope: !208, file: !1, line: 170, type: !102)
!530 = !DILocation(line: 170, column: 30, scope: !208)
!531 = !DILocation(line: 172, column: 24, scope: !208)
!532 = !DILocation(line: 172, column: 27, scope: !208)
!533 = !DILocation(line: 172, column: 9, scope: !208)
!534 = !DILocation(line: 172, column: 7, scope: !208)
!535 = !DILocation(line: 173, column: 10, scope: !208)
!536 = !DILocation(line: 173, column: 16, scope: !208)
!537 = !DILocation(line: 173, column: 8, scope: !208)
!538 = !DILocation(line: 174, column: 6, scope: !539)
!539 = distinct !DILexicalBlock(scope: !208, file: !1, line: 174, column: 6)
!540 = !DILocation(line: 174, column: 12, scope: !539)
!541 = !DILocation(line: 174, column: 6, scope: !208)
!542 = !DILocation(line: 175, column: 8, scope: !543)
!543 = distinct !DILexicalBlock(scope: !544, file: !1, line: 175, column: 7)
!544 = distinct !DILexicalBlock(scope: !539, file: !1, line: 174, column: 21)
!545 = !DILocation(line: 175, column: 14, scope: !543)
!546 = !DILocation(line: 175, column: 7, scope: !544)
!547 = !DILocation(line: 178, column: 12, scope: !548)
!548 = distinct !DILexicalBlock(scope: !543, file: !1, line: 175, column: 39)
!549 = !DILocation(line: 178, column: 15, scope: !548)
!550 = !DILocation(line: 177, column: 8, scope: !548)
!551 = !DILocation(line: 176, column: 4, scope: !548)
!552 = !DILocation(line: 176, column: 10, scope: !548)
!553 = !DILocation(line: 176, column: 24, scope: !548)
!554 = !DILocation(line: 179, column: 4, scope: !548)
!555 = !DILocation(line: 179, column: 10, scope: !548)
!556 = !DILocation(line: 179, column: 34, scope: !548)
!557 = !DILocation(line: 180, column: 3, scope: !548)
!558 = !DILocation(line: 181, column: 11, scope: !544)
!559 = !DILocation(line: 181, column: 17, scope: !544)
!560 = !DILocation(line: 181, column: 9, scope: !544)
!561 = !DILocation(line: 182, column: 2, scope: !544)
!562 = !DILocation(line: 183, column: 10, scope: !208)
!563 = !DILocation(line: 183, column: 2, scope: !208)
!564 = !DILocalVariable(name: "a", arg: 1, scope: !211, file: !1, line: 217, type: !4)
!565 = !DILocation(line: 217, column: 36, scope: !211)
!566 = !DILocalVariable(name: "entry", arg: 2, scope: !211, file: !1, line: 217, type: !30)
!567 = !DILocation(line: 217, column: 61, scope: !211)
!568 = !DILocalVariable(name: "ino", scope: !211, file: !1, line: 219, type: !52)
!569 = !DILocation(line: 219, column: 10, scope: !211)
!570 = !DILocalVariable(name: "cpio", scope: !211, file: !1, line: 220, type: !192)
!571 = !DILocation(line: 220, column: 15, scope: !211)
!572 = !DILocalVariable(name: "p", scope: !211, file: !1, line: 221, type: !80)
!573 = !DILocation(line: 221, column: 14, scope: !211)
!574 = !DILocalVariable(name: "path", scope: !211, file: !1, line: 221, type: !80)
!575 = !DILocation(line: 221, column: 18, scope: !211)
!576 = !DILocalVariable(name: "pathlength", scope: !211, file: !1, line: 222, type: !23)
!577 = !DILocation(line: 222, column: 6, scope: !211)
!578 = !DILocalVariable(name: "ret", scope: !211, file: !1, line: 222, type: !23)
!579 = !DILocation(line: 222, column: 18, scope: !211)
!580 = !DILocalVariable(name: "ret_final", scope: !211, file: !1, line: 222, type: !23)
!581 = !DILocation(line: 222, column: 23, scope: !211)
!582 = !DILocalVariable(name: "h", scope: !211, file: !1, line: 223, type: !583)
!583 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 880, align: 8, elements: !584)
!584 = !{!585}
!585 = !DISubrange(count: 110)
!586 = !DILocation(line: 223, column: 7, scope: !211)
!587 = !DILocalVariable(name: "sconv", scope: !211, file: !1, line: 224, type: !102)
!588 = !DILocation(line: 224, column: 30, scope: !211)
!589 = !DILocalVariable(name: "entry_main", scope: !211, file: !1, line: 225, type: !30)
!590 = !DILocation(line: 225, column: 24, scope: !211)
!591 = !DILocalVariable(name: "len", scope: !211, file: !1, line: 226, type: !45)
!592 = !DILocation(line: 226, column: 9, scope: !211)
!593 = !DILocalVariable(name: "pad", scope: !211, file: !1, line: 227, type: !23)
!594 = !DILocation(line: 227, column: 6, scope: !211)
!595 = !DILocation(line: 229, column: 24, scope: !211)
!596 = !DILocation(line: 229, column: 27, scope: !211)
!597 = !DILocation(line: 229, column: 9, scope: !211)
!598 = !DILocation(line: 229, column: 7, scope: !211)
!599 = !DILocation(line: 230, column: 12, scope: !211)
!600 = !DILocation(line: 231, column: 20, scope: !211)
!601 = !DILocation(line: 231, column: 10, scope: !211)
!602 = !DILocation(line: 231, column: 8, scope: !211)
!603 = !DILocation(line: 247, column: 13, scope: !211)
!604 = !DILocation(line: 250, column: 33, scope: !211)
!605 = !DILocation(line: 250, column: 53, scope: !211)
!606 = !DILocation(line: 250, column: 8, scope: !211)
!607 = !DILocation(line: 250, column: 6, scope: !211)
!608 = !DILocation(line: 251, column: 6, scope: !609)
!609 = distinct !DILexicalBlock(scope: !211, file: !1, line: 251, column: 6)
!610 = !DILocation(line: 251, column: 10, scope: !609)
!611 = !DILocation(line: 251, column: 6, scope: !211)
!612 = !DILocation(line: 252, column: 7, scope: !613)
!613 = distinct !DILexicalBlock(scope: !614, file: !1, line: 252, column: 7)
!614 = distinct !DILexicalBlock(scope: !609, file: !1, line: 251, column: 16)
!615 = !DILocation(line: 252, column: 13, scope: !613)
!616 = !DILocation(line: 252, column: 7, scope: !614)
!617 = !DILocation(line: 253, column: 23, scope: !618)
!618 = distinct !DILexicalBlock(scope: !613, file: !1, line: 252, column: 24)
!619 = !DILocation(line: 253, column: 26, scope: !618)
!620 = !DILocation(line: 253, column: 4, scope: !618)
!621 = !DILocation(line: 255, column: 14, scope: !618)
!622 = !DILocation(line: 256, column: 4, scope: !618)
!623 = !DILocation(line: 258, column: 22, scope: !614)
!624 = !DILocation(line: 258, column: 25, scope: !614)
!625 = !DILocation(line: 260, column: 30, scope: !614)
!626 = !DILocation(line: 260, column: 7, scope: !614)
!627 = !DILocation(line: 261, column: 46, scope: !614)
!628 = !DILocation(line: 261, column: 7, scope: !614)
!629 = !DILocation(line: 258, column: 3, scope: !614)
!630 = !DILocation(line: 262, column: 13, scope: !614)
!631 = !DILocation(line: 263, column: 2, scope: !614)
!632 = !DILocation(line: 264, column: 20, scope: !211)
!633 = !DILocation(line: 264, column: 15, scope: !211)
!634 = !DILocation(line: 264, column: 24, scope: !211)
!635 = !DILocation(line: 264, column: 13, scope: !211)
!636 = !DILocation(line: 266, column: 2, scope: !211)
!637 = !DILocation(line: 267, column: 23, scope: !211)
!638 = !DILocation(line: 267, column: 25, scope: !211)
!639 = !DILocation(line: 267, column: 2, scope: !211)
!640 = !DILocation(line: 268, column: 36, scope: !211)
!641 = !DILocation(line: 268, column: 13, scope: !211)
!642 = !DILocation(line: 268, column: 44, scope: !211)
!643 = !DILocation(line: 268, column: 46, scope: !211)
!644 = !DILocation(line: 268, column: 2, scope: !645)
!645 = !DILexicalBlockFile(scope: !211, file: !1, discriminator: 1)
!646 = !DILocation(line: 270, column: 36, scope: !211)
!647 = !DILocation(line: 270, column: 13, scope: !211)
!648 = !DILocation(line: 270, column: 44, scope: !211)
!649 = !DILocation(line: 270, column: 46, scope: !211)
!650 = !DILocation(line: 270, column: 2, scope: !645)
!651 = !DILocation(line: 273, column: 28, scope: !211)
!652 = !DILocation(line: 273, column: 8, scope: !211)
!653 = !DILocation(line: 273, column: 6, scope: !211)
!654 = !DILocation(line: 274, column: 6, scope: !655)
!655 = distinct !DILexicalBlock(scope: !211, file: !1, line: 274, column: 6)
!656 = !DILocation(line: 274, column: 10, scope: !655)
!657 = !DILocation(line: 274, column: 6, scope: !211)
!658 = !DILocation(line: 275, column: 22, scope: !659)
!659 = distinct !DILexicalBlock(scope: !655, file: !1, line: 274, column: 24)
!660 = !DILocation(line: 275, column: 25, scope: !659)
!661 = !DILocation(line: 275, column: 3, scope: !659)
!662 = !DILocation(line: 277, column: 13, scope: !659)
!663 = !DILocation(line: 278, column: 2, scope: !659)
!664 = !DILocation(line: 281, column: 13, scope: !211)
!665 = !DILocation(line: 281, column: 17, scope: !211)
!666 = !DILocation(line: 281, column: 31, scope: !211)
!667 = !DILocation(line: 281, column: 33, scope: !211)
!668 = !DILocation(line: 281, column: 2, scope: !211)
!669 = !DILocation(line: 282, column: 32, scope: !211)
!670 = !DILocation(line: 282, column: 13, scope: !211)
!671 = !DILocation(line: 282, column: 40, scope: !211)
!672 = !DILocation(line: 282, column: 42, scope: !211)
!673 = !DILocation(line: 282, column: 2, scope: !645)
!674 = !DILocation(line: 283, column: 31, scope: !211)
!675 = !DILocation(line: 283, column: 13, scope: !211)
!676 = !DILocation(line: 283, column: 39, scope: !211)
!677 = !DILocation(line: 283, column: 41, scope: !211)
!678 = !DILocation(line: 283, column: 2, scope: !645)
!679 = !DILocation(line: 284, column: 31, scope: !211)
!680 = !DILocation(line: 284, column: 13, scope: !211)
!681 = !DILocation(line: 284, column: 39, scope: !211)
!682 = !DILocation(line: 284, column: 41, scope: !211)
!683 = !DILocation(line: 284, column: 2, scope: !645)
!684 = !DILocation(line: 285, column: 33, scope: !211)
!685 = !DILocation(line: 285, column: 13, scope: !211)
!686 = !DILocation(line: 285, column: 41, scope: !211)
!687 = !DILocation(line: 285, column: 43, scope: !211)
!688 = !DILocation(line: 285, column: 2, scope: !645)
!689 = !DILocation(line: 286, column: 29, scope: !690)
!690 = distinct !DILexicalBlock(scope: !211, file: !1, line: 286, column: 6)
!691 = !DILocation(line: 286, column: 6, scope: !690)
!692 = !DILocation(line: 286, column: 36, scope: !690)
!693 = !DILocation(line: 287, column: 6, scope: !690)
!694 = !DILocation(line: 287, column: 32, scope: !695)
!695 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 1)
!696 = !DILocation(line: 287, column: 9, scope: !695)
!697 = !DILocation(line: 287, column: 39, scope: !695)
!698 = !DILocation(line: 286, column: 6, scope: !645)
!699 = !DILocation(line: 288, column: 41, scope: !700)
!700 = distinct !DILexicalBlock(scope: !690, file: !1, line: 287, column: 52)
!701 = !DILocation(line: 288, column: 17, scope: !700)
!702 = !DILocation(line: 288, column: 49, scope: !700)
!703 = !DILocation(line: 288, column: 51, scope: !700)
!704 = !DILocation(line: 288, column: 6, scope: !705)
!705 = !DILexicalBlockFile(scope: !700, file: !1, discriminator: 1)
!706 = !DILocation(line: 289, column: 41, scope: !700)
!707 = !DILocation(line: 289, column: 17, scope: !700)
!708 = !DILocation(line: 289, column: 49, scope: !700)
!709 = !DILocation(line: 289, column: 51, scope: !700)
!710 = !DILocation(line: 289, column: 6, scope: !705)
!711 = !DILocation(line: 290, column: 2, scope: !700)
!712 = !DILocation(line: 291, column: 20, scope: !713)
!713 = distinct !DILexicalBlock(scope: !690, file: !1, line: 290, column: 9)
!714 = !DILocation(line: 291, column: 22, scope: !713)
!715 = !DILocation(line: 291, column: 6, scope: !713)
!716 = !DILocation(line: 292, column: 20, scope: !713)
!717 = !DILocation(line: 292, column: 22, scope: !713)
!718 = !DILocation(line: 292, column: 6, scope: !713)
!719 = !DILocation(line: 294, column: 33, scope: !211)
!720 = !DILocation(line: 294, column: 13, scope: !211)
!721 = !DILocation(line: 294, column: 41, scope: !211)
!722 = !DILocation(line: 294, column: 43, scope: !211)
!723 = !DILocation(line: 294, column: 2, scope: !645)
!724 = !DILocation(line: 295, column: 13, scope: !211)
!725 = !DILocation(line: 295, column: 25, scope: !211)
!726 = !DILocation(line: 295, column: 27, scope: !211)
!727 = !DILocation(line: 295, column: 2, scope: !211)
!728 = !DILocation(line: 296, column: 16, scope: !211)
!729 = !DILocation(line: 296, column: 18, scope: !211)
!730 = !DILocation(line: 296, column: 2, scope: !211)
!731 = !DILocation(line: 299, column: 29, scope: !732)
!732 = distinct !DILexicalBlock(scope: !211, file: !1, line: 299, column: 6)
!733 = !DILocation(line: 299, column: 6, scope: !732)
!734 = !DILocation(line: 299, column: 36, scope: !732)
!735 = !DILocation(line: 299, column: 6, scope: !211)
!736 = !DILocation(line: 300, column: 26, scope: !732)
!737 = !DILocation(line: 300, column: 3, scope: !732)
!738 = !DILocation(line: 303, column: 32, scope: !211)
!739 = !DILocation(line: 303, column: 49, scope: !211)
!740 = !DILocation(line: 303, column: 8, scope: !211)
!741 = !DILocation(line: 303, column: 6, scope: !211)
!742 = !DILocation(line: 304, column: 6, scope: !743)
!743 = distinct !DILexicalBlock(scope: !211, file: !1, line: 304, column: 6)
!744 = !DILocation(line: 304, column: 10, scope: !743)
!745 = !DILocation(line: 304, column: 6, scope: !211)
!746 = !DILocation(line: 305, column: 7, scope: !747)
!747 = distinct !DILexicalBlock(scope: !748, file: !1, line: 305, column: 7)
!748 = distinct !DILexicalBlock(scope: !743, file: !1, line: 304, column: 16)
!749 = !DILocation(line: 305, column: 13, scope: !747)
!750 = !DILocation(line: 305, column: 7, scope: !748)
!751 = !DILocation(line: 306, column: 23, scope: !752)
!752 = distinct !DILexicalBlock(scope: !747, file: !1, line: 305, column: 24)
!753 = !DILocation(line: 306, column: 26, scope: !752)
!754 = !DILocation(line: 306, column: 4, scope: !752)
!755 = !DILocation(line: 308, column: 14, scope: !752)
!756 = !DILocation(line: 309, column: 4, scope: !752)
!757 = !DILocation(line: 311, column: 22, scope: !748)
!758 = !DILocation(line: 311, column: 25, scope: !748)
!759 = !DILocation(line: 313, column: 29, scope: !748)
!760 = !DILocation(line: 313, column: 7, scope: !748)
!761 = !DILocation(line: 314, column: 46, scope: !748)
!762 = !DILocation(line: 314, column: 7, scope: !748)
!763 = !DILocation(line: 311, column: 3, scope: !748)
!764 = !DILocation(line: 315, column: 13, scope: !748)
!765 = !DILocation(line: 316, column: 2, scope: !748)
!766 = !DILocation(line: 317, column: 6, scope: !767)
!767 = distinct !DILexicalBlock(scope: !211, file: !1, line: 317, column: 6)
!768 = !DILocation(line: 317, column: 10, scope: !767)
!769 = !DILocation(line: 317, column: 14, scope: !767)
!770 = !DILocation(line: 317, column: 17, scope: !771)
!771 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 1)
!772 = !DILocation(line: 317, column: 19, scope: !771)
!773 = !DILocation(line: 317, column: 28, scope: !771)
!774 = !DILocation(line: 317, column: 33, scope: !775)
!775 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 2)
!776 = !DILocation(line: 317, column: 32, scope: !775)
!777 = !DILocation(line: 317, column: 35, scope: !775)
!778 = !DILocation(line: 317, column: 6, scope: !775)
!779 = !DILocation(line: 318, column: 27, scope: !767)
!780 = !DILocation(line: 318, column: 20, scope: !767)
!781 = !DILocation(line: 318, column: 31, scope: !767)
!782 = !DILocation(line: 318, column: 33, scope: !767)
!783 = !DILocation(line: 318, column: 9, scope: !771)
!784 = !DILocation(line: 318, column: 7, scope: !767)
!785 = !DILocation(line: 318, column: 3, scope: !767)
!786 = !DILocation(line: 321, column: 39, scope: !767)
!787 = !DILocation(line: 321, column: 20, scope: !767)
!788 = !DILocation(line: 322, column: 7, scope: !767)
!789 = !DILocation(line: 322, column: 9, scope: !767)
!790 = !DILocation(line: 321, column: 9, scope: !771)
!791 = !DILocation(line: 321, column: 7, scope: !767)
!792 = !DILocation(line: 323, column: 6, scope: !793)
!793 = distinct !DILexicalBlock(scope: !211, file: !1, line: 323, column: 6)
!794 = !DILocation(line: 323, column: 6, scope: !211)
!795 = !DILocation(line: 324, column: 22, scope: !796)
!796 = distinct !DILexicalBlock(scope: !793, file: !1, line: 323, column: 11)
!797 = !DILocation(line: 324, column: 25, scope: !796)
!798 = !DILocation(line: 324, column: 3, scope: !796)
!799 = !DILocation(line: 326, column: 13, scope: !796)
!800 = !DILocation(line: 327, column: 3, scope: !796)
!801 = !DILocation(line: 330, column: 31, scope: !211)
!802 = !DILocation(line: 330, column: 34, scope: !211)
!803 = !DILocation(line: 330, column: 8, scope: !211)
!804 = !DILocation(line: 330, column: 6, scope: !211)
!805 = !DILocation(line: 331, column: 6, scope: !806)
!806 = distinct !DILexicalBlock(scope: !211, file: !1, line: 331, column: 6)
!807 = !DILocation(line: 331, column: 10, scope: !806)
!808 = !DILocation(line: 331, column: 6, scope: !211)
!809 = !DILocation(line: 332, column: 13, scope: !810)
!810 = distinct !DILexicalBlock(scope: !806, file: !1, line: 331, column: 25)
!811 = !DILocation(line: 333, column: 3, scope: !810)
!812 = !DILocation(line: 337, column: 31, scope: !211)
!813 = !DILocation(line: 337, column: 34, scope: !211)
!814 = !DILocation(line: 337, column: 40, scope: !211)
!815 = !DILocation(line: 337, column: 8, scope: !211)
!816 = !DILocation(line: 337, column: 6, scope: !211)
!817 = !DILocation(line: 338, column: 6, scope: !818)
!818 = distinct !DILexicalBlock(scope: !211, file: !1, line: 338, column: 6)
!819 = !DILocation(line: 338, column: 10, scope: !818)
!820 = !DILocation(line: 338, column: 6, scope: !211)
!821 = !DILocation(line: 339, column: 13, scope: !822)
!822 = distinct !DILexicalBlock(scope: !818, file: !1, line: 338, column: 25)
!823 = !DILocation(line: 340, column: 3, scope: !822)
!824 = !DILocation(line: 342, column: 8, scope: !211)
!825 = !DILocation(line: 342, column: 6, scope: !211)
!826 = !DILocation(line: 343, column: 6, scope: !827)
!827 = distinct !DILexicalBlock(scope: !211, file: !1, line: 343, column: 6)
!828 = !DILocation(line: 343, column: 6, scope: !211)
!829 = !DILocation(line: 344, column: 32, scope: !830)
!830 = distinct !DILexicalBlock(scope: !827, file: !1, line: 343, column: 11)
!831 = !DILocation(line: 344, column: 45, scope: !830)
!832 = !DILocation(line: 344, column: 9, scope: !830)
!833 = !DILocation(line: 344, column: 7, scope: !830)
!834 = !DILocation(line: 345, column: 7, scope: !835)
!835 = distinct !DILexicalBlock(scope: !830, file: !1, line: 345, column: 7)
!836 = !DILocation(line: 345, column: 11, scope: !835)
!837 = !DILocation(line: 345, column: 7, scope: !830)
!838 = !DILocation(line: 346, column: 14, scope: !839)
!839 = distinct !DILexicalBlock(scope: !835, file: !1, line: 345, column: 26)
!840 = !DILocation(line: 347, column: 4, scope: !839)
!841 = !DILocation(line: 349, column: 2, scope: !830)
!842 = !DILocation(line: 351, column: 51, scope: !211)
!843 = !DILocation(line: 351, column: 32, scope: !211)
!844 = !DILocation(line: 351, column: 2, scope: !211)
!845 = !DILocation(line: 351, column: 8, scope: !211)
!846 = !DILocation(line: 351, column: 30, scope: !211)
!847 = !DILocation(line: 352, column: 23, scope: !211)
!848 = !DILocation(line: 352, column: 18, scope: !211)
!849 = !DILocation(line: 352, column: 2, scope: !211)
!850 = !DILocation(line: 352, column: 8, scope: !211)
!851 = !DILocation(line: 352, column: 16, scope: !211)
!852 = !DILocation(line: 355, column: 6, scope: !853)
!853 = distinct !DILexicalBlock(scope: !211, file: !1, line: 355, column: 6)
!854 = !DILocation(line: 355, column: 8, scope: !853)
!855 = !DILocation(line: 355, column: 17, scope: !853)
!856 = !DILocation(line: 355, column: 22, scope: !857)
!857 = !DILexicalBlockFile(scope: !853, file: !1, discriminator: 1)
!858 = !DILocation(line: 355, column: 21, scope: !857)
!859 = !DILocation(line: 355, column: 24, scope: !857)
!860 = !DILocation(line: 355, column: 6, scope: !857)
!861 = !DILocation(line: 356, column: 32, scope: !862)
!862 = distinct !DILexicalBlock(scope: !853, file: !1, line: 355, column: 33)
!863 = !DILocation(line: 356, column: 35, scope: !862)
!864 = !DILocation(line: 356, column: 45, scope: !862)
!865 = !DILocation(line: 356, column: 38, scope: !862)
!866 = !DILocation(line: 356, column: 9, scope: !867)
!867 = !DILexicalBlockFile(scope: !862, file: !1, discriminator: 1)
!868 = !DILocation(line: 356, column: 7, scope: !862)
!869 = !DILocation(line: 357, column: 7, scope: !870)
!870 = distinct !DILexicalBlock(scope: !862, file: !1, line: 357, column: 7)
!871 = !DILocation(line: 357, column: 11, scope: !870)
!872 = !DILocation(line: 357, column: 7, scope: !862)
!873 = !DILocation(line: 358, column: 14, scope: !874)
!874 = distinct !DILexicalBlock(scope: !870, file: !1, line: 357, column: 26)
!875 = !DILocation(line: 359, column: 4, scope: !874)
!876 = !DILocation(line: 361, column: 9, scope: !862)
!877 = !DILocation(line: 361, column: 7, scope: !862)
!878 = !DILocation(line: 362, column: 32, scope: !862)
!879 = !DILocation(line: 362, column: 45, scope: !862)
!880 = !DILocation(line: 362, column: 9, scope: !862)
!881 = !DILocation(line: 362, column: 7, scope: !862)
!882 = !DILocation(line: 363, column: 7, scope: !883)
!883 = distinct !DILexicalBlock(scope: !862, file: !1, line: 363, column: 7)
!884 = !DILocation(line: 363, column: 11, scope: !883)
!885 = !DILocation(line: 363, column: 7, scope: !862)
!886 = !DILocation(line: 364, column: 14, scope: !887)
!887 = distinct !DILexicalBlock(scope: !883, file: !1, line: 363, column: 26)
!888 = !DILocation(line: 365, column: 4, scope: !887)
!889 = !DILocation(line: 367, column: 2, scope: !862)
!890 = !DILocation(line: 355, column: 27, scope: !891)
!891 = !DILexicalBlockFile(scope: !853, file: !1, discriminator: 2)
!892 = !DILocation(line: 369, column: 6, scope: !893)
!893 = distinct !DILexicalBlock(scope: !211, file: !1, line: 369, column: 6)
!894 = !DILocation(line: 369, column: 6, scope: !211)
!895 = !DILocation(line: 370, column: 22, scope: !893)
!896 = !DILocation(line: 370, column: 3, scope: !893)
!897 = !DILocation(line: 371, column: 10, scope: !211)
!898 = !DILocation(line: 371, column: 2, scope: !211)
!899 = !DILocalVariable(name: "v", arg: 1, scope: !212, file: !1, line: 396, type: !52)
!900 = !DILocation(line: 396, column: 20, scope: !212)
!901 = !DILocalVariable(name: "p", arg: 2, scope: !212, file: !1, line: 396, type: !124)
!902 = !DILocation(line: 396, column: 29, scope: !212)
!903 = !DILocalVariable(name: "digits", arg: 3, scope: !212, file: !1, line: 396, type: !23)
!904 = !DILocation(line: 396, column: 36, scope: !212)
!905 = !DILocalVariable(name: "max", scope: !212, file: !1, line: 398, type: !52)
!906 = !DILocation(line: 398, column: 10, scope: !212)
!907 = !DILocalVariable(name: "ret", scope: !212, file: !1, line: 399, type: !23)
!908 = !DILocation(line: 399, column: 6, scope: !212)
!909 = !DILocation(line: 401, column: 26, scope: !212)
!910 = !DILocation(line: 401, column: 33, scope: !212)
!911 = !DILocation(line: 401, column: 22, scope: !212)
!912 = !DILocation(line: 401, column: 39, scope: !212)
!913 = !DILocation(line: 401, column: 6, scope: !212)
!914 = !DILocation(line: 402, column: 6, scope: !915)
!915 = distinct !DILexicalBlock(scope: !212, file: !1, line: 402, column: 6)
!916 = !DILocation(line: 402, column: 8, scope: !915)
!917 = !DILocation(line: 402, column: 14, scope: !915)
!918 = !DILocation(line: 402, column: 18, scope: !919)
!919 = !DILexicalBlockFile(scope: !915, file: !1, discriminator: 1)
!920 = !DILocation(line: 402, column: 23, scope: !919)
!921 = !DILocation(line: 402, column: 20, scope: !919)
!922 = !DILocation(line: 402, column: 6, scope: !919)
!923 = !DILocation(line: 403, column: 27, scope: !924)
!924 = distinct !DILexicalBlock(scope: !915, file: !1, line: 402, column: 28)
!925 = !DILocation(line: 403, column: 38, scope: !924)
!926 = !DILocation(line: 403, column: 41, scope: !924)
!927 = !DILocation(line: 403, column: 6, scope: !924)
!928 = !DILocation(line: 404, column: 10, scope: !924)
!929 = !DILocation(line: 405, column: 2, scope: !924)
!930 = !DILocation(line: 406, column: 27, scope: !931)
!931 = distinct !DILexicalBlock(scope: !915, file: !1, line: 405, column: 9)
!932 = !DILocation(line: 406, column: 40, scope: !931)
!933 = !DILocation(line: 406, column: 43, scope: !931)
!934 = !DILocation(line: 406, column: 6, scope: !931)
!935 = !DILocation(line: 407, column: 10, scope: !931)
!936 = !DILocation(line: 409, column: 10, scope: !212)
!937 = !DILocation(line: 409, column: 2, scope: !212)
!938 = !DILocalVariable(name: "v", arg: 1, scope: !215, file: !1, line: 413, type: !52)
!939 = !DILocation(line: 413, column: 30, scope: !215)
!940 = !DILocalVariable(name: "p", arg: 2, scope: !215, file: !1, line: 413, type: !95)
!941 = !DILocation(line: 413, column: 39, scope: !215)
!942 = !DILocalVariable(name: "s", arg: 3, scope: !215, file: !1, line: 413, type: !23)
!943 = !DILocation(line: 413, column: 46, scope: !215)
!944 = !DILocation(line: 415, column: 6, scope: !945)
!945 = distinct !DILexicalBlock(scope: !215, file: !1, line: 415, column: 6)
!946 = !DILocation(line: 415, column: 8, scope: !945)
!947 = !DILocation(line: 415, column: 6, scope: !215)
!948 = !DILocation(line: 416, column: 11, scope: !945)
!949 = !DILocation(line: 416, column: 3, scope: !945)
!950 = !DILocation(line: 417, column: 27, scope: !215)
!951 = !DILocation(line: 417, column: 30, scope: !215)
!952 = !DILocation(line: 417, column: 31, scope: !215)
!953 = !DILocation(line: 417, column: 35, scope: !215)
!954 = !DILocation(line: 417, column: 36, scope: !215)
!955 = !DILocation(line: 417, column: 6, scope: !215)
!956 = !DILocation(line: 417, column: 4, scope: !215)
!957 = !DILocation(line: 418, column: 26, scope: !215)
!958 = !DILocation(line: 418, column: 28, scope: !215)
!959 = !DILocation(line: 418, column: 7, scope: !215)
!960 = !DILocation(line: 418, column: 3, scope: !215)
!961 = !DILocation(line: 418, column: 5, scope: !215)
!962 = !DILocation(line: 419, column: 10, scope: !215)
!963 = !DILocation(line: 419, column: 12, scope: !215)
!964 = !DILocation(line: 419, column: 2, scope: !215)
!965 = !DILocation(line: 420, column: 1, scope: !215)
