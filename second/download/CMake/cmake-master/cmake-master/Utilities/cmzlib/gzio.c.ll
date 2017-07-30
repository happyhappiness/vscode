; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/gzio.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.gz_stream = type { %struct.z_stream_s, i32, i32, %struct._IO_FILE*, i8*, i8*, i64, i8*, i8*, i32, i8, i64, i64, i64, i32, i32 }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [8 x i8] c"<fd:%d>\00", align 1
@cm_zlib_z_errmsg = external constant [10 x i8*], align 16
@.str.1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.2 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1
@.str.4 = private unnamed_addr constant [21 x i8] c"%c%c%c%c%c%c%c%c%c%c\00", align 1
@gz_magic = internal constant [2 x i32] [i32 31, i32 139], align 4

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_gzopen(i8* %path, i8* %mode) #0 !dbg !134 {
entry:
  %path.addr = alloca i8*, align 8
  %mode.addr = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !214, metadata !215), !dbg !216
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !217, metadata !215), !dbg !218
  %0 = load i8*, i8** %path.addr, align 8, !dbg !219
  %1 = load i8*, i8** %mode.addr, align 8, !dbg !220
  %call = call i8* @gz_open(i8* %0, i8* %1, i32 -1), !dbg !221
  ret i8* %call, !dbg !222
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i8* @gz_open(i8* %path, i8* %mode, i32 %fd) #0 !dbg !188 {
entry:
  %retval = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %mode.addr = alloca i8*, align 8
  %fd.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %level = alloca i32, align 4
  %strategy = alloca i32, align 4
  %p = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  %fmode = alloca [80 x i8], align 16
  %m = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !223, metadata !215), !dbg !224
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !225, metadata !215), !dbg !226
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !227, metadata !215), !dbg !228
  call void @llvm.dbg.declare(metadata i32* %err, metadata !229, metadata !215), !dbg !230
  call void @llvm.dbg.declare(metadata i32* %level, metadata !231, metadata !215), !dbg !232
  store i32 -1, i32* %level, align 4, !dbg !232
  call void @llvm.dbg.declare(metadata i32* %strategy, metadata !233, metadata !215), !dbg !234
  store i32 0, i32* %strategy, align 4, !dbg !234
  call void @llvm.dbg.declare(metadata i8** %p, metadata !235, metadata !215), !dbg !236
  %0 = load i8*, i8** %mode.addr, align 8, !dbg !237
  store i8* %0, i8** %p, align 8, !dbg !236
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !238, metadata !215), !dbg !239
  call void @llvm.dbg.declare(metadata [80 x i8]* %fmode, metadata !240, metadata !215), !dbg !244
  call void @llvm.dbg.declare(metadata i8** %m, metadata !245, metadata !215), !dbg !246
  %arraydecay = getelementptr inbounds [80 x i8], [80 x i8]* %fmode, i32 0, i32 0, !dbg !247
  store i8* %arraydecay, i8** %m, align 8, !dbg !246
  %1 = load i8*, i8** %path.addr, align 8, !dbg !248
  %tobool = icmp ne i8* %1, null, !dbg !248
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !250

lor.lhs.false:                                    ; preds = %entry
  %2 = load i8*, i8** %mode.addr, align 8, !dbg !251
  %tobool1 = icmp ne i8* %2, null, !dbg !251
  br i1 %tobool1, label %if.end, label %if.then, !dbg !253

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i8* null, i8** %retval, align 8, !dbg !254
  br label %return, !dbg !254

if.end:                                           ; preds = %lor.lhs.false
  %call = call noalias i8* @malloc(i64 208) #6, !dbg !256
  %3 = bitcast i8* %call to %struct.gz_stream*, !dbg !257
  store %struct.gz_stream* %3, %struct.gz_stream** %s, align 8, !dbg !258
  %4 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !259
  %tobool2 = icmp ne %struct.gz_stream* %4, null, !dbg !259
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !261

if.then3:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !262
  br label %return, !dbg !262

if.end4:                                          ; preds = %if.end
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !264
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 0, !dbg !265
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 8, !dbg !266
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !267
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !268
  %stream5 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 0, !dbg !269
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream5, i32 0, i32 9, !dbg !270
  store void (i8*, i8*)* null, void (i8*, i8*)** %zfree, align 8, !dbg !271
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !272
  %stream6 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 0, !dbg !273
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream6, i32 0, i32 10, !dbg !274
  store i8* null, i8** %opaque, align 8, !dbg !275
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !276
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 4, !dbg !277
  store i8* null, i8** %inbuf, align 8, !dbg !278
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !279
  %stream7 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 0, !dbg !280
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream7, i32 0, i32 0, !dbg !281
  store i8* null, i8** %next_in, align 8, !dbg !282
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !283
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 5, !dbg !284
  store i8* null, i8** %outbuf, align 8, !dbg !285
  %11 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !286
  %stream8 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %11, i32 0, i32 0, !dbg !287
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream8, i32 0, i32 3, !dbg !288
  store i8* null, i8** %next_out, align 8, !dbg !289
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !290
  %stream9 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 0, !dbg !291
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream9, i32 0, i32 4, !dbg !292
  store i32 0, i32* %avail_out, align 8, !dbg !293
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !294
  %stream10 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 0, !dbg !295
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream10, i32 0, i32 1, !dbg !296
  store i32 0, i32* %avail_in, align 8, !dbg !297
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !298
  %file = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 3, !dbg !299
  store %struct._IO_FILE* null, %struct._IO_FILE** %file, align 8, !dbg !300
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !301
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 1, !dbg !302
  store i32 0, i32* %z_err, align 8, !dbg !303
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !304
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 2, !dbg !305
  store i32 0, i32* %z_eof, align 4, !dbg !306
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !307
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 12, !dbg !308
  store i64 0, i64* %in, align 8, !dbg !309
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !310
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 13, !dbg !311
  store i64 0, i64* %out, align 8, !dbg !312
  %19 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !313
  %back = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %19, i32 0, i32 14, !dbg !314
  store i32 -1, i32* %back, align 8, !dbg !315
  %call11 = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !316
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !317
  %crc = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 6, !dbg !318
  store i64 %call11, i64* %crc, align 8, !dbg !319
  %21 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !320
  %msg = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %21, i32 0, i32 7, !dbg !321
  store i8* null, i8** %msg, align 8, !dbg !322
  %22 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !323
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %22, i32 0, i32 9, !dbg !324
  store i32 0, i32* %transparent, align 8, !dbg !325
  %23 = load i8*, i8** %path.addr, align 8, !dbg !326
  %call12 = call i64 @strlen(i8* %23) #8, !dbg !326
  %add = add i64 %call12, 1, !dbg !326
  %call13 = call noalias i8* @malloc(i64 %add) #6, !dbg !327
  %24 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !329
  %path14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %24, i32 0, i32 8, !dbg !330
  store i8* %call13, i8** %path14, align 8, !dbg !331
  %25 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !332
  %path15 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %25, i32 0, i32 8, !dbg !334
  %26 = load i8*, i8** %path15, align 8, !dbg !334
  %cmp = icmp eq i8* %26, null, !dbg !335
  br i1 %cmp, label %if.then16, label %if.end18, !dbg !336

if.then16:                                        ; preds = %if.end4
  %27 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !337
  %call17 = call i32 @destroy(%struct.gz_stream* %27), !dbg !339
  store i8* null, i8** %retval, align 8, !dbg !340
  br label %return, !dbg !340

if.end18:                                         ; preds = %if.end4
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !341
  %path19 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 8, !dbg !342
  %29 = load i8*, i8** %path19, align 8, !dbg !342
  %30 = load i8*, i8** %path.addr, align 8, !dbg !343
  %call20 = call i8* @strcpy(i8* %29, i8* %30) #6, !dbg !344
  %31 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !345
  %mode21 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %31, i32 0, i32 10, !dbg !346
  store i8 0, i8* %mode21, align 4, !dbg !347
  br label %do.body, !dbg !348

do.body:                                          ; preds = %land.end, %if.end18
  %32 = load i8*, i8** %p, align 8, !dbg !349
  %33 = load i8, i8* %32, align 1, !dbg !352
  %conv = sext i8 %33 to i32, !dbg !352
  %cmp22 = icmp eq i32 %conv, 114, !dbg !353
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !354

if.then24:                                        ; preds = %do.body
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !355
  %mode25 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %34, i32 0, i32 10, !dbg !357
  store i8 114, i8* %mode25, align 4, !dbg !358
  br label %if.end26, !dbg !355

if.end26:                                         ; preds = %if.then24, %do.body
  %35 = load i8*, i8** %p, align 8, !dbg !359
  %36 = load i8, i8* %35, align 1, !dbg !361
  %conv27 = sext i8 %36 to i32, !dbg !361
  %cmp28 = icmp eq i32 %conv27, 119, !dbg !362
  br i1 %cmp28, label %if.then34, label %lor.lhs.false30, !dbg !363

lor.lhs.false30:                                  ; preds = %if.end26
  %37 = load i8*, i8** %p, align 8, !dbg !364
  %38 = load i8, i8* %37, align 1, !dbg !366
  %conv31 = sext i8 %38 to i32, !dbg !366
  %cmp32 = icmp eq i32 %conv31, 97, !dbg !367
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !368

if.then34:                                        ; preds = %lor.lhs.false30, %if.end26
  %39 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !369
  %mode35 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %39, i32 0, i32 10, !dbg !371
  store i8 119, i8* %mode35, align 4, !dbg !372
  br label %if.end36, !dbg !369

if.end36:                                         ; preds = %if.then34, %lor.lhs.false30
  %40 = load i8*, i8** %p, align 8, !dbg !373
  %41 = load i8, i8* %40, align 1, !dbg !375
  %conv37 = sext i8 %41 to i32, !dbg !375
  %cmp38 = icmp sge i32 %conv37, 48, !dbg !376
  br i1 %cmp38, label %land.lhs.true, label %if.else, !dbg !377

land.lhs.true:                                    ; preds = %if.end36
  %42 = load i8*, i8** %p, align 8, !dbg !378
  %43 = load i8, i8* %42, align 1, !dbg !380
  %conv40 = sext i8 %43 to i32, !dbg !380
  %cmp41 = icmp sle i32 %conv40, 57, !dbg !381
  br i1 %cmp41, label %if.then43, label %if.else, !dbg !382

if.then43:                                        ; preds = %land.lhs.true
  %44 = load i8*, i8** %p, align 8, !dbg !383
  %45 = load i8, i8* %44, align 1, !dbg !385
  %conv44 = sext i8 %45 to i32, !dbg !385
  %sub = sub nsw i32 %conv44, 48, !dbg !386
  store i32 %sub, i32* %level, align 4, !dbg !387
  br label %if.end63, !dbg !388

if.else:                                          ; preds = %land.lhs.true, %if.end36
  %46 = load i8*, i8** %p, align 8, !dbg !389
  %47 = load i8, i8* %46, align 1, !dbg !392
  %conv45 = sext i8 %47 to i32, !dbg !392
  %cmp46 = icmp eq i32 %conv45, 102, !dbg !393
  br i1 %cmp46, label %if.then48, label %if.else49, !dbg !392

if.then48:                                        ; preds = %if.else
  store i32 1, i32* %strategy, align 4, !dbg !394
  br label %if.end62, !dbg !396

if.else49:                                        ; preds = %if.else
  %48 = load i8*, i8** %p, align 8, !dbg !397
  %49 = load i8, i8* %48, align 1, !dbg !400
  %conv50 = sext i8 %49 to i32, !dbg !400
  %cmp51 = icmp eq i32 %conv50, 104, !dbg !401
  br i1 %cmp51, label %if.then53, label %if.else54, !dbg !400

if.then53:                                        ; preds = %if.else49
  store i32 2, i32* %strategy, align 4, !dbg !402
  br label %if.end61, !dbg !404

if.else54:                                        ; preds = %if.else49
  %50 = load i8*, i8** %p, align 8, !dbg !405
  %51 = load i8, i8* %50, align 1, !dbg !408
  %conv55 = sext i8 %51 to i32, !dbg !408
  %cmp56 = icmp eq i32 %conv55, 82, !dbg !409
  br i1 %cmp56, label %if.then58, label %if.else59, !dbg !408

if.then58:                                        ; preds = %if.else54
  store i32 3, i32* %strategy, align 4, !dbg !410
  br label %if.end60, !dbg !412

if.else59:                                        ; preds = %if.else54
  %52 = load i8*, i8** %p, align 8, !dbg !413
  %53 = load i8, i8* %52, align 1, !dbg !415
  %54 = load i8*, i8** %m, align 8, !dbg !416
  %incdec.ptr = getelementptr inbounds i8, i8* %54, i32 1, !dbg !416
  store i8* %incdec.ptr, i8** %m, align 8, !dbg !416
  store i8 %53, i8* %54, align 1, !dbg !417
  br label %if.end60

if.end60:                                         ; preds = %if.else59, %if.then58
  br label %if.end61

if.end61:                                         ; preds = %if.end60, %if.then53
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.then48
  br label %if.end63

if.end63:                                         ; preds = %if.end62, %if.then43
  br label %do.cond, !dbg !418

do.cond:                                          ; preds = %if.end63
  %55 = load i8*, i8** %p, align 8, !dbg !419
  %incdec.ptr64 = getelementptr inbounds i8, i8* %55, i32 1, !dbg !419
  store i8* %incdec.ptr64, i8** %p, align 8, !dbg !419
  %56 = load i8, i8* %55, align 1, !dbg !420
  %conv65 = sext i8 %56 to i32, !dbg !420
  %tobool66 = icmp ne i32 %conv65, 0, !dbg !420
  br i1 %tobool66, label %land.rhs, label %land.end, !dbg !421

land.rhs:                                         ; preds = %do.cond
  %57 = load i8*, i8** %m, align 8, !dbg !422
  %arraydecay67 = getelementptr inbounds [80 x i8], [80 x i8]* %fmode, i32 0, i32 0, !dbg !424
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay67, i64 80, !dbg !425
  %cmp68 = icmp ne i8* %57, %add.ptr, !dbg !426
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %58 = phi i1 [ false, %do.cond ], [ %cmp68, %land.rhs ]
  br i1 %58, label %do.body, label %do.end, !dbg !427

do.end:                                           ; preds = %land.end
  %59 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !429
  %mode70 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %59, i32 0, i32 10, !dbg !431
  %60 = load i8, i8* %mode70, align 4, !dbg !431
  %conv71 = sext i8 %60 to i32, !dbg !429
  %cmp72 = icmp eq i32 %conv71, 0, !dbg !432
  br i1 %cmp72, label %if.then74, label %if.end76, !dbg !433

if.then74:                                        ; preds = %do.end
  %61 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !434
  %call75 = call i32 @destroy(%struct.gz_stream* %61), !dbg !436
  store i8* null, i8** %retval, align 8, !dbg !437
  br label %return, !dbg !437

if.end76:                                         ; preds = %do.end
  %62 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !438
  %mode77 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %62, i32 0, i32 10, !dbg !440
  %63 = load i8, i8* %mode77, align 4, !dbg !440
  %conv78 = sext i8 %63 to i32, !dbg !438
  %cmp79 = icmp eq i32 %conv78, 119, !dbg !441
  br i1 %cmp79, label %if.then81, label %if.else97, !dbg !442

if.then81:                                        ; preds = %if.end76
  %64 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !443
  %stream82 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %64, i32 0, i32 0, !dbg !443
  %65 = load i32, i32* %level, align 4, !dbg !443
  %66 = load i32, i32* %strategy, align 4, !dbg !443
  %call83 = call i32 @cm_zlib_deflateInit2_(%struct.z_stream_s* %stream82, i32 %65, i32 8, i32 -15, i32 8, i32 %66, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i32 0, i32 0), i32 112), !dbg !443
  store i32 %call83, i32* %err, align 4, !dbg !445
  %call84 = call noalias i8* @malloc(i64 16384) #6, !dbg !446
  %67 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !447
  %outbuf85 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %67, i32 0, i32 5, !dbg !448
  store i8* %call84, i8** %outbuf85, align 8, !dbg !449
  %68 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !450
  %stream86 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %68, i32 0, i32 0, !dbg !451
  %next_out87 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream86, i32 0, i32 3, !dbg !452
  store i8* %call84, i8** %next_out87, align 8, !dbg !453
  %69 = load i32, i32* %err, align 4, !dbg !454
  %cmp88 = icmp ne i32 %69, 0, !dbg !456
  br i1 %cmp88, label %if.then94, label %lor.lhs.false90, !dbg !457

lor.lhs.false90:                                  ; preds = %if.then81
  %70 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !458
  %outbuf91 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %70, i32 0, i32 5, !dbg !460
  %71 = load i8*, i8** %outbuf91, align 8, !dbg !460
  %cmp92 = icmp eq i8* %71, null, !dbg !461
  br i1 %cmp92, label %if.then94, label %if.end96, !dbg !462

if.then94:                                        ; preds = %lor.lhs.false90, %if.then81
  %72 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !463
  %call95 = call i32 @destroy(%struct.gz_stream* %72), !dbg !465
  store i8* null, i8** %retval, align 8, !dbg !466
  br label %return, !dbg !466

if.end96:                                         ; preds = %lor.lhs.false90
  br label %if.end113, !dbg !467

if.else97:                                        ; preds = %if.end76
  %call98 = call noalias i8* @malloc(i64 16384) #6, !dbg !468
  %73 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !470
  %inbuf99 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %73, i32 0, i32 4, !dbg !471
  store i8* %call98, i8** %inbuf99, align 8, !dbg !472
  %74 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !473
  %stream100 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %74, i32 0, i32 0, !dbg !474
  %next_in101 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream100, i32 0, i32 0, !dbg !475
  store i8* %call98, i8** %next_in101, align 8, !dbg !476
  %75 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !477
  %stream102 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %75, i32 0, i32 0, !dbg !477
  %call103 = call i32 @cm_zlib_inflateInit2_(%struct.z_stream_s* %stream102, i32 -15, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i32 0, i32 0), i32 112), !dbg !477
  store i32 %call103, i32* %err, align 4, !dbg !478
  %76 = load i32, i32* %err, align 4, !dbg !479
  %cmp104 = icmp ne i32 %76, 0, !dbg !481
  br i1 %cmp104, label %if.then110, label %lor.lhs.false106, !dbg !482

lor.lhs.false106:                                 ; preds = %if.else97
  %77 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !483
  %inbuf107 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %77, i32 0, i32 4, !dbg !485
  %78 = load i8*, i8** %inbuf107, align 8, !dbg !485
  %cmp108 = icmp eq i8* %78, null, !dbg !486
  br i1 %cmp108, label %if.then110, label %if.end112, !dbg !487

if.then110:                                       ; preds = %lor.lhs.false106, %if.else97
  %79 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !488
  %call111 = call i32 @destroy(%struct.gz_stream* %79), !dbg !490
  store i8* null, i8** %retval, align 8, !dbg !491
  br label %return, !dbg !491

if.end112:                                        ; preds = %lor.lhs.false106
  br label %if.end113

if.end113:                                        ; preds = %if.end112, %if.end96
  %80 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !492
  %stream114 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %80, i32 0, i32 0, !dbg !493
  %avail_out115 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream114, i32 0, i32 4, !dbg !494
  store i32 16384, i32* %avail_out115, align 8, !dbg !495
  %call116 = call i32* @__errno_location() #1, !dbg !496
  store i32 0, i32* %call116, align 4, !dbg !497
  %81 = load i32, i32* %fd.addr, align 4, !dbg !498
  %cmp117 = icmp slt i32 %81, 0, !dbg !499
  br i1 %cmp117, label %cond.true, label %cond.false, !dbg !498

cond.true:                                        ; preds = %if.end113
  %82 = load i8*, i8** %path.addr, align 8, !dbg !500
  %arraydecay119 = getelementptr inbounds [80 x i8], [80 x i8]* %fmode, i32 0, i32 0, !dbg !500
  %call120 = call %struct._IO_FILE* @fopen(i8* %82, i8* %arraydecay119), !dbg !500
  br label %cond.end, !dbg !501

cond.false:                                       ; preds = %if.end113
  %83 = load i32, i32* %fd.addr, align 4, !dbg !502
  %arraydecay121 = getelementptr inbounds [80 x i8], [80 x i8]* %fmode, i32 0, i32 0, !dbg !503
  %call122 = call %struct._IO_FILE* @fdopen(i32 %83, i8* %arraydecay121) #6, !dbg !504
  br label %cond.end, !dbg !505

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct._IO_FILE* [ %call120, %cond.true ], [ %call122, %cond.false ], !dbg !506
  %84 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !508
  %file123 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %84, i32 0, i32 3, !dbg !509
  store %struct._IO_FILE* %cond, %struct._IO_FILE** %file123, align 8, !dbg !510
  %85 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !511
  %file124 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %85, i32 0, i32 3, !dbg !513
  %86 = load %struct._IO_FILE*, %struct._IO_FILE** %file124, align 8, !dbg !513
  %cmp125 = icmp eq %struct._IO_FILE* %86, null, !dbg !514
  br i1 %cmp125, label %if.then127, label %if.end129, !dbg !515

if.then127:                                       ; preds = %cond.end
  %87 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !516
  %call128 = call i32 @destroy(%struct.gz_stream* %87), !dbg !518
  store i8* null, i8** %retval, align 8, !dbg !519
  br label %return, !dbg !519

if.end129:                                        ; preds = %cond.end
  %88 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !520
  %mode130 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %88, i32 0, i32 10, !dbg !522
  %89 = load i8, i8* %mode130, align 4, !dbg !522
  %conv131 = sext i8 %89 to i32, !dbg !520
  %cmp132 = icmp eq i32 %conv131, 119, !dbg !523
  br i1 %cmp132, label %if.then134, label %if.else137, !dbg !524

if.then134:                                       ; preds = %if.end129
  %90 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !525
  %file135 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %90, i32 0, i32 3, !dbg !527
  %91 = load %struct._IO_FILE*, %struct._IO_FILE** %file135, align 8, !dbg !527
  %92 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @gz_magic, i64 0, i64 0), align 4, !dbg !528
  %93 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @gz_magic, i64 0, i64 1), align 4, !dbg !529
  %call136 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %91, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.4, i32 0, i32 0), i32 %92, i32 %93, i32 8, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 3), !dbg !530
  %94 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !531
  %start = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %94, i32 0, i32 11, !dbg !532
  store i64 10, i64* %start, align 8, !dbg !533
  br label %if.end145, !dbg !534

if.else137:                                       ; preds = %if.end129
  %95 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !535
  call void @check_header(%struct.gz_stream* %95), !dbg !537
  %96 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !538
  %file138 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %96, i32 0, i32 3, !dbg !539
  %97 = load %struct._IO_FILE*, %struct._IO_FILE** %file138, align 8, !dbg !539
  %call139 = call i64 @ftell(%struct._IO_FILE* %97), !dbg !540
  %98 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !541
  %stream140 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %98, i32 0, i32 0, !dbg !542
  %avail_in141 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream140, i32 0, i32 1, !dbg !543
  %99 = load i32, i32* %avail_in141, align 8, !dbg !543
  %conv142 = zext i32 %99 to i64, !dbg !541
  %sub143 = sub nsw i64 %call139, %conv142, !dbg !544
  %100 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !545
  %start144 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %100, i32 0, i32 11, !dbg !546
  store i64 %sub143, i64* %start144, align 8, !dbg !547
  br label %if.end145

if.end145:                                        ; preds = %if.else137, %if.then134
  %101 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !548
  %102 = bitcast %struct.gz_stream* %101 to i8*, !dbg !549
  store i8* %102, i8** %retval, align 8, !dbg !550
  br label %return, !dbg !550

return:                                           ; preds = %if.end145, %if.then127, %if.then110, %if.then94, %if.then74, %if.then16, %if.then3, %if.then
  %103 = load i8*, i8** %retval, align 8, !dbg !551
  ret i8* %103, !dbg !551
}

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_gzdopen(i32 %fd, i8* %mode) #0 !dbg !137 {
entry:
  %retval = alloca i8*, align 8
  %fd.addr = alloca i32, align 4
  %mode.addr = alloca i8*, align 8
  %name = alloca [46 x i8], align 16
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !552, metadata !215), !dbg !553
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !554, metadata !215), !dbg !555
  call void @llvm.dbg.declare(metadata [46 x i8]* %name, metadata !556, metadata !215), !dbg !560
  %0 = load i32, i32* %fd.addr, align 4, !dbg !561
  %cmp = icmp slt i32 %0, 0, !dbg !563
  br i1 %cmp, label %if.then, label %if.end, !dbg !564

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !565
  br label %return, !dbg !565

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %name, i32 0, i32 0, !dbg !567
  %1 = load i32, i32* %fd.addr, align 4, !dbg !568
  %call = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 %1) #6, !dbg !569
  %arraydecay1 = getelementptr inbounds [46 x i8], [46 x i8]* %name, i32 0, i32 0, !dbg !570
  %2 = load i8*, i8** %mode.addr, align 8, !dbg !571
  %3 = load i32, i32* %fd.addr, align 4, !dbg !572
  %call2 = call i8* @gz_open(i8* %arraydecay1, i8* %2, i32 %3), !dbg !573
  store i8* %call2, i8** %retval, align 8, !dbg !574
  br label %return, !dbg !574

return:                                           ; preds = %if.end, %if.then
  %4 = load i8*, i8** %retval, align 8, !dbg !575
  ret i8* %4, !dbg !575
}

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzsetparams(i8* %file, i32 %level, i32 %strategy) #0 !dbg !140 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %level.addr = alloca i32, align 4
  %strategy.addr = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !576, metadata !215), !dbg !577
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !578, metadata !215), !dbg !579
  store i32 %strategy, i32* %strategy.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %strategy.addr, metadata !580, metadata !215), !dbg !581
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !582, metadata !215), !dbg !583
  %0 = load i8*, i8** %file.addr, align 8, !dbg !584
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !585
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !583
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !586
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !588
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !589

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !590
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !592
  %4 = load i8, i8* %mode, align 4, !dbg !592
  %conv = sext i8 %4 to i32, !dbg !590
  %cmp1 = icmp ne i32 %conv, 119, !dbg !593
  br i1 %cmp1, label %if.then, label %if.end, !dbg !594

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !595
  br label %return, !dbg !595

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !597
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 0, !dbg !599
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 4, !dbg !600
  %6 = load i32, i32* %avail_out, align 8, !dbg !600
  %cmp3 = icmp eq i32 %6, 0, !dbg !601
  br i1 %cmp3, label %if.then5, label %if.end15, !dbg !602

if.then5:                                         ; preds = %if.end
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !603
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 5, !dbg !605
  %8 = load i8*, i8** %outbuf, align 8, !dbg !605
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !606
  %stream6 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 0, !dbg !607
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream6, i32 0, i32 3, !dbg !608
  store i8* %8, i8** %next_out, align 8, !dbg !609
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !610
  %outbuf7 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 5, !dbg !612
  %11 = load i8*, i8** %outbuf7, align 8, !dbg !612
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !613
  %file8 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 3, !dbg !614
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %file8, align 8, !dbg !614
  %call = call i64 @fwrite(i8* %11, i64 1, i64 16384, %struct._IO_FILE* %13), !dbg !615
  %cmp9 = icmp ne i64 %call, 16384, !dbg !616
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !617

if.then11:                                        ; preds = %if.then5
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !618
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 1, !dbg !620
  store i32 -1, i32* %z_err, align 8, !dbg !621
  br label %if.end12, !dbg !622

if.end12:                                         ; preds = %if.then11, %if.then5
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !623
  %stream13 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 0, !dbg !624
  %avail_out14 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream13, i32 0, i32 4, !dbg !625
  store i32 16384, i32* %avail_out14, align 8, !dbg !626
  br label %if.end15, !dbg !627

if.end15:                                         ; preds = %if.end12, %if.end
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !628
  %stream16 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 0, !dbg !629
  %17 = load i32, i32* %level.addr, align 4, !dbg !630
  %18 = load i32, i32* %strategy.addr, align 4, !dbg !631
  %call17 = call i32 @cm_zlib_deflateParams(%struct.z_stream_s* %stream16, i32 %17, i32 %18), !dbg !632
  store i32 %call17, i32* %retval, align 4, !dbg !633
  br label %return, !dbg !633

return:                                           ; preds = %if.end15, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !634
  ret i32 %19, !dbg !634
}

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #3

declare i32 @cm_zlib_deflateParams(%struct.z_stream_s*, i32, i32) #3

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzread(i8* %file, i8* %buf, i32 %len) #0 !dbg !143 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  %start = alloca i8*, align 8
  %next_out = alloca i8*, align 8
  %n = alloca i32, align 4
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !635, metadata !215), !dbg !636
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !637, metadata !215), !dbg !638
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !639, metadata !215), !dbg !640
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !641, metadata !215), !dbg !642
  %0 = load i8*, i8** %file.addr, align 8, !dbg !643
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !644
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !642
  call void @llvm.dbg.declare(metadata i8** %start, metadata !645, metadata !215), !dbg !646
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !647
  store i8* %2, i8** %start, align 8, !dbg !646
  call void @llvm.dbg.declare(metadata i8** %next_out, metadata !648, metadata !215), !dbg !649
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !650
  %cmp = icmp eq %struct.gz_stream* %3, null, !dbg !652
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !653

lor.lhs.false:                                    ; preds = %entry
  %4 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !654
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %4, i32 0, i32 10, !dbg !656
  %5 = load i8, i8* %mode, align 4, !dbg !656
  %conv = sext i8 %5 to i32, !dbg !654
  %cmp1 = icmp ne i32 %conv, 114, !dbg !657
  br i1 %cmp1, label %if.then, label %if.end, !dbg !658

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !659
  br label %return, !dbg !659

if.end:                                           ; preds = %lor.lhs.false
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !661
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 1, !dbg !663
  %7 = load i32, i32* %z_err, align 8, !dbg !663
  %cmp3 = icmp eq i32 %7, -3, !dbg !664
  br i1 %cmp3, label %if.then9, label %lor.lhs.false5, !dbg !665

lor.lhs.false5:                                   ; preds = %if.end
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !666
  %z_err6 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 1, !dbg !668
  %9 = load i32, i32* %z_err6, align 8, !dbg !668
  %cmp7 = icmp eq i32 %9, -1, !dbg !669
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !670

if.then9:                                         ; preds = %lor.lhs.false5, %if.end
  store i32 -1, i32* %retval, align 4, !dbg !671
  br label %return, !dbg !671

if.end10:                                         ; preds = %lor.lhs.false5
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !673
  %z_err11 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 1, !dbg !675
  %11 = load i32, i32* %z_err11, align 8, !dbg !675
  %cmp12 = icmp eq i32 %11, 1, !dbg !676
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !677

if.then14:                                        ; preds = %if.end10
  store i32 0, i32* %retval, align 4, !dbg !678
  br label %return, !dbg !678

if.end15:                                         ; preds = %if.end10
  %12 = load i8*, i8** %buf.addr, align 8, !dbg !680
  store i8* %12, i8** %next_out, align 8, !dbg !681
  %13 = load i8*, i8** %buf.addr, align 8, !dbg !682
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !683
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 0, !dbg !684
  %next_out16 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 3, !dbg !685
  store i8* %13, i8** %next_out16, align 8, !dbg !686
  %15 = load i32, i32* %len.addr, align 4, !dbg !687
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !688
  %stream17 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 0, !dbg !689
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream17, i32 0, i32 4, !dbg !690
  store i32 %15, i32* %avail_out, align 8, !dbg !691
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !692
  %stream18 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 0, !dbg !694
  %avail_out19 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream18, i32 0, i32 4, !dbg !695
  %18 = load i32, i32* %avail_out19, align 8, !dbg !695
  %tobool = icmp ne i32 %18, 0, !dbg !692
  br i1 %tobool, label %land.lhs.true, label %if.end36, !dbg !696

land.lhs.true:                                    ; preds = %if.end15
  %19 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !697
  %back = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %19, i32 0, i32 14, !dbg !699
  %20 = load i32, i32* %back, align 8, !dbg !699
  %cmp20 = icmp ne i32 %20, -1, !dbg !700
  br i1 %cmp20, label %if.then22, label %if.end36, !dbg !701

if.then22:                                        ; preds = %land.lhs.true
  %21 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !702
  %back23 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %21, i32 0, i32 14, !dbg !704
  %22 = load i32, i32* %back23, align 8, !dbg !704
  %conv24 = trunc i32 %22 to i8, !dbg !702
  %23 = load i8*, i8** %next_out, align 8, !dbg !705
  %incdec.ptr = getelementptr inbounds i8, i8* %23, i32 1, !dbg !705
  store i8* %incdec.ptr, i8** %next_out, align 8, !dbg !705
  store i8 %conv24, i8* %23, align 1, !dbg !706
  %24 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !707
  %stream25 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %24, i32 0, i32 0, !dbg !708
  %next_out26 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream25, i32 0, i32 3, !dbg !709
  %25 = load i8*, i8** %next_out26, align 8, !dbg !710
  %incdec.ptr27 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !710
  store i8* %incdec.ptr27, i8** %next_out26, align 8, !dbg !710
  %26 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !711
  %stream28 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %26, i32 0, i32 0, !dbg !712
  %avail_out29 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream28, i32 0, i32 4, !dbg !713
  %27 = load i32, i32* %avail_out29, align 8, !dbg !714
  %dec = add i32 %27, -1, !dbg !714
  store i32 %dec, i32* %avail_out29, align 8, !dbg !714
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !715
  %back30 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 14, !dbg !716
  store i32 -1, i32* %back30, align 8, !dbg !717
  %29 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !718
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %29, i32 0, i32 13, !dbg !719
  %30 = load i64, i64* %out, align 8, !dbg !720
  %inc = add nsw i64 %30, 1, !dbg !720
  store i64 %inc, i64* %out, align 8, !dbg !720
  %31 = load i8*, i8** %start, align 8, !dbg !721
  %incdec.ptr31 = getelementptr inbounds i8, i8* %31, i32 1, !dbg !721
  store i8* %incdec.ptr31, i8** %start, align 8, !dbg !721
  %32 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !722
  %last = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %32, i32 0, i32 15, !dbg !724
  %33 = load i32, i32* %last, align 4, !dbg !724
  %tobool32 = icmp ne i32 %33, 0, !dbg !722
  br i1 %tobool32, label %if.then33, label %if.end35, !dbg !725

if.then33:                                        ; preds = %if.then22
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !726
  %z_err34 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %34, i32 0, i32 1, !dbg !728
  store i32 1, i32* %z_err34, align 8, !dbg !729
  store i32 1, i32* %retval, align 4, !dbg !730
  br label %return, !dbg !730

if.end35:                                         ; preds = %if.then22
  br label %if.end36, !dbg !731

if.end36:                                         ; preds = %if.end35, %land.lhs.true, %if.end15
  br label %while.cond, !dbg !732

while.cond:                                       ; preds = %if.end187, %if.end36
  %35 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !733
  %stream37 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %35, i32 0, i32 0, !dbg !735
  %avail_out38 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream37, i32 0, i32 4, !dbg !736
  %36 = load i32, i32* %avail_out38, align 8, !dbg !736
  %cmp39 = icmp ne i32 %36, 0, !dbg !737
  br i1 %cmp39, label %while.body, label %while.end, !dbg !738

while.body:                                       ; preds = %while.cond
  %37 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !739
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %37, i32 0, i32 9, !dbg !742
  %38 = load i32, i32* %transparent, align 8, !dbg !742
  %tobool41 = icmp ne i32 %38, 0, !dbg !739
  br i1 %tobool41, label %if.then42, label %if.end96, !dbg !743

if.then42:                                        ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %n, metadata !744, metadata !215), !dbg !746
  %39 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !747
  %stream43 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %39, i32 0, i32 0, !dbg !748
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream43, i32 0, i32 1, !dbg !749
  %40 = load i32, i32* %avail_in, align 8, !dbg !749
  store i32 %40, i32* %n, align 4, !dbg !746
  %41 = load i32, i32* %n, align 4, !dbg !750
  %42 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !752
  %stream44 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %42, i32 0, i32 0, !dbg !753
  %avail_out45 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream44, i32 0, i32 4, !dbg !754
  %43 = load i32, i32* %avail_out45, align 8, !dbg !754
  %cmp46 = icmp ugt i32 %41, %43, !dbg !755
  br i1 %cmp46, label %if.then48, label %if.end51, !dbg !756

if.then48:                                        ; preds = %if.then42
  %44 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !757
  %stream49 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %44, i32 0, i32 0, !dbg !759
  %avail_out50 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream49, i32 0, i32 4, !dbg !760
  %45 = load i32, i32* %avail_out50, align 8, !dbg !760
  store i32 %45, i32* %n, align 4, !dbg !761
  br label %if.end51, !dbg !762

if.end51:                                         ; preds = %if.then48, %if.then42
  %46 = load i32, i32* %n, align 4, !dbg !763
  %cmp52 = icmp ugt i32 %46, 0, !dbg !765
  br i1 %cmp52, label %if.then54, label %if.end70, !dbg !766

if.then54:                                        ; preds = %if.end51
  %47 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !767
  %stream55 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %47, i32 0, i32 0, !dbg !769
  %next_out56 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream55, i32 0, i32 3, !dbg !770
  %48 = load i8*, i8** %next_out56, align 8, !dbg !770
  %49 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !771
  %stream57 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %49, i32 0, i32 0, !dbg !772
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream57, i32 0, i32 0, !dbg !773
  %50 = load i8*, i8** %next_in, align 8, !dbg !773
  %51 = load i32, i32* %n, align 4, !dbg !774
  %conv58 = zext i32 %51 to i64, !dbg !774
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %48, i8* %50, i64 %conv58, i32 1, i1 false), !dbg !775
  %52 = load i32, i32* %n, align 4, !dbg !776
  %53 = load i8*, i8** %next_out, align 8, !dbg !777
  %idx.ext = zext i32 %52 to i64, !dbg !777
  %add.ptr = getelementptr inbounds i8, i8* %53, i64 %idx.ext, !dbg !777
  store i8* %add.ptr, i8** %next_out, align 8, !dbg !777
  %54 = load i8*, i8** %next_out, align 8, !dbg !778
  %55 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !779
  %stream59 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %55, i32 0, i32 0, !dbg !780
  %next_out60 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream59, i32 0, i32 3, !dbg !781
  store i8* %54, i8** %next_out60, align 8, !dbg !782
  %56 = load i32, i32* %n, align 4, !dbg !783
  %57 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !784
  %stream61 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %57, i32 0, i32 0, !dbg !785
  %next_in62 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream61, i32 0, i32 0, !dbg !786
  %58 = load i8*, i8** %next_in62, align 8, !dbg !787
  %idx.ext63 = zext i32 %56 to i64, !dbg !787
  %add.ptr64 = getelementptr inbounds i8, i8* %58, i64 %idx.ext63, !dbg !787
  store i8* %add.ptr64, i8** %next_in62, align 8, !dbg !787
  %59 = load i32, i32* %n, align 4, !dbg !788
  %60 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !789
  %stream65 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %60, i32 0, i32 0, !dbg !790
  %avail_out66 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream65, i32 0, i32 4, !dbg !791
  %61 = load i32, i32* %avail_out66, align 8, !dbg !792
  %sub = sub i32 %61, %59, !dbg !792
  store i32 %sub, i32* %avail_out66, align 8, !dbg !792
  %62 = load i32, i32* %n, align 4, !dbg !793
  %63 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !794
  %stream67 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %63, i32 0, i32 0, !dbg !795
  %avail_in68 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream67, i32 0, i32 1, !dbg !796
  %64 = load i32, i32* %avail_in68, align 8, !dbg !797
  %sub69 = sub i32 %64, %62, !dbg !797
  store i32 %sub69, i32* %avail_in68, align 8, !dbg !797
  br label %if.end70, !dbg !798

if.end70:                                         ; preds = %if.then54, %if.end51
  %65 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !799
  %stream71 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %65, i32 0, i32 0, !dbg !801
  %avail_out72 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream71, i32 0, i32 4, !dbg !802
  %66 = load i32, i32* %avail_out72, align 8, !dbg !802
  %cmp73 = icmp ugt i32 %66, 0, !dbg !803
  br i1 %cmp73, label %if.then75, label %if.end84, !dbg !804

if.then75:                                        ; preds = %if.end70
  %67 = load i8*, i8** %next_out, align 8, !dbg !805
  %68 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !807
  %stream76 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %68, i32 0, i32 0, !dbg !808
  %avail_out77 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream76, i32 0, i32 4, !dbg !809
  %69 = load i32, i32* %avail_out77, align 8, !dbg !809
  %conv78 = zext i32 %69 to i64, !dbg !807
  %70 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !810
  %file79 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %70, i32 0, i32 3, !dbg !811
  %71 = load %struct._IO_FILE*, %struct._IO_FILE** %file79, align 8, !dbg !811
  %call = call i64 @fread(i8* %67, i64 1, i64 %conv78, %struct._IO_FILE* %71), !dbg !812
  %conv80 = trunc i64 %call to i32, !dbg !813
  %72 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !814
  %stream81 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %72, i32 0, i32 0, !dbg !815
  %avail_out82 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream81, i32 0, i32 4, !dbg !816
  %73 = load i32, i32* %avail_out82, align 8, !dbg !817
  %sub83 = sub i32 %73, %conv80, !dbg !817
  store i32 %sub83, i32* %avail_out82, align 8, !dbg !817
  br label %if.end84, !dbg !818

if.end84:                                         ; preds = %if.then75, %if.end70
  %74 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !819
  %stream85 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %74, i32 0, i32 0, !dbg !820
  %avail_out86 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream85, i32 0, i32 4, !dbg !821
  %75 = load i32, i32* %avail_out86, align 8, !dbg !821
  %76 = load i32, i32* %len.addr, align 4, !dbg !822
  %sub87 = sub i32 %76, %75, !dbg !822
  store i32 %sub87, i32* %len.addr, align 4, !dbg !822
  %77 = load i32, i32* %len.addr, align 4, !dbg !823
  %conv88 = zext i32 %77 to i64, !dbg !823
  %78 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !824
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %78, i32 0, i32 12, !dbg !825
  %79 = load i64, i64* %in, align 8, !dbg !826
  %add = add nsw i64 %79, %conv88, !dbg !826
  store i64 %add, i64* %in, align 8, !dbg !826
  %80 = load i32, i32* %len.addr, align 4, !dbg !827
  %conv89 = zext i32 %80 to i64, !dbg !827
  %81 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !828
  %out90 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %81, i32 0, i32 13, !dbg !829
  %82 = load i64, i64* %out90, align 8, !dbg !830
  %add91 = add nsw i64 %82, %conv89, !dbg !830
  store i64 %add91, i64* %out90, align 8, !dbg !830
  %83 = load i32, i32* %len.addr, align 4, !dbg !831
  %cmp92 = icmp eq i32 %83, 0, !dbg !833
  br i1 %cmp92, label %if.then94, label %if.end95, !dbg !834

if.then94:                                        ; preds = %if.end84
  %84 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !835
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %84, i32 0, i32 2, !dbg !837
  store i32 1, i32* %z_eof, align 4, !dbg !838
  br label %if.end95, !dbg !835

if.end95:                                         ; preds = %if.then94, %if.end84
  %85 = load i32, i32* %len.addr, align 4, !dbg !839
  store i32 %85, i32* %retval, align 4, !dbg !840
  br label %return, !dbg !840

if.end96:                                         ; preds = %while.body
  %86 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !841
  %stream97 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %86, i32 0, i32 0, !dbg !843
  %avail_in98 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream97, i32 0, i32 1, !dbg !844
  %87 = load i32, i32* %avail_in98, align 8, !dbg !844
  %cmp99 = icmp eq i32 %87, 0, !dbg !845
  br i1 %cmp99, label %land.lhs.true101, label %if.end127, !dbg !846

land.lhs.true101:                                 ; preds = %if.end96
  %88 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !847
  %z_eof102 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %88, i32 0, i32 2, !dbg !849
  %89 = load i32, i32* %z_eof102, align 4, !dbg !849
  %tobool103 = icmp ne i32 %89, 0, !dbg !847
  br i1 %tobool103, label %if.end127, label %if.then104, !dbg !850

if.then104:                                       ; preds = %land.lhs.true101
  %call105 = call i32* @__errno_location() #1, !dbg !851
  store i32 0, i32* %call105, align 4, !dbg !853
  %90 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !854
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %90, i32 0, i32 4, !dbg !855
  %91 = load i8*, i8** %inbuf, align 8, !dbg !855
  %92 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !856
  %file106 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %92, i32 0, i32 3, !dbg !857
  %93 = load %struct._IO_FILE*, %struct._IO_FILE** %file106, align 8, !dbg !857
  %call107 = call i64 @fread(i8* %91, i64 1, i64 16384, %struct._IO_FILE* %93), !dbg !858
  %conv108 = trunc i64 %call107 to i32, !dbg !859
  %94 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !860
  %stream109 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %94, i32 0, i32 0, !dbg !861
  %avail_in110 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream109, i32 0, i32 1, !dbg !862
  store i32 %conv108, i32* %avail_in110, align 8, !dbg !863
  %95 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !864
  %stream111 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %95, i32 0, i32 0, !dbg !866
  %avail_in112 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream111, i32 0, i32 1, !dbg !867
  %96 = load i32, i32* %avail_in112, align 8, !dbg !867
  %cmp113 = icmp eq i32 %96, 0, !dbg !868
  br i1 %cmp113, label %if.then115, label %if.end123, !dbg !869

if.then115:                                       ; preds = %if.then104
  %97 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !870
  %z_eof116 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %97, i32 0, i32 2, !dbg !872
  store i32 1, i32* %z_eof116, align 4, !dbg !873
  %98 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !874
  %file117 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %98, i32 0, i32 3, !dbg !876
  %99 = load %struct._IO_FILE*, %struct._IO_FILE** %file117, align 8, !dbg !876
  %call118 = call i32 @ferror(%struct._IO_FILE* %99) #6, !dbg !877
  %tobool119 = icmp ne i32 %call118, 0, !dbg !877
  br i1 %tobool119, label %if.then120, label %if.end122, !dbg !878

if.then120:                                       ; preds = %if.then115
  %100 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !879
  %z_err121 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %100, i32 0, i32 1, !dbg !881
  store i32 -1, i32* %z_err121, align 8, !dbg !882
  br label %while.end, !dbg !883

if.end122:                                        ; preds = %if.then115
  br label %if.end123, !dbg !884

if.end123:                                        ; preds = %if.end122, %if.then104
  %101 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !885
  %inbuf124 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %101, i32 0, i32 4, !dbg !886
  %102 = load i8*, i8** %inbuf124, align 8, !dbg !886
  %103 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !887
  %stream125 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %103, i32 0, i32 0, !dbg !888
  %next_in126 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream125, i32 0, i32 0, !dbg !889
  store i8* %102, i8** %next_in126, align 8, !dbg !890
  br label %if.end127, !dbg !891

if.end127:                                        ; preds = %if.end123, %land.lhs.true101, %if.end96
  %104 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !892
  %stream128 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %104, i32 0, i32 0, !dbg !893
  %avail_in129 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream128, i32 0, i32 1, !dbg !894
  %105 = load i32, i32* %avail_in129, align 8, !dbg !894
  %conv130 = zext i32 %105 to i64, !dbg !892
  %106 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !895
  %in131 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %106, i32 0, i32 12, !dbg !896
  %107 = load i64, i64* %in131, align 8, !dbg !897
  %add132 = add nsw i64 %107, %conv130, !dbg !897
  store i64 %add132, i64* %in131, align 8, !dbg !897
  %108 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !898
  %stream133 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %108, i32 0, i32 0, !dbg !899
  %avail_out134 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream133, i32 0, i32 4, !dbg !900
  %109 = load i32, i32* %avail_out134, align 8, !dbg !900
  %conv135 = zext i32 %109 to i64, !dbg !898
  %110 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !901
  %out136 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %110, i32 0, i32 13, !dbg !902
  %111 = load i64, i64* %out136, align 8, !dbg !903
  %add137 = add nsw i64 %111, %conv135, !dbg !903
  store i64 %add137, i64* %out136, align 8, !dbg !903
  %112 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !904
  %stream138 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %112, i32 0, i32 0, !dbg !905
  %call139 = call i32 @cm_zlib_inflate(%struct.z_stream_s* %stream138, i32 0), !dbg !906
  %113 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !907
  %z_err140 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %113, i32 0, i32 1, !dbg !908
  store i32 %call139, i32* %z_err140, align 8, !dbg !909
  %114 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !910
  %stream141 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %114, i32 0, i32 0, !dbg !911
  %avail_in142 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream141, i32 0, i32 1, !dbg !912
  %115 = load i32, i32* %avail_in142, align 8, !dbg !912
  %conv143 = zext i32 %115 to i64, !dbg !910
  %116 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !913
  %in144 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %116, i32 0, i32 12, !dbg !914
  %117 = load i64, i64* %in144, align 8, !dbg !915
  %sub145 = sub nsw i64 %117, %conv143, !dbg !915
  store i64 %sub145, i64* %in144, align 8, !dbg !915
  %118 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !916
  %stream146 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %118, i32 0, i32 0, !dbg !917
  %avail_out147 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream146, i32 0, i32 4, !dbg !918
  %119 = load i32, i32* %avail_out147, align 8, !dbg !918
  %conv148 = zext i32 %119 to i64, !dbg !916
  %120 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !919
  %out149 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %120, i32 0, i32 13, !dbg !920
  %121 = load i64, i64* %out149, align 8, !dbg !921
  %sub150 = sub nsw i64 %121, %conv148, !dbg !921
  store i64 %sub150, i64* %out149, align 8, !dbg !921
  %122 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !922
  %z_err151 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %122, i32 0, i32 1, !dbg !924
  %123 = load i32, i32* %z_err151, align 8, !dbg !924
  %cmp152 = icmp eq i32 %123, 1, !dbg !925
  br i1 %cmp152, label %if.then154, label %if.end179, !dbg !926

if.then154:                                       ; preds = %if.end127
  %124 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !927
  %crc = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %124, i32 0, i32 6, !dbg !929
  %125 = load i64, i64* %crc, align 8, !dbg !929
  %126 = load i8*, i8** %start, align 8, !dbg !930
  %127 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !931
  %stream155 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %127, i32 0, i32 0, !dbg !932
  %next_out156 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream155, i32 0, i32 3, !dbg !933
  %128 = load i8*, i8** %next_out156, align 8, !dbg !933
  %129 = load i8*, i8** %start, align 8, !dbg !934
  %sub.ptr.lhs.cast = ptrtoint i8* %128 to i64, !dbg !935
  %sub.ptr.rhs.cast = ptrtoint i8* %129 to i64, !dbg !935
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !935
  %conv157 = trunc i64 %sub.ptr.sub to i32, !dbg !936
  %call158 = call i64 @cm_zlib_crc32(i64 %125, i8* %126, i32 %conv157), !dbg !937
  %130 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !938
  %crc159 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %130, i32 0, i32 6, !dbg !939
  store i64 %call158, i64* %crc159, align 8, !dbg !940
  %131 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !941
  %stream160 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %131, i32 0, i32 0, !dbg !942
  %next_out161 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream160, i32 0, i32 3, !dbg !943
  %132 = load i8*, i8** %next_out161, align 8, !dbg !943
  store i8* %132, i8** %start, align 8, !dbg !944
  %133 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !945
  %call162 = call i64 @getLong(%struct.gz_stream* %133), !dbg !947
  %134 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !948
  %crc163 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %134, i32 0, i32 6, !dbg !949
  %135 = load i64, i64* %crc163, align 8, !dbg !949
  %cmp164 = icmp ne i64 %call162, %135, !dbg !950
  br i1 %cmp164, label %if.then166, label %if.else, !dbg !951

if.then166:                                       ; preds = %if.then154
  %136 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !952
  %z_err167 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %136, i32 0, i32 1, !dbg !954
  store i32 -3, i32* %z_err167, align 8, !dbg !955
  br label %if.end178, !dbg !956

if.else:                                          ; preds = %if.then154
  %137 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !957
  %call168 = call i64 @getLong(%struct.gz_stream* %137), !dbg !959
  %138 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !960
  call void @check_header(%struct.gz_stream* %138), !dbg !961
  %139 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !962
  %z_err169 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %139, i32 0, i32 1, !dbg !964
  %140 = load i32, i32* %z_err169, align 8, !dbg !964
  %cmp170 = icmp eq i32 %140, 0, !dbg !965
  br i1 %cmp170, label %if.then172, label %if.end177, !dbg !966

if.then172:                                       ; preds = %if.else
  %141 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !967
  %stream173 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %141, i32 0, i32 0, !dbg !969
  %call174 = call i32 @cm_zlib_inflateReset(%struct.z_stream_s* %stream173), !dbg !970
  %call175 = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !971
  %142 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !972
  %crc176 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %142, i32 0, i32 6, !dbg !973
  store i64 %call175, i64* %crc176, align 8, !dbg !974
  br label %if.end177, !dbg !975

if.end177:                                        ; preds = %if.then172, %if.else
  br label %if.end178

if.end178:                                        ; preds = %if.end177, %if.then166
  br label %if.end179, !dbg !976

if.end179:                                        ; preds = %if.end178, %if.end127
  %143 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !977
  %z_err180 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %143, i32 0, i32 1, !dbg !979
  %144 = load i32, i32* %z_err180, align 8, !dbg !979
  %cmp181 = icmp ne i32 %144, 0, !dbg !980
  br i1 %cmp181, label %if.then186, label %lor.lhs.false183, !dbg !981

lor.lhs.false183:                                 ; preds = %if.end179
  %145 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !982
  %z_eof184 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %145, i32 0, i32 2, !dbg !984
  %146 = load i32, i32* %z_eof184, align 4, !dbg !984
  %tobool185 = icmp ne i32 %146, 0, !dbg !982
  br i1 %tobool185, label %if.then186, label %if.end187, !dbg !985

if.then186:                                       ; preds = %lor.lhs.false183, %if.end179
  br label %while.end, !dbg !986

if.end187:                                        ; preds = %lor.lhs.false183
  br label %while.cond, !dbg !988

while.end:                                        ; preds = %if.then186, %if.then120, %while.cond
  %147 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !990
  %crc188 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %147, i32 0, i32 6, !dbg !991
  %148 = load i64, i64* %crc188, align 8, !dbg !991
  %149 = load i8*, i8** %start, align 8, !dbg !992
  %150 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !993
  %stream189 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %150, i32 0, i32 0, !dbg !994
  %next_out190 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream189, i32 0, i32 3, !dbg !995
  %151 = load i8*, i8** %next_out190, align 8, !dbg !995
  %152 = load i8*, i8** %start, align 8, !dbg !996
  %sub.ptr.lhs.cast191 = ptrtoint i8* %151 to i64, !dbg !997
  %sub.ptr.rhs.cast192 = ptrtoint i8* %152 to i64, !dbg !997
  %sub.ptr.sub193 = sub i64 %sub.ptr.lhs.cast191, %sub.ptr.rhs.cast192, !dbg !997
  %conv194 = trunc i64 %sub.ptr.sub193 to i32, !dbg !998
  %call195 = call i64 @cm_zlib_crc32(i64 %148, i8* %149, i32 %conv194), !dbg !999
  %153 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1000
  %crc196 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %153, i32 0, i32 6, !dbg !1001
  store i64 %call195, i64* %crc196, align 8, !dbg !1002
  %154 = load i32, i32* %len.addr, align 4, !dbg !1003
  %155 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1005
  %stream197 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %155, i32 0, i32 0, !dbg !1006
  %avail_out198 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream197, i32 0, i32 4, !dbg !1007
  %156 = load i32, i32* %avail_out198, align 8, !dbg !1007
  %cmp199 = icmp eq i32 %154, %156, !dbg !1008
  br i1 %cmp199, label %land.lhs.true201, label %if.end210, !dbg !1009

land.lhs.true201:                                 ; preds = %while.end
  %157 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1010
  %z_err202 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %157, i32 0, i32 1, !dbg !1011
  %158 = load i32, i32* %z_err202, align 8, !dbg !1011
  %cmp203 = icmp eq i32 %158, -3, !dbg !1012
  br i1 %cmp203, label %if.then209, label %lor.lhs.false205, !dbg !1013

lor.lhs.false205:                                 ; preds = %land.lhs.true201
  %159 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1014
  %z_err206 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %159, i32 0, i32 1, !dbg !1016
  %160 = load i32, i32* %z_err206, align 8, !dbg !1016
  %cmp207 = icmp eq i32 %160, -1, !dbg !1017
  br i1 %cmp207, label %if.then209, label %if.end210, !dbg !1018

if.then209:                                       ; preds = %lor.lhs.false205, %land.lhs.true201
  store i32 -1, i32* %retval, align 4, !dbg !1019
  br label %return, !dbg !1019

if.end210:                                        ; preds = %lor.lhs.false205, %while.end
  %161 = load i32, i32* %len.addr, align 4, !dbg !1020
  %162 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1021
  %stream211 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %162, i32 0, i32 0, !dbg !1022
  %avail_out212 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream211, i32 0, i32 4, !dbg !1023
  %163 = load i32, i32* %avail_out212, align 8, !dbg !1023
  %sub213 = sub i32 %161, %163, !dbg !1024
  store i32 %sub213, i32* %retval, align 4, !dbg !1025
  br label %return, !dbg !1025

return:                                           ; preds = %if.end210, %if.then209, %if.end95, %if.then33, %if.then14, %if.then9, %if.then
  %164 = load i32, i32* %retval, align 4, !dbg !1026
  ret i32 %164, !dbg !1026
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare i32 @ferror(%struct._IO_FILE*) #2

declare i32 @cm_zlib_inflate(%struct.z_stream_s*, i32) #3

declare i64 @cm_zlib_crc32(i64, i8*, i32) #3

; Function Attrs: nounwind uwtable
define internal i64 @getLong(%struct.gz_stream* %s) #0 !dbg !198 {
entry:
  %s.addr = alloca %struct.gz_stream*, align 8
  %x = alloca i64, align 8
  %c = alloca i32, align 4
  store %struct.gz_stream* %s, %struct.gz_stream** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s.addr, metadata !1027, metadata !215), !dbg !1028
  call void @llvm.dbg.declare(metadata i64* %x, metadata !1029, metadata !215), !dbg !1030
  %0 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1031
  %call = call i32 @get_byte(%struct.gz_stream* %0), !dbg !1032
  %conv = sext i32 %call to i64, !dbg !1033
  store i64 %conv, i64* %x, align 8, !dbg !1030
  call void @llvm.dbg.declare(metadata i32* %c, metadata !1034, metadata !215), !dbg !1035
  %1 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1036
  %call1 = call i32 @get_byte(%struct.gz_stream* %1), !dbg !1037
  %conv2 = sext i32 %call1 to i64, !dbg !1038
  %shl = shl i64 %conv2, 8, !dbg !1039
  %2 = load i64, i64* %x, align 8, !dbg !1040
  %add = add i64 %2, %shl, !dbg !1040
  store i64 %add, i64* %x, align 8, !dbg !1040
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1041
  %call3 = call i32 @get_byte(%struct.gz_stream* %3), !dbg !1042
  %conv4 = sext i32 %call3 to i64, !dbg !1043
  %shl5 = shl i64 %conv4, 16, !dbg !1044
  %4 = load i64, i64* %x, align 8, !dbg !1045
  %add6 = add i64 %4, %shl5, !dbg !1045
  store i64 %add6, i64* %x, align 8, !dbg !1045
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1046
  %call7 = call i32 @get_byte(%struct.gz_stream* %5), !dbg !1047
  store i32 %call7, i32* %c, align 4, !dbg !1048
  %6 = load i32, i32* %c, align 4, !dbg !1049
  %cmp = icmp eq i32 %6, -1, !dbg !1051
  br i1 %cmp, label %if.then, label %if.end, !dbg !1052

if.then:                                          ; preds = %entry
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1053
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 1, !dbg !1055
  store i32 -3, i32* %z_err, align 8, !dbg !1056
  br label %if.end, !dbg !1053

if.end:                                           ; preds = %if.then, %entry
  %8 = load i32, i32* %c, align 4, !dbg !1057
  %conv9 = sext i32 %8 to i64, !dbg !1058
  %shl10 = shl i64 %conv9, 24, !dbg !1059
  %9 = load i64, i64* %x, align 8, !dbg !1060
  %add11 = add i64 %9, %shl10, !dbg !1060
  store i64 %add11, i64* %x, align 8, !dbg !1060
  %10 = load i64, i64* %x, align 8, !dbg !1061
  ret i64 %10, !dbg !1062
}

; Function Attrs: nounwind uwtable
define internal void @check_header(%struct.gz_stream* %s) #0 !dbg !191 {
entry:
  %s.addr = alloca %struct.gz_stream*, align 8
  %method = alloca i32, align 4
  %flags = alloca i32, align 4
  %len = alloca i32, align 4
  %c = alloca i32, align 4
  store %struct.gz_stream* %s, %struct.gz_stream** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s.addr, metadata !1063, metadata !215), !dbg !1064
  call void @llvm.dbg.declare(metadata i32* %method, metadata !1065, metadata !215), !dbg !1066
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1067, metadata !215), !dbg !1068
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1069, metadata !215), !dbg !1070
  call void @llvm.dbg.declare(metadata i32* %c, metadata !1071, metadata !215), !dbg !1072
  %0 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1073
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %0, i32 0, i32 0, !dbg !1074
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !1075
  %1 = load i32, i32* %avail_in, align 8, !dbg !1075
  store i32 %1, i32* %len, align 4, !dbg !1076
  %2 = load i32, i32* %len, align 4, !dbg !1077
  %cmp = icmp ult i32 %2, 2, !dbg !1079
  br i1 %cmp, label %if.then, label %if.end27, !dbg !1080

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %len, align 4, !dbg !1081
  %tobool = icmp ne i32 %3, 0, !dbg !1081
  br i1 %tobool, label %if.then1, label %if.end, !dbg !1084

if.then1:                                         ; preds = %if.then
  %4 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1085
  %stream2 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %4, i32 0, i32 0, !dbg !1087
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream2, i32 0, i32 0, !dbg !1088
  %5 = load i8*, i8** %next_in, align 8, !dbg !1088
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !1085
  %6 = load i8, i8* %arrayidx, align 1, !dbg !1085
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1089
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 4, !dbg !1090
  %8 = load i8*, i8** %inbuf, align 8, !dbg !1090
  %arrayidx3 = getelementptr inbounds i8, i8* %8, i64 0, !dbg !1089
  store i8 %6, i8* %arrayidx3, align 1, !dbg !1091
  br label %if.end, !dbg !1089

if.end:                                           ; preds = %if.then1, %if.then
  %call = call i32* @__errno_location() #1, !dbg !1092
  store i32 0, i32* %call, align 4, !dbg !1093
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1094
  %inbuf4 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 4, !dbg !1095
  %10 = load i8*, i8** %inbuf4, align 8, !dbg !1095
  %11 = load i32, i32* %len, align 4, !dbg !1096
  %idx.ext = zext i32 %11 to i64, !dbg !1097
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %idx.ext, !dbg !1097
  %12 = load i32, i32* %len, align 4, !dbg !1098
  %shr = ashr i32 16384, %12, !dbg !1099
  %conv = sext i32 %shr to i64, !dbg !1100
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1101
  %file = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 3, !dbg !1102
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !1102
  %call5 = call i64 @fread(i8* %add.ptr, i64 1, i64 %conv, %struct._IO_FILE* %14), !dbg !1103
  %conv6 = trunc i64 %call5 to i32, !dbg !1104
  store i32 %conv6, i32* %len, align 4, !dbg !1105
  %15 = load i32, i32* %len, align 4, !dbg !1106
  %cmp7 = icmp eq i32 %15, 0, !dbg !1108
  br i1 %cmp7, label %land.lhs.true, label %if.end13, !dbg !1109

land.lhs.true:                                    ; preds = %if.end
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1110
  %file9 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 3, !dbg !1112
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** %file9, align 8, !dbg !1112
  %call10 = call i32 @ferror(%struct._IO_FILE* %17) #6, !dbg !1113
  %tobool11 = icmp ne i32 %call10, 0, !dbg !1113
  br i1 %tobool11, label %if.then12, label %if.end13, !dbg !1114

if.then12:                                        ; preds = %land.lhs.true
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1115
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 1, !dbg !1117
  store i32 -1, i32* %z_err, align 8, !dbg !1118
  br label %if.end13, !dbg !1115

if.end13:                                         ; preds = %if.then12, %land.lhs.true, %if.end
  %19 = load i32, i32* %len, align 4, !dbg !1119
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1120
  %stream14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 0, !dbg !1121
  %avail_in15 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream14, i32 0, i32 1, !dbg !1122
  %21 = load i32, i32* %avail_in15, align 8, !dbg !1123
  %add = add i32 %21, %19, !dbg !1123
  store i32 %add, i32* %avail_in15, align 8, !dbg !1123
  %22 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1124
  %inbuf16 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %22, i32 0, i32 4, !dbg !1125
  %23 = load i8*, i8** %inbuf16, align 8, !dbg !1125
  %24 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1126
  %stream17 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %24, i32 0, i32 0, !dbg !1127
  %next_in18 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream17, i32 0, i32 0, !dbg !1128
  store i8* %23, i8** %next_in18, align 8, !dbg !1129
  %25 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1130
  %stream19 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %25, i32 0, i32 0, !dbg !1132
  %avail_in20 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream19, i32 0, i32 1, !dbg !1133
  %26 = load i32, i32* %avail_in20, align 8, !dbg !1133
  %cmp21 = icmp ult i32 %26, 2, !dbg !1134
  br i1 %cmp21, label %if.then23, label %if.end26, !dbg !1135

if.then23:                                        ; preds = %if.end13
  %27 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1136
  %stream24 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %27, i32 0, i32 0, !dbg !1138
  %avail_in25 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream24, i32 0, i32 1, !dbg !1139
  %28 = load i32, i32* %avail_in25, align 8, !dbg !1139
  %29 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1140
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %29, i32 0, i32 9, !dbg !1141
  store i32 %28, i32* %transparent, align 8, !dbg !1142
  br label %return, !dbg !1143

if.end26:                                         ; preds = %if.end13
  br label %if.end27, !dbg !1144

if.end27:                                         ; preds = %if.end26, %entry
  %30 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1145
  %stream28 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %30, i32 0, i32 0, !dbg !1147
  %next_in29 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream28, i32 0, i32 0, !dbg !1148
  %31 = load i8*, i8** %next_in29, align 8, !dbg !1148
  %arrayidx30 = getelementptr inbounds i8, i8* %31, i64 0, !dbg !1145
  %32 = load i8, i8* %arrayidx30, align 1, !dbg !1145
  %conv31 = zext i8 %32 to i32, !dbg !1145
  %33 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @gz_magic, i64 0, i64 0), align 4, !dbg !1149
  %cmp32 = icmp ne i32 %conv31, %33, !dbg !1150
  br i1 %cmp32, label %if.then40, label %lor.lhs.false, !dbg !1151

lor.lhs.false:                                    ; preds = %if.end27
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1152
  %stream34 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %34, i32 0, i32 0, !dbg !1153
  %next_in35 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream34, i32 0, i32 0, !dbg !1154
  %35 = load i8*, i8** %next_in35, align 8, !dbg !1154
  %arrayidx36 = getelementptr inbounds i8, i8* %35, i64 1, !dbg !1152
  %36 = load i8, i8* %arrayidx36, align 1, !dbg !1152
  %conv37 = zext i8 %36 to i32, !dbg !1152
  %37 = load i32, i32* getelementptr inbounds ([2 x i32], [2 x i32]* @gz_magic, i64 0, i64 1), align 4, !dbg !1155
  %cmp38 = icmp ne i32 %conv37, %37, !dbg !1156
  br i1 %cmp38, label %if.then40, label %if.end42, !dbg !1157

if.then40:                                        ; preds = %lor.lhs.false, %if.end27
  %38 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1159
  %transparent41 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %38, i32 0, i32 9, !dbg !1161
  store i32 1, i32* %transparent41, align 8, !dbg !1162
  br label %return, !dbg !1163

if.end42:                                         ; preds = %lor.lhs.false
  %39 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1164
  %stream43 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %39, i32 0, i32 0, !dbg !1165
  %avail_in44 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream43, i32 0, i32 1, !dbg !1166
  %40 = load i32, i32* %avail_in44, align 8, !dbg !1167
  %sub = sub i32 %40, 2, !dbg !1167
  store i32 %sub, i32* %avail_in44, align 8, !dbg !1167
  %41 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1168
  %stream45 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %41, i32 0, i32 0, !dbg !1169
  %next_in46 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream45, i32 0, i32 0, !dbg !1170
  %42 = load i8*, i8** %next_in46, align 8, !dbg !1171
  %add.ptr47 = getelementptr inbounds i8, i8* %42, i64 2, !dbg !1171
  store i8* %add.ptr47, i8** %next_in46, align 8, !dbg !1171
  %43 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1172
  %call48 = call i32 @get_byte(%struct.gz_stream* %43), !dbg !1173
  store i32 %call48, i32* %method, align 4, !dbg !1174
  %44 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1175
  %call49 = call i32 @get_byte(%struct.gz_stream* %44), !dbg !1176
  store i32 %call49, i32* %flags, align 4, !dbg !1177
  %45 = load i32, i32* %method, align 4, !dbg !1178
  %cmp50 = icmp ne i32 %45, 8, !dbg !1180
  br i1 %cmp50, label %if.then55, label %lor.lhs.false52, !dbg !1181

lor.lhs.false52:                                  ; preds = %if.end42
  %46 = load i32, i32* %flags, align 4, !dbg !1182
  %and = and i32 %46, 224, !dbg !1184
  %cmp53 = icmp ne i32 %and, 0, !dbg !1185
  br i1 %cmp53, label %if.then55, label %if.end57, !dbg !1186

if.then55:                                        ; preds = %lor.lhs.false52, %if.end42
  %47 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1187
  %z_err56 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %47, i32 0, i32 1, !dbg !1189
  store i32 -3, i32* %z_err56, align 8, !dbg !1190
  br label %return, !dbg !1191

if.end57:                                         ; preds = %lor.lhs.false52
  store i32 0, i32* %len, align 4, !dbg !1192
  br label %for.cond, !dbg !1194

for.cond:                                         ; preds = %for.inc, %if.end57
  %48 = load i32, i32* %len, align 4, !dbg !1195
  %cmp58 = icmp ult i32 %48, 6, !dbg !1198
  br i1 %cmp58, label %for.body, label %for.end, !dbg !1199

for.body:                                         ; preds = %for.cond
  %49 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1200
  %call60 = call i32 @get_byte(%struct.gz_stream* %49), !dbg !1202
  br label %for.inc, !dbg !1203

for.inc:                                          ; preds = %for.body
  %50 = load i32, i32* %len, align 4, !dbg !1204
  %inc = add i32 %50, 1, !dbg !1204
  store i32 %inc, i32* %len, align 4, !dbg !1204
  br label %for.cond, !dbg !1206

for.end:                                          ; preds = %for.cond
  %51 = load i32, i32* %flags, align 4, !dbg !1207
  %and61 = and i32 %51, 4, !dbg !1209
  %cmp62 = icmp ne i32 %and61, 0, !dbg !1210
  br i1 %cmp62, label %if.then64, label %if.end73, !dbg !1211

if.then64:                                        ; preds = %for.end
  %52 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1212
  %call65 = call i32 @get_byte(%struct.gz_stream* %52), !dbg !1214
  store i32 %call65, i32* %len, align 4, !dbg !1215
  %53 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1216
  %call66 = call i32 @get_byte(%struct.gz_stream* %53), !dbg !1217
  %shl = shl i32 %call66, 8, !dbg !1218
  %54 = load i32, i32* %len, align 4, !dbg !1219
  %add67 = add i32 %54, %shl, !dbg !1219
  store i32 %add67, i32* %len, align 4, !dbg !1219
  br label %while.cond, !dbg !1220

while.cond:                                       ; preds = %while.body, %if.then64
  %55 = load i32, i32* %len, align 4, !dbg !1221
  %dec = add i32 %55, -1, !dbg !1221
  store i32 %dec, i32* %len, align 4, !dbg !1221
  %cmp68 = icmp ne i32 %55, 0, !dbg !1223
  br i1 %cmp68, label %land.rhs, label %land.end, !dbg !1224

land.rhs:                                         ; preds = %while.cond
  %56 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1225
  %call70 = call i32 @get_byte(%struct.gz_stream* %56), !dbg !1227
  %cmp71 = icmp ne i32 %call70, -1, !dbg !1228
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %57 = phi i1 [ false, %while.cond ], [ %cmp71, %land.rhs ]
  br i1 %57, label %while.body, label %while.end, !dbg !1229

while.body:                                       ; preds = %land.end
  br label %while.cond, !dbg !1231

while.end:                                        ; preds = %land.end
  br label %if.end73, !dbg !1233

if.end73:                                         ; preds = %while.end, %for.end
  %58 = load i32, i32* %flags, align 4, !dbg !1234
  %and74 = and i32 %58, 8, !dbg !1236
  %cmp75 = icmp ne i32 %and74, 0, !dbg !1237
  br i1 %cmp75, label %if.then77, label %if.end88, !dbg !1238

if.then77:                                        ; preds = %if.end73
  br label %while.cond78, !dbg !1239

while.cond78:                                     ; preds = %while.body86, %if.then77
  %59 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1241
  %call79 = call i32 @get_byte(%struct.gz_stream* %59), !dbg !1243
  store i32 %call79, i32* %c, align 4, !dbg !1244
  %cmp80 = icmp ne i32 %call79, 0, !dbg !1245
  br i1 %cmp80, label %land.rhs82, label %land.end85, !dbg !1246

land.rhs82:                                       ; preds = %while.cond78
  %60 = load i32, i32* %c, align 4, !dbg !1247
  %cmp83 = icmp ne i32 %60, -1, !dbg !1249
  br label %land.end85

land.end85:                                       ; preds = %land.rhs82, %while.cond78
  %61 = phi i1 [ false, %while.cond78 ], [ %cmp83, %land.rhs82 ]
  br i1 %61, label %while.body86, label %while.end87, !dbg !1250

while.body86:                                     ; preds = %land.end85
  br label %while.cond78, !dbg !1252

while.end87:                                      ; preds = %land.end85
  br label %if.end88, !dbg !1254

if.end88:                                         ; preds = %while.end87, %if.end73
  %62 = load i32, i32* %flags, align 4, !dbg !1255
  %and89 = and i32 %62, 16, !dbg !1257
  %cmp90 = icmp ne i32 %and89, 0, !dbg !1258
  br i1 %cmp90, label %if.then92, label %if.end103, !dbg !1259

if.then92:                                        ; preds = %if.end88
  br label %while.cond93, !dbg !1260

while.cond93:                                     ; preds = %while.body101, %if.then92
  %63 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1262
  %call94 = call i32 @get_byte(%struct.gz_stream* %63), !dbg !1264
  store i32 %call94, i32* %c, align 4, !dbg !1265
  %cmp95 = icmp ne i32 %call94, 0, !dbg !1266
  br i1 %cmp95, label %land.rhs97, label %land.end100, !dbg !1267

land.rhs97:                                       ; preds = %while.cond93
  %64 = load i32, i32* %c, align 4, !dbg !1268
  %cmp98 = icmp ne i32 %64, -1, !dbg !1270
  br label %land.end100

land.end100:                                      ; preds = %land.rhs97, %while.cond93
  %65 = phi i1 [ false, %while.cond93 ], [ %cmp98, %land.rhs97 ]
  br i1 %65, label %while.body101, label %while.end102, !dbg !1271

while.body101:                                    ; preds = %land.end100
  br label %while.cond93, !dbg !1273

while.end102:                                     ; preds = %land.end100
  br label %if.end103, !dbg !1275

if.end103:                                        ; preds = %while.end102, %if.end88
  %66 = load i32, i32* %flags, align 4, !dbg !1276
  %and104 = and i32 %66, 2, !dbg !1278
  %cmp105 = icmp ne i32 %and104, 0, !dbg !1279
  br i1 %cmp105, label %if.then107, label %if.end116, !dbg !1280

if.then107:                                       ; preds = %if.end103
  store i32 0, i32* %len, align 4, !dbg !1281
  br label %for.cond108, !dbg !1284

for.cond108:                                      ; preds = %for.inc113, %if.then107
  %67 = load i32, i32* %len, align 4, !dbg !1285
  %cmp109 = icmp ult i32 %67, 2, !dbg !1288
  br i1 %cmp109, label %for.body111, label %for.end115, !dbg !1289

for.body111:                                      ; preds = %for.cond108
  %68 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1290
  %call112 = call i32 @get_byte(%struct.gz_stream* %68), !dbg !1292
  br label %for.inc113, !dbg !1293

for.inc113:                                       ; preds = %for.body111
  %69 = load i32, i32* %len, align 4, !dbg !1294
  %inc114 = add i32 %69, 1, !dbg !1294
  store i32 %inc114, i32* %len, align 4, !dbg !1294
  br label %for.cond108, !dbg !1296

for.end115:                                       ; preds = %for.cond108
  br label %if.end116, !dbg !1297

if.end116:                                        ; preds = %for.end115, %if.end103
  %70 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1298
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %70, i32 0, i32 2, !dbg !1299
  %71 = load i32, i32* %z_eof, align 4, !dbg !1299
  %tobool117 = icmp ne i32 %71, 0, !dbg !1298
  %cond = select i1 %tobool117, i32 -3, i32 0, !dbg !1298
  %72 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !1300
  %z_err118 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %72, i32 0, i32 1, !dbg !1301
  store i32 %cond, i32* %z_err118, align 8, !dbg !1302
  br label %return, !dbg !1303

return:                                           ; preds = %if.end116, %if.then55, %if.then40, %if.then23
  ret void, !dbg !1304
}

declare i32 @cm_zlib_inflateReset(%struct.z_stream_s*) #3

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzgetc(i8* %file) #0 !dbg !146 {
entry:
  %file.addr = alloca i8*, align 8
  %c = alloca i8, align 1
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1305, metadata !215), !dbg !1306
  call void @llvm.dbg.declare(metadata i8* %c, metadata !1307, metadata !215), !dbg !1308
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1309
  %call = call i32 @cm_zlib_gzread(i8* %0, i8* %c, i32 1), !dbg !1310
  %cmp = icmp eq i32 %call, 1, !dbg !1311
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1310

cond.true:                                        ; preds = %entry
  %1 = load i8, i8* %c, align 1, !dbg !1312
  %conv = zext i8 %1 to i32, !dbg !1312
  br label %cond.end, !dbg !1314

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1315

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %conv, %cond.true ], [ -1, %cond.false ], !dbg !1317
  ret i32 %cond, !dbg !1319
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzungetc(i32 %c, i8* %file) #0 !dbg !149 {
entry:
  %retval = alloca i32, align 4
  %c.addr = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !1320, metadata !215), !dbg !1321
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1322, metadata !215), !dbg !1323
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !1324, metadata !215), !dbg !1325
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1326
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !1327
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !1325
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1328
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !1330
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1331

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1332
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !1334
  %4 = load i8, i8* %mode, align 4, !dbg !1334
  %conv = sext i8 %4 to i32, !dbg !1332
  %cmp1 = icmp ne i32 %conv, 114, !dbg !1335
  br i1 %cmp1, label %if.then, label %lor.lhs.false3, !dbg !1336

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %5 = load i32, i32* %c.addr, align 4, !dbg !1337
  %cmp4 = icmp eq i32 %5, -1, !dbg !1339
  br i1 %cmp4, label %if.then, label %lor.lhs.false6, !dbg !1340

lor.lhs.false6:                                   ; preds = %lor.lhs.false3
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1341
  %back = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 14, !dbg !1343
  %7 = load i32, i32* %back, align 8, !dbg !1343
  %cmp7 = icmp ne i32 %7, -1, !dbg !1344
  br i1 %cmp7, label %if.then, label %if.end, !dbg !1345

if.then:                                          ; preds = %lor.lhs.false6, %lor.lhs.false3, %lor.lhs.false, %entry
  store i32 -1, i32* %retval, align 4, !dbg !1346
  br label %return, !dbg !1346

if.end:                                           ; preds = %lor.lhs.false6
  %8 = load i32, i32* %c.addr, align 4, !dbg !1348
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1349
  %back9 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 14, !dbg !1350
  store i32 %8, i32* %back9, align 8, !dbg !1351
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1352
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 13, !dbg !1353
  %11 = load i64, i64* %out, align 8, !dbg !1354
  %dec = add nsw i64 %11, -1, !dbg !1354
  store i64 %dec, i64* %out, align 8, !dbg !1354
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1355
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 1, !dbg !1356
  %13 = load i32, i32* %z_err, align 8, !dbg !1356
  %cmp10 = icmp eq i32 %13, 1, !dbg !1357
  %conv11 = zext i1 %cmp10 to i32, !dbg !1357
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1358
  %last = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 15, !dbg !1359
  store i32 %conv11, i32* %last, align 4, !dbg !1360
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1361
  %last12 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 15, !dbg !1363
  %16 = load i32, i32* %last12, align 4, !dbg !1363
  %tobool = icmp ne i32 %16, 0, !dbg !1361
  br i1 %tobool, label %if.then13, label %if.end15, !dbg !1364

if.then13:                                        ; preds = %if.end
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1365
  %z_err14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 1, !dbg !1367
  store i32 0, i32* %z_err14, align 8, !dbg !1368
  br label %if.end15, !dbg !1365

if.end15:                                         ; preds = %if.then13, %if.end
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1369
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 2, !dbg !1370
  store i32 0, i32* %z_eof, align 4, !dbg !1371
  %19 = load i32, i32* %c.addr, align 4, !dbg !1372
  store i32 %19, i32* %retval, align 4, !dbg !1373
  br label %return, !dbg !1373

return:                                           ; preds = %if.end15, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !1374
  ret i32 %20, !dbg !1374
}

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_gzgets(i8* %file, i8* %buf, i32 %len) #0 !dbg !152 {
entry:
  %retval = alloca i8*, align 8
  %file.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %b = alloca i8*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1375, metadata !215), !dbg !1376
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1377, metadata !215), !dbg !1378
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !1379, metadata !215), !dbg !1380
  call void @llvm.dbg.declare(metadata i8** %b, metadata !1381, metadata !215), !dbg !1382
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1383
  store i8* %0, i8** %b, align 8, !dbg !1382
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !1384
  %cmp = icmp eq i8* %1, null, !dbg !1386
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1387

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32, i32* %len.addr, align 4, !dbg !1388
  %cmp1 = icmp sle i32 %2, 0, !dbg !1390
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1391

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i8* null, i8** %retval, align 8, !dbg !1392
  br label %return, !dbg !1392

if.end:                                           ; preds = %lor.lhs.false
  br label %while.cond, !dbg !1394

while.cond:                                       ; preds = %while.body, %if.end
  %3 = load i32, i32* %len.addr, align 4, !dbg !1395
  %dec = add nsw i32 %3, -1, !dbg !1395
  store i32 %dec, i32* %len.addr, align 4, !dbg !1395
  %cmp2 = icmp sgt i32 %dec, 0, !dbg !1397
  br i1 %cmp2, label %land.lhs.true, label %land.end, !dbg !1398

land.lhs.true:                                    ; preds = %while.cond
  %4 = load i8*, i8** %file.addr, align 8, !dbg !1399
  %5 = load i8*, i8** %buf.addr, align 8, !dbg !1401
  %call = call i32 @cm_zlib_gzread(i8* %4, i8* %5, i32 1), !dbg !1402
  %cmp3 = icmp eq i32 %call, 1, !dbg !1403
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !1404

land.rhs:                                         ; preds = %land.lhs.true
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !1405
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !1405
  store i8* %incdec.ptr, i8** %buf.addr, align 8, !dbg !1405
  %7 = load i8, i8* %6, align 1, !dbg !1407
  %conv = sext i8 %7 to i32, !dbg !1407
  %cmp4 = icmp ne i32 %conv, 10, !dbg !1408
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %while.cond
  %8 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond ], [ %cmp4, %land.rhs ]
  br i1 %8, label %while.body, label %while.end, !dbg !1409

while.body:                                       ; preds = %land.end
  br label %while.cond, !dbg !1411

while.end:                                        ; preds = %land.end
  %9 = load i8*, i8** %buf.addr, align 8, !dbg !1413
  store i8 0, i8* %9, align 1, !dbg !1414
  %10 = load i8*, i8** %b, align 8, !dbg !1415
  %11 = load i8*, i8** %buf.addr, align 8, !dbg !1416
  %cmp6 = icmp eq i8* %10, %11, !dbg !1417
  br i1 %cmp6, label %land.lhs.true8, label %cond.false, !dbg !1418

land.lhs.true8:                                   ; preds = %while.end
  %12 = load i32, i32* %len.addr, align 4, !dbg !1419
  %cmp9 = icmp sgt i32 %12, 0, !dbg !1420
  br i1 %cmp9, label %cond.true, label %cond.false, !dbg !1421

cond.true:                                        ; preds = %land.lhs.true8
  br label %cond.end, !dbg !1422

cond.false:                                       ; preds = %land.lhs.true8, %while.end
  %13 = load i8*, i8** %b, align 8, !dbg !1423
  br label %cond.end, !dbg !1424

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ null, %cond.true ], [ %13, %cond.false ], !dbg !1425
  store i8* %cond, i8** %retval, align 8, !dbg !1426
  br label %return, !dbg !1426

return:                                           ; preds = %cond.end, %if.then
  %14 = load i8*, i8** %retval, align 8, !dbg !1427
  ret i8* %14, !dbg !1427
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzwrite(i8* %file, i8* %buf, i32 %len) #0 !dbg !155 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1428, metadata !215), !dbg !1429
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1430, metadata !215), !dbg !1431
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !1432, metadata !215), !dbg !1433
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !1434, metadata !215), !dbg !1435
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1436
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !1437
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !1435
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1438
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !1440
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1441

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1442
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !1444
  %4 = load i8, i8* %mode, align 4, !dbg !1444
  %conv = sext i8 %4 to i32, !dbg !1442
  %cmp1 = icmp ne i32 %conv, 119, !dbg !1445
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1446

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !1447
  br label %return, !dbg !1447

if.end:                                           ; preds = %lor.lhs.false
  %5 = load i8*, i8** %buf.addr, align 8, !dbg !1449
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1450
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 0, !dbg !1451
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 0, !dbg !1452
  store i8* %5, i8** %next_in, align 8, !dbg !1453
  %7 = load i32, i32* %len.addr, align 4, !dbg !1454
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1455
  %stream3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 0, !dbg !1456
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream3, i32 0, i32 1, !dbg !1457
  store i32 %7, i32* %avail_in, align 8, !dbg !1458
  br label %while.cond, !dbg !1459

while.cond:                                       ; preds = %if.end45, %if.end
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1460
  %stream4 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 0, !dbg !1462
  %avail_in5 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream4, i32 0, i32 1, !dbg !1463
  %10 = load i32, i32* %avail_in5, align 8, !dbg !1463
  %cmp6 = icmp ne i32 %10, 0, !dbg !1464
  br i1 %cmp6, label %while.body, label %while.end, !dbg !1465

while.body:                                       ; preds = %while.cond
  %11 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1466
  %stream8 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %11, i32 0, i32 0, !dbg !1469
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream8, i32 0, i32 4, !dbg !1470
  %12 = load i32, i32* %avail_out, align 8, !dbg !1470
  %cmp9 = icmp eq i32 %12, 0, !dbg !1471
  br i1 %cmp9, label %if.then11, label %if.end21, !dbg !1472

if.then11:                                        ; preds = %while.body
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1473
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 5, !dbg !1475
  %14 = load i8*, i8** %outbuf, align 8, !dbg !1475
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1476
  %stream12 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 0, !dbg !1477
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream12, i32 0, i32 3, !dbg !1478
  store i8* %14, i8** %next_out, align 8, !dbg !1479
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1480
  %outbuf13 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 5, !dbg !1482
  %17 = load i8*, i8** %outbuf13, align 8, !dbg !1482
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1483
  %file14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 3, !dbg !1484
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %file14, align 8, !dbg !1484
  %call = call i64 @fwrite(i8* %17, i64 1, i64 16384, %struct._IO_FILE* %19), !dbg !1485
  %cmp15 = icmp ne i64 %call, 16384, !dbg !1486
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !1487

if.then17:                                        ; preds = %if.then11
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1488
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 1, !dbg !1490
  store i32 -1, i32* %z_err, align 8, !dbg !1491
  br label %while.end, !dbg !1492

if.end18:                                         ; preds = %if.then11
  %21 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1493
  %stream19 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %21, i32 0, i32 0, !dbg !1494
  %avail_out20 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream19, i32 0, i32 4, !dbg !1495
  store i32 16384, i32* %avail_out20, align 8, !dbg !1496
  br label %if.end21, !dbg !1497

if.end21:                                         ; preds = %if.end18, %while.body
  %22 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1498
  %stream22 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %22, i32 0, i32 0, !dbg !1499
  %avail_in23 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream22, i32 0, i32 1, !dbg !1500
  %23 = load i32, i32* %avail_in23, align 8, !dbg !1500
  %conv24 = zext i32 %23 to i64, !dbg !1498
  %24 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1501
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %24, i32 0, i32 12, !dbg !1502
  %25 = load i64, i64* %in, align 8, !dbg !1503
  %add = add nsw i64 %25, %conv24, !dbg !1503
  store i64 %add, i64* %in, align 8, !dbg !1503
  %26 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1504
  %stream25 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %26, i32 0, i32 0, !dbg !1505
  %avail_out26 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream25, i32 0, i32 4, !dbg !1506
  %27 = load i32, i32* %avail_out26, align 8, !dbg !1506
  %conv27 = zext i32 %27 to i64, !dbg !1504
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1507
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 13, !dbg !1508
  %29 = load i64, i64* %out, align 8, !dbg !1509
  %add28 = add nsw i64 %29, %conv27, !dbg !1509
  store i64 %add28, i64* %out, align 8, !dbg !1509
  %30 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1510
  %stream29 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %30, i32 0, i32 0, !dbg !1511
  %call30 = call i32 @cm_zlib_deflate(%struct.z_stream_s* %stream29, i32 0), !dbg !1512
  %31 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1513
  %z_err31 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %31, i32 0, i32 1, !dbg !1514
  store i32 %call30, i32* %z_err31, align 8, !dbg !1515
  %32 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1516
  %stream32 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %32, i32 0, i32 0, !dbg !1517
  %avail_in33 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream32, i32 0, i32 1, !dbg !1518
  %33 = load i32, i32* %avail_in33, align 8, !dbg !1518
  %conv34 = zext i32 %33 to i64, !dbg !1516
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1519
  %in35 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %34, i32 0, i32 12, !dbg !1520
  %35 = load i64, i64* %in35, align 8, !dbg !1521
  %sub = sub nsw i64 %35, %conv34, !dbg !1521
  store i64 %sub, i64* %in35, align 8, !dbg !1521
  %36 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1522
  %stream36 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %36, i32 0, i32 0, !dbg !1523
  %avail_out37 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream36, i32 0, i32 4, !dbg !1524
  %37 = load i32, i32* %avail_out37, align 8, !dbg !1524
  %conv38 = zext i32 %37 to i64, !dbg !1522
  %38 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1525
  %out39 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %38, i32 0, i32 13, !dbg !1526
  %39 = load i64, i64* %out39, align 8, !dbg !1527
  %sub40 = sub nsw i64 %39, %conv38, !dbg !1527
  store i64 %sub40, i64* %out39, align 8, !dbg !1527
  %40 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1528
  %z_err41 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %40, i32 0, i32 1, !dbg !1530
  %41 = load i32, i32* %z_err41, align 8, !dbg !1530
  %cmp42 = icmp ne i32 %41, 0, !dbg !1531
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !1532

if.then44:                                        ; preds = %if.end21
  br label %while.end, !dbg !1533

if.end45:                                         ; preds = %if.end21
  br label %while.cond, !dbg !1535

while.end:                                        ; preds = %if.then44, %if.then17, %while.cond
  %42 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1537
  %crc = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %42, i32 0, i32 6, !dbg !1538
  %43 = load i64, i64* %crc, align 8, !dbg !1538
  %44 = load i8*, i8** %buf.addr, align 8, !dbg !1539
  %45 = load i32, i32* %len.addr, align 4, !dbg !1540
  %call46 = call i64 @cm_zlib_crc32(i64 %43, i8* %44, i32 %45), !dbg !1541
  %46 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1542
  %crc47 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %46, i32 0, i32 6, !dbg !1543
  store i64 %call46, i64* %crc47, align 8, !dbg !1544
  %47 = load i32, i32* %len.addr, align 4, !dbg !1545
  %48 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1546
  %stream48 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %48, i32 0, i32 0, !dbg !1547
  %avail_in49 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream48, i32 0, i32 1, !dbg !1548
  %49 = load i32, i32* %avail_in49, align 8, !dbg !1548
  %sub50 = sub i32 %47, %49, !dbg !1549
  store i32 %sub50, i32* %retval, align 4, !dbg !1550
  br label %return, !dbg !1550

return:                                           ; preds = %while.end, %if.then
  %50 = load i32, i32* %retval, align 4, !dbg !1551
  ret i32 %50, !dbg !1551
}

declare i32 @cm_zlib_deflate(%struct.z_stream_s*, i32) #3

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzprintf(i8* %file, i8* %format, ...) #0 !dbg !161 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %format.addr = alloca i8*, align 8
  %buf = alloca [4096 x i8], align 16
  %va = alloca [1 x %struct.__va_list_tag], align 16
  %len = alloca i32, align 4
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1552, metadata !215), !dbg !1553
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1554, metadata !215), !dbg !1555
  call void @llvm.dbg.declare(metadata [4096 x i8]* %buf, metadata !1556, metadata !215), !dbg !1560
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %va, metadata !1561, metadata !215), !dbg !1573
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1574, metadata !215), !dbg !1575
  %arrayidx = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i64 0, i64 4095, !dbg !1576
  store i8 0, i8* %arrayidx, align 1, !dbg !1577
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %va, i32 0, i32 0, !dbg !1578
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1578
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1578
  %arraydecay2 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i32 0, i32 0, !dbg !1579
  %0 = load i8*, i8** %format.addr, align 8, !dbg !1580
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %va, i32 0, i32 0, !dbg !1581
  %call = call i32 @vsnprintf(i8* %arraydecay2, i64 4096, i8* %0, %struct.__va_list_tag* %arraydecay3) #6, !dbg !1582
  store i32 %call, i32* %len, align 4, !dbg !1583
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %va, i32 0, i32 0, !dbg !1584
  %arraydecay45 = bitcast %struct.__va_list_tag* %arraydecay4 to i8*, !dbg !1584
  call void @llvm.va_end(i8* %arraydecay45), !dbg !1584
  %1 = load i32, i32* %len, align 4, !dbg !1585
  %cmp = icmp sle i32 %1, 0, !dbg !1587
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1588

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32, i32* %len, align 4, !dbg !1589
  %cmp6 = icmp sge i32 %2, 4096, !dbg !1591
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !1592

lor.lhs.false7:                                   ; preds = %lor.lhs.false
  %arrayidx8 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i64 0, i64 4095, !dbg !1593
  %3 = load i8, i8* %arrayidx8, align 1, !dbg !1593
  %conv = sext i8 %3 to i32, !dbg !1593
  %cmp9 = icmp ne i32 %conv, 0, !dbg !1595
  br i1 %cmp9, label %if.then, label %if.end, !dbg !1596

if.then:                                          ; preds = %lor.lhs.false7, %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !1597
  br label %return, !dbg !1597

if.end:                                           ; preds = %lor.lhs.false7
  %4 = load i8*, i8** %file.addr, align 8, !dbg !1598
  %arraydecay11 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i32 0, i32 0, !dbg !1599
  %5 = load i32, i32* %len, align 4, !dbg !1600
  %call12 = call i32 @cm_zlib_gzwrite(i8* %4, i8* %arraydecay11, i32 %5), !dbg !1601
  store i32 %call12, i32* %retval, align 4, !dbg !1602
  br label %return, !dbg !1602

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1603
  ret i32 %6, !dbg !1603
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #6

; Function Attrs: nounwind
declare i32 @vsnprintf(i8*, i64, i8*, %struct.__va_list_tag*) #2

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #6

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzputc(i8* %file, i32 %c) #0 !dbg !164 {
entry:
  %file.addr = alloca i8*, align 8
  %c.addr = alloca i32, align 4
  %cc = alloca i8, align 1
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1604, metadata !215), !dbg !1605
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !1606, metadata !215), !dbg !1607
  call void @llvm.dbg.declare(metadata i8* %cc, metadata !1608, metadata !215), !dbg !1609
  %0 = load i32, i32* %c.addr, align 4, !dbg !1610
  %conv = trunc i32 %0 to i8, !dbg !1611
  store i8 %conv, i8* %cc, align 1, !dbg !1609
  %1 = load i8*, i8** %file.addr, align 8, !dbg !1612
  %call = call i32 @cm_zlib_gzwrite(i8* %1, i8* %cc, i32 1), !dbg !1613
  %cmp = icmp eq i32 %call, 1, !dbg !1614
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1613

cond.true:                                        ; preds = %entry
  %2 = load i8, i8* %cc, align 1, !dbg !1615
  %conv2 = zext i8 %2 to i32, !dbg !1617
  br label %cond.end, !dbg !1618

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1619

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %conv2, %cond.true ], [ -1, %cond.false ], !dbg !1621
  ret i32 %cond, !dbg !1623
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzputs(i8* %file, i8* %s) #0 !dbg !167 {
entry:
  %file.addr = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1624, metadata !215), !dbg !1625
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !1626, metadata !215), !dbg !1627
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1628
  %1 = load i8*, i8** %s.addr, align 8, !dbg !1629
  %2 = load i8*, i8** %s.addr, align 8, !dbg !1630
  %call = call i64 @strlen(i8* %2) #8, !dbg !1631
  %conv = trunc i64 %call to i32, !dbg !1632
  %call1 = call i32 @cm_zlib_gzwrite(i8* %0, i8* %1, i32 %conv), !dbg !1633
  ret i32 %call1, !dbg !1635
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #7

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzflush(i8* %file, i32 %flush) #0 !dbg !170 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %flush.addr = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  %err = alloca i32, align 4
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1636, metadata !215), !dbg !1637
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !1638, metadata !215), !dbg !1639
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !1640, metadata !215), !dbg !1641
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1642
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !1643
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !1641
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1644, metadata !215), !dbg !1645
  %2 = load i8*, i8** %file.addr, align 8, !dbg !1646
  %3 = load i32, i32* %flush.addr, align 4, !dbg !1647
  %call = call i32 @do_flush(i8* %2, i32 %3), !dbg !1648
  store i32 %call, i32* %err, align 4, !dbg !1645
  %4 = load i32, i32* %err, align 4, !dbg !1649
  %tobool = icmp ne i32 %4, 0, !dbg !1649
  br i1 %tobool, label %if.then, label %if.end, !dbg !1651

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %err, align 4, !dbg !1652
  store i32 %5, i32* %retval, align 4, !dbg !1654
  br label %return, !dbg !1654

if.end:                                           ; preds = %entry
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1655
  %file1 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 3, !dbg !1656
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %file1, align 8, !dbg !1656
  %call2 = call i32 @fflush(%struct._IO_FILE* %7), !dbg !1657
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1658
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 1, !dbg !1659
  %9 = load i32, i32* %z_err, align 8, !dbg !1659
  %cmp = icmp eq i32 %9, 1, !dbg !1660
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1658

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !1661

cond.false:                                       ; preds = %if.end
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1663
  %z_err3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 1, !dbg !1665
  %11 = load i32, i32* %z_err3, align 8, !dbg !1665
  br label %cond.end, !dbg !1666

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 0, %cond.true ], [ %11, %cond.false ], !dbg !1667
  store i32 %cond, i32* %retval, align 4, !dbg !1669
  br label %return, !dbg !1669

return:                                           ; preds = %cond.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1670
  ret i32 %12, !dbg !1670
}

; Function Attrs: nounwind uwtable
define internal i32 @do_flush(i8* %file, i32 %flush) #0 !dbg !197 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %flush.addr = alloca i32, align 4
  %len = alloca i32, align 4
  %done = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1671, metadata !215), !dbg !1672
  store i32 %flush, i32* %flush.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flush.addr, metadata !1673, metadata !215), !dbg !1674
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1675, metadata !215), !dbg !1676
  call void @llvm.dbg.declare(metadata i32* %done, metadata !1677, metadata !215), !dbg !1678
  store i32 0, i32* %done, align 4, !dbg !1678
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !1679, metadata !215), !dbg !1680
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1681
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !1682
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !1680
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1683
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !1685
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1686

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1687
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !1689
  %4 = load i8, i8* %mode, align 4, !dbg !1689
  %conv = sext i8 %4 to i32, !dbg !1687
  %cmp1 = icmp ne i32 %conv, 119, !dbg !1690
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1691

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !1692
  br label %return, !dbg !1692

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1694
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 0, !dbg !1695
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !1696
  store i32 0, i32* %avail_in, align 8, !dbg !1697
  br label %for.cond, !dbg !1698

for.cond:                                         ; preds = %if.end55, %if.end
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1699
  %stream3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 0, !dbg !1703
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream3, i32 0, i32 4, !dbg !1704
  %7 = load i32, i32* %avail_out, align 8, !dbg !1704
  %sub = sub i32 16384, %7, !dbg !1705
  store i32 %sub, i32* %len, align 4, !dbg !1706
  %8 = load i32, i32* %len, align 4, !dbg !1707
  %cmp4 = icmp ne i32 %8, 0, !dbg !1709
  br i1 %cmp4, label %if.then6, label %if.end18, !dbg !1710

if.then6:                                         ; preds = %for.cond
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1711
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 5, !dbg !1714
  %10 = load i8*, i8** %outbuf, align 8, !dbg !1714
  %11 = load i32, i32* %len, align 4, !dbg !1715
  %conv7 = zext i32 %11 to i64, !dbg !1715
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1716
  %file8 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 3, !dbg !1717
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %file8, align 8, !dbg !1717
  %call = call i64 @fwrite(i8* %10, i64 1, i64 %conv7, %struct._IO_FILE* %13), !dbg !1718
  %conv9 = trunc i64 %call to i32, !dbg !1719
  %14 = load i32, i32* %len, align 4, !dbg !1720
  %cmp10 = icmp ne i32 %conv9, %14, !dbg !1721
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !1722

if.then12:                                        ; preds = %if.then6
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1723
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 1, !dbg !1725
  store i32 -1, i32* %z_err, align 8, !dbg !1726
  store i32 -1, i32* %retval, align 4, !dbg !1727
  br label %return, !dbg !1727

if.end13:                                         ; preds = %if.then6
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1728
  %outbuf14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 5, !dbg !1729
  %17 = load i8*, i8** %outbuf14, align 8, !dbg !1729
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1730
  %stream15 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 0, !dbg !1731
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream15, i32 0, i32 3, !dbg !1732
  store i8* %17, i8** %next_out, align 8, !dbg !1733
  %19 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1734
  %stream16 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %19, i32 0, i32 0, !dbg !1735
  %avail_out17 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream16, i32 0, i32 4, !dbg !1736
  store i32 16384, i32* %avail_out17, align 8, !dbg !1737
  br label %if.end18, !dbg !1738

if.end18:                                         ; preds = %if.end13, %for.cond
  %20 = load i32, i32* %done, align 4, !dbg !1739
  %tobool = icmp ne i32 %20, 0, !dbg !1739
  br i1 %tobool, label %if.then19, label %if.end20, !dbg !1741

if.then19:                                        ; preds = %if.end18
  br label %for.end, !dbg !1742

if.end20:                                         ; preds = %if.end18
  %21 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1744
  %stream21 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %21, i32 0, i32 0, !dbg !1745
  %avail_out22 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream21, i32 0, i32 4, !dbg !1746
  %22 = load i32, i32* %avail_out22, align 8, !dbg !1746
  %conv23 = zext i32 %22 to i64, !dbg !1744
  %23 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1747
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %23, i32 0, i32 13, !dbg !1748
  %24 = load i64, i64* %out, align 8, !dbg !1749
  %add = add nsw i64 %24, %conv23, !dbg !1749
  store i64 %add, i64* %out, align 8, !dbg !1749
  %25 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1750
  %stream24 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %25, i32 0, i32 0, !dbg !1751
  %26 = load i32, i32* %flush.addr, align 4, !dbg !1752
  %call25 = call i32 @cm_zlib_deflate(%struct.z_stream_s* %stream24, i32 %26), !dbg !1753
  %27 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1754
  %z_err26 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %27, i32 0, i32 1, !dbg !1755
  store i32 %call25, i32* %z_err26, align 8, !dbg !1756
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1757
  %stream27 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 0, !dbg !1758
  %avail_out28 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream27, i32 0, i32 4, !dbg !1759
  %29 = load i32, i32* %avail_out28, align 8, !dbg !1759
  %conv29 = zext i32 %29 to i64, !dbg !1757
  %30 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1760
  %out30 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %30, i32 0, i32 13, !dbg !1761
  %31 = load i64, i64* %out30, align 8, !dbg !1762
  %sub31 = sub nsw i64 %31, %conv29, !dbg !1762
  store i64 %sub31, i64* %out30, align 8, !dbg !1762
  %32 = load i32, i32* %len, align 4, !dbg !1763
  %cmp32 = icmp eq i32 %32, 0, !dbg !1765
  br i1 %cmp32, label %land.lhs.true, label %if.end39, !dbg !1766

land.lhs.true:                                    ; preds = %if.end20
  %33 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1767
  %z_err34 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %33, i32 0, i32 1, !dbg !1769
  %34 = load i32, i32* %z_err34, align 8, !dbg !1769
  %cmp35 = icmp eq i32 %34, -5, !dbg !1770
  br i1 %cmp35, label %if.then37, label %if.end39, !dbg !1771

if.then37:                                        ; preds = %land.lhs.true
  %35 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1772
  %z_err38 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %35, i32 0, i32 1, !dbg !1774
  store i32 0, i32* %z_err38, align 8, !dbg !1775
  br label %if.end39, !dbg !1772

if.end39:                                         ; preds = %if.then37, %land.lhs.true, %if.end20
  %36 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1776
  %stream40 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %36, i32 0, i32 0, !dbg !1777
  %avail_out41 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream40, i32 0, i32 4, !dbg !1778
  %37 = load i32, i32* %avail_out41, align 8, !dbg !1778
  %cmp42 = icmp ne i32 %37, 0, !dbg !1779
  br i1 %cmp42, label %lor.end, label %lor.rhs, !dbg !1780

lor.rhs:                                          ; preds = %if.end39
  %38 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1781
  %z_err44 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %38, i32 0, i32 1, !dbg !1783
  %39 = load i32, i32* %z_err44, align 8, !dbg !1783
  %cmp45 = icmp eq i32 %39, 1, !dbg !1784
  br label %lor.end, !dbg !1785

lor.end:                                          ; preds = %lor.rhs, %if.end39
  %40 = phi i1 [ true, %if.end39 ], [ %cmp45, %lor.rhs ]
  %lor.ext = zext i1 %40 to i32, !dbg !1786
  store i32 %lor.ext, i32* %done, align 4, !dbg !1788
  %41 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1789
  %z_err47 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %41, i32 0, i32 1, !dbg !1791
  %42 = load i32, i32* %z_err47, align 8, !dbg !1791
  %cmp48 = icmp ne i32 %42, 0, !dbg !1792
  br i1 %cmp48, label %land.lhs.true50, label %if.end55, !dbg !1793

land.lhs.true50:                                  ; preds = %lor.end
  %43 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1794
  %z_err51 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %43, i32 0, i32 1, !dbg !1796
  %44 = load i32, i32* %z_err51, align 8, !dbg !1796
  %cmp52 = icmp ne i32 %44, 1, !dbg !1797
  br i1 %cmp52, label %if.then54, label %if.end55, !dbg !1798

if.then54:                                        ; preds = %land.lhs.true50
  br label %for.end, !dbg !1799

if.end55:                                         ; preds = %land.lhs.true50, %lor.end
  br label %for.cond, !dbg !1801

for.end:                                          ; preds = %if.then54, %if.then19
  %45 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1803
  %z_err56 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %45, i32 0, i32 1, !dbg !1804
  %46 = load i32, i32* %z_err56, align 8, !dbg !1804
  %cmp57 = icmp eq i32 %46, 1, !dbg !1805
  br i1 %cmp57, label %cond.true, label %cond.false, !dbg !1803

cond.true:                                        ; preds = %for.end
  br label %cond.end, !dbg !1806

cond.false:                                       ; preds = %for.end
  %47 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1808
  %z_err59 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %47, i32 0, i32 1, !dbg !1810
  %48 = load i32, i32* %z_err59, align 8, !dbg !1810
  br label %cond.end, !dbg !1811

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 0, %cond.true ], [ %48, %cond.false ], !dbg !1812
  store i32 %cond, i32* %retval, align 4, !dbg !1814
  br label %return, !dbg !1814

return:                                           ; preds = %cond.end, %if.then12, %if.then
  %49 = load i32, i32* %retval, align 4, !dbg !1815
  ret i32 %49, !dbg !1815
}

declare i32 @fflush(%struct._IO_FILE*) #3

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_gzseek(i8* %file, i64 %offset, i32 %whence) #0 !dbg !171 {
entry:
  %retval = alloca i64, align 8
  %file.addr = alloca i8*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %s = alloca %struct.gz_stream*, align 8
  %size = alloca i32, align 4
  %size108 = alloca i32, align 4
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !1816, metadata !215), !dbg !1817
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !1818, metadata !215), !dbg !1819
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !1820, metadata !215), !dbg !1821
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !1822, metadata !215), !dbg !1823
  %0 = load i8*, i8** %file.addr, align 8, !dbg !1824
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !1825
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !1823
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1826
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !1828
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1829

lor.lhs.false:                                    ; preds = %entry
  %3 = load i32, i32* %whence.addr, align 4, !dbg !1830
  %cmp1 = icmp eq i32 %3, 2, !dbg !1832
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1833

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %4 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1834
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %4, i32 0, i32 1, !dbg !1835
  %5 = load i32, i32* %z_err, align 8, !dbg !1835
  %cmp3 = icmp eq i32 %5, -1, !dbg !1836
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !1837

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1838
  %z_err5 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 1, !dbg !1839
  %7 = load i32, i32* %z_err5, align 8, !dbg !1839
  %cmp6 = icmp eq i32 %7, -3, !dbg !1840
  br i1 %cmp6, label %if.then, label %if.end, !dbg !1841

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i64 -1, i64* %retval, align 8, !dbg !1843
  br label %return, !dbg !1843

if.end:                                           ; preds = %lor.lhs.false4
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1845
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 10, !dbg !1847
  %9 = load i8, i8* %mode, align 4, !dbg !1847
  %conv = sext i8 %9 to i32, !dbg !1845
  %cmp7 = icmp eq i32 %conv, 119, !dbg !1848
  br i1 %cmp7, label %if.then9, label %if.end45, !dbg !1849

if.then9:                                         ; preds = %if.end
  %10 = load i32, i32* %whence.addr, align 4, !dbg !1850
  %cmp10 = icmp eq i32 %10, 0, !dbg !1853
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !1854

if.then12:                                        ; preds = %if.then9
  %11 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1855
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %11, i32 0, i32 12, !dbg !1857
  %12 = load i64, i64* %in, align 8, !dbg !1857
  %13 = load i64, i64* %offset.addr, align 8, !dbg !1858
  %sub = sub nsw i64 %13, %12, !dbg !1858
  store i64 %sub, i64* %offset.addr, align 8, !dbg !1858
  br label %if.end13, !dbg !1859

if.end13:                                         ; preds = %if.then12, %if.then9
  %14 = load i64, i64* %offset.addr, align 8, !dbg !1860
  %cmp14 = icmp slt i64 %14, 0, !dbg !1862
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !1863

if.then16:                                        ; preds = %if.end13
  store i64 -1, i64* %retval, align 8, !dbg !1864
  br label %return, !dbg !1864

if.end17:                                         ; preds = %if.end13
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1866
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 4, !dbg !1868
  %16 = load i8*, i8** %inbuf, align 8, !dbg !1868
  %cmp18 = icmp eq i8* %16, null, !dbg !1869
  br i1 %cmp18, label %if.then20, label %if.end28, !dbg !1870

if.then20:                                        ; preds = %if.end17
  %call = call noalias i8* @malloc(i64 16384) #6, !dbg !1871
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1873
  %inbuf21 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 4, !dbg !1874
  store i8* %call, i8** %inbuf21, align 8, !dbg !1875
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1876
  %inbuf22 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 4, !dbg !1878
  %19 = load i8*, i8** %inbuf22, align 8, !dbg !1878
  %cmp23 = icmp eq i8* %19, null, !dbg !1879
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !1880

if.then25:                                        ; preds = %if.then20
  store i64 -1, i64* %retval, align 8, !dbg !1881
  br label %return, !dbg !1881

if.end26:                                         ; preds = %if.then20
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1883
  %inbuf27 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 4, !dbg !1883
  %21 = load i8*, i8** %inbuf27, align 8, !dbg !1883
  call void @llvm.memset.p0i8.i64(i8* %21, i8 0, i64 16384, i32 1, i1 false), !dbg !1883
  br label %if.end28, !dbg !1884

if.end28:                                         ; preds = %if.end26, %if.end17
  br label %while.cond, !dbg !1885

while.cond:                                       ; preds = %if.end41, %if.end28
  %22 = load i64, i64* %offset.addr, align 8, !dbg !1886
  %cmp29 = icmp sgt i64 %22, 0, !dbg !1888
  br i1 %cmp29, label %while.body, label %while.end, !dbg !1889

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %size, metadata !1890, metadata !215), !dbg !1892
  store i32 16384, i32* %size, align 4, !dbg !1892
  %23 = load i64, i64* %offset.addr, align 8, !dbg !1893
  %cmp31 = icmp slt i64 %23, 16384, !dbg !1895
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !1896

if.then33:                                        ; preds = %while.body
  %24 = load i64, i64* %offset.addr, align 8, !dbg !1897
  %conv34 = trunc i64 %24 to i32, !dbg !1899
  store i32 %conv34, i32* %size, align 4, !dbg !1900
  br label %if.end35, !dbg !1901

if.end35:                                         ; preds = %if.then33, %while.body
  %25 = load i8*, i8** %file.addr, align 8, !dbg !1902
  %26 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1903
  %inbuf36 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %26, i32 0, i32 4, !dbg !1904
  %27 = load i8*, i8** %inbuf36, align 8, !dbg !1904
  %28 = load i32, i32* %size, align 4, !dbg !1905
  %call37 = call i32 @cm_zlib_gzwrite(i8* %25, i8* %27, i32 %28), !dbg !1906
  store i32 %call37, i32* %size, align 4, !dbg !1907
  %29 = load i32, i32* %size, align 4, !dbg !1908
  %cmp38 = icmp eq i32 %29, 0, !dbg !1910
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !1911

if.then40:                                        ; preds = %if.end35
  store i64 -1, i64* %retval, align 8, !dbg !1912
  br label %return, !dbg !1912

if.end41:                                         ; preds = %if.end35
  %30 = load i32, i32* %size, align 4, !dbg !1914
  %conv42 = zext i32 %30 to i64, !dbg !1914
  %31 = load i64, i64* %offset.addr, align 8, !dbg !1915
  %sub43 = sub nsw i64 %31, %conv42, !dbg !1915
  store i64 %sub43, i64* %offset.addr, align 8, !dbg !1915
  br label %while.cond, !dbg !1916

while.end:                                        ; preds = %while.cond
  %32 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1918
  %in44 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %32, i32 0, i32 12, !dbg !1919
  %33 = load i64, i64* %in44, align 8, !dbg !1919
  store i64 %33, i64* %retval, align 8, !dbg !1920
  br label %return, !dbg !1920

if.end45:                                         ; preds = %if.end
  %34 = load i32, i32* %whence.addr, align 4, !dbg !1921
  %cmp46 = icmp eq i32 %34, 1, !dbg !1923
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !1924

if.then48:                                        ; preds = %if.end45
  %35 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1925
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %35, i32 0, i32 13, !dbg !1927
  %36 = load i64, i64* %out, align 8, !dbg !1927
  %37 = load i64, i64* %offset.addr, align 8, !dbg !1928
  %add = add nsw i64 %37, %36, !dbg !1928
  store i64 %add, i64* %offset.addr, align 8, !dbg !1928
  br label %if.end49, !dbg !1929

if.end49:                                         ; preds = %if.then48, %if.end45
  %38 = load i64, i64* %offset.addr, align 8, !dbg !1930
  %cmp50 = icmp slt i64 %38, 0, !dbg !1932
  br i1 %cmp50, label %if.then52, label %if.end53, !dbg !1933

if.then52:                                        ; preds = %if.end49
  store i64 -1, i64* %retval, align 8, !dbg !1934
  br label %return, !dbg !1934

if.end53:                                         ; preds = %if.end49
  %39 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1936
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %39, i32 0, i32 9, !dbg !1938
  %40 = load i32, i32* %transparent, align 8, !dbg !1938
  %tobool = icmp ne i32 %40, 0, !dbg !1936
  br i1 %tobool, label %if.then54, label %if.end65, !dbg !1939

if.then54:                                        ; preds = %if.end53
  %41 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1940
  %back = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %41, i32 0, i32 14, !dbg !1942
  store i32 -1, i32* %back, align 8, !dbg !1943
  %42 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1944
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %42, i32 0, i32 0, !dbg !1945
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !1946
  store i32 0, i32* %avail_in, align 8, !dbg !1947
  %43 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1948
  %inbuf55 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %43, i32 0, i32 4, !dbg !1949
  %44 = load i8*, i8** %inbuf55, align 8, !dbg !1949
  %45 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1950
  %stream56 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %45, i32 0, i32 0, !dbg !1951
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream56, i32 0, i32 0, !dbg !1952
  store i8* %44, i8** %next_in, align 8, !dbg !1953
  %46 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1954
  %file57 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %46, i32 0, i32 3, !dbg !1956
  %47 = load %struct._IO_FILE*, %struct._IO_FILE** %file57, align 8, !dbg !1956
  %48 = load i64, i64* %offset.addr, align 8, !dbg !1957
  %call58 = call i32 @fseek(%struct._IO_FILE* %47, i64 %48, i32 0), !dbg !1958
  %cmp59 = icmp slt i32 %call58, 0, !dbg !1959
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !1960

if.then61:                                        ; preds = %if.then54
  store i64 -1, i64* %retval, align 8, !dbg !1961
  br label %return, !dbg !1961

if.end62:                                         ; preds = %if.then54
  %49 = load i64, i64* %offset.addr, align 8, !dbg !1963
  %50 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1964
  %out63 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %50, i32 0, i32 13, !dbg !1965
  store i64 %49, i64* %out63, align 8, !dbg !1966
  %51 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1967
  %in64 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %51, i32 0, i32 12, !dbg !1968
  store i64 %49, i64* %in64, align 8, !dbg !1969
  %52 = load i64, i64* %offset.addr, align 8, !dbg !1970
  store i64 %52, i64* %retval, align 8, !dbg !1971
  br label %return, !dbg !1971

if.end65:                                         ; preds = %if.end53
  %53 = load i64, i64* %offset.addr, align 8, !dbg !1972
  %54 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1974
  %out66 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %54, i32 0, i32 13, !dbg !1975
  %55 = load i64, i64* %out66, align 8, !dbg !1975
  %cmp67 = icmp sge i64 %53, %55, !dbg !1976
  br i1 %cmp67, label %if.then69, label %if.else, !dbg !1977

if.then69:                                        ; preds = %if.end65
  %56 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1978
  %out70 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %56, i32 0, i32 13, !dbg !1980
  %57 = load i64, i64* %out70, align 8, !dbg !1980
  %58 = load i64, i64* %offset.addr, align 8, !dbg !1981
  %sub71 = sub nsw i64 %58, %57, !dbg !1981
  store i64 %sub71, i64* %offset.addr, align 8, !dbg !1981
  br label %if.end77, !dbg !1982

if.else:                                          ; preds = %if.end65
  %59 = load i8*, i8** %file.addr, align 8, !dbg !1983
  %call72 = call i32 @cm_zlib_gzrewind(i8* %59), !dbg !1986
  %cmp73 = icmp slt i32 %call72, 0, !dbg !1987
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !1986

if.then75:                                        ; preds = %if.else
  store i64 -1, i64* %retval, align 8, !dbg !1988
  br label %return, !dbg !1988

if.end76:                                         ; preds = %if.else
  br label %if.end77

if.end77:                                         ; preds = %if.end76, %if.then69
  %60 = load i64, i64* %offset.addr, align 8, !dbg !1990
  %cmp78 = icmp ne i64 %60, 0, !dbg !1992
  br i1 %cmp78, label %land.lhs.true, label %if.end90, !dbg !1993

land.lhs.true:                                    ; preds = %if.end77
  %61 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !1994
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %61, i32 0, i32 5, !dbg !1996
  %62 = load i8*, i8** %outbuf, align 8, !dbg !1996
  %cmp80 = icmp eq i8* %62, null, !dbg !1997
  br i1 %cmp80, label %if.then82, label %if.end90, !dbg !1998

if.then82:                                        ; preds = %land.lhs.true
  %call83 = call noalias i8* @malloc(i64 16384) #6, !dbg !1999
  %63 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2001
  %outbuf84 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %63, i32 0, i32 5, !dbg !2002
  store i8* %call83, i8** %outbuf84, align 8, !dbg !2003
  %64 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2004
  %outbuf85 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %64, i32 0, i32 5, !dbg !2006
  %65 = load i8*, i8** %outbuf85, align 8, !dbg !2006
  %cmp86 = icmp eq i8* %65, null, !dbg !2007
  br i1 %cmp86, label %if.then88, label %if.end89, !dbg !2008

if.then88:                                        ; preds = %if.then82
  store i64 -1, i64* %retval, align 8, !dbg !2009
  br label %return, !dbg !2009

if.end89:                                         ; preds = %if.then82
  br label %if.end90, !dbg !2011

if.end90:                                         ; preds = %if.end89, %land.lhs.true, %if.end77
  %66 = load i64, i64* %offset.addr, align 8, !dbg !2012
  %tobool91 = icmp ne i64 %66, 0, !dbg !2012
  br i1 %tobool91, label %land.lhs.true92, label %if.end103, !dbg !2014

land.lhs.true92:                                  ; preds = %if.end90
  %67 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2015
  %back93 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %67, i32 0, i32 14, !dbg !2017
  %68 = load i32, i32* %back93, align 8, !dbg !2017
  %cmp94 = icmp ne i32 %68, -1, !dbg !2018
  br i1 %cmp94, label %if.then96, label %if.end103, !dbg !2019

if.then96:                                        ; preds = %land.lhs.true92
  %69 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2020
  %back97 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %69, i32 0, i32 14, !dbg !2022
  store i32 -1, i32* %back97, align 8, !dbg !2023
  %70 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2024
  %out98 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %70, i32 0, i32 13, !dbg !2025
  %71 = load i64, i64* %out98, align 8, !dbg !2026
  %inc = add nsw i64 %71, 1, !dbg !2026
  store i64 %inc, i64* %out98, align 8, !dbg !2026
  %72 = load i64, i64* %offset.addr, align 8, !dbg !2027
  %dec = add nsw i64 %72, -1, !dbg !2027
  store i64 %dec, i64* %offset.addr, align 8, !dbg !2027
  %73 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2028
  %last = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %73, i32 0, i32 15, !dbg !2030
  %74 = load i32, i32* %last, align 4, !dbg !2030
  %tobool99 = icmp ne i32 %74, 0, !dbg !2028
  br i1 %tobool99, label %if.then100, label %if.end102, !dbg !2031

if.then100:                                       ; preds = %if.then96
  %75 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2032
  %z_err101 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %75, i32 0, i32 1, !dbg !2034
  store i32 1, i32* %z_err101, align 8, !dbg !2035
  br label %if.end102, !dbg !2032

if.end102:                                        ; preds = %if.then100, %if.then96
  br label %if.end103, !dbg !2036

if.end103:                                        ; preds = %if.end102, %land.lhs.true92, %if.end90
  br label %while.cond104, !dbg !2037

while.cond104:                                    ; preds = %if.end119, %if.end103
  %76 = load i64, i64* %offset.addr, align 8, !dbg !2038
  %cmp105 = icmp sgt i64 %76, 0, !dbg !2040
  br i1 %cmp105, label %while.body107, label %while.end122, !dbg !2041

while.body107:                                    ; preds = %while.cond104
  call void @llvm.dbg.declare(metadata i32* %size108, metadata !2042, metadata !215), !dbg !2044
  store i32 16384, i32* %size108, align 4, !dbg !2044
  %77 = load i64, i64* %offset.addr, align 8, !dbg !2045
  %cmp109 = icmp slt i64 %77, 16384, !dbg !2047
  br i1 %cmp109, label %if.then111, label %if.end113, !dbg !2048

if.then111:                                       ; preds = %while.body107
  %78 = load i64, i64* %offset.addr, align 8, !dbg !2049
  %conv112 = trunc i64 %78 to i32, !dbg !2051
  store i32 %conv112, i32* %size108, align 4, !dbg !2052
  br label %if.end113, !dbg !2053

if.end113:                                        ; preds = %if.then111, %while.body107
  %79 = load i8*, i8** %file.addr, align 8, !dbg !2054
  %80 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2055
  %outbuf114 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %80, i32 0, i32 5, !dbg !2056
  %81 = load i8*, i8** %outbuf114, align 8, !dbg !2056
  %82 = load i32, i32* %size108, align 4, !dbg !2057
  %call115 = call i32 @cm_zlib_gzread(i8* %79, i8* %81, i32 %82), !dbg !2058
  store i32 %call115, i32* %size108, align 4, !dbg !2059
  %83 = load i32, i32* %size108, align 4, !dbg !2060
  %cmp116 = icmp sle i32 %83, 0, !dbg !2062
  br i1 %cmp116, label %if.then118, label %if.end119, !dbg !2063

if.then118:                                       ; preds = %if.end113
  store i64 -1, i64* %retval, align 8, !dbg !2064
  br label %return, !dbg !2064

if.end119:                                        ; preds = %if.end113
  %84 = load i32, i32* %size108, align 4, !dbg !2066
  %conv120 = sext i32 %84 to i64, !dbg !2066
  %85 = load i64, i64* %offset.addr, align 8, !dbg !2067
  %sub121 = sub nsw i64 %85, %conv120, !dbg !2067
  store i64 %sub121, i64* %offset.addr, align 8, !dbg !2067
  br label %while.cond104, !dbg !2068

while.end122:                                     ; preds = %while.cond104
  %86 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2069
  %out123 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %86, i32 0, i32 13, !dbg !2070
  %87 = load i64, i64* %out123, align 8, !dbg !2070
  store i64 %87, i64* %retval, align 8, !dbg !2071
  br label %return, !dbg !2071

return:                                           ; preds = %while.end122, %if.then118, %if.then88, %if.then75, %if.end62, %if.then61, %if.then52, %while.end, %if.then40, %if.then25, %if.then16, %if.then
  %88 = load i64, i64* %retval, align 8, !dbg !2072
  ret i64 %88, !dbg !2072
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #3

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzrewind(i8* %file) #0 !dbg !174 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2073, metadata !215), !dbg !2074
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2075, metadata !215), !dbg !2076
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2077
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2078
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2076
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2079
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2081
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2082

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2083
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !2085
  %4 = load i8, i8* %mode, align 4, !dbg !2085
  %conv = sext i8 %4 to i32, !dbg !2083
  %cmp1 = icmp ne i32 %conv, 114, !dbg !2086
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2087

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -1, i32* %retval, align 4, !dbg !2088
  br label %return, !dbg !2088

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2090
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 1, !dbg !2091
  store i32 0, i32* %z_err, align 8, !dbg !2092
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2093
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 2, !dbg !2094
  store i32 0, i32* %z_eof, align 4, !dbg !2095
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2096
  %back = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 14, !dbg !2097
  store i32 -1, i32* %back, align 8, !dbg !2098
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2099
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 0, !dbg !2100
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !2101
  store i32 0, i32* %avail_in, align 8, !dbg !2102
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2103
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 4, !dbg !2104
  %10 = load i8*, i8** %inbuf, align 8, !dbg !2104
  %11 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2105
  %stream3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %11, i32 0, i32 0, !dbg !2106
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream3, i32 0, i32 0, !dbg !2107
  store i8* %10, i8** %next_in, align 8, !dbg !2108
  %call = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !2109
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2110
  %crc = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 6, !dbg !2111
  store i64 %call, i64* %crc, align 8, !dbg !2112
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2113
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 9, !dbg !2115
  %14 = load i32, i32* %transparent, align 8, !dbg !2115
  %tobool = icmp ne i32 %14, 0, !dbg !2113
  br i1 %tobool, label %if.end7, label %if.then4, !dbg !2116

if.then4:                                         ; preds = %if.end
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2117
  %stream5 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 0, !dbg !2119
  %call6 = call i32 @cm_zlib_inflateReset(%struct.z_stream_s* %stream5), !dbg !2120
  br label %if.end7, !dbg !2121

if.end7:                                          ; preds = %if.then4, %if.end
  %16 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2122
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %16, i32 0, i32 12, !dbg !2123
  store i64 0, i64* %in, align 8, !dbg !2124
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2125
  %out = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 13, !dbg !2126
  store i64 0, i64* %out, align 8, !dbg !2127
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2128
  %file8 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 3, !dbg !2129
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %file8, align 8, !dbg !2129
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2130
  %start = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 11, !dbg !2131
  %21 = load i64, i64* %start, align 8, !dbg !2131
  %call9 = call i32 @fseek(%struct._IO_FILE* %19, i64 %21, i32 0), !dbg !2132
  store i32 %call9, i32* %retval, align 4, !dbg !2133
  br label %return, !dbg !2133

return:                                           ; preds = %if.end7, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !2134
  ret i32 %22, !dbg !2134
}

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_gztell(i8* %file) #0 !dbg !175 {
entry:
  %file.addr = alloca i8*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2135, metadata !215), !dbg !2136
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2137
  %call = call i64 @cm_zlib_gzseek(i8* %0, i64 0, i32 1), !dbg !2138
  ret i64 %call, !dbg !2139
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzeof(i8* %file) #0 !dbg !178 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2140, metadata !215), !dbg !2141
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2142, metadata !215), !dbg !2143
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2144
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2145
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2143
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2146
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2148
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2149

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2150
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !2152
  %4 = load i8, i8* %mode, align 4, !dbg !2152
  %conv = sext i8 %4 to i32, !dbg !2150
  %cmp1 = icmp ne i32 %conv, 114, !dbg !2153
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2154

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !2155
  br label %return, !dbg !2155

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2157
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 2, !dbg !2159
  %6 = load i32, i32* %z_eof, align 4, !dbg !2159
  %tobool = icmp ne i32 %6, 0, !dbg !2157
  br i1 %tobool, label %if.then3, label %if.end4, !dbg !2160

if.then3:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !2161
  br label %return, !dbg !2161

if.end4:                                          ; preds = %if.end
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2163
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 1, !dbg !2164
  %8 = load i32, i32* %z_err, align 8, !dbg !2164
  %cmp5 = icmp eq i32 %8, 1, !dbg !2165
  %conv6 = zext i1 %cmp5 to i32, !dbg !2165
  store i32 %conv6, i32* %retval, align 4, !dbg !2166
  br label %return, !dbg !2166

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !2167
  ret i32 %9, !dbg !2167
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzdirect(i8* %file) #0 !dbg !179 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2168, metadata !215), !dbg !2169
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2170, metadata !215), !dbg !2171
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2172
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2173
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2171
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2174
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2176
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2177

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2178
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !2180
  %4 = load i8, i8* %mode, align 4, !dbg !2180
  %conv = sext i8 %4 to i32, !dbg !2178
  %cmp1 = icmp ne i32 %conv, 114, !dbg !2181
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2182

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !2183
  br label %return, !dbg !2183

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2185
  %transparent = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 9, !dbg !2186
  %6 = load i32, i32* %transparent, align 8, !dbg !2186
  store i32 %6, i32* %retval, align 4, !dbg !2187
  br label %return, !dbg !2187

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !2188
  ret i32 %7, !dbg !2188
}

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_gzclose(i8* %file) #0 !dbg !180 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2189, metadata !215), !dbg !2190
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2191, metadata !215), !dbg !2192
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2193
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2194
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2192
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2195
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2197
  br i1 %cmp, label %if.then, label %if.end, !dbg !2198

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !2199
  br label %return, !dbg !2199

if.end:                                           ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2201
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 10, !dbg !2203
  %4 = load i8, i8* %mode, align 4, !dbg !2203
  %conv = sext i8 %4 to i32, !dbg !2201
  %cmp1 = icmp eq i32 %conv, 119, !dbg !2204
  br i1 %cmp1, label %if.then3, label %if.end11, !dbg !2205

if.then3:                                         ; preds = %if.end
  %5 = load i8*, i8** %file.addr, align 8, !dbg !2206
  %call = call i32 @do_flush(i8* %5, i32 4), !dbg !2209
  %cmp4 = icmp ne i32 %call, 0, !dbg !2210
  br i1 %cmp4, label %if.then6, label %if.end8, !dbg !2211

if.then6:                                         ; preds = %if.then3
  %6 = load i8*, i8** %file.addr, align 8, !dbg !2212
  %7 = bitcast i8* %6 to %struct.gz_stream*, !dbg !2213
  %call7 = call i32 @destroy(%struct.gz_stream* %7), !dbg !2214
  store i32 %call7, i32* %retval, align 4, !dbg !2215
  br label %return, !dbg !2215

if.end8:                                          ; preds = %if.then3
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2216
  %file9 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 3, !dbg !2217
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** %file9, align 8, !dbg !2217
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2218
  %crc = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 6, !dbg !2219
  %11 = load i64, i64* %crc, align 8, !dbg !2219
  call void @putLong(%struct._IO_FILE* %9, i64 %11), !dbg !2220
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2221
  %file10 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 3, !dbg !2222
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %file10, align 8, !dbg !2222
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2223
  %in = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 12, !dbg !2224
  %15 = load i64, i64* %in, align 8, !dbg !2224
  %and = and i64 %15, 4294967295, !dbg !2225
  call void @putLong(%struct._IO_FILE* %13, i64 %and), !dbg !2226
  br label %if.end11, !dbg !2227

if.end11:                                         ; preds = %if.end8, %if.end
  %16 = load i8*, i8** %file.addr, align 8, !dbg !2228
  %17 = bitcast i8* %16 to %struct.gz_stream*, !dbg !2229
  %call12 = call i32 @destroy(%struct.gz_stream* %17), !dbg !2230
  store i32 %call12, i32* %retval, align 4, !dbg !2231
  br label %return, !dbg !2231

return:                                           ; preds = %if.end11, %if.then6, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !2232
  ret i32 %18, !dbg !2232
}

; Function Attrs: nounwind uwtable
define internal i32 @destroy(%struct.gz_stream* %s) #0 !dbg !201 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.gz_stream*, align 8
  %err = alloca i32, align 4
  store %struct.gz_stream* %s, %struct.gz_stream** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s.addr, metadata !2233, metadata !215), !dbg !2234
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2235, metadata !215), !dbg !2236
  store i32 0, i32* %err, align 4, !dbg !2236
  %0 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2237
  %tobool = icmp ne %struct.gz_stream* %0, null, !dbg !2237
  br i1 %tobool, label %if.end, label %if.then, !dbg !2239

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !2240
  br label %return, !dbg !2240

if.end:                                           ; preds = %entry
  %1 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2242
  %msg = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %1, i32 0, i32 7, !dbg !2242
  %2 = load i8*, i8** %msg, align 8, !dbg !2242
  %tobool1 = icmp ne i8* %2, null, !dbg !2242
  br i1 %tobool1, label %if.then2, label %if.end4, !dbg !2245

if.then2:                                         ; preds = %if.end
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2246
  %msg3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 7, !dbg !2246
  %4 = load i8*, i8** %msg3, align 8, !dbg !2246
  call void @free(i8* %4) #6, !dbg !2246
  br label %if.end4, !dbg !2246

if.end4:                                          ; preds = %if.then2, %if.end
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2248
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 0, !dbg !2250
  %state = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 7, !dbg !2251
  %6 = load %struct.internal_state*, %struct.internal_state** %state, align 8, !dbg !2251
  %cmp = icmp ne %struct.internal_state* %6, null, !dbg !2252
  br i1 %cmp, label %if.then5, label %if.end19, !dbg !2253

if.then5:                                         ; preds = %if.end4
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2254
  %mode = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 10, !dbg !2257
  %8 = load i8, i8* %mode, align 4, !dbg !2257
  %conv = sext i8 %8 to i32, !dbg !2254
  %cmp6 = icmp eq i32 %conv, 119, !dbg !2258
  br i1 %cmp6, label %if.then8, label %if.else, !dbg !2259

if.then8:                                         ; preds = %if.then5
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2260
  %stream9 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 0, !dbg !2262
  %call = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %stream9), !dbg !2263
  store i32 %call, i32* %err, align 4, !dbg !2264
  br label %if.end18, !dbg !2265

if.else:                                          ; preds = %if.then5
  %10 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2266
  %mode10 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %10, i32 0, i32 10, !dbg !2269
  %11 = load i8, i8* %mode10, align 4, !dbg !2269
  %conv11 = sext i8 %11 to i32, !dbg !2266
  %cmp12 = icmp eq i32 %conv11, 114, !dbg !2270
  br i1 %cmp12, label %if.then14, label %if.end17, !dbg !2266

if.then14:                                        ; preds = %if.else
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2271
  %stream15 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 0, !dbg !2273
  %call16 = call i32 @cm_zlib_inflateEnd(%struct.z_stream_s* %stream15), !dbg !2274
  store i32 %call16, i32* %err, align 4, !dbg !2275
  br label %if.end17, !dbg !2276

if.end17:                                         ; preds = %if.then14, %if.else
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then8
  br label %if.end19, !dbg !2277

if.end19:                                         ; preds = %if.end18, %if.end4
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2278
  %file = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 3, !dbg !2280
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !2280
  %cmp20 = icmp ne %struct._IO_FILE* %14, null, !dbg !2281
  br i1 %cmp20, label %land.lhs.true, label %if.end31, !dbg !2282

land.lhs.true:                                    ; preds = %if.end19
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2283
  %file22 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 3, !dbg !2285
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %file22, align 8, !dbg !2285
  %call23 = call i32 @fclose(%struct._IO_FILE* %16), !dbg !2286
  %tobool24 = icmp ne i32 %call23, 0, !dbg !2286
  br i1 %tobool24, label %if.then25, label %if.end31, !dbg !2287

if.then25:                                        ; preds = %land.lhs.true
  %call26 = call i32* @__errno_location() #1, !dbg !2288
  %17 = load i32, i32* %call26, align 4, !dbg !2288
  %cmp27 = icmp ne i32 %17, 29, !dbg !2291
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !2292

if.then29:                                        ; preds = %if.then25
  store i32 -1, i32* %err, align 4, !dbg !2293
  br label %if.end30, !dbg !2294

if.end30:                                         ; preds = %if.then29, %if.then25
  br label %if.end31, !dbg !2295

if.end31:                                         ; preds = %if.end30, %land.lhs.true, %if.end19
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2296
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 1, !dbg !2298
  %19 = load i32, i32* %z_err, align 8, !dbg !2298
  %cmp32 = icmp slt i32 %19, 0, !dbg !2299
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !2300

if.then34:                                        ; preds = %if.end31
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2301
  %z_err35 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 1, !dbg !2303
  %21 = load i32, i32* %z_err35, align 8, !dbg !2303
  store i32 %21, i32* %err, align 4, !dbg !2304
  br label %if.end36, !dbg !2305

if.end36:                                         ; preds = %if.then34, %if.end31
  %22 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2306
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %22, i32 0, i32 4, !dbg !2306
  %23 = load i8*, i8** %inbuf, align 8, !dbg !2306
  %tobool37 = icmp ne i8* %23, null, !dbg !2306
  br i1 %tobool37, label %if.then38, label %if.end40, !dbg !2309

if.then38:                                        ; preds = %if.end36
  %24 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2310
  %inbuf39 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %24, i32 0, i32 4, !dbg !2310
  %25 = load i8*, i8** %inbuf39, align 8, !dbg !2310
  call void @free(i8* %25) #6, !dbg !2310
  br label %if.end40, !dbg !2310

if.end40:                                         ; preds = %if.then38, %if.end36
  %26 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2312
  %outbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %26, i32 0, i32 5, !dbg !2312
  %27 = load i8*, i8** %outbuf, align 8, !dbg !2312
  %tobool41 = icmp ne i8* %27, null, !dbg !2312
  br i1 %tobool41, label %if.then42, label %if.end44, !dbg !2315

if.then42:                                        ; preds = %if.end40
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2316
  %outbuf43 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 5, !dbg !2316
  %29 = load i8*, i8** %outbuf43, align 8, !dbg !2316
  call void @free(i8* %29) #6, !dbg !2316
  br label %if.end44, !dbg !2316

if.end44:                                         ; preds = %if.then42, %if.end40
  %30 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2318
  %path = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %30, i32 0, i32 8, !dbg !2318
  %31 = load i8*, i8** %path, align 8, !dbg !2318
  %tobool45 = icmp ne i8* %31, null, !dbg !2318
  br i1 %tobool45, label %if.then46, label %if.end48, !dbg !2321

if.then46:                                        ; preds = %if.end44
  %32 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2322
  %path47 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %32, i32 0, i32 8, !dbg !2322
  %33 = load i8*, i8** %path47, align 8, !dbg !2322
  call void @free(i8* %33) #6, !dbg !2322
  br label %if.end48, !dbg !2322

if.end48:                                         ; preds = %if.then46, %if.end44
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2324
  %tobool49 = icmp ne %struct.gz_stream* %34, null, !dbg !2324
  br i1 %tobool49, label %if.then50, label %if.end51, !dbg !2327

if.then50:                                        ; preds = %if.end48
  %35 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2328
  %36 = bitcast %struct.gz_stream* %35 to i8*, !dbg !2328
  call void @free(i8* %36) #6, !dbg !2328
  br label %if.end51, !dbg !2328

if.end51:                                         ; preds = %if.then50, %if.end48
  %37 = load i32, i32* %err, align 4, !dbg !2330
  store i32 %37, i32* %retval, align 4, !dbg !2331
  br label %return, !dbg !2331

return:                                           ; preds = %if.end51, %if.then
  %38 = load i32, i32* %retval, align 4, !dbg !2332
  ret i32 %38, !dbg !2332
}

; Function Attrs: nounwind uwtable
define internal void @putLong(%struct._IO_FILE* %file, i64 %x) #0 !dbg !202 {
entry:
  %file.addr = alloca %struct._IO_FILE*, align 8
  %x.addr = alloca i64, align 8
  %n = alloca i32, align 4
  store %struct._IO_FILE* %file, %struct._IO_FILE** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %file.addr, metadata !2333, metadata !215), !dbg !2334
  store i64 %x, i64* %x.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %x.addr, metadata !2335, metadata !215), !dbg !2336
  call void @llvm.dbg.declare(metadata i32* %n, metadata !2337, metadata !215), !dbg !2338
  store i32 0, i32* %n, align 4, !dbg !2339
  br label %for.cond, !dbg !2341

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %n, align 4, !dbg !2342
  %cmp = icmp slt i32 %0, 4, !dbg !2345
  br i1 %cmp, label %for.body, label %for.end, !dbg !2346

for.body:                                         ; preds = %for.cond
  %1 = load i64, i64* %x.addr, align 8, !dbg !2347
  %and = and i64 %1, 255, !dbg !2349
  %conv = trunc i64 %and to i32, !dbg !2350
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %file.addr, align 8, !dbg !2351
  %call = call i32 @fputc(i32 %conv, %struct._IO_FILE* %2), !dbg !2352
  %3 = load i64, i64* %x.addr, align 8, !dbg !2353
  %shr = lshr i64 %3, 8, !dbg !2353
  store i64 %shr, i64* %x.addr, align 8, !dbg !2353
  br label %for.inc, !dbg !2354

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* %n, align 4, !dbg !2355
  %inc = add nsw i32 %4, 1, !dbg !2355
  store i32 %inc, i32* %n, align 4, !dbg !2355
  br label %for.cond, !dbg !2357

for.end:                                          ; preds = %for.cond
  ret void, !dbg !2358
}

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_gzerror(i8* %file, i32* %errnum) #0 !dbg !181 {
entry:
  %retval = alloca i8*, align 8
  %file.addr = alloca i8*, align 8
  %errnum.addr = alloca i32*, align 8
  %m = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2359, metadata !215), !dbg !2360
  store i32* %errnum, i32** %errnum.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %errnum.addr, metadata !2361, metadata !215), !dbg !2362
  call void @llvm.dbg.declare(metadata i8** %m, metadata !2363, metadata !215), !dbg !2364
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2365, metadata !215), !dbg !2366
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2367
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2368
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2366
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2369
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2371
  br i1 %cmp, label %if.then, label %if.end, !dbg !2372

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %errnum.addr, align 8, !dbg !2373
  store i32 -2, i32* %3, align 4, !dbg !2375
  %4 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 4), align 16, !dbg !2376
  store i8* %4, i8** %retval, align 8, !dbg !2377
  br label %return, !dbg !2377

if.end:                                           ; preds = %entry
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2378
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 1, !dbg !2379
  %6 = load i32, i32* %z_err, align 8, !dbg !2379
  %7 = load i32*, i32** %errnum.addr, align 8, !dbg !2380
  store i32 %6, i32* %7, align 4, !dbg !2381
  %8 = load i32*, i32** %errnum.addr, align 8, !dbg !2382
  %9 = load i32, i32* %8, align 4, !dbg !2384
  %cmp1 = icmp eq i32 %9, 0, !dbg !2385
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2386

if.then2:                                         ; preds = %if.end
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.1, i32 0, i32 0), i8** %retval, align 8, !dbg !2387
  br label %return, !dbg !2387

if.end3:                                          ; preds = %if.end
  %10 = load i32*, i32** %errnum.addr, align 8, !dbg !2389
  %11 = load i32, i32* %10, align 4, !dbg !2390
  %cmp4 = icmp eq i32 %11, -1, !dbg !2391
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !2390

cond.true:                                        ; preds = %if.end3
  %call = call i32* @__errno_location() #1, !dbg !2392
  %12 = load i32, i32* %call, align 4, !dbg !2392
  %call5 = call i8* @strerror(i32 %12) #6, !dbg !2394
  br label %cond.end, !dbg !2396

cond.false:                                       ; preds = %if.end3
  %13 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2397
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %13, i32 0, i32 0, !dbg !2399
  %msg = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 6, !dbg !2400
  %14 = load i8*, i8** %msg, align 8, !dbg !2400
  br label %cond.end, !dbg !2401

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %call5, %cond.true ], [ %14, %cond.false ], !dbg !2402
  store i8* %cond, i8** %m, align 8, !dbg !2404
  %15 = load i8*, i8** %m, align 8, !dbg !2405
  %cmp6 = icmp eq i8* %15, null, !dbg !2407
  br i1 %cmp6, label %if.then9, label %lor.lhs.false, !dbg !2408

lor.lhs.false:                                    ; preds = %cond.end
  %16 = load i8*, i8** %m, align 8, !dbg !2409
  %17 = load i8, i8* %16, align 1, !dbg !2411
  %conv = sext i8 %17 to i32, !dbg !2411
  %cmp7 = icmp eq i32 %conv, 0, !dbg !2412
  br i1 %cmp7, label %if.then9, label %if.end11, !dbg !2413

if.then9:                                         ; preds = %lor.lhs.false, %cond.end
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2414
  %z_err10 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 1, !dbg !2414
  %19 = load i32, i32* %z_err10, align 8, !dbg !2414
  %sub = sub nsw i32 2, %19, !dbg !2414
  %idxprom = sext i32 %sub to i64, !dbg !2414
  %arrayidx = getelementptr inbounds [10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 %idxprom, !dbg !2414
  %20 = load i8*, i8** %arrayidx, align 8, !dbg !2414
  store i8* %20, i8** %m, align 8, !dbg !2416
  br label %if.end11, !dbg !2417

if.end11:                                         ; preds = %if.then9, %lor.lhs.false
  %21 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2418
  %msg12 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %21, i32 0, i32 7, !dbg !2418
  %22 = load i8*, i8** %msg12, align 8, !dbg !2418
  %tobool = icmp ne i8* %22, null, !dbg !2418
  br i1 %tobool, label %if.then13, label %if.end15, !dbg !2421

if.then13:                                        ; preds = %if.end11
  %23 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2422
  %msg14 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %23, i32 0, i32 7, !dbg !2422
  %24 = load i8*, i8** %msg14, align 8, !dbg !2422
  call void @free(i8* %24) #6, !dbg !2422
  br label %if.end15, !dbg !2422

if.end15:                                         ; preds = %if.then13, %if.end11
  %25 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2424
  %path = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %25, i32 0, i32 8, !dbg !2424
  %26 = load i8*, i8** %path, align 8, !dbg !2424
  %call16 = call i64 @strlen(i8* %26) #8, !dbg !2424
  %27 = load i8*, i8** %m, align 8, !dbg !2424
  %call17 = call i64 @strlen(i8* %27) #8, !dbg !2425
  %add = add i64 %call16, %call17, !dbg !2424
  %add18 = add i64 %add, 3, !dbg !2424
  %call19 = call noalias i8* @malloc(i64 %add18) #6, !dbg !2426
  %28 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2427
  %msg20 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %28, i32 0, i32 7, !dbg !2428
  store i8* %call19, i8** %msg20, align 8, !dbg !2429
  %29 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2430
  %msg21 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %29, i32 0, i32 7, !dbg !2432
  %30 = load i8*, i8** %msg21, align 8, !dbg !2432
  %cmp22 = icmp eq i8* %30, null, !dbg !2433
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !2434

if.then24:                                        ; preds = %if.end15
  %31 = load i8*, i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 6), align 16, !dbg !2435
  store i8* %31, i8** %retval, align 8, !dbg !2437
  br label %return, !dbg !2437

if.end25:                                         ; preds = %if.end15
  %32 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2438
  %msg26 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %32, i32 0, i32 7, !dbg !2439
  %33 = load i8*, i8** %msg26, align 8, !dbg !2439
  %34 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2440
  %path27 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %34, i32 0, i32 8, !dbg !2441
  %35 = load i8*, i8** %path27, align 8, !dbg !2441
  %call28 = call i8* @strcpy(i8* %33, i8* %35) #6, !dbg !2442
  %36 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2443
  %msg29 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %36, i32 0, i32 7, !dbg !2444
  %37 = load i8*, i8** %msg29, align 8, !dbg !2444
  %call30 = call i8* @strcat(i8* %37, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0)) #6, !dbg !2445
  %38 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2446
  %msg31 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %38, i32 0, i32 7, !dbg !2447
  %39 = load i8*, i8** %msg31, align 8, !dbg !2447
  %40 = load i8*, i8** %m, align 8, !dbg !2448
  %call32 = call i8* @strcat(i8* %39, i8* %40) #6, !dbg !2449
  %41 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2450
  %msg33 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %41, i32 0, i32 7, !dbg !2451
  %42 = load i8*, i8** %msg33, align 8, !dbg !2451
  store i8* %42, i8** %retval, align 8, !dbg !2452
  br label %return, !dbg !2452

return:                                           ; preds = %if.end25, %if.then24, %if.then2, %if.then
  %43 = load i8*, i8** %retval, align 8, !dbg !2453
  ret i8* %43, !dbg !2453
}

; Function Attrs: nounwind
declare i8* @strerror(i32) #2

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #2

; Function Attrs: nounwind uwtable
define void @cm_zlib_gzclearerr(i8* %file) #0 !dbg !185 {
entry:
  %file.addr = alloca i8*, align 8
  %s = alloca %struct.gz_stream*, align 8
  store i8* %file, i8** %file.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %file.addr, metadata !2454, metadata !215), !dbg !2455
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s, metadata !2456, metadata !215), !dbg !2457
  %0 = load i8*, i8** %file.addr, align 8, !dbg !2458
  %1 = bitcast i8* %0 to %struct.gz_stream*, !dbg !2459
  store %struct.gz_stream* %1, %struct.gz_stream** %s, align 8, !dbg !2457
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2460
  %cmp = icmp eq %struct.gz_stream* %2, null, !dbg !2462
  br i1 %cmp, label %if.then, label %if.end, !dbg !2463

if.then:                                          ; preds = %entry
  br label %return, !dbg !2464

if.end:                                           ; preds = %entry
  %3 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2466
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %3, i32 0, i32 1, !dbg !2468
  %4 = load i32, i32* %z_err, align 8, !dbg !2468
  %cmp1 = icmp ne i32 %4, 1, !dbg !2469
  br i1 %cmp1, label %if.then2, label %if.end4, !dbg !2470

if.then2:                                         ; preds = %if.end
  %5 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2471
  %z_err3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %5, i32 0, i32 1, !dbg !2473
  store i32 0, i32* %z_err3, align 8, !dbg !2474
  br label %if.end4, !dbg !2471

if.end4:                                          ; preds = %if.then2, %if.end
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2475
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 2, !dbg !2476
  store i32 0, i32* %z_eof, align 4, !dbg !2477
  %7 = load %struct.gz_stream*, %struct.gz_stream** %s, align 8, !dbg !2478
  %file5 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %7, i32 0, i32 3, !dbg !2479
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %file5, align 8, !dbg !2479
  call void @clearerr(%struct._IO_FILE* %8) #6, !dbg !2480
  br label %return, !dbg !2481

return:                                           ; preds = %if.end4, %if.then
  ret void, !dbg !2482
}

; Function Attrs: nounwind
declare void @clearerr(%struct._IO_FILE*) #2

declare i32 @cm_zlib_deflateInit2_(%struct.z_stream_s*, i32, i32, i32, i32, i32, i8*, i32) #3

declare i32 @cm_zlib_inflateInit2_(%struct.z_stream_s*, i32, i8*, i32) #3

declare %struct._IO_FILE* @fopen(i8*, i8*) #3

; Function Attrs: nounwind
declare %struct._IO_FILE* @fdopen(i32, i8*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

declare i64 @ftell(%struct._IO_FILE*) #3

; Function Attrs: nounwind uwtable
define internal i32 @get_byte(%struct.gz_stream* %s) #0 !dbg !194 {
entry:
  %retval = alloca i32, align 4
  %s.addr = alloca %struct.gz_stream*, align 8
  store %struct.gz_stream* %s, %struct.gz_stream** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gz_stream** %s.addr, metadata !2484, metadata !215), !dbg !2485
  %0 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2486
  %z_eof = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %0, i32 0, i32 2, !dbg !2488
  %1 = load i32, i32* %z_eof, align 4, !dbg !2488
  %tobool = icmp ne i32 %1, 0, !dbg !2486
  br i1 %tobool, label %if.then, label %if.end, !dbg !2489

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !2490
  br label %return, !dbg !2490

if.end:                                           ; preds = %entry
  %2 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2492
  %stream = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %2, i32 0, i32 0, !dbg !2494
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !2495
  %3 = load i32, i32* %avail_in, align 8, !dbg !2495
  %cmp = icmp eq i32 %3, 0, !dbg !2496
  br i1 %cmp, label %if.then1, label %if.end19, !dbg !2497

if.then1:                                         ; preds = %if.end
  %call = call i32* @__errno_location() #1, !dbg !2498
  store i32 0, i32* %call, align 4, !dbg !2500
  %4 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2501
  %inbuf = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %4, i32 0, i32 4, !dbg !2502
  %5 = load i8*, i8** %inbuf, align 8, !dbg !2502
  %6 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2503
  %file = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %6, i32 0, i32 3, !dbg !2504
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %file, align 8, !dbg !2504
  %call2 = call i64 @fread(i8* %5, i64 1, i64 16384, %struct._IO_FILE* %7), !dbg !2505
  %conv = trunc i64 %call2 to i32, !dbg !2506
  %8 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2507
  %stream3 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %8, i32 0, i32 0, !dbg !2508
  %avail_in4 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream3, i32 0, i32 1, !dbg !2509
  store i32 %conv, i32* %avail_in4, align 8, !dbg !2510
  %9 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2511
  %stream5 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %9, i32 0, i32 0, !dbg !2513
  %avail_in6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream5, i32 0, i32 1, !dbg !2514
  %10 = load i32, i32* %avail_in6, align 8, !dbg !2514
  %cmp7 = icmp eq i32 %10, 0, !dbg !2515
  br i1 %cmp7, label %if.then9, label %if.end16, !dbg !2516

if.then9:                                         ; preds = %if.then1
  %11 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2517
  %z_eof10 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %11, i32 0, i32 2, !dbg !2519
  store i32 1, i32* %z_eof10, align 4, !dbg !2520
  %12 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2521
  %file11 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %12, i32 0, i32 3, !dbg !2523
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %file11, align 8, !dbg !2523
  %call12 = call i32 @ferror(%struct._IO_FILE* %13) #6, !dbg !2524
  %tobool13 = icmp ne i32 %call12, 0, !dbg !2524
  br i1 %tobool13, label %if.then14, label %if.end15, !dbg !2525

if.then14:                                        ; preds = %if.then9
  %14 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2526
  %z_err = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %14, i32 0, i32 1, !dbg !2528
  store i32 -1, i32* %z_err, align 8, !dbg !2529
  br label %if.end15, !dbg !2526

if.end15:                                         ; preds = %if.then14, %if.then9
  store i32 -1, i32* %retval, align 4, !dbg !2530
  br label %return, !dbg !2530

if.end16:                                         ; preds = %if.then1
  %15 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2531
  %inbuf17 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %15, i32 0, i32 4, !dbg !2532
  %16 = load i8*, i8** %inbuf17, align 8, !dbg !2532
  %17 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2533
  %stream18 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %17, i32 0, i32 0, !dbg !2534
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream18, i32 0, i32 0, !dbg !2535
  store i8* %16, i8** %next_in, align 8, !dbg !2536
  br label %if.end19, !dbg !2537

if.end19:                                         ; preds = %if.end16, %if.end
  %18 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2538
  %stream20 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %18, i32 0, i32 0, !dbg !2539
  %avail_in21 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream20, i32 0, i32 1, !dbg !2540
  %19 = load i32, i32* %avail_in21, align 8, !dbg !2541
  %dec = add i32 %19, -1, !dbg !2541
  store i32 %dec, i32* %avail_in21, align 8, !dbg !2541
  %20 = load %struct.gz_stream*, %struct.gz_stream** %s.addr, align 8, !dbg !2542
  %stream22 = getelementptr inbounds %struct.gz_stream, %struct.gz_stream* %20, i32 0, i32 0, !dbg !2543
  %next_in23 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream22, i32 0, i32 0, !dbg !2544
  %21 = load i8*, i8** %next_in23, align 8, !dbg !2545
  %incdec.ptr = getelementptr inbounds i8, i8* %21, i32 1, !dbg !2545
  store i8* %incdec.ptr, i8** %next_in23, align 8, !dbg !2545
  %22 = load i8, i8* %21, align 1, !dbg !2546
  %conv24 = zext i8 %22 to i32, !dbg !2546
  store i32 %conv24, i32* %retval, align 4, !dbg !2547
  br label %return, !dbg !2547

return:                                           ; preds = %if.end19, %if.end15, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !2548
  ret i32 %23, !dbg !2548
}

declare i32 @cm_zlib_deflateEnd(%struct.z_stream_s*) #3

declare i32 @cm_zlib_inflateEnd(%struct.z_stream_s*) #3

declare i32 @fclose(%struct._IO_FILE*) #3

declare i32 @fputc(i32, %struct._IO_FILE*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!211, !212}
!llvm.ident = !{!213}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !133, globals: !205)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/gzio.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{}
!3 = !{!4, !9, !8, !18, !117, !23, !39, !129, !24, !21, !32, !26, !131, !41, !47, !45, !58}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "gzFile", file: !5, line: 1066, baseType: !6)
!5 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidp", file: !7, line: 286, baseType: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "gz_stream", file: !1, line: 73, baseType: !11)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "gz_stream", file: !1, line: 56, size: 1664, align: 64, elements: !12)
!12 = !{!13, !55, !56, !57, !116, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128}
!13 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !11, file: !1, line: 57, baseType: !14, size: 896, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !5, line: 101, baseType: !15)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !5, line: 82, size: 896, align: 64, elements: !16)
!16 = !{!17, !22, !25, !28, !29, !30, !31, !34, !40, !46, !51, !52, !53, !54}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !15, file: !5, line: 83, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !7, line: 276, baseType: !20)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !7, line: 267, baseType: !21)
!21 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !15, file: !5, line: 84, baseType: !23, size: 32, align: 32, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !7, line: 269, baseType: !24)
!24 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !15, file: !5, line: 85, baseType: !26, size: 64, align: 64, offset: 128)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !7, line: 270, baseType: !27)
!27 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !15, file: !5, line: 87, baseType: !18, size: 64, align: 64, offset: 192)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !15, file: !5, line: 88, baseType: !23, size: 32, align: 32, offset: 256)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !15, file: !5, line: 89, baseType: !26, size: 64, align: 64, offset: 320)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !15, file: !5, line: 91, baseType: !32, size: 64, align: 64, offset: 384)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !15, file: !5, line: 92, baseType: !35, size: 64, align: 64, offset: 448)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !1, line: 19, size: 32, align: 32, elements: !37)
!37 = !{!38}
!38 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !36, file: !1, line: 19, baseType: !39, size: 32, align: 32)
!39 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !15, file: !5, line: 94, baseType: !41, size: 64, align: 64, offset: 512)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !5, line: 77, baseType: !42)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DISubroutineType(types: !44)
!44 = !{!45, !45, !23, !23}
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !7, line: 285, baseType: !8)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !15, file: !5, line: 95, baseType: !47, size: 64, align: 64, offset: 576)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !5, line: 78, baseType: !48)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DISubroutineType(types: !50)
!50 = !{null, !45, !45}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !15, file: !5, line: 96, baseType: !45, size: 64, align: 64, offset: 640)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !15, file: !5, line: 98, baseType: !39, size: 32, align: 32, offset: 704)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !15, file: !5, line: 99, baseType: !26, size: 64, align: 64, offset: 768)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !15, file: !5, line: 100, baseType: !26, size: 64, align: 64, offset: 832)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "z_err", scope: !11, file: !1, line: 58, baseType: !39, size: 32, align: 32, offset: 896)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "z_eof", scope: !11, file: !1, line: 59, baseType: !39, size: 32, align: 32, offset: 928)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !11, file: !1, line: 60, baseType: !58, size: 64, align: 64, offset: 960)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !60, line: 48, baseType: !61)
!60 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!61 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !62, line: 245, size: 1728, align: 64, elements: !63)
!62 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!63 = !{!64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !84, !85, !86, !87, !91, !93, !95, !99, !102, !104, !105, !106, !107, !108, !111, !112}
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !61, file: !62, line: 246, baseType: !39, size: 32, align: 32)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !61, file: !62, line: 251, baseType: !32, size: 64, align: 64, offset: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !61, file: !62, line: 252, baseType: !32, size: 64, align: 64, offset: 128)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !61, file: !62, line: 253, baseType: !32, size: 64, align: 64, offset: 192)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !61, file: !62, line: 254, baseType: !32, size: 64, align: 64, offset: 256)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !61, file: !62, line: 255, baseType: !32, size: 64, align: 64, offset: 320)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !61, file: !62, line: 256, baseType: !32, size: 64, align: 64, offset: 384)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !61, file: !62, line: 257, baseType: !32, size: 64, align: 64, offset: 448)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !61, file: !62, line: 258, baseType: !32, size: 64, align: 64, offset: 512)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !61, file: !62, line: 260, baseType: !32, size: 64, align: 64, offset: 576)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !61, file: !62, line: 261, baseType: !32, size: 64, align: 64, offset: 640)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !61, file: !62, line: 262, baseType: !32, size: 64, align: 64, offset: 704)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !61, file: !62, line: 264, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !62, line: 160, size: 192, align: 64, elements: !79)
!79 = !{!80, !81, !83}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !78, file: !62, line: 161, baseType: !77, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !78, file: !62, line: 162, baseType: !82, size: 64, align: 64, offset: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !78, file: !62, line: 166, baseType: !39, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !61, file: !62, line: 266, baseType: !82, size: 64, align: 64, offset: 832)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !61, file: !62, line: 268, baseType: !39, size: 32, align: 32, offset: 896)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !61, file: !62, line: 272, baseType: !39, size: 32, align: 32, offset: 928)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !61, file: !62, line: 274, baseType: !88, size: 64, align: 64, offset: 960)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !89, line: 131, baseType: !90)
!89 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!90 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !61, file: !62, line: 278, baseType: !92, size: 16, align: 16, offset: 1024)
!92 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !61, file: !62, line: 279, baseType: !94, size: 8, align: 8, offset: 1040)
!94 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !61, file: !62, line: 280, baseType: !96, size: 8, align: 8, offset: 1048)
!96 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 8, align: 8, elements: !97)
!97 = !{!98}
!98 = !DISubrange(count: 1)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !61, file: !62, line: 284, baseType: !100, size: 64, align: 64, offset: 1088)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !62, line: 154, baseType: null)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !61, file: !62, line: 293, baseType: !103, size: 64, align: 64, offset: 1152)
!103 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !89, line: 132, baseType: !90)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !61, file: !62, line: 302, baseType: !8, size: 64, align: 64, offset: 1216)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !61, file: !62, line: 303, baseType: !8, size: 64, align: 64, offset: 1280)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !61, file: !62, line: 304, baseType: !8, size: 64, align: 64, offset: 1344)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !61, file: !62, line: 305, baseType: !8, size: 64, align: 64, offset: 1408)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !61, file: !62, line: 306, baseType: !109, size: 64, align: 64, offset: 1472)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !110, line: 62, baseType: !27)
!110 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!111 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !61, file: !62, line: 308, baseType: !39, size: 32, align: 32, offset: 1536)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !61, file: !62, line: 310, baseType: !113, size: 160, align: 8, offset: 1568)
!113 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 160, align: 8, elements: !114)
!114 = !{!115}
!115 = !DISubrange(count: 20)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "inbuf", scope: !11, file: !1, line: 61, baseType: !117, size: 64, align: 64, offset: 1024)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "outbuf", scope: !11, file: !1, line: 62, baseType: !117, size: 64, align: 64, offset: 1088)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !11, file: !1, line: 63, baseType: !26, size: 64, align: 64, offset: 1152)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !11, file: !1, line: 64, baseType: !32, size: 64, align: 64, offset: 1216)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !11, file: !1, line: 65, baseType: !32, size: 64, align: 64, offset: 1280)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "transparent", scope: !11, file: !1, line: 66, baseType: !39, size: 32, align: 32, offset: 1344)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !11, file: !1, line: 67, baseType: !33, size: 8, align: 8, offset: 1376)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !11, file: !1, line: 68, baseType: !90, size: 64, align: 64, offset: 1408)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !11, file: !1, line: 69, baseType: !90, size: 64, align: 64, offset: 1472)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !11, file: !1, line: 70, baseType: !90, size: 64, align: 64, offset: 1536)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "back", scope: !11, file: !1, line: 71, baseType: !39, size: 32, align: 32, offset: 1600)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !11, file: !1, line: 72, baseType: !39, size: 32, align: 32, offset: 1632)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !19)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !33)
!133 = !{!134, !137, !140, !143, !146, !149, !152, !155, !161, !164, !167, !170, !171, !174, !175, !178, !179, !180, !181, !185, !188, !191, !194, !197, !198, !201, !202}
!134 = distinct !DISubprogram(name: "cm_zlib_gzopen", scope: !1, file: !1, line: 208, type: !135, isLocal: false, isDefinition: true, scopeLine: 211, isOptimized: false, variables: !2)
!135 = !DISubroutineType(types: !136)
!136 = !{!4, !131, !131}
!137 = distinct !DISubprogram(name: "cm_zlib_gzdopen", scope: !1, file: !1, line: 219, type: !138, isLocal: false, isDefinition: true, scopeLine: 222, isOptimized: false, variables: !2)
!138 = !DISubroutineType(types: !139)
!139 = !{!4, !39, !131}
!140 = distinct !DISubprogram(name: "cm_zlib_gzsetparams", scope: !1, file: !1, line: 234, type: !141, isLocal: false, isDefinition: true, scopeLine: 238, isOptimized: false, variables: !2)
!141 = !DISubroutineType(types: !142)
!142 = !{!39, !4, !39, !39}
!143 = distinct !DISubprogram(name: "cm_zlib_gzread", scope: !1, file: !1, line: 394, type: !144, isLocal: false, isDefinition: true, scopeLine: 398, isOptimized: false, variables: !2)
!144 = !DISubroutineType(types: !145)
!145 = !{!39, !4, !6, !24}
!146 = distinct !DISubprogram(name: "cm_zlib_gzgetc", scope: !1, file: !1, line: 503, type: !147, isLocal: false, isDefinition: true, scopeLine: 505, isOptimized: false, variables: !2)
!147 = !DISubroutineType(types: !148)
!148 = !{!39, !4}
!149 = distinct !DISubprogram(name: "cm_zlib_gzungetc", scope: !1, file: !1, line: 515, type: !150, isLocal: false, isDefinition: true, scopeLine: 518, isOptimized: false, variables: !2)
!150 = !DISubroutineType(types: !151)
!151 = !{!39, !39, !4}
!152 = distinct !DISubprogram(name: "cm_zlib_gzgets", scope: !1, file: !1, line: 540, type: !153, isLocal: false, isDefinition: true, scopeLine: 544, isOptimized: false, variables: !2)
!153 = !DISubroutineType(types: !154)
!154 = !{!32, !4, !32, !39}
!155 = distinct !DISubprogram(name: "cm_zlib_gzwrite", scope: !1, file: !1, line: 559, type: !156, isLocal: false, isDefinition: true, scopeLine: 563, isOptimized: false, variables: !2)
!156 = !DISubroutineType(types: !157)
!157 = !{!39, !4, !158, !24}
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpc", file: !7, line: 284, baseType: !159)
!159 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!160 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!161 = distinct !DISubprogram(name: "cm_zlib_gzprintf", scope: !1, file: !1, line: 603, type: !162, isLocal: false, isDefinition: true, scopeLine: 604, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!162 = !DISubroutineType(types: !163)
!163 = !{!39, !4, !131, null}
!164 = distinct !DISubprogram(name: "cm_zlib_gzputc", scope: !1, file: !1, line: 678, type: !165, isLocal: false, isDefinition: true, scopeLine: 681, isOptimized: false, variables: !2)
!165 = !DISubroutineType(types: !166)
!166 = !{!39, !4, !39}
!167 = distinct !DISubprogram(name: "cm_zlib_gzputs", scope: !1, file: !1, line: 693, type: !168, isLocal: false, isDefinition: true, scopeLine: 696, isOptimized: false, variables: !2)
!168 = !DISubroutineType(types: !169)
!169 = !{!39, !4, !131}
!170 = distinct !DISubprogram(name: "cm_zlib_gzflush", scope: !1, file: !1, line: 746, type: !165, isLocal: false, isDefinition: true, scopeLine: 749, isOptimized: false, variables: !2)
!171 = distinct !DISubprogram(name: "cm_zlib_gzseek", scope: !1, file: !1, line: 767, type: !172, isLocal: false, isDefinition: true, scopeLine: 771, isOptimized: false, variables: !2)
!172 = !DISubroutineType(types: !173)
!173 = !{!90, !4, !90, !39}
!174 = distinct !DISubprogram(name: "cm_zlib_gzrewind", scope: !1, file: !1, line: 857, type: !147, isLocal: false, isDefinition: true, scopeLine: 859, isOptimized: false, variables: !2)
!175 = distinct !DISubprogram(name: "cm_zlib_gztell", scope: !1, file: !1, line: 881, type: !176, isLocal: false, isDefinition: true, scopeLine: 883, isOptimized: false, variables: !2)
!176 = !DISubroutineType(types: !177)
!177 = !{!90, !4}
!178 = distinct !DISubprogram(name: "cm_zlib_gzeof", scope: !1, file: !1, line: 891, type: !147, isLocal: false, isDefinition: true, scopeLine: 893, isOptimized: false, variables: !2)
!179 = distinct !DISubprogram(name: "cm_zlib_gzdirect", scope: !1, file: !1, line: 908, type: !147, isLocal: false, isDefinition: true, scopeLine: 910, isOptimized: false, variables: !2)
!180 = distinct !DISubprogram(name: "cm_zlib_gzclose", scope: !1, file: !1, line: 953, type: !147, isLocal: false, isDefinition: true, scopeLine: 955, isOptimized: false, variables: !2)
!181 = distinct !DISubprogram(name: "cm_zlib_gzerror", scope: !1, file: !1, line: 987, type: !182, isLocal: false, isDefinition: true, scopeLine: 990, isOptimized: false, variables: !2)
!182 = !DISubroutineType(types: !183)
!183 = !{!131, !4, !184}
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!185 = distinct !DISubprogram(name: "cm_zlib_gzclearerr", scope: !1, file: !1, line: 1017, type: !186, isLocal: false, isDefinition: true, scopeLine: 1019, isOptimized: false, variables: !2)
!186 = !DISubroutineType(types: !187)
!187 = !{null, !4}
!188 = distinct !DISubprogram(name: "gz_open", scope: !1, file: !1, line: 93, type: !189, isLocal: true, isDefinition: true, scopeLine: 97, isOptimized: false, variables: !2)
!189 = !DISubroutineType(types: !190)
!190 = !{!4, !131, !131, !39}
!191 = distinct !DISubprogram(name: "check_header", scope: !1, file: !1, line: 288, type: !192, isLocal: true, isDefinition: true, scopeLine: 290, isOptimized: false, variables: !2)
!192 = !DISubroutineType(types: !193)
!193 = !{null, !9}
!194 = distinct !DISubprogram(name: "get_byte", scope: !1, file: !1, line: 261, type: !195, isLocal: true, isDefinition: true, scopeLine: 263, isOptimized: false, variables: !2)
!195 = !DISubroutineType(types: !196)
!196 = !{!39, !9}
!197 = distinct !DISubprogram(name: "do_flush", scope: !1, file: !1, line: 705, type: !165, isLocal: true, isDefinition: true, scopeLine: 708, isOptimized: false, variables: !2)
!198 = distinct !DISubprogram(name: "getLong", scope: !1, file: !1, line: 935, type: !199, isLocal: true, isDefinition: true, scopeLine: 937, isOptimized: false, variables: !2)
!199 = !DISubroutineType(types: !200)
!200 = !{!26, !9}
!201 = distinct !DISubprogram(name: "destroy", scope: !1, file: !1, line: 355, type: !195, isLocal: true, isDefinition: true, scopeLine: 357, isOptimized: false, variables: !2)
!202 = distinct !DISubprogram(name: "putLong", scope: !1, file: !1, line: 920, type: !203, isLocal: true, isDefinition: true, scopeLine: 923, isOptimized: false, variables: !2)
!203 = !DISubroutineType(types: !204)
!204 = !{null, !58, !26}
!205 = !{!206}
!206 = !DIGlobalVariable(name: "gz_magic", scope: !0, file: !1, line: 46, type: !207, isLocal: true, isDefinition: true, variable: [2 x i32]* @gz_magic)
!207 = !DICompositeType(tag: DW_TAG_array_type, baseType: !208, size: 64, align: 32, elements: !209)
!208 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !39)
!209 = !{!210}
!210 = !DISubrange(count: 2)
!211 = !{i32 2, !"Dwarf Version", i32 4}
!212 = !{i32 2, !"Debug Info Version", i32 3}
!213 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!214 = !DILocalVariable(name: "path", arg: 1, scope: !134, file: !1, line: 209, type: !131)
!215 = !DIExpression()
!216 = !DILocation(line: 209, column: 17, scope: !134)
!217 = !DILocalVariable(name: "mode", arg: 2, scope: !134, file: !1, line: 210, type: !131)
!218 = !DILocation(line: 210, column: 17, scope: !134)
!219 = !DILocation(line: 212, column: 21, scope: !134)
!220 = !DILocation(line: 212, column: 27, scope: !134)
!221 = !DILocation(line: 212, column: 12, scope: !134)
!222 = !DILocation(line: 212, column: 5, scope: !134)
!223 = !DILocalVariable(name: "path", arg: 1, scope: !188, file: !1, line: 94, type: !131)
!224 = !DILocation(line: 94, column: 17, scope: !188)
!225 = !DILocalVariable(name: "mode", arg: 2, scope: !188, file: !1, line: 95, type: !131)
!226 = !DILocation(line: 95, column: 17, scope: !188)
!227 = !DILocalVariable(name: "fd", arg: 3, scope: !188, file: !1, line: 96, type: !39)
!228 = !DILocation(line: 96, column: 10, scope: !188)
!229 = !DILocalVariable(name: "err", scope: !188, file: !1, line: 98, type: !39)
!230 = !DILocation(line: 98, column: 9, scope: !188)
!231 = !DILocalVariable(name: "level", scope: !188, file: !1, line: 99, type: !39)
!232 = !DILocation(line: 99, column: 9, scope: !188)
!233 = !DILocalVariable(name: "strategy", scope: !188, file: !1, line: 100, type: !39)
!234 = !DILocation(line: 100, column: 9, scope: !188)
!235 = !DILocalVariable(name: "p", scope: !188, file: !1, line: 101, type: !32)
!236 = !DILocation(line: 101, column: 11, scope: !188)
!237 = !DILocation(line: 101, column: 22, scope: !188)
!238 = !DILocalVariable(name: "s", scope: !188, file: !1, line: 102, type: !9)
!239 = !DILocation(line: 102, column: 16, scope: !188)
!240 = !DILocalVariable(name: "fmode", scope: !188, file: !1, line: 103, type: !241)
!241 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 640, align: 8, elements: !242)
!242 = !{!243}
!243 = !DISubrange(count: 80)
!244 = !DILocation(line: 103, column: 10, scope: !188)
!245 = !DILocalVariable(name: "m", scope: !188, file: !1, line: 104, type: !32)
!246 = !DILocation(line: 104, column: 11, scope: !188)
!247 = !DILocation(line: 104, column: 15, scope: !188)
!248 = !DILocation(line: 106, column: 10, scope: !249)
!249 = distinct !DILexicalBlock(scope: !188, file: !1, line: 106, column: 9)
!250 = !DILocation(line: 106, column: 15, scope: !249)
!251 = !DILocation(line: 106, column: 19, scope: !252)
!252 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 1)
!253 = !DILocation(line: 106, column: 9, scope: !252)
!254 = !DILocation(line: 106, column: 25, scope: !255)
!255 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 2)
!256 = !DILocation(line: 108, column: 22, scope: !188)
!257 = !DILocation(line: 108, column: 9, scope: !188)
!258 = !DILocation(line: 108, column: 7, scope: !188)
!259 = !DILocation(line: 109, column: 10, scope: !260)
!260 = distinct !DILexicalBlock(scope: !188, file: !1, line: 109, column: 9)
!261 = !DILocation(line: 109, column: 9, scope: !188)
!262 = !DILocation(line: 109, column: 13, scope: !263)
!263 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 1)
!264 = !DILocation(line: 111, column: 5, scope: !188)
!265 = !DILocation(line: 111, column: 8, scope: !188)
!266 = !DILocation(line: 111, column: 15, scope: !188)
!267 = !DILocation(line: 111, column: 22, scope: !188)
!268 = !DILocation(line: 112, column: 5, scope: !188)
!269 = !DILocation(line: 112, column: 8, scope: !188)
!270 = !DILocation(line: 112, column: 15, scope: !188)
!271 = !DILocation(line: 112, column: 21, scope: !188)
!272 = !DILocation(line: 113, column: 5, scope: !188)
!273 = !DILocation(line: 113, column: 8, scope: !188)
!274 = !DILocation(line: 113, column: 15, scope: !188)
!275 = !DILocation(line: 113, column: 22, scope: !188)
!276 = !DILocation(line: 114, column: 25, scope: !188)
!277 = !DILocation(line: 114, column: 28, scope: !188)
!278 = !DILocation(line: 114, column: 34, scope: !188)
!279 = !DILocation(line: 114, column: 5, scope: !188)
!280 = !DILocation(line: 114, column: 8, scope: !188)
!281 = !DILocation(line: 114, column: 15, scope: !188)
!282 = !DILocation(line: 114, column: 23, scope: !188)
!283 = !DILocation(line: 115, column: 26, scope: !188)
!284 = !DILocation(line: 115, column: 29, scope: !188)
!285 = !DILocation(line: 115, column: 36, scope: !188)
!286 = !DILocation(line: 115, column: 5, scope: !188)
!287 = !DILocation(line: 115, column: 8, scope: !188)
!288 = !DILocation(line: 115, column: 15, scope: !188)
!289 = !DILocation(line: 115, column: 24, scope: !188)
!290 = !DILocation(line: 116, column: 26, scope: !188)
!291 = !DILocation(line: 116, column: 29, scope: !188)
!292 = !DILocation(line: 116, column: 36, scope: !188)
!293 = !DILocation(line: 116, column: 46, scope: !188)
!294 = !DILocation(line: 116, column: 5, scope: !188)
!295 = !DILocation(line: 116, column: 8, scope: !188)
!296 = !DILocation(line: 116, column: 15, scope: !188)
!297 = !DILocation(line: 116, column: 24, scope: !188)
!298 = !DILocation(line: 117, column: 5, scope: !188)
!299 = !DILocation(line: 117, column: 8, scope: !188)
!300 = !DILocation(line: 117, column: 13, scope: !188)
!301 = !DILocation(line: 118, column: 5, scope: !188)
!302 = !DILocation(line: 118, column: 8, scope: !188)
!303 = !DILocation(line: 118, column: 14, scope: !188)
!304 = !DILocation(line: 119, column: 5, scope: !188)
!305 = !DILocation(line: 119, column: 8, scope: !188)
!306 = !DILocation(line: 119, column: 14, scope: !188)
!307 = !DILocation(line: 120, column: 5, scope: !188)
!308 = !DILocation(line: 120, column: 8, scope: !188)
!309 = !DILocation(line: 120, column: 11, scope: !188)
!310 = !DILocation(line: 121, column: 5, scope: !188)
!311 = !DILocation(line: 121, column: 8, scope: !188)
!312 = !DILocation(line: 121, column: 12, scope: !188)
!313 = !DILocation(line: 122, column: 5, scope: !188)
!314 = !DILocation(line: 122, column: 8, scope: !188)
!315 = !DILocation(line: 122, column: 13, scope: !188)
!316 = !DILocation(line: 123, column: 14, scope: !188)
!317 = !DILocation(line: 123, column: 5, scope: !188)
!318 = !DILocation(line: 123, column: 8, scope: !188)
!319 = !DILocation(line: 123, column: 12, scope: !188)
!320 = !DILocation(line: 124, column: 5, scope: !188)
!321 = !DILocation(line: 124, column: 8, scope: !188)
!322 = !DILocation(line: 124, column: 12, scope: !188)
!323 = !DILocation(line: 125, column: 5, scope: !188)
!324 = !DILocation(line: 125, column: 8, scope: !188)
!325 = !DILocation(line: 125, column: 20, scope: !188)
!326 = !DILocation(line: 127, column: 22, scope: !188)
!327 = !DILocation(line: 127, column: 22, scope: !328)
!328 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 1)
!329 = !DILocation(line: 127, column: 5, scope: !188)
!330 = !DILocation(line: 127, column: 8, scope: !188)
!331 = !DILocation(line: 127, column: 13, scope: !188)
!332 = !DILocation(line: 128, column: 9, scope: !333)
!333 = distinct !DILexicalBlock(scope: !188, file: !1, line: 128, column: 9)
!334 = !DILocation(line: 128, column: 12, scope: !333)
!335 = !DILocation(line: 128, column: 17, scope: !333)
!336 = !DILocation(line: 128, column: 9, scope: !188)
!337 = !DILocation(line: 129, column: 24, scope: !338)
!338 = distinct !DILexicalBlock(scope: !333, file: !1, line: 128, column: 26)
!339 = !DILocation(line: 129, column: 16, scope: !338)
!340 = !DILocation(line: 129, column: 9, scope: !338)
!341 = !DILocation(line: 131, column: 12, scope: !188)
!342 = !DILocation(line: 131, column: 15, scope: !188)
!343 = !DILocation(line: 131, column: 21, scope: !188)
!344 = !DILocation(line: 131, column: 5, scope: !188)
!345 = !DILocation(line: 133, column: 5, scope: !188)
!346 = !DILocation(line: 133, column: 8, scope: !188)
!347 = !DILocation(line: 133, column: 13, scope: !188)
!348 = !DILocation(line: 134, column: 5, scope: !188)
!349 = !DILocation(line: 135, column: 14, scope: !350)
!350 = distinct !DILexicalBlock(scope: !351, file: !1, line: 135, column: 13)
!351 = distinct !DILexicalBlock(scope: !188, file: !1, line: 134, column: 8)
!352 = !DILocation(line: 135, column: 13, scope: !350)
!353 = !DILocation(line: 135, column: 16, scope: !350)
!354 = !DILocation(line: 135, column: 13, scope: !351)
!355 = !DILocation(line: 135, column: 24, scope: !356)
!356 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 1)
!357 = !DILocation(line: 135, column: 27, scope: !356)
!358 = !DILocation(line: 135, column: 32, scope: !356)
!359 = !DILocation(line: 136, column: 14, scope: !360)
!360 = distinct !DILexicalBlock(scope: !351, file: !1, line: 136, column: 13)
!361 = !DILocation(line: 136, column: 13, scope: !360)
!362 = !DILocation(line: 136, column: 16, scope: !360)
!363 = !DILocation(line: 136, column: 23, scope: !360)
!364 = !DILocation(line: 136, column: 27, scope: !365)
!365 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 1)
!366 = !DILocation(line: 136, column: 26, scope: !365)
!367 = !DILocation(line: 136, column: 29, scope: !365)
!368 = !DILocation(line: 136, column: 13, scope: !365)
!369 = !DILocation(line: 136, column: 37, scope: !370)
!370 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 2)
!371 = !DILocation(line: 136, column: 40, scope: !370)
!372 = !DILocation(line: 136, column: 45, scope: !370)
!373 = !DILocation(line: 137, column: 14, scope: !374)
!374 = distinct !DILexicalBlock(scope: !351, file: !1, line: 137, column: 13)
!375 = !DILocation(line: 137, column: 13, scope: !374)
!376 = !DILocation(line: 137, column: 16, scope: !374)
!377 = !DILocation(line: 137, column: 23, scope: !374)
!378 = !DILocation(line: 137, column: 27, scope: !379)
!379 = !DILexicalBlockFile(scope: !374, file: !1, discriminator: 1)
!380 = !DILocation(line: 137, column: 26, scope: !379)
!381 = !DILocation(line: 137, column: 29, scope: !379)
!382 = !DILocation(line: 137, column: 13, scope: !379)
!383 = !DILocation(line: 138, column: 22, scope: !384)
!384 = distinct !DILexicalBlock(scope: !374, file: !1, line: 137, column: 37)
!385 = !DILocation(line: 138, column: 21, scope: !384)
!386 = !DILocation(line: 138, column: 24, scope: !384)
!387 = !DILocation(line: 138, column: 19, scope: !384)
!388 = !DILocation(line: 139, column: 9, scope: !384)
!389 = !DILocation(line: 139, column: 21, scope: !390)
!390 = !DILexicalBlockFile(scope: !391, file: !1, discriminator: 1)
!391 = distinct !DILexicalBlock(scope: !374, file: !1, line: 139, column: 20)
!392 = !DILocation(line: 139, column: 20, scope: !390)
!393 = !DILocation(line: 139, column: 23, scope: !390)
!394 = !DILocation(line: 140, column: 20, scope: !395)
!395 = distinct !DILexicalBlock(scope: !391, file: !1, line: 139, column: 31)
!396 = !DILocation(line: 141, column: 9, scope: !395)
!397 = !DILocation(line: 141, column: 21, scope: !398)
!398 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!399 = distinct !DILexicalBlock(scope: !391, file: !1, line: 141, column: 20)
!400 = !DILocation(line: 141, column: 20, scope: !398)
!401 = !DILocation(line: 141, column: 23, scope: !398)
!402 = !DILocation(line: 142, column: 20, scope: !403)
!403 = distinct !DILexicalBlock(scope: !399, file: !1, line: 141, column: 31)
!404 = !DILocation(line: 143, column: 9, scope: !403)
!405 = !DILocation(line: 143, column: 21, scope: !406)
!406 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 1)
!407 = distinct !DILexicalBlock(scope: !399, file: !1, line: 143, column: 20)
!408 = !DILocation(line: 143, column: 20, scope: !406)
!409 = !DILocation(line: 143, column: 23, scope: !406)
!410 = !DILocation(line: 144, column: 20, scope: !411)
!411 = distinct !DILexicalBlock(scope: !407, file: !1, line: 143, column: 31)
!412 = !DILocation(line: 145, column: 9, scope: !411)
!413 = !DILocation(line: 146, column: 21, scope: !414)
!414 = distinct !DILexicalBlock(scope: !407, file: !1, line: 145, column: 16)
!415 = !DILocation(line: 146, column: 20, scope: !414)
!416 = !DILocation(line: 146, column: 15, scope: !414)
!417 = !DILocation(line: 146, column: 18, scope: !414)
!418 = !DILocation(line: 148, column: 5, scope: !351)
!419 = !DILocation(line: 148, column: 16, scope: !328)
!420 = !DILocation(line: 148, column: 14, scope: !328)
!421 = !DILocation(line: 148, column: 19, scope: !328)
!422 = !DILocation(line: 148, column: 22, scope: !423)
!423 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 2)
!424 = !DILocation(line: 148, column: 27, scope: !423)
!425 = !DILocation(line: 148, column: 33, scope: !423)
!426 = !DILocation(line: 148, column: 24, scope: !423)
!427 = !DILocation(line: 148, column: 5, scope: !428)
!428 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 3)
!429 = !DILocation(line: 149, column: 9, scope: !430)
!430 = distinct !DILexicalBlock(scope: !188, file: !1, line: 149, column: 9)
!431 = !DILocation(line: 149, column: 12, scope: !430)
!432 = !DILocation(line: 149, column: 17, scope: !430)
!433 = !DILocation(line: 149, column: 9, scope: !188)
!434 = !DILocation(line: 149, column: 41, scope: !435)
!435 = !DILexicalBlockFile(scope: !430, file: !1, discriminator: 1)
!436 = !DILocation(line: 149, column: 33, scope: !435)
!437 = !DILocation(line: 149, column: 26, scope: !435)
!438 = !DILocation(line: 151, column: 9, scope: !439)
!439 = distinct !DILexicalBlock(scope: !188, file: !1, line: 151, column: 9)
!440 = !DILocation(line: 151, column: 12, scope: !439)
!441 = !DILocation(line: 151, column: 17, scope: !439)
!442 = !DILocation(line: 151, column: 9, scope: !188)
!443 = !DILocation(line: 155, column: 15, scope: !444)
!444 = distinct !DILexicalBlock(scope: !439, file: !1, line: 151, column: 25)
!445 = !DILocation(line: 155, column: 13, scope: !444)
!446 = !DILocation(line: 159, column: 49, scope: !444)
!447 = !DILocation(line: 159, column: 30, scope: !444)
!448 = !DILocation(line: 159, column: 33, scope: !444)
!449 = !DILocation(line: 159, column: 40, scope: !444)
!450 = !DILocation(line: 159, column: 9, scope: !444)
!451 = !DILocation(line: 159, column: 12, scope: !444)
!452 = !DILocation(line: 159, column: 19, scope: !444)
!453 = !DILocation(line: 159, column: 28, scope: !444)
!454 = !DILocation(line: 161, column: 13, scope: !455)
!455 = distinct !DILexicalBlock(scope: !444, file: !1, line: 161, column: 13)
!456 = !DILocation(line: 161, column: 17, scope: !455)
!457 = !DILocation(line: 161, column: 25, scope: !455)
!458 = !DILocation(line: 161, column: 28, scope: !459)
!459 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!460 = !DILocation(line: 161, column: 31, scope: !459)
!461 = !DILocation(line: 161, column: 38, scope: !459)
!462 = !DILocation(line: 161, column: 13, scope: !459)
!463 = !DILocation(line: 162, column: 28, scope: !464)
!464 = distinct !DILexicalBlock(scope: !455, file: !1, line: 161, column: 49)
!465 = !DILocation(line: 162, column: 20, scope: !464)
!466 = !DILocation(line: 162, column: 13, scope: !464)
!467 = !DILocation(line: 164, column: 5, scope: !444)
!468 = !DILocation(line: 165, column: 48, scope: !469)
!469 = distinct !DILexicalBlock(scope: !439, file: !1, line: 164, column: 12)
!470 = !DILocation(line: 165, column: 30, scope: !469)
!471 = !DILocation(line: 165, column: 33, scope: !469)
!472 = !DILocation(line: 165, column: 39, scope: !469)
!473 = !DILocation(line: 165, column: 9, scope: !469)
!474 = !DILocation(line: 165, column: 12, scope: !469)
!475 = !DILocation(line: 165, column: 19, scope: !469)
!476 = !DILocation(line: 165, column: 28, scope: !469)
!477 = !DILocation(line: 167, column: 15, scope: !469)
!478 = !DILocation(line: 167, column: 13, scope: !469)
!479 = !DILocation(line: 174, column: 13, scope: !480)
!480 = distinct !DILexicalBlock(scope: !469, file: !1, line: 174, column: 13)
!481 = !DILocation(line: 174, column: 17, scope: !480)
!482 = !DILocation(line: 174, column: 25, scope: !480)
!483 = !DILocation(line: 174, column: 28, scope: !484)
!484 = !DILexicalBlockFile(scope: !480, file: !1, discriminator: 1)
!485 = !DILocation(line: 174, column: 31, scope: !484)
!486 = !DILocation(line: 174, column: 37, scope: !484)
!487 = !DILocation(line: 174, column: 13, scope: !484)
!488 = !DILocation(line: 175, column: 28, scope: !489)
!489 = distinct !DILexicalBlock(scope: !480, file: !1, line: 174, column: 48)
!490 = !DILocation(line: 175, column: 20, scope: !489)
!491 = !DILocation(line: 175, column: 13, scope: !489)
!492 = !DILocation(line: 178, column: 5, scope: !188)
!493 = !DILocation(line: 178, column: 8, scope: !188)
!494 = !DILocation(line: 178, column: 15, scope: !188)
!495 = !DILocation(line: 178, column: 25, scope: !188)
!496 = !DILocation(line: 180, column: 5, scope: !188)
!497 = !DILocation(line: 180, column: 11, scope: !188)
!498 = !DILocation(line: 181, column: 15, scope: !188)
!499 = !DILocation(line: 181, column: 18, scope: !188)
!500 = !DILocation(line: 181, column: 24, scope: !328)
!501 = !DILocation(line: 181, column: 15, scope: !328)
!502 = !DILocation(line: 181, column: 60, scope: !423)
!503 = !DILocation(line: 181, column: 64, scope: !423)
!504 = !DILocation(line: 181, column: 53, scope: !423)
!505 = !DILocation(line: 181, column: 15, scope: !423)
!506 = !DILocation(line: 181, column: 15, scope: !507)
!507 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 3)
!508 = !DILocation(line: 181, column: 5, scope: !507)
!509 = !DILocation(line: 181, column: 8, scope: !507)
!510 = !DILocation(line: 181, column: 13, scope: !507)
!511 = !DILocation(line: 183, column: 9, scope: !512)
!512 = distinct !DILexicalBlock(scope: !188, file: !1, line: 183, column: 9)
!513 = !DILocation(line: 183, column: 12, scope: !512)
!514 = !DILocation(line: 183, column: 17, scope: !512)
!515 = !DILocation(line: 183, column: 9, scope: !188)
!516 = !DILocation(line: 184, column: 24, scope: !517)
!517 = distinct !DILexicalBlock(scope: !512, file: !1, line: 183, column: 26)
!518 = !DILocation(line: 184, column: 16, scope: !517)
!519 = !DILocation(line: 184, column: 9, scope: !517)
!520 = !DILocation(line: 186, column: 9, scope: !521)
!521 = distinct !DILexicalBlock(scope: !188, file: !1, line: 186, column: 9)
!522 = !DILocation(line: 186, column: 12, scope: !521)
!523 = !DILocation(line: 186, column: 17, scope: !521)
!524 = !DILocation(line: 186, column: 9, scope: !188)
!525 = !DILocation(line: 189, column: 17, scope: !526)
!526 = distinct !DILexicalBlock(scope: !521, file: !1, line: 186, column: 25)
!527 = !DILocation(line: 189, column: 20, scope: !526)
!528 = !DILocation(line: 189, column: 50, scope: !526)
!529 = !DILocation(line: 189, column: 63, scope: !526)
!530 = !DILocation(line: 189, column: 9, scope: !526)
!531 = !DILocation(line: 191, column: 9, scope: !526)
!532 = !DILocation(line: 191, column: 12, scope: !526)
!533 = !DILocation(line: 191, column: 18, scope: !526)
!534 = !DILocation(line: 197, column: 5, scope: !526)
!535 = !DILocation(line: 198, column: 22, scope: !536)
!536 = distinct !DILexicalBlock(scope: !521, file: !1, line: 197, column: 12)
!537 = !DILocation(line: 198, column: 9, scope: !536)
!538 = !DILocation(line: 199, column: 26, scope: !536)
!539 = !DILocation(line: 199, column: 29, scope: !536)
!540 = !DILocation(line: 199, column: 20, scope: !536)
!541 = !DILocation(line: 199, column: 37, scope: !536)
!542 = !DILocation(line: 199, column: 40, scope: !536)
!543 = !DILocation(line: 199, column: 47, scope: !536)
!544 = !DILocation(line: 199, column: 35, scope: !536)
!545 = !DILocation(line: 199, column: 9, scope: !536)
!546 = !DILocation(line: 199, column: 12, scope: !536)
!547 = !DILocation(line: 199, column: 18, scope: !536)
!548 = !DILocation(line: 202, column: 20, scope: !188)
!549 = !DILocation(line: 202, column: 12, scope: !188)
!550 = !DILocation(line: 202, column: 5, scope: !188)
!551 = !DILocation(line: 203, column: 1, scope: !188)
!552 = !DILocalVariable(name: "fd", arg: 1, scope: !137, file: !1, line: 220, type: !39)
!553 = !DILocation(line: 220, column: 9, scope: !137)
!554 = !DILocalVariable(name: "mode", arg: 2, scope: !137, file: !1, line: 221, type: !131)
!555 = !DILocation(line: 221, column: 17, scope: !137)
!556 = !DILocalVariable(name: "name", scope: !137, file: !1, line: 223, type: !557)
!557 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 368, align: 8, elements: !558)
!558 = !{!559}
!559 = !DISubrange(count: 46)
!560 = !DILocation(line: 223, column: 10, scope: !137)
!561 = !DILocation(line: 225, column: 9, scope: !562)
!562 = distinct !DILexicalBlock(scope: !137, file: !1, line: 225, column: 9)
!563 = !DILocation(line: 225, column: 12, scope: !562)
!564 = !DILocation(line: 225, column: 9, scope: !137)
!565 = !DILocation(line: 225, column: 17, scope: !566)
!566 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 1)
!567 = !DILocation(line: 226, column: 13, scope: !137)
!568 = !DILocation(line: 226, column: 30, scope: !137)
!569 = !DILocation(line: 226, column: 5, scope: !137)
!570 = !DILocation(line: 228, column: 21, scope: !137)
!571 = !DILocation(line: 228, column: 27, scope: !137)
!572 = !DILocation(line: 228, column: 33, scope: !137)
!573 = !DILocation(line: 228, column: 12, scope: !137)
!574 = !DILocation(line: 228, column: 5, scope: !137)
!575 = !DILocation(line: 229, column: 1, scope: !137)
!576 = !DILocalVariable(name: "file", arg: 1, scope: !140, file: !1, line: 235, type: !4)
!577 = !DILocation(line: 235, column: 12, scope: !140)
!578 = !DILocalVariable(name: "level", arg: 2, scope: !140, file: !1, line: 236, type: !39)
!579 = !DILocation(line: 236, column: 9, scope: !140)
!580 = !DILocalVariable(name: "strategy", arg: 3, scope: !140, file: !1, line: 237, type: !39)
!581 = !DILocation(line: 237, column: 9, scope: !140)
!582 = !DILocalVariable(name: "s", scope: !140, file: !1, line: 239, type: !9)
!583 = !DILocation(line: 239, column: 16, scope: !140)
!584 = !DILocation(line: 239, column: 32, scope: !140)
!585 = !DILocation(line: 239, column: 20, scope: !140)
!586 = !DILocation(line: 241, column: 9, scope: !587)
!587 = distinct !DILexicalBlock(scope: !140, file: !1, line: 241, column: 9)
!588 = !DILocation(line: 241, column: 11, scope: !587)
!589 = !DILocation(line: 241, column: 19, scope: !587)
!590 = !DILocation(line: 241, column: 22, scope: !591)
!591 = !DILexicalBlockFile(scope: !587, file: !1, discriminator: 1)
!592 = !DILocation(line: 241, column: 25, scope: !591)
!593 = !DILocation(line: 241, column: 30, scope: !591)
!594 = !DILocation(line: 241, column: 9, scope: !591)
!595 = !DILocation(line: 241, column: 38, scope: !596)
!596 = !DILexicalBlockFile(scope: !587, file: !1, discriminator: 2)
!597 = !DILocation(line: 244, column: 9, scope: !598)
!598 = distinct !DILexicalBlock(scope: !140, file: !1, line: 244, column: 9)
!599 = !DILocation(line: 244, column: 12, scope: !598)
!600 = !DILocation(line: 244, column: 19, scope: !598)
!601 = !DILocation(line: 244, column: 29, scope: !598)
!602 = !DILocation(line: 244, column: 9, scope: !140)
!603 = !DILocation(line: 246, column: 30, scope: !604)
!604 = distinct !DILexicalBlock(scope: !598, file: !1, line: 244, column: 35)
!605 = !DILocation(line: 246, column: 33, scope: !604)
!606 = !DILocation(line: 246, column: 9, scope: !604)
!607 = !DILocation(line: 246, column: 12, scope: !604)
!608 = !DILocation(line: 246, column: 19, scope: !604)
!609 = !DILocation(line: 246, column: 28, scope: !604)
!610 = !DILocation(line: 247, column: 20, scope: !611)
!611 = distinct !DILexicalBlock(scope: !604, file: !1, line: 247, column: 13)
!612 = !DILocation(line: 247, column: 23, scope: !611)
!613 = !DILocation(line: 247, column: 45, scope: !611)
!614 = !DILocation(line: 247, column: 48, scope: !611)
!615 = !DILocation(line: 247, column: 13, scope: !611)
!616 = !DILocation(line: 247, column: 54, scope: !611)
!617 = !DILocation(line: 247, column: 13, scope: !604)
!618 = !DILocation(line: 248, column: 13, scope: !619)
!619 = distinct !DILexicalBlock(scope: !611, file: !1, line: 247, column: 68)
!620 = !DILocation(line: 248, column: 16, scope: !619)
!621 = !DILocation(line: 248, column: 22, scope: !619)
!622 = !DILocation(line: 249, column: 9, scope: !619)
!623 = !DILocation(line: 250, column: 9, scope: !604)
!624 = !DILocation(line: 250, column: 12, scope: !604)
!625 = !DILocation(line: 250, column: 19, scope: !604)
!626 = !DILocation(line: 250, column: 29, scope: !604)
!627 = !DILocation(line: 251, column: 5, scope: !604)
!628 = !DILocation(line: 253, column: 29, scope: !140)
!629 = !DILocation(line: 253, column: 32, scope: !140)
!630 = !DILocation(line: 253, column: 41, scope: !140)
!631 = !DILocation(line: 253, column: 48, scope: !140)
!632 = !DILocation(line: 253, column: 12, scope: !140)
!633 = !DILocation(line: 253, column: 5, scope: !140)
!634 = !DILocation(line: 254, column: 1, scope: !140)
!635 = !DILocalVariable(name: "file", arg: 1, scope: !143, file: !1, line: 395, type: !4)
!636 = !DILocation(line: 395, column: 12, scope: !143)
!637 = !DILocalVariable(name: "buf", arg: 2, scope: !143, file: !1, line: 396, type: !6)
!638 = !DILocation(line: 396, column: 11, scope: !143)
!639 = !DILocalVariable(name: "len", arg: 3, scope: !143, file: !1, line: 397, type: !24)
!640 = !DILocation(line: 397, column: 14, scope: !143)
!641 = !DILocalVariable(name: "s", scope: !143, file: !1, line: 399, type: !9)
!642 = !DILocation(line: 399, column: 16, scope: !143)
!643 = !DILocation(line: 399, column: 32, scope: !143)
!644 = !DILocation(line: 399, column: 20, scope: !143)
!645 = !DILocalVariable(name: "start", scope: !143, file: !1, line: 400, type: !18)
!646 = !DILocation(line: 400, column: 12, scope: !143)
!647 = !DILocation(line: 400, column: 28, scope: !143)
!648 = !DILocalVariable(name: "next_out", scope: !143, file: !1, line: 401, type: !117)
!649 = !DILocation(line: 401, column: 12, scope: !143)
!650 = !DILocation(line: 403, column: 9, scope: !651)
!651 = distinct !DILexicalBlock(scope: !143, file: !1, line: 403, column: 9)
!652 = !DILocation(line: 403, column: 11, scope: !651)
!653 = !DILocation(line: 403, column: 19, scope: !651)
!654 = !DILocation(line: 403, column: 22, scope: !655)
!655 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 1)
!656 = !DILocation(line: 403, column: 25, scope: !655)
!657 = !DILocation(line: 403, column: 30, scope: !655)
!658 = !DILocation(line: 403, column: 9, scope: !655)
!659 = !DILocation(line: 403, column: 38, scope: !660)
!660 = !DILexicalBlockFile(scope: !651, file: !1, discriminator: 2)
!661 = !DILocation(line: 405, column: 9, scope: !662)
!662 = distinct !DILexicalBlock(scope: !143, file: !1, line: 405, column: 9)
!663 = !DILocation(line: 405, column: 12, scope: !662)
!664 = !DILocation(line: 405, column: 18, scope: !662)
!665 = !DILocation(line: 405, column: 34, scope: !662)
!666 = !DILocation(line: 405, column: 37, scope: !667)
!667 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 1)
!668 = !DILocation(line: 405, column: 40, scope: !667)
!669 = !DILocation(line: 405, column: 46, scope: !667)
!670 = !DILocation(line: 405, column: 9, scope: !667)
!671 = !DILocation(line: 405, column: 58, scope: !672)
!672 = !DILexicalBlockFile(scope: !662, file: !1, discriminator: 2)
!673 = !DILocation(line: 406, column: 9, scope: !674)
!674 = distinct !DILexicalBlock(scope: !143, file: !1, line: 406, column: 9)
!675 = !DILocation(line: 406, column: 12, scope: !674)
!676 = !DILocation(line: 406, column: 18, scope: !674)
!677 = !DILocation(line: 406, column: 9, scope: !143)
!678 = !DILocation(line: 406, column: 35, scope: !679)
!679 = !DILexicalBlockFile(scope: !674, file: !1, discriminator: 1)
!680 = !DILocation(line: 408, column: 23, scope: !143)
!681 = !DILocation(line: 408, column: 14, scope: !143)
!682 = !DILocation(line: 409, column: 34, scope: !143)
!683 = !DILocation(line: 409, column: 5, scope: !143)
!684 = !DILocation(line: 409, column: 8, scope: !143)
!685 = !DILocation(line: 409, column: 15, scope: !143)
!686 = !DILocation(line: 409, column: 24, scope: !143)
!687 = !DILocation(line: 410, column: 27, scope: !143)
!688 = !DILocation(line: 410, column: 5, scope: !143)
!689 = !DILocation(line: 410, column: 8, scope: !143)
!690 = !DILocation(line: 410, column: 15, scope: !143)
!691 = !DILocation(line: 410, column: 25, scope: !143)
!692 = !DILocation(line: 412, column: 9, scope: !693)
!693 = distinct !DILexicalBlock(scope: !143, file: !1, line: 412, column: 9)
!694 = !DILocation(line: 412, column: 12, scope: !693)
!695 = !DILocation(line: 412, column: 19, scope: !693)
!696 = !DILocation(line: 412, column: 29, scope: !693)
!697 = !DILocation(line: 412, column: 32, scope: !698)
!698 = !DILexicalBlockFile(scope: !693, file: !1, discriminator: 1)
!699 = !DILocation(line: 412, column: 35, scope: !698)
!700 = !DILocation(line: 412, column: 40, scope: !698)
!701 = !DILocation(line: 412, column: 9, scope: !698)
!702 = !DILocation(line: 413, column: 23, scope: !703)
!703 = distinct !DILexicalBlock(scope: !693, file: !1, line: 412, column: 48)
!704 = !DILocation(line: 413, column: 26, scope: !703)
!705 = !DILocation(line: 413, column: 18, scope: !703)
!706 = !DILocation(line: 413, column: 21, scope: !703)
!707 = !DILocation(line: 414, column: 9, scope: !703)
!708 = !DILocation(line: 414, column: 12, scope: !703)
!709 = !DILocation(line: 414, column: 19, scope: !703)
!710 = !DILocation(line: 414, column: 27, scope: !703)
!711 = !DILocation(line: 415, column: 9, scope: !703)
!712 = !DILocation(line: 415, column: 12, scope: !703)
!713 = !DILocation(line: 415, column: 19, scope: !703)
!714 = !DILocation(line: 415, column: 28, scope: !703)
!715 = !DILocation(line: 416, column: 9, scope: !703)
!716 = !DILocation(line: 416, column: 12, scope: !703)
!717 = !DILocation(line: 416, column: 17, scope: !703)
!718 = !DILocation(line: 417, column: 9, scope: !703)
!719 = !DILocation(line: 417, column: 12, scope: !703)
!720 = !DILocation(line: 417, column: 15, scope: !703)
!721 = !DILocation(line: 418, column: 14, scope: !703)
!722 = !DILocation(line: 419, column: 13, scope: !723)
!723 = distinct !DILexicalBlock(scope: !703, file: !1, line: 419, column: 13)
!724 = !DILocation(line: 419, column: 16, scope: !723)
!725 = !DILocation(line: 419, column: 13, scope: !703)
!726 = !DILocation(line: 420, column: 13, scope: !727)
!727 = distinct !DILexicalBlock(scope: !723, file: !1, line: 419, column: 22)
!728 = !DILocation(line: 420, column: 16, scope: !727)
!729 = !DILocation(line: 420, column: 22, scope: !727)
!730 = !DILocation(line: 421, column: 13, scope: !727)
!731 = !DILocation(line: 423, column: 5, scope: !703)
!732 = !DILocation(line: 425, column: 5, scope: !143)
!733 = !DILocation(line: 425, column: 12, scope: !734)
!734 = !DILexicalBlockFile(scope: !143, file: !1, discriminator: 1)
!735 = !DILocation(line: 425, column: 15, scope: !734)
!736 = !DILocation(line: 425, column: 22, scope: !734)
!737 = !DILocation(line: 425, column: 32, scope: !734)
!738 = !DILocation(line: 425, column: 5, scope: !734)
!739 = !DILocation(line: 427, column: 13, scope: !740)
!740 = distinct !DILexicalBlock(scope: !741, file: !1, line: 427, column: 13)
!741 = distinct !DILexicalBlock(scope: !143, file: !1, line: 425, column: 38)
!742 = !DILocation(line: 427, column: 16, scope: !740)
!743 = !DILocation(line: 427, column: 13, scope: !741)
!744 = !DILocalVariable(name: "n", scope: !745, file: !1, line: 429, type: !23)
!745 = distinct !DILexicalBlock(scope: !740, file: !1, line: 427, column: 29)
!746 = !DILocation(line: 429, column: 18, scope: !745)
!747 = !DILocation(line: 429, column: 22, scope: !745)
!748 = !DILocation(line: 429, column: 25, scope: !745)
!749 = !DILocation(line: 429, column: 32, scope: !745)
!750 = !DILocation(line: 430, column: 17, scope: !751)
!751 = distinct !DILexicalBlock(scope: !745, file: !1, line: 430, column: 17)
!752 = !DILocation(line: 430, column: 21, scope: !751)
!753 = !DILocation(line: 430, column: 24, scope: !751)
!754 = !DILocation(line: 430, column: 31, scope: !751)
!755 = !DILocation(line: 430, column: 19, scope: !751)
!756 = !DILocation(line: 430, column: 17, scope: !745)
!757 = !DILocation(line: 430, column: 46, scope: !758)
!758 = !DILexicalBlockFile(scope: !751, file: !1, discriminator: 1)
!759 = !DILocation(line: 430, column: 49, scope: !758)
!760 = !DILocation(line: 430, column: 56, scope: !758)
!761 = !DILocation(line: 430, column: 44, scope: !758)
!762 = !DILocation(line: 430, column: 42, scope: !758)
!763 = !DILocation(line: 431, column: 17, scope: !764)
!764 = distinct !DILexicalBlock(scope: !745, file: !1, line: 431, column: 17)
!765 = !DILocation(line: 431, column: 19, scope: !764)
!766 = !DILocation(line: 431, column: 17, scope: !745)
!767 = !DILocation(line: 432, column: 25, scope: !768)
!768 = distinct !DILexicalBlock(scope: !764, file: !1, line: 431, column: 24)
!769 = !DILocation(line: 432, column: 28, scope: !768)
!770 = !DILocation(line: 432, column: 35, scope: !768)
!771 = !DILocation(line: 432, column: 45, scope: !768)
!772 = !DILocation(line: 432, column: 48, scope: !768)
!773 = !DILocation(line: 432, column: 55, scope: !768)
!774 = !DILocation(line: 432, column: 64, scope: !768)
!775 = !DILocation(line: 432, column: 17, scope: !768)
!776 = !DILocation(line: 433, column: 29, scope: !768)
!777 = !DILocation(line: 433, column: 26, scope: !768)
!778 = !DILocation(line: 434, column: 38, scope: !768)
!779 = !DILocation(line: 434, column: 17, scope: !768)
!780 = !DILocation(line: 434, column: 20, scope: !768)
!781 = !DILocation(line: 434, column: 27, scope: !768)
!782 = !DILocation(line: 434, column: 36, scope: !768)
!783 = !DILocation(line: 435, column: 40, scope: !768)
!784 = !DILocation(line: 435, column: 17, scope: !768)
!785 = !DILocation(line: 435, column: 20, scope: !768)
!786 = !DILocation(line: 435, column: 27, scope: !768)
!787 = !DILocation(line: 435, column: 37, scope: !768)
!788 = !DILocation(line: 436, column: 40, scope: !768)
!789 = !DILocation(line: 436, column: 17, scope: !768)
!790 = !DILocation(line: 436, column: 20, scope: !768)
!791 = !DILocation(line: 436, column: 27, scope: !768)
!792 = !DILocation(line: 436, column: 37, scope: !768)
!793 = !DILocation(line: 437, column: 40, scope: !768)
!794 = !DILocation(line: 437, column: 17, scope: !768)
!795 = !DILocation(line: 437, column: 20, scope: !768)
!796 = !DILocation(line: 437, column: 27, scope: !768)
!797 = !DILocation(line: 437, column: 37, scope: !768)
!798 = !DILocation(line: 438, column: 13, scope: !768)
!799 = !DILocation(line: 439, column: 17, scope: !800)
!800 = distinct !DILexicalBlock(scope: !745, file: !1, line: 439, column: 17)
!801 = !DILocation(line: 439, column: 20, scope: !800)
!802 = !DILocation(line: 439, column: 27, scope: !800)
!803 = !DILocation(line: 439, column: 37, scope: !800)
!804 = !DILocation(line: 439, column: 17, scope: !745)
!805 = !DILocation(line: 441, column: 33, scope: !806)
!806 = distinct !DILexicalBlock(scope: !800, file: !1, line: 439, column: 42)
!807 = !DILocation(line: 441, column: 46, scope: !806)
!808 = !DILocation(line: 441, column: 49, scope: !806)
!809 = !DILocation(line: 441, column: 56, scope: !806)
!810 = !DILocation(line: 441, column: 67, scope: !806)
!811 = !DILocation(line: 441, column: 70, scope: !806)
!812 = !DILocation(line: 441, column: 27, scope: !806)
!813 = !DILocation(line: 441, column: 21, scope: !806)
!814 = !DILocation(line: 440, column: 17, scope: !806)
!815 = !DILocation(line: 440, column: 20, scope: !806)
!816 = !DILocation(line: 440, column: 27, scope: !806)
!817 = !DILocation(line: 440, column: 37, scope: !806)
!818 = !DILocation(line: 442, column: 13, scope: !806)
!819 = !DILocation(line: 443, column: 20, scope: !745)
!820 = !DILocation(line: 443, column: 23, scope: !745)
!821 = !DILocation(line: 443, column: 30, scope: !745)
!822 = !DILocation(line: 443, column: 17, scope: !745)
!823 = !DILocation(line: 444, column: 23, scope: !745)
!824 = !DILocation(line: 444, column: 13, scope: !745)
!825 = !DILocation(line: 444, column: 16, scope: !745)
!826 = !DILocation(line: 444, column: 20, scope: !745)
!827 = !DILocation(line: 445, column: 23, scope: !745)
!828 = !DILocation(line: 445, column: 13, scope: !745)
!829 = !DILocation(line: 445, column: 16, scope: !745)
!830 = !DILocation(line: 445, column: 20, scope: !745)
!831 = !DILocation(line: 446, column: 17, scope: !832)
!832 = distinct !DILexicalBlock(scope: !745, file: !1, line: 446, column: 17)
!833 = !DILocation(line: 446, column: 21, scope: !832)
!834 = !DILocation(line: 446, column: 17, scope: !745)
!835 = !DILocation(line: 446, column: 27, scope: !836)
!836 = !DILexicalBlockFile(scope: !832, file: !1, discriminator: 1)
!837 = !DILocation(line: 446, column: 30, scope: !836)
!838 = !DILocation(line: 446, column: 36, scope: !836)
!839 = !DILocation(line: 447, column: 25, scope: !745)
!840 = !DILocation(line: 447, column: 13, scope: !745)
!841 = !DILocation(line: 449, column: 13, scope: !842)
!842 = distinct !DILexicalBlock(scope: !741, file: !1, line: 449, column: 13)
!843 = !DILocation(line: 449, column: 16, scope: !842)
!844 = !DILocation(line: 449, column: 23, scope: !842)
!845 = !DILocation(line: 449, column: 32, scope: !842)
!846 = !DILocation(line: 449, column: 37, scope: !842)
!847 = !DILocation(line: 449, column: 41, scope: !848)
!848 = !DILexicalBlockFile(scope: !842, file: !1, discriminator: 1)
!849 = !DILocation(line: 449, column: 44, scope: !848)
!850 = !DILocation(line: 449, column: 13, scope: !848)
!851 = !DILocation(line: 451, column: 13, scope: !852)
!852 = distinct !DILexicalBlock(scope: !842, file: !1, line: 449, column: 51)
!853 = !DILocation(line: 451, column: 19, scope: !852)
!854 = !DILocation(line: 452, column: 46, scope: !852)
!855 = !DILocation(line: 452, column: 49, scope: !852)
!856 = !DILocation(line: 452, column: 70, scope: !852)
!857 = !DILocation(line: 452, column: 73, scope: !852)
!858 = !DILocation(line: 452, column: 40, scope: !852)
!859 = !DILocation(line: 452, column: 34, scope: !852)
!860 = !DILocation(line: 452, column: 13, scope: !852)
!861 = !DILocation(line: 452, column: 16, scope: !852)
!862 = !DILocation(line: 452, column: 23, scope: !852)
!863 = !DILocation(line: 452, column: 32, scope: !852)
!864 = !DILocation(line: 453, column: 17, scope: !865)
!865 = distinct !DILexicalBlock(scope: !852, file: !1, line: 453, column: 17)
!866 = !DILocation(line: 453, column: 20, scope: !865)
!867 = !DILocation(line: 453, column: 27, scope: !865)
!868 = !DILocation(line: 453, column: 36, scope: !865)
!869 = !DILocation(line: 453, column: 17, scope: !852)
!870 = !DILocation(line: 454, column: 17, scope: !871)
!871 = distinct !DILexicalBlock(scope: !865, file: !1, line: 453, column: 42)
!872 = !DILocation(line: 454, column: 20, scope: !871)
!873 = !DILocation(line: 454, column: 26, scope: !871)
!874 = !DILocation(line: 455, column: 28, scope: !875)
!875 = distinct !DILexicalBlock(scope: !871, file: !1, line: 455, column: 21)
!876 = !DILocation(line: 455, column: 31, scope: !875)
!877 = !DILocation(line: 455, column: 21, scope: !875)
!878 = !DILocation(line: 455, column: 21, scope: !871)
!879 = !DILocation(line: 456, column: 21, scope: !880)
!880 = distinct !DILexicalBlock(scope: !875, file: !1, line: 455, column: 38)
!881 = !DILocation(line: 456, column: 24, scope: !880)
!882 = !DILocation(line: 456, column: 30, scope: !880)
!883 = !DILocation(line: 457, column: 21, scope: !880)
!884 = !DILocation(line: 459, column: 13, scope: !871)
!885 = !DILocation(line: 460, column: 33, scope: !852)
!886 = !DILocation(line: 460, column: 36, scope: !852)
!887 = !DILocation(line: 460, column: 13, scope: !852)
!888 = !DILocation(line: 460, column: 16, scope: !852)
!889 = !DILocation(line: 460, column: 23, scope: !852)
!890 = !DILocation(line: 460, column: 31, scope: !852)
!891 = !DILocation(line: 461, column: 9, scope: !852)
!892 = !DILocation(line: 462, column: 18, scope: !741)
!893 = !DILocation(line: 462, column: 21, scope: !741)
!894 = !DILocation(line: 462, column: 28, scope: !741)
!895 = !DILocation(line: 462, column: 9, scope: !741)
!896 = !DILocation(line: 462, column: 12, scope: !741)
!897 = !DILocation(line: 462, column: 15, scope: !741)
!898 = !DILocation(line: 463, column: 19, scope: !741)
!899 = !DILocation(line: 463, column: 22, scope: !741)
!900 = !DILocation(line: 463, column: 29, scope: !741)
!901 = !DILocation(line: 463, column: 9, scope: !741)
!902 = !DILocation(line: 463, column: 12, scope: !741)
!903 = !DILocation(line: 463, column: 16, scope: !741)
!904 = !DILocation(line: 464, column: 30, scope: !741)
!905 = !DILocation(line: 464, column: 33, scope: !741)
!906 = !DILocation(line: 464, column: 20, scope: !741)
!907 = !DILocation(line: 464, column: 9, scope: !741)
!908 = !DILocation(line: 464, column: 12, scope: !741)
!909 = !DILocation(line: 464, column: 18, scope: !741)
!910 = !DILocation(line: 465, column: 18, scope: !741)
!911 = !DILocation(line: 465, column: 21, scope: !741)
!912 = !DILocation(line: 465, column: 28, scope: !741)
!913 = !DILocation(line: 465, column: 9, scope: !741)
!914 = !DILocation(line: 465, column: 12, scope: !741)
!915 = !DILocation(line: 465, column: 15, scope: !741)
!916 = !DILocation(line: 466, column: 19, scope: !741)
!917 = !DILocation(line: 466, column: 22, scope: !741)
!918 = !DILocation(line: 466, column: 29, scope: !741)
!919 = !DILocation(line: 466, column: 9, scope: !741)
!920 = !DILocation(line: 466, column: 12, scope: !741)
!921 = !DILocation(line: 466, column: 16, scope: !741)
!922 = !DILocation(line: 468, column: 13, scope: !923)
!923 = distinct !DILexicalBlock(scope: !741, file: !1, line: 468, column: 13)
!924 = !DILocation(line: 468, column: 16, scope: !923)
!925 = !DILocation(line: 468, column: 22, scope: !923)
!926 = !DILocation(line: 468, column: 13, scope: !741)
!927 = !DILocation(line: 470, column: 28, scope: !928)
!928 = distinct !DILexicalBlock(scope: !923, file: !1, line: 468, column: 39)
!929 = !DILocation(line: 470, column: 31, scope: !928)
!930 = !DILocation(line: 470, column: 36, scope: !928)
!931 = !DILocation(line: 470, column: 50, scope: !928)
!932 = !DILocation(line: 470, column: 53, scope: !928)
!933 = !DILocation(line: 470, column: 60, scope: !928)
!934 = !DILocation(line: 470, column: 71, scope: !928)
!935 = !DILocation(line: 470, column: 69, scope: !928)
!936 = !DILocation(line: 470, column: 43, scope: !928)
!937 = !DILocation(line: 470, column: 22, scope: !928)
!938 = !DILocation(line: 470, column: 13, scope: !928)
!939 = !DILocation(line: 470, column: 16, scope: !928)
!940 = !DILocation(line: 470, column: 20, scope: !928)
!941 = !DILocation(line: 471, column: 21, scope: !928)
!942 = !DILocation(line: 471, column: 24, scope: !928)
!943 = !DILocation(line: 471, column: 31, scope: !928)
!944 = !DILocation(line: 471, column: 19, scope: !928)
!945 = !DILocation(line: 473, column: 25, scope: !946)
!946 = distinct !DILexicalBlock(scope: !928, file: !1, line: 473, column: 17)
!947 = !DILocation(line: 473, column: 17, scope: !946)
!948 = !DILocation(line: 473, column: 31, scope: !946)
!949 = !DILocation(line: 473, column: 34, scope: !946)
!950 = !DILocation(line: 473, column: 28, scope: !946)
!951 = !DILocation(line: 473, column: 17, scope: !928)
!952 = !DILocation(line: 474, column: 17, scope: !953)
!953 = distinct !DILexicalBlock(scope: !946, file: !1, line: 473, column: 39)
!954 = !DILocation(line: 474, column: 20, scope: !953)
!955 = !DILocation(line: 474, column: 26, scope: !953)
!956 = !DILocation(line: 475, column: 13, scope: !953)
!957 = !DILocation(line: 476, column: 31, scope: !958)
!958 = distinct !DILexicalBlock(scope: !946, file: !1, line: 475, column: 20)
!959 = !DILocation(line: 476, column: 23, scope: !958)
!960 = !DILocation(line: 481, column: 30, scope: !958)
!961 = !DILocation(line: 481, column: 17, scope: !958)
!962 = !DILocation(line: 482, column: 21, scope: !963)
!963 = distinct !DILexicalBlock(scope: !958, file: !1, line: 482, column: 21)
!964 = !DILocation(line: 482, column: 24, scope: !963)
!965 = !DILocation(line: 482, column: 30, scope: !963)
!966 = !DILocation(line: 482, column: 21, scope: !958)
!967 = !DILocation(line: 483, column: 36, scope: !968)
!968 = distinct !DILexicalBlock(scope: !963, file: !1, line: 482, column: 39)
!969 = !DILocation(line: 483, column: 39, scope: !968)
!970 = !DILocation(line: 483, column: 21, scope: !968)
!971 = !DILocation(line: 484, column: 30, scope: !968)
!972 = !DILocation(line: 484, column: 21, scope: !968)
!973 = !DILocation(line: 484, column: 24, scope: !968)
!974 = !DILocation(line: 484, column: 28, scope: !968)
!975 = !DILocation(line: 485, column: 17, scope: !968)
!976 = !DILocation(line: 487, column: 9, scope: !928)
!977 = !DILocation(line: 488, column: 13, scope: !978)
!978 = distinct !DILexicalBlock(scope: !741, file: !1, line: 488, column: 13)
!979 = !DILocation(line: 488, column: 16, scope: !978)
!980 = !DILocation(line: 488, column: 22, scope: !978)
!981 = !DILocation(line: 488, column: 30, scope: !978)
!982 = !DILocation(line: 488, column: 33, scope: !983)
!983 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 1)
!984 = !DILocation(line: 488, column: 36, scope: !983)
!985 = !DILocation(line: 488, column: 13, scope: !983)
!986 = !DILocation(line: 488, column: 43, scope: !987)
!987 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 2)
!988 = !DILocation(line: 425, column: 5, scope: !989)
!989 = !DILexicalBlockFile(scope: !143, file: !1, discriminator: 2)
!990 = !DILocation(line: 490, column: 20, scope: !143)
!991 = !DILocation(line: 490, column: 23, scope: !143)
!992 = !DILocation(line: 490, column: 28, scope: !143)
!993 = !DILocation(line: 490, column: 42, scope: !143)
!994 = !DILocation(line: 490, column: 45, scope: !143)
!995 = !DILocation(line: 490, column: 52, scope: !143)
!996 = !DILocation(line: 490, column: 63, scope: !143)
!997 = !DILocation(line: 490, column: 61, scope: !143)
!998 = !DILocation(line: 490, column: 35, scope: !143)
!999 = !DILocation(line: 490, column: 14, scope: !143)
!1000 = !DILocation(line: 490, column: 5, scope: !143)
!1001 = !DILocation(line: 490, column: 8, scope: !143)
!1002 = !DILocation(line: 490, column: 12, scope: !143)
!1003 = !DILocation(line: 492, column: 9, scope: !1004)
!1004 = distinct !DILexicalBlock(scope: !143, file: !1, line: 492, column: 9)
!1005 = !DILocation(line: 492, column: 16, scope: !1004)
!1006 = !DILocation(line: 492, column: 19, scope: !1004)
!1007 = !DILocation(line: 492, column: 26, scope: !1004)
!1008 = !DILocation(line: 492, column: 13, scope: !1004)
!1009 = !DILocation(line: 492, column: 36, scope: !1004)
!1010 = !DILocation(line: 493, column: 10, scope: !1004)
!1011 = !DILocation(line: 493, column: 13, scope: !1004)
!1012 = !DILocation(line: 493, column: 19, scope: !1004)
!1013 = !DILocation(line: 493, column: 35, scope: !1004)
!1014 = !DILocation(line: 493, column: 38, scope: !1015)
!1015 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 1)
!1016 = !DILocation(line: 493, column: 41, scope: !1015)
!1017 = !DILocation(line: 493, column: 47, scope: !1015)
!1018 = !DILocation(line: 492, column: 9, scope: !734)
!1019 = !DILocation(line: 494, column: 9, scope: !1004)
!1020 = !DILocation(line: 495, column: 18, scope: !143)
!1021 = !DILocation(line: 495, column: 24, scope: !143)
!1022 = !DILocation(line: 495, column: 27, scope: !143)
!1023 = !DILocation(line: 495, column: 34, scope: !143)
!1024 = !DILocation(line: 495, column: 22, scope: !143)
!1025 = !DILocation(line: 495, column: 5, scope: !143)
!1026 = !DILocation(line: 496, column: 1, scope: !143)
!1027 = !DILocalVariable(name: "s", arg: 1, scope: !198, file: !1, line: 936, type: !9)
!1028 = !DILocation(line: 936, column: 16, scope: !198)
!1029 = !DILocalVariable(name: "x", scope: !198, file: !1, line: 938, type: !26)
!1030 = !DILocation(line: 938, column: 11, scope: !198)
!1031 = !DILocation(line: 938, column: 31, scope: !198)
!1032 = !DILocation(line: 938, column: 22, scope: !198)
!1033 = !DILocation(line: 938, column: 15, scope: !198)
!1034 = !DILocalVariable(name: "c", scope: !198, file: !1, line: 939, type: !39)
!1035 = !DILocation(line: 939, column: 9, scope: !198)
!1036 = !DILocation(line: 941, column: 27, scope: !198)
!1037 = !DILocation(line: 941, column: 18, scope: !198)
!1038 = !DILocation(line: 941, column: 11, scope: !198)
!1039 = !DILocation(line: 941, column: 30, scope: !198)
!1040 = !DILocation(line: 941, column: 7, scope: !198)
!1041 = !DILocation(line: 942, column: 27, scope: !198)
!1042 = !DILocation(line: 942, column: 18, scope: !198)
!1043 = !DILocation(line: 942, column: 11, scope: !198)
!1044 = !DILocation(line: 942, column: 30, scope: !198)
!1045 = !DILocation(line: 942, column: 7, scope: !198)
!1046 = !DILocation(line: 943, column: 18, scope: !198)
!1047 = !DILocation(line: 943, column: 9, scope: !198)
!1048 = !DILocation(line: 943, column: 7, scope: !198)
!1049 = !DILocation(line: 944, column: 9, scope: !1050)
!1050 = distinct !DILexicalBlock(scope: !198, file: !1, line: 944, column: 9)
!1051 = !DILocation(line: 944, column: 11, scope: !1050)
!1052 = !DILocation(line: 944, column: 9, scope: !198)
!1053 = !DILocation(line: 944, column: 19, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 1)
!1055 = !DILocation(line: 944, column: 22, scope: !1054)
!1056 = !DILocation(line: 944, column: 28, scope: !1054)
!1057 = !DILocation(line: 945, column: 18, scope: !198)
!1058 = !DILocation(line: 945, column: 11, scope: !198)
!1059 = !DILocation(line: 945, column: 20, scope: !198)
!1060 = !DILocation(line: 945, column: 7, scope: !198)
!1061 = !DILocation(line: 946, column: 12, scope: !198)
!1062 = !DILocation(line: 946, column: 5, scope: !198)
!1063 = !DILocalVariable(name: "s", arg: 1, scope: !191, file: !1, line: 289, type: !9)
!1064 = !DILocation(line: 289, column: 16, scope: !191)
!1065 = !DILocalVariable(name: "method", scope: !191, file: !1, line: 291, type: !39)
!1066 = !DILocation(line: 291, column: 9, scope: !191)
!1067 = !DILocalVariable(name: "flags", scope: !191, file: !1, line: 292, type: !39)
!1068 = !DILocation(line: 292, column: 9, scope: !191)
!1069 = !DILocalVariable(name: "len", scope: !191, file: !1, line: 293, type: !23)
!1070 = !DILocation(line: 293, column: 10, scope: !191)
!1071 = !DILocalVariable(name: "c", scope: !191, file: !1, line: 294, type: !39)
!1072 = !DILocation(line: 294, column: 9, scope: !191)
!1073 = !DILocation(line: 299, column: 11, scope: !191)
!1074 = !DILocation(line: 299, column: 14, scope: !191)
!1075 = !DILocation(line: 299, column: 21, scope: !191)
!1076 = !DILocation(line: 299, column: 9, scope: !191)
!1077 = !DILocation(line: 300, column: 9, scope: !1078)
!1078 = distinct !DILexicalBlock(scope: !191, file: !1, line: 300, column: 9)
!1079 = !DILocation(line: 300, column: 13, scope: !1078)
!1080 = !DILocation(line: 300, column: 9, scope: !191)
!1081 = !DILocation(line: 301, column: 13, scope: !1082)
!1082 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 301, column: 13)
!1083 = distinct !DILexicalBlock(scope: !1078, file: !1, line: 300, column: 18)
!1084 = !DILocation(line: 301, column: 13, scope: !1083)
!1085 = !DILocation(line: 301, column: 32, scope: !1086)
!1086 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 1)
!1087 = !DILocation(line: 301, column: 35, scope: !1086)
!1088 = !DILocation(line: 301, column: 42, scope: !1086)
!1089 = !DILocation(line: 301, column: 18, scope: !1086)
!1090 = !DILocation(line: 301, column: 21, scope: !1086)
!1091 = !DILocation(line: 301, column: 30, scope: !1086)
!1092 = !DILocation(line: 302, column: 9, scope: !1083)
!1093 = !DILocation(line: 302, column: 15, scope: !1083)
!1094 = !DILocation(line: 303, column: 27, scope: !1083)
!1095 = !DILocation(line: 303, column: 30, scope: !1083)
!1096 = !DILocation(line: 303, column: 38, scope: !1083)
!1097 = !DILocation(line: 303, column: 36, scope: !1083)
!1098 = !DILocation(line: 303, column: 59, scope: !1083)
!1099 = !DILocation(line: 303, column: 56, scope: !1083)
!1100 = !DILocation(line: 303, column: 46, scope: !1083)
!1101 = !DILocation(line: 303, column: 64, scope: !1083)
!1102 = !DILocation(line: 303, column: 67, scope: !1083)
!1103 = !DILocation(line: 303, column: 21, scope: !1083)
!1104 = !DILocation(line: 303, column: 15, scope: !1083)
!1105 = !DILocation(line: 303, column: 13, scope: !1083)
!1106 = !DILocation(line: 304, column: 13, scope: !1107)
!1107 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 304, column: 13)
!1108 = !DILocation(line: 304, column: 17, scope: !1107)
!1109 = !DILocation(line: 304, column: 22, scope: !1107)
!1110 = !DILocation(line: 304, column: 32, scope: !1111)
!1111 = !DILexicalBlockFile(scope: !1107, file: !1, discriminator: 1)
!1112 = !DILocation(line: 304, column: 35, scope: !1111)
!1113 = !DILocation(line: 304, column: 25, scope: !1111)
!1114 = !DILocation(line: 304, column: 13, scope: !1111)
!1115 = !DILocation(line: 304, column: 42, scope: !1116)
!1116 = !DILexicalBlockFile(scope: !1107, file: !1, discriminator: 2)
!1117 = !DILocation(line: 304, column: 45, scope: !1116)
!1118 = !DILocation(line: 304, column: 51, scope: !1116)
!1119 = !DILocation(line: 305, column: 31, scope: !1083)
!1120 = !DILocation(line: 305, column: 9, scope: !1083)
!1121 = !DILocation(line: 305, column: 12, scope: !1083)
!1122 = !DILocation(line: 305, column: 19, scope: !1083)
!1123 = !DILocation(line: 305, column: 28, scope: !1083)
!1124 = !DILocation(line: 306, column: 29, scope: !1083)
!1125 = !DILocation(line: 306, column: 32, scope: !1083)
!1126 = !DILocation(line: 306, column: 9, scope: !1083)
!1127 = !DILocation(line: 306, column: 12, scope: !1083)
!1128 = !DILocation(line: 306, column: 19, scope: !1083)
!1129 = !DILocation(line: 306, column: 27, scope: !1083)
!1130 = !DILocation(line: 307, column: 13, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 307, column: 13)
!1132 = !DILocation(line: 307, column: 16, scope: !1131)
!1133 = !DILocation(line: 307, column: 23, scope: !1131)
!1134 = !DILocation(line: 307, column: 32, scope: !1131)
!1135 = !DILocation(line: 307, column: 13, scope: !1083)
!1136 = !DILocation(line: 308, column: 30, scope: !1137)
!1137 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 307, column: 37)
!1138 = !DILocation(line: 308, column: 33, scope: !1137)
!1139 = !DILocation(line: 308, column: 40, scope: !1137)
!1140 = !DILocation(line: 308, column: 13, scope: !1137)
!1141 = !DILocation(line: 308, column: 16, scope: !1137)
!1142 = !DILocation(line: 308, column: 28, scope: !1137)
!1143 = !DILocation(line: 309, column: 13, scope: !1137)
!1144 = !DILocation(line: 311, column: 5, scope: !1083)
!1145 = !DILocation(line: 314, column: 9, scope: !1146)
!1146 = distinct !DILexicalBlock(scope: !191, file: !1, line: 314, column: 9)
!1147 = !DILocation(line: 314, column: 12, scope: !1146)
!1148 = !DILocation(line: 314, column: 19, scope: !1146)
!1149 = !DILocation(line: 314, column: 33, scope: !1146)
!1150 = !DILocation(line: 314, column: 30, scope: !1146)
!1151 = !DILocation(line: 314, column: 45, scope: !1146)
!1152 = !DILocation(line: 315, column: 9, scope: !1146)
!1153 = !DILocation(line: 315, column: 12, scope: !1146)
!1154 = !DILocation(line: 315, column: 19, scope: !1146)
!1155 = !DILocation(line: 315, column: 33, scope: !1146)
!1156 = !DILocation(line: 315, column: 30, scope: !1146)
!1157 = !DILocation(line: 314, column: 9, scope: !1158)
!1158 = !DILexicalBlockFile(scope: !191, file: !1, discriminator: 1)
!1159 = !DILocation(line: 316, column: 9, scope: !1160)
!1160 = distinct !DILexicalBlock(scope: !1146, file: !1, line: 315, column: 46)
!1161 = !DILocation(line: 316, column: 12, scope: !1160)
!1162 = !DILocation(line: 316, column: 24, scope: !1160)
!1163 = !DILocation(line: 317, column: 9, scope: !1160)
!1164 = !DILocation(line: 319, column: 5, scope: !191)
!1165 = !DILocation(line: 319, column: 8, scope: !191)
!1166 = !DILocation(line: 319, column: 15, scope: !191)
!1167 = !DILocation(line: 319, column: 24, scope: !191)
!1168 = !DILocation(line: 320, column: 5, scope: !191)
!1169 = !DILocation(line: 320, column: 8, scope: !191)
!1170 = !DILocation(line: 320, column: 15, scope: !191)
!1171 = !DILocation(line: 320, column: 23, scope: !191)
!1172 = !DILocation(line: 323, column: 23, scope: !191)
!1173 = !DILocation(line: 323, column: 14, scope: !191)
!1174 = !DILocation(line: 323, column: 12, scope: !191)
!1175 = !DILocation(line: 324, column: 22, scope: !191)
!1176 = !DILocation(line: 324, column: 13, scope: !191)
!1177 = !DILocation(line: 324, column: 11, scope: !191)
!1178 = !DILocation(line: 325, column: 9, scope: !1179)
!1179 = distinct !DILexicalBlock(scope: !191, file: !1, line: 325, column: 9)
!1180 = !DILocation(line: 325, column: 16, scope: !1179)
!1181 = !DILocation(line: 325, column: 30, scope: !1179)
!1182 = !DILocation(line: 325, column: 34, scope: !1183)
!1183 = !DILexicalBlockFile(scope: !1179, file: !1, discriminator: 1)
!1184 = !DILocation(line: 325, column: 40, scope: !1183)
!1185 = !DILocation(line: 325, column: 52, scope: !1183)
!1186 = !DILocation(line: 325, column: 9, scope: !1183)
!1187 = !DILocation(line: 326, column: 9, scope: !1188)
!1188 = distinct !DILexicalBlock(scope: !1179, file: !1, line: 325, column: 58)
!1189 = !DILocation(line: 326, column: 12, scope: !1188)
!1190 = !DILocation(line: 326, column: 18, scope: !1188)
!1191 = !DILocation(line: 327, column: 9, scope: !1188)
!1192 = !DILocation(line: 331, column: 14, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !191, file: !1, line: 331, column: 5)
!1194 = !DILocation(line: 331, column: 10, scope: !1193)
!1195 = !DILocation(line: 331, column: 19, scope: !1196)
!1196 = !DILexicalBlockFile(scope: !1197, file: !1, discriminator: 1)
!1197 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 331, column: 5)
!1198 = !DILocation(line: 331, column: 23, scope: !1196)
!1199 = !DILocation(line: 331, column: 5, scope: !1196)
!1200 = !DILocation(line: 331, column: 50, scope: !1201)
!1201 = !DILexicalBlockFile(scope: !1197, file: !1, discriminator: 2)
!1202 = !DILocation(line: 331, column: 41, scope: !1201)
!1203 = !DILocation(line: 331, column: 35, scope: !1201)
!1204 = !DILocation(line: 331, column: 31, scope: !1205)
!1205 = !DILexicalBlockFile(scope: !1197, file: !1, discriminator: 3)
!1206 = !DILocation(line: 331, column: 5, scope: !1205)
!1207 = !DILocation(line: 333, column: 10, scope: !1208)
!1208 = distinct !DILexicalBlock(scope: !191, file: !1, line: 333, column: 9)
!1209 = !DILocation(line: 333, column: 16, scope: !1208)
!1210 = !DILocation(line: 333, column: 31, scope: !1208)
!1211 = !DILocation(line: 333, column: 9, scope: !191)
!1212 = !DILocation(line: 334, column: 32, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1208, file: !1, line: 333, column: 37)
!1214 = !DILocation(line: 334, column: 23, scope: !1213)
!1215 = !DILocation(line: 334, column: 14, scope: !1213)
!1216 = !DILocation(line: 335, column: 32, scope: !1213)
!1217 = !DILocation(line: 335, column: 23, scope: !1213)
!1218 = !DILocation(line: 335, column: 35, scope: !1213)
!1219 = !DILocation(line: 335, column: 13, scope: !1213)
!1220 = !DILocation(line: 337, column: 9, scope: !1213)
!1221 = !DILocation(line: 337, column: 19, scope: !1222)
!1222 = !DILexicalBlockFile(scope: !1213, file: !1, discriminator: 1)
!1223 = !DILocation(line: 337, column: 22, scope: !1222)
!1224 = !DILocation(line: 337, column: 27, scope: !1222)
!1225 = !DILocation(line: 337, column: 39, scope: !1226)
!1226 = !DILexicalBlockFile(scope: !1213, file: !1, discriminator: 2)
!1227 = !DILocation(line: 337, column: 30, scope: !1226)
!1228 = !DILocation(line: 337, column: 42, scope: !1226)
!1229 = !DILocation(line: 337, column: 9, scope: !1230)
!1230 = !DILexicalBlockFile(scope: !1213, file: !1, discriminator: 3)
!1231 = !DILocation(line: 337, column: 9, scope: !1232)
!1232 = !DILexicalBlockFile(scope: !1213, file: !1, discriminator: 4)
!1233 = !DILocation(line: 338, column: 5, scope: !1213)
!1234 = !DILocation(line: 339, column: 10, scope: !1235)
!1235 = distinct !DILexicalBlock(scope: !191, file: !1, line: 339, column: 9)
!1236 = !DILocation(line: 339, column: 16, scope: !1235)
!1237 = !DILocation(line: 339, column: 29, scope: !1235)
!1238 = !DILocation(line: 339, column: 9, scope: !191)
!1239 = !DILocation(line: 340, column: 9, scope: !1240)
!1240 = distinct !DILexicalBlock(scope: !1235, file: !1, line: 339, column: 35)
!1241 = !DILocation(line: 340, column: 30, scope: !1242)
!1242 = !DILexicalBlockFile(scope: !1240, file: !1, discriminator: 1)
!1243 = !DILocation(line: 340, column: 21, scope: !1242)
!1244 = !DILocation(line: 340, column: 19, scope: !1242)
!1245 = !DILocation(line: 340, column: 34, scope: !1242)
!1246 = !DILocation(line: 340, column: 39, scope: !1242)
!1247 = !DILocation(line: 340, column: 42, scope: !1248)
!1248 = !DILexicalBlockFile(scope: !1240, file: !1, discriminator: 2)
!1249 = !DILocation(line: 340, column: 44, scope: !1248)
!1250 = !DILocation(line: 340, column: 9, scope: !1251)
!1251 = !DILexicalBlockFile(scope: !1240, file: !1, discriminator: 3)
!1252 = !DILocation(line: 340, column: 9, scope: !1253)
!1253 = !DILexicalBlockFile(scope: !1240, file: !1, discriminator: 4)
!1254 = !DILocation(line: 341, column: 5, scope: !1240)
!1255 = !DILocation(line: 342, column: 10, scope: !1256)
!1256 = distinct !DILexicalBlock(scope: !191, file: !1, line: 342, column: 9)
!1257 = !DILocation(line: 342, column: 16, scope: !1256)
!1258 = !DILocation(line: 342, column: 27, scope: !1256)
!1259 = !DILocation(line: 342, column: 9, scope: !191)
!1260 = !DILocation(line: 343, column: 9, scope: !1261)
!1261 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 342, column: 33)
!1262 = !DILocation(line: 343, column: 30, scope: !1263)
!1263 = !DILexicalBlockFile(scope: !1261, file: !1, discriminator: 1)
!1264 = !DILocation(line: 343, column: 21, scope: !1263)
!1265 = !DILocation(line: 343, column: 19, scope: !1263)
!1266 = !DILocation(line: 343, column: 34, scope: !1263)
!1267 = !DILocation(line: 343, column: 39, scope: !1263)
!1268 = !DILocation(line: 343, column: 42, scope: !1269)
!1269 = !DILexicalBlockFile(scope: !1261, file: !1, discriminator: 2)
!1270 = !DILocation(line: 343, column: 44, scope: !1269)
!1271 = !DILocation(line: 343, column: 9, scope: !1272)
!1272 = !DILexicalBlockFile(scope: !1261, file: !1, discriminator: 3)
!1273 = !DILocation(line: 343, column: 9, scope: !1274)
!1274 = !DILexicalBlockFile(scope: !1261, file: !1, discriminator: 4)
!1275 = !DILocation(line: 344, column: 5, scope: !1261)
!1276 = !DILocation(line: 345, column: 10, scope: !1277)
!1277 = distinct !DILexicalBlock(scope: !191, file: !1, line: 345, column: 9)
!1278 = !DILocation(line: 345, column: 16, scope: !1277)
!1279 = !DILocation(line: 345, column: 28, scope: !1277)
!1280 = !DILocation(line: 345, column: 9, scope: !191)
!1281 = !DILocation(line: 346, column: 18, scope: !1282)
!1282 = distinct !DILexicalBlock(scope: !1283, file: !1, line: 346, column: 9)
!1283 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 345, column: 34)
!1284 = !DILocation(line: 346, column: 14, scope: !1282)
!1285 = !DILocation(line: 346, column: 23, scope: !1286)
!1286 = !DILexicalBlockFile(scope: !1287, file: !1, discriminator: 1)
!1287 = distinct !DILexicalBlock(scope: !1282, file: !1, line: 346, column: 9)
!1288 = !DILocation(line: 346, column: 27, scope: !1286)
!1289 = !DILocation(line: 346, column: 9, scope: !1286)
!1290 = !DILocation(line: 346, column: 54, scope: !1291)
!1291 = !DILexicalBlockFile(scope: !1287, file: !1, discriminator: 2)
!1292 = !DILocation(line: 346, column: 45, scope: !1291)
!1293 = !DILocation(line: 346, column: 39, scope: !1291)
!1294 = !DILocation(line: 346, column: 35, scope: !1295)
!1295 = !DILexicalBlockFile(scope: !1287, file: !1, discriminator: 3)
!1296 = !DILocation(line: 346, column: 9, scope: !1295)
!1297 = !DILocation(line: 347, column: 5, scope: !1283)
!1298 = !DILocation(line: 348, column: 16, scope: !191)
!1299 = !DILocation(line: 348, column: 19, scope: !191)
!1300 = !DILocation(line: 348, column: 5, scope: !191)
!1301 = !DILocation(line: 348, column: 8, scope: !191)
!1302 = !DILocation(line: 348, column: 14, scope: !191)
!1303 = !DILocation(line: 349, column: 1, scope: !191)
!1304 = !DILocation(line: 349, column: 1, scope: !1158)
!1305 = !DILocalVariable(name: "file", arg: 1, scope: !146, file: !1, line: 504, type: !4)
!1306 = !DILocation(line: 504, column: 12, scope: !146)
!1307 = !DILocalVariable(name: "c", scope: !146, file: !1, line: 506, type: !21)
!1308 = !DILocation(line: 506, column: 19, scope: !146)
!1309 = !DILocation(line: 508, column: 19, scope: !146)
!1310 = !DILocation(line: 508, column: 12, scope: !146)
!1311 = !DILocation(line: 508, column: 32, scope: !146)
!1312 = !DILocation(line: 508, column: 39, scope: !1313)
!1313 = !DILexicalBlockFile(scope: !146, file: !1, discriminator: 1)
!1314 = !DILocation(line: 508, column: 12, scope: !1313)
!1315 = !DILocation(line: 508, column: 12, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !146, file: !1, discriminator: 2)
!1317 = !DILocation(line: 508, column: 12, scope: !1318)
!1318 = !DILexicalBlockFile(scope: !146, file: !1, discriminator: 3)
!1319 = !DILocation(line: 508, column: 5, scope: !1318)
!1320 = !DILocalVariable(name: "c", arg: 1, scope: !149, file: !1, line: 516, type: !39)
!1321 = !DILocation(line: 516, column: 9, scope: !149)
!1322 = !DILocalVariable(name: "file", arg: 2, scope: !149, file: !1, line: 517, type: !4)
!1323 = !DILocation(line: 517, column: 12, scope: !149)
!1324 = !DILocalVariable(name: "s", scope: !149, file: !1, line: 519, type: !9)
!1325 = !DILocation(line: 519, column: 16, scope: !149)
!1326 = !DILocation(line: 519, column: 32, scope: !149)
!1327 = !DILocation(line: 519, column: 20, scope: !149)
!1328 = !DILocation(line: 521, column: 9, scope: !1329)
!1329 = distinct !DILexicalBlock(scope: !149, file: !1, line: 521, column: 9)
!1330 = !DILocation(line: 521, column: 11, scope: !1329)
!1331 = !DILocation(line: 521, column: 19, scope: !1329)
!1332 = !DILocation(line: 521, column: 22, scope: !1333)
!1333 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 1)
!1334 = !DILocation(line: 521, column: 25, scope: !1333)
!1335 = !DILocation(line: 521, column: 30, scope: !1333)
!1336 = !DILocation(line: 521, column: 37, scope: !1333)
!1337 = !DILocation(line: 521, column: 40, scope: !1338)
!1338 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 2)
!1339 = !DILocation(line: 521, column: 42, scope: !1338)
!1340 = !DILocation(line: 521, column: 49, scope: !1338)
!1341 = !DILocation(line: 521, column: 52, scope: !1342)
!1342 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 3)
!1343 = !DILocation(line: 521, column: 55, scope: !1342)
!1344 = !DILocation(line: 521, column: 60, scope: !1342)
!1345 = !DILocation(line: 521, column: 9, scope: !1342)
!1346 = !DILocation(line: 521, column: 68, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 4)
!1348 = !DILocation(line: 522, column: 15, scope: !149)
!1349 = !DILocation(line: 522, column: 5, scope: !149)
!1350 = !DILocation(line: 522, column: 8, scope: !149)
!1351 = !DILocation(line: 522, column: 13, scope: !149)
!1352 = !DILocation(line: 523, column: 5, scope: !149)
!1353 = !DILocation(line: 523, column: 8, scope: !149)
!1354 = !DILocation(line: 523, column: 11, scope: !149)
!1355 = !DILocation(line: 524, column: 16, scope: !149)
!1356 = !DILocation(line: 524, column: 19, scope: !149)
!1357 = !DILocation(line: 524, column: 25, scope: !149)
!1358 = !DILocation(line: 524, column: 5, scope: !149)
!1359 = !DILocation(line: 524, column: 8, scope: !149)
!1360 = !DILocation(line: 524, column: 13, scope: !149)
!1361 = !DILocation(line: 525, column: 9, scope: !1362)
!1362 = distinct !DILexicalBlock(scope: !149, file: !1, line: 525, column: 9)
!1363 = !DILocation(line: 525, column: 12, scope: !1362)
!1364 = !DILocation(line: 525, column: 9, scope: !149)
!1365 = !DILocation(line: 525, column: 18, scope: !1366)
!1366 = !DILexicalBlockFile(scope: !1362, file: !1, discriminator: 1)
!1367 = !DILocation(line: 525, column: 21, scope: !1366)
!1368 = !DILocation(line: 525, column: 27, scope: !1366)
!1369 = !DILocation(line: 526, column: 5, scope: !149)
!1370 = !DILocation(line: 526, column: 8, scope: !149)
!1371 = !DILocation(line: 526, column: 14, scope: !149)
!1372 = !DILocation(line: 527, column: 12, scope: !149)
!1373 = !DILocation(line: 527, column: 5, scope: !149)
!1374 = !DILocation(line: 528, column: 1, scope: !149)
!1375 = !DILocalVariable(name: "file", arg: 1, scope: !152, file: !1, line: 541, type: !4)
!1376 = !DILocation(line: 541, column: 12, scope: !152)
!1377 = !DILocalVariable(name: "buf", arg: 2, scope: !152, file: !1, line: 542, type: !32)
!1378 = !DILocation(line: 542, column: 11, scope: !152)
!1379 = !DILocalVariable(name: "len", arg: 3, scope: !152, file: !1, line: 543, type: !39)
!1380 = !DILocation(line: 543, column: 9, scope: !152)
!1381 = !DILocalVariable(name: "b", scope: !152, file: !1, line: 545, type: !32)
!1382 = !DILocation(line: 545, column: 11, scope: !152)
!1383 = !DILocation(line: 545, column: 15, scope: !152)
!1384 = !DILocation(line: 546, column: 9, scope: !1385)
!1385 = distinct !DILexicalBlock(scope: !152, file: !1, line: 546, column: 9)
!1386 = !DILocation(line: 546, column: 13, scope: !1385)
!1387 = !DILocation(line: 546, column: 23, scope: !1385)
!1388 = !DILocation(line: 546, column: 26, scope: !1389)
!1389 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 1)
!1390 = !DILocation(line: 546, column: 30, scope: !1389)
!1391 = !DILocation(line: 546, column: 9, scope: !1389)
!1392 = !DILocation(line: 546, column: 36, scope: !1393)
!1393 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 2)
!1394 = !DILocation(line: 548, column: 5, scope: !152)
!1395 = !DILocation(line: 548, column: 12, scope: !1396)
!1396 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 1)
!1397 = !DILocation(line: 548, column: 18, scope: !1396)
!1398 = !DILocation(line: 548, column: 22, scope: !1396)
!1399 = !DILocation(line: 548, column: 32, scope: !1400)
!1400 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 2)
!1401 = !DILocation(line: 548, column: 38, scope: !1400)
!1402 = !DILocation(line: 548, column: 25, scope: !1400)
!1403 = !DILocation(line: 548, column: 46, scope: !1400)
!1404 = !DILocation(line: 548, column: 51, scope: !1400)
!1405 = !DILocation(line: 548, column: 58, scope: !1406)
!1406 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 3)
!1407 = !DILocation(line: 548, column: 54, scope: !1406)
!1408 = !DILocation(line: 548, column: 61, scope: !1406)
!1409 = !DILocation(line: 548, column: 5, scope: !1410)
!1410 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 4)
!1411 = !DILocation(line: 548, column: 5, scope: !1412)
!1412 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 5)
!1413 = !DILocation(line: 549, column: 6, scope: !152)
!1414 = !DILocation(line: 549, column: 10, scope: !152)
!1415 = !DILocation(line: 550, column: 12, scope: !152)
!1416 = !DILocation(line: 550, column: 17, scope: !152)
!1417 = !DILocation(line: 550, column: 14, scope: !152)
!1418 = !DILocation(line: 550, column: 21, scope: !152)
!1419 = !DILocation(line: 550, column: 24, scope: !1396)
!1420 = !DILocation(line: 550, column: 28, scope: !1396)
!1421 = !DILocation(line: 550, column: 12, scope: !1396)
!1422 = !DILocation(line: 550, column: 12, scope: !1400)
!1423 = !DILocation(line: 550, column: 43, scope: !1406)
!1424 = !DILocation(line: 550, column: 12, scope: !1406)
!1425 = !DILocation(line: 550, column: 12, scope: !1410)
!1426 = !DILocation(line: 550, column: 5, scope: !1410)
!1427 = !DILocation(line: 551, column: 1, scope: !152)
!1428 = !DILocalVariable(name: "file", arg: 1, scope: !155, file: !1, line: 560, type: !4)
!1429 = !DILocation(line: 560, column: 12, scope: !155)
!1430 = !DILocalVariable(name: "buf", arg: 2, scope: !155, file: !1, line: 561, type: !158)
!1431 = !DILocation(line: 561, column: 12, scope: !155)
!1432 = !DILocalVariable(name: "len", arg: 3, scope: !155, file: !1, line: 562, type: !24)
!1433 = !DILocation(line: 562, column: 14, scope: !155)
!1434 = !DILocalVariable(name: "s", scope: !155, file: !1, line: 564, type: !9)
!1435 = !DILocation(line: 564, column: 16, scope: !155)
!1436 = !DILocation(line: 564, column: 32, scope: !155)
!1437 = !DILocation(line: 564, column: 20, scope: !155)
!1438 = !DILocation(line: 566, column: 9, scope: !1439)
!1439 = distinct !DILexicalBlock(scope: !155, file: !1, line: 566, column: 9)
!1440 = !DILocation(line: 566, column: 11, scope: !1439)
!1441 = !DILocation(line: 566, column: 19, scope: !1439)
!1442 = !DILocation(line: 566, column: 22, scope: !1443)
!1443 = !DILexicalBlockFile(scope: !1439, file: !1, discriminator: 1)
!1444 = !DILocation(line: 566, column: 25, scope: !1443)
!1445 = !DILocation(line: 566, column: 30, scope: !1443)
!1446 = !DILocation(line: 566, column: 9, scope: !1443)
!1447 = !DILocation(line: 566, column: 38, scope: !1448)
!1448 = !DILexicalBlockFile(scope: !1439, file: !1, discriminator: 2)
!1449 = !DILocation(line: 568, column: 33, scope: !155)
!1450 = !DILocation(line: 568, column: 5, scope: !155)
!1451 = !DILocation(line: 568, column: 8, scope: !155)
!1452 = !DILocation(line: 568, column: 15, scope: !155)
!1453 = !DILocation(line: 568, column: 23, scope: !155)
!1454 = !DILocation(line: 569, column: 26, scope: !155)
!1455 = !DILocation(line: 569, column: 5, scope: !155)
!1456 = !DILocation(line: 569, column: 8, scope: !155)
!1457 = !DILocation(line: 569, column: 15, scope: !155)
!1458 = !DILocation(line: 569, column: 24, scope: !155)
!1459 = !DILocation(line: 571, column: 5, scope: !155)
!1460 = !DILocation(line: 571, column: 12, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !155, file: !1, discriminator: 1)
!1462 = !DILocation(line: 571, column: 15, scope: !1461)
!1463 = !DILocation(line: 571, column: 22, scope: !1461)
!1464 = !DILocation(line: 571, column: 31, scope: !1461)
!1465 = !DILocation(line: 571, column: 5, scope: !1461)
!1466 = !DILocation(line: 573, column: 13, scope: !1467)
!1467 = distinct !DILexicalBlock(scope: !1468, file: !1, line: 573, column: 13)
!1468 = distinct !DILexicalBlock(scope: !155, file: !1, line: 571, column: 37)
!1469 = !DILocation(line: 573, column: 16, scope: !1467)
!1470 = !DILocation(line: 573, column: 23, scope: !1467)
!1471 = !DILocation(line: 573, column: 33, scope: !1467)
!1472 = !DILocation(line: 573, column: 13, scope: !1468)
!1473 = !DILocation(line: 575, column: 34, scope: !1474)
!1474 = distinct !DILexicalBlock(scope: !1467, file: !1, line: 573, column: 39)
!1475 = !DILocation(line: 575, column: 37, scope: !1474)
!1476 = !DILocation(line: 575, column: 13, scope: !1474)
!1477 = !DILocation(line: 575, column: 16, scope: !1474)
!1478 = !DILocation(line: 575, column: 23, scope: !1474)
!1479 = !DILocation(line: 575, column: 32, scope: !1474)
!1480 = !DILocation(line: 576, column: 24, scope: !1481)
!1481 = distinct !DILexicalBlock(scope: !1474, file: !1, line: 576, column: 17)
!1482 = !DILocation(line: 576, column: 27, scope: !1481)
!1483 = !DILocation(line: 576, column: 49, scope: !1481)
!1484 = !DILocation(line: 576, column: 52, scope: !1481)
!1485 = !DILocation(line: 576, column: 17, scope: !1481)
!1486 = !DILocation(line: 576, column: 58, scope: !1481)
!1487 = !DILocation(line: 576, column: 17, scope: !1474)
!1488 = !DILocation(line: 577, column: 17, scope: !1489)
!1489 = distinct !DILexicalBlock(scope: !1481, file: !1, line: 576, column: 72)
!1490 = !DILocation(line: 577, column: 20, scope: !1489)
!1491 = !DILocation(line: 577, column: 26, scope: !1489)
!1492 = !DILocation(line: 578, column: 17, scope: !1489)
!1493 = !DILocation(line: 580, column: 13, scope: !1474)
!1494 = !DILocation(line: 580, column: 16, scope: !1474)
!1495 = !DILocation(line: 580, column: 23, scope: !1474)
!1496 = !DILocation(line: 580, column: 33, scope: !1474)
!1497 = !DILocation(line: 581, column: 9, scope: !1474)
!1498 = !DILocation(line: 582, column: 18, scope: !1468)
!1499 = !DILocation(line: 582, column: 21, scope: !1468)
!1500 = !DILocation(line: 582, column: 28, scope: !1468)
!1501 = !DILocation(line: 582, column: 9, scope: !1468)
!1502 = !DILocation(line: 582, column: 12, scope: !1468)
!1503 = !DILocation(line: 582, column: 15, scope: !1468)
!1504 = !DILocation(line: 583, column: 19, scope: !1468)
!1505 = !DILocation(line: 583, column: 22, scope: !1468)
!1506 = !DILocation(line: 583, column: 29, scope: !1468)
!1507 = !DILocation(line: 583, column: 9, scope: !1468)
!1508 = !DILocation(line: 583, column: 12, scope: !1468)
!1509 = !DILocation(line: 583, column: 16, scope: !1468)
!1510 = !DILocation(line: 584, column: 30, scope: !1468)
!1511 = !DILocation(line: 584, column: 33, scope: !1468)
!1512 = !DILocation(line: 584, column: 20, scope: !1468)
!1513 = !DILocation(line: 584, column: 9, scope: !1468)
!1514 = !DILocation(line: 584, column: 12, scope: !1468)
!1515 = !DILocation(line: 584, column: 18, scope: !1468)
!1516 = !DILocation(line: 585, column: 18, scope: !1468)
!1517 = !DILocation(line: 585, column: 21, scope: !1468)
!1518 = !DILocation(line: 585, column: 28, scope: !1468)
!1519 = !DILocation(line: 585, column: 9, scope: !1468)
!1520 = !DILocation(line: 585, column: 12, scope: !1468)
!1521 = !DILocation(line: 585, column: 15, scope: !1468)
!1522 = !DILocation(line: 586, column: 19, scope: !1468)
!1523 = !DILocation(line: 586, column: 22, scope: !1468)
!1524 = !DILocation(line: 586, column: 29, scope: !1468)
!1525 = !DILocation(line: 586, column: 9, scope: !1468)
!1526 = !DILocation(line: 586, column: 12, scope: !1468)
!1527 = !DILocation(line: 586, column: 16, scope: !1468)
!1528 = !DILocation(line: 587, column: 13, scope: !1529)
!1529 = distinct !DILexicalBlock(scope: !1468, file: !1, line: 587, column: 13)
!1530 = !DILocation(line: 587, column: 16, scope: !1529)
!1531 = !DILocation(line: 587, column: 22, scope: !1529)
!1532 = !DILocation(line: 587, column: 13, scope: !1468)
!1533 = !DILocation(line: 587, column: 31, scope: !1534)
!1534 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 1)
!1535 = !DILocation(line: 571, column: 5, scope: !1536)
!1536 = !DILexicalBlockFile(scope: !155, file: !1, discriminator: 2)
!1537 = !DILocation(line: 589, column: 20, scope: !155)
!1538 = !DILocation(line: 589, column: 23, scope: !155)
!1539 = !DILocation(line: 589, column: 43, scope: !155)
!1540 = !DILocation(line: 589, column: 48, scope: !155)
!1541 = !DILocation(line: 589, column: 14, scope: !155)
!1542 = !DILocation(line: 589, column: 5, scope: !155)
!1543 = !DILocation(line: 589, column: 8, scope: !155)
!1544 = !DILocation(line: 589, column: 12, scope: !155)
!1545 = !DILocation(line: 591, column: 18, scope: !155)
!1546 = !DILocation(line: 591, column: 24, scope: !155)
!1547 = !DILocation(line: 591, column: 27, scope: !155)
!1548 = !DILocation(line: 591, column: 34, scope: !155)
!1549 = !DILocation(line: 591, column: 22, scope: !155)
!1550 = !DILocation(line: 591, column: 5, scope: !155)
!1551 = !DILocation(line: 592, column: 1, scope: !155)
!1552 = !DILocalVariable(name: "file", arg: 1, scope: !161, file: !1, line: 603, type: !4)
!1553 = !DILocation(line: 603, column: 32, scope: !161)
!1554 = !DILocalVariable(name: "format", arg: 2, scope: !161, file: !1, line: 603, type: !131)
!1555 = !DILocation(line: 603, column: 50, scope: !161)
!1556 = !DILocalVariable(name: "buf", scope: !161, file: !1, line: 605, type: !1557)
!1557 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 32768, align: 8, elements: !1558)
!1558 = !{!1559}
!1559 = !DISubrange(count: 4096)
!1560 = !DILocation(line: 605, column: 10, scope: !161)
!1561 = !DILocalVariable(name: "va", scope: !161, file: !1, line: 606, type: !1562)
!1562 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !60, line: 79, baseType: !1563)
!1563 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !1564, line: 50, baseType: !1565)
!1564 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!1565 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 606, baseType: !1566)
!1566 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1567, size: 192, align: 64, elements: !97)
!1567 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 606, size: 192, align: 64, elements: !1568)
!1568 = !{!1569, !1570, !1571, !1572}
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !1567, file: !1, line: 606, baseType: !24, size: 32, align: 32)
!1570 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !1567, file: !1, line: 606, baseType: !24, size: 32, align: 32, offset: 32)
!1571 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !1567, file: !1, line: 606, baseType: !8, size: 64, align: 64, offset: 64)
!1572 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !1567, file: !1, line: 606, baseType: !8, size: 64, align: 64, offset: 128)
!1573 = !DILocation(line: 606, column: 13, scope: !161)
!1574 = !DILocalVariable(name: "len", scope: !161, file: !1, line: 607, type: !39)
!1575 = !DILocation(line: 607, column: 9, scope: !161)
!1576 = !DILocation(line: 609, column: 5, scope: !161)
!1577 = !DILocation(line: 609, column: 26, scope: !161)
!1578 = !DILocation(line: 610, column: 5, scope: !161)
!1579 = !DILocation(line: 627, column: 21, scope: !161)
!1580 = !DILocation(line: 627, column: 39, scope: !161)
!1581 = !DILocation(line: 627, column: 47, scope: !161)
!1582 = !DILocation(line: 627, column: 11, scope: !161)
!1583 = !DILocation(line: 627, column: 9, scope: !161)
!1584 = !DILocation(line: 628, column: 5, scope: !161)
!1585 = !DILocation(line: 631, column: 9, scope: !1586)
!1586 = distinct !DILexicalBlock(scope: !161, file: !1, line: 631, column: 9)
!1587 = !DILocation(line: 631, column: 13, scope: !1586)
!1588 = !DILocation(line: 631, column: 18, scope: !1586)
!1589 = !DILocation(line: 631, column: 21, scope: !1590)
!1590 = !DILexicalBlockFile(scope: !1586, file: !1, discriminator: 1)
!1591 = !DILocation(line: 631, column: 25, scope: !1590)
!1592 = !DILocation(line: 631, column: 45, scope: !1590)
!1593 = !DILocation(line: 631, column: 48, scope: !1594)
!1594 = !DILexicalBlockFile(scope: !1586, file: !1, discriminator: 2)
!1595 = !DILocation(line: 631, column: 69, scope: !1594)
!1596 = !DILocation(line: 631, column: 9, scope: !1594)
!1597 = !DILocation(line: 632, column: 9, scope: !1586)
!1598 = !DILocation(line: 633, column: 20, scope: !161)
!1599 = !DILocation(line: 633, column: 26, scope: !161)
!1600 = !DILocation(line: 633, column: 41, scope: !161)
!1601 = !DILocation(line: 633, column: 12, scope: !161)
!1602 = !DILocation(line: 633, column: 5, scope: !161)
!1603 = !DILocation(line: 634, column: 1, scope: !161)
!1604 = !DILocalVariable(name: "file", arg: 1, scope: !164, file: !1, line: 679, type: !4)
!1605 = !DILocation(line: 679, column: 12, scope: !164)
!1606 = !DILocalVariable(name: "c", arg: 2, scope: !164, file: !1, line: 680, type: !39)
!1607 = !DILocation(line: 680, column: 9, scope: !164)
!1608 = !DILocalVariable(name: "cc", scope: !164, file: !1, line: 682, type: !21)
!1609 = !DILocation(line: 682, column: 19, scope: !164)
!1610 = !DILocation(line: 682, column: 40, scope: !164)
!1611 = !DILocation(line: 682, column: 24, scope: !164)
!1612 = !DILocation(line: 684, column: 20, scope: !164)
!1613 = !DILocation(line: 684, column: 12, scope: !164)
!1614 = !DILocation(line: 684, column: 34, scope: !164)
!1615 = !DILocation(line: 684, column: 46, scope: !1616)
!1616 = !DILexicalBlockFile(scope: !164, file: !1, discriminator: 1)
!1617 = !DILocation(line: 684, column: 41, scope: !1616)
!1618 = !DILocation(line: 684, column: 12, scope: !1616)
!1619 = !DILocation(line: 684, column: 12, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !164, file: !1, discriminator: 2)
!1621 = !DILocation(line: 684, column: 12, scope: !1622)
!1622 = !DILexicalBlockFile(scope: !164, file: !1, discriminator: 3)
!1623 = !DILocation(line: 684, column: 5, scope: !1622)
!1624 = !DILocalVariable(name: "file", arg: 1, scope: !167, file: !1, line: 694, type: !4)
!1625 = !DILocation(line: 694, column: 12, scope: !167)
!1626 = !DILocalVariable(name: "s", arg: 2, scope: !167, file: !1, line: 695, type: !131)
!1627 = !DILocation(line: 695, column: 17, scope: !167)
!1628 = !DILocation(line: 697, column: 20, scope: !167)
!1629 = !DILocation(line: 697, column: 33, scope: !167)
!1630 = !DILocation(line: 697, column: 53, scope: !167)
!1631 = !DILocation(line: 697, column: 46, scope: !167)
!1632 = !DILocation(line: 697, column: 36, scope: !167)
!1633 = !DILocation(line: 697, column: 12, scope: !1634)
!1634 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!1635 = !DILocation(line: 697, column: 5, scope: !167)
!1636 = !DILocalVariable(name: "file", arg: 1, scope: !170, file: !1, line: 747, type: !4)
!1637 = !DILocation(line: 747, column: 13, scope: !170)
!1638 = !DILocalVariable(name: "flush", arg: 2, scope: !170, file: !1, line: 748, type: !39)
!1639 = !DILocation(line: 748, column: 10, scope: !170)
!1640 = !DILocalVariable(name: "s", scope: !170, file: !1, line: 750, type: !9)
!1641 = !DILocation(line: 750, column: 16, scope: !170)
!1642 = !DILocation(line: 750, column: 32, scope: !170)
!1643 = !DILocation(line: 750, column: 20, scope: !170)
!1644 = !DILocalVariable(name: "err", scope: !170, file: !1, line: 751, type: !39)
!1645 = !DILocation(line: 751, column: 9, scope: !170)
!1646 = !DILocation(line: 751, column: 25, scope: !170)
!1647 = !DILocation(line: 751, column: 31, scope: !170)
!1648 = !DILocation(line: 751, column: 15, scope: !170)
!1649 = !DILocation(line: 753, column: 9, scope: !1650)
!1650 = distinct !DILexicalBlock(scope: !170, file: !1, line: 753, column: 9)
!1651 = !DILocation(line: 753, column: 9, scope: !170)
!1652 = !DILocation(line: 753, column: 21, scope: !1653)
!1653 = !DILexicalBlockFile(scope: !1650, file: !1, discriminator: 1)
!1654 = !DILocation(line: 753, column: 14, scope: !1653)
!1655 = !DILocation(line: 754, column: 12, scope: !170)
!1656 = !DILocation(line: 754, column: 15, scope: !170)
!1657 = !DILocation(line: 754, column: 5, scope: !170)
!1658 = !DILocation(line: 755, column: 13, scope: !170)
!1659 = !DILocation(line: 755, column: 16, scope: !170)
!1660 = !DILocation(line: 755, column: 22, scope: !170)
!1661 = !DILocation(line: 755, column: 13, scope: !1662)
!1662 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!1663 = !DILocation(line: 755, column: 47, scope: !1664)
!1664 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 2)
!1665 = !DILocation(line: 755, column: 50, scope: !1664)
!1666 = !DILocation(line: 755, column: 13, scope: !1664)
!1667 = !DILocation(line: 755, column: 13, scope: !1668)
!1668 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 3)
!1669 = !DILocation(line: 755, column: 5, scope: !1668)
!1670 = !DILocation(line: 756, column: 1, scope: !170)
!1671 = !DILocalVariable(name: "file", arg: 1, scope: !197, file: !1, line: 706, type: !4)
!1672 = !DILocation(line: 706, column: 12, scope: !197)
!1673 = !DILocalVariable(name: "flush", arg: 2, scope: !197, file: !1, line: 707, type: !39)
!1674 = !DILocation(line: 707, column: 9, scope: !197)
!1675 = !DILocalVariable(name: "len", scope: !197, file: !1, line: 709, type: !23)
!1676 = !DILocation(line: 709, column: 10, scope: !197)
!1677 = !DILocalVariable(name: "done", scope: !197, file: !1, line: 710, type: !39)
!1678 = !DILocation(line: 710, column: 9, scope: !197)
!1679 = !DILocalVariable(name: "s", scope: !197, file: !1, line: 711, type: !9)
!1680 = !DILocation(line: 711, column: 16, scope: !197)
!1681 = !DILocation(line: 711, column: 32, scope: !197)
!1682 = !DILocation(line: 711, column: 20, scope: !197)
!1683 = !DILocation(line: 713, column: 9, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !197, file: !1, line: 713, column: 9)
!1685 = !DILocation(line: 713, column: 11, scope: !1684)
!1686 = !DILocation(line: 713, column: 19, scope: !1684)
!1687 = !DILocation(line: 713, column: 22, scope: !1688)
!1688 = !DILexicalBlockFile(scope: !1684, file: !1, discriminator: 1)
!1689 = !DILocation(line: 713, column: 25, scope: !1688)
!1690 = !DILocation(line: 713, column: 30, scope: !1688)
!1691 = !DILocation(line: 713, column: 9, scope: !1688)
!1692 = !DILocation(line: 713, column: 38, scope: !1693)
!1693 = !DILexicalBlockFile(scope: !1684, file: !1, discriminator: 2)
!1694 = !DILocation(line: 715, column: 5, scope: !197)
!1695 = !DILocation(line: 715, column: 8, scope: !197)
!1696 = !DILocation(line: 715, column: 15, scope: !197)
!1697 = !DILocation(line: 715, column: 24, scope: !197)
!1698 = !DILocation(line: 717, column: 5, scope: !197)
!1699 = !DILocation(line: 718, column: 27, scope: !1700)
!1700 = distinct !DILexicalBlock(scope: !1701, file: !1, line: 717, column: 14)
!1701 = distinct !DILexicalBlock(scope: !1702, file: !1, line: 717, column: 5)
!1702 = distinct !DILexicalBlock(scope: !197, file: !1, line: 717, column: 5)
!1703 = !DILocation(line: 718, column: 30, scope: !1700)
!1704 = !DILocation(line: 718, column: 37, scope: !1700)
!1705 = !DILocation(line: 718, column: 25, scope: !1700)
!1706 = !DILocation(line: 718, column: 13, scope: !1700)
!1707 = !DILocation(line: 720, column: 13, scope: !1708)
!1708 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 720, column: 13)
!1709 = !DILocation(line: 720, column: 17, scope: !1708)
!1710 = !DILocation(line: 720, column: 13, scope: !1700)
!1711 = !DILocation(line: 721, column: 30, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1713, file: !1, line: 721, column: 17)
!1713 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 720, column: 23)
!1714 = !DILocation(line: 721, column: 33, scope: !1712)
!1715 = !DILocation(line: 721, column: 44, scope: !1712)
!1716 = !DILocation(line: 721, column: 49, scope: !1712)
!1717 = !DILocation(line: 721, column: 52, scope: !1712)
!1718 = !DILocation(line: 721, column: 23, scope: !1712)
!1719 = !DILocation(line: 721, column: 17, scope: !1712)
!1720 = !DILocation(line: 721, column: 61, scope: !1712)
!1721 = !DILocation(line: 721, column: 58, scope: !1712)
!1722 = !DILocation(line: 721, column: 17, scope: !1713)
!1723 = !DILocation(line: 722, column: 17, scope: !1724)
!1724 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 721, column: 66)
!1725 = !DILocation(line: 722, column: 20, scope: !1724)
!1726 = !DILocation(line: 722, column: 26, scope: !1724)
!1727 = !DILocation(line: 723, column: 17, scope: !1724)
!1728 = !DILocation(line: 725, column: 34, scope: !1713)
!1729 = !DILocation(line: 725, column: 37, scope: !1713)
!1730 = !DILocation(line: 725, column: 13, scope: !1713)
!1731 = !DILocation(line: 725, column: 16, scope: !1713)
!1732 = !DILocation(line: 725, column: 23, scope: !1713)
!1733 = !DILocation(line: 725, column: 32, scope: !1713)
!1734 = !DILocation(line: 726, column: 13, scope: !1713)
!1735 = !DILocation(line: 726, column: 16, scope: !1713)
!1736 = !DILocation(line: 726, column: 23, scope: !1713)
!1737 = !DILocation(line: 726, column: 33, scope: !1713)
!1738 = !DILocation(line: 727, column: 9, scope: !1713)
!1739 = !DILocation(line: 728, column: 13, scope: !1740)
!1740 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 728, column: 13)
!1741 = !DILocation(line: 728, column: 13, scope: !1700)
!1742 = !DILocation(line: 728, column: 19, scope: !1743)
!1743 = !DILexicalBlockFile(scope: !1740, file: !1, discriminator: 1)
!1744 = !DILocation(line: 729, column: 19, scope: !1700)
!1745 = !DILocation(line: 729, column: 22, scope: !1700)
!1746 = !DILocation(line: 729, column: 29, scope: !1700)
!1747 = !DILocation(line: 729, column: 9, scope: !1700)
!1748 = !DILocation(line: 729, column: 12, scope: !1700)
!1749 = !DILocation(line: 729, column: 16, scope: !1700)
!1750 = !DILocation(line: 730, column: 30, scope: !1700)
!1751 = !DILocation(line: 730, column: 33, scope: !1700)
!1752 = !DILocation(line: 730, column: 42, scope: !1700)
!1753 = !DILocation(line: 730, column: 20, scope: !1700)
!1754 = !DILocation(line: 730, column: 9, scope: !1700)
!1755 = !DILocation(line: 730, column: 12, scope: !1700)
!1756 = !DILocation(line: 730, column: 18, scope: !1700)
!1757 = !DILocation(line: 731, column: 19, scope: !1700)
!1758 = !DILocation(line: 731, column: 22, scope: !1700)
!1759 = !DILocation(line: 731, column: 29, scope: !1700)
!1760 = !DILocation(line: 731, column: 9, scope: !1700)
!1761 = !DILocation(line: 731, column: 12, scope: !1700)
!1762 = !DILocation(line: 731, column: 16, scope: !1700)
!1763 = !DILocation(line: 734, column: 13, scope: !1764)
!1764 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 734, column: 13)
!1765 = !DILocation(line: 734, column: 17, scope: !1764)
!1766 = !DILocation(line: 734, column: 22, scope: !1764)
!1767 = !DILocation(line: 734, column: 25, scope: !1768)
!1768 = !DILexicalBlockFile(scope: !1764, file: !1, discriminator: 1)
!1769 = !DILocation(line: 734, column: 28, scope: !1768)
!1770 = !DILocation(line: 734, column: 34, scope: !1768)
!1771 = !DILocation(line: 734, column: 13, scope: !1768)
!1772 = !DILocation(line: 734, column: 50, scope: !1773)
!1773 = !DILexicalBlockFile(scope: !1764, file: !1, discriminator: 2)
!1774 = !DILocation(line: 734, column: 53, scope: !1773)
!1775 = !DILocation(line: 734, column: 59, scope: !1773)
!1776 = !DILocation(line: 739, column: 17, scope: !1700)
!1777 = !DILocation(line: 739, column: 20, scope: !1700)
!1778 = !DILocation(line: 739, column: 27, scope: !1700)
!1779 = !DILocation(line: 739, column: 37, scope: !1700)
!1780 = !DILocation(line: 739, column: 42, scope: !1700)
!1781 = !DILocation(line: 739, column: 45, scope: !1782)
!1782 = !DILexicalBlockFile(scope: !1700, file: !1, discriminator: 1)
!1783 = !DILocation(line: 739, column: 48, scope: !1782)
!1784 = !DILocation(line: 739, column: 54, scope: !1782)
!1785 = !DILocation(line: 739, column: 42, scope: !1782)
!1786 = !DILocation(line: 739, column: 42, scope: !1787)
!1787 = !DILexicalBlockFile(scope: !1700, file: !1, discriminator: 2)
!1788 = !DILocation(line: 739, column: 14, scope: !1787)
!1789 = !DILocation(line: 741, column: 13, scope: !1790)
!1790 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 741, column: 13)
!1791 = !DILocation(line: 741, column: 16, scope: !1790)
!1792 = !DILocation(line: 741, column: 22, scope: !1790)
!1793 = !DILocation(line: 741, column: 30, scope: !1790)
!1794 = !DILocation(line: 741, column: 33, scope: !1795)
!1795 = !DILexicalBlockFile(scope: !1790, file: !1, discriminator: 1)
!1796 = !DILocation(line: 741, column: 36, scope: !1795)
!1797 = !DILocation(line: 741, column: 42, scope: !1795)
!1798 = !DILocation(line: 741, column: 13, scope: !1795)
!1799 = !DILocation(line: 741, column: 59, scope: !1800)
!1800 = !DILexicalBlockFile(scope: !1790, file: !1, discriminator: 2)
!1801 = !DILocation(line: 717, column: 5, scope: !1802)
!1802 = !DILexicalBlockFile(scope: !1701, file: !1, discriminator: 1)
!1803 = !DILocation(line: 743, column: 13, scope: !197)
!1804 = !DILocation(line: 743, column: 16, scope: !197)
!1805 = !DILocation(line: 743, column: 22, scope: !197)
!1806 = !DILocation(line: 743, column: 13, scope: !1807)
!1807 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!1808 = !DILocation(line: 743, column: 47, scope: !1809)
!1809 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 2)
!1810 = !DILocation(line: 743, column: 50, scope: !1809)
!1811 = !DILocation(line: 743, column: 13, scope: !1809)
!1812 = !DILocation(line: 743, column: 13, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 3)
!1814 = !DILocation(line: 743, column: 5, scope: !1813)
!1815 = !DILocation(line: 744, column: 1, scope: !197)
!1816 = !DILocalVariable(name: "file", arg: 1, scope: !171, file: !1, line: 768, type: !4)
!1817 = !DILocation(line: 768, column: 12, scope: !171)
!1818 = !DILocalVariable(name: "offset", arg: 2, scope: !171, file: !1, line: 769, type: !90)
!1819 = !DILocation(line: 769, column: 13, scope: !171)
!1820 = !DILocalVariable(name: "whence", arg: 3, scope: !171, file: !1, line: 770, type: !39)
!1821 = !DILocation(line: 770, column: 9, scope: !171)
!1822 = !DILocalVariable(name: "s", scope: !171, file: !1, line: 772, type: !9)
!1823 = !DILocation(line: 772, column: 16, scope: !171)
!1824 = !DILocation(line: 772, column: 32, scope: !171)
!1825 = !DILocation(line: 772, column: 20, scope: !171)
!1826 = !DILocation(line: 774, column: 9, scope: !1827)
!1827 = distinct !DILexicalBlock(scope: !171, file: !1, line: 774, column: 9)
!1828 = !DILocation(line: 774, column: 11, scope: !1827)
!1829 = !DILocation(line: 774, column: 19, scope: !1827)
!1830 = !DILocation(line: 774, column: 22, scope: !1831)
!1831 = !DILexicalBlockFile(scope: !1827, file: !1, discriminator: 1)
!1832 = !DILocation(line: 774, column: 29, scope: !1831)
!1833 = !DILocation(line: 774, column: 41, scope: !1831)
!1834 = !DILocation(line: 775, column: 9, scope: !1827)
!1835 = !DILocation(line: 775, column: 12, scope: !1827)
!1836 = !DILocation(line: 775, column: 18, scope: !1827)
!1837 = !DILocation(line: 775, column: 29, scope: !1827)
!1838 = !DILocation(line: 775, column: 32, scope: !1831)
!1839 = !DILocation(line: 775, column: 35, scope: !1831)
!1840 = !DILocation(line: 775, column: 41, scope: !1831)
!1841 = !DILocation(line: 774, column: 9, scope: !1842)
!1842 = !DILexicalBlockFile(scope: !171, file: !1, discriminator: 2)
!1843 = !DILocation(line: 776, column: 9, scope: !1844)
!1844 = distinct !DILexicalBlock(scope: !1827, file: !1, line: 775, column: 58)
!1845 = !DILocation(line: 779, column: 9, scope: !1846)
!1846 = distinct !DILexicalBlock(scope: !171, file: !1, line: 779, column: 9)
!1847 = !DILocation(line: 779, column: 12, scope: !1846)
!1848 = !DILocation(line: 779, column: 17, scope: !1846)
!1849 = !DILocation(line: 779, column: 9, scope: !171)
!1850 = !DILocation(line: 783, column: 13, scope: !1851)
!1851 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 783, column: 13)
!1852 = distinct !DILexicalBlock(scope: !1846, file: !1, line: 779, column: 25)
!1853 = !DILocation(line: 783, column: 20, scope: !1851)
!1854 = !DILocation(line: 783, column: 13, scope: !1852)
!1855 = !DILocation(line: 784, column: 23, scope: !1856)
!1856 = distinct !DILexicalBlock(scope: !1851, file: !1, line: 783, column: 33)
!1857 = !DILocation(line: 784, column: 26, scope: !1856)
!1858 = !DILocation(line: 784, column: 20, scope: !1856)
!1859 = !DILocation(line: 785, column: 9, scope: !1856)
!1860 = !DILocation(line: 786, column: 13, scope: !1861)
!1861 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 786, column: 13)
!1862 = !DILocation(line: 786, column: 20, scope: !1861)
!1863 = !DILocation(line: 786, column: 13, scope: !1852)
!1864 = !DILocation(line: 786, column: 25, scope: !1865)
!1865 = !DILexicalBlockFile(scope: !1861, file: !1, discriminator: 1)
!1866 = !DILocation(line: 789, column: 13, scope: !1867)
!1867 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 789, column: 13)
!1868 = !DILocation(line: 789, column: 16, scope: !1867)
!1869 = !DILocation(line: 789, column: 22, scope: !1867)
!1870 = !DILocation(line: 789, column: 13, scope: !1852)
!1871 = !DILocation(line: 790, column: 31, scope: !1872)
!1872 = distinct !DILexicalBlock(scope: !1867, file: !1, line: 789, column: 33)
!1873 = !DILocation(line: 790, column: 13, scope: !1872)
!1874 = !DILocation(line: 790, column: 16, scope: !1872)
!1875 = !DILocation(line: 790, column: 22, scope: !1872)
!1876 = !DILocation(line: 791, column: 17, scope: !1877)
!1877 = distinct !DILexicalBlock(scope: !1872, file: !1, line: 791, column: 17)
!1878 = !DILocation(line: 791, column: 20, scope: !1877)
!1879 = !DILocation(line: 791, column: 26, scope: !1877)
!1880 = !DILocation(line: 791, column: 17, scope: !1872)
!1881 = !DILocation(line: 791, column: 37, scope: !1882)
!1882 = !DILexicalBlockFile(scope: !1877, file: !1, discriminator: 1)
!1883 = !DILocation(line: 792, column: 13, scope: !1872)
!1884 = !DILocation(line: 793, column: 9, scope: !1872)
!1885 = !DILocation(line: 794, column: 9, scope: !1852)
!1886 = !DILocation(line: 794, column: 16, scope: !1887)
!1887 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 1)
!1888 = !DILocation(line: 794, column: 23, scope: !1887)
!1889 = !DILocation(line: 794, column: 9, scope: !1887)
!1890 = !DILocalVariable(name: "size", scope: !1891, file: !1, line: 795, type: !23)
!1891 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 794, column: 29)
!1892 = !DILocation(line: 795, column: 18, scope: !1891)
!1893 = !DILocation(line: 796, column: 17, scope: !1894)
!1894 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 796, column: 17)
!1895 = !DILocation(line: 796, column: 24, scope: !1894)
!1896 = !DILocation(line: 796, column: 17, scope: !1891)
!1897 = !DILocation(line: 796, column: 50, scope: !1898)
!1898 = !DILexicalBlockFile(scope: !1894, file: !1, discriminator: 1)
!1899 = !DILocation(line: 796, column: 44, scope: !1898)
!1900 = !DILocation(line: 796, column: 42, scope: !1898)
!1901 = !DILocation(line: 796, column: 37, scope: !1898)
!1902 = !DILocation(line: 798, column: 28, scope: !1891)
!1903 = !DILocation(line: 798, column: 34, scope: !1891)
!1904 = !DILocation(line: 798, column: 37, scope: !1891)
!1905 = !DILocation(line: 798, column: 44, scope: !1891)
!1906 = !DILocation(line: 798, column: 20, scope: !1891)
!1907 = !DILocation(line: 798, column: 18, scope: !1891)
!1908 = !DILocation(line: 799, column: 17, scope: !1909)
!1909 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 799, column: 17)
!1910 = !DILocation(line: 799, column: 22, scope: !1909)
!1911 = !DILocation(line: 799, column: 17, scope: !1891)
!1912 = !DILocation(line: 799, column: 28, scope: !1913)
!1913 = !DILexicalBlockFile(scope: !1909, file: !1, discriminator: 1)
!1914 = !DILocation(line: 801, column: 23, scope: !1891)
!1915 = !DILocation(line: 801, column: 20, scope: !1891)
!1916 = !DILocation(line: 794, column: 9, scope: !1917)
!1917 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 2)
!1918 = !DILocation(line: 803, column: 16, scope: !1852)
!1919 = !DILocation(line: 803, column: 19, scope: !1852)
!1920 = !DILocation(line: 803, column: 9, scope: !1852)
!1921 = !DILocation(line: 809, column: 9, scope: !1922)
!1922 = distinct !DILexicalBlock(scope: !171, file: !1, line: 809, column: 9)
!1923 = !DILocation(line: 809, column: 16, scope: !1922)
!1924 = !DILocation(line: 809, column: 9, scope: !171)
!1925 = !DILocation(line: 810, column: 19, scope: !1926)
!1926 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 809, column: 29)
!1927 = !DILocation(line: 810, column: 22, scope: !1926)
!1928 = !DILocation(line: 810, column: 16, scope: !1926)
!1929 = !DILocation(line: 811, column: 5, scope: !1926)
!1930 = !DILocation(line: 812, column: 9, scope: !1931)
!1931 = distinct !DILexicalBlock(scope: !171, file: !1, line: 812, column: 9)
!1932 = !DILocation(line: 812, column: 16, scope: !1931)
!1933 = !DILocation(line: 812, column: 9, scope: !171)
!1934 = !DILocation(line: 812, column: 21, scope: !1935)
!1935 = !DILexicalBlockFile(scope: !1931, file: !1, discriminator: 1)
!1936 = !DILocation(line: 814, column: 9, scope: !1937)
!1937 = distinct !DILexicalBlock(scope: !171, file: !1, line: 814, column: 9)
!1938 = !DILocation(line: 814, column: 12, scope: !1937)
!1939 = !DILocation(line: 814, column: 9, scope: !171)
!1940 = !DILocation(line: 816, column: 9, scope: !1941)
!1941 = distinct !DILexicalBlock(scope: !1937, file: !1, line: 814, column: 25)
!1942 = !DILocation(line: 816, column: 12, scope: !1941)
!1943 = !DILocation(line: 816, column: 17, scope: !1941)
!1944 = !DILocation(line: 817, column: 9, scope: !1941)
!1945 = !DILocation(line: 817, column: 12, scope: !1941)
!1946 = !DILocation(line: 817, column: 19, scope: !1941)
!1947 = !DILocation(line: 817, column: 28, scope: !1941)
!1948 = !DILocation(line: 818, column: 29, scope: !1941)
!1949 = !DILocation(line: 818, column: 32, scope: !1941)
!1950 = !DILocation(line: 818, column: 9, scope: !1941)
!1951 = !DILocation(line: 818, column: 12, scope: !1941)
!1952 = !DILocation(line: 818, column: 19, scope: !1941)
!1953 = !DILocation(line: 818, column: 27, scope: !1941)
!1954 = !DILocation(line: 819, column: 19, scope: !1955)
!1955 = distinct !DILexicalBlock(scope: !1941, file: !1, line: 819, column: 13)
!1956 = !DILocation(line: 819, column: 22, scope: !1955)
!1957 = !DILocation(line: 819, column: 28, scope: !1955)
!1958 = !DILocation(line: 819, column: 13, scope: !1955)
!1959 = !DILocation(line: 819, column: 46, scope: !1955)
!1960 = !DILocation(line: 819, column: 13, scope: !1941)
!1961 = !DILocation(line: 819, column: 51, scope: !1962)
!1962 = !DILexicalBlockFile(scope: !1955, file: !1, discriminator: 1)
!1963 = !DILocation(line: 821, column: 26, scope: !1941)
!1964 = !DILocation(line: 821, column: 17, scope: !1941)
!1965 = !DILocation(line: 821, column: 20, scope: !1941)
!1966 = !DILocation(line: 821, column: 24, scope: !1941)
!1967 = !DILocation(line: 821, column: 9, scope: !1941)
!1968 = !DILocation(line: 821, column: 12, scope: !1941)
!1969 = !DILocation(line: 821, column: 15, scope: !1941)
!1970 = !DILocation(line: 822, column: 16, scope: !1941)
!1971 = !DILocation(line: 822, column: 9, scope: !1941)
!1972 = !DILocation(line: 826, column: 9, scope: !1973)
!1973 = distinct !DILexicalBlock(scope: !171, file: !1, line: 826, column: 9)
!1974 = !DILocation(line: 826, column: 19, scope: !1973)
!1975 = !DILocation(line: 826, column: 22, scope: !1973)
!1976 = !DILocation(line: 826, column: 16, scope: !1973)
!1977 = !DILocation(line: 826, column: 9, scope: !171)
!1978 = !DILocation(line: 827, column: 19, scope: !1979)
!1979 = distinct !DILexicalBlock(scope: !1973, file: !1, line: 826, column: 27)
!1980 = !DILocation(line: 827, column: 22, scope: !1979)
!1981 = !DILocation(line: 827, column: 16, scope: !1979)
!1982 = !DILocation(line: 828, column: 5, scope: !1979)
!1983 = !DILocation(line: 828, column: 25, scope: !1984)
!1984 = !DILexicalBlockFile(scope: !1985, file: !1, discriminator: 1)
!1985 = distinct !DILexicalBlock(scope: !1973, file: !1, line: 828, column: 16)
!1986 = !DILocation(line: 828, column: 16, scope: !1984)
!1987 = !DILocation(line: 828, column: 31, scope: !1984)
!1988 = !DILocation(line: 829, column: 9, scope: !1989)
!1989 = distinct !DILexicalBlock(scope: !1985, file: !1, line: 828, column: 36)
!1990 = !DILocation(line: 833, column: 9, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !171, file: !1, line: 833, column: 9)
!1992 = !DILocation(line: 833, column: 16, scope: !1991)
!1993 = !DILocation(line: 833, column: 21, scope: !1991)
!1994 = !DILocation(line: 833, column: 24, scope: !1995)
!1995 = !DILexicalBlockFile(scope: !1991, file: !1, discriminator: 1)
!1996 = !DILocation(line: 833, column: 27, scope: !1995)
!1997 = !DILocation(line: 833, column: 34, scope: !1995)
!1998 = !DILocation(line: 833, column: 9, scope: !1995)
!1999 = !DILocation(line: 834, column: 28, scope: !2000)
!2000 = distinct !DILexicalBlock(scope: !1991, file: !1, line: 833, column: 45)
!2001 = !DILocation(line: 834, column: 9, scope: !2000)
!2002 = !DILocation(line: 834, column: 12, scope: !2000)
!2003 = !DILocation(line: 834, column: 19, scope: !2000)
!2004 = !DILocation(line: 835, column: 13, scope: !2005)
!2005 = distinct !DILexicalBlock(scope: !2000, file: !1, line: 835, column: 13)
!2006 = !DILocation(line: 835, column: 16, scope: !2005)
!2007 = !DILocation(line: 835, column: 23, scope: !2005)
!2008 = !DILocation(line: 835, column: 13, scope: !2000)
!2009 = !DILocation(line: 835, column: 34, scope: !2010)
!2010 = !DILexicalBlockFile(scope: !2005, file: !1, discriminator: 1)
!2011 = !DILocation(line: 836, column: 5, scope: !2000)
!2012 = !DILocation(line: 837, column: 9, scope: !2013)
!2013 = distinct !DILexicalBlock(scope: !171, file: !1, line: 837, column: 9)
!2014 = !DILocation(line: 837, column: 16, scope: !2013)
!2015 = !DILocation(line: 837, column: 19, scope: !2016)
!2016 = !DILexicalBlockFile(scope: !2013, file: !1, discriminator: 1)
!2017 = !DILocation(line: 837, column: 22, scope: !2016)
!2018 = !DILocation(line: 837, column: 27, scope: !2016)
!2019 = !DILocation(line: 837, column: 9, scope: !2016)
!2020 = !DILocation(line: 838, column: 9, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 837, column: 35)
!2022 = !DILocation(line: 838, column: 12, scope: !2021)
!2023 = !DILocation(line: 838, column: 17, scope: !2021)
!2024 = !DILocation(line: 839, column: 9, scope: !2021)
!2025 = !DILocation(line: 839, column: 12, scope: !2021)
!2026 = !DILocation(line: 839, column: 15, scope: !2021)
!2027 = !DILocation(line: 840, column: 15, scope: !2021)
!2028 = !DILocation(line: 841, column: 13, scope: !2029)
!2029 = distinct !DILexicalBlock(scope: !2021, file: !1, line: 841, column: 13)
!2030 = !DILocation(line: 841, column: 16, scope: !2029)
!2031 = !DILocation(line: 841, column: 13, scope: !2021)
!2032 = !DILocation(line: 841, column: 22, scope: !2033)
!2033 = !DILexicalBlockFile(scope: !2029, file: !1, discriminator: 1)
!2034 = !DILocation(line: 841, column: 25, scope: !2033)
!2035 = !DILocation(line: 841, column: 31, scope: !2033)
!2036 = !DILocation(line: 842, column: 5, scope: !2021)
!2037 = !DILocation(line: 843, column: 5, scope: !171)
!2038 = !DILocation(line: 843, column: 12, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !171, file: !1, discriminator: 1)
!2040 = !DILocation(line: 843, column: 19, scope: !2039)
!2041 = !DILocation(line: 843, column: 5, scope: !2039)
!2042 = !DILocalVariable(name: "size", scope: !2043, file: !1, line: 844, type: !39)
!2043 = distinct !DILexicalBlock(scope: !171, file: !1, line: 843, column: 25)
!2044 = !DILocation(line: 844, column: 13, scope: !2043)
!2045 = !DILocation(line: 845, column: 13, scope: !2046)
!2046 = distinct !DILexicalBlock(scope: !2043, file: !1, line: 845, column: 13)
!2047 = !DILocation(line: 845, column: 20, scope: !2046)
!2048 = !DILocation(line: 845, column: 13, scope: !2043)
!2049 = !DILocation(line: 845, column: 45, scope: !2050)
!2050 = !DILexicalBlockFile(scope: !2046, file: !1, discriminator: 1)
!2051 = !DILocation(line: 845, column: 40, scope: !2050)
!2052 = !DILocation(line: 845, column: 38, scope: !2050)
!2053 = !DILocation(line: 845, column: 33, scope: !2050)
!2054 = !DILocation(line: 847, column: 23, scope: !2043)
!2055 = !DILocation(line: 847, column: 29, scope: !2043)
!2056 = !DILocation(line: 847, column: 32, scope: !2043)
!2057 = !DILocation(line: 847, column: 46, scope: !2043)
!2058 = !DILocation(line: 847, column: 16, scope: !2043)
!2059 = !DILocation(line: 847, column: 14, scope: !2043)
!2060 = !DILocation(line: 848, column: 13, scope: !2061)
!2061 = distinct !DILexicalBlock(scope: !2043, file: !1, line: 848, column: 13)
!2062 = !DILocation(line: 848, column: 18, scope: !2061)
!2063 = !DILocation(line: 848, column: 13, scope: !2043)
!2064 = !DILocation(line: 848, column: 24, scope: !2065)
!2065 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 1)
!2066 = !DILocation(line: 849, column: 19, scope: !2043)
!2067 = !DILocation(line: 849, column: 16, scope: !2043)
!2068 = !DILocation(line: 843, column: 5, scope: !1842)
!2069 = !DILocation(line: 851, column: 12, scope: !171)
!2070 = !DILocation(line: 851, column: 15, scope: !171)
!2071 = !DILocation(line: 851, column: 5, scope: !171)
!2072 = !DILocation(line: 852, column: 1, scope: !171)
!2073 = !DILocalVariable(name: "file", arg: 1, scope: !174, file: !1, line: 858, type: !4)
!2074 = !DILocation(line: 858, column: 12, scope: !174)
!2075 = !DILocalVariable(name: "s", scope: !174, file: !1, line: 860, type: !9)
!2076 = !DILocation(line: 860, column: 16, scope: !174)
!2077 = !DILocation(line: 860, column: 32, scope: !174)
!2078 = !DILocation(line: 860, column: 20, scope: !174)
!2079 = !DILocation(line: 862, column: 9, scope: !2080)
!2080 = distinct !DILexicalBlock(scope: !174, file: !1, line: 862, column: 9)
!2081 = !DILocation(line: 862, column: 11, scope: !2080)
!2082 = !DILocation(line: 862, column: 19, scope: !2080)
!2083 = !DILocation(line: 862, column: 22, scope: !2084)
!2084 = !DILexicalBlockFile(scope: !2080, file: !1, discriminator: 1)
!2085 = !DILocation(line: 862, column: 25, scope: !2084)
!2086 = !DILocation(line: 862, column: 30, scope: !2084)
!2087 = !DILocation(line: 862, column: 9, scope: !2084)
!2088 = !DILocation(line: 862, column: 38, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2080, file: !1, discriminator: 2)
!2090 = !DILocation(line: 864, column: 5, scope: !174)
!2091 = !DILocation(line: 864, column: 8, scope: !174)
!2092 = !DILocation(line: 864, column: 14, scope: !174)
!2093 = !DILocation(line: 865, column: 5, scope: !174)
!2094 = !DILocation(line: 865, column: 8, scope: !174)
!2095 = !DILocation(line: 865, column: 14, scope: !174)
!2096 = !DILocation(line: 866, column: 5, scope: !174)
!2097 = !DILocation(line: 866, column: 8, scope: !174)
!2098 = !DILocation(line: 866, column: 13, scope: !174)
!2099 = !DILocation(line: 867, column: 5, scope: !174)
!2100 = !DILocation(line: 867, column: 8, scope: !174)
!2101 = !DILocation(line: 867, column: 15, scope: !174)
!2102 = !DILocation(line: 867, column: 24, scope: !174)
!2103 = !DILocation(line: 868, column: 25, scope: !174)
!2104 = !DILocation(line: 868, column: 28, scope: !174)
!2105 = !DILocation(line: 868, column: 5, scope: !174)
!2106 = !DILocation(line: 868, column: 8, scope: !174)
!2107 = !DILocation(line: 868, column: 15, scope: !174)
!2108 = !DILocation(line: 868, column: 23, scope: !174)
!2109 = !DILocation(line: 869, column: 14, scope: !174)
!2110 = !DILocation(line: 869, column: 5, scope: !174)
!2111 = !DILocation(line: 869, column: 8, scope: !174)
!2112 = !DILocation(line: 869, column: 12, scope: !174)
!2113 = !DILocation(line: 870, column: 10, scope: !2114)
!2114 = distinct !DILexicalBlock(scope: !174, file: !1, line: 870, column: 9)
!2115 = !DILocation(line: 870, column: 13, scope: !2114)
!2116 = !DILocation(line: 870, column: 9, scope: !174)
!2117 = !DILocation(line: 870, column: 46, scope: !2118)
!2118 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 1)
!2119 = !DILocation(line: 870, column: 49, scope: !2118)
!2120 = !DILocation(line: 870, column: 32, scope: !2118)
!2121 = !DILocation(line: 870, column: 26, scope: !2118)
!2122 = !DILocation(line: 871, column: 5, scope: !174)
!2123 = !DILocation(line: 871, column: 8, scope: !174)
!2124 = !DILocation(line: 871, column: 11, scope: !174)
!2125 = !DILocation(line: 872, column: 5, scope: !174)
!2126 = !DILocation(line: 872, column: 8, scope: !174)
!2127 = !DILocation(line: 872, column: 12, scope: !174)
!2128 = !DILocation(line: 873, column: 18, scope: !174)
!2129 = !DILocation(line: 873, column: 21, scope: !174)
!2130 = !DILocation(line: 873, column: 27, scope: !174)
!2131 = !DILocation(line: 873, column: 30, scope: !174)
!2132 = !DILocation(line: 873, column: 12, scope: !174)
!2133 = !DILocation(line: 873, column: 5, scope: !174)
!2134 = !DILocation(line: 874, column: 1, scope: !174)
!2135 = !DILocalVariable(name: "file", arg: 1, scope: !175, file: !1, line: 882, type: !4)
!2136 = !DILocation(line: 882, column: 12, scope: !175)
!2137 = !DILocation(line: 884, column: 19, scope: !175)
!2138 = !DILocation(line: 884, column: 12, scope: !175)
!2139 = !DILocation(line: 884, column: 5, scope: !175)
!2140 = !DILocalVariable(name: "file", arg: 1, scope: !178, file: !1, line: 892, type: !4)
!2141 = !DILocation(line: 892, column: 12, scope: !178)
!2142 = !DILocalVariable(name: "s", scope: !178, file: !1, line: 894, type: !9)
!2143 = !DILocation(line: 894, column: 16, scope: !178)
!2144 = !DILocation(line: 894, column: 32, scope: !178)
!2145 = !DILocation(line: 894, column: 20, scope: !178)
!2146 = !DILocation(line: 900, column: 9, scope: !2147)
!2147 = distinct !DILexicalBlock(scope: !178, file: !1, line: 900, column: 9)
!2148 = !DILocation(line: 900, column: 11, scope: !2147)
!2149 = !DILocation(line: 900, column: 19, scope: !2147)
!2150 = !DILocation(line: 900, column: 22, scope: !2151)
!2151 = !DILexicalBlockFile(scope: !2147, file: !1, discriminator: 1)
!2152 = !DILocation(line: 900, column: 25, scope: !2151)
!2153 = !DILocation(line: 900, column: 30, scope: !2151)
!2154 = !DILocation(line: 900, column: 9, scope: !2151)
!2155 = !DILocation(line: 900, column: 38, scope: !2156)
!2156 = !DILexicalBlockFile(scope: !2147, file: !1, discriminator: 2)
!2157 = !DILocation(line: 901, column: 9, scope: !2158)
!2158 = distinct !DILexicalBlock(scope: !178, file: !1, line: 901, column: 9)
!2159 = !DILocation(line: 901, column: 12, scope: !2158)
!2160 = !DILocation(line: 901, column: 9, scope: !178)
!2161 = !DILocation(line: 901, column: 19, scope: !2162)
!2162 = !DILexicalBlockFile(scope: !2158, file: !1, discriminator: 1)
!2163 = !DILocation(line: 902, column: 12, scope: !178)
!2164 = !DILocation(line: 902, column: 15, scope: !178)
!2165 = !DILocation(line: 902, column: 21, scope: !178)
!2166 = !DILocation(line: 902, column: 5, scope: !178)
!2167 = !DILocation(line: 903, column: 1, scope: !178)
!2168 = !DILocalVariable(name: "file", arg: 1, scope: !179, file: !1, line: 909, type: !4)
!2169 = !DILocation(line: 909, column: 12, scope: !179)
!2170 = !DILocalVariable(name: "s", scope: !179, file: !1, line: 911, type: !9)
!2171 = !DILocation(line: 911, column: 16, scope: !179)
!2172 = !DILocation(line: 911, column: 32, scope: !179)
!2173 = !DILocation(line: 911, column: 20, scope: !179)
!2174 = !DILocation(line: 913, column: 9, scope: !2175)
!2175 = distinct !DILexicalBlock(scope: !179, file: !1, line: 913, column: 9)
!2176 = !DILocation(line: 913, column: 11, scope: !2175)
!2177 = !DILocation(line: 913, column: 19, scope: !2175)
!2178 = !DILocation(line: 913, column: 22, scope: !2179)
!2179 = !DILexicalBlockFile(scope: !2175, file: !1, discriminator: 1)
!2180 = !DILocation(line: 913, column: 25, scope: !2179)
!2181 = !DILocation(line: 913, column: 30, scope: !2179)
!2182 = !DILocation(line: 913, column: 9, scope: !2179)
!2183 = !DILocation(line: 913, column: 38, scope: !2184)
!2184 = !DILexicalBlockFile(scope: !2175, file: !1, discriminator: 2)
!2185 = !DILocation(line: 914, column: 12, scope: !179)
!2186 = !DILocation(line: 914, column: 15, scope: !179)
!2187 = !DILocation(line: 914, column: 5, scope: !179)
!2188 = !DILocation(line: 915, column: 1, scope: !179)
!2189 = !DILocalVariable(name: "file", arg: 1, scope: !180, file: !1, line: 954, type: !4)
!2190 = !DILocation(line: 954, column: 12, scope: !180)
!2191 = !DILocalVariable(name: "s", scope: !180, file: !1, line: 956, type: !9)
!2192 = !DILocation(line: 956, column: 16, scope: !180)
!2193 = !DILocation(line: 956, column: 32, scope: !180)
!2194 = !DILocation(line: 956, column: 20, scope: !180)
!2195 = !DILocation(line: 958, column: 9, scope: !2196)
!2196 = distinct !DILexicalBlock(scope: !180, file: !1, line: 958, column: 9)
!2197 = !DILocation(line: 958, column: 11, scope: !2196)
!2198 = !DILocation(line: 958, column: 9, scope: !180)
!2199 = !DILocation(line: 958, column: 20, scope: !2200)
!2200 = !DILexicalBlockFile(scope: !2196, file: !1, discriminator: 1)
!2201 = !DILocation(line: 960, column: 9, scope: !2202)
!2202 = distinct !DILexicalBlock(scope: !180, file: !1, line: 960, column: 9)
!2203 = !DILocation(line: 960, column: 12, scope: !2202)
!2204 = !DILocation(line: 960, column: 17, scope: !2202)
!2205 = !DILocation(line: 960, column: 9, scope: !180)
!2206 = !DILocation(line: 964, column: 23, scope: !2207)
!2207 = distinct !DILexicalBlock(scope: !2208, file: !1, line: 964, column: 13)
!2208 = distinct !DILexicalBlock(scope: !2202, file: !1, line: 960, column: 25)
!2209 = !DILocation(line: 964, column: 13, scope: !2207)
!2210 = !DILocation(line: 964, column: 39, scope: !2207)
!2211 = !DILocation(line: 964, column: 13, scope: !2208)
!2212 = !DILocation(line: 965, column: 40, scope: !2207)
!2213 = !DILocation(line: 965, column: 28, scope: !2207)
!2214 = !DILocation(line: 965, column: 20, scope: !2207)
!2215 = !DILocation(line: 965, column: 13, scope: !2207)
!2216 = !DILocation(line: 967, column: 18, scope: !2208)
!2217 = !DILocation(line: 967, column: 21, scope: !2208)
!2218 = !DILocation(line: 967, column: 27, scope: !2208)
!2219 = !DILocation(line: 967, column: 30, scope: !2208)
!2220 = !DILocation(line: 967, column: 9, scope: !2208)
!2221 = !DILocation(line: 968, column: 18, scope: !2208)
!2222 = !DILocation(line: 968, column: 21, scope: !2208)
!2223 = !DILocation(line: 968, column: 35, scope: !2208)
!2224 = !DILocation(line: 968, column: 38, scope: !2208)
!2225 = !DILocation(line: 968, column: 41, scope: !2208)
!2226 = !DILocation(line: 968, column: 9, scope: !2208)
!2227 = !DILocation(line: 970, column: 5, scope: !2208)
!2228 = !DILocation(line: 971, column: 32, scope: !180)
!2229 = !DILocation(line: 971, column: 20, scope: !180)
!2230 = !DILocation(line: 971, column: 12, scope: !180)
!2231 = !DILocation(line: 971, column: 5, scope: !180)
!2232 = !DILocation(line: 972, column: 1, scope: !180)
!2233 = !DILocalVariable(name: "s", arg: 1, scope: !201, file: !1, line: 356, type: !9)
!2234 = !DILocation(line: 356, column: 16, scope: !201)
!2235 = !DILocalVariable(name: "err", scope: !201, file: !1, line: 358, type: !39)
!2236 = !DILocation(line: 358, column: 9, scope: !201)
!2237 = !DILocation(line: 360, column: 10, scope: !2238)
!2238 = distinct !DILexicalBlock(scope: !201, file: !1, line: 360, column: 9)
!2239 = !DILocation(line: 360, column: 9, scope: !201)
!2240 = !DILocation(line: 360, column: 13, scope: !2241)
!2241 = !DILexicalBlockFile(scope: !2238, file: !1, discriminator: 1)
!2242 = !DILocation(line: 362, column: 5, scope: !2243)
!2243 = distinct !DILexicalBlock(scope: !2244, file: !1, line: 362, column: 5)
!2244 = distinct !DILexicalBlock(scope: !201, file: !1, line: 362, column: 5)
!2245 = !DILocation(line: 362, column: 5, scope: !2244)
!2246 = !DILocation(line: 362, column: 5, scope: !2247)
!2247 = !DILexicalBlockFile(scope: !2243, file: !1, discriminator: 1)
!2248 = !DILocation(line: 364, column: 9, scope: !2249)
!2249 = distinct !DILexicalBlock(scope: !201, file: !1, line: 364, column: 9)
!2250 = !DILocation(line: 364, column: 12, scope: !2249)
!2251 = !DILocation(line: 364, column: 19, scope: !2249)
!2252 = !DILocation(line: 364, column: 25, scope: !2249)
!2253 = !DILocation(line: 364, column: 9, scope: !201)
!2254 = !DILocation(line: 365, column: 13, scope: !2255)
!2255 = distinct !DILexicalBlock(scope: !2256, file: !1, line: 365, column: 13)
!2256 = distinct !DILexicalBlock(scope: !2249, file: !1, line: 364, column: 34)
!2257 = !DILocation(line: 365, column: 16, scope: !2255)
!2258 = !DILocation(line: 365, column: 21, scope: !2255)
!2259 = !DILocation(line: 365, column: 13, scope: !2256)
!2260 = !DILocation(line: 369, column: 32, scope: !2261)
!2261 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 365, column: 29)
!2262 = !DILocation(line: 369, column: 35, scope: !2261)
!2263 = !DILocation(line: 369, column: 19, scope: !2261)
!2264 = !DILocation(line: 369, column: 17, scope: !2261)
!2265 = !DILocation(line: 371, column: 9, scope: !2261)
!2266 = !DILocation(line: 371, column: 20, scope: !2267)
!2267 = !DILexicalBlockFile(scope: !2268, file: !1, discriminator: 1)
!2268 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 371, column: 20)
!2269 = !DILocation(line: 371, column: 23, scope: !2267)
!2270 = !DILocation(line: 371, column: 28, scope: !2267)
!2271 = !DILocation(line: 372, column: 32, scope: !2272)
!2272 = distinct !DILexicalBlock(scope: !2268, file: !1, line: 371, column: 36)
!2273 = !DILocation(line: 372, column: 35, scope: !2272)
!2274 = !DILocation(line: 372, column: 19, scope: !2272)
!2275 = !DILocation(line: 372, column: 17, scope: !2272)
!2276 = !DILocation(line: 373, column: 9, scope: !2272)
!2277 = !DILocation(line: 374, column: 5, scope: !2256)
!2278 = !DILocation(line: 375, column: 9, scope: !2279)
!2279 = distinct !DILexicalBlock(scope: !201, file: !1, line: 375, column: 9)
!2280 = !DILocation(line: 375, column: 12, scope: !2279)
!2281 = !DILocation(line: 375, column: 17, scope: !2279)
!2282 = !DILocation(line: 375, column: 25, scope: !2279)
!2283 = !DILocation(line: 375, column: 35, scope: !2284)
!2284 = !DILexicalBlockFile(scope: !2279, file: !1, discriminator: 1)
!2285 = !DILocation(line: 375, column: 38, scope: !2284)
!2286 = !DILocation(line: 375, column: 28, scope: !2284)
!2287 = !DILocation(line: 375, column: 9, scope: !2284)
!2288 = !DILocation(line: 377, column: 13, scope: !2289)
!2289 = distinct !DILexicalBlock(scope: !2290, file: !1, line: 377, column: 13)
!2290 = distinct !DILexicalBlock(scope: !2279, file: !1, line: 375, column: 45)
!2291 = !DILocation(line: 377, column: 19, scope: !2289)
!2292 = !DILocation(line: 377, column: 13, scope: !2290)
!2293 = !DILocation(line: 379, column: 17, scope: !2289)
!2294 = !DILocation(line: 379, column: 13, scope: !2289)
!2295 = !DILocation(line: 380, column: 5, scope: !2290)
!2296 = !DILocation(line: 381, column: 9, scope: !2297)
!2297 = distinct !DILexicalBlock(scope: !201, file: !1, line: 381, column: 9)
!2298 = !DILocation(line: 381, column: 12, scope: !2297)
!2299 = !DILocation(line: 381, column: 18, scope: !2297)
!2300 = !DILocation(line: 381, column: 9, scope: !201)
!2301 = !DILocation(line: 381, column: 29, scope: !2302)
!2302 = !DILexicalBlockFile(scope: !2297, file: !1, discriminator: 1)
!2303 = !DILocation(line: 381, column: 32, scope: !2302)
!2304 = !DILocation(line: 381, column: 27, scope: !2302)
!2305 = !DILocation(line: 381, column: 23, scope: !2302)
!2306 = !DILocation(line: 383, column: 5, scope: !2307)
!2307 = distinct !DILexicalBlock(scope: !2308, file: !1, line: 383, column: 5)
!2308 = distinct !DILexicalBlock(scope: !201, file: !1, line: 383, column: 5)
!2309 = !DILocation(line: 383, column: 5, scope: !2308)
!2310 = !DILocation(line: 383, column: 5, scope: !2311)
!2311 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 1)
!2312 = !DILocation(line: 384, column: 5, scope: !2313)
!2313 = distinct !DILexicalBlock(scope: !2314, file: !1, line: 384, column: 5)
!2314 = distinct !DILexicalBlock(scope: !201, file: !1, line: 384, column: 5)
!2315 = !DILocation(line: 384, column: 5, scope: !2314)
!2316 = !DILocation(line: 384, column: 5, scope: !2317)
!2317 = !DILexicalBlockFile(scope: !2313, file: !1, discriminator: 1)
!2318 = !DILocation(line: 385, column: 5, scope: !2319)
!2319 = distinct !DILexicalBlock(scope: !2320, file: !1, line: 385, column: 5)
!2320 = distinct !DILexicalBlock(scope: !201, file: !1, line: 385, column: 5)
!2321 = !DILocation(line: 385, column: 5, scope: !2320)
!2322 = !DILocation(line: 385, column: 5, scope: !2323)
!2323 = !DILexicalBlockFile(scope: !2319, file: !1, discriminator: 1)
!2324 = !DILocation(line: 386, column: 5, scope: !2325)
!2325 = distinct !DILexicalBlock(scope: !2326, file: !1, line: 386, column: 5)
!2326 = distinct !DILexicalBlock(scope: !201, file: !1, line: 386, column: 5)
!2327 = !DILocation(line: 386, column: 5, scope: !2326)
!2328 = !DILocation(line: 386, column: 5, scope: !2329)
!2329 = !DILexicalBlockFile(scope: !2325, file: !1, discriminator: 1)
!2330 = !DILocation(line: 387, column: 12, scope: !201)
!2331 = !DILocation(line: 387, column: 5, scope: !201)
!2332 = !DILocation(line: 388, column: 1, scope: !201)
!2333 = !DILocalVariable(name: "file", arg: 1, scope: !202, file: !1, line: 921, type: !58)
!2334 = !DILocation(line: 921, column: 11, scope: !202)
!2335 = !DILocalVariable(name: "x", arg: 2, scope: !202, file: !1, line: 922, type: !26)
!2336 = !DILocation(line: 922, column: 11, scope: !202)
!2337 = !DILocalVariable(name: "n", scope: !202, file: !1, line: 924, type: !39)
!2338 = !DILocation(line: 924, column: 9, scope: !202)
!2339 = !DILocation(line: 925, column: 12, scope: !2340)
!2340 = distinct !DILexicalBlock(scope: !202, file: !1, line: 925, column: 5)
!2341 = !DILocation(line: 925, column: 10, scope: !2340)
!2342 = !DILocation(line: 925, column: 17, scope: !2343)
!2343 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 1)
!2344 = distinct !DILexicalBlock(scope: !2340, file: !1, line: 925, column: 5)
!2345 = !DILocation(line: 925, column: 19, scope: !2343)
!2346 = !DILocation(line: 925, column: 5, scope: !2343)
!2347 = !DILocation(line: 926, column: 21, scope: !2348)
!2348 = distinct !DILexicalBlock(scope: !2344, file: !1, line: 925, column: 29)
!2349 = !DILocation(line: 926, column: 23, scope: !2348)
!2350 = !DILocation(line: 926, column: 15, scope: !2348)
!2351 = !DILocation(line: 926, column: 32, scope: !2348)
!2352 = !DILocation(line: 926, column: 9, scope: !2348)
!2353 = !DILocation(line: 927, column: 11, scope: !2348)
!2354 = !DILocation(line: 928, column: 5, scope: !2348)
!2355 = !DILocation(line: 925, column: 25, scope: !2356)
!2356 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 2)
!2357 = !DILocation(line: 925, column: 5, scope: !2356)
!2358 = !DILocation(line: 929, column: 1, scope: !202)
!2359 = !DILocalVariable(name: "file", arg: 1, scope: !181, file: !1, line: 988, type: !4)
!2360 = !DILocation(line: 988, column: 12, scope: !181)
!2361 = !DILocalVariable(name: "errnum", arg: 2, scope: !181, file: !1, line: 989, type: !184)
!2362 = !DILocation(line: 989, column: 10, scope: !181)
!2363 = !DILocalVariable(name: "m", scope: !181, file: !1, line: 991, type: !32)
!2364 = !DILocation(line: 991, column: 11, scope: !181)
!2365 = !DILocalVariable(name: "s", scope: !181, file: !1, line: 992, type: !9)
!2366 = !DILocation(line: 992, column: 16, scope: !181)
!2367 = !DILocation(line: 992, column: 32, scope: !181)
!2368 = !DILocation(line: 992, column: 20, scope: !181)
!2369 = !DILocation(line: 994, column: 9, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !181, file: !1, line: 994, column: 9)
!2371 = !DILocation(line: 994, column: 11, scope: !2370)
!2372 = !DILocation(line: 994, column: 9, scope: !181)
!2373 = !DILocation(line: 995, column: 10, scope: !2374)
!2374 = distinct !DILexicalBlock(scope: !2370, file: !1, line: 994, column: 20)
!2375 = !DILocation(line: 995, column: 17, scope: !2374)
!2376 = !DILocation(line: 996, column: 29, scope: !2374)
!2377 = !DILocation(line: 996, column: 9, scope: !2374)
!2378 = !DILocation(line: 998, column: 15, scope: !181)
!2379 = !DILocation(line: 998, column: 18, scope: !181)
!2380 = !DILocation(line: 998, column: 6, scope: !181)
!2381 = !DILocation(line: 998, column: 13, scope: !181)
!2382 = !DILocation(line: 999, column: 10, scope: !2383)
!2383 = distinct !DILexicalBlock(scope: !181, file: !1, line: 999, column: 9)
!2384 = !DILocation(line: 999, column: 9, scope: !2383)
!2385 = !DILocation(line: 999, column: 17, scope: !2383)
!2386 = !DILocation(line: 999, column: 9, scope: !181)
!2387 = !DILocation(line: 999, column: 26, scope: !2388)
!2388 = !DILexicalBlockFile(scope: !2383, file: !1, discriminator: 1)
!2389 = !DILocation(line: 1001, column: 18, scope: !181)
!2390 = !DILocation(line: 1001, column: 17, scope: !181)
!2391 = !DILocation(line: 1001, column: 25, scope: !181)
!2392 = !DILocation(line: 1001, column: 38, scope: !2393)
!2393 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 1)
!2394 = !DILocation(line: 1001, column: 38, scope: !2395)
!2395 = !DILexicalBlockFile(scope: !2393, file: !1, discriminator: 4)
!2396 = !DILocation(line: 1001, column: 17, scope: !2393)
!2397 = !DILocation(line: 1001, column: 57, scope: !2398)
!2398 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 2)
!2399 = !DILocation(line: 1001, column: 60, scope: !2398)
!2400 = !DILocation(line: 1001, column: 67, scope: !2398)
!2401 = !DILocation(line: 1001, column: 17, scope: !2398)
!2402 = !DILocation(line: 1001, column: 17, scope: !2403)
!2403 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 3)
!2404 = !DILocation(line: 1001, column: 7, scope: !2403)
!2405 = !DILocation(line: 1003, column: 9, scope: !2406)
!2406 = distinct !DILexicalBlock(scope: !181, file: !1, line: 1003, column: 9)
!2407 = !DILocation(line: 1003, column: 11, scope: !2406)
!2408 = !DILocation(line: 1003, column: 19, scope: !2406)
!2409 = !DILocation(line: 1003, column: 23, scope: !2410)
!2410 = !DILexicalBlockFile(scope: !2406, file: !1, discriminator: 1)
!2411 = !DILocation(line: 1003, column: 22, scope: !2410)
!2412 = !DILocation(line: 1003, column: 25, scope: !2410)
!2413 = !DILocation(line: 1003, column: 9, scope: !2410)
!2414 = !DILocation(line: 1003, column: 45, scope: !2415)
!2415 = !DILexicalBlockFile(scope: !2406, file: !1, discriminator: 2)
!2416 = !DILocation(line: 1003, column: 36, scope: !2415)
!2417 = !DILocation(line: 1003, column: 34, scope: !2415)
!2418 = !DILocation(line: 1005, column: 5, scope: !2419)
!2419 = distinct !DILexicalBlock(scope: !2420, file: !1, line: 1005, column: 5)
!2420 = distinct !DILexicalBlock(scope: !181, file: !1, line: 1005, column: 5)
!2421 = !DILocation(line: 1005, column: 5, scope: !2420)
!2422 = !DILocation(line: 1005, column: 5, scope: !2423)
!2423 = !DILexicalBlockFile(scope: !2419, file: !1, discriminator: 1)
!2424 = !DILocation(line: 1006, column: 21, scope: !181)
!2425 = !DILocation(line: 1006, column: 21, scope: !2393)
!2426 = !DILocation(line: 1006, column: 21, scope: !2398)
!2427 = !DILocation(line: 1006, column: 5, scope: !181)
!2428 = !DILocation(line: 1006, column: 8, scope: !181)
!2429 = !DILocation(line: 1006, column: 12, scope: !181)
!2430 = !DILocation(line: 1007, column: 9, scope: !2431)
!2431 = distinct !DILexicalBlock(scope: !181, file: !1, line: 1007, column: 9)
!2432 = !DILocation(line: 1007, column: 12, scope: !2431)
!2433 = !DILocation(line: 1007, column: 16, scope: !2431)
!2434 = !DILocation(line: 1007, column: 9, scope: !181)
!2435 = !DILocation(line: 1007, column: 47, scope: !2436)
!2436 = !DILexicalBlockFile(scope: !2431, file: !1, discriminator: 1)
!2437 = !DILocation(line: 1007, column: 27, scope: !2436)
!2438 = !DILocation(line: 1008, column: 12, scope: !181)
!2439 = !DILocation(line: 1008, column: 15, scope: !181)
!2440 = !DILocation(line: 1008, column: 20, scope: !181)
!2441 = !DILocation(line: 1008, column: 23, scope: !181)
!2442 = !DILocation(line: 1008, column: 5, scope: !181)
!2443 = !DILocation(line: 1009, column: 12, scope: !181)
!2444 = !DILocation(line: 1009, column: 15, scope: !181)
!2445 = !DILocation(line: 1009, column: 5, scope: !181)
!2446 = !DILocation(line: 1010, column: 12, scope: !181)
!2447 = !DILocation(line: 1010, column: 15, scope: !181)
!2448 = !DILocation(line: 1010, column: 20, scope: !181)
!2449 = !DILocation(line: 1010, column: 5, scope: !181)
!2450 = !DILocation(line: 1011, column: 25, scope: !181)
!2451 = !DILocation(line: 1011, column: 28, scope: !181)
!2452 = !DILocation(line: 1011, column: 5, scope: !181)
!2453 = !DILocation(line: 1012, column: 1, scope: !181)
!2454 = !DILocalVariable(name: "file", arg: 1, scope: !185, file: !1, line: 1018, type: !4)
!2455 = !DILocation(line: 1018, column: 12, scope: !185)
!2456 = !DILocalVariable(name: "s", scope: !185, file: !1, line: 1020, type: !9)
!2457 = !DILocation(line: 1020, column: 16, scope: !185)
!2458 = !DILocation(line: 1020, column: 32, scope: !185)
!2459 = !DILocation(line: 1020, column: 20, scope: !185)
!2460 = !DILocation(line: 1022, column: 9, scope: !2461)
!2461 = distinct !DILexicalBlock(scope: !185, file: !1, line: 1022, column: 9)
!2462 = !DILocation(line: 1022, column: 11, scope: !2461)
!2463 = !DILocation(line: 1022, column: 9, scope: !185)
!2464 = !DILocation(line: 1022, column: 20, scope: !2465)
!2465 = !DILexicalBlockFile(scope: !2461, file: !1, discriminator: 1)
!2466 = !DILocation(line: 1023, column: 9, scope: !2467)
!2467 = distinct !DILexicalBlock(scope: !185, file: !1, line: 1023, column: 9)
!2468 = !DILocation(line: 1023, column: 12, scope: !2467)
!2469 = !DILocation(line: 1023, column: 18, scope: !2467)
!2470 = !DILocation(line: 1023, column: 9, scope: !185)
!2471 = !DILocation(line: 1023, column: 35, scope: !2472)
!2472 = !DILexicalBlockFile(scope: !2467, file: !1, discriminator: 1)
!2473 = !DILocation(line: 1023, column: 38, scope: !2472)
!2474 = !DILocation(line: 1023, column: 44, scope: !2472)
!2475 = !DILocation(line: 1024, column: 5, scope: !185)
!2476 = !DILocation(line: 1024, column: 8, scope: !185)
!2477 = !DILocation(line: 1024, column: 14, scope: !185)
!2478 = !DILocation(line: 1025, column: 14, scope: !185)
!2479 = !DILocation(line: 1025, column: 17, scope: !185)
!2480 = !DILocation(line: 1025, column: 5, scope: !185)
!2481 = !DILocation(line: 1026, column: 1, scope: !185)
!2482 = !DILocation(line: 1026, column: 1, scope: !2483)
!2483 = !DILexicalBlockFile(scope: !185, file: !1, discriminator: 1)
!2484 = !DILocalVariable(name: "s", arg: 1, scope: !194, file: !1, line: 262, type: !9)
!2485 = !DILocation(line: 262, column: 16, scope: !194)
!2486 = !DILocation(line: 264, column: 9, scope: !2487)
!2487 = distinct !DILexicalBlock(scope: !194, file: !1, line: 264, column: 9)
!2488 = !DILocation(line: 264, column: 12, scope: !2487)
!2489 = !DILocation(line: 264, column: 9, scope: !194)
!2490 = !DILocation(line: 264, column: 19, scope: !2491)
!2491 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 1)
!2492 = !DILocation(line: 265, column: 9, scope: !2493)
!2493 = distinct !DILexicalBlock(scope: !194, file: !1, line: 265, column: 9)
!2494 = !DILocation(line: 265, column: 12, scope: !2493)
!2495 = !DILocation(line: 265, column: 19, scope: !2493)
!2496 = !DILocation(line: 265, column: 28, scope: !2493)
!2497 = !DILocation(line: 265, column: 9, scope: !194)
!2498 = !DILocation(line: 266, column: 9, scope: !2499)
!2499 = distinct !DILexicalBlock(scope: !2493, file: !1, line: 265, column: 34)
!2500 = !DILocation(line: 266, column: 15, scope: !2499)
!2501 = !DILocation(line: 267, column: 42, scope: !2499)
!2502 = !DILocation(line: 267, column: 45, scope: !2499)
!2503 = !DILocation(line: 267, column: 66, scope: !2499)
!2504 = !DILocation(line: 267, column: 69, scope: !2499)
!2505 = !DILocation(line: 267, column: 36, scope: !2499)
!2506 = !DILocation(line: 267, column: 30, scope: !2499)
!2507 = !DILocation(line: 267, column: 9, scope: !2499)
!2508 = !DILocation(line: 267, column: 12, scope: !2499)
!2509 = !DILocation(line: 267, column: 19, scope: !2499)
!2510 = !DILocation(line: 267, column: 28, scope: !2499)
!2511 = !DILocation(line: 268, column: 13, scope: !2512)
!2512 = distinct !DILexicalBlock(scope: !2499, file: !1, line: 268, column: 13)
!2513 = !DILocation(line: 268, column: 16, scope: !2512)
!2514 = !DILocation(line: 268, column: 23, scope: !2512)
!2515 = !DILocation(line: 268, column: 32, scope: !2512)
!2516 = !DILocation(line: 268, column: 13, scope: !2499)
!2517 = !DILocation(line: 269, column: 13, scope: !2518)
!2518 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 268, column: 38)
!2519 = !DILocation(line: 269, column: 16, scope: !2518)
!2520 = !DILocation(line: 269, column: 22, scope: !2518)
!2521 = !DILocation(line: 270, column: 24, scope: !2522)
!2522 = distinct !DILexicalBlock(scope: !2518, file: !1, line: 270, column: 17)
!2523 = !DILocation(line: 270, column: 27, scope: !2522)
!2524 = !DILocation(line: 270, column: 17, scope: !2522)
!2525 = !DILocation(line: 270, column: 17, scope: !2518)
!2526 = !DILocation(line: 270, column: 34, scope: !2527)
!2527 = !DILexicalBlockFile(scope: !2522, file: !1, discriminator: 1)
!2528 = !DILocation(line: 270, column: 37, scope: !2527)
!2529 = !DILocation(line: 270, column: 43, scope: !2527)
!2530 = !DILocation(line: 271, column: 13, scope: !2518)
!2531 = !DILocation(line: 273, column: 29, scope: !2499)
!2532 = !DILocation(line: 273, column: 32, scope: !2499)
!2533 = !DILocation(line: 273, column: 9, scope: !2499)
!2534 = !DILocation(line: 273, column: 12, scope: !2499)
!2535 = !DILocation(line: 273, column: 19, scope: !2499)
!2536 = !DILocation(line: 273, column: 27, scope: !2499)
!2537 = !DILocation(line: 274, column: 5, scope: !2499)
!2538 = !DILocation(line: 275, column: 5, scope: !194)
!2539 = !DILocation(line: 275, column: 8, scope: !194)
!2540 = !DILocation(line: 275, column: 15, scope: !194)
!2541 = !DILocation(line: 275, column: 23, scope: !194)
!2542 = !DILocation(line: 276, column: 14, scope: !194)
!2543 = !DILocation(line: 276, column: 17, scope: !194)
!2544 = !DILocation(line: 276, column: 24, scope: !194)
!2545 = !DILocation(line: 276, column: 32, scope: !194)
!2546 = !DILocation(line: 276, column: 12, scope: !194)
!2547 = !DILocation(line: 276, column: 5, scope: !194)
!2548 = !DILocation(line: 277, column: 1, scope: !194)
