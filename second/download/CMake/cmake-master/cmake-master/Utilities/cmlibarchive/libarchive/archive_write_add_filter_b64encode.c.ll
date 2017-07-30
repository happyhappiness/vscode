; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_b64encode.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.private_b64encode = type { i32, %struct.archive_string, %struct.archive_string, i64, i64, [57 x i8] }

@.str = private unnamed_addr constant [28 x i8] c"archive_write_add_filter_uu\00", align 1
@.str.1 = private unnamed_addr constant [41 x i8] c"Can't allocate data for b64encode filter\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@.str.3 = private unnamed_addr constant [10 x i8] c"b64encode\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"mode\00", align 1
@.str.5 = private unnamed_addr constant [34 x i8] c"mode option requires octal digits\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@.str.7 = private unnamed_addr constant [30 x i8] c"name option requires a string\00", align 1
@.str.8 = private unnamed_addr constant [41 x i8] c"Can't allocate data for b64encode buffer\00", align 1
@.str.9 = private unnamed_addr constant [20 x i8] c"begin-base64 %o %s\0A\00", align 1
@base64 = internal constant [64 x i8] c"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", align 16
@.str.10 = private unnamed_addr constant [6 x i8] c"====\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_b64encode(%struct.archive* %_a) #0 !dbg !204 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %state = alloca %struct.private_b64encode*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !225, metadata !226), !dbg !227
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !228, metadata !226), !dbg !229
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !230
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !231
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !229
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !232, metadata !226), !dbg !233
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !234
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !235
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !233
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !236, metadata !226), !dbg !237
  br label %do.body, !dbg !238

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !239, metadata !226), !dbg !241
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !242
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 0, !dbg !242
  %call1 = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0)), !dbg !242
  store i32 %call1, i32* %magic_test, align 4, !dbg !242
  %4 = load i32, i32* %magic_test, align 4, !dbg !242
  %cmp = icmp eq i32 %4, -30, !dbg !242
  br i1 %cmp, label %if.then, label %if.end, !dbg !242

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !244
  br label %return, !dbg !244

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !247

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 136) #6, !dbg !249
  %5 = bitcast i8* %call2 to %struct.private_b64encode*, !dbg !250
  store %struct.private_b64encode* %5, %struct.private_b64encode** %state, align 8, !dbg !251
  %6 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !252
  %cmp3 = icmp eq %struct.private_b64encode* %6, null, !dbg !254
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !255

if.then4:                                         ; preds = %do.end
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !256
  %archive5 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 1, !dbg !258
  %8 = load %struct.archive*, %struct.archive** %archive5, align 8, !dbg !258
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %8, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.1, i32 0, i32 0)), !dbg !259
  store i32 -30, i32* %retval, align 4, !dbg !260
  br label %return, !dbg !260

if.end6:                                          ; preds = %do.end
  %9 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !261
  %name = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %9, i32 0, i32 1, !dbg !261
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 1, !dbg !261
  store i64 0, i64* %length, align 8, !dbg !261
  %10 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !261
  %name7 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %10, i32 0, i32 1, !dbg !261
  %call8 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %name7, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i64 1), !dbg !261
  %11 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !262
  %mode = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %11, i32 0, i32 0, !dbg !263
  store i32 420, i32* %mode, align 8, !dbg !264
  %12 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !265
  %13 = bitcast %struct.private_b64encode* %12 to i8*, !dbg !265
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !266
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %14, i32 0, i32 8, !dbg !267
  store i8* %13, i8** %data, align 8, !dbg !268
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !269
  %name9 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %15, i32 0, i32 9, !dbg !270
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i8** %name9, align 8, !dbg !271
  %16 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !272
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %16, i32 0, i32 10, !dbg !273
  store i32 7, i32* %code, align 8, !dbg !274
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !275
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %17, i32 0, i32 4, !dbg !276
  store i32 (%struct.archive_write_filter*)* @archive_filter_b64encode_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !277
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !278
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 3, !dbg !279
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_filter_b64encode_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !280
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !281
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %19, i32 0, i32 5, !dbg !282
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_filter_b64encode_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !283
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !284
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 6, !dbg !285
  store i32 (%struct.archive_write_filter*)* @archive_filter_b64encode_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !286
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !287
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %21, i32 0, i32 7, !dbg !288
  store i32 (%struct.archive_write_filter*)* @archive_filter_b64encode_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !289
  store i32 0, i32* %retval, align 4, !dbg !290
  br label %return, !dbg !290

return:                                           ; preds = %if.end6, %if.then4, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !291
  ret i32 %22, !dbg !291
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_b64encode_open(%struct.archive_write_filter* %f) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %state = alloca %struct.private_b64encode*, align 8
  %bs = alloca i64, align 8
  %bpb = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !292, metadata !226), !dbg !293
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !294, metadata !226), !dbg !295
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !296
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !297
  %1 = load i8*, i8** %data, align 8, !dbg !297
  %2 = bitcast i8* %1 to %struct.private_b64encode*, !dbg !298
  store %struct.private_b64encode* %2, %struct.private_b64encode** %state, align 8, !dbg !295
  call void @llvm.dbg.declare(metadata i64* %bs, metadata !299, metadata !226), !dbg !300
  store i64 65536, i64* %bs, align 8, !dbg !300
  call void @llvm.dbg.declare(metadata i64* %bpb, metadata !301, metadata !226), !dbg !302
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !303, metadata !226), !dbg !304
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !305
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 2, !dbg !306
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !306
  %call = call i32 @__archive_write_open_filter(%struct.archive_write_filter* %4), !dbg !307
  store i32 %call, i32* %ret, align 4, !dbg !308
  %5 = load i32, i32* %ret, align 4, !dbg !309
  %cmp = icmp ne i32 %5, 0, !dbg !311
  br i1 %cmp, label %if.then, label %if.end, !dbg !312

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %ret, align 4, !dbg !313
  store i32 %6, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !315
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 1, !dbg !317
  %8 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !317
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %8, i32 0, i32 0, !dbg !318
  %9 = load i32, i32* %magic, align 8, !dbg !318
  %cmp1 = icmp eq i32 %9, -1329217314, !dbg !319
  br i1 %cmp1, label %if.then2, label %if.end13, !dbg !320

if.then2:                                         ; preds = %if.end
  %10 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !321
  %archive3 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %10, i32 0, i32 1, !dbg !323
  %11 = load %struct.archive*, %struct.archive** %archive3, align 8, !dbg !323
  %call4 = call i32 @archive_write_get_bytes_per_block(%struct.archive* %11), !dbg !324
  %conv = sext i32 %call4 to i64, !dbg !324
  store i64 %conv, i64* %bpb, align 8, !dbg !325
  %12 = load i64, i64* %bpb, align 8, !dbg !326
  %13 = load i64, i64* %bs, align 8, !dbg !328
  %cmp5 = icmp ugt i64 %12, %13, !dbg !329
  br i1 %cmp5, label %if.then7, label %if.else, !dbg !330

if.then7:                                         ; preds = %if.then2
  %14 = load i64, i64* %bpb, align 8, !dbg !331
  store i64 %14, i64* %bs, align 8, !dbg !332
  br label %if.end12, !dbg !333

if.else:                                          ; preds = %if.then2
  %15 = load i64, i64* %bpb, align 8, !dbg !334
  %cmp8 = icmp ne i64 %15, 0, !dbg !336
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !337

if.then10:                                        ; preds = %if.else
  %16 = load i64, i64* %bs, align 8, !dbg !338
  %17 = load i64, i64* %bpb, align 8, !dbg !339
  %rem = urem i64 %16, %17, !dbg !340
  %18 = load i64, i64* %bs, align 8, !dbg !341
  %sub = sub i64 %18, %rem, !dbg !341
  store i64 %sub, i64* %bs, align 8, !dbg !341
  br label %if.end11, !dbg !342

if.end11:                                         ; preds = %if.then10, %if.else
  br label %if.end12

if.end12:                                         ; preds = %if.end11, %if.then7
  br label %if.end13, !dbg !343

if.end13:                                         ; preds = %if.end12, %if.end
  %19 = load i64, i64* %bs, align 8, !dbg !344
  %20 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !345
  %bs14 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %20, i32 0, i32 3, !dbg !346
  store i64 %19, i64* %bs14, align 8, !dbg !347
  %21 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !348
  %encoded_buff = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %21, i32 0, i32 2, !dbg !350
  %22 = load i64, i64* %bs, align 8, !dbg !351
  %add = add i64 %22, 512, !dbg !352
  %call15 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %encoded_buff, i64 %add), !dbg !353
  %cmp16 = icmp eq %struct.archive_string* %call15, null, !dbg !354
  br i1 %cmp16, label %if.then18, label %if.end20, !dbg !355

if.then18:                                        ; preds = %if.end13
  %23 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !356
  %archive19 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %23, i32 0, i32 1, !dbg !358
  %24 = load %struct.archive*, %struct.archive** %archive19, align 8, !dbg !358
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %24, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.8, i32 0, i32 0)), !dbg !359
  store i32 -30, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

if.end20:                                         ; preds = %if.end13
  %25 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !361
  %encoded_buff21 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %25, i32 0, i32 2, !dbg !362
  %26 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !363
  %mode = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %26, i32 0, i32 0, !dbg !364
  %27 = load i32, i32* %mode, align 8, !dbg !364
  %28 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !365
  %name = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %28, i32 0, i32 1, !dbg !366
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 0, !dbg !367
  %29 = load i8*, i8** %s, align 8, !dbg !367
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %encoded_buff21, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.9, i32 0, i32 0), i32 %27, i8* %29), !dbg !368
  %30 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !369
  %31 = bitcast %struct.private_b64encode* %30 to i8*, !dbg !369
  %32 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !370
  %data22 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %32, i32 0, i32 8, !dbg !371
  store i8* %31, i8** %data22, align 8, !dbg !372
  store i32 0, i32* %retval, align 4, !dbg !373
  br label %return, !dbg !373

return:                                           ; preds = %if.end20, %if.then18, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !374
  ret i32 %33, !dbg !374
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_b64encode_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %state = alloca %struct.private_b64encode*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !375, metadata !226), !dbg !376
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !377, metadata !226), !dbg !378
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !379, metadata !226), !dbg !380
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !381, metadata !226), !dbg !382
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !383
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !384
  %1 = load i8*, i8** %data, align 8, !dbg !384
  %2 = bitcast i8* %1 to %struct.private_b64encode*, !dbg !385
  store %struct.private_b64encode* %2, %struct.private_b64encode** %state, align 8, !dbg !382
  %3 = load i8*, i8** %key.addr, align 8, !dbg !386
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)) #7, !dbg !388
  %cmp = icmp eq i32 %call, 0, !dbg !389
  br i1 %cmp, label %if.then, label %if.else, !dbg !390

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %value.addr, align 8, !dbg !391
  %cmp1 = icmp eq i8* %4, null, !dbg !394
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !395

