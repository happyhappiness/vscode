; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_cpio.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.cpio = type { i64, i64, %struct.anon*, i64, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }
%struct.anon = type { i64, i32 }

@.str = private unnamed_addr constant [30 x i8] c"archive_write_set_format_cpio\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate cpio data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"cpio\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"POSIX cpio\00", align 1
@.str.4 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.5 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"Filetype required\00", align 1
@.str.7 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.8 = private unnamed_addr constant [18 x i8] c"Pathname required\00", align 1
@.str.9 = private unnamed_addr constant [14 x i8] c"Size required\00", align 1
@.str.10 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.11 = private unnamed_addr constant [36 x i8] c"No memory for ino translation table\00", align 1
@.str.12 = private unnamed_addr constant [36 x i8] c"Too many files for this cpio format\00", align 1
@.str.13 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.14 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.15 = private unnamed_addr constant [35 x i8] c"File is too large for cpio format.\00", align 1
@.str.16 = private unnamed_addr constant [11 x i8] c"TRAILER!!!\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_cpio(%struct.archive* %_a) #0 !dbg !213 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !236, metadata !237), !dbg !238
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !239, metadata !237), !dbg !240
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !241
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !242
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !240
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !243, metadata !237), !dbg !244
  br label %do.body, !dbg !245

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !246, metadata !237), !dbg !248
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !249
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !249
  store i32 %call, i32* %magic_test, align 4, !dbg !249
  %3 = load i32, i32* %magic_test, align 4, !dbg !249
  %cmp = icmp eq i32 %3, -30, !dbg !249
  br i1 %cmp, label %if.then, label %if.end, !dbg !249

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !251
  br label %return, !dbg !251

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !254

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !256
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !258
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !258
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !259
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !260

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !261
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !262
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !262
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !263
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !264
  br label %if.end5, !dbg !264

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 64) #7, !dbg !265
  %9 = bitcast i8* %call6 to %struct.cpio*, !dbg !266
  store %struct.cpio* %9, %struct.cpio** %cpio, align 8, !dbg !267
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !268
  %cmp7 = icmp eq %struct.cpio* %10, null, !dbg !270
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !271

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !272
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !274
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !275
  store i32 -30, i32* %retval, align 4, !dbg !276
  br label %return, !dbg !276

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !277
  %13 = bitcast %struct.cpio* %12 to i8*, !dbg !277
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !278
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 14, !dbg !279
  store i8* %13, i8** %format_data, align 8, !dbg !280
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !281
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 15, !dbg !282
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !283
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !284
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 17, !dbg !285
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_cpio_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !286
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !287
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 19, !dbg !288
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_cpio_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !289
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !290
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 20, !dbg !291
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_cpio_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !292
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !293
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 18, !dbg !294
  store i32 (%struct.archive_write*)* @archive_write_cpio_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !295
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !296
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 21, !dbg !297
  store i32 (%struct.archive_write*)* @archive_write_cpio_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !298
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !299
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 22, !dbg !300
  store i32 (%struct.archive_write*)* @archive_write_cpio_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !301
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !302
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 0, !dbg !303
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !304
  store i32 65537, i32* %archive_format, align 8, !dbg !305
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !306
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !307
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !308
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !309
  store i32 0, i32* %retval, align 4, !dbg !310
  br label %return, !dbg !310

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !311
  ret i32 %24, !dbg !311
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_cpio_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !214 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !312, metadata !237), !dbg !313
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !314, metadata !237), !dbg !315
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !316, metadata !237), !dbg !317
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !318, metadata !237), !dbg !319
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !320
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !321
  %1 = load i8*, i8** %format_data, align 8, !dbg !321
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !322
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !319
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !323, metadata !237), !dbg !324
  store i32 -25, i32* %ret, align 4, !dbg !324
  %3 = load i8*, i8** %key.addr, align 8, !dbg !325
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.4, i32 0, i32 0)) #8, !dbg !327
  %cmp = icmp eq i32 %call, 0, !dbg !328
  br i1 %cmp, label %if.then, label %if.end13, !dbg !329

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !330
  %cmp1 = icmp eq i8* %4, null, !dbg !333
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !334

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !335
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !335
  %6 = load i8, i8* %arrayidx, align 1, !dbg !335
  %conv = sext i8 %6 to i32, !dbg !335
  %cmp2 = icmp eq i32 %conv, 0, !dbg !337
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !338

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !339
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !340
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !341
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !342
  %9 = load i8*, i8** %format_name, align 8, !dbg !342
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.5, i32 0, i32 0), i8* %9), !dbg !343
  br label %if.end12, !dbg !343

if.else:                                          ; preds = %lor.lhs.false
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !344
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !346
  %11 = load i8*, i8** %val.addr, align 8, !dbg !347
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive5, i8* %11, i32 0), !dbg !348
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !349
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 5, !dbg !350
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !351
  %13 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !352
  %opt_sconv7 = getelementptr inbounds %struct.cpio, %struct.cpio* %13, i32 0, i32 5, !dbg !354
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !354
  %cmp8 = icmp ne %struct.archive_string_conv* %14, null, !dbg !355
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !356

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !357
  br label %if.end, !dbg !358

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !359
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %15 = load i32, i32* %ret, align 4, !dbg !360
  store i32 %15, i32* %retval, align 4, !dbg !361
  br label %return, !dbg !361

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !362
  br label %return, !dbg !362

return:                                           ; preds = %if.end13, %if.end12
  %16 = load i32, i32* %retval, align 4, !dbg !363
  ret i32 %16, !dbg !363
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_cpio_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %path = alloca i8*, align 8
  %len = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !364, metadata !237), !dbg !365
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !366, metadata !237), !dbg !367
  call void @llvm.dbg.declare(metadata i8** %path, metadata !368, metadata !237), !dbg !369
  call void @llvm.dbg.declare(metadata i64* %len, metadata !370, metadata !237), !dbg !371
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !372
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %0), !dbg !374
  %cmp = icmp eq i32 %call, 0, !dbg !375
  br i1 %cmp, label %if.then, label %if.end, !dbg !376

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !377
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %1, i32 0, i32 0, !dbg !379
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0)), !dbg !380
  store i32 -25, i32* %retval, align 4, !dbg !381
  br label %return, !dbg !381

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !382
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !384
  %call2 = call %struct.archive_string_conv* @get_sconv(%struct.archive_write* %3), !dbg !385
  %call3 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %2, i8** %path, i64* %len, %struct.archive_string_conv* %call2), !dbg !386
  %cmp4 = icmp ne i32 %call3, 0, !dbg !388
  br i1 %cmp4, label %land.lhs.true, label %if.end9, !dbg !389

land.lhs.true:                                    ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !390
  %4 = load i32, i32* %call5, align 4, !dbg !390
  %cmp6 = icmp eq i32 %4, 12, !dbg !392
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !393

if.then7:                                         ; preds = %land.lhs.true
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !395
  %archive8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !397
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive8, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !398
  store i32 -30, i32* %retval, align 4, !dbg !399
  br label %return, !dbg !399

if.end9:                                          ; preds = %land.lhs.true, %if.end
  %6 = load i64, i64* %len, align 8, !dbg !400
  %cmp10 = icmp eq i64 %6, 0, !dbg !402
  br i1 %cmp10, label %if.then15, label %lor.lhs.false, !dbg !403

lor.lhs.false:                                    ; preds = %if.end9
  %7 = load i8*, i8** %path, align 8, !dbg !404
  %cmp11 = icmp eq i8* %7, null, !dbg !406
  br i1 %cmp11, label %if.then15, label %lor.lhs.false12, !dbg !407

lor.lhs.false12:                                  ; preds = %lor.lhs.false
  %8 = load i8*, i8** %path, align 8, !dbg !408
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 0, !dbg !408
  %9 = load i8, i8* %arrayidx, align 1, !dbg !408
  %conv = sext i8 %9 to i32, !dbg !408
  %cmp13 = icmp eq i32 %conv, 0, !dbg !410
  br i1 %cmp13, label %if.then15, label %if.end17, !dbg !411

if.then15:                                        ; preds = %lor.lhs.false12, %lor.lhs.false, %if.end9
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !412
  %archive16 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !414
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.8, i32 0, i32 0)), !dbg !415
  store i32 -25, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

if.end17:                                         ; preds = %lor.lhs.false12
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !417
  %call18 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %11), !dbg !419
  %tobool = icmp ne i32 %call18, 0, !dbg !419
  br i1 %tobool, label %lor.lhs.false19, label %if.then23, !dbg !420

lor.lhs.false19:                                  ; preds = %if.end17
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !421
  %call20 = call i64 @archive_entry_size(%struct.archive_entry* %12), !dbg !423
  %cmp21 = icmp slt i64 %call20, 0, !dbg !424
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !425

if.then23:                                        ; preds = %lor.lhs.false19, %if.end17
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !426
  %archive24 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 0, !dbg !428
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive24, i32 -1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0)), !dbg !429
  store i32 -25, i32* %retval, align 4, !dbg !430
  br label %return, !dbg !430

if.end25:                                         ; preds = %lor.lhs.false19
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !431
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !432
  %call26 = call i32 @write_header(%struct.archive_write* %14, %struct.archive_entry* %15), !dbg !433
  store i32 %call26, i32* %retval, align 4, !dbg !434
  br label %return, !dbg !434

return:                                           ; preds = %if.end25, %if.then23, %if.then15, %if.then7, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !435
  ret i32 %16, !dbg !435
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_cpio_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !229 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %cpio = alloca %struct.cpio*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !436, metadata !237), !dbg !437
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !438, metadata !237), !dbg !439
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !440, metadata !237), !dbg !441
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !442, metadata !237), !dbg !443
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !444, metadata !237), !dbg !445
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !446
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !447
  %1 = load i8*, i8** %format_data, align 8, !dbg !447
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !448
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !449
  %3 = load i64, i64* %s.addr, align 8, !dbg !450
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !452
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 0, !dbg !453
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !453
  %cmp = icmp ugt i64 %3, %5, !dbg !454
  br i1 %cmp, label %if.then, label %if.end, !dbg !455

if.then:                                          ; preds = %entry
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !456
  %entry_bytes_remaining1 = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 0, !dbg !457
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !457
  store i64 %7, i64* %s.addr, align 8, !dbg !458
  br label %if.end, !dbg !459

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !460
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !461
  %10 = load i64, i64* %s.addr, align 8, !dbg !462
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %9, i64 %10), !dbg !463
  store i32 %call, i32* %ret, align 4, !dbg !464
  %11 = load i64, i64* %s.addr, align 8, !dbg !465
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !466
  %entry_bytes_remaining2 = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 0, !dbg !467
  %13 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !468
  %sub = sub i64 %13, %11, !dbg !468
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !468
  %14 = load i32, i32* %ret, align 4, !dbg !469
  %cmp3 = icmp sge i32 %14, 0, !dbg !471
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !472

if.then4:                                         ; preds = %if.end
  %15 = load i64, i64* %s.addr, align 8, !dbg !473
  store i64 %15, i64* %retval, align 8, !dbg !474
  br label %return, !dbg !474

if.else:                                          ; preds = %if.end
  %16 = load i32, i32* %ret, align 4, !dbg !475
  %conv = sext i32 %16 to i64, !dbg !476
  store i64 %conv, i64* %retval, align 8, !dbg !477
  br label %return, !dbg !477

return:                                           ; preds = %if.else, %if.then4
  %17 = load i64, i64* %retval, align 8, !dbg !478
  ret i64 %17, !dbg !478
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_cpio_finish_entry(%struct.archive_write* %a) #0 !dbg !232 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !479, metadata !237), !dbg !480
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !481, metadata !237), !dbg !482
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !483
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !484
  %1 = load i8*, i8** %format_data, align 8, !dbg !484
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !485
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !486
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !487
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !488
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 0, !dbg !489
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !489
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %3, i64 %5), !dbg !490
  ret i32 %call, !dbg !491
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_cpio_close(%struct.archive_write* %a) #0 !dbg !230 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %er = alloca i32, align 4
  %trailer = alloca %struct.archive_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !492, metadata !237), !dbg !493
  call void @llvm.dbg.declare(metadata i32* %er, metadata !494, metadata !237), !dbg !495
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %trailer, metadata !496, metadata !237), !dbg !497
  %call = call %struct.archive_entry* @archive_entry_new2(%struct.archive* null), !dbg !498
  store %struct.archive_entry* %call, %struct.archive_entry** %trailer, align 8, !dbg !499
  %0 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !500
  call void @archive_entry_set_nlink(%struct.archive_entry* %0, i32 1), !dbg !501
  %1 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !502
  call void @archive_entry_set_size(%struct.archive_entry* %1, i64 0), !dbg !503
  %2 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !504
  call void @archive_entry_set_pathname(%struct.archive_entry* %2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.16, i32 0, i32 0)), !dbg !505
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !506
  %4 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !507
  %call1 = call i32 @write_header(%struct.archive_write* %3, %struct.archive_entry* %4), !dbg !508
  store i32 %call1, i32* %er, align 4, !dbg !509
  %5 = load %struct.archive_entry*, %struct.archive_entry** %trailer, align 8, !dbg !510
  call void @archive_entry_free(%struct.archive_entry* %5), !dbg !511
  %6 = load i32, i32* %er, align 4, !dbg !512
  ret i32 %6, !dbg !513
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_cpio_free(%struct.archive_write* %a) #0 !dbg !231 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !514, metadata !237), !dbg !515
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !516, metadata !237), !dbg !517
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !518
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !519
  %1 = load i8*, i8** %format_data, align 8, !dbg !519
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !520
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !521
  %3 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !522
  %ino_list = getelementptr inbounds %struct.cpio, %struct.cpio* %3, i32 0, i32 2, !dbg !523
  %4 = load %struct.anon*, %struct.anon** %ino_list, align 8, !dbg !523
  %5 = bitcast %struct.anon* %4 to i8*, !dbg !522
  call void @free(i8* %5) #7, !dbg !524
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !525
  %7 = bitcast %struct.cpio* %6 to i8*, !dbg !525
  call void @free(i8* %7) #7, !dbg !526
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !527
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 14, !dbg !528
  store i8* null, i8** %format_data1, align 8, !dbg !529
  ret i32 0, !dbg !530
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal %struct.archive_string_conv* @get_sconv(%struct.archive_write* %a) #0 !dbg !216 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !531, metadata !237), !dbg !532
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !533, metadata !237), !dbg !534
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !535, metadata !237), !dbg !536
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !537
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !538
  %1 = load i8*, i8** %format_data, align 8, !dbg !538
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !539
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !540
  %3 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !541
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %3, i32 0, i32 5, !dbg !542
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !542
  store %struct.archive_string_conv* %4, %struct.archive_string_conv** %sconv, align 8, !dbg !543
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !544
  %cmp = icmp eq %struct.archive_string_conv* %5, null, !dbg !546
  br i1 %cmp, label %if.then, label %if.end4, !dbg !547