if.then2:                                         ; preds = %if.then
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !396
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 1, !dbg !398
  %6 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !398
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 -1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.5, i32 0, i32 0)), !dbg !399
  store i32 -25, i32* %retval, align 4, !dbg !400
  br label %return, !dbg !400

if.end:                                           ; preds = %if.then
  %7 = load i8*, i8** %value.addr, align 8, !dbg !401
  %8 = load i8*, i8** %value.addr, align 8, !dbg !402
  %call3 = call i64 @strlen(i8* %8) #7, !dbg !403
  %call4 = call i64 @atol8(i8* %7, i64 %call3), !dbg !404
  %conv = trunc i64 %call4 to i32, !dbg !406
  %and = and i32 %conv, 511, !dbg !407
  %9 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !408
  %mode = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %9, i32 0, i32 0, !dbg !409
  store i32 %and, i32* %mode, align 8, !dbg !410
  store i32 0, i32* %retval, align 4, !dbg !411
  br label %return, !dbg !411

if.else:                                          ; preds = %entry
  %10 = load i8*, i8** %key.addr, align 8, !dbg !412
  %call5 = call i32 @strcmp(i8* %10, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i32 0, i32 0)) #7, !dbg !414
  %cmp6 = icmp eq i32 %call5, 0, !dbg !415
  br i1 %cmp6, label %if.then8, label %if.end19, !dbg !416

if.then8:                                         ; preds = %if.else
  %11 = load i8*, i8** %value.addr, align 8, !dbg !417
  %cmp9 = icmp eq i8* %11, null, !dbg !420
  br i1 %cmp9, label %if.then11, label %if.end13, !dbg !421

if.then11:                                        ; preds = %if.then8
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !422
  %archive12 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 1, !dbg !424
  %13 = load %struct.archive*, %struct.archive** %archive12, align 8, !dbg !424
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 -1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.7, i32 0, i32 0)), !dbg !425
  store i32 -25, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

if.end13:                                         ; preds = %if.then8
  %14 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !427
  %name = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %14, i32 0, i32 1, !dbg !427
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 1, !dbg !427
  store i64 0, i64* %length, align 8, !dbg !427
  %15 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !427
  %name14 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %15, i32 0, i32 1, !dbg !427
  %16 = load i8*, i8** %value.addr, align 8, !dbg !427
  %17 = load i8*, i8** %value.addr, align 8, !dbg !427
  %cmp15 = icmp eq i8* %17, null, !dbg !427
  br i1 %cmp15, label %cond.true, label %cond.false, !dbg !427

cond.true:                                        ; preds = %if.end13
  br label %cond.end, !dbg !428

cond.false:                                       ; preds = %if.end13
  %18 = load i8*, i8** %value.addr, align 8, !dbg !430
  %call17 = call i64 @strlen(i8* %18) #7, !dbg !430
  br label %cond.end, !dbg !430

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call17, %cond.false ], !dbg !432
  %call18 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %name14, i8* %16, i64 %cond), !dbg !432
  store i32 0, i32* %retval, align 4, !dbg !434
  br label %return, !dbg !434

if.end19:                                         ; preds = %if.else
  br label %if.end20

if.end20:                                         ; preds = %if.end19
  store i32 -20, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

return:                                           ; preds = %if.end20, %cond.end, %if.then11, %if.end, %if.then2
  %19 = load i32, i32* %retval, align 4, !dbg !436
  ret i32 %19, !dbg !436
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_b64encode_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !210 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %state = alloca %struct.private_b64encode*, align 8
  %p = alloca i8*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !437, metadata !226), !dbg !438
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !439, metadata !226), !dbg !440
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !441, metadata !226), !dbg !442
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !443, metadata !226), !dbg !444
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !445
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !446
  %1 = load i8*, i8** %data, align 8, !dbg !446
  %2 = bitcast i8* %1 to %struct.private_b64encode*, !dbg !447
  store %struct.private_b64encode* %2, %struct.private_b64encode** %state, align 8, !dbg !444
  call void @llvm.dbg.declare(metadata i8** %p, metadata !448, metadata !226), !dbg !449
  %3 = load i8*, i8** %buff.addr, align 8, !dbg !450
  store i8* %3, i8** %p, align 8, !dbg !449
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !451, metadata !226), !dbg !452
  store i32 0, i32* %ret, align 4, !dbg !452
  %4 = load i64, i64* %length.addr, align 8, !dbg !453
  %cmp = icmp eq i64 %4, 0, !dbg !455
  br i1 %cmp, label %if.then, label %if.end, !dbg !456

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %ret, align 4, !dbg !457
  store i32 %5, i32* %retval, align 4, !dbg !458
  br label %return, !dbg !458

if.end:                                           ; preds = %entry
  %6 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !459
  %hold_len = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %6, i32 0, i32 4, !dbg !461
  %7 = load i64, i64* %hold_len, align 8, !dbg !461
  %tobool = icmp ne i64 %7, 0, !dbg !459
  br i1 %tobool, label %if.then1, label %if.end12, !dbg !462

if.then1:                                         ; preds = %if.end
  br label %while.cond, !dbg !463

while.cond:                                       ; preds = %while.body, %if.then1
  %8 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !465
  %hold_len2 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %8, i32 0, i32 4, !dbg !467
  %9 = load i64, i64* %hold_len2, align 8, !dbg !467
  %cmp3 = icmp ult i64 %9, 57, !dbg !468
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !469

land.rhs:                                         ; preds = %while.cond
  %10 = load i64, i64* %length.addr, align 8, !dbg !470
  %cmp4 = icmp ugt i64 %10, 0, !dbg !472
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %11 = phi i1 [ false, %while.cond ], [ %cmp4, %land.rhs ]
  br i1 %11, label %while.body, label %while.end, !dbg !473

while.body:                                       ; preds = %land.end
  %12 = load i8*, i8** %p, align 8, !dbg !475
  %incdec.ptr = getelementptr inbounds i8, i8* %12, i32 1, !dbg !475
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !475
  %13 = load i8, i8* %12, align 1, !dbg !477
  %14 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !478
  %hold_len5 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %14, i32 0, i32 4, !dbg !479
  %15 = load i64, i64* %hold_len5, align 8, !dbg !480
  %inc = add i64 %15, 1, !dbg !480
  store i64 %inc, i64* %hold_len5, align 8, !dbg !480
  %16 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !481
  %hold = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %16, i32 0, i32 5, !dbg !482
  %arrayidx = getelementptr inbounds [57 x i8], [57 x i8]* %hold, i64 0, i64 %15, !dbg !481
  store i8 %13, i8* %arrayidx, align 1, !dbg !483
  %17 = load i64, i64* %length.addr, align 8, !dbg !484
  %dec = add i64 %17, -1, !dbg !484
  store i64 %dec, i64* %length.addr, align 8, !dbg !484
  br label %while.cond, !dbg !485

while.end:                                        ; preds = %land.end
  %18 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !487
  %hold_len6 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %18, i32 0, i32 4, !dbg !489
  %19 = load i64, i64* %hold_len6, align 8, !dbg !489
  %cmp7 = icmp ult i64 %19, 57, !dbg !490
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !491

if.then8:                                         ; preds = %while.end
  %20 = load i32, i32* %ret, align 4, !dbg !492
  store i32 %20, i32* %retval, align 4, !dbg !493
  br label %return, !dbg !493

if.end9:                                          ; preds = %while.end
  %21 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !494
  %encoded_buff = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %21, i32 0, i32 2, !dbg !495
  %22 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !496
  %hold10 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %22, i32 0, i32 5, !dbg !497
  %arraydecay = getelementptr inbounds [57 x i8], [57 x i8]* %hold10, i32 0, i32 0, !dbg !496
  call void @b64_encode(%struct.archive_string* %encoded_buff, i8* %arraydecay, i64 57), !dbg !498
  %23 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !499
  %hold_len11 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %23, i32 0, i32 4, !dbg !500
  store i64 0, i64* %hold_len11, align 8, !dbg !501
  br label %if.end12, !dbg !502

if.end12:                                         ; preds = %if.end9, %if.end
  br label %for.cond, !dbg !503

for.cond:                                         ; preds = %for.inc, %if.end12
  %24 = load i64, i64* %length.addr, align 8, !dbg !504
  %cmp13 = icmp uge i64 %24, 57, !dbg !508
  br i1 %cmp13, label %for.body, label %for.end, !dbg !509

for.body:                                         ; preds = %for.cond
  %25 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !510
  %encoded_buff14 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %25, i32 0, i32 2, !dbg !511
  %26 = load i8*, i8** %p, align 8, !dbg !512
  call void @b64_encode(%struct.archive_string* %encoded_buff14, i8* %26, i64 57), !dbg !513
  br label %for.inc, !dbg !513

for.inc:                                          ; preds = %for.body
  %27 = load i64, i64* %length.addr, align 8, !dbg !514
  %sub = sub i64 %27, 57, !dbg !514
  store i64 %sub, i64* %length.addr, align 8, !dbg !514
  %28 = load i8*, i8** %p, align 8, !dbg !516
  %add.ptr = getelementptr inbounds i8, i8* %28, i64 57, !dbg !516
  store i8* %add.ptr, i8** %p, align 8, !dbg !516
  br label %for.cond, !dbg !517

for.end:                                          ; preds = %for.cond
  %29 = load i64, i64* %length.addr, align 8, !dbg !518
  %cmp15 = icmp ugt i64 %29, 0, !dbg !520
  br i1 %cmp15, label %if.then16, label %if.end20, !dbg !521

if.then16:                                        ; preds = %for.end
  %30 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !522
  %hold17 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %30, i32 0, i32 5, !dbg !524
  %arraydecay18 = getelementptr inbounds [57 x i8], [57 x i8]* %hold17, i32 0, i32 0, !dbg !525
  %31 = load i8*, i8** %p, align 8, !dbg !526
  %32 = load i64, i64* %length.addr, align 8, !dbg !527
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay18, i8* %31, i64 %32, i32 1, i1 false), !dbg !525
  %33 = load i64, i64* %length.addr, align 8, !dbg !528
  %34 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !529
  %hold_len19 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %34, i32 0, i32 4, !dbg !530
  store i64 %33, i64* %hold_len19, align 8, !dbg !531
  br label %if.end20, !dbg !532

if.end20:                                         ; preds = %if.then16, %for.end
  br label %while.cond21, !dbg !533

while.cond21:                                     ; preds = %while.body25, %if.end20
  %35 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !534
  %encoded_buff22 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %35, i32 0, i32 2, !dbg !534
  %length23 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff22, i32 0, i32 1, !dbg !534
  %36 = load i64, i64* %length23, align 8, !dbg !534
  %37 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !536
  %bs = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %37, i32 0, i32 3, !dbg !537
  %38 = load i64, i64* %bs, align 8, !dbg !537
  %cmp24 = icmp uge i64 %36, %38, !dbg !538
  br i1 %cmp24, label %while.body25, label %while.end42, !dbg !539

while.body25:                                     ; preds = %while.cond21
  %39 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !540
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %39, i32 0, i32 2, !dbg !542
  %40 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !542
  %41 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !543
  %encoded_buff26 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %41, i32 0, i32 2, !dbg !544
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff26, i32 0, i32 0, !dbg !545
  %42 = load i8*, i8** %s, align 8, !dbg !545
  %43 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !546
  %bs27 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %43, i32 0, i32 3, !dbg !547
  %44 = load i64, i64* %bs27, align 8, !dbg !547
  %call = call i32 @__archive_write_filter(%struct.archive_write_filter* %40, i8* %42, i64 %44), !dbg !548
  store i32 %call, i32* %ret, align 4, !dbg !549
  %45 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !550
  %encoded_buff28 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %45, i32 0, i32 2, !dbg !551
  %s29 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff28, i32 0, i32 0, !dbg !552
  %46 = load i8*, i8** %s29, align 8, !dbg !552
  %47 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !553
  %encoded_buff30 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %47, i32 0, i32 2, !dbg !554
  %s31 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff30, i32 0, i32 0, !dbg !555
  %48 = load i8*, i8** %s31, align 8, !dbg !555
  %49 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !556
  %bs32 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %49, i32 0, i32 3, !dbg !557
  %50 = load i64, i64* %bs32, align 8, !dbg !557
  %add.ptr33 = getelementptr inbounds i8, i8* %48, i64 %50, !dbg !558
  %51 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !559
  %encoded_buff34 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %51, i32 0, i32 2, !dbg !560
  %length35 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff34, i32 0, i32 1, !dbg !561
  %52 = load i64, i64* %length35, align 8, !dbg !561
  %53 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !562
  %bs36 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %53, i32 0, i32 3, !dbg !563
  %54 = load i64, i64* %bs36, align 8, !dbg !563
  %sub37 = sub i64 %52, %54, !dbg !564
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %46, i8* %add.ptr33, i64 %sub37, i32 1, i1 false), !dbg !565
  %55 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !566
  %bs38 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %55, i32 0, i32 3, !dbg !567
  %56 = load i64, i64* %bs38, align 8, !dbg !567
  %57 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !568
  %encoded_buff39 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %57, i32 0, i32 2, !dbg !569
  %length40 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff39, i32 0, i32 1, !dbg !570
  %58 = load i64, i64* %length40, align 8, !dbg !571
  %sub41 = sub i64 %58, %56, !dbg !571
  store i64 %sub41, i64* %length40, align 8, !dbg !571
  br label %while.cond21, !dbg !572

while.end42:                                      ; preds = %while.cond21
  %59 = load i32, i32* %ret, align 4, !dbg !574
  store i32 %59, i32* %retval, align 4, !dbg !575
  br label %return, !dbg !575

return:                                           ; preds = %while.end42, %if.then8, %if.then
  %60 = load i32, i32* %retval, align 4, !dbg !576
  ret i32 %60, !dbg !576
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_b64encode_close(%struct.archive_write_filter* %f) #0 !dbg !215 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %state = alloca %struct.private_b64encode*, align 8
  %ret = alloca i32, align 4
  %ret2 = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !577, metadata !226), !dbg !578
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !579, metadata !226), !dbg !580
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !581
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !582
  %1 = load i8*, i8** %data, align 8, !dbg !582
  %2 = bitcast i8* %1 to %struct.private_b64encode*, !dbg !583
  store %struct.private_b64encode* %2, %struct.private_b64encode** %state, align 8, !dbg !580
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !584, metadata !226), !dbg !585
  call void @llvm.dbg.declare(metadata i32* %ret2, metadata !586, metadata !226), !dbg !587
  %3 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !588
  %hold_len = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %3, i32 0, i32 4, !dbg !590
  %4 = load i64, i64* %hold_len, align 8, !dbg !590
  %cmp = icmp ne i64 %4, 0, !dbg !591
  br i1 %cmp, label %if.then, label %if.end, !dbg !592

if.then:                                          ; preds = %entry
  %5 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !593
  %encoded_buff = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %5, i32 0, i32 2, !dbg !594
  %6 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !595
  %hold = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %6, i32 0, i32 5, !dbg !596
  %arraydecay = getelementptr inbounds [57 x i8], [57 x i8]* %hold, i32 0, i32 0, !dbg !595
  %7 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !597
  %hold_len1 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %7, i32 0, i32 4, !dbg !598
  %8 = load i64, i64* %hold_len1, align 8, !dbg !598
  call void @b64_encode(%struct.archive_string* %encoded_buff, i8* %arraydecay, i64 %8), !dbg !599
  br label %if.end, !dbg !599

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !600
  %encoded_buff2 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %9, i32 0, i32 2, !dbg !601
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %encoded_buff2, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)), !dbg !602
  %10 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !603
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %10, i32 0, i32 1, !dbg !604
  %11 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !604
  %call = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %11, i32 1), !dbg !605
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !606
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 2, !dbg !607
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !607
  %14 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !608
  %encoded_buff3 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %14, i32 0, i32 2, !dbg !609
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff3, i32 0, i32 0, !dbg !610
  %15 = load i8*, i8** %s, align 8, !dbg !610
  %16 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !611
  %encoded_buff4 = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %16, i32 0, i32 2, !dbg !611
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %encoded_buff4, i32 0, i32 1, !dbg !611
  %17 = load i64, i64* %length, align 8, !dbg !611
  %call5 = call i32 @__archive_write_filter(%struct.archive_write_filter* %13, i8* %15, i64 %17), !dbg !612
  store i32 %call5, i32* %ret, align 4, !dbg !613
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !614
  %next_filter6 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 2, !dbg !615
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter6, align 8, !dbg !615
  %call7 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %19), !dbg !616
  store i32 %call7, i32* %ret2, align 4, !dbg !617
  %20 = load i32, i32* %ret, align 4, !dbg !618
  %21 = load i32, i32* %ret2, align 4, !dbg !620
  %cmp8 = icmp sgt i32 %20, %21, !dbg !621
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !622

if.then9:                                         ; preds = %if.end
  %22 = load i32, i32* %ret2, align 4, !dbg !623
  store i32 %22, i32* %ret, align 4, !dbg !624
  br label %if.end10, !dbg !625

if.end10:                                         ; preds = %if.then9, %if.end
  %23 = load i32, i32* %ret, align 4, !dbg !626
  ret i32 %23, !dbg !627
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_b64encode_free(%struct.archive_write_filter* %f) #0 !dbg !216 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %state = alloca %struct.private_b64encode*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !628, metadata !226), !dbg !629
  call void @llvm.dbg.declare(metadata %struct.private_b64encode** %state, metadata !630, metadata !226), !dbg !631
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !632
  %data = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !633
  %1 = load i8*, i8** %data, align 8, !dbg !633
  %2 = bitcast i8* %1 to %struct.private_b64encode*, !dbg !634
  store %struct.private_b64encode* %2, %struct.private_b64encode** %state, align 8, !dbg !631
  %3 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !635
  %name = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %3, i32 0, i32 1, !dbg !636
  call void @archive_string_free(%struct.archive_string* %name), !dbg !637
  %4 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !638
  %encoded_buff = getelementptr inbounds %struct.private_b64encode, %struct.private_b64encode* %4, i32 0, i32 2, !dbg !639
  call void @archive_string_free(%struct.archive_string* %encoded_buff), !dbg !640
  %5 = load %struct.private_b64encode*, %struct.private_b64encode** %state, align 8, !dbg !641
  %6 = bitcast %struct.private_b64encode* %5 to i8*, !dbg !641
  call void @free(i8* %6) #6, !dbg !642
  ret i32 0, !dbg !643
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i64 @atol8(i8* %p, i64 %char_cnt) #0 !dbg !206 {
entry:
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  %l = alloca i64, align 8
  %digit = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !644, metadata !226), !dbg !645
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !646, metadata !226), !dbg !647
  call void @llvm.dbg.declare(metadata i64* %l, metadata !648, metadata !226), !dbg !649
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !650, metadata !226), !dbg !651
  store i64 0, i64* %l, align 8, !dbg !652
  br label %while.cond, !dbg !653

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i64, i64* %char_cnt.addr, align 8, !dbg !654
  %dec = add i64 %0, -1, !dbg !654
  store i64 %dec, i64* %char_cnt.addr, align 8, !dbg !654
  %cmp = icmp ugt i64 %0, 0, !dbg !656
  br i1 %cmp, label %while.body, label %while.end, !dbg !657

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !658
  %2 = load i8, i8* %1, align 1, !dbg !661
  %conv = sext i8 %2 to i32, !dbg !661
  %cmp1 = icmp sge i32 %conv, 48, !dbg !662
  br i1 %cmp1, label %land.lhs.true, label %if.else, !dbg !663

land.lhs.true:                                    ; preds = %while.body
  %3 = load i8*, i8** %p.addr, align 8, !dbg !664
  %4 = load i8, i8* %3, align 1, !dbg !666
  %conv3 = sext i8 %4 to i32, !dbg !666
  %cmp4 = icmp sle i32 %conv3, 55, !dbg !667
  br i1 %cmp4, label %if.then, label %if.else, !dbg !668

if.then:                                          ; preds = %land.lhs.true
  %5 = load i8*, i8** %p.addr, align 8, !dbg !669
  %6 = load i8, i8* %5, align 1, !dbg !670
  %conv6 = sext i8 %6 to i32, !dbg !670
  %sub = sub nsw i32 %conv6, 48, !dbg !671
  store i32 %sub, i32* %digit, align 4, !dbg !672
  br label %if.end, !dbg !673

if.else:                                          ; preds = %land.lhs.true, %while.body
  br label %while.end, !dbg !674

if.end:                                           ; preds = %if.then
  %7 = load i8*, i8** %p.addr, align 8, !dbg !675
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !675
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !675
  %8 = load i64, i64* %l, align 8, !dbg !676
  %shl = shl i64 %8, 3, !dbg !676
  store i64 %shl, i64* %l, align 8, !dbg !676
  %9 = load i32, i32* %digit, align 4, !dbg !677
  %conv7 = sext i32 %9 to i64, !dbg !677
  %10 = load i64, i64* %l, align 8, !dbg !678
  %or = or i64 %10, %conv7, !dbg !678
  store i64 %or, i64* %l, align 8, !dbg !678
  br label %while.cond, !dbg !679