if.then:                                          ; preds = %entry
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !548
  %init_default_conversion = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 7, !dbg !551
  %7 = load i32, i32* %init_default_conversion, align 8, !dbg !551
  %tobool = icmp ne i32 %7, 0, !dbg !548
  br i1 %tobool, label %if.end, label %if.then1, !dbg !552

if.then1:                                         ; preds = %if.then
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !553
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !555
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !556
  %9 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !557
  %sconv_default = getelementptr inbounds %struct.cpio, %struct.cpio* %9, i32 0, i32 6, !dbg !558
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !559
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !560
  %init_default_conversion2 = getelementptr inbounds %struct.cpio, %struct.cpio* %10, i32 0, i32 7, !dbg !561
  store i32 1, i32* %init_default_conversion2, align 8, !dbg !562
  br label %if.end, !dbg !563

if.end:                                           ; preds = %if.then1, %if.then
  %11 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !564
  %sconv_default3 = getelementptr inbounds %struct.cpio, %struct.cpio* %11, i32 0, i32 6, !dbg !565
  %12 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default3, align 8, !dbg !565
  store %struct.archive_string_conv* %12, %struct.archive_string_conv** %sconv, align 8, !dbg !566
  br label %if.end4, !dbg !567

if.end4:                                          ; preds = %if.end, %entry
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !568
  ret %struct.archive_string_conv* %13, !dbg !569
}

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i32 @archive_entry_size_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @write_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !219 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %p = alloca i8*, align 8
  %path = alloca i8*, align 8
  %pathlength = alloca i32, align 4
  %ret = alloca i32, align 4
  %ret_final = alloca i32, align 4
  %ino = alloca i64, align 8
  %h = alloca [76 x i8], align 16
  %sconv = alloca %struct.archive_string_conv*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %len = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !570, metadata !237), !dbg !571
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !572, metadata !237), !dbg !573
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !574, metadata !237), !dbg !575
  call void @llvm.dbg.declare(metadata i8** %p, metadata !576, metadata !237), !dbg !577
  call void @llvm.dbg.declare(metadata i8** %path, metadata !578, metadata !237), !dbg !579
  call void @llvm.dbg.declare(metadata i32* %pathlength, metadata !580, metadata !237), !dbg !581
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !582, metadata !237), !dbg !583
  call void @llvm.dbg.declare(metadata i32* %ret_final, metadata !584, metadata !237), !dbg !585
  call void @llvm.dbg.declare(metadata i64* %ino, metadata !586, metadata !237), !dbg !587
  call void @llvm.dbg.declare(metadata [76 x i8]* %h, metadata !588, metadata !237), !dbg !592
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !593, metadata !237), !dbg !594
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !595, metadata !237), !dbg !596
  call void @llvm.dbg.declare(metadata i64* %len, metadata !597, metadata !237), !dbg !598
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !599
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !600
  %1 = load i8*, i8** %format_data, align 8, !dbg !600
  %2 = bitcast i8* %1 to %struct.cpio*, !dbg !601
  store %struct.cpio* %2, %struct.cpio** %cpio, align 8, !dbg !602
  store i32 0, i32* %ret_final, align 4, !dbg !603
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !604
  %call = call %struct.archive_string_conv* @get_sconv(%struct.archive_write* %3), !dbg !605
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv, align 8, !dbg !606
  store %struct.archive_entry* null, %struct.archive_entry** %entry_main, align 8, !dbg !607
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !608
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !609
  %call2 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %4, i8** %path, i64* %len, %struct.archive_string_conv* %5), !dbg !610
  store i32 %call2, i32* %ret, align 4, !dbg !611
  %6 = load i32, i32* %ret, align 4, !dbg !612
  %cmp = icmp ne i32 %6, 0, !dbg !614
  br i1 %cmp, label %if.then, label %if.end9, !dbg !615

if.then:                                          ; preds = %entry
  %call3 = call i32* @__errno_location() #1, !dbg !616
  %7 = load i32, i32* %call3, align 4, !dbg !616
  %cmp4 = icmp eq i32 %7, 12, !dbg !619
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !620

if.then5:                                         ; preds = %if.then
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !621
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !623
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0)), !dbg !624
  store i32 -30, i32* %ret_final, align 4, !dbg !625
  br label %exit_write_header, !dbg !626

if.end:                                           ; preds = %if.then
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !627
  %archive6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !628
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !629
  %call7 = call i8* @archive_entry_pathname(%struct.archive_entry* %10), !dbg !630
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !631
  %call8 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %11), !dbg !632
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.10, i32 0, i32 0), i8* %call7, i8* %call8), !dbg !633
  store i32 -20, i32* %ret_final, align 4, !dbg !634
  br label %if.end9, !dbg !635

if.end9:                                          ; preds = %if.end, %entry
  %12 = load i64, i64* %len, align 8, !dbg !636
  %conv = trunc i64 %12 to i32, !dbg !637
  %add = add nsw i32 %conv, 1, !dbg !638
  store i32 %add, i32* %pathlength, align 4, !dbg !639
  %arraydecay = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !640
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 76, i32 16, i1 false), !dbg !640
  %arraydecay10 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !641
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay10, i64 0, !dbg !642
  %call11 = call i32 @format_octal(i64 29127, i8* %add.ptr, i32 6), !dbg !643
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !644
  %call12 = call i64 @archive_entry_dev(%struct.archive_entry* %13), !dbg !645
  %arraydecay13 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !646
  %add.ptr14 = getelementptr inbounds i8, i8* %arraydecay13, i64 6, !dbg !647
  %call15 = call i32 @format_octal(i64 %call12, i8* %add.ptr14, i32 6), !dbg !648
  %14 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !650
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !651
  %call16 = call i32 @synthesize_ino_value(%struct.cpio* %14, %struct.archive_entry* %15), !dbg !652
  %conv17 = sext i32 %call16 to i64, !dbg !652
  store i64 %conv17, i64* %ino, align 8, !dbg !653
  %16 = load i64, i64* %ino, align 8, !dbg !654
  %cmp18 = icmp slt i64 %16, 0, !dbg !656
  br i1 %cmp18, label %if.then20, label %if.else, !dbg !657

if.then20:                                        ; preds = %if.end9
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !658
  %archive21 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 0, !dbg !660
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive21, i32 12, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.11, i32 0, i32 0)), !dbg !661
  store i32 -30, i32* %ret_final, align 4, !dbg !662
  br label %exit_write_header, !dbg !663

if.else:                                          ; preds = %if.end9
  %18 = load i64, i64* %ino, align 8, !dbg !664
  %cmp22 = icmp sgt i64 %18, 262143, !dbg !666
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !667

if.then24:                                        ; preds = %if.else
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !668
  %archive25 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !670
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 34, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.12, i32 0, i32 0)), !dbg !671
  store i32 -30, i32* %ret_final, align 4, !dbg !672
  br label %exit_write_header, !dbg !673

if.end26:                                         ; preds = %if.else
  br label %if.end27

if.end27:                                         ; preds = %if.end26
  %20 = load i64, i64* %ino, align 8, !dbg !674
  %and = and i64 %20, 262143, !dbg !675
  %arraydecay28 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !676
  %add.ptr29 = getelementptr inbounds i8, i8* %arraydecay28, i64 12, !dbg !677
  %call30 = call i32 @format_octal(i64 %and, i8* %add.ptr29, i32 6), !dbg !678
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !679
  %call31 = call i32 @archive_entry_mode(%struct.archive_entry* %21), !dbg !680
  %conv32 = zext i32 %call31 to i64, !dbg !680
  %arraydecay33 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !681
  %add.ptr34 = getelementptr inbounds i8, i8* %arraydecay33, i64 18, !dbg !682
  %call35 = call i32 @format_octal(i64 %conv32, i8* %add.ptr34, i32 6), !dbg !683
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !684
  %call36 = call i64 @archive_entry_uid(%struct.archive_entry* %22), !dbg !685
  %arraydecay37 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !686
  %add.ptr38 = getelementptr inbounds i8, i8* %arraydecay37, i64 24, !dbg !687
  %call39 = call i32 @format_octal(i64 %call36, i8* %add.ptr38, i32 6), !dbg !688
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !689
  %call40 = call i64 @archive_entry_gid(%struct.archive_entry* %23), !dbg !690
  %arraydecay41 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !691
  %add.ptr42 = getelementptr inbounds i8, i8* %arraydecay41, i64 30, !dbg !692
  %call43 = call i32 @format_octal(i64 %call40, i8* %add.ptr42, i32 6), !dbg !693
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !694
  %call44 = call i32 @archive_entry_nlink(%struct.archive_entry* %24), !dbg !695
  %conv45 = zext i32 %call44 to i64, !dbg !695
  %arraydecay46 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !696
  %add.ptr47 = getelementptr inbounds i8, i8* %arraydecay46, i64 36, !dbg !697
  %call48 = call i32 @format_octal(i64 %conv45, i8* %add.ptr47, i32 6), !dbg !698
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !699
  %call49 = call i32 @archive_entry_filetype(%struct.archive_entry* %25), !dbg !701
  %cmp50 = icmp eq i32 %call49, 24576, !dbg !702
  br i1 %cmp50, label %if.then55, label %lor.lhs.false, !dbg !703

lor.lhs.false:                                    ; preds = %if.end27
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !704
  %call52 = call i32 @archive_entry_filetype(%struct.archive_entry* %26), !dbg !706
  %cmp53 = icmp eq i32 %call52, 8192, !dbg !707
  br i1 %cmp53, label %if.then55, label %if.else60, !dbg !708

if.then55:                                        ; preds = %lor.lhs.false, %if.end27
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !709
  %call56 = call i64 @archive_entry_dev(%struct.archive_entry* %27), !dbg !710
  %arraydecay57 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !711
  %add.ptr58 = getelementptr inbounds i8, i8* %arraydecay57, i64 42, !dbg !712
  %call59 = call i32 @format_octal(i64 %call56, i8* %add.ptr58, i32 6), !dbg !713
  br label %if.end64, !dbg !714

if.else60:                                        ; preds = %lor.lhs.false
  %arraydecay61 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !715
  %add.ptr62 = getelementptr inbounds i8, i8* %arraydecay61, i64 42, !dbg !716
  %call63 = call i32 @format_octal(i64 0, i8* %add.ptr62, i32 6), !dbg !717
  br label %if.end64

if.end64:                                         ; preds = %if.else60, %if.then55
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !718
  %call65 = call i64 @archive_entry_mtime(%struct.archive_entry* %28), !dbg !719
  %arraydecay66 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !720
  %add.ptr67 = getelementptr inbounds i8, i8* %arraydecay66, i64 48, !dbg !721
  %call68 = call i32 @format_octal(i64 %call65, i8* %add.ptr67, i32 11), !dbg !722
  %29 = load i32, i32* %pathlength, align 4, !dbg !723
  %conv69 = sext i32 %29 to i64, !dbg !723
  %arraydecay70 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !724
  %add.ptr71 = getelementptr inbounds i8, i8* %arraydecay70, i64 59, !dbg !725
  %call72 = call i32 @format_octal(i64 %conv69, i8* %add.ptr71, i32 6), !dbg !726
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !727
  %call73 = call i32 @archive_entry_filetype(%struct.archive_entry* %30), !dbg !729
  %cmp74 = icmp ne i32 %call73, 32768, !dbg !730
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !731

if.then76:                                        ; preds = %if.end64
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !732
  call void @archive_entry_set_size(%struct.archive_entry* %31, i64 0), !dbg !733
  br label %if.end77, !dbg !733

if.end77:                                         ; preds = %if.then76, %if.end64
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !734
  %33 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !735
  %call78 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %32, i8** %p, i64* %len, %struct.archive_string_conv* %33), !dbg !736
  store i32 %call78, i32* %ret, align 4, !dbg !737
  %34 = load i32, i32* %ret, align 4, !dbg !738
  %cmp79 = icmp ne i32 %34, 0, !dbg !740
  br i1 %cmp79, label %if.then81, label %if.end91, !dbg !741

if.then81:                                        ; preds = %if.end77
  %call82 = call i32* @__errno_location() #1, !dbg !742
  %35 = load i32, i32* %call82, align 4, !dbg !742
  %cmp83 = icmp eq i32 %35, 12, !dbg !745
  br i1 %cmp83, label %if.then85, label %if.end87, !dbg !746

if.then85:                                        ; preds = %if.then81
  %36 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !747
  %archive86 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %36, i32 0, i32 0, !dbg !749
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive86, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.13, i32 0, i32 0)), !dbg !750
  store i32 -30, i32* %ret_final, align 4, !dbg !751
  br label %exit_write_header, !dbg !752

if.end87:                                         ; preds = %if.then81
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !753
  %archive88 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %37, i32 0, i32 0, !dbg !754
  %38 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !755
  %call89 = call i8* @archive_entry_symlink(%struct.archive_entry* %38), !dbg !756
  %39 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !757
  %call90 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %39), !dbg !758
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive88, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.14, i32 0, i32 0), i8* %call89, i8* %call90), !dbg !759
  store i32 -20, i32* %ret_final, align 4, !dbg !760
  br label %if.end91, !dbg !761

if.end91:                                         ; preds = %if.end87, %if.end77
  %40 = load i64, i64* %len, align 8, !dbg !762
  %cmp92 = icmp ugt i64 %40, 0, !dbg !764
  br i1 %cmp92, label %land.lhs.true, label %if.else105, !dbg !765

land.lhs.true:                                    ; preds = %if.end91
  %41 = load i8*, i8** %p, align 8, !dbg !766
  %cmp94 = icmp ne i8* %41, null, !dbg !768
  br i1 %cmp94, label %land.lhs.true96, label %if.else105, !dbg !769

land.lhs.true96:                                  ; preds = %land.lhs.true
  %42 = load i8*, i8** %p, align 8, !dbg !770
  %43 = load i8, i8* %42, align 1, !dbg !772
  %conv97 = sext i8 %43 to i32, !dbg !772
  %cmp98 = icmp ne i32 %conv97, 0, !dbg !773
  br i1 %cmp98, label %if.then100, label %if.else105, !dbg !774

if.then100:                                       ; preds = %land.lhs.true96
  %44 = load i8*, i8** %p, align 8, !dbg !775
  %call101 = call i64 @strlen(i8* %44) #8, !dbg !776
  %arraydecay102 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !777
  %add.ptr103 = getelementptr inbounds i8, i8* %arraydecay102, i64 65, !dbg !778
  %call104 = call i32 @format_octal(i64 %call101, i8* %add.ptr103, i32 11), !dbg !779
  store i32 %call104, i32* %ret, align 4, !dbg !780
  br label %if.end110, !dbg !781

if.else105:                                       ; preds = %land.lhs.true96, %land.lhs.true, %if.end91
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !782
  %call106 = call i64 @archive_entry_size(%struct.archive_entry* %45), !dbg !783
  %arraydecay107 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !784
  %add.ptr108 = getelementptr inbounds i8, i8* %arraydecay107, i64 65, !dbg !785
  %call109 = call i32 @format_octal(i64 %call106, i8* %add.ptr108, i32 11), !dbg !786
  store i32 %call109, i32* %ret, align 4, !dbg !787
  br label %if.end110

if.end110:                                        ; preds = %if.else105, %if.then100
  %46 = load i32, i32* %ret, align 4, !dbg !788
  %tobool = icmp ne i32 %46, 0, !dbg !788
  br i1 %tobool, label %if.then111, label %if.end113, !dbg !790

if.then111:                                       ; preds = %if.end110
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !791
  %archive112 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %47, i32 0, i32 0, !dbg !793
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive112, i32 34, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.15, i32 0, i32 0)), !dbg !794
  store i32 -25, i32* %ret_final, align 4, !dbg !795
  br label %exit_write_header, !dbg !796

if.end113:                                        ; preds = %if.end110
  %48 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !797
  %arraydecay114 = getelementptr inbounds [76 x i8], [76 x i8]* %h, i32 0, i32 0, !dbg !798
  %call115 = call i32 @__archive_write_output(%struct.archive_write* %48, i8* %arraydecay114, i64 76), !dbg !799
  store i32 %call115, i32* %ret, align 4, !dbg !800
  %49 = load i32, i32* %ret, align 4, !dbg !801
  %cmp116 = icmp ne i32 %49, 0, !dbg !803
  br i1 %cmp116, label %if.then118, label %if.end119, !dbg !804

if.then118:                                       ; preds = %if.end113
  store i32 -30, i32* %ret_final, align 4, !dbg !805
  br label %exit_write_header, !dbg !807

if.end119:                                        ; preds = %if.end113
  %50 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !808
  %51 = load i8*, i8** %path, align 8, !dbg !809
  %52 = load i32, i32* %pathlength, align 4, !dbg !810
  %conv120 = sext i32 %52 to i64, !dbg !810
  %call121 = call i32 @__archive_write_output(%struct.archive_write* %50, i8* %51, i64 %conv120), !dbg !811
  store i32 %call121, i32* %ret, align 4, !dbg !812
  %53 = load i32, i32* %ret, align 4, !dbg !813
  %cmp122 = icmp ne i32 %53, 0, !dbg !815
  br i1 %cmp122, label %if.then124, label %if.end125, !dbg !816

if.then124:                                       ; preds = %if.end119
  store i32 -30, i32* %ret_final, align 4, !dbg !817
  br label %exit_write_header, !dbg !819

if.end125:                                        ; preds = %if.end119
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !820
  %call126 = call i64 @archive_entry_size(%struct.archive_entry* %54), !dbg !821
  %55 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !822
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %55, i32 0, i32 0, !dbg !823
  store i64 %call126, i64* %entry_bytes_remaining, align 8, !dbg !824
  %56 = load i8*, i8** %p, align 8, !dbg !825
  %cmp127 = icmp ne i8* %56, null, !dbg !827
  br i1 %cmp127, label %land.lhs.true129, label %if.end140, !dbg !828

land.lhs.true129:                                 ; preds = %if.end125
  %57 = load i8*, i8** %p, align 8, !dbg !829
  %58 = load i8, i8* %57, align 1, !dbg !831
  %conv130 = sext i8 %58 to i32, !dbg !831
  %cmp131 = icmp ne i32 %conv130, 0, !dbg !832
  br i1 %cmp131, label %if.then133, label %if.end140, !dbg !833

if.then133:                                       ; preds = %land.lhs.true129
  %59 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !834
  %60 = load i8*, i8** %p, align 8, !dbg !836
  %61 = load i8*, i8** %p, align 8, !dbg !837
  %call134 = call i64 @strlen(i8* %61) #8, !dbg !838
  %call135 = call i32 @__archive_write_output(%struct.archive_write* %59, i8* %60, i64 %call134), !dbg !839
  store i32 %call135, i32* %ret, align 4, !dbg !841
  %62 = load i32, i32* %ret, align 4, !dbg !842
  %cmp136 = icmp ne i32 %62, 0, !dbg !844
  br i1 %cmp136, label %if.then138, label %if.end139, !dbg !845

if.then138:                                       ; preds = %if.then133
  store i32 -30, i32* %ret_final, align 4, !dbg !846
  br label %exit_write_header, !dbg !848

if.end139:                                        ; preds = %if.then133
  br label %if.end140, !dbg !849

if.end140:                                        ; preds = %if.end139, %land.lhs.true129, %if.end125
  br label %exit_write_header, !dbg !850

exit_write_header:                                ; preds = %if.end140, %if.then138, %if.then124, %if.then118, %if.then111, %if.then85, %if.then24, %if.then20, %if.then5
  %63 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !852
  %tobool141 = icmp ne %struct.archive_entry* %63, null, !dbg !852
  br i1 %tobool141, label %if.then142, label %if.end143, !dbg !854

if.then142:                                       ; preds = %exit_write_header
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !855
  call void @archive_entry_free(%struct.archive_entry* %64), !dbg !856
  br label %if.end143, !dbg !856

if.end143:                                        ; preds = %if.then142, %exit_write_header
  %65 = load i32, i32* %ret_final, align 4, !dbg !857
  ret i32 %65, !dbg !858
}

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @format_octal(i64 %v, i8* %p, i32 %digits) #0 !dbg !220 {
entry:
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %digits.addr = alloca i32, align 4
  %max = alloca i64, align 8
  %ret = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !859, metadata !237), !dbg !860
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !861, metadata !237), !dbg !862
  store i32 %digits, i32* %digits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %digits.addr, metadata !863, metadata !237), !dbg !864
  call void @llvm.dbg.declare(metadata i64* %max, metadata !865, metadata !237), !dbg !866
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !867, metadata !237), !dbg !868
  %0 = load i32, i32* %digits.addr, align 4, !dbg !869
  %mul = mul nsw i32 %0, 3, !dbg !870
  %sh_prom = zext i32 %mul to i64, !dbg !871
  %shl = shl i64 1, %sh_prom, !dbg !871
  %sub = sub nsw i64 %shl, 1, !dbg !872
  store i64 %sub, i64* %max, align 8, !dbg !873
  %1 = load i64, i64* %v.addr, align 8, !dbg !874
  %cmp = icmp sge i64 %1, 0, !dbg !876
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !877

land.lhs.true:                                    ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !878
  %3 = load i64, i64* %max, align 8, !dbg !880
  %cmp1 = icmp sle i64 %2, %3, !dbg !881
  br i1 %cmp1, label %if.then, label %if.else, !dbg !882

if.then:                                          ; preds = %land.lhs.true
  %4 = load i64, i64* %v.addr, align 8, !dbg !883
  %5 = load i8*, i8** %p.addr, align 8, !dbg !885
  %6 = load i32, i32* %digits.addr, align 4, !dbg !886
  %call = call i64 @format_octal_recursive(i64 %4, i8* %5, i32 %6), !dbg !887
  store i32 0, i32* %ret, align 4, !dbg !888
  br label %if.end, !dbg !889

if.else:                                          ; preds = %land.lhs.true, %entry
  %7 = load i64, i64* %max, align 8, !dbg !890
  %8 = load i8*, i8** %p.addr, align 8, !dbg !892
  %9 = load i32, i32* %digits.addr, align 4, !dbg !893
  %call2 = call i64 @format_octal_recursive(i64 %7, i8* %8, i32 %9), !dbg !894
  store i32 -1, i32* %ret, align 4, !dbg !895
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %ret, align 4, !dbg !896
  ret i32 %10, !dbg !897
}

declare i64 @archive_entry_dev(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @synthesize_ino_value(%struct.cpio* %cpio, %struct.archive_entry* %entry1) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ino = alloca i64, align 8
  %ino_new = alloca i32, align 4
  %i = alloca i64, align 8
  %newsize = alloca i64, align 8
  %newlist = alloca i8*, align 8
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !898, metadata !237), !dbg !899
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !900, metadata !237), !dbg !901
  call void @llvm.dbg.declare(metadata i64* %ino, metadata !902, metadata !237), !dbg !903
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !904
  %call = call i64 @archive_entry_ino64(%struct.archive_entry* %0), !dbg !905
  store i64 %call, i64* %ino, align 8, !dbg !903
  call void @llvm.dbg.declare(metadata i32* %ino_new, metadata !906, metadata !237), !dbg !907
  call void @llvm.dbg.declare(metadata i64* %i, metadata !908, metadata !237), !dbg !909
  %1 = load i64, i64* %ino, align 8, !dbg !910
  %cmp = icmp eq i64 %1, 0, !dbg !912
  br i1 %cmp, label %if.then, label %if.end, !dbg !913

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !914
  br label %return, !dbg !914

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !915
  %call2 = call i32 @archive_entry_nlink(%struct.archive_entry* %2), !dbg !917
  %cmp3 = icmp ult i32 %call2, 2, !dbg !918
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !919

if.then4:                                         ; preds = %if.end
  %3 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !920
  %ino_next = getelementptr inbounds %struct.cpio, %struct.cpio* %3, i32 0, i32 1, !dbg !922
  %4 = load i64, i64* %ino_next, align 8, !dbg !923
  %inc = add nsw i64 %4, 1, !dbg !923
  store i64 %inc, i64* %ino_next, align 8, !dbg !923
  %conv = trunc i64 %inc to i32, !dbg !924
  store i32 %conv, i32* %retval, align 4, !dbg !925
  br label %return, !dbg !925

if.end5:                                          ; preds = %if.end
  store i64 0, i64* %i, align 8, !dbg !926
  br label %for.cond, !dbg !928

for.cond:                                         ; preds = %for.inc, %if.end5
  %5 = load i64, i64* %i, align 8, !dbg !929
  %6 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !932
  %ino_list_next = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 4, !dbg !933
  %7 = load i64, i64* %ino_list_next, align 8, !dbg !933
  %cmp6 = icmp ult i64 %5, %7, !dbg !934
  br i1 %cmp6, label %for.body, label %for.end, !dbg !935

for.body:                                         ; preds = %for.cond
  %8 = load i64, i64* %i, align 8, !dbg !936
  %9 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !939
  %ino_list = getelementptr inbounds %struct.cpio, %struct.cpio* %9, i32 0, i32 2, !dbg !940
  %10 = load %struct.anon*, %struct.anon** %ino_list, align 8, !dbg !940
  %arrayidx = getelementptr inbounds %struct.anon, %struct.anon* %10, i64 %8, !dbg !939
  %old = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 0, !dbg !941
  %11 = load i64, i64* %old, align 8, !dbg !941
  %12 = load i64, i64* %ino, align 8, !dbg !942
  %cmp8 = icmp eq i64 %11, %12, !dbg !943
  br i1 %cmp8, label %if.then10, label %if.end13, !dbg !944

if.then10:                                        ; preds = %for.body
  %13 = load i64, i64* %i, align 8, !dbg !945
  %14 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !946
  %ino_list11 = getelementptr inbounds %struct.cpio, %struct.cpio* %14, i32 0, i32 2, !dbg !947
  %15 = load %struct.anon*, %struct.anon** %ino_list11, align 8, !dbg !947
  %arrayidx12 = getelementptr inbounds %struct.anon, %struct.anon* %15, i64 %13, !dbg !946
  %new = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx12, i32 0, i32 1, !dbg !948
  %16 = load i32, i32* %new, align 8, !dbg !948
  store i32 %16, i32* %retval, align 4, !dbg !949
  br label %return, !dbg !949

if.end13:                                         ; preds = %for.body
  br label %for.inc, !dbg !950

for.inc:                                          ; preds = %if.end13
  %17 = load i64, i64* %i, align 8, !dbg !951
  %inc14 = add i64 %17, 1, !dbg !951
  store i64 %inc14, i64* %i, align 8, !dbg !951
  br label %for.cond, !dbg !953