while.end:                                        ; preds = %if.else, %while.cond
  %11 = load i64, i64* %l, align 8, !dbg !681
  ret i64 %11, !dbg !682
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @__archive_write_open_filter(%struct.archive_write_filter*) #2

declare i32 @archive_write_get_bytes_per_block(%struct.archive*) #2

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal void @b64_encode(%struct.archive_string* %as, i8* %p, i64 %len) #0 !dbg !211 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %c = alloca i32, align 4
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !683, metadata !226), !dbg !684
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !685, metadata !226), !dbg !686
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !687, metadata !226), !dbg !688
  call void @llvm.dbg.declare(metadata i32* %c, metadata !689, metadata !226), !dbg !690
  br label %for.cond, !dbg !691

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %len.addr, align 8, !dbg !692
  %cmp = icmp uge i64 %0, 3, !dbg !696
  br i1 %cmp, label %for.body, label %for.end, !dbg !697

for.body:                                         ; preds = %for.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !698
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !698
  %2 = load i8, i8* %arrayidx, align 1, !dbg !698
  %conv = zext i8 %2 to i32, !dbg !698
  %shr = ashr i32 %conv, 2, !dbg !700
  store i32 %shr, i32* %c, align 4, !dbg !701
  %3 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !702
  %4 = load i32, i32* %c, align 4, !dbg !703
  %idxprom = sext i32 %4 to i64, !dbg !704
  %arrayidx1 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom, !dbg !704
  %5 = load i8, i8* %arrayidx1, align 1, !dbg !704
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %3, i8 signext %5), !dbg !705
  %6 = load i8*, i8** %p.addr, align 8, !dbg !706
  %arrayidx2 = getelementptr inbounds i8, i8* %6, i64 0, !dbg !706
  %7 = load i8, i8* %arrayidx2, align 1, !dbg !706
  %conv3 = zext i8 %7 to i32, !dbg !706
  %and = and i32 %conv3, 3, !dbg !707
  %shl = shl i32 %and, 4, !dbg !708
  %8 = load i8*, i8** %p.addr, align 8, !dbg !709
  %arrayidx4 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !709
  %9 = load i8, i8* %arrayidx4, align 1, !dbg !709
  %conv5 = zext i8 %9 to i32, !dbg !709
  %and6 = and i32 %conv5, 240, !dbg !710
  %shr7 = ashr i32 %and6, 4, !dbg !711
  %or = or i32 %shl, %shr7, !dbg !712
  store i32 %or, i32* %c, align 4, !dbg !713
  %10 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !714
  %11 = load i32, i32* %c, align 4, !dbg !715
  %idxprom8 = sext i32 %11 to i64, !dbg !716
  %arrayidx9 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom8, !dbg !716
  %12 = load i8, i8* %arrayidx9, align 1, !dbg !716
  %call10 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %10, i8 signext %12), !dbg !717
  %13 = load i8*, i8** %p.addr, align 8, !dbg !718
  %arrayidx11 = getelementptr inbounds i8, i8* %13, i64 1, !dbg !718
  %14 = load i8, i8* %arrayidx11, align 1, !dbg !718
  %conv12 = zext i8 %14 to i32, !dbg !718
  %and13 = and i32 %conv12, 15, !dbg !719
  %shl14 = shl i32 %and13, 2, !dbg !720
  %15 = load i8*, i8** %p.addr, align 8, !dbg !721
  %arrayidx15 = getelementptr inbounds i8, i8* %15, i64 2, !dbg !721
  %16 = load i8, i8* %arrayidx15, align 1, !dbg !721
  %conv16 = zext i8 %16 to i32, !dbg !721
  %and17 = and i32 %conv16, 192, !dbg !722
  %shr18 = ashr i32 %and17, 6, !dbg !723
  %or19 = or i32 %shl14, %shr18, !dbg !724
  store i32 %or19, i32* %c, align 4, !dbg !725
  %17 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !726
  %18 = load i32, i32* %c, align 4, !dbg !727
  %idxprom20 = sext i32 %18 to i64, !dbg !728
  %arrayidx21 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom20, !dbg !728
  %19 = load i8, i8* %arrayidx21, align 1, !dbg !728
  %call22 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %17, i8 signext %19), !dbg !729
  %20 = load i8*, i8** %p.addr, align 8, !dbg !730
  %arrayidx23 = getelementptr inbounds i8, i8* %20, i64 2, !dbg !730
  %21 = load i8, i8* %arrayidx23, align 1, !dbg !730
  %conv24 = zext i8 %21 to i32, !dbg !730
  %and25 = and i32 %conv24, 63, !dbg !731
  store i32 %and25, i32* %c, align 4, !dbg !732
  %22 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !733
  %23 = load i32, i32* %c, align 4, !dbg !734
  %idxprom26 = sext i32 %23 to i64, !dbg !735
  %arrayidx27 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom26, !dbg !735
  %24 = load i8, i8* %arrayidx27, align 1, !dbg !735
  %call28 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %22, i8 signext %24), !dbg !736
  br label %for.inc, !dbg !737

for.inc:                                          ; preds = %for.body
  %25 = load i8*, i8** %p.addr, align 8, !dbg !738
  %add.ptr = getelementptr inbounds i8, i8* %25, i64 3, !dbg !738
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !738
  %26 = load i64, i64* %len.addr, align 8, !dbg !740
  %sub = sub i64 %26, 3, !dbg !740
  store i64 %sub, i64* %len.addr, align 8, !dbg !740
  br label %for.cond, !dbg !741

for.end:                                          ; preds = %for.cond
  %27 = load i64, i64* %len.addr, align 8, !dbg !742
  %cmp29 = icmp ugt i64 %27, 0, !dbg !744
  br i1 %cmp29, label %if.then, label %if.end65, !dbg !745

if.then:                                          ; preds = %for.end
  %28 = load i8*, i8** %p.addr, align 8, !dbg !746
  %arrayidx31 = getelementptr inbounds i8, i8* %28, i64 0, !dbg !746
  %29 = load i8, i8* %arrayidx31, align 1, !dbg !746
  %conv32 = zext i8 %29 to i32, !dbg !746
  %shr33 = ashr i32 %conv32, 2, !dbg !748
  store i32 %shr33, i32* %c, align 4, !dbg !749
  %30 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !750
  %31 = load i32, i32* %c, align 4, !dbg !751
  %idxprom34 = sext i32 %31 to i64, !dbg !752
  %arrayidx35 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom34, !dbg !752
  %32 = load i8, i8* %arrayidx35, align 1, !dbg !752
  %call36 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %30, i8 signext %32), !dbg !753
  %33 = load i8*, i8** %p.addr, align 8, !dbg !754
  %arrayidx37 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !754
  %34 = load i8, i8* %arrayidx37, align 1, !dbg !754
  %conv38 = zext i8 %34 to i32, !dbg !754
  %and39 = and i32 %conv38, 3, !dbg !755
  %shl40 = shl i32 %and39, 4, !dbg !756
  store i32 %shl40, i32* %c, align 4, !dbg !757
  %35 = load i64, i64* %len.addr, align 8, !dbg !758
  %cmp41 = icmp eq i64 %35, 1, !dbg !760
  br i1 %cmp41, label %if.then43, label %if.else, !dbg !761

if.then43:                                        ; preds = %if.then
  %36 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !762
  %37 = load i32, i32* %c, align 4, !dbg !764
  %idxprom44 = sext i32 %37 to i64, !dbg !765
  %arrayidx45 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom44, !dbg !765
  %38 = load i8, i8* %arrayidx45, align 1, !dbg !765
  %call46 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %36, i8 signext %38), !dbg !766
  %39 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !767
  %call47 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %39, i8 signext 61), !dbg !768
  %40 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !769
  %call48 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %40, i8 signext 61), !dbg !770
  br label %if.end, !dbg !771

if.else:                                          ; preds = %if.then
  %41 = load i8*, i8** %p.addr, align 8, !dbg !772
  %arrayidx49 = getelementptr inbounds i8, i8* %41, i64 1, !dbg !772
  %42 = load i8, i8* %arrayidx49, align 1, !dbg !772
  %conv50 = zext i8 %42 to i32, !dbg !772
  %and51 = and i32 %conv50, 240, !dbg !774
  %shr52 = ashr i32 %and51, 4, !dbg !775
  %43 = load i32, i32* %c, align 4, !dbg !776
  %or53 = or i32 %43, %shr52, !dbg !776
  store i32 %or53, i32* %c, align 4, !dbg !776
  %44 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !777
  %45 = load i32, i32* %c, align 4, !dbg !778
  %idxprom54 = sext i32 %45 to i64, !dbg !779
  %arrayidx55 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom54, !dbg !779
  %46 = load i8, i8* %arrayidx55, align 1, !dbg !779
  %call56 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %44, i8 signext %46), !dbg !780
  %47 = load i8*, i8** %p.addr, align 8, !dbg !781
  %arrayidx57 = getelementptr inbounds i8, i8* %47, i64 1, !dbg !781
  %48 = load i8, i8* %arrayidx57, align 1, !dbg !781
  %conv58 = zext i8 %48 to i32, !dbg !781
  %and59 = and i32 %conv58, 15, !dbg !782
  %shl60 = shl i32 %and59, 2, !dbg !783
  store i32 %shl60, i32* %c, align 4, !dbg !784
  %49 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !785
  %50 = load i32, i32* %c, align 4, !dbg !786
  %idxprom61 = sext i32 %50 to i64, !dbg !787
  %arrayidx62 = getelementptr inbounds [64 x i8], [64 x i8]* @base64, i64 0, i64 %idxprom61, !dbg !787
  %51 = load i8, i8* %arrayidx62, align 1, !dbg !787
  %call63 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %49, i8 signext %51), !dbg !788
  %52 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !789
  %call64 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %52, i8 signext 61), !dbg !790
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then43
  br label %if.end65, !dbg !791