for.end:                                          ; preds = %for.cond
  %18 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !954
  %ino_next15 = getelementptr inbounds %struct.cpio, %struct.cpio* %18, i32 0, i32 1, !dbg !955
  %19 = load i64, i64* %ino_next15, align 8, !dbg !956
  %inc16 = add nsw i64 %19, 1, !dbg !956
  store i64 %inc16, i64* %ino_next15, align 8, !dbg !956
  %conv17 = trunc i64 %inc16 to i32, !dbg !957
  store i32 %conv17, i32* %ino_new, align 4, !dbg !958
  %20 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !959
  %ino_list_size = getelementptr inbounds %struct.cpio, %struct.cpio* %20, i32 0, i32 3, !dbg !961
  %21 = load i64, i64* %ino_list_size, align 8, !dbg !961
  %22 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !962
  %ino_list_next18 = getelementptr inbounds %struct.cpio, %struct.cpio* %22, i32 0, i32 4, !dbg !963
  %23 = load i64, i64* %ino_list_next18, align 8, !dbg !963
  %cmp19 = icmp ule i64 %21, %23, !dbg !964
  br i1 %cmp19, label %if.then21, label %if.end35, !dbg !965

if.then21:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata i64* %newsize, metadata !966, metadata !237), !dbg !968
  %24 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !969
  %ino_list_size22 = getelementptr inbounds %struct.cpio, %struct.cpio* %24, i32 0, i32 3, !dbg !970
  %25 = load i64, i64* %ino_list_size22, align 8, !dbg !970
  %cmp23 = icmp ult i64 %25, 512, !dbg !971
  br i1 %cmp23, label %cond.true, label %cond.false, !dbg !969

cond.true:                                        ; preds = %if.then21
  br label %cond.end, !dbg !972

cond.false:                                       ; preds = %if.then21
  %26 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !974
  %ino_list_size25 = getelementptr inbounds %struct.cpio, %struct.cpio* %26, i32 0, i32 3, !dbg !975
  %27 = load i64, i64* %ino_list_size25, align 8, !dbg !975
  %mul = mul i64 %27, 2, !dbg !976
  br label %cond.end, !dbg !977

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 512, %cond.true ], [ %mul, %cond.false ], !dbg !979
  store i64 %cond, i64* %newsize, align 8, !dbg !981
  call void @llvm.dbg.declare(metadata i8** %newlist, metadata !982, metadata !237), !dbg !983
  %28 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !984
  %ino_list26 = getelementptr inbounds %struct.cpio, %struct.cpio* %28, i32 0, i32 2, !dbg !985
  %29 = load %struct.anon*, %struct.anon** %ino_list26, align 8, !dbg !985
  %30 = bitcast %struct.anon* %29 to i8*, !dbg !984
  %31 = load i64, i64* %newsize, align 8, !dbg !986
  %mul27 = mul i64 16, %31, !dbg !987
  %call28 = call i8* @realloc(i8* %30, i64 %mul27) #7, !dbg !988
  store i8* %call28, i8** %newlist, align 8, !dbg !983
  %32 = load i8*, i8** %newlist, align 8, !dbg !989
  %cmp29 = icmp eq i8* %32, null, !dbg !991
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !992

if.then31:                                        ; preds = %cond.end
  store i32 -1, i32* %retval, align 4, !dbg !993
  br label %return, !dbg !993

if.end32:                                         ; preds = %cond.end
  %33 = load i64, i64* %newsize, align 8, !dbg !994
  %34 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !995
  %ino_list_size33 = getelementptr inbounds %struct.cpio, %struct.cpio* %34, i32 0, i32 3, !dbg !996
  store i64 %33, i64* %ino_list_size33, align 8, !dbg !997
  %35 = load i8*, i8** %newlist, align 8, !dbg !998
  %36 = bitcast i8* %35 to %struct.anon*, !dbg !998
  %37 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !999
  %ino_list34 = getelementptr inbounds %struct.cpio, %struct.cpio* %37, i32 0, i32 2, !dbg !1000
  store %struct.anon* %36, %struct.anon** %ino_list34, align 8, !dbg !1001
  br label %if.end35, !dbg !1002

if.end35:                                         ; preds = %if.end32, %for.end
  %38 = load i64, i64* %ino, align 8, !dbg !1003
  %39 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1004
  %ino_list_next36 = getelementptr inbounds %struct.cpio, %struct.cpio* %39, i32 0, i32 4, !dbg !1005
  %40 = load i64, i64* %ino_list_next36, align 8, !dbg !1005
  %41 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1006
  %ino_list37 = getelementptr inbounds %struct.cpio, %struct.cpio* %41, i32 0, i32 2, !dbg !1007
  %42 = load %struct.anon*, %struct.anon** %ino_list37, align 8, !dbg !1007
  %arrayidx38 = getelementptr inbounds %struct.anon, %struct.anon* %42, i64 %40, !dbg !1006
  %old39 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx38, i32 0, i32 0, !dbg !1008
  store i64 %38, i64* %old39, align 8, !dbg !1009
  %43 = load i32, i32* %ino_new, align 4, !dbg !1010
  %44 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1011
  %ino_list_next40 = getelementptr inbounds %struct.cpio, %struct.cpio* %44, i32 0, i32 4, !dbg !1012
  %45 = load i64, i64* %ino_list_next40, align 8, !dbg !1012
  %46 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1013
  %ino_list41 = getelementptr inbounds %struct.cpio, %struct.cpio* %46, i32 0, i32 2, !dbg !1014
  %47 = load %struct.anon*, %struct.anon** %ino_list41, align 8, !dbg !1014
  %arrayidx42 = getelementptr inbounds %struct.anon, %struct.anon* %47, i64 %45, !dbg !1013
  %new43 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx42, i32 0, i32 1, !dbg !1015
  store i32 %43, i32* %new43, align 8, !dbg !1016
  %48 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1017
  %ino_list_next44 = getelementptr inbounds %struct.cpio, %struct.cpio* %48, i32 0, i32 4, !dbg !1018
  %49 = load i64, i64* %ino_list_next44, align 8, !dbg !1019
  %inc45 = add i64 %49, 1, !dbg !1019
  store i64 %inc45, i64* %ino_list_next44, align 8, !dbg !1019
  %50 = load i32, i32* %ino_new, align 4, !dbg !1020
  store i32 %50, i32* %retval, align 4, !dbg !1021
  br label %return, !dbg !1021

return:                                           ; preds = %if.end35, %if.then31, %if.then10, %if.then4, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !1022
  ret i32 %51, !dbg !1022
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare i32 @archive_entry_nlink(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i64 @format_octal_recursive(i64 %v, i8* %p, i32 %s) #0 !dbg !223 {
entry:
  %retval = alloca i64, align 8
  %v.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i32, align 4
  store i64 %v, i64* %v.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %v.addr, metadata !1023, metadata !237), !dbg !1024
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1025, metadata !237), !dbg !1026
  store i32 %s, i32* %s.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %s.addr, metadata !1027, metadata !237), !dbg !1028
  %0 = load i32, i32* %s.addr, align 4, !dbg !1029
  %cmp = icmp eq i32 %0, 0, !dbg !1031
  br i1 %cmp, label %if.then, label %if.end, !dbg !1032

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %v.addr, align 8, !dbg !1033
  store i64 %1, i64* %retval, align 8, !dbg !1034
  br label %return, !dbg !1034

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %v.addr, align 8, !dbg !1035
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1036
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 1, !dbg !1037
  %4 = load i32, i32* %s.addr, align 4, !dbg !1038
  %sub = sub nsw i32 %4, 1, !dbg !1039
  %call = call i64 @format_octal_recursive(i64 %2, i8* %add.ptr, i32 %sub), !dbg !1040
  store i64 %call, i64* %v.addr, align 8, !dbg !1041
  %5 = load i64, i64* %v.addr, align 8, !dbg !1042
  %conv = trunc i64 %5 to i8, !dbg !1043
  %conv1 = sext i8 %conv to i32, !dbg !1043
  %and = and i32 %conv1, 7, !dbg !1044
  %add = add nsw i32 48, %and, !dbg !1045
  %conv2 = trunc i32 %add to i8, !dbg !1046
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1047
  store i8 %conv2, i8* %6, align 1, !dbg !1048
  %7 = load i64, i64* %v.addr, align 8, !dbg !1049
  %shr = ashr i64 %7, 3, !dbg !1050
  store i64 %shr, i64* %retval, align 8, !dbg !1051
  br label %return, !dbg !1051

return:                                           ; preds = %if.end, %if.then
  %8 = load i64, i64* %retval, align 8, !dbg !1052
  ret i64 %8, !dbg !1052
}

declare i64 @archive_entry_ino64(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #3

declare %struct.archive_entry* @archive_entry_new2(%struct.archive*) #2

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
!llvm.module.flags = !{!233, !234}
!llvm.ident = !{!235}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !212)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_cpio.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !23, !209, !52, !95, !82, !45}
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
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "cpio", file: !1, line: 60, size: 512, align: 64, elements: !194)
!194 = !{!195, !197, !198, !204, !205, !206, !207, !208}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 61, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "ino_next", scope: !193, file: !1, line: 63, baseType: !52, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "ino_list", scope: !193, file: !1, line: 65, baseType: !199, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DICompositeType(tag: DW_TAG_structure_type, scope: !193, file: !1, line: 65, size: 128, align: 64, elements: !201)
!201 = !{!202, !203}
!202 = !DIDerivedType(tag: DW_TAG_member, name: "old", scope: !200, file: !1, line: 65, baseType: !52, size: 64, align: 64)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "new", scope: !200, file: !1, line: 65, baseType: !23, size: 32, align: 32, offset: 64)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "ino_list_size", scope: !193, file: !1, line: 66, baseType: !45, size: 64, align: 64, offset: 192)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "ino_list_next", scope: !193, file: !1, line: 67, baseType: !45, size: 64, align: 64, offset: 256)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !193, file: !1, line: 69, baseType: !102, size: 64, align: 64, offset: 320)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !193, file: !1, line: 70, baseType: !102, size: 64, align: 64, offset: 384)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !193, file: !1, line: 71, baseType: !23, size: 32, align: 32, offset: 448)
!209 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !210, line: 70, baseType: !211)
!210 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!212 = !{!213, !214, !215, !216, !219, !220, !223, !226, !229, !230, !231, !232}
!213 = distinct !DISubprogram(name: "archive_write_set_format_cpio", scope: !1, file: !1, line: 101, type: !21, isLocal: false, isDefinition: true, scopeLine: 102, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!214 = distinct !DISubprogram(name: "archive_write_cpio_options", scope: !1, file: !1, line: 132, type: !172, isLocal: true, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = distinct !DISubprogram(name: "archive_write_cpio_header", scope: !1, file: !1, line: 247, type: !177, isLocal: true, isDefinition: true, scopeLine: 248, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "get_sconv", scope: !1, file: !1, line: 227, type: !217, isLocal: true, isDefinition: true, scopeLine: 228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = !DISubroutineType(types: !218)
!218 = !{!102, !4}
!219 = distinct !DISubprogram(name: "write_header", scope: !1, file: !1, line: 276, type: !177, isLocal: true, isDefinition: true, scopeLine: 277, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "format_octal", scope: !1, file: !1, line: 438, type: !221, isLocal: true, isDefinition: true, scopeLine: 439, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = !DISubroutineType(types: !222)
!222 = !{!23, !52, !124, !23}
!223 = distinct !DISubprogram(name: "format_octal_recursive", scope: !1, file: !1, line: 455, type: !224, isLocal: true, isDefinition: true, scopeLine: 456, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!224 = !DISubroutineType(types: !225)
!225 = !{!52, !52, !95, !23}
!226 = distinct !DISubprogram(name: "synthesize_ino_value", scope: !1, file: !1, line: 175, type: !227, isLocal: true, isDefinition: true, scopeLine: 176, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = !DISubroutineType(types: !228)
!228 = !{!23, !192, !30}
!229 = distinct !DISubprogram(name: "archive_write_cpio_data", scope: !1, file: !1, line: 417, type: !181, isLocal: true, isDefinition: true, scopeLine: 418, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!230 = distinct !DISubprogram(name: "archive_write_cpio_close", scope: !1, file: !1, line: 465, type: !168, isLocal: true, isDefinition: true, scopeLine: 466, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!231 = distinct !DISubprogram(name: "archive_write_cpio_free", scope: !1, file: !1, line: 481, type: !168, isLocal: true, isDefinition: true, scopeLine: 482, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!232 = distinct !DISubprogram(name: "archive_write_cpio_finish_entry", scope: !1, file: !1, line: 493, type: !168, isLocal: true, isDefinition: true, scopeLine: 494, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = !{i32 2, !"Dwarf Version", i32 4}
!234 = !{i32 2, !"Debug Info Version", i32 3}
!235 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!236 = !DILocalVariable(name: "_a", arg: 1, scope: !213, file: !1, line: 101, type: !24)
!237 = !DIExpression()
!238 = !DILocation(line: 101, column: 47, scope: !213)
!239 = !DILocalVariable(name: "a", scope: !213, file: !1, line: 103, type: !4)
!240 = !DILocation(line: 103, column: 24, scope: !213)
!241 = !DILocation(line: 103, column: 52, scope: !213)
!242 = !DILocation(line: 103, column: 28, scope: !213)
!243 = !DILocalVariable(name: "cpio", scope: !213, file: !1, line: 104, type: !192)
!244 = !DILocation(line: 104, column: 15, scope: !213)
!245 = !DILocation(line: 106, column: 2, scope: !213)
!246 = !DILocalVariable(name: "magic_test", scope: !247, file: !1, line: 106, type: !23)
!247 = distinct !DILexicalBlock(scope: !213, file: !1, line: 106, column: 2)
!248 = !DILocation(line: 106, column: 2, scope: !247)
!249 = !DILocation(line: 106, column: 2, scope: !250)
!250 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 1)
!251 = !DILocation(line: 106, column: 2, scope: !252)
!252 = !DILexicalBlockFile(scope: !253, file: !1, discriminator: 2)
!253 = distinct !DILexicalBlock(scope: !247, file: !1, line: 106, column: 2)
!254 = !DILocation(line: 106, column: 2, scope: !255)
!255 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 3)
!256 = !DILocation(line: 110, column: 6, scope: !257)
!257 = distinct !DILexicalBlock(scope: !213, file: !1, line: 110, column: 6)
!258 = !DILocation(line: 110, column: 9, scope: !257)
!259 = !DILocation(line: 110, column: 21, scope: !257)
!260 = !DILocation(line: 110, column: 6, scope: !213)
!261 = !DILocation(line: 111, column: 4, scope: !257)
!262 = !DILocation(line: 111, column: 7, scope: !257)
!263 = !DILocation(line: 111, column: 20, scope: !257)
!264 = !DILocation(line: 111, column: 3, scope: !257)
!265 = !DILocation(line: 113, column: 24, scope: !213)
!266 = !DILocation(line: 113, column: 9, scope: !213)
!267 = !DILocation(line: 113, column: 7, scope: !213)
!268 = !DILocation(line: 114, column: 6, scope: !269)
!269 = distinct !DILexicalBlock(scope: !213, file: !1, line: 114, column: 6)
!270 = !DILocation(line: 114, column: 11, scope: !269)
!271 = !DILocation(line: 114, column: 6, scope: !213)
!272 = !DILocation(line: 115, column: 22, scope: !273)
!273 = distinct !DILexicalBlock(scope: !269, file: !1, line: 114, column: 20)
!274 = !DILocation(line: 115, column: 25, scope: !273)
!275 = !DILocation(line: 115, column: 3, scope: !273)
!276 = !DILocation(line: 116, column: 3, scope: !273)
!277 = !DILocation(line: 118, column: 19, scope: !213)
!278 = !DILocation(line: 118, column: 2, scope: !213)
!279 = !DILocation(line: 118, column: 5, scope: !213)
!280 = !DILocation(line: 118, column: 17, scope: !213)
!281 = !DILocation(line: 119, column: 2, scope: !213)
!282 = !DILocation(line: 119, column: 5, scope: !213)
!283 = !DILocation(line: 119, column: 17, scope: !213)
!284 = !DILocation(line: 120, column: 2, scope: !213)
!285 = !DILocation(line: 120, column: 5, scope: !213)
!286 = !DILocation(line: 120, column: 20, scope: !213)
!287 = !DILocation(line: 121, column: 2, scope: !213)
!288 = !DILocation(line: 121, column: 5, scope: !213)
!289 = !DILocation(line: 121, column: 25, scope: !213)
!290 = !DILocation(line: 122, column: 2, scope: !213)
!291 = !DILocation(line: 122, column: 5, scope: !213)
!292 = !DILocation(line: 122, column: 23, scope: !213)
!293 = !DILocation(line: 123, column: 2, scope: !213)
!294 = !DILocation(line: 123, column: 5, scope: !213)
!295 = !DILocation(line: 123, column: 25, scope: !213)
!296 = !DILocation(line: 124, column: 2, scope: !213)
!297 = !DILocation(line: 124, column: 5, scope: !213)
!298 = !DILocation(line: 124, column: 18, scope: !213)
!299 = !DILocation(line: 125, column: 2, scope: !213)
!300 = !DILocation(line: 125, column: 5, scope: !213)
!301 = !DILocation(line: 125, column: 17, scope: !213)
!302 = !DILocation(line: 126, column: 2, scope: !213)
!303 = !DILocation(line: 126, column: 5, scope: !213)
!304 = !DILocation(line: 126, column: 13, scope: !213)
!305 = !DILocation(line: 126, column: 28, scope: !213)
!306 = !DILocation(line: 127, column: 2, scope: !213)
!307 = !DILocation(line: 127, column: 5, scope: !213)
!308 = !DILocation(line: 127, column: 13, scope: !213)
!309 = !DILocation(line: 127, column: 33, scope: !213)
!310 = !DILocation(line: 128, column: 2, scope: !213)
!311 = !DILocation(line: 129, column: 1, scope: !213)
!312 = !DILocalVariable(name: "a", arg: 1, scope: !214, file: !1, line: 132, type: !4)
!313 = !DILocation(line: 132, column: 50, scope: !214)
!314 = !DILocalVariable(name: "key", arg: 2, scope: !214, file: !1, line: 132, type: !80)
!315 = !DILocation(line: 132, column: 65, scope: !214)
!316 = !DILocalVariable(name: "val", arg: 3, scope: !214, file: !1, line: 133, type: !80)
!317 = !DILocation(line: 133, column: 17, scope: !214)
!318 = !DILocalVariable(name: "cpio", scope: !214, file: !1, line: 135, type: !192)
!319 = !DILocation(line: 135, column: 15, scope: !214)
!320 = !DILocation(line: 135, column: 37, scope: !214)
!321 = !DILocation(line: 135, column: 40, scope: !214)
!322 = !DILocation(line: 135, column: 22, scope: !214)
!323 = !DILocalVariable(name: "ret", scope: !214, file: !1, line: 136, type: !23)
!324 = !DILocation(line: 136, column: 6, scope: !214)
!325 = !DILocation(line: 138, column: 13, scope: !326)
!326 = distinct !DILexicalBlock(scope: !214, file: !1, line: 138, column: 6)
!327 = !DILocation(line: 138, column: 6, scope: !326)
!328 = !DILocation(line: 138, column: 33, scope: !326)
!329 = !DILocation(line: 138, column: 6, scope: !214)
!330 = !DILocation(line: 139, column: 7, scope: !331)
!331 = distinct !DILexicalBlock(scope: !332, file: !1, line: 139, column: 7)
!332 = distinct !DILexicalBlock(scope: !326, file: !1, line: 138, column: 39)
!333 = !DILocation(line: 139, column: 11, scope: !331)
!334 = !DILocation(line: 139, column: 19, scope: !331)
!335 = !DILocation(line: 139, column: 22, scope: !336)
!336 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 1)
!337 = !DILocation(line: 139, column: 29, scope: !336)
!338 = !DILocation(line: 139, column: 7, scope: !336)
!339 = !DILocation(line: 140, column: 23, scope: !331)
!340 = !DILocation(line: 140, column: 26, scope: !331)
!341 = !DILocation(line: 142, column: 8, scope: !331)
!342 = !DILocation(line: 142, column: 11, scope: !331)
!343 = !DILocation(line: 140, column: 4, scope: !331)
!344 = !DILocation(line: 145, column: 9, scope: !345)
!345 = distinct !DILexicalBlock(scope: !331, file: !1, line: 143, column: 8)
!346 = !DILocation(line: 145, column: 12, scope: !345)
!347 = !DILocation(line: 145, column: 21, scope: !345)
!348 = !DILocation(line: 144, column: 22, scope: !345)
!349 = !DILocation(line: 144, column: 4, scope: !345)
!350 = !DILocation(line: 144, column: 10, scope: !345)
!351 = !DILocation(line: 144, column: 20, scope: !345)
!352 = !DILocation(line: 146, column: 8, scope: !353)
!353 = distinct !DILexicalBlock(scope: !345, file: !1, line: 146, column: 8)
!354 = !DILocation(line: 146, column: 14, scope: !353)
!355 = !DILocation(line: 146, column: 24, scope: !353)
!356 = !DILocation(line: 146, column: 8, scope: !345)
!357 = !DILocation(line: 147, column: 9, scope: !353)
!358 = !DILocation(line: 147, column: 5, scope: !353)
!359 = !DILocation(line: 149, column: 9, scope: !353)
!360 = !DILocation(line: 151, column: 11, scope: !332)
!361 = !DILocation(line: 151, column: 3, scope: !332)
!362 = !DILocation(line: 157, column: 2, scope: !214)
!363 = !DILocation(line: 158, column: 1, scope: !214)
!364 = !DILocalVariable(name: "a", arg: 1, scope: !215, file: !1, line: 247, type: !4)
!365 = !DILocation(line: 247, column: 49, scope: !215)
!366 = !DILocalVariable(name: "entry", arg: 2, scope: !215, file: !1, line: 247, type: !30)
!367 = !DILocation(line: 247, column: 74, scope: !215)
!368 = !DILocalVariable(name: "path", scope: !215, file: !1, line: 249, type: !80)
!369 = !DILocation(line: 249, column: 14, scope: !215)
!370 = !DILocalVariable(name: "len", scope: !215, file: !1, line: 250, type: !45)
!371 = !DILocation(line: 250, column: 9, scope: !215)
!372 = !DILocation(line: 252, column: 29, scope: !373)
!373 = distinct !DILexicalBlock(scope: !215, file: !1, line: 252, column: 6)
!374 = !DILocation(line: 252, column: 6, scope: !373)
!375 = !DILocation(line: 252, column: 36, scope: !373)
!376 = !DILocation(line: 252, column: 6, scope: !215)
!377 = !DILocation(line: 253, column: 22, scope: !378)
!378 = distinct !DILexicalBlock(scope: !373, file: !1, line: 252, column: 42)
!379 = !DILocation(line: 253, column: 25, scope: !378)
!380 = !DILocation(line: 253, column: 3, scope: !378)
!381 = !DILocation(line: 254, column: 3, scope: !378)
!382 = !DILocation(line: 257, column: 31, scope: !383)
!383 = distinct !DILexicalBlock(scope: !215, file: !1, line: 257, column: 6)
!384 = !DILocation(line: 257, column: 61, scope: !383)
!385 = !DILocation(line: 257, column: 51, scope: !383)
!386 = !DILocation(line: 257, column: 6, scope: !387)
!387 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 2)
!388 = !DILocation(line: 257, column: 65, scope: !383)
!389 = !DILocation(line: 258, column: 6, scope: !383)
!390 = !DILocation(line: 258, column: 9, scope: !391)
!391 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 1)
!392 = !DILocation(line: 258, column: 15, scope: !391)
!393 = !DILocation(line: 257, column: 6, scope: !394)
!394 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!395 = !DILocation(line: 259, column: 22, scope: !396)
!396 = distinct !DILexicalBlock(scope: !383, file: !1, line: 258, column: 26)
!397 = !DILocation(line: 259, column: 25, scope: !396)
!398 = !DILocation(line: 259, column: 3, scope: !396)
!399 = !DILocation(line: 261, column: 3, scope: !396)
!400 = !DILocation(line: 263, column: 6, scope: !401)
!401 = distinct !DILexicalBlock(scope: !215, file: !1, line: 263, column: 6)
!402 = !DILocation(line: 263, column: 10, scope: !401)
!403 = !DILocation(line: 263, column: 15, scope: !401)
!404 = !DILocation(line: 263, column: 18, scope: !405)
!405 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 1)
!406 = !DILocation(line: 263, column: 23, scope: !405)
!407 = !DILocation(line: 263, column: 31, scope: !405)
!408 = !DILocation(line: 263, column: 34, scope: !409)
!409 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 2)
!410 = !DILocation(line: 263, column: 42, scope: !409)
!411 = !DILocation(line: 263, column: 6, scope: !409)
!412 = !DILocation(line: 264, column: 22, scope: !413)
!413 = distinct !DILexicalBlock(scope: !401, file: !1, line: 263, column: 51)
!414 = !DILocation(line: 264, column: 25, scope: !413)
!415 = !DILocation(line: 264, column: 3, scope: !413)
!416 = !DILocation(line: 265, column: 3, scope: !413)
!417 = !DILocation(line: 268, column: 33, scope: !418)
!418 = distinct !DILexicalBlock(scope: !215, file: !1, line: 268, column: 6)
!419 = !DILocation(line: 268, column: 7, scope: !418)
!420 = !DILocation(line: 268, column: 40, scope: !418)
!421 = !DILocation(line: 268, column: 62, scope: !422)
!422 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 1)
!423 = !DILocation(line: 268, column: 43, scope: !422)
!424 = !DILocation(line: 268, column: 69, scope: !422)
!425 = !DILocation(line: 268, column: 6, scope: !422)
!426 = !DILocation(line: 269, column: 22, scope: !427)
!427 = distinct !DILexicalBlock(scope: !418, file: !1, line: 268, column: 74)
!428 = !DILocation(line: 269, column: 25, scope: !427)
!429 = !DILocation(line: 269, column: 3, scope: !427)
!430 = !DILocation(line: 270, column: 3, scope: !427)
!431 = !DILocation(line: 272, column: 22, scope: !215)
!432 = !DILocation(line: 272, column: 25, scope: !215)
!433 = !DILocation(line: 272, column: 9, scope: !215)
!434 = !DILocation(line: 272, column: 2, scope: !215)
!435 = !DILocation(line: 273, column: 1, scope: !215)
!436 = !DILocalVariable(name: "a", arg: 1, scope: !229, file: !1, line: 417, type: !4)
!437 = !DILocation(line: 417, column: 47, scope: !229)
!438 = !DILocalVariable(name: "buff", arg: 2, scope: !229, file: !1, line: 417, type: !43)
!439 = !DILocation(line: 417, column: 62, scope: !229)
!440 = !DILocalVariable(name: "s", arg: 3, scope: !229, file: !1, line: 417, type: !45)
!441 = !DILocation(line: 417, column: 75, scope: !229)
!442 = !DILocalVariable(name: "cpio", scope: !229, file: !1, line: 419, type: !192)
!443 = !DILocation(line: 419, column: 15, scope: !229)
!444 = !DILocalVariable(name: "ret", scope: !229, file: !1, line: 420, type: !23)
!445 = !DILocation(line: 420, column: 6, scope: !229)
!446 = !DILocation(line: 422, column: 24, scope: !229)
!447 = !DILocation(line: 422, column: 27, scope: !229)
!448 = !DILocation(line: 422, column: 9, scope: !229)
!449 = !DILocation(line: 422, column: 7, scope: !229)
!450 = !DILocation(line: 423, column: 6, scope: !451)
!451 = distinct !DILexicalBlock(scope: !229, file: !1, line: 423, column: 6)
!452 = !DILocation(line: 423, column: 10, scope: !451)
!453 = !DILocation(line: 423, column: 16, scope: !451)
!454 = !DILocation(line: 423, column: 8, scope: !451)
!455 = !DILocation(line: 423, column: 6, scope: !229)
!456 = !DILocation(line: 424, column: 15, scope: !451)
!457 = !DILocation(line: 424, column: 21, scope: !451)
!458 = !DILocation(line: 424, column: 5, scope: !451)
!459 = !DILocation(line: 424, column: 3, scope: !451)
!460 = !DILocation(line: 426, column: 31, scope: !229)
!461 = !DILocation(line: 426, column: 34, scope: !229)
!462 = !DILocation(line: 426, column: 40, scope: !229)
!463 = !DILocation(line: 426, column: 8, scope: !229)
!464 = !DILocation(line: 426, column: 6, scope: !229)
!465 = !DILocation(line: 427, column: 33, scope: !229)
!466 = !DILocation(line: 427, column: 2, scope: !229)
!467 = !DILocation(line: 427, column: 8, scope: !229)
!468 = !DILocation(line: 427, column: 30, scope: !229)
!469 = !DILocation(line: 428, column: 6, scope: !470)
!470 = distinct !DILexicalBlock(scope: !229, file: !1, line: 428, column: 6)
!471 = !DILocation(line: 428, column: 10, scope: !470)
!472 = !DILocation(line: 428, column: 6, scope: !229)
!473 = !DILocation(line: 429, column: 11, scope: !470)
!474 = !DILocation(line: 429, column: 3, scope: !470)
!475 = !DILocation(line: 431, column: 11, scope: !470)
!476 = !DILocation(line: 431, column: 10, scope: !470)
!477 = !DILocation(line: 431, column: 3, scope: !470)
!478 = !DILocation(line: 432, column: 1, scope: !229)
!479 = !DILocalVariable(name: "a", arg: 1, scope: !232, file: !1, line: 493, type: !4)
!480 = !DILocation(line: 493, column: 55, scope: !232)
!481 = !DILocalVariable(name: "cpio", scope: !232, file: !1, line: 495, type: !192)
!482 = !DILocation(line: 495, column: 15, scope: !232)
!483 = !DILocation(line: 497, column: 24, scope: !232)
!484 = !DILocation(line: 497, column: 27, scope: !232)
!485 = !DILocation(line: 497, column: 9, scope: !232)
!486 = !DILocation(line: 497, column: 7, scope: !232)
!487 = !DILocation(line: 498, column: 32, scope: !232)
!488 = !DILocation(line: 499, column: 11, scope: !232)
!489 = !DILocation(line: 499, column: 17, scope: !232)
!490 = !DILocation(line: 498, column: 10, scope: !232)
!491 = !DILocation(line: 498, column: 2, scope: !232)
!492 = !DILocalVariable(name: "a", arg: 1, scope: !230, file: !1, line: 465, type: !4)
!493 = !DILocation(line: 465, column: 48, scope: !230)
!494 = !DILocalVariable(name: "er", scope: !230, file: !1, line: 467, type: !23)
!495 = !DILocation(line: 467, column: 6, scope: !230)
!496 = !DILocalVariable(name: "trailer", scope: !230, file: !1, line: 468, type: !30)
!497 = !DILocation(line: 468, column: 24, scope: !230)
!498 = !DILocation(line: 470, column: 12, scope: !230)
!499 = !DILocation(line: 470, column: 10, scope: !230)
!500 = !DILocation(line: 472, column: 26, scope: !230)
!501 = !DILocation(line: 472, column: 2, scope: !230)
!502 = !DILocation(line: 473, column: 25, scope: !230)
!503 = !DILocation(line: 473, column: 2, scope: !230)
!504 = !DILocation(line: 474, column: 29, scope: !230)
!505 = !DILocation(line: 474, column: 2, scope: !230)
!506 = !DILocation(line: 475, column: 20, scope: !230)
!507 = !DILocation(line: 475, column: 23, scope: !230)
!508 = !DILocation(line: 475, column: 7, scope: !230)
!509 = !DILocation(line: 475, column: 5, scope: !230)
!510 = !DILocation(line: 476, column: 21, scope: !230)
!511 = !DILocation(line: 476, column: 2, scope: !230)
!512 = !DILocation(line: 477, column: 10, scope: !230)
!513 = !DILocation(line: 477, column: 2, scope: !230)
!514 = !DILocalVariable(name: "a", arg: 1, scope: !231, file: !1, line: 481, type: !4)
!515 = !DILocation(line: 481, column: 47, scope: !231)
!516 = !DILocalVariable(name: "cpio", scope: !231, file: !1, line: 483, type: !192)
!517 = !DILocation(line: 483, column: 15, scope: !231)
!518 = !DILocation(line: 485, column: 24, scope: !231)
!519 = !DILocation(line: 485, column: 27, scope: !231)
!520 = !DILocation(line: 485, column: 9, scope: !231)
!521 = !DILocation(line: 485, column: 7, scope: !231)
!522 = !DILocation(line: 486, column: 7, scope: !231)
!523 = !DILocation(line: 486, column: 13, scope: !231)
!524 = !DILocation(line: 486, column: 2, scope: !231)
!525 = !DILocation(line: 487, column: 7, scope: !231)
!526 = !DILocation(line: 487, column: 2, scope: !231)
!527 = !DILocation(line: 488, column: 2, scope: !231)
!528 = !DILocation(line: 488, column: 5, scope: !231)
!529 = !DILocation(line: 488, column: 17, scope: !231)
!530 = !DILocation(line: 489, column: 2, scope: !231)
!531 = !DILocalVariable(name: "a", arg: 1, scope: !216, file: !1, line: 227, type: !4)
!532 = !DILocation(line: 227, column: 33, scope: !216)
!533 = !DILocalVariable(name: "cpio", scope: !216, file: !1, line: 229, type: !192)
!534 = !DILocation(line: 229, column: 15, scope: !216)
!535 = !DILocalVariable(name: "sconv", scope: !216, file: !1, line: 230, type: !102)
!536 = !DILocation(line: 230, column: 30, scope: !216)
!537 = !DILocation(line: 232, column: 24, scope: !216)
!538 = !DILocation(line: 232, column: 27, scope: !216)
!539 = !DILocation(line: 232, column: 9, scope: !216)
!540 = !DILocation(line: 232, column: 7, scope: !216)
!541 = !DILocation(line: 233, column: 10, scope: !216)
!542 = !DILocation(line: 233, column: 16, scope: !216)
!543 = !DILocation(line: 233, column: 8, scope: !216)
!544 = !DILocation(line: 234, column: 6, scope: !545)
!545 = distinct !DILexicalBlock(scope: !216, file: !1, line: 234, column: 6)
!546 = !DILocation(line: 234, column: 12, scope: !545)
!547 = !DILocation(line: 234, column: 6, scope: !216)
!548 = !DILocation(line: 235, column: 8, scope: !549)
!549 = distinct !DILexicalBlock(scope: !550, file: !1, line: 235, column: 7)
!550 = distinct !DILexicalBlock(scope: !545, file: !1, line: 234, column: 21)
!551 = !DILocation(line: 235, column: 14, scope: !549)
!552 = !DILocation(line: 235, column: 7, scope: !550)
!553 = !DILocation(line: 238, column: 12, scope: !554)
!554 = distinct !DILexicalBlock(scope: !549, file: !1, line: 235, column: 39)
!555 = !DILocation(line: 238, column: 15, scope: !554)
!556 = !DILocation(line: 237, column: 8, scope: !554)
!557 = !DILocation(line: 236, column: 4, scope: !554)
!558 = !DILocation(line: 236, column: 10, scope: !554)
!559 = !DILocation(line: 236, column: 24, scope: !554)
!560 = !DILocation(line: 239, column: 4, scope: !554)
!561 = !DILocation(line: 239, column: 10, scope: !554)
!562 = !DILocation(line: 239, column: 34, scope: !554)
!563 = !DILocation(line: 240, column: 3, scope: !554)
!564 = !DILocation(line: 241, column: 11, scope: !550)
!565 = !DILocation(line: 241, column: 17, scope: !550)
!566 = !DILocation(line: 241, column: 9, scope: !550)
!567 = !DILocation(line: 242, column: 2, scope: !550)
!568 = !DILocation(line: 243, column: 10, scope: !216)
!569 = !DILocation(line: 243, column: 2, scope: !216)
!570 = !DILocalVariable(name: "a", arg: 1, scope: !219, file: !1, line: 276, type: !4)
!571 = !DILocation(line: 276, column: 36, scope: !219)
!572 = !DILocalVariable(name: "entry", arg: 2, scope: !219, file: !1, line: 276, type: !30)
!573 = !DILocation(line: 276, column: 61, scope: !219)
!574 = !DILocalVariable(name: "cpio", scope: !219, file: !1, line: 278, type: !192)
!575 = !DILocation(line: 278, column: 15, scope: !219)
!576 = !DILocalVariable(name: "p", scope: !219, file: !1, line: 279, type: !80)
!577 = !DILocation(line: 279, column: 14, scope: !219)
!578 = !DILocalVariable(name: "path", scope: !219, file: !1, line: 279, type: !80)
!579 = !DILocation(line: 279, column: 18, scope: !219)
!580 = !DILocalVariable(name: "pathlength", scope: !219, file: !1, line: 280, type: !23)
!581 = !DILocation(line: 280, column: 6, scope: !219)
!582 = !DILocalVariable(name: "ret", scope: !219, file: !1, line: 280, type: !23)
!583 = !DILocation(line: 280, column: 18, scope: !219)
!584 = !DILocalVariable(name: "ret_final", scope: !219, file: !1, line: 280, type: !23)
!585 = !DILocation(line: 280, column: 23, scope: !219)
!586 = !DILocalVariable(name: "ino", scope: !219, file: !1, line: 281, type: !52)
!587 = !DILocation(line: 281, column: 10, scope: !219)
!588 = !DILocalVariable(name: "h", scope: !219, file: !1, line: 282, type: !589)
!589 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 608, align: 8, elements: !590)
!590 = !{!591}
!591 = !DISubrange(count: 76)
!592 = !DILocation(line: 282, column: 7, scope: !219)
!593 = !DILocalVariable(name: "sconv", scope: !219, file: !1, line: 283, type: !102)
!594 = !DILocation(line: 283, column: 30, scope: !219)
!595 = !DILocalVariable(name: "entry_main", scope: !219, file: !1, line: 284, type: !30)
!596 = !DILocation(line: 284, column: 24, scope: !219)
!597 = !DILocalVariable(name: "len", scope: !219, file: !1, line: 285, type: !45)
!598 = !DILocation(line: 285, column: 9, scope: !219)
!599 = !DILocation(line: 287, column: 24, scope: !219)
!600 = !DILocation(line: 287, column: 27, scope: !219)
!601 = !DILocation(line: 287, column: 9, scope: !219)
!602 = !DILocation(line: 287, column: 7, scope: !219)
!603 = !DILocation(line: 288, column: 12, scope: !219)
!604 = !DILocation(line: 289, column: 20, scope: !219)
!605 = !DILocation(line: 289, column: 10, scope: !219)
!606 = !DILocation(line: 289, column: 8, scope: !219)
!607 = !DILocation(line: 305, column: 13, scope: !219)
!608 = !DILocation(line: 308, column: 33, scope: !219)
!609 = !DILocation(line: 308, column: 53, scope: !219)
!610 = !DILocation(line: 308, column: 8, scope: !219)
!611 = !DILocation(line: 308, column: 6, scope: !219)
!612 = !DILocation(line: 309, column: 6, scope: !613)
!613 = distinct !DILexicalBlock(scope: !219, file: !1, line: 309, column: 6)
!614 = !DILocation(line: 309, column: 10, scope: !613)
!615 = !DILocation(line: 309, column: 6, scope: !219)
!616 = !DILocation(line: 310, column: 7, scope: !617)
!617 = distinct !DILexicalBlock(scope: !618, file: !1, line: 310, column: 7)
!618 = distinct !DILexicalBlock(scope: !613, file: !1, line: 309, column: 16)
!619 = !DILocation(line: 310, column: 13, scope: !617)
!620 = !DILocation(line: 310, column: 7, scope: !618)
!621 = !DILocation(line: 311, column: 23, scope: !622)
!622 = distinct !DILexicalBlock(scope: !617, file: !1, line: 310, column: 24)
!623 = !DILocation(line: 311, column: 26, scope: !622)
!624 = !DILocation(line: 311, column: 4, scope: !622)
!625 = !DILocation(line: 313, column: 14, scope: !622)
!626 = !DILocation(line: 314, column: 4, scope: !622)
!627 = !DILocation(line: 316, column: 22, scope: !618)
!628 = !DILocation(line: 316, column: 25, scope: !618)
!629 = !DILocation(line: 318, column: 30, scope: !618)
!630 = !DILocation(line: 318, column: 7, scope: !618)
!631 = !DILocation(line: 319, column: 46, scope: !618)
!632 = !DILocation(line: 319, column: 7, scope: !618)
!633 = !DILocation(line: 316, column: 3, scope: !618)
!634 = !DILocation(line: 320, column: 13, scope: !618)
!635 = !DILocation(line: 321, column: 2, scope: !618)
!636 = !DILocation(line: 323, column: 20, scope: !219)
!637 = !DILocation(line: 323, column: 15, scope: !219)
!638 = !DILocation(line: 323, column: 24, scope: !219)
!639 = !DILocation(line: 323, column: 13, scope: !219)
!640 = !DILocation(line: 325, column: 2, scope: !219)
!641 = !DILocation(line: 326, column: 23, scope: !219)
!642 = !DILocation(line: 326, column: 25, scope: !219)
!643 = !DILocation(line: 326, column: 2, scope: !219)
!644 = !DILocation(line: 327, column: 33, scope: !219)
!645 = !DILocation(line: 327, column: 15, scope: !219)
!646 = !DILocation(line: 327, column: 41, scope: !219)
!647 = !DILocation(line: 327, column: 43, scope: !219)
!648 = !DILocation(line: 327, column: 2, scope: !649)
!649 = !DILexicalBlockFile(scope: !219, file: !1, discriminator: 1)
!650 = !DILocation(line: 329, column: 29, scope: !219)
!651 = !DILocation(line: 329, column: 35, scope: !219)
!652 = !DILocation(line: 329, column: 8, scope: !219)
!653 = !DILocation(line: 329, column: 6, scope: !219)
!654 = !DILocation(line: 330, column: 6, scope: !655)
!655 = distinct !DILexicalBlock(scope: !219, file: !1, line: 330, column: 6)
!656 = !DILocation(line: 330, column: 10, scope: !655)
!657 = !DILocation(line: 330, column: 6, scope: !219)
!658 = !DILocation(line: 331, column: 22, scope: !659)
!659 = distinct !DILexicalBlock(scope: !655, file: !1, line: 330, column: 15)
!660 = !DILocation(line: 331, column: 25, scope: !659)
!661 = !DILocation(line: 331, column: 3, scope: !659)
!662 = !DILocation(line: 333, column: 13, scope: !659)
!663 = !DILocation(line: 334, column: 3, scope: !659)
!664 = !DILocation(line: 335, column: 13, scope: !665)
!665 = distinct !DILexicalBlock(scope: !655, file: !1, line: 335, column: 13)
!666 = !DILocation(line: 335, column: 17, scope: !665)
!667 = !DILocation(line: 335, column: 13, scope: !655)
!668 = !DILocation(line: 336, column: 22, scope: !669)
!669 = distinct !DILexicalBlock(scope: !665, file: !1, line: 335, column: 28)
!670 = !DILocation(line: 336, column: 25, scope: !669)
!671 = !DILocation(line: 336, column: 3, scope: !669)
!672 = !DILocation(line: 338, column: 13, scope: !669)
!673 = !DILocation(line: 339, column: 3, scope: !669)
!674 = !DILocation(line: 341, column: 15, scope: !219)
!675 = !DILocation(line: 341, column: 19, scope: !219)
!676 = !DILocation(line: 341, column: 30, scope: !219)
!677 = !DILocation(line: 341, column: 32, scope: !219)
!678 = !DILocation(line: 341, column: 2, scope: !219)
!679 = !DILocation(line: 344, column: 34, scope: !219)
!680 = !DILocation(line: 344, column: 15, scope: !219)
!681 = !DILocation(line: 344, column: 42, scope: !219)
!682 = !DILocation(line: 344, column: 44, scope: !219)
!683 = !DILocation(line: 344, column: 2, scope: !649)
!684 = !DILocation(line: 345, column: 33, scope: !219)
!685 = !DILocation(line: 345, column: 15, scope: !219)
!686 = !DILocation(line: 345, column: 41, scope: !219)
!687 = !DILocation(line: 345, column: 43, scope: !219)
!688 = !DILocation(line: 345, column: 2, scope: !649)
!689 = !DILocation(line: 346, column: 33, scope: !219)
!690 = !DILocation(line: 346, column: 15, scope: !219)
!691 = !DILocation(line: 346, column: 41, scope: !219)
!692 = !DILocation(line: 346, column: 43, scope: !219)
!693 = !DILocation(line: 346, column: 2, scope: !649)
!694 = !DILocation(line: 347, column: 35, scope: !219)
!695 = !DILocation(line: 347, column: 15, scope: !219)
!696 = !DILocation(line: 347, column: 43, scope: !219)
!697 = !DILocation(line: 347, column: 45, scope: !219)
!698 = !DILocation(line: 347, column: 2, scope: !649)
!699 = !DILocation(line: 348, column: 29, scope: !700)
!700 = distinct !DILexicalBlock(scope: !219, file: !1, line: 348, column: 6)
!701 = !DILocation(line: 348, column: 6, scope: !700)
!702 = !DILocation(line: 348, column: 36, scope: !700)
!703 = !DILocation(line: 349, column: 6, scope: !700)
!704 = !DILocation(line: 349, column: 32, scope: !705)
!705 = !DILexicalBlockFile(scope: !700, file: !1, discriminator: 1)
!706 = !DILocation(line: 349, column: 9, scope: !705)
!707 = !DILocation(line: 349, column: 39, scope: !705)
!708 = !DILocation(line: 348, column: 6, scope: !649)
!709 = !DILocation(line: 350, column: 37, scope: !700)
!710 = !DILocation(line: 350, column: 19, scope: !700)
!711 = !DILocation(line: 350, column: 45, scope: !700)
!712 = !DILocation(line: 350, column: 47, scope: !700)
!713 = !DILocation(line: 350, column: 6, scope: !705)
!714 = !DILocation(line: 350, column: 6, scope: !700)
!715 = !DILocation(line: 352, column: 22, scope: !700)
!716 = !DILocation(line: 352, column: 24, scope: !700)
!717 = !DILocation(line: 352, column: 6, scope: !700)
!718 = !DILocation(line: 353, column: 35, scope: !219)
!719 = !DILocation(line: 353, column: 15, scope: !219)
!720 = !DILocation(line: 353, column: 43, scope: !219)
!721 = !DILocation(line: 353, column: 45, scope: !219)
!722 = !DILocation(line: 353, column: 2, scope: !649)
!723 = !DILocation(line: 354, column: 15, scope: !219)
!724 = !DILocation(line: 354, column: 27, scope: !219)
!725 = !DILocation(line: 354, column: 29, scope: !219)
!726 = !DILocation(line: 354, column: 2, scope: !219)
!727 = !DILocation(line: 357, column: 29, scope: !728)
!728 = distinct !DILexicalBlock(scope: !219, file: !1, line: 357, column: 6)
!729 = !DILocation(line: 357, column: 6, scope: !728)
!730 = !DILocation(line: 357, column: 36, scope: !728)
!731 = !DILocation(line: 357, column: 6, scope: !219)
!732 = !DILocation(line: 358, column: 26, scope: !728)
!733 = !DILocation(line: 358, column: 3, scope: !728)
!734 = !DILocation(line: 361, column: 32, scope: !219)
!735 = !DILocation(line: 361, column: 49, scope: !219)
!736 = !DILocation(line: 361, column: 8, scope: !219)
!737 = !DILocation(line: 361, column: 6, scope: !219)
!738 = !DILocation(line: 362, column: 6, scope: !739)
!739 = distinct !DILexicalBlock(scope: !219, file: !1, line: 362, column: 6)
!740 = !DILocation(line: 362, column: 10, scope: !739)
!741 = !DILocation(line: 362, column: 6, scope: !219)
!742 = !DILocation(line: 363, column: 7, scope: !743)
!743 = distinct !DILexicalBlock(scope: !744, file: !1, line: 363, column: 7)
!744 = distinct !DILexicalBlock(scope: !739, file: !1, line: 362, column: 16)
!745 = !DILocation(line: 363, column: 13, scope: !743)
!746 = !DILocation(line: 363, column: 7, scope: !744)
!747 = !DILocation(line: 364, column: 23, scope: !748)
!748 = distinct !DILexicalBlock(scope: !743, file: !1, line: 363, column: 24)
!749 = !DILocation(line: 364, column: 26, scope: !748)
!750 = !DILocation(line: 364, column: 4, scope: !748)
!751 = !DILocation(line: 366, column: 14, scope: !748)
!752 = !DILocation(line: 367, column: 4, scope: !748)
!753 = !DILocation(line: 369, column: 22, scope: !744)
!754 = !DILocation(line: 369, column: 25, scope: !744)
!755 = !DILocation(line: 371, column: 29, scope: !744)
!756 = !DILocation(line: 371, column: 7, scope: !744)
!757 = !DILocation(line: 372, column: 46, scope: !744)
!758 = !DILocation(line: 372, column: 7, scope: !744)
!759 = !DILocation(line: 369, column: 3, scope: !744)
!760 = !DILocation(line: 373, column: 13, scope: !744)
!761 = !DILocation(line: 374, column: 2, scope: !744)
!762 = !DILocation(line: 375, column: 6, scope: !763)
!763 = distinct !DILexicalBlock(scope: !219, file: !1, line: 375, column: 6)
!764 = !DILocation(line: 375, column: 10, scope: !763)
!765 = !DILocation(line: 375, column: 14, scope: !763)
!766 = !DILocation(line: 375, column: 17, scope: !767)
!767 = !DILexicalBlockFile(scope: !763, file: !1, discriminator: 1)
!768 = !DILocation(line: 375, column: 19, scope: !767)
!769 = !DILocation(line: 375, column: 28, scope: !767)
!770 = !DILocation(line: 375, column: 33, scope: !771)
!771 = !DILexicalBlockFile(scope: !763, file: !1, discriminator: 2)
!772 = !DILocation(line: 375, column: 32, scope: !771)
!773 = !DILocation(line: 375, column: 35, scope: !771)
!774 = !DILocation(line: 375, column: 6, scope: !771)
!775 = !DILocation(line: 376, column: 29, scope: !763)
!776 = !DILocation(line: 376, column: 22, scope: !763)
!777 = !DILocation(line: 376, column: 33, scope: !763)
!778 = !DILocation(line: 376, column: 35, scope: !763)
!779 = !DILocation(line: 376, column: 9, scope: !767)
!780 = !DILocation(line: 376, column: 7, scope: !763)
!781 = !DILocation(line: 376, column: 3, scope: !763)
!782 = !DILocation(line: 379, column: 41, scope: !763)
!783 = !DILocation(line: 379, column: 22, scope: !763)
!784 = !DILocation(line: 380, column: 7, scope: !763)
!785 = !DILocation(line: 380, column: 9, scope: !763)
!786 = !DILocation(line: 379, column: 9, scope: !767)
!787 = !DILocation(line: 379, column: 7, scope: !763)
!788 = !DILocation(line: 381, column: 6, scope: !789)
!789 = distinct !DILexicalBlock(scope: !219, file: !1, line: 381, column: 6)
!790 = !DILocation(line: 381, column: 6, scope: !219)
!791 = !DILocation(line: 382, column: 22, scope: !792)
!792 = distinct !DILexicalBlock(scope: !789, file: !1, line: 381, column: 11)
!793 = !DILocation(line: 382, column: 25, scope: !792)
!794 = !DILocation(line: 382, column: 3, scope: !792)
!795 = !DILocation(line: 384, column: 13, scope: !792)
!796 = !DILocation(line: 385, column: 3, scope: !792)
!797 = !DILocation(line: 388, column: 31, scope: !219)
!798 = !DILocation(line: 388, column: 34, scope: !219)
!799 = !DILocation(line: 388, column: 8, scope: !219)
!800 = !DILocation(line: 388, column: 6, scope: !219)
!801 = !DILocation(line: 389, column: 6, scope: !802)
!802 = distinct !DILexicalBlock(scope: !219, file: !1, line: 389, column: 6)
!803 = !DILocation(line: 389, column: 10, scope: !802)
!804 = !DILocation(line: 389, column: 6, scope: !219)
!805 = !DILocation(line: 390, column: 13, scope: !806)
!806 = distinct !DILexicalBlock(scope: !802, file: !1, line: 389, column: 25)
!807 = !DILocation(line: 391, column: 3, scope: !806)
!808 = !DILocation(line: 394, column: 31, scope: !219)
!809 = !DILocation(line: 394, column: 34, scope: !219)
!810 = !DILocation(line: 394, column: 40, scope: !219)
!811 = !DILocation(line: 394, column: 8, scope: !219)
!812 = !DILocation(line: 394, column: 6, scope: !219)
!813 = !DILocation(line: 395, column: 6, scope: !814)
!814 = distinct !DILexicalBlock(scope: !219, file: !1, line: 395, column: 6)
!815 = !DILocation(line: 395, column: 10, scope: !814)
!816 = !DILocation(line: 395, column: 6, scope: !219)
!817 = !DILocation(line: 396, column: 13, scope: !818)
!818 = distinct !DILexicalBlock(scope: !814, file: !1, line: 395, column: 25)
!819 = !DILocation(line: 397, column: 3, scope: !818)
!820 = !DILocation(line: 400, column: 51, scope: !219)
!821 = !DILocation(line: 400, column: 32, scope: !219)
!822 = !DILocation(line: 400, column: 2, scope: !219)
!823 = !DILocation(line: 400, column: 8, scope: !219)
!824 = !DILocation(line: 400, column: 30, scope: !219)
!825 = !DILocation(line: 403, column: 6, scope: !826)
!826 = distinct !DILexicalBlock(scope: !219, file: !1, line: 403, column: 6)
!827 = !DILocation(line: 403, column: 8, scope: !826)
!828 = !DILocation(line: 403, column: 17, scope: !826)
!829 = !DILocation(line: 403, column: 22, scope: !830)
!830 = !DILexicalBlockFile(scope: !826, file: !1, discriminator: 1)
!831 = !DILocation(line: 403, column: 21, scope: !830)
!832 = !DILocation(line: 403, column: 24, scope: !830)
!833 = !DILocation(line: 403, column: 6, scope: !830)
!834 = !DILocation(line: 404, column: 32, scope: !835)
!835 = distinct !DILexicalBlock(scope: !826, file: !1, line: 403, column: 33)
!836 = !DILocation(line: 404, column: 35, scope: !835)
!837 = !DILocation(line: 404, column: 45, scope: !835)
!838 = !DILocation(line: 404, column: 38, scope: !835)
!839 = !DILocation(line: 404, column: 9, scope: !840)
!840 = !DILexicalBlockFile(scope: !835, file: !1, discriminator: 1)
!841 = !DILocation(line: 404, column: 7, scope: !835)
!842 = !DILocation(line: 405, column: 7, scope: !843)
!843 = distinct !DILexicalBlock(scope: !835, file: !1, line: 405, column: 7)
!844 = !DILocation(line: 405, column: 11, scope: !843)
!845 = !DILocation(line: 405, column: 7, scope: !835)
!846 = !DILocation(line: 406, column: 14, scope: !847)
!847 = distinct !DILexicalBlock(scope: !843, file: !1, line: 405, column: 26)
!848 = !DILocation(line: 407, column: 4, scope: !847)
!849 = !DILocation(line: 409, column: 2, scope: !835)
!850 = !DILocation(line: 403, column: 27, scope: !851)
!851 = !DILexicalBlockFile(scope: !826, file: !1, discriminator: 2)
!852 = !DILocation(line: 411, column: 6, scope: !853)
!853 = distinct !DILexicalBlock(scope: !219, file: !1, line: 411, column: 6)
!854 = !DILocation(line: 411, column: 6, scope: !219)
!855 = !DILocation(line: 412, column: 22, scope: !853)
!856 = !DILocation(line: 412, column: 3, scope: !853)
!857 = !DILocation(line: 413, column: 10, scope: !219)
!858 = !DILocation(line: 413, column: 2, scope: !219)
!859 = !DILocalVariable(name: "v", arg: 1, scope: !220, file: !1, line: 438, type: !52)
!860 = !DILocation(line: 438, column: 22, scope: !220)
!861 = !DILocalVariable(name: "p", arg: 2, scope: !220, file: !1, line: 438, type: !124)
!862 = !DILocation(line: 438, column: 31, scope: !220)
!863 = !DILocalVariable(name: "digits", arg: 3, scope: !220, file: !1, line: 438, type: !23)
!864 = !DILocation(line: 438, column: 38, scope: !220)
!865 = !DILocalVariable(name: "max", scope: !220, file: !1, line: 440, type: !52)
!866 = !DILocation(line: 440, column: 10, scope: !220)
!867 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 441, type: !23)
!868 = !DILocation(line: 441, column: 6, scope: !220)
!869 = !DILocation(line: 443, column: 26, scope: !220)
!870 = !DILocation(line: 443, column: 33, scope: !220)
!871 = !DILocation(line: 443, column: 22, scope: !220)
!872 = !DILocation(line: 443, column: 39, scope: !220)
!873 = !DILocation(line: 443, column: 6, scope: !220)
!874 = !DILocation(line: 444, column: 6, scope: !875)
!875 = distinct !DILexicalBlock(scope: !220, file: !1, line: 444, column: 6)
!876 = !DILocation(line: 444, column: 8, scope: !875)
!877 = !DILocation(line: 444, column: 14, scope: !875)
!878 = !DILocation(line: 444, column: 18, scope: !879)
!879 = !DILexicalBlockFile(scope: !875, file: !1, discriminator: 1)
!880 = !DILocation(line: 444, column: 23, scope: !879)
!881 = !DILocation(line: 444, column: 20, scope: !879)
!882 = !DILocation(line: 444, column: 6, scope: !879)
!883 = !DILocation(line: 445, column: 29, scope: !884)
!884 = distinct !DILexicalBlock(scope: !875, file: !1, line: 444, column: 28)
!885 = !DILocation(line: 445, column: 40, scope: !884)
!886 = !DILocation(line: 445, column: 43, scope: !884)
!887 = !DILocation(line: 445, column: 6, scope: !884)
!888 = !DILocation(line: 446, column: 10, scope: !884)
!889 = !DILocation(line: 447, column: 2, scope: !884)
!890 = !DILocation(line: 448, column: 29, scope: !891)
!891 = distinct !DILexicalBlock(scope: !875, file: !1, line: 447, column: 9)
!892 = !DILocation(line: 448, column: 42, scope: !891)
!893 = !DILocation(line: 448, column: 45, scope: !891)
!894 = !DILocation(line: 448, column: 6, scope: !891)
!895 = !DILocation(line: 449, column: 10, scope: !891)
!896 = !DILocation(line: 451, column: 10, scope: !220)
!897 = !DILocation(line: 451, column: 2, scope: !220)
!898 = !DILocalVariable(name: "cpio", arg: 1, scope: !226, file: !1, line: 175, type: !192)
!899 = !DILocation(line: 175, column: 35, scope: !226)
!900 = !DILocalVariable(name: "entry", arg: 2, scope: !226, file: !1, line: 175, type: !30)
!901 = !DILocation(line: 175, column: 63, scope: !226)
!902 = !DILocalVariable(name: "ino", scope: !226, file: !1, line: 177, type: !52)
!903 = !DILocation(line: 177, column: 10, scope: !226)
!904 = !DILocation(line: 177, column: 36, scope: !226)
!905 = !DILocation(line: 177, column: 16, scope: !226)
!906 = !DILocalVariable(name: "ino_new", scope: !226, file: !1, line: 178, type: !23)
!907 = !DILocation(line: 178, column: 6, scope: !226)
!908 = !DILocalVariable(name: "i", scope: !226, file: !1, line: 179, type: !45)
!909 = !DILocation(line: 179, column: 9, scope: !226)
!910 = !DILocation(line: 187, column: 6, scope: !911)
!911 = distinct !DILexicalBlock(scope: !226, file: !1, line: 187, column: 6)
!912 = !DILocation(line: 187, column: 10, scope: !911)
!913 = !DILocation(line: 187, column: 6, scope: !226)
!914 = !DILocation(line: 188, column: 3, scope: !911)
!915 = !DILocation(line: 191, column: 26, scope: !916)
!916 = distinct !DILexicalBlock(scope: !226, file: !1, line: 191, column: 6)
!917 = !DILocation(line: 191, column: 6, scope: !916)
!918 = !DILocation(line: 191, column: 33, scope: !916)
!919 = !DILocation(line: 191, column: 6, scope: !226)
!920 = !DILocation(line: 192, column: 18, scope: !921)
!921 = distinct !DILexicalBlock(scope: !916, file: !1, line: 191, column: 38)
!922 = !DILocation(line: 192, column: 24, scope: !921)
!923 = !DILocation(line: 192, column: 16, scope: !921)
!924 = !DILocation(line: 192, column: 10, scope: !921)
!925 = !DILocation(line: 192, column: 3, scope: !921)
!926 = !DILocation(line: 197, column: 9, scope: !927)
!927 = distinct !DILexicalBlock(scope: !226, file: !1, line: 197, column: 2)
!928 = !DILocation(line: 197, column: 7, scope: !927)
!929 = !DILocation(line: 197, column: 14, scope: !930)
!930 = !DILexicalBlockFile(scope: !931, file: !1, discriminator: 1)
!931 = distinct !DILexicalBlock(scope: !927, file: !1, line: 197, column: 2)
!932 = !DILocation(line: 197, column: 18, scope: !930)
!933 = !DILocation(line: 197, column: 24, scope: !930)
!934 = !DILocation(line: 197, column: 16, scope: !930)
!935 = !DILocation(line: 197, column: 2, scope: !930)
!936 = !DILocation(line: 198, column: 22, scope: !937)
!937 = distinct !DILexicalBlock(scope: !938, file: !1, line: 198, column: 7)
!938 = distinct !DILexicalBlock(scope: !931, file: !1, line: 197, column: 44)
!939 = !DILocation(line: 198, column: 7, scope: !937)
!940 = !DILocation(line: 198, column: 13, scope: !937)
!941 = !DILocation(line: 198, column: 25, scope: !937)
!942 = !DILocation(line: 198, column: 32, scope: !937)
!943 = !DILocation(line: 198, column: 29, scope: !937)
!944 = !DILocation(line: 198, column: 7, scope: !938)
!945 = !DILocation(line: 199, column: 27, scope: !937)
!946 = !DILocation(line: 199, column: 12, scope: !937)
!947 = !DILocation(line: 199, column: 18, scope: !937)
!948 = !DILocation(line: 199, column: 30, scope: !937)
!949 = !DILocation(line: 199, column: 4, scope: !937)
!950 = !DILocation(line: 200, column: 2, scope: !938)
!951 = !DILocation(line: 197, column: 39, scope: !952)
!952 = !DILexicalBlockFile(scope: !931, file: !1, discriminator: 2)
!953 = !DILocation(line: 197, column: 2, scope: !952)
!954 = !DILocation(line: 203, column: 20, scope: !226)
!955 = !DILocation(line: 203, column: 26, scope: !226)
!956 = !DILocation(line: 203, column: 18, scope: !226)
!957 = !DILocation(line: 203, column: 12, scope: !226)
!958 = !DILocation(line: 203, column: 10, scope: !226)
!959 = !DILocation(line: 206, column: 6, scope: !960)
!960 = distinct !DILexicalBlock(scope: !226, file: !1, line: 206, column: 6)
!961 = !DILocation(line: 206, column: 12, scope: !960)
!962 = !DILocation(line: 206, column: 29, scope: !960)
!963 = !DILocation(line: 206, column: 35, scope: !960)
!964 = !DILocation(line: 206, column: 26, scope: !960)
!965 = !DILocation(line: 206, column: 6, scope: !226)
!966 = !DILocalVariable(name: "newsize", scope: !967, file: !1, line: 207, type: !45)
!967 = distinct !DILexicalBlock(scope: !960, file: !1, line: 206, column: 50)
!968 = !DILocation(line: 207, column: 10, scope: !967)
!969 = !DILocation(line: 207, column: 20, scope: !967)
!970 = !DILocation(line: 207, column: 26, scope: !967)
!971 = !DILocation(line: 207, column: 40, scope: !967)
!972 = !DILocation(line: 207, column: 20, scope: !973)
!973 = !DILexicalBlockFile(scope: !967, file: !1, discriminator: 1)
!974 = !DILocation(line: 208, column: 15, scope: !967)
!975 = !DILocation(line: 208, column: 21, scope: !967)
!976 = !DILocation(line: 208, column: 35, scope: !967)
!977 = !DILocation(line: 207, column: 20, scope: !978)
!978 = !DILexicalBlockFile(scope: !967, file: !1, discriminator: 2)
!979 = !DILocation(line: 207, column: 20, scope: !980)
!980 = !DILexicalBlockFile(scope: !967, file: !1, discriminator: 3)
!981 = !DILocation(line: 207, column: 10, scope: !980)
!982 = !DILocalVariable(name: "newlist", scope: !967, file: !1, line: 209, type: !124)
!983 = !DILocation(line: 209, column: 9, scope: !967)
!984 = !DILocation(line: 209, column: 27, scope: !967)
!985 = !DILocation(line: 209, column: 33, scope: !967)
!986 = !DILocation(line: 210, column: 35, scope: !967)
!987 = !DILocation(line: 210, column: 33, scope: !967)
!988 = !DILocation(line: 209, column: 19, scope: !967)
!989 = !DILocation(line: 211, column: 7, scope: !990)
!990 = distinct !DILexicalBlock(scope: !967, file: !1, line: 211, column: 7)
!991 = !DILocation(line: 211, column: 15, scope: !990)
!992 = !DILocation(line: 211, column: 7, scope: !967)
!993 = !DILocation(line: 212, column: 4, scope: !990)
!994 = !DILocation(line: 214, column: 25, scope: !967)
!995 = !DILocation(line: 214, column: 3, scope: !967)
!996 = !DILocation(line: 214, column: 9, scope: !967)
!997 = !DILocation(line: 214, column: 23, scope: !967)
!998 = !DILocation(line: 215, column: 20, scope: !967)
!999 = !DILocation(line: 215, column: 3, scope: !967)
!1000 = !DILocation(line: 215, column: 9, scope: !967)
!1001 = !DILocation(line: 215, column: 18, scope: !967)
!1002 = !DILocation(line: 216, column: 2, scope: !967)
!1003 = !DILocation(line: 219, column: 44, scope: !226)
!1004 = !DILocation(line: 219, column: 17, scope: !226)
!1005 = !DILocation(line: 219, column: 23, scope: !226)
!1006 = !DILocation(line: 219, column: 2, scope: !226)
!1007 = !DILocation(line: 219, column: 8, scope: !226)
!1008 = !DILocation(line: 219, column: 38, scope: !226)
!1009 = !DILocation(line: 219, column: 42, scope: !226)
!1010 = !DILocation(line: 220, column: 44, scope: !226)
!1011 = !DILocation(line: 220, column: 17, scope: !226)
!1012 = !DILocation(line: 220, column: 23, scope: !226)
!1013 = !DILocation(line: 220, column: 2, scope: !226)
!1014 = !DILocation(line: 220, column: 8, scope: !226)
!1015 = !DILocation(line: 220, column: 38, scope: !226)
!1016 = !DILocation(line: 220, column: 42, scope: !226)
!1017 = !DILocation(line: 221, column: 4, scope: !226)
!1018 = !DILocation(line: 221, column: 10, scope: !226)
!1019 = !DILocation(line: 221, column: 2, scope: !226)
!1020 = !DILocation(line: 222, column: 10, scope: !226)
!1021 = !DILocation(line: 222, column: 2, scope: !226)
!1022 = !DILocation(line: 223, column: 1, scope: !226)
!1023 = !DILocalVariable(name: "v", arg: 1, scope: !223, file: !1, line: 455, type: !52)
!1024 = !DILocation(line: 455, column: 32, scope: !223)
!1025 = !DILocalVariable(name: "p", arg: 2, scope: !223, file: !1, line: 455, type: !95)
!1026 = !DILocation(line: 455, column: 41, scope: !223)
!1027 = !DILocalVariable(name: "s", arg: 3, scope: !223, file: !1, line: 455, type: !23)
!1028 = !DILocation(line: 455, column: 48, scope: !223)
!1029 = !DILocation(line: 457, column: 6, scope: !1030)
!1030 = distinct !DILexicalBlock(scope: !223, file: !1, line: 457, column: 6)
!1031 = !DILocation(line: 457, column: 8, scope: !1030)
!1032 = !DILocation(line: 457, column: 6, scope: !223)
!1033 = !DILocation(line: 458, column: 11, scope: !1030)
!1034 = !DILocation(line: 458, column: 3, scope: !1030)
!1035 = !DILocation(line: 459, column: 29, scope: !223)
!1036 = !DILocation(line: 459, column: 32, scope: !223)
!1037 = !DILocation(line: 459, column: 33, scope: !223)
!1038 = !DILocation(line: 459, column: 37, scope: !223)
!1039 = !DILocation(line: 459, column: 38, scope: !223)
!1040 = !DILocation(line: 459, column: 6, scope: !223)
!1041 = !DILocation(line: 459, column: 4, scope: !223)
!1042 = !DILocation(line: 460, column: 20, scope: !223)
!1043 = !DILocation(line: 460, column: 14, scope: !223)
!1044 = !DILocation(line: 460, column: 22, scope: !223)
!1045 = !DILocation(line: 460, column: 11, scope: !223)
!1046 = !DILocation(line: 460, column: 7, scope: !223)
!1047 = !DILocation(line: 460, column: 3, scope: !223)
!1048 = !DILocation(line: 460, column: 5, scope: !223)
!1049 = !DILocation(line: 461, column: 10, scope: !223)
!1050 = !DILocation(line: 461, column: 12, scope: !223)
!1051 = !DILocation(line: 461, column: 2, scope: !223)
!1052 = !DILocation(line: 462, column: 1, scope: !223)