if.end65:                                         ; preds = %if.end, %for.end
  %53 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !792
  %call66 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %53, i8 signext 10), !dbg !793
  ret void, !dbg !794
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare i32 @__archive_write_filter(%struct.archive_write_filter*, i8*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #2

declare i32 @__archive_write_close_filter(%struct.archive_write_filter*) #2

declare void @archive_string_free(%struct.archive_string*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!222, !223}
!llvm.ident = !{!224}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !203, globals: !217)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_b64encode.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !191, !123, !23}
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
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_b64encode", file: !1, line: 47, size: 1088, align: 64, elements: !193)
!193 = !{!194, !195, !196, !197, !198, !199}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !192, file: !1, line: 48, baseType: !23, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !192, file: !1, line: 49, baseType: !91, size: 192, align: 64, offset: 64)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "encoded_buff", scope: !192, file: !1, line: 50, baseType: !91, size: 192, align: 64, offset: 256)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "bs", scope: !192, file: !1, line: 51, baseType: !45, size: 64, align: 64, offset: 448)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "hold_len", scope: !192, file: !1, line: 52, baseType: !45, size: 64, align: 64, offset: 512)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "hold", scope: !192, file: !1, line: 53, baseType: !200, size: 456, align: 8, offset: 576)
!200 = !DICompositeType(tag: DW_TAG_array_type, baseType: !116, size: 456, align: 8, elements: !201)
!201 = !{!202}
!202 = !DISubrange(count: 57)
!203 = !{!204, !205, !206, !209, !210, !211, !215, !216}
!204 = distinct !DISubprogram(name: "archive_write_add_filter_b64encode", scope: !1, file: !1, line: 81, type: !21, isLocal: false, isDefinition: true, scopeLine: 82, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!205 = distinct !DISubprogram(name: "archive_filter_b64encode_options", scope: !1, file: !1, line: 115, type: !145, isLocal: true, isDefinition: true, scopeLine: 117, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!206 = distinct !DISubprogram(name: "atol8", scope: !1, file: !1, line: 297, type: !207, isLocal: true, isDefinition: true, scopeLine: 298, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!207 = !DISubroutineType(types: !208)
!208 = !{!52, !80, !45}
!209 = distinct !DISubprogram(name: "archive_filter_b64encode_open", scope: !1, file: !1, line: 148, type: !149, isLocal: true, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!210 = distinct !DISubprogram(name: "archive_filter_b64encode_write", scope: !1, file: !1, line: 220, type: !153, isLocal: true, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!211 = distinct !DISubprogram(name: "b64_encode", scope: !1, file: !1, line: 183, type: !212, isLocal: true, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = !DISubroutineType(types: !213)
!213 = !{null, !214, !114, !45}
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!215 = distinct !DISubprogram(name: "archive_filter_b64encode_close", scope: !1, file: !1, line: 266, type: !149, isLocal: true, isDefinition: true, scopeLine: 267, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "archive_filter_b64encode_free", scope: !1, file: !1, line: 286, type: !149, isLocal: true, isDefinition: true, scopeLine: 287, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = !{!218}
!218 = !DIGlobalVariable(name: "base64", scope: !0, file: !1, line: 66, type: !219, isLocal: true, isDefinition: true, variable: [64 x i8]* @base64)
!219 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 512, align: 8, elements: !220)
!220 = !{!221}
!221 = !DISubrange(count: 64)
!222 = !{i32 2, !"Dwarf Version", i32 4}
!223 = !{i32 2, !"Debug Info Version", i32 3}
!224 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!225 = !DILocalVariable(name: "_a", arg: 1, scope: !204, file: !1, line: 81, type: !24)
!226 = !DIExpression()
!227 = !DILocation(line: 81, column: 52, scope: !204)
!228 = !DILocalVariable(name: "a", scope: !204, file: !1, line: 83, type: !4)
!229 = !DILocation(line: 83, column: 24, scope: !204)
!230 = !DILocation(line: 83, column: 52, scope: !204)
!231 = !DILocation(line: 83, column: 28, scope: !204)
!232 = !DILocalVariable(name: "f", scope: !204, file: !1, line: 84, type: !137)
!233 = !DILocation(line: 84, column: 31, scope: !204)
!234 = !DILocation(line: 84, column: 67, scope: !204)
!235 = !DILocation(line: 84, column: 35, scope: !204)
!236 = !DILocalVariable(name: "state", scope: !204, file: !1, line: 85, type: !191)
!237 = !DILocation(line: 85, column: 28, scope: !204)
!238 = !DILocation(line: 87, column: 2, scope: !204)
!239 = !DILocalVariable(name: "magic_test", scope: !240, file: !1, line: 87, type: !23)
!240 = distinct !DILexicalBlock(scope: !204, file: !1, line: 87, column: 2)
!241 = !DILocation(line: 87, column: 2, scope: !240)
!242 = !DILocation(line: 87, column: 2, scope: !243)
!243 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!244 = !DILocation(line: 87, column: 2, scope: !245)
!245 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 2)
!246 = distinct !DILexicalBlock(scope: !240, file: !1, line: 87, column: 2)
!247 = !DILocation(line: 87, column: 2, scope: !248)
!248 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 3)
!249 = !DILocation(line: 90, column: 38, scope: !204)
!250 = !DILocation(line: 90, column: 10, scope: !204)
!251 = !DILocation(line: 90, column: 8, scope: !204)
!252 = !DILocation(line: 91, column: 6, scope: !253)
!253 = distinct !DILexicalBlock(scope: !204, file: !1, line: 91, column: 6)
!254 = !DILocation(line: 91, column: 12, scope: !253)
!255 = !DILocation(line: 91, column: 6, scope: !204)
!256 = !DILocation(line: 92, column: 21, scope: !257)
!257 = distinct !DILexicalBlock(scope: !253, file: !1, line: 91, column: 21)
!258 = !DILocation(line: 92, column: 24, scope: !257)
!259 = !DILocation(line: 92, column: 3, scope: !257)
!260 = !DILocation(line: 94, column: 3, scope: !257)
!261 = !DILocation(line: 96, column: 2, scope: !204)
!262 = !DILocation(line: 97, column: 2, scope: !204)
!263 = !DILocation(line: 97, column: 9, scope: !204)
!264 = !DILocation(line: 97, column: 14, scope: !204)
!265 = !DILocation(line: 99, column: 12, scope: !204)
!266 = !DILocation(line: 99, column: 2, scope: !204)
!267 = !DILocation(line: 99, column: 5, scope: !204)
!268 = !DILocation(line: 99, column: 10, scope: !204)
!269 = !DILocation(line: 100, column: 2, scope: !204)
!270 = !DILocation(line: 100, column: 5, scope: !204)
!271 = !DILocation(line: 100, column: 10, scope: !204)
!272 = !DILocation(line: 101, column: 2, scope: !204)
!273 = !DILocation(line: 101, column: 5, scope: !204)
!274 = !DILocation(line: 101, column: 10, scope: !204)
!275 = !DILocation(line: 102, column: 2, scope: !204)
!276 = !DILocation(line: 102, column: 5, scope: !204)
!277 = !DILocation(line: 102, column: 10, scope: !204)
!278 = !DILocation(line: 103, column: 2, scope: !204)
!279 = !DILocation(line: 103, column: 5, scope: !204)
!280 = !DILocation(line: 103, column: 13, scope: !204)
!281 = !DILocation(line: 104, column: 2, scope: !204)
!282 = !DILocation(line: 104, column: 5, scope: !204)
!283 = !DILocation(line: 104, column: 11, scope: !204)
!284 = !DILocation(line: 105, column: 2, scope: !204)
!285 = !DILocation(line: 105, column: 5, scope: !204)
!286 = !DILocation(line: 105, column: 11, scope: !204)
!287 = !DILocation(line: 106, column: 2, scope: !204)
!288 = !DILocation(line: 106, column: 5, scope: !204)
!289 = !DILocation(line: 106, column: 10, scope: !204)
!290 = !DILocation(line: 108, column: 2, scope: !204)
!291 = !DILocation(line: 109, column: 1, scope: !204)
!292 = !DILocalVariable(name: "f", arg: 1, scope: !209, file: !1, line: 148, type: !137)
!293 = !DILocation(line: 148, column: 60, scope: !209)
!294 = !DILocalVariable(name: "state", scope: !209, file: !1, line: 150, type: !191)
!295 = !DILocation(line: 150, column: 28, scope: !209)
!296 = !DILocation(line: 150, column: 64, scope: !209)
!297 = !DILocation(line: 150, column: 67, scope: !209)
!298 = !DILocation(line: 150, column: 36, scope: !209)
!299 = !DILocalVariable(name: "bs", scope: !209, file: !1, line: 151, type: !45)
!300 = !DILocation(line: 151, column: 9, scope: !209)
!301 = !DILocalVariable(name: "bpb", scope: !209, file: !1, line: 151, type: !45)
!302 = !DILocation(line: 151, column: 21, scope: !209)
!303 = !DILocalVariable(name: "ret", scope: !209, file: !1, line: 152, type: !23)
!304 = !DILocation(line: 152, column: 6, scope: !209)
!305 = !DILocation(line: 154, column: 36, scope: !209)
!306 = !DILocation(line: 154, column: 39, scope: !209)
!307 = !DILocation(line: 154, column: 8, scope: !209)
!308 = !DILocation(line: 154, column: 6, scope: !209)
!309 = !DILocation(line: 155, column: 6, scope: !310)
!310 = distinct !DILexicalBlock(scope: !209, file: !1, line: 155, column: 6)
!311 = !DILocation(line: 155, column: 10, scope: !310)
!312 = !DILocation(line: 155, column: 6, scope: !209)
!313 = !DILocation(line: 156, column: 11, scope: !310)
!314 = !DILocation(line: 156, column: 3, scope: !310)
!315 = !DILocation(line: 158, column: 6, scope: !316)
!316 = distinct !DILexicalBlock(scope: !209, file: !1, line: 158, column: 6)
!317 = !DILocation(line: 158, column: 9, scope: !316)
!318 = !DILocation(line: 158, column: 18, scope: !316)
!319 = !DILocation(line: 158, column: 24, scope: !316)
!320 = !DILocation(line: 158, column: 6, scope: !209)
!321 = !DILocation(line: 161, column: 43, scope: !322)
!322 = distinct !DILexicalBlock(scope: !316, file: !1, line: 158, column: 48)
!323 = !DILocation(line: 161, column: 46, scope: !322)
!324 = !DILocation(line: 161, column: 9, scope: !322)
!325 = !DILocation(line: 161, column: 7, scope: !322)
!326 = !DILocation(line: 162, column: 7, scope: !327)
!327 = distinct !DILexicalBlock(scope: !322, file: !1, line: 162, column: 7)
!328 = !DILocation(line: 162, column: 13, scope: !327)
!329 = !DILocation(line: 162, column: 11, scope: !327)
!330 = !DILocation(line: 162, column: 7, scope: !322)
!331 = !DILocation(line: 163, column: 9, scope: !327)
!332 = !DILocation(line: 163, column: 7, scope: !327)
!333 = !DILocation(line: 163, column: 4, scope: !327)
!334 = !DILocation(line: 164, column: 12, scope: !335)
!335 = distinct !DILexicalBlock(scope: !327, file: !1, line: 164, column: 12)
!336 = !DILocation(line: 164, column: 16, scope: !335)
!337 = !DILocation(line: 164, column: 12, scope: !327)
!338 = !DILocation(line: 165, column: 10, scope: !335)
!339 = !DILocation(line: 165, column: 15, scope: !335)
!340 = !DILocation(line: 165, column: 13, scope: !335)
!341 = !DILocation(line: 165, column: 7, scope: !335)
!342 = !DILocation(line: 165, column: 4, scope: !335)
!343 = !DILocation(line: 166, column: 2, scope: !322)
!344 = !DILocation(line: 168, column: 14, scope: !209)
!345 = !DILocation(line: 168, column: 2, scope: !209)
!346 = !DILocation(line: 168, column: 9, scope: !209)
!347 = !DILocation(line: 168, column: 12, scope: !209)
!348 = !DILocation(line: 169, column: 29, scope: !349)
!349 = distinct !DILexicalBlock(scope: !209, file: !1, line: 169, column: 6)
!350 = !DILocation(line: 169, column: 36, scope: !349)
!351 = !DILocation(line: 169, column: 50, scope: !349)
!352 = !DILocation(line: 169, column: 53, scope: !349)
!353 = !DILocation(line: 169, column: 6, scope: !349)
!354 = !DILocation(line: 169, column: 60, scope: !349)
!355 = !DILocation(line: 169, column: 6, scope: !209)
!356 = !DILocation(line: 170, column: 21, scope: !357)
!357 = distinct !DILexicalBlock(scope: !349, file: !1, line: 169, column: 69)
!358 = !DILocation(line: 170, column: 24, scope: !357)
!359 = !DILocation(line: 170, column: 3, scope: !357)
!360 = !DILocation(line: 172, column: 3, scope: !357)
!361 = !DILocation(line: 175, column: 26, scope: !209)
!362 = !DILocation(line: 175, column: 33, scope: !209)
!363 = !DILocation(line: 176, column: 6, scope: !209)
!364 = !DILocation(line: 176, column: 13, scope: !209)
!365 = !DILocation(line: 176, column: 19, scope: !209)
!366 = !DILocation(line: 176, column: 26, scope: !209)
!367 = !DILocation(line: 176, column: 31, scope: !209)
!368 = !DILocation(line: 175, column: 2, scope: !209)
!369 = !DILocation(line: 178, column: 12, scope: !209)
!370 = !DILocation(line: 178, column: 2, scope: !209)
!371 = !DILocation(line: 178, column: 5, scope: !209)
!372 = !DILocation(line: 178, column: 10, scope: !209)
!373 = !DILocation(line: 179, column: 2, scope: !209)
!374 = !DILocation(line: 180, column: 1, scope: !209)
!375 = !DILocalVariable(name: "f", arg: 1, scope: !205, file: !1, line: 115, type: !137)
!376 = !DILocation(line: 115, column: 63, scope: !205)
!377 = !DILocalVariable(name: "key", arg: 2, scope: !205, file: !1, line: 115, type: !80)
!378 = !DILocation(line: 115, column: 78, scope: !205)
!379 = !DILocalVariable(name: "value", arg: 3, scope: !205, file: !1, line: 116, type: !80)
!380 = !DILocation(line: 116, column: 17, scope: !205)
!381 = !DILocalVariable(name: "state", scope: !205, file: !1, line: 118, type: !191)
!382 = !DILocation(line: 118, column: 28, scope: !205)
!383 = !DILocation(line: 118, column: 64, scope: !205)
!384 = !DILocation(line: 118, column: 67, scope: !205)
!385 = !DILocation(line: 118, column: 36, scope: !205)
!386 = !DILocation(line: 120, column: 13, scope: !387)
!387 = distinct !DILexicalBlock(scope: !205, file: !1, line: 120, column: 6)
!388 = !DILocation(line: 120, column: 6, scope: !387)
!389 = !DILocation(line: 120, column: 26, scope: !387)
!390 = !DILocation(line: 120, column: 6, scope: !205)
!391 = !DILocation(line: 121, column: 7, scope: !392)
!392 = distinct !DILexicalBlock(scope: !393, file: !1, line: 121, column: 7)
!393 = distinct !DILexicalBlock(scope: !387, file: !1, line: 120, column: 32)
!394 = !DILocation(line: 121, column: 13, scope: !392)
!395 = !DILocation(line: 121, column: 7, scope: !393)
!396 = !DILocation(line: 122, column: 22, scope: !397)
!397 = distinct !DILexicalBlock(scope: !392, file: !1, line: 121, column: 22)
!398 = !DILocation(line: 122, column: 25, scope: !397)
!399 = !DILocation(line: 122, column: 4, scope: !397)
!400 = !DILocation(line: 124, column: 4, scope: !397)
!401 = !DILocation(line: 126, column: 28, scope: !393)
!402 = !DILocation(line: 126, column: 42, scope: !393)
!403 = !DILocation(line: 126, column: 35, scope: !393)
!404 = !DILocation(line: 126, column: 22, scope: !405)
!405 = !DILexicalBlockFile(scope: !393, file: !1, discriminator: 1)
!406 = !DILocation(line: 126, column: 17, scope: !393)
!407 = !DILocation(line: 126, column: 50, scope: !393)
!408 = !DILocation(line: 126, column: 3, scope: !393)
!409 = !DILocation(line: 126, column: 10, scope: !393)
!410 = !DILocation(line: 126, column: 15, scope: !393)
!411 = !DILocation(line: 127, column: 3, scope: !393)
!412 = !DILocation(line: 128, column: 20, scope: !413)
!413 = distinct !DILexicalBlock(scope: !387, file: !1, line: 128, column: 13)
!414 = !DILocation(line: 128, column: 13, scope: !413)
!415 = !DILocation(line: 128, column: 33, scope: !413)
!416 = !DILocation(line: 128, column: 13, scope: !387)
!417 = !DILocation(line: 129, column: 7, scope: !418)
!418 = distinct !DILexicalBlock(scope: !419, file: !1, line: 129, column: 7)
!419 = distinct !DILexicalBlock(scope: !413, file: !1, line: 128, column: 39)
!420 = !DILocation(line: 129, column: 13, scope: !418)
!421 = !DILocation(line: 129, column: 7, scope: !419)
!422 = !DILocation(line: 130, column: 22, scope: !423)
!423 = distinct !DILexicalBlock(scope: !418, file: !1, line: 129, column: 22)
!424 = !DILocation(line: 130, column: 25, scope: !423)
!425 = !DILocation(line: 130, column: 4, scope: !423)
!426 = !DILocation(line: 132, column: 4, scope: !423)
!427 = !DILocation(line: 134, column: 3, scope: !419)
!428 = !DILocation(line: 134, column: 3, scope: !429)
!429 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 1)
!430 = !DILocation(line: 134, column: 3, scope: !431)
!431 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 2)
!432 = !DILocation(line: 134, column: 3, scope: !433)
!433 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 3)
!434 = !DILocation(line: 135, column: 3, scope: !419)
!435 = !DILocation(line: 141, column: 2, scope: !205)
!436 = !DILocation(line: 142, column: 1, scope: !205)
!437 = !DILocalVariable(name: "f", arg: 1, scope: !210, file: !1, line: 220, type: !137)
!438 = !DILocation(line: 220, column: 61, scope: !210)
!439 = !DILocalVariable(name: "buff", arg: 2, scope: !210, file: !1, line: 220, type: !43)
!440 = !DILocation(line: 220, column: 76, scope: !210)
!441 = !DILocalVariable(name: "length", arg: 3, scope: !210, file: !1, line: 221, type: !45)
!442 = !DILocation(line: 221, column: 12, scope: !210)
!443 = !DILocalVariable(name: "state", scope: !210, file: !1, line: 223, type: !191)
!444 = !DILocation(line: 223, column: 28, scope: !210)
!445 = !DILocation(line: 223, column: 64, scope: !210)
!446 = !DILocation(line: 223, column: 67, scope: !210)
!447 = !DILocation(line: 223, column: 36, scope: !210)
!448 = !DILocalVariable(name: "p", scope: !210, file: !1, line: 224, type: !114)
!449 = !DILocation(line: 224, column: 23, scope: !210)
!450 = !DILocation(line: 224, column: 27, scope: !210)
!451 = !DILocalVariable(name: "ret", scope: !210, file: !1, line: 225, type: !23)
!452 = !DILocation(line: 225, column: 6, scope: !210)
!453 = !DILocation(line: 227, column: 6, scope: !454)
!454 = distinct !DILexicalBlock(scope: !210, file: !1, line: 227, column: 6)
!455 = !DILocation(line: 227, column: 13, scope: !454)
!456 = !DILocation(line: 227, column: 6, scope: !210)
!457 = !DILocation(line: 228, column: 11, scope: !454)
!458 = !DILocation(line: 228, column: 3, scope: !454)
!459 = !DILocation(line: 230, column: 6, scope: !460)
!460 = distinct !DILexicalBlock(scope: !210, file: !1, line: 230, column: 6)
!461 = !DILocation(line: 230, column: 13, scope: !460)
!462 = !DILocation(line: 230, column: 6, scope: !210)
!463 = !DILocation(line: 231, column: 3, scope: !464)
!464 = distinct !DILexicalBlock(scope: !460, file: !1, line: 230, column: 23)
!465 = !DILocation(line: 231, column: 10, scope: !466)
!466 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 1)
!467 = !DILocation(line: 231, column: 17, scope: !466)
!468 = !DILocation(line: 231, column: 26, scope: !466)
!469 = !DILocation(line: 231, column: 35, scope: !466)
!470 = !DILocation(line: 231, column: 38, scope: !471)
!471 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 2)
!472 = !DILocation(line: 231, column: 45, scope: !471)
!473 = !DILocation(line: 231, column: 3, scope: !474)
!474 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 3)
!475 = !DILocation(line: 232, column: 39, scope: !476)
!476 = distinct !DILexicalBlock(scope: !464, file: !1, line: 231, column: 50)
!477 = !DILocation(line: 232, column: 37, scope: !476)
!478 = !DILocation(line: 232, column: 16, scope: !476)
!479 = !DILocation(line: 232, column: 23, scope: !476)
!480 = !DILocation(line: 232, column: 31, scope: !476)
!481 = !DILocation(line: 232, column: 4, scope: !476)
!482 = !DILocation(line: 232, column: 11, scope: !476)
!483 = !DILocation(line: 232, column: 35, scope: !476)
!484 = !DILocation(line: 233, column: 10, scope: !476)
!485 = !DILocation(line: 231, column: 3, scope: !486)
!486 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 4)
!487 = !DILocation(line: 235, column: 7, scope: !488)
!488 = distinct !DILexicalBlock(scope: !464, file: !1, line: 235, column: 7)
!489 = !DILocation(line: 235, column: 14, scope: !488)
!490 = !DILocation(line: 235, column: 23, scope: !488)
!491 = !DILocation(line: 235, column: 7, scope: !464)
!492 = !DILocation(line: 236, column: 12, scope: !488)
!493 = !DILocation(line: 236, column: 4, scope: !488)
!494 = !DILocation(line: 237, column: 15, scope: !464)
!495 = !DILocation(line: 237, column: 22, scope: !464)
!496 = !DILocation(line: 237, column: 36, scope: !464)
!497 = !DILocation(line: 237, column: 43, scope: !464)
!498 = !DILocation(line: 237, column: 3, scope: !464)
!499 = !DILocation(line: 238, column: 3, scope: !464)
!500 = !DILocation(line: 238, column: 10, scope: !464)
!501 = !DILocation(line: 238, column: 19, scope: !464)
!502 = !DILocation(line: 239, column: 2, scope: !464)
!503 = !DILocation(line: 241, column: 2, scope: !210)
!504 = !DILocation(line: 241, column: 9, scope: !505)
!505 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!506 = distinct !DILexicalBlock(scope: !507, file: !1, line: 241, column: 2)
!507 = distinct !DILexicalBlock(scope: !210, file: !1, line: 241, column: 2)
!508 = !DILocation(line: 241, column: 16, scope: !505)
!509 = !DILocation(line: 241, column: 2, scope: !505)
!510 = !DILocation(line: 242, column: 15, scope: !506)
!511 = !DILocation(line: 242, column: 22, scope: !506)
!512 = !DILocation(line: 242, column: 36, scope: !506)
!513 = !DILocation(line: 242, column: 3, scope: !506)
!514 = !DILocation(line: 241, column: 34, scope: !515)
!515 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 2)
!516 = !DILocation(line: 241, column: 47, scope: !515)
!517 = !DILocation(line: 241, column: 2, scope: !515)
!518 = !DILocation(line: 245, column: 6, scope: !519)
!519 = distinct !DILexicalBlock(scope: !210, file: !1, line: 245, column: 6)
!520 = !DILocation(line: 245, column: 13, scope: !519)
!521 = !DILocation(line: 245, column: 6, scope: !210)
!522 = !DILocation(line: 246, column: 10, scope: !523)
!523 = distinct !DILexicalBlock(scope: !519, file: !1, line: 245, column: 18)
!524 = !DILocation(line: 246, column: 17, scope: !523)
!525 = !DILocation(line: 246, column: 3, scope: !523)
!526 = !DILocation(line: 246, column: 23, scope: !523)
!527 = !DILocation(line: 246, column: 26, scope: !523)
!528 = !DILocation(line: 247, column: 21, scope: !523)
!529 = !DILocation(line: 247, column: 3, scope: !523)
!530 = !DILocation(line: 247, column: 10, scope: !523)
!531 = !DILocation(line: 247, column: 19, scope: !523)
!532 = !DILocation(line: 248, column: 2, scope: !523)
!533 = !DILocation(line: 249, column: 2, scope: !210)
!534 = !DILocation(line: 249, column: 9, scope: !535)
!535 = !DILexicalBlockFile(scope: !210, file: !1, discriminator: 1)
!536 = !DILocation(line: 249, column: 49, scope: !535)
!537 = !DILocation(line: 249, column: 56, scope: !535)
!538 = !DILocation(line: 249, column: 46, scope: !535)
!539 = !DILocation(line: 249, column: 2, scope: !535)
!540 = !DILocation(line: 250, column: 32, scope: !541)
!541 = distinct !DILexicalBlock(scope: !210, file: !1, line: 249, column: 60)
!542 = !DILocation(line: 250, column: 35, scope: !541)
!543 = !DILocation(line: 251, column: 7, scope: !541)
!544 = !DILocation(line: 251, column: 14, scope: !541)
!545 = !DILocation(line: 251, column: 27, scope: !541)
!546 = !DILocation(line: 251, column: 30, scope: !541)
!547 = !DILocation(line: 251, column: 37, scope: !541)
!548 = !DILocation(line: 250, column: 9, scope: !541)
!549 = !DILocation(line: 250, column: 7, scope: !541)
!550 = !DILocation(line: 252, column: 11, scope: !541)
!551 = !DILocation(line: 252, column: 18, scope: !541)
!552 = !DILocation(line: 252, column: 31, scope: !541)
!553 = !DILocation(line: 253, column: 7, scope: !541)
!554 = !DILocation(line: 253, column: 14, scope: !541)
!555 = !DILocation(line: 253, column: 27, scope: !541)
!556 = !DILocation(line: 253, column: 31, scope: !541)
!557 = !DILocation(line: 253, column: 38, scope: !541)
!558 = !DILocation(line: 253, column: 29, scope: !541)
!559 = !DILocation(line: 254, column: 7, scope: !541)
!560 = !DILocation(line: 254, column: 14, scope: !541)
!561 = !DILocation(line: 254, column: 27, scope: !541)
!562 = !DILocation(line: 254, column: 36, scope: !541)
!563 = !DILocation(line: 254, column: 43, scope: !541)
!564 = !DILocation(line: 254, column: 34, scope: !541)
!565 = !DILocation(line: 252, column: 3, scope: !541)
!566 = !DILocation(line: 255, column: 33, scope: !541)
!567 = !DILocation(line: 255, column: 40, scope: !541)
!568 = !DILocation(line: 255, column: 3, scope: !541)
!569 = !DILocation(line: 255, column: 10, scope: !541)
!570 = !DILocation(line: 255, column: 23, scope: !541)
!571 = !DILocation(line: 255, column: 30, scope: !541)
!572 = !DILocation(line: 249, column: 2, scope: !573)
!573 = !DILexicalBlockFile(scope: !210, file: !1, discriminator: 2)
!574 = !DILocation(line: 258, column: 10, scope: !210)
!575 = !DILocation(line: 258, column: 2, scope: !210)
!576 = !DILocation(line: 259, column: 1, scope: !210)
!577 = !DILocalVariable(name: "f", arg: 1, scope: !215, file: !1, line: 266, type: !137)
!578 = !DILocation(line: 266, column: 61, scope: !215)
!579 = !DILocalVariable(name: "state", scope: !215, file: !1, line: 268, type: !191)
!580 = !DILocation(line: 268, column: 28, scope: !215)
!581 = !DILocation(line: 268, column: 64, scope: !215)
!582 = !DILocation(line: 268, column: 67, scope: !215)
!583 = !DILocation(line: 268, column: 36, scope: !215)
!584 = !DILocalVariable(name: "ret", scope: !215, file: !1, line: 269, type: !23)
!585 = !DILocation(line: 269, column: 6, scope: !215)
!586 = !DILocalVariable(name: "ret2", scope: !215, file: !1, line: 269, type: !23)
!587 = !DILocation(line: 269, column: 11, scope: !215)
!588 = !DILocation(line: 272, column: 6, scope: !589)
!589 = distinct !DILexicalBlock(scope: !215, file: !1, line: 272, column: 6)
!590 = !DILocation(line: 272, column: 13, scope: !589)
!591 = !DILocation(line: 272, column: 22, scope: !589)
!592 = !DILocation(line: 272, column: 6, scope: !215)
!593 = !DILocation(line: 273, column: 15, scope: !589)
!594 = !DILocation(line: 273, column: 22, scope: !589)
!595 = !DILocation(line: 273, column: 36, scope: !589)
!596 = !DILocation(line: 273, column: 43, scope: !589)
!597 = !DILocation(line: 273, column: 49, scope: !589)
!598 = !DILocation(line: 273, column: 56, scope: !589)
!599 = !DILocation(line: 273, column: 3, scope: !589)
!600 = !DILocation(line: 274, column: 26, scope: !215)
!601 = !DILocation(line: 274, column: 33, scope: !215)
!602 = !DILocation(line: 274, column: 2, scope: !215)
!603 = !DILocation(line: 276, column: 40, scope: !215)
!604 = !DILocation(line: 276, column: 43, scope: !215)
!605 = !DILocation(line: 276, column: 2, scope: !215)
!606 = !DILocation(line: 277, column: 31, scope: !215)
!607 = !DILocation(line: 277, column: 34, scope: !215)
!608 = !DILocation(line: 278, column: 6, scope: !215)
!609 = !DILocation(line: 278, column: 13, scope: !215)
!610 = !DILocation(line: 278, column: 26, scope: !215)
!611 = !DILocation(line: 278, column: 29, scope: !215)
!612 = !DILocation(line: 277, column: 8, scope: !215)
!613 = !DILocation(line: 277, column: 6, scope: !215)
!614 = !DILocation(line: 279, column: 38, scope: !215)
!615 = !DILocation(line: 279, column: 41, scope: !215)
!616 = !DILocation(line: 279, column: 9, scope: !215)
!617 = !DILocation(line: 279, column: 7, scope: !215)
!618 = !DILocation(line: 280, column: 6, scope: !619)
!619 = distinct !DILexicalBlock(scope: !215, file: !1, line: 280, column: 6)
!620 = !DILocation(line: 280, column: 12, scope: !619)
!621 = !DILocation(line: 280, column: 10, scope: !619)
!622 = !DILocation(line: 280, column: 6, scope: !215)
!623 = !DILocation(line: 281, column: 9, scope: !619)
!624 = !DILocation(line: 281, column: 7, scope: !619)
!625 = !DILocation(line: 281, column: 3, scope: !619)
!626 = !DILocation(line: 282, column: 10, scope: !215)
!627 = !DILocation(line: 282, column: 2, scope: !215)
!628 = !DILocalVariable(name: "f", arg: 1, scope: !216, file: !1, line: 286, type: !137)
!629 = !DILocation(line: 286, column: 60, scope: !216)
!630 = !DILocalVariable(name: "state", scope: !216, file: !1, line: 288, type: !191)
!631 = !DILocation(line: 288, column: 28, scope: !216)
!632 = !DILocation(line: 288, column: 64, scope: !216)
!633 = !DILocation(line: 288, column: 67, scope: !216)
!634 = !DILocation(line: 288, column: 36, scope: !216)
!635 = !DILocation(line: 290, column: 23, scope: !216)
!636 = !DILocation(line: 290, column: 30, scope: !216)
!637 = !DILocation(line: 290, column: 2, scope: !216)
!638 = !DILocation(line: 291, column: 23, scope: !216)
!639 = !DILocation(line: 291, column: 30, scope: !216)
!640 = !DILocation(line: 291, column: 2, scope: !216)
!641 = !DILocation(line: 292, column: 7, scope: !216)
!642 = !DILocation(line: 292, column: 2, scope: !216)
!643 = !DILocation(line: 293, column: 2, scope: !216)
!644 = !DILocalVariable(name: "p", arg: 1, scope: !206, file: !1, line: 297, type: !80)
!645 = !DILocation(line: 297, column: 19, scope: !206)
!646 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !206, file: !1, line: 297, type: !45)
!647 = !DILocation(line: 297, column: 29, scope: !206)
!648 = !DILocalVariable(name: "l", scope: !206, file: !1, line: 299, type: !52)
!649 = !DILocation(line: 299, column: 10, scope: !206)
!650 = !DILocalVariable(name: "digit", scope: !206, file: !1, line: 300, type: !23)
!651 = !DILocation(line: 300, column: 6, scope: !206)
!652 = !DILocation(line: 302, column: 4, scope: !206)
!653 = !DILocation(line: 303, column: 2, scope: !206)
!654 = !DILocation(line: 303, column: 17, scope: !655)
!655 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!656 = !DILocation(line: 303, column: 20, scope: !655)
!657 = !DILocation(line: 303, column: 2, scope: !655)
!658 = !DILocation(line: 304, column: 8, scope: !659)
!659 = distinct !DILexicalBlock(scope: !660, file: !1, line: 304, column: 7)
!660 = distinct !DILexicalBlock(scope: !206, file: !1, line: 303, column: 25)
!661 = !DILocation(line: 304, column: 7, scope: !659)
!662 = !DILocation(line: 304, column: 10, scope: !659)
!663 = !DILocation(line: 304, column: 17, scope: !659)
!664 = !DILocation(line: 304, column: 21, scope: !665)
!665 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!666 = !DILocation(line: 304, column: 20, scope: !665)
!667 = !DILocation(line: 304, column: 23, scope: !665)
!668 = !DILocation(line: 304, column: 7, scope: !665)
!669 = !DILocation(line: 305, column: 13, scope: !659)
!670 = !DILocation(line: 305, column: 12, scope: !659)
!671 = !DILocation(line: 305, column: 15, scope: !659)
!672 = !DILocation(line: 305, column: 10, scope: !659)
!673 = !DILocation(line: 305, column: 4, scope: !659)
!674 = !DILocation(line: 307, column: 4, scope: !659)
!675 = !DILocation(line: 308, column: 4, scope: !660)
!676 = !DILocation(line: 309, column: 5, scope: !660)
!677 = !DILocation(line: 310, column: 8, scope: !660)
!678 = !DILocation(line: 310, column: 5, scope: !660)
!679 = !DILocation(line: 303, column: 2, scope: !680)
!680 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 2)
!681 = !DILocation(line: 312, column: 10, scope: !206)
!682 = !DILocation(line: 312, column: 2, scope: !206)
!683 = !DILocalVariable(name: "as", arg: 1, scope: !211, file: !1, line: 183, type: !214)
!684 = !DILocation(line: 183, column: 35, scope: !211)
!685 = !DILocalVariable(name: "p", arg: 2, scope: !211, file: !1, line: 183, type: !114)
!686 = !DILocation(line: 183, column: 60, scope: !211)
!687 = !DILocalVariable(name: "len", arg: 3, scope: !211, file: !1, line: 183, type: !45)
!688 = !DILocation(line: 183, column: 70, scope: !211)
!689 = !DILocalVariable(name: "c", scope: !211, file: !1, line: 185, type: !23)
!690 = !DILocation(line: 185, column: 6, scope: !211)
!691 = !DILocation(line: 187, column: 2, scope: !211)
!692 = !DILocation(line: 187, column: 9, scope: !693)
!693 = !DILexicalBlockFile(scope: !694, file: !1, discriminator: 1)
!694 = distinct !DILexicalBlock(scope: !695, file: !1, line: 187, column: 2)
!695 = distinct !DILexicalBlock(scope: !211, file: !1, line: 187, column: 2)
!696 = !DILocation(line: 187, column: 13, scope: !693)
!697 = !DILocation(line: 187, column: 2, scope: !693)
!698 = !DILocation(line: 188, column: 7, scope: !699)
!699 = distinct !DILexicalBlock(scope: !694, file: !1, line: 187, column: 37)
!700 = !DILocation(line: 188, column: 12, scope: !699)
!701 = !DILocation(line: 188, column: 5, scope: !699)
!702 = !DILocation(line: 189, column: 26, scope: !699)
!703 = !DILocation(line: 189, column: 37, scope: !699)
!704 = !DILocation(line: 189, column: 30, scope: !699)
!705 = !DILocation(line: 189, column: 3, scope: !699)
!706 = !DILocation(line: 190, column: 9, scope: !699)
!707 = !DILocation(line: 190, column: 14, scope: !699)
!708 = !DILocation(line: 190, column: 22, scope: !699)
!709 = !DILocation(line: 190, column: 32, scope: !699)
!710 = !DILocation(line: 190, column: 37, scope: !699)
!711 = !DILocation(line: 190, column: 45, scope: !699)
!712 = !DILocation(line: 190, column: 28, scope: !699)
!713 = !DILocation(line: 190, column: 5, scope: !699)
!714 = !DILocation(line: 191, column: 26, scope: !699)
!715 = !DILocation(line: 191, column: 37, scope: !699)
!716 = !DILocation(line: 191, column: 30, scope: !699)
!717 = !DILocation(line: 191, column: 3, scope: !699)
!718 = !DILocation(line: 192, column: 9, scope: !699)
!719 = !DILocation(line: 192, column: 14, scope: !699)
!720 = !DILocation(line: 192, column: 22, scope: !699)
!721 = !DILocation(line: 192, column: 32, scope: !699)
!722 = !DILocation(line: 192, column: 37, scope: !699)
!723 = !DILocation(line: 192, column: 45, scope: !699)
!724 = !DILocation(line: 192, column: 28, scope: !699)
!725 = !DILocation(line: 192, column: 5, scope: !699)
!726 = !DILocation(line: 193, column: 26, scope: !699)
!727 = !DILocation(line: 193, column: 37, scope: !699)
!728 = !DILocation(line: 193, column: 30, scope: !699)
!729 = !DILocation(line: 193, column: 3, scope: !699)
!730 = !DILocation(line: 194, column: 7, scope: !699)
!731 = !DILocation(line: 194, column: 12, scope: !699)
!732 = !DILocation(line: 194, column: 5, scope: !699)
!733 = !DILocation(line: 195, column: 26, scope: !699)
!734 = !DILocation(line: 195, column: 37, scope: !699)
!735 = !DILocation(line: 195, column: 30, scope: !699)
!736 = !DILocation(line: 195, column: 3, scope: !699)
!737 = !DILocation(line: 196, column: 2, scope: !699)
!738 = !DILocation(line: 187, column: 21, scope: !739)
!739 = !DILexicalBlockFile(scope: !694, file: !1, discriminator: 2)
!740 = !DILocation(line: 187, column: 31, scope: !739)
!741 = !DILocation(line: 187, column: 2, scope: !739)
!742 = !DILocation(line: 197, column: 6, scope: !743)
!743 = distinct !DILexicalBlock(scope: !211, file: !1, line: 197, column: 6)
!744 = !DILocation(line: 197, column: 10, scope: !743)
!745 = !DILocation(line: 197, column: 6, scope: !211)
!746 = !DILocation(line: 198, column: 7, scope: !747)
!747 = distinct !DILexicalBlock(scope: !743, file: !1, line: 197, column: 15)
!748 = !DILocation(line: 198, column: 12, scope: !747)
!749 = !DILocation(line: 198, column: 5, scope: !747)
!750 = !DILocation(line: 199, column: 26, scope: !747)
!751 = !DILocation(line: 199, column: 37, scope: !747)
!752 = !DILocation(line: 199, column: 30, scope: !747)
!753 = !DILocation(line: 199, column: 3, scope: !747)
!754 = !DILocation(line: 200, column: 8, scope: !747)
!755 = !DILocation(line: 200, column: 13, scope: !747)
!756 = !DILocation(line: 200, column: 21, scope: !747)
!757 = !DILocation(line: 200, column: 5, scope: !747)
!758 = !DILocation(line: 201, column: 7, scope: !759)
!759 = distinct !DILexicalBlock(scope: !747, file: !1, line: 201, column: 7)
!760 = !DILocation(line: 201, column: 11, scope: !759)
!761 = !DILocation(line: 201, column: 7, scope: !747)
!762 = !DILocation(line: 202, column: 27, scope: !763)
!763 = distinct !DILexicalBlock(scope: !759, file: !1, line: 201, column: 17)
!764 = !DILocation(line: 202, column: 38, scope: !763)
!765 = !DILocation(line: 202, column: 31, scope: !763)
!766 = !DILocation(line: 202, column: 4, scope: !763)
!767 = !DILocation(line: 203, column: 27, scope: !763)
!768 = !DILocation(line: 203, column: 4, scope: !763)
!769 = !DILocation(line: 204, column: 27, scope: !763)
!770 = !DILocation(line: 204, column: 4, scope: !763)
!771 = !DILocation(line: 205, column: 3, scope: !763)
!772 = !DILocation(line: 206, column: 10, scope: !773)
!773 = distinct !DILexicalBlock(scope: !759, file: !1, line: 205, column: 10)
!774 = !DILocation(line: 206, column: 15, scope: !773)
!775 = !DILocation(line: 206, column: 23, scope: !773)
!776 = !DILocation(line: 206, column: 6, scope: !773)
!777 = !DILocation(line: 207, column: 27, scope: !773)
!778 = !DILocation(line: 207, column: 38, scope: !773)
!779 = !DILocation(line: 207, column: 31, scope: !773)
!780 = !DILocation(line: 207, column: 4, scope: !773)
!781 = !DILocation(line: 208, column: 9, scope: !773)
!782 = !DILocation(line: 208, column: 14, scope: !773)
!783 = !DILocation(line: 208, column: 22, scope: !773)
!784 = !DILocation(line: 208, column: 6, scope: !773)
!785 = !DILocation(line: 209, column: 27, scope: !773)
!786 = !DILocation(line: 209, column: 38, scope: !773)
!787 = !DILocation(line: 209, column: 31, scope: !773)
!788 = !DILocation(line: 209, column: 4, scope: !773)
!789 = !DILocation(line: 210, column: 27, scope: !773)
!790 = !DILocation(line: 210, column: 4, scope: !773)
!791 = !DILocation(line: 212, column: 2, scope: !747)
!792 = !DILocation(line: 213, column: 25, scope: !211)
!793 = !DILocation(line: 213, column: 2, scope: !211)
!794 = !DILocation(line: 214, column: 1, scope: !211)
