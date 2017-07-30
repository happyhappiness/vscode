; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_fast.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_coder_s = type { %struct.lzma_range_encoder, i32, [4 x i32], [274 x %struct.lzma_match], i32, i32, i8, i8, i8, i32, i32, i32, [16 x [768 x i16]], [12 x [16 x i16]], [12 x i16], [12 x i16], [12 x i16], [12 x i16], [12 x [16 x i16]], [4 x [64 x i16]], [114 x i16], [16 x i16], %struct.lzma_length_encoder, %struct.lzma_length_encoder, [4 x [64 x i32]], [4 x [128 x i32]], i32, i32, [16 x i32], i32, i32, i32, [4096 x %struct.lzma_optimal] }
%struct.lzma_range_encoder = type { i64, i64, i32, i8, i64, i64, [58 x i32], [58 x i16*] }
%struct.lzma_match = type { i32, i32 }
%struct.lzma_length_encoder = type { i16, i16, [16 x [8 x i16]], [16 x [8 x i16]], [256 x i16], [16 x [272 x i32]], i32, [16 x i32] }
%struct.lzma_optimal = type { i32, i8, i8, i32, i32, i32, i32, i32, [4 x i32] }
%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }

@.str = private unnamed_addr constant [20 x i8] c"mf->read_ahead == 1\00", align 1
@.str.1 = private unnamed_addr constant [95 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_fast.c\00", align 1
@__PRETTY_FUNCTION__.lzma_lzma_optimum_fast = private unnamed_addr constant [109 x i8] c"void lzma_lzma_optimum_fast(lzma_coder *restrict, lzma_mf *restrict, uint32_t *restrict, uint32_t *restrict)\00", align 1

; Function Attrs: nounwind uwtable
define void @lzma_lzma_optimum_fast(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i32* noalias %back_res, i32* noalias %len_res) #0 !dbg !65 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %back_res.addr = alloca i32*, align 8
  %len_res.addr = alloca i32*, align 8
  %buf = alloca i8*, align 8
  %buf_avail = alloca i32, align 4
  %i = alloca i32, align 4
  %rep_len = alloca i32, align 4
  %rep_index = alloca i32, align 4
  %back_main = alloca i32, align 4
  %limit = alloca i32, align 4
  %nice_len = alloca i32, align 4
  %len_main = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len = alloca i32, align 4
  %buf_back = alloca i8*, align 8
  %new_dist = alloca i32, align 4
  %len188 = alloca i32, align 4
  %buf_back189 = alloca i8*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !232, metadata !233), !dbg !234
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !235, metadata !233), !dbg !236
  store i32* %back_res, i32** %back_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %back_res.addr, metadata !237, metadata !233), !dbg !238
  store i32* %len_res, i32** %len_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %len_res.addr, metadata !239, metadata !233), !dbg !240
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !241, metadata !233), !dbg !244
  call void @llvm.dbg.declare(metadata i32* %buf_avail, metadata !245, metadata !233), !dbg !246
  call void @llvm.dbg.declare(metadata i32* %i, metadata !247, metadata !233), !dbg !248
  call void @llvm.dbg.declare(metadata i32* %rep_len, metadata !249, metadata !233), !dbg !250
  store i32 0, i32* %rep_len, align 4, !dbg !250
  call void @llvm.dbg.declare(metadata i32* %rep_index, metadata !251, metadata !233), !dbg !252
  store i32 0, i32* %rep_index, align 4, !dbg !252
  call void @llvm.dbg.declare(metadata i32* %back_main, metadata !253, metadata !233), !dbg !254
  store i32 0, i32* %back_main, align 4, !dbg !254
  call void @llvm.dbg.declare(metadata i32* %limit, metadata !255, metadata !233), !dbg !256
  call void @llvm.dbg.declare(metadata i32* %nice_len, metadata !257, metadata !233), !dbg !259
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !260
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 18, !dbg !261
  %1 = load i32, i32* %nice_len1, align 8, !dbg !261
  store i32 %1, i32* %nice_len, align 4, !dbg !259
  call void @llvm.dbg.declare(metadata i32* %len_main, metadata !262, metadata !233), !dbg !263
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !264, metadata !233), !dbg !265
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !266
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 6, !dbg !268
  %3 = load i32, i32* %read_ahead, align 4, !dbg !268
  %cmp = icmp eq i32 %3, 0, !dbg !269
  br i1 %cmp, label %if.then, label %if.else, !dbg !270

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !271
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !273
  %matches = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 3, !dbg !274
  %arraydecay = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches, i32 0, i32 0, !dbg !273
  %call = call i32 @lzma_mf_find(%struct.lzma_mf_s* %4, i32* %matches_count, %struct.lzma_match* %arraydecay), !dbg !275
  store i32 %call, i32* %len_main, align 4, !dbg !276
  br label %if.end, !dbg !277

if.else:                                          ; preds = %entry
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !278
  %read_ahead2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 6, !dbg !278
  %7 = load i32, i32* %read_ahead2, align 4, !dbg !278
  %cmp3 = icmp eq i32 %7, 1, !dbg !278
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !278

cond.true:                                        ; preds = %if.else
  br label %cond.end, !dbg !280

cond.false:                                       ; preds = %if.else
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([95 x i8], [95 x i8]* @.str.1, i32 0, i32 0), i32 38, i8* getelementptr inbounds ([109 x i8], [109 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_optimum_fast, i32 0, i32 0)) #5, !dbg !282
  unreachable, !dbg !282
                                                  ; No predecessors!
  br label %cond.end, !dbg !284

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !286
  %longest_match_length = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 5, !dbg !287
  %10 = load i32, i32* %longest_match_length, align 8, !dbg !287
  store i32 %10, i32* %len_main, align 4, !dbg !288
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !289
  %matches_count4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 4, !dbg !290
  %12 = load i32, i32* %matches_count4, align 4, !dbg !290
  store i32 %12, i32* %matches_count, align 4, !dbg !291
  br label %if.end

if.end:                                           ; preds = %cond.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !292
  %call5 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !293
  %add.ptr = getelementptr inbounds i8, i8* %call5, i64 -1, !dbg !294
  store i8* %add.ptr, i8** %buf, align 8, !dbg !295
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !296
  %call6 = call i32 @mf_avail(%struct.lzma_mf_s* %14), !dbg !296
  %add = add i32 %call6, 1, !dbg !296
  %cmp7 = icmp ult i32 %add, 273, !dbg !296
  br i1 %cmp7, label %cond.true8, label %cond.false11, !dbg !296

cond.true8:                                       ; preds = %if.end
  %15 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !297
  %call9 = call i32 @mf_avail(%struct.lzma_mf_s* %15), !dbg !297
  %add10 = add i32 %call9, 1, !dbg !297
  br label %cond.end12, !dbg !297

cond.false11:                                     ; preds = %if.end
  br label %cond.end12, !dbg !299

cond.end12:                                       ; preds = %cond.false11, %cond.true8
  %cond = phi i32 [ %add10, %cond.true8 ], [ 273, %cond.false11 ], !dbg !301
  store i32 %cond, i32* %buf_avail, align 4, !dbg !303
  %16 = load i32, i32* %buf_avail, align 4, !dbg !304
  %cmp13 = icmp ult i32 %16, 2, !dbg !306
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !307

if.then14:                                        ; preds = %cond.end12
  %17 = load i32*, i32** %back_res.addr, align 8, !dbg !308
  store i32 -1, i32* %17, align 4, !dbg !310
  %18 = load i32*, i32** %len_res.addr, align 8, !dbg !311
  store i32 1, i32* %18, align 4, !dbg !312
  br label %return, !dbg !313

if.end15:                                         ; preds = %cond.end12
  store i32 0, i32* %i, align 4, !dbg !314
  br label %for.cond, !dbg !316

for.cond:                                         ; preds = %for.inc44, %if.end15
  %19 = load i32, i32* %i, align 4, !dbg !317
  %cmp16 = icmp ult i32 %19, 4, !dbg !320
  br i1 %cmp16, label %for.body, label %for.end46, !dbg !321

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %len, metadata !322, metadata !233), !dbg !324
  call void @llvm.dbg.declare(metadata i8** %buf_back, metadata !325, metadata !233), !dbg !327
  %20 = load i8*, i8** %buf, align 8, !dbg !328
  %21 = load i32, i32* %i, align 4, !dbg !329
  %idxprom = zext i32 %21 to i64, !dbg !330
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !330
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 2, !dbg !331
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 %idxprom, !dbg !330
  %23 = load i32, i32* %arrayidx, align 4, !dbg !330
  %idx.ext = zext i32 %23 to i64, !dbg !332
  %idx.neg = sub i64 0, %idx.ext, !dbg !332
  %add.ptr17 = getelementptr inbounds i8, i8* %20, i64 %idx.neg, !dbg !332
  %add.ptr18 = getelementptr inbounds i8, i8* %add.ptr17, i64 -1, !dbg !333
  store i8* %add.ptr18, i8** %buf_back, align 8, !dbg !327
  %24 = load i8*, i8** %buf, align 8, !dbg !334
  %25 = bitcast i8* %24 to i16*, !dbg !334
  %26 = load i16, i16* %25, align 2, !dbg !334
  %conv = zext i16 %26 to i32, !dbg !334
  %27 = load i8*, i8** %buf_back, align 8, !dbg !334
  %28 = bitcast i8* %27 to i16*, !dbg !334
  %29 = load i16, i16* %28, align 2, !dbg !334
  %conv19 = zext i16 %29 to i32, !dbg !334
  %cmp20 = icmp ne i32 %conv, %conv19, !dbg !334
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !336

if.then22:                                        ; preds = %for.body
  br label %for.inc44, !dbg !337

if.end23:                                         ; preds = %for.body
  store i32 2, i32* %len, align 4, !dbg !338
  br label %for.cond24, !dbg !340

for.cond24:                                       ; preds = %for.inc, %if.end23
  %30 = load i32, i32* %len, align 4, !dbg !341
  %31 = load i32, i32* %buf_avail, align 4, !dbg !344
  %cmp25 = icmp ult i32 %30, %31, !dbg !345
  br i1 %cmp25, label %land.rhs, label %land.end, !dbg !346

land.rhs:                                         ; preds = %for.cond24
  %32 = load i32, i32* %len, align 4, !dbg !347
  %idxprom27 = zext i32 %32 to i64, !dbg !348
  %33 = load i8*, i8** %buf, align 8, !dbg !348
  %arrayidx28 = getelementptr inbounds i8, i8* %33, i64 %idxprom27, !dbg !348
  %34 = load i8, i8* %arrayidx28, align 1, !dbg !348
  %conv29 = zext i8 %34 to i32, !dbg !348
  %35 = load i32, i32* %len, align 4, !dbg !349
  %idxprom30 = zext i32 %35 to i64, !dbg !350
  %36 = load i8*, i8** %buf_back, align 8, !dbg !350
  %arrayidx31 = getelementptr inbounds i8, i8* %36, i64 %idxprom30, !dbg !350
  %37 = load i8, i8* %arrayidx31, align 1, !dbg !350
  %conv32 = zext i8 %37 to i32, !dbg !350
  %cmp33 = icmp eq i32 %conv29, %conv32, !dbg !351
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond24
  %38 = phi i1 [ false, %for.cond24 ], [ %cmp33, %land.rhs ]
  br i1 %38, label %for.body35, label %for.end, !dbg !352

for.body35:                                       ; preds = %land.end
  br label %for.inc, !dbg !354

for.inc:                                          ; preds = %for.body35
  %39 = load i32, i32* %len, align 4, !dbg !356
  %inc = add i32 %39, 1, !dbg !356
  store i32 %inc, i32* %len, align 4, !dbg !356
  br label %for.cond24, !dbg !358

for.end:                                          ; preds = %land.end
  %40 = load i32, i32* %len, align 4, !dbg !360
  %41 = load i32, i32* %nice_len, align 4, !dbg !362
  %cmp36 = icmp uge i32 %40, %41, !dbg !363
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !364

if.then38:                                        ; preds = %for.end
  %42 = load i32, i32* %i, align 4, !dbg !365
  %43 = load i32*, i32** %back_res.addr, align 8, !dbg !367
  store i32 %42, i32* %43, align 4, !dbg !368
  %44 = load i32, i32* %len, align 4, !dbg !369
  %45 = load i32*, i32** %len_res.addr, align 8, !dbg !370
  store i32 %44, i32* %45, align 4, !dbg !371
  %46 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !372
  %47 = load i32, i32* %len, align 4, !dbg !373
  %sub = sub i32 %47, 1, !dbg !374
  call void @mf_skip(%struct.lzma_mf_s* %46, i32 %sub), !dbg !375
  br label %return, !dbg !376

if.end39:                                         ; preds = %for.end
  %48 = load i32, i32* %len, align 4, !dbg !377
  %49 = load i32, i32* %rep_len, align 4, !dbg !379
  %cmp40 = icmp ugt i32 %48, %49, !dbg !380
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !381

if.then42:                                        ; preds = %if.end39
  %50 = load i32, i32* %i, align 4, !dbg !382
  store i32 %50, i32* %rep_index, align 4, !dbg !384
  %51 = load i32, i32* %len, align 4, !dbg !385
  store i32 %51, i32* %rep_len, align 4, !dbg !386
  br label %if.end43, !dbg !387

if.end43:                                         ; preds = %if.then42, %if.end39
  br label %for.inc44, !dbg !388

for.inc44:                                        ; preds = %if.end43, %if.then22
  %52 = load i32, i32* %i, align 4, !dbg !389
  %inc45 = add i32 %52, 1, !dbg !389
  store i32 %inc45, i32* %i, align 4, !dbg !389
  br label %for.cond, !dbg !391

for.end46:                                        ; preds = %for.cond
  %53 = load i32, i32* %len_main, align 4, !dbg !392
  %54 = load i32, i32* %nice_len, align 4, !dbg !394
  %cmp47 = icmp uge i32 %53, %54, !dbg !395
  br i1 %cmp47, label %if.then49, label %if.end56, !dbg !396

if.then49:                                        ; preds = %for.end46
  %55 = load i32, i32* %matches_count, align 4, !dbg !397
  %sub50 = sub i32 %55, 1, !dbg !399
  %idxprom51 = zext i32 %sub50 to i64, !dbg !400
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !400
  %matches52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 3, !dbg !401
  %arrayidx53 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches52, i64 0, i64 %idxprom51, !dbg !400
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx53, i32 0, i32 1, !dbg !402
  %57 = load i32, i32* %dist, align 4, !dbg !402
  %add54 = add i32 %57, 4, !dbg !403
  %58 = load i32*, i32** %back_res.addr, align 8, !dbg !404
  store i32 %add54, i32* %58, align 4, !dbg !405
  %59 = load i32, i32* %len_main, align 4, !dbg !406
  %60 = load i32*, i32** %len_res.addr, align 8, !dbg !407
  store i32 %59, i32* %60, align 4, !dbg !408
  %61 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !409
  %62 = load i32, i32* %len_main, align 4, !dbg !410
  %sub55 = sub i32 %62, 1, !dbg !411
  call void @mf_skip(%struct.lzma_mf_s* %61, i32 %sub55), !dbg !412
  br label %return, !dbg !413

if.end56:                                         ; preds = %for.end46
  %63 = load i32, i32* %len_main, align 4, !dbg !414
  %cmp57 = icmp uge i32 %63, 2, !dbg !416
  br i1 %cmp57, label %if.then59, label %if.end102, !dbg !417

if.then59:                                        ; preds = %if.end56
  %64 = load i32, i32* %matches_count, align 4, !dbg !418
  %sub60 = sub i32 %64, 1, !dbg !420
  %idxprom61 = zext i32 %sub60 to i64, !dbg !421
  %65 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !421
  %matches62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %65, i32 0, i32 3, !dbg !422
  %arrayidx63 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches62, i64 0, i64 %idxprom61, !dbg !421
  %dist64 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx63, i32 0, i32 1, !dbg !423
  %66 = load i32, i32* %dist64, align 4, !dbg !423
  store i32 %66, i32* %back_main, align 4, !dbg !424
  br label %while.cond, !dbg !425

while.cond:                                       ; preds = %if.end85, %if.then59
  %67 = load i32, i32* %matches_count, align 4, !dbg !426
  %cmp65 = icmp ugt i32 %67, 1, !dbg !428
  br i1 %cmp65, label %land.rhs67, label %land.end76, !dbg !429

land.rhs67:                                       ; preds = %while.cond
  %68 = load i32, i32* %len_main, align 4, !dbg !430
  %69 = load i32, i32* %matches_count, align 4, !dbg !432
  %sub68 = sub i32 %69, 2, !dbg !433
  %idxprom69 = zext i32 %sub68 to i64, !dbg !434
  %70 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !434
  %matches70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %70, i32 0, i32 3, !dbg !435
  %arrayidx71 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches70, i64 0, i64 %idxprom69, !dbg !434
  %len72 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx71, i32 0, i32 0, !dbg !436
  %71 = load i32, i32* %len72, align 4, !dbg !436
  %add73 = add i32 %71, 1, !dbg !437
  %cmp74 = icmp eq i32 %68, %add73, !dbg !438
  br label %land.end76

land.end76:                                       ; preds = %land.rhs67, %while.cond
  %72 = phi i1 [ false, %while.cond ], [ %cmp74, %land.rhs67 ]
  br i1 %72, label %while.body, label %while.end, !dbg !439

while.body:                                       ; preds = %land.end76
  %73 = load i32, i32* %back_main, align 4, !dbg !441
  %shr = lshr i32 %73, 7, !dbg !441
  %74 = load i32, i32* %matches_count, align 4, !dbg !441
  %sub77 = sub i32 %74, 2, !dbg !441
  %idxprom78 = zext i32 %sub77 to i64, !dbg !441
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !441
  %matches79 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 3, !dbg !441
  %arrayidx80 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches79, i64 0, i64 %idxprom78, !dbg !441
  %dist81 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx80, i32 0, i32 1, !dbg !441
  %76 = load i32, i32* %dist81, align 4, !dbg !441
  %cmp82 = icmp ugt i32 %shr, %76, !dbg !441
  br i1 %cmp82, label %if.end85, label %if.then84, !dbg !444

if.then84:                                        ; preds = %while.body
  br label %while.end, !dbg !445

if.end85:                                         ; preds = %while.body
  %77 = load i32, i32* %matches_count, align 4, !dbg !446
  %dec = add i32 %77, -1, !dbg !446
  store i32 %dec, i32* %matches_count, align 4, !dbg !446
  %78 = load i32, i32* %matches_count, align 4, !dbg !447
  %sub86 = sub i32 %78, 1, !dbg !448
  %idxprom87 = zext i32 %sub86 to i64, !dbg !449
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !449
  %matches88 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 3, !dbg !450
  %arrayidx89 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches88, i64 0, i64 %idxprom87, !dbg !449
  %len90 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx89, i32 0, i32 0, !dbg !451
  %80 = load i32, i32* %len90, align 4, !dbg !451
  store i32 %80, i32* %len_main, align 4, !dbg !452
  %81 = load i32, i32* %matches_count, align 4, !dbg !453
  %sub91 = sub i32 %81, 1, !dbg !454
  %idxprom92 = zext i32 %sub91 to i64, !dbg !455
  %82 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !455
  %matches93 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %82, i32 0, i32 3, !dbg !456
  %arrayidx94 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches93, i64 0, i64 %idxprom92, !dbg !455
  %dist95 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx94, i32 0, i32 1, !dbg !457
  %83 = load i32, i32* %dist95, align 4, !dbg !457
  store i32 %83, i32* %back_main, align 4, !dbg !458
  br label %while.cond, !dbg !459

while.end:                                        ; preds = %if.then84, %land.end76
  %84 = load i32, i32* %len_main, align 4, !dbg !461
  %cmp96 = icmp eq i32 %84, 2, !dbg !463
  br i1 %cmp96, label %land.lhs.true, label %if.end101, !dbg !464

land.lhs.true:                                    ; preds = %while.end
  %85 = load i32, i32* %back_main, align 4, !dbg !465
  %cmp98 = icmp uge i32 %85, 128, !dbg !467
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !468

if.then100:                                       ; preds = %land.lhs.true
  store i32 1, i32* %len_main, align 4, !dbg !469
  br label %if.end101, !dbg !470

if.end101:                                        ; preds = %if.then100, %land.lhs.true, %while.end
  br label %if.end102, !dbg !471

if.end102:                                        ; preds = %if.end101, %if.end56
  %86 = load i32, i32* %rep_len, align 4, !dbg !472
  %cmp103 = icmp uge i32 %86, 2, !dbg !474
  br i1 %cmp103, label %if.then105, label %if.end125, !dbg !475

if.then105:                                       ; preds = %if.end102
  %87 = load i32, i32* %rep_len, align 4, !dbg !476
  %add106 = add i32 %87, 1, !dbg !479
  %88 = load i32, i32* %len_main, align 4, !dbg !480
  %cmp107 = icmp uge i32 %add106, %88, !dbg !481
  br i1 %cmp107, label %if.then122, label %lor.lhs.false, !dbg !482

lor.lhs.false:                                    ; preds = %if.then105
  %89 = load i32, i32* %rep_len, align 4, !dbg !483
  %add109 = add i32 %89, 2, !dbg !485
  %90 = load i32, i32* %len_main, align 4, !dbg !486
  %cmp110 = icmp uge i32 %add109, %90, !dbg !487
  br i1 %cmp110, label %land.lhs.true112, label %lor.lhs.false115, !dbg !488

land.lhs.true112:                                 ; preds = %lor.lhs.false
  %91 = load i32, i32* %back_main, align 4, !dbg !489
  %cmp113 = icmp ugt i32 %91, 512, !dbg !490
  br i1 %cmp113, label %if.then122, label %lor.lhs.false115, !dbg !491

lor.lhs.false115:                                 ; preds = %land.lhs.true112, %lor.lhs.false
  %92 = load i32, i32* %rep_len, align 4, !dbg !492
  %add116 = add i32 %92, 3, !dbg !493
  %93 = load i32, i32* %len_main, align 4, !dbg !494
  %cmp117 = icmp uge i32 %add116, %93, !dbg !495
  br i1 %cmp117, label %land.lhs.true119, label %if.end124, !dbg !496

land.lhs.true119:                                 ; preds = %lor.lhs.false115
  %94 = load i32, i32* %back_main, align 4, !dbg !497
  %cmp120 = icmp ugt i32 %94, 32768, !dbg !498
  br i1 %cmp120, label %if.then122, label %if.end124, !dbg !499

if.then122:                                       ; preds = %land.lhs.true119, %land.lhs.true112, %if.then105
  %95 = load i32, i32* %rep_index, align 4, !dbg !501
  %96 = load i32*, i32** %back_res.addr, align 8, !dbg !503
  store i32 %95, i32* %96, align 4, !dbg !504
  %97 = load i32, i32* %rep_len, align 4, !dbg !505
  %98 = load i32*, i32** %len_res.addr, align 8, !dbg !506
  store i32 %97, i32* %98, align 4, !dbg !507
  %99 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !508
  %100 = load i32, i32* %rep_len, align 4, !dbg !509
  %sub123 = sub i32 %100, 1, !dbg !510
  call void @mf_skip(%struct.lzma_mf_s* %99, i32 %sub123), !dbg !511
  br label %return, !dbg !512

if.end124:                                        ; preds = %land.lhs.true119, %lor.lhs.false115
  br label %if.end125, !dbg !513

if.end125:                                        ; preds = %if.end124, %if.end102
  %101 = load i32, i32* %len_main, align 4, !dbg !514
  %cmp126 = icmp ult i32 %101, 2, !dbg !516
  br i1 %cmp126, label %if.then131, label %lor.lhs.false128, !dbg !517

lor.lhs.false128:                                 ; preds = %if.end125
  %102 = load i32, i32* %buf_avail, align 4, !dbg !518
  %cmp129 = icmp ule i32 %102, 2, !dbg !520
  br i1 %cmp129, label %if.then131, label %if.end132, !dbg !521

if.then131:                                       ; preds = %lor.lhs.false128, %if.end125
  %103 = load i32*, i32** %back_res.addr, align 8, !dbg !522
  store i32 -1, i32* %103, align 4, !dbg !524
  %104 = load i32*, i32** %len_res.addr, align 8, !dbg !525
  store i32 1, i32* %104, align 4, !dbg !526
  br label %return, !dbg !527

if.end132:                                        ; preds = %lor.lhs.false128
  %105 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !528
  %106 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !529
  %matches_count133 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %106, i32 0, i32 4, !dbg !530
  %107 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !531
  %matches134 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %107, i32 0, i32 3, !dbg !532
  %arraydecay135 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches134, i32 0, i32 0, !dbg !531
  %call136 = call i32 @lzma_mf_find(%struct.lzma_mf_s* %105, i32* %matches_count133, %struct.lzma_match* %arraydecay135), !dbg !533
  %108 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !534
  %longest_match_length137 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %108, i32 0, i32 5, !dbg !535
  store i32 %call136, i32* %longest_match_length137, align 8, !dbg !536
  %109 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !537
  %longest_match_length138 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %109, i32 0, i32 5, !dbg !539
  %110 = load i32, i32* %longest_match_length138, align 8, !dbg !539
  %cmp139 = icmp uge i32 %110, 2, !dbg !540
  br i1 %cmp139, label %if.then141, label %if.end182, !dbg !541

if.then141:                                       ; preds = %if.end132
  call void @llvm.dbg.declare(metadata i32* %new_dist, metadata !542, metadata !233), !dbg !544
  %111 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !545
  %matches_count142 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %111, i32 0, i32 4, !dbg !546
  %112 = load i32, i32* %matches_count142, align 4, !dbg !546
  %sub143 = sub i32 %112, 1, !dbg !547
  %idxprom144 = zext i32 %sub143 to i64, !dbg !548
  %113 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !548
  %matches145 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %113, i32 0, i32 3, !dbg !549
  %arrayidx146 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches145, i64 0, i64 %idxprom144, !dbg !548
  %dist147 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx146, i32 0, i32 1, !dbg !550
  %114 = load i32, i32* %dist147, align 4, !dbg !550
  store i32 %114, i32* %new_dist, align 4, !dbg !544
  %115 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !551
  %longest_match_length148 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %115, i32 0, i32 5, !dbg !553
  %116 = load i32, i32* %longest_match_length148, align 8, !dbg !553
  %117 = load i32, i32* %len_main, align 4, !dbg !554
  %cmp149 = icmp uge i32 %116, %117, !dbg !555
  br i1 %cmp149, label %land.lhs.true151, label %lor.lhs.false154, !dbg !556

land.lhs.true151:                                 ; preds = %if.then141
  %118 = load i32, i32* %new_dist, align 4, !dbg !557
  %119 = load i32, i32* %back_main, align 4, !dbg !559
  %cmp152 = icmp ult i32 %118, %119, !dbg !560
  br i1 %cmp152, label %if.then180, label %lor.lhs.false154, !dbg !561

lor.lhs.false154:                                 ; preds = %land.lhs.true151, %if.then141
  %120 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !562
  %longest_match_length155 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %120, i32 0, i32 5, !dbg !563
  %121 = load i32, i32* %longest_match_length155, align 8, !dbg !563
  %122 = load i32, i32* %len_main, align 4, !dbg !564
  %add156 = add i32 %122, 1, !dbg !565
  %cmp157 = icmp eq i32 %121, %add156, !dbg !566
  br i1 %cmp157, label %land.lhs.true159, label %lor.lhs.false163, !dbg !567

land.lhs.true159:                                 ; preds = %lor.lhs.false154
  %123 = load i32, i32* %new_dist, align 4, !dbg !568
  %shr160 = lshr i32 %123, 7, !dbg !568
  %124 = load i32, i32* %back_main, align 4, !dbg !568
  %cmp161 = icmp ugt i32 %shr160, %124, !dbg !568
  br i1 %cmp161, label %lor.lhs.false163, label %if.then180, !dbg !569

lor.lhs.false163:                                 ; preds = %land.lhs.true159, %lor.lhs.false154
  %125 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !570
  %longest_match_length164 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %125, i32 0, i32 5, !dbg !571
  %126 = load i32, i32* %longest_match_length164, align 8, !dbg !571
  %127 = load i32, i32* %len_main, align 4, !dbg !572
  %add165 = add i32 %127, 1, !dbg !573
  %cmp166 = icmp ugt i32 %126, %add165, !dbg !574
  br i1 %cmp166, label %if.then180, label %lor.lhs.false168, !dbg !575

lor.lhs.false168:                                 ; preds = %lor.lhs.false163
  %128 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !576
  %longest_match_length169 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %128, i32 0, i32 5, !dbg !577
  %129 = load i32, i32* %longest_match_length169, align 8, !dbg !577
  %add170 = add i32 %129, 1, !dbg !578
  %130 = load i32, i32* %len_main, align 4, !dbg !579
  %cmp171 = icmp uge i32 %add170, %130, !dbg !580
  br i1 %cmp171, label %land.lhs.true173, label %if.end181, !dbg !581

land.lhs.true173:                                 ; preds = %lor.lhs.false168
  %131 = load i32, i32* %len_main, align 4, !dbg !582
  %cmp174 = icmp uge i32 %131, 3, !dbg !583
  br i1 %cmp174, label %land.lhs.true176, label %if.end181, !dbg !584

land.lhs.true176:                                 ; preds = %land.lhs.true173
  %132 = load i32, i32* %back_main, align 4, !dbg !585
  %shr177 = lshr i32 %132, 7, !dbg !585
  %133 = load i32, i32* %new_dist, align 4, !dbg !585
  %cmp178 = icmp ugt i32 %shr177, %133, !dbg !585
  br i1 %cmp178, label %if.then180, label %if.end181, !dbg !586

if.then180:                                       ; preds = %land.lhs.true176, %lor.lhs.false163, %land.lhs.true159, %land.lhs.true151
  %134 = load i32*, i32** %back_res.addr, align 8, !dbg !588
  store i32 -1, i32* %134, align 4, !dbg !590
  %135 = load i32*, i32** %len_res.addr, align 8, !dbg !591
  store i32 1, i32* %135, align 4, !dbg !592
  br label %return, !dbg !593

if.end181:                                        ; preds = %land.lhs.true176, %land.lhs.true173, %lor.lhs.false168
  br label %if.end182, !dbg !594

if.end182:                                        ; preds = %if.end181, %if.end132
  %136 = load i8*, i8** %buf, align 8, !dbg !595
  %incdec.ptr = getelementptr inbounds i8, i8* %136, i32 1, !dbg !595
  store i8* %incdec.ptr, i8** %buf, align 8, !dbg !595
  %137 = load i32, i32* %len_main, align 4, !dbg !596
  %sub183 = sub i32 %137, 1, !dbg !597
  store i32 %sub183, i32* %limit, align 4, !dbg !598
  store i32 0, i32* %i, align 4, !dbg !599
  br label %for.cond184, !dbg !601

for.cond184:                                      ; preds = %for.inc224, %if.end182
  %138 = load i32, i32* %i, align 4, !dbg !602
  %cmp185 = icmp ult i32 %138, 4, !dbg !605
  br i1 %cmp185, label %for.body187, label %for.end226, !dbg !606

for.body187:                                      ; preds = %for.cond184
  call void @llvm.dbg.declare(metadata i32* %len188, metadata !607, metadata !233), !dbg !609
  call void @llvm.dbg.declare(metadata i8** %buf_back189, metadata !610, metadata !233), !dbg !611
  %139 = load i8*, i8** %buf, align 8, !dbg !612
  %140 = load i32, i32* %i, align 4, !dbg !613
  %idxprom190 = zext i32 %140 to i64, !dbg !614
  %141 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !614
  %reps191 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %141, i32 0, i32 2, !dbg !615
  %arrayidx192 = getelementptr inbounds [4 x i32], [4 x i32]* %reps191, i64 0, i64 %idxprom190, !dbg !614
  %142 = load i32, i32* %arrayidx192, align 4, !dbg !614
  %idx.ext193 = zext i32 %142 to i64, !dbg !616
  %idx.neg194 = sub i64 0, %idx.ext193, !dbg !616
  %add.ptr195 = getelementptr inbounds i8, i8* %139, i64 %idx.neg194, !dbg !616
  %add.ptr196 = getelementptr inbounds i8, i8* %add.ptr195, i64 -1, !dbg !617
  store i8* %add.ptr196, i8** %buf_back189, align 8, !dbg !611
  %143 = load i8*, i8** %buf, align 8, !dbg !618
  %144 = bitcast i8* %143 to i16*, !dbg !618
  %145 = load i16, i16* %144, align 2, !dbg !618
  %conv197 = zext i16 %145 to i32, !dbg !618
  %146 = load i8*, i8** %buf_back189, align 8, !dbg !618
  %147 = bitcast i8* %146 to i16*, !dbg !618
  %148 = load i16, i16* %147, align 2, !dbg !618
  %conv198 = zext i16 %148 to i32, !dbg !618
  %cmp199 = icmp ne i32 %conv197, %conv198, !dbg !618
  br i1 %cmp199, label %if.then201, label %if.end202, !dbg !620

if.then201:                                       ; preds = %for.body187
  br label %for.inc224, !dbg !621

if.end202:                                        ; preds = %for.body187
  store i32 2, i32* %len188, align 4, !dbg !622
  br label %for.cond203, !dbg !624

for.cond203:                                      ; preds = %for.inc217, %if.end202
  %149 = load i32, i32* %len188, align 4, !dbg !625
  %150 = load i32, i32* %limit, align 4, !dbg !628
  %cmp204 = icmp ult i32 %149, %150, !dbg !629
  br i1 %cmp204, label %land.rhs206, label %land.end215, !dbg !630

land.rhs206:                                      ; preds = %for.cond203
  %151 = load i32, i32* %len188, align 4, !dbg !631
  %idxprom207 = zext i32 %151 to i64, !dbg !632
  %152 = load i8*, i8** %buf, align 8, !dbg !632
  %arrayidx208 = getelementptr inbounds i8, i8* %152, i64 %idxprom207, !dbg !632
  %153 = load i8, i8* %arrayidx208, align 1, !dbg !632
  %conv209 = zext i8 %153 to i32, !dbg !632
  %154 = load i32, i32* %len188, align 4, !dbg !633
  %idxprom210 = zext i32 %154 to i64, !dbg !634
  %155 = load i8*, i8** %buf_back189, align 8, !dbg !634
  %arrayidx211 = getelementptr inbounds i8, i8* %155, i64 %idxprom210, !dbg !634
  %156 = load i8, i8* %arrayidx211, align 1, !dbg !634
  %conv212 = zext i8 %156 to i32, !dbg !634
  %cmp213 = icmp eq i32 %conv209, %conv212, !dbg !635
  br label %land.end215

land.end215:                                      ; preds = %land.rhs206, %for.cond203
  %157 = phi i1 [ false, %for.cond203 ], [ %cmp213, %land.rhs206 ]
  br i1 %157, label %for.body216, label %for.end219, !dbg !636

for.body216:                                      ; preds = %land.end215
  br label %for.inc217, !dbg !638

for.inc217:                                       ; preds = %for.body216
  %158 = load i32, i32* %len188, align 4, !dbg !640
  %inc218 = add i32 %158, 1, !dbg !640
  store i32 %inc218, i32* %len188, align 4, !dbg !640
  br label %for.cond203, !dbg !642

for.end219:                                       ; preds = %land.end215
  %159 = load i32, i32* %len188, align 4, !dbg !644
  %160 = load i32, i32* %limit, align 4, !dbg !646
  %cmp220 = icmp uge i32 %159, %160, !dbg !647
  br i1 %cmp220, label %if.then222, label %if.end223, !dbg !648

if.then222:                                       ; preds = %for.end219
  %161 = load i32*, i32** %back_res.addr, align 8, !dbg !649
  store i32 -1, i32* %161, align 4, !dbg !651
  %162 = load i32*, i32** %len_res.addr, align 8, !dbg !652
  store i32 1, i32* %162, align 4, !dbg !653
  br label %return, !dbg !654

if.end223:                                        ; preds = %for.end219
  br label %for.inc224, !dbg !655

for.inc224:                                       ; preds = %if.end223, %if.then201
  %163 = load i32, i32* %i, align 4, !dbg !656
  %inc225 = add i32 %163, 1, !dbg !656
  store i32 %inc225, i32* %i, align 4, !dbg !656
  br label %for.cond184, !dbg !658

for.end226:                                       ; preds = %for.cond184
  %164 = load i32, i32* %back_main, align 4, !dbg !659
  %add227 = add i32 %164, 4, !dbg !660
  %165 = load i32*, i32** %back_res.addr, align 8, !dbg !661
  store i32 %add227, i32* %165, align 4, !dbg !662
  %166 = load i32, i32* %len_main, align 4, !dbg !663
  %167 = load i32*, i32** %len_res.addr, align 8, !dbg !664
  store i32 %166, i32* %167, align 4, !dbg !665
  %168 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !666
  %169 = load i32, i32* %len_main, align 4, !dbg !667
  %sub228 = sub i32 %169, 2, !dbg !668
  call void @mf_skip(%struct.lzma_mf_s* %168, i32 %sub228), !dbg !669
  br label %return, !dbg !670

return:                                           ; preds = %for.end226, %if.then222, %if.then180, %if.then131, %if.then122, %if.then49, %if.then38, %if.then14
  ret void, !dbg !671
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @lzma_mf_find(%struct.lzma_mf_s*, i32*, %struct.lzma_match*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal i8* @mf_ptr(%struct.lzma_mf_s* %mf) #4 !dbg !220 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !672, metadata !233), !dbg !673
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !674
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 0, !dbg !675
  %1 = load i8*, i8** %buffer, align 8, !dbg !675
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !676
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !677
  %3 = load i32, i32* %read_pos, align 8, !dbg !677
  %idx.ext = zext i32 %3 to i64, !dbg !678
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !678
  ret i8* %add.ptr, !dbg !679
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @mf_avail(%struct.lzma_mf_s* %mf) #4 !dbg !225 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !680, metadata !233), !dbg !681
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !682
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 8, !dbg !683
  %1 = load i32, i32* %write_pos, align 4, !dbg !683
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !684
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !685
  %3 = load i32, i32* %read_pos, align 8, !dbg !685
  %sub = sub i32 %1, %3, !dbg !686
  ret i32 %sub, !dbg !687
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @mf_skip(%struct.lzma_mf_s* %mf, i32 %amount) #4 !dbg !228 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !688, metadata !233), !dbg !689
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !690, metadata !233), !dbg !691
  %0 = load i32, i32* %amount.addr, align 4, !dbg !692
  %cmp = icmp ne i32 %0, 0, !dbg !694
  br i1 %cmp, label %if.then, label %if.end, !dbg !695

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !696
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 11, !dbg !698
  %2 = load void (%struct.lzma_mf_s*, i32)*, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !698
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !699
  %4 = load i32, i32* %amount.addr, align 4, !dbg !700
  call void %2(%struct.lzma_mf_s* %3, i32 %4), !dbg !696
  %5 = load i32, i32* %amount.addr, align 4, !dbg !701
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !702
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 6, !dbg !703
  %7 = load i32, i32* %read_ahead, align 4, !dbg !704
  %add = add i32 %7, %5, !dbg !704
  store i32 %add, i32* %read_ahead, align 4, !dbg !704
  br label %if.end, !dbg !705

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !706
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!229, !230}
!llvm.ident = !{!231}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !61, subprograms: !64)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_fast.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !39, !54}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !5, file: !4, line: 40, size: 32, align: 32, elements: !33)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/range_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 27, size: 5888, align: 64, elements: !6)
!6 = !{!7, !11, !12, !15, !18, !21, !22, !26}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "low", scope: !5, file: !4, line: 28, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !9, line: 55, baseType: !10)
!9 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!10 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !5, file: !4, line: 29, baseType: !8, size: 64, align: 64, offset: 64)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !5, file: !4, line: 30, baseType: !13, size: 32, align: 32, offset: 128)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !9, line: 51, baseType: !14)
!14 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !5, file: !4, line: 31, baseType: !16, size: 8, align: 8, offset: 160)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !9, line: 48, baseType: !17)
!17 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !5, file: !4, line: 34, baseType: !19, size: 64, align: 64, offset: 192)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !20, line: 62, baseType: !10)
!20 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!21 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !5, file: !4, line: 37, baseType: !19, size: 64, align: 64, offset: 256)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "symbols", scope: !5, file: !4, line: 46, baseType: !23, size: 1856, align: 32, offset: 320)
!23 = !DICompositeType(tag: DW_TAG_array_type, baseType: !3, size: 1856, align: 32, elements: !24)
!24 = !{!25}
!25 = !DISubrange(count: 58)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "probs", scope: !5, file: !4, line: 49, baseType: !27, size: 3712, align: 64, offset: 2176)
!27 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 3712, align: 64, elements: !24)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "probability", file: !30, line: 72, baseType: !31)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/range_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !9, line: 49, baseType: !32)
!32 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!33 = !{!34, !35, !36, !37, !38}
!34 = !DIEnumerator(name: "RC_BIT_0", value: 0)
!35 = !DIEnumerator(name: "RC_BIT_1", value: 1)
!36 = !DIEnumerator(name: "RC_DIRECT_0", value: 2)
!37 = !DIEnumerator(name: "RC_DIRECT_1", value: 3)
!38 = !DIEnumerator(name: "RC_FLUSH", value: 4)
!39 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !40, line: 56, size: 32, align: 32, elements: !41)
!40 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!41 = !{!42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53}
!42 = !DIEnumerator(name: "STATE_LIT_LIT", value: 0)
!43 = !DIEnumerator(name: "STATE_MATCH_LIT_LIT", value: 1)
!44 = !DIEnumerator(name: "STATE_REP_LIT_LIT", value: 2)
!45 = !DIEnumerator(name: "STATE_SHORTREP_LIT_LIT", value: 3)
!46 = !DIEnumerator(name: "STATE_MATCH_LIT", value: 4)
!47 = !DIEnumerator(name: "STATE_REP_LIT", value: 5)
!48 = !DIEnumerator(name: "STATE_SHORTREP_LIT", value: 6)
!49 = !DIEnumerator(name: "STATE_LIT_MATCH", value: 7)
!50 = !DIEnumerator(name: "STATE_LIT_LONGREP", value: 8)
!51 = !DIEnumerator(name: "STATE_LIT_SHORTREP", value: 9)
!52 = !DIEnumerator(name: "STATE_NONLIT_MATCH", value: 10)
!53 = !DIEnumerator(name: "STATE_NONLIT_REP", value: 11)
!54 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !55, line: 250, size: 32, align: 32, elements: !56)
!55 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!56 = !{!57, !58, !59, !60}
!57 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!58 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!59 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!60 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!61 = !{!62}
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!64 = !{!65, !220, !225, !228}
!65 = distinct !DISubprogram(name: "lzma_lzma_optimum_fast", scope: !1, file: !1, line: 20, type: !66, isLocal: false, isDefinition: true, scopeLine: 22, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!66 = !DISubroutineType(types: !67)
!67 = !{null, !68, !180, !218, !218}
!68 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !69)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !71, line: 73, baseType: !72)
!71 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!72 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !73, line: 72, size: 1996608, align: 64, elements: !74)
!73 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!74 = !{!75, !77, !79, !83, !93, !94, !95, !97, !98, !99, !100, !101, !102, !107, !111, !114, !115, !116, !117, !118, !122, !126, !129, !151, !152, !154, !158, !159, !160, !161, !162, !163, !164}
!75 = !DIDerivedType(tag: DW_TAG_member, name: "rc", scope: !72, file: !73, line: 74, baseType: !76, size: 5888, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_range_encoder", file: !4, line: 51, baseType: !5)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !72, file: !73, line: 77, baseType: !78, size: 32, align: 32, offset: 5888)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lzma_state", file: !40, line: 69, baseType: !39)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reps", scope: !72, file: !73, line: 80, baseType: !80, size: 128, align: 32, offset: 5920)
!80 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 128, align: 32, elements: !81)
!81 = !{!82}
!82 = !DISubrange(count: 4)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "matches", scope: !72, file: !73, line: 83, baseType: !84, size: 17536, align: 32, offset: 6048)
!84 = !DICompositeType(tag: DW_TAG_array_type, baseType: !85, size: 17536, align: 32, elements: !91)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match", file: !86, line: 25, baseType: !87)
!86 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!87 = !DICompositeType(tag: DW_TAG_structure_type, file: !86, line: 22, size: 64, align: 32, elements: !88)
!88 = !{!89, !90}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !87, file: !86, line: 23, baseType: !13, size: 32, align: 32)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !87, file: !86, line: 24, baseType: !13, size: 32, align: 32, offset: 32)
!91 = !{!92}
!92 = !DISubrange(count: 274)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "matches_count", scope: !72, file: !73, line: 86, baseType: !13, size: 32, align: 32, offset: 23584)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "longest_match_length", scope: !72, file: !73, line: 90, baseType: !13, size: 32, align: 32, offset: 23616)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "fast_mode", scope: !72, file: !73, line: 93, baseType: !96, size: 8, align: 8, offset: 23648)
!96 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "is_initialized", scope: !72, file: !73, line: 97, baseType: !96, size: 8, align: 8, offset: 23656)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "is_flushed", scope: !72, file: !73, line: 101, baseType: !96, size: 8, align: 8, offset: 23664)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "pos_mask", scope: !72, file: !73, line: 103, baseType: !13, size: 32, align: 32, offset: 23680)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "literal_context_bits", scope: !72, file: !73, line: 104, baseType: !13, size: 32, align: 32, offset: 23712)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "literal_pos_mask", scope: !72, file: !73, line: 105, baseType: !13, size: 32, align: 32, offset: 23744)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "literal", scope: !72, file: !73, line: 108, baseType: !103, size: 196608, align: 16, offset: 23776)
!103 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 196608, align: 16, elements: !104)
!104 = !{!105, !106}
!105 = !DISubrange(count: 16)
!106 = !DISubrange(count: 768)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "is_match", scope: !72, file: !73, line: 109, baseType: !108, size: 3072, align: 16, offset: 220384)
!108 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 3072, align: 16, elements: !109)
!109 = !{!110, !105}
!110 = !DISubrange(count: 12)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep", scope: !72, file: !73, line: 110, baseType: !112, size: 192, align: 16, offset: 223456)
!112 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 192, align: 16, elements: !113)
!113 = !{!110}
!114 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep0", scope: !72, file: !73, line: 111, baseType: !112, size: 192, align: 16, offset: 223648)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep1", scope: !72, file: !73, line: 112, baseType: !112, size: 192, align: 16, offset: 223840)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep2", scope: !72, file: !73, line: 113, baseType: !112, size: 192, align: 16, offset: 224032)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep0_long", scope: !72, file: !73, line: 114, baseType: !108, size: 3072, align: 16, offset: 224224)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "pos_slot", scope: !72, file: !73, line: 115, baseType: !119, size: 4096, align: 16, offset: 227296)
!119 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 4096, align: 16, elements: !120)
!120 = !{!82, !121}
!121 = !DISubrange(count: 64)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "pos_special", scope: !72, file: !73, line: 116, baseType: !123, size: 1824, align: 16, offset: 231392)
!123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 1824, align: 16, elements: !124)
!124 = !{!125}
!125 = !DISubrange(count: 114)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "pos_align", scope: !72, file: !73, line: 117, baseType: !127, size: 256, align: 16, offset: 233216)
!127 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 256, align: 16, elements: !128)
!128 = !{!105}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_encoder", scope: !72, file: !73, line: 121, baseType: !130, size: 148032, align: 32, offset: 233472)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_length_encoder", file: !73, line: 51, baseType: !131)
!131 = !DICompositeType(tag: DW_TAG_structure_type, file: !73, line: 40, size: 148032, align: 32, elements: !132)
!132 = !{!133, !134, !135, !139, !140, !144, !148, !149}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "choice", scope: !131, file: !73, line: 41, baseType: !29, size: 16, align: 16)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "choice2", scope: !131, file: !73, line: 42, baseType: !29, size: 16, align: 16, offset: 16)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "low", scope: !131, file: !73, line: 43, baseType: !136, size: 2048, align: 16, offset: 32)
!136 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 2048, align: 16, elements: !137)
!137 = !{!105, !138}
!138 = !DISubrange(count: 8)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !131, file: !73, line: 44, baseType: !136, size: 2048, align: 16, offset: 2080)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "high", scope: !131, file: !73, line: 45, baseType: !141, size: 4096, align: 16, offset: 4128)
!141 = !DICompositeType(tag: DW_TAG_array_type, baseType: !29, size: 4096, align: 16, elements: !142)
!142 = !{!143}
!143 = !DISubrange(count: 256)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "prices", scope: !131, file: !73, line: 47, baseType: !145, size: 139264, align: 32, offset: 8224)
!145 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 139264, align: 32, elements: !146)
!146 = !{!105, !147}
!147 = !DISubrange(count: 272)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "table_size", scope: !131, file: !73, line: 48, baseType: !13, size: 32, align: 32, offset: 147488)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "counters", scope: !131, file: !73, line: 49, baseType: !150, size: 512, align: 32, offset: 147520)
!150 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 512, align: 32, elements: !128)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "rep_len_encoder", scope: !72, file: !73, line: 122, baseType: !130, size: 148032, align: 32, offset: 381504)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "pos_slot_prices", scope: !72, file: !73, line: 125, baseType: !153, size: 8192, align: 32, offset: 529536)
!153 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 8192, align: 32, elements: !120)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "distances_prices", scope: !72, file: !73, line: 126, baseType: !155, size: 16384, align: 32, offset: 537728)
!155 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 16384, align: 32, elements: !156)
!156 = !{!82, !157}
!157 = !DISubrange(count: 128)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "dist_table_size", scope: !72, file: !73, line: 127, baseType: !13, size: 32, align: 32, offset: 554112)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "match_price_count", scope: !72, file: !73, line: 128, baseType: !13, size: 32, align: 32, offset: 554144)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "align_prices", scope: !72, file: !73, line: 130, baseType: !150, size: 512, align: 32, offset: 554176)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "align_price_count", scope: !72, file: !73, line: 131, baseType: !13, size: 32, align: 32, offset: 554688)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "opts_end_index", scope: !72, file: !73, line: 134, baseType: !13, size: 32, align: 32, offset: 554720)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "opts_current_index", scope: !72, file: !73, line: 135, baseType: !13, size: 32, align: 32, offset: 554752)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "opts", scope: !72, file: !73, line: 136, baseType: !165, size: 1441792, align: 32, offset: 554784)
!165 = !DICompositeType(tag: DW_TAG_array_type, baseType: !166, size: 1441792, align: 32, elements: !178)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_optimal", file: !73, line: 69, baseType: !167)
!167 = !DICompositeType(tag: DW_TAG_structure_type, file: !73, line: 54, size: 352, align: 32, elements: !168)
!168 = !{!169, !170, !171, !172, !173, !174, !175, !176, !177}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !167, file: !73, line: 55, baseType: !78, size: 32, align: 32)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "prev_1_is_literal", scope: !167, file: !73, line: 57, baseType: !96, size: 8, align: 8, offset: 32)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "prev_2", scope: !167, file: !73, line: 58, baseType: !96, size: 8, align: 8, offset: 40)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "pos_prev_2", scope: !167, file: !73, line: 60, baseType: !13, size: 32, align: 32, offset: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "back_prev_2", scope: !167, file: !73, line: 61, baseType: !13, size: 32, align: 32, offset: 96)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "price", scope: !167, file: !73, line: 63, baseType: !13, size: 32, align: 32, offset: 128)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "pos_prev", scope: !167, file: !73, line: 64, baseType: !13, size: 32, align: 32, offset: 160)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "back_prev", scope: !167, file: !73, line: 65, baseType: !13, size: 32, align: 32, offset: 192)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "backs", scope: !167, file: !73, line: 67, baseType: !80, size: 128, align: 32, offset: 224)
!178 = !{!179}
!179 = !DISubrange(count: 4096)
!180 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !181)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mf", file: !86, line: 28, baseType: !183)
!183 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_mf_s", file: !86, line: 29, size: 960, align: 64, elements: !184)
!184 = !{!185, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !201, !205, !207, !208, !209, !210, !211, !212, !213, !214, !216, !217}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !183, file: !86, line: 35, baseType: !186, size: 64, align: 64)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !183, file: !86, line: 39, baseType: !13, size: 32, align: 32, offset: 64)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_before", scope: !183, file: !86, line: 45, baseType: !13, size: 32, align: 32, offset: 96)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_after", scope: !183, file: !86, line: 51, baseType: !13, size: 32, align: 32, offset: 128)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !183, file: !86, line: 58, baseType: !13, size: 32, align: 32, offset: 160)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !183, file: !86, line: 63, baseType: !13, size: 32, align: 32, offset: 192)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "read_ahead", scope: !183, file: !86, line: 67, baseType: !13, size: 32, align: 32, offset: 224)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "read_limit", scope: !183, file: !86, line: 75, baseType: !13, size: 32, align: 32, offset: 256)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "write_pos", scope: !183, file: !86, line: 80, baseType: !13, size: 32, align: 32, offset: 288)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !183, file: !86, line: 84, baseType: !13, size: 32, align: 32, offset: 320)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "find", scope: !183, file: !86, line: 92, baseType: !197, size: 64, align: 64, offset: 384)
!197 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !198, size: 64, align: 64)
!198 = !DISubroutineType(types: !199)
!199 = !{!13, !181, !200}
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !183, file: !86, line: 97, baseType: !202, size: 64, align: 64, offset: 448)
!202 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!203 = !DISubroutineType(types: !204)
!204 = !{null, !181, !13}
!205 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !183, file: !86, line: 99, baseType: !206, size: 64, align: 64, offset: 512)
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "son", scope: !183, file: !86, line: 100, baseType: !206, size: 64, align: 64, offset: 576)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_pos", scope: !183, file: !86, line: 101, baseType: !13, size: 32, align: 32, offset: 640)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_size", scope: !183, file: !86, line: 102, baseType: !13, size: 32, align: 32, offset: 672)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !183, file: !86, line: 103, baseType: !13, size: 32, align: 32, offset: 704)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !183, file: !86, line: 106, baseType: !13, size: 32, align: 32, offset: 736)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !183, file: !86, line: 109, baseType: !13, size: 32, align: 32, offset: 768)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !183, file: !86, line: 114, baseType: !13, size: 32, align: 32, offset: 800)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "action", scope: !183, file: !86, line: 119, baseType: !215, size: 32, align: 32, offset: 832)
!215 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !55, line: 322, baseType: !54)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size_sum", scope: !183, file: !86, line: 122, baseType: !13, size: 32, align: 32, offset: 864)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "sons_count", scope: !183, file: !86, line: 125, baseType: !13, size: 32, align: 32, offset: 896)
!218 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !206)
!219 = !{}
!220 = distinct !DISubprogram(name: "mf_ptr", scope: !86, file: !86, line: 222, type: !221, isLocal: true, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!221 = !DISubroutineType(types: !222)
!222 = !{!186, !223}
!223 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !224, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !182)
!225 = distinct !DISubprogram(name: "mf_avail", scope: !86, file: !86, line: 230, type: !226, isLocal: true, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!226 = !DISubroutineType(types: !227)
!227 = !{!13, !223}
!228 = distinct !DISubprogram(name: "mf_skip", scope: !86, file: !86, line: 268, type: !203, isLocal: true, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!229 = !{i32 2, !"Dwarf Version", i32 4}
!230 = !{i32 2, !"Debug Info Version", i32 3}
!231 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!232 = !DILocalVariable(name: "coder", arg: 1, scope: !65, file: !1, line: 20, type: !68)
!233 = !DIExpression()
!234 = !DILocation(line: 20, column: 50, scope: !65)
!235 = !DILocalVariable(name: "mf", arg: 2, scope: !65, file: !1, line: 20, type: !180)
!236 = !DILocation(line: 20, column: 80, scope: !65)
!237 = !DILocalVariable(name: "back_res", arg: 3, scope: !65, file: !1, line: 21, type: !218)
!238 = !DILocation(line: 21, column: 27, scope: !65)
!239 = !DILocalVariable(name: "len_res", arg: 4, scope: !65, file: !1, line: 21, type: !218)
!240 = !DILocation(line: 21, column: 61, scope: !65)
!241 = !DILocalVariable(name: "buf", scope: !65, file: !1, line: 23, type: !242)
!242 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !243, size: 64, align: 64)
!243 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!244 = !DILocation(line: 23, column: 17, scope: !65)
!245 = !DILocalVariable(name: "buf_avail", scope: !65, file: !1, line: 24, type: !13)
!246 = !DILocation(line: 24, column: 11, scope: !65)
!247 = !DILocalVariable(name: "i", scope: !65, file: !1, line: 25, type: !13)
!248 = !DILocation(line: 25, column: 11, scope: !65)
!249 = !DILocalVariable(name: "rep_len", scope: !65, file: !1, line: 26, type: !13)
!250 = !DILocation(line: 26, column: 11, scope: !65)
!251 = !DILocalVariable(name: "rep_index", scope: !65, file: !1, line: 27, type: !13)
!252 = !DILocation(line: 27, column: 11, scope: !65)
!253 = !DILocalVariable(name: "back_main", scope: !65, file: !1, line: 28, type: !13)
!254 = !DILocation(line: 28, column: 11, scope: !65)
!255 = !DILocalVariable(name: "limit", scope: !65, file: !1, line: 29, type: !13)
!256 = !DILocation(line: 29, column: 11, scope: !65)
!257 = !DILocalVariable(name: "nice_len", scope: !65, file: !1, line: 31, type: !258)
!258 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!259 = !DILocation(line: 31, column: 17, scope: !65)
!260 = !DILocation(line: 31, column: 28, scope: !65)
!261 = !DILocation(line: 31, column: 32, scope: !65)
!262 = !DILocalVariable(name: "len_main", scope: !65, file: !1, line: 33, type: !13)
!263 = !DILocation(line: 33, column: 11, scope: !65)
!264 = !DILocalVariable(name: "matches_count", scope: !65, file: !1, line: 34, type: !13)
!265 = !DILocation(line: 34, column: 11, scope: !65)
!266 = !DILocation(line: 35, column: 6, scope: !267)
!267 = distinct !DILexicalBlock(scope: !65, file: !1, line: 35, column: 6)
!268 = !DILocation(line: 35, column: 10, scope: !267)
!269 = !DILocation(line: 35, column: 21, scope: !267)
!270 = !DILocation(line: 35, column: 6, scope: !65)
!271 = !DILocation(line: 36, column: 22, scope: !272)
!272 = distinct !DILexicalBlock(scope: !267, file: !1, line: 35, column: 27)
!273 = !DILocation(line: 36, column: 42, scope: !272)
!274 = !DILocation(line: 36, column: 49, scope: !272)
!275 = !DILocation(line: 36, column: 14, scope: !272)
!276 = !DILocation(line: 36, column: 12, scope: !272)
!277 = !DILocation(line: 37, column: 2, scope: !272)
!278 = !DILocation(line: 38, column: 3, scope: !279)
!279 = distinct !DILexicalBlock(scope: !267, file: !1, line: 37, column: 9)
!280 = !DILocation(line: 38, column: 3, scope: !281)
!281 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 1)
!282 = !DILocation(line: 38, column: 3, scope: !283)
!283 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 2)
!284 = !DILocation(line: 38, column: 3, scope: !285)
!285 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 3)
!286 = !DILocation(line: 39, column: 14, scope: !279)
!287 = !DILocation(line: 39, column: 21, scope: !279)
!288 = !DILocation(line: 39, column: 12, scope: !279)
!289 = !DILocation(line: 40, column: 19, scope: !279)
!290 = !DILocation(line: 40, column: 26, scope: !279)
!291 = !DILocation(line: 40, column: 17, scope: !279)
!292 = !DILocation(line: 43, column: 15, scope: !65)
!293 = !DILocation(line: 43, column: 8, scope: !65)
!294 = !DILocation(line: 43, column: 19, scope: !65)
!295 = !DILocation(line: 43, column: 6, scope: !65)
!296 = !DILocation(line: 44, column: 14, scope: !65)
!297 = !DILocation(line: 44, column: 14, scope: !298)
!298 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 1)
!299 = !DILocation(line: 44, column: 14, scope: !300)
!300 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 2)
!301 = !DILocation(line: 44, column: 14, scope: !302)
!302 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 3)
!303 = !DILocation(line: 44, column: 12, scope: !302)
!304 = !DILocation(line: 46, column: 6, scope: !305)
!305 = distinct !DILexicalBlock(scope: !65, file: !1, line: 46, column: 6)
!306 = !DILocation(line: 46, column: 16, scope: !305)
!307 = !DILocation(line: 46, column: 6, scope: !65)
!308 = !DILocation(line: 48, column: 4, scope: !309)
!309 = distinct !DILexicalBlock(scope: !305, file: !1, line: 46, column: 21)
!310 = !DILocation(line: 48, column: 13, scope: !309)
!311 = !DILocation(line: 49, column: 4, scope: !309)
!312 = !DILocation(line: 49, column: 12, scope: !309)
!313 = !DILocation(line: 50, column: 3, scope: !309)
!314 = !DILocation(line: 54, column: 9, scope: !315)
!315 = distinct !DILexicalBlock(scope: !65, file: !1, line: 54, column: 2)
!316 = !DILocation(line: 54, column: 7, scope: !315)
!317 = !DILocation(line: 54, column: 14, scope: !318)
!318 = !DILexicalBlockFile(scope: !319, file: !1, discriminator: 1)
!319 = distinct !DILexicalBlock(scope: !315, file: !1, line: 54, column: 2)
!320 = !DILocation(line: 54, column: 16, scope: !318)
!321 = !DILocation(line: 54, column: 2, scope: !318)
!322 = !DILocalVariable(name: "len", scope: !323, file: !1, line: 55, type: !13)
!323 = distinct !DILexicalBlock(scope: !319, file: !1, line: 54, column: 38)
!324 = !DILocation(line: 55, column: 12, scope: !323)
!325 = !DILocalVariable(name: "buf_back", scope: !323, file: !1, line: 58, type: !326)
!326 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !242)
!327 = !DILocation(line: 58, column: 24, scope: !323)
!328 = !DILocation(line: 58, column: 35, scope: !323)
!329 = !DILocation(line: 58, column: 53, scope: !323)
!330 = !DILocation(line: 58, column: 41, scope: !323)
!331 = !DILocation(line: 58, column: 48, scope: !323)
!332 = !DILocation(line: 58, column: 39, scope: !323)
!333 = !DILocation(line: 58, column: 56, scope: !323)
!334 = !DILocation(line: 62, column: 7, scope: !335)
!335 = distinct !DILexicalBlock(scope: !323, file: !1, line: 62, column: 7)
!336 = !DILocation(line: 62, column: 7, scope: !323)
!337 = !DILocation(line: 63, column: 4, scope: !335)
!338 = !DILocation(line: 67, column: 12, scope: !339)
!339 = distinct !DILexicalBlock(scope: !323, file: !1, line: 67, column: 3)
!340 = !DILocation(line: 67, column: 8, scope: !339)
!341 = !DILocation(line: 67, column: 17, scope: !342)
!342 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 1)
!343 = distinct !DILexicalBlock(scope: !339, file: !1, line: 67, column: 3)
!344 = !DILocation(line: 67, column: 23, scope: !342)
!345 = !DILocation(line: 67, column: 21, scope: !342)
!346 = !DILocation(line: 68, column: 5, scope: !343)
!347 = !DILocation(line: 68, column: 12, scope: !342)
!348 = !DILocation(line: 68, column: 8, scope: !342)
!349 = !DILocation(line: 68, column: 29, scope: !342)
!350 = !DILocation(line: 68, column: 20, scope: !342)
!351 = !DILocation(line: 68, column: 17, scope: !342)
!352 = !DILocation(line: 67, column: 3, scope: !353)
!353 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 2)
!354 = !DILocation(line: 67, column: 3, scope: !355)
!355 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 3)
!356 = !DILocation(line: 68, column: 35, scope: !357)
!357 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 2)
!358 = !DILocation(line: 67, column: 3, scope: !359)
!359 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 4)
!360 = !DILocation(line: 72, column: 7, scope: !361)
!361 = distinct !DILexicalBlock(scope: !323, file: !1, line: 72, column: 7)
!362 = !DILocation(line: 72, column: 14, scope: !361)
!363 = !DILocation(line: 72, column: 11, scope: !361)
!364 = !DILocation(line: 72, column: 7, scope: !323)
!365 = !DILocation(line: 73, column: 16, scope: !366)
!366 = distinct !DILexicalBlock(scope: !361, file: !1, line: 72, column: 24)
!367 = !DILocation(line: 73, column: 5, scope: !366)
!368 = !DILocation(line: 73, column: 14, scope: !366)
!369 = !DILocation(line: 74, column: 15, scope: !366)
!370 = !DILocation(line: 74, column: 5, scope: !366)
!371 = !DILocation(line: 74, column: 13, scope: !366)
!372 = !DILocation(line: 75, column: 12, scope: !366)
!373 = !DILocation(line: 75, column: 16, scope: !366)
!374 = !DILocation(line: 75, column: 20, scope: !366)
!375 = !DILocation(line: 75, column: 4, scope: !366)
!376 = !DILocation(line: 76, column: 4, scope: !366)
!377 = !DILocation(line: 79, column: 7, scope: !378)
!378 = distinct !DILexicalBlock(scope: !323, file: !1, line: 79, column: 7)
!379 = !DILocation(line: 79, column: 13, scope: !378)
!380 = !DILocation(line: 79, column: 11, scope: !378)
!381 = !DILocation(line: 79, column: 7, scope: !323)
!382 = !DILocation(line: 80, column: 16, scope: !383)
!383 = distinct !DILexicalBlock(scope: !378, file: !1, line: 79, column: 22)
!384 = !DILocation(line: 80, column: 14, scope: !383)
!385 = !DILocation(line: 81, column: 14, scope: !383)
!386 = !DILocation(line: 81, column: 12, scope: !383)
!387 = !DILocation(line: 82, column: 3, scope: !383)
!388 = !DILocation(line: 83, column: 2, scope: !323)
!389 = !DILocation(line: 54, column: 33, scope: !390)
!390 = !DILexicalBlockFile(scope: !319, file: !1, discriminator: 2)
!391 = !DILocation(line: 54, column: 2, scope: !390)
!392 = !DILocation(line: 87, column: 6, scope: !393)
!393 = distinct !DILexicalBlock(scope: !65, file: !1, line: 87, column: 6)
!394 = !DILocation(line: 87, column: 18, scope: !393)
!395 = !DILocation(line: 87, column: 15, scope: !393)
!396 = !DILocation(line: 87, column: 6, scope: !65)
!397 = !DILocation(line: 88, column: 30, scope: !398)
!398 = distinct !DILexicalBlock(scope: !393, file: !1, line: 87, column: 28)
!399 = !DILocation(line: 88, column: 44, scope: !398)
!400 = !DILocation(line: 88, column: 15, scope: !398)
!401 = !DILocation(line: 88, column: 22, scope: !398)
!402 = !DILocation(line: 88, column: 49, scope: !398)
!403 = !DILocation(line: 89, column: 5, scope: !398)
!404 = !DILocation(line: 88, column: 4, scope: !398)
!405 = !DILocation(line: 88, column: 13, scope: !398)
!406 = !DILocation(line: 90, column: 14, scope: !398)
!407 = !DILocation(line: 90, column: 4, scope: !398)
!408 = !DILocation(line: 90, column: 12, scope: !398)
!409 = !DILocation(line: 91, column: 11, scope: !398)
!410 = !DILocation(line: 91, column: 15, scope: !398)
!411 = !DILocation(line: 91, column: 24, scope: !398)
!412 = !DILocation(line: 91, column: 3, scope: !398)
!413 = !DILocation(line: 92, column: 3, scope: !398)
!414 = !DILocation(line: 95, column: 6, scope: !415)
!415 = distinct !DILexicalBlock(scope: !65, file: !1, line: 95, column: 6)
!416 = !DILocation(line: 95, column: 15, scope: !415)
!417 = !DILocation(line: 95, column: 6, scope: !65)
!418 = !DILocation(line: 96, column: 30, scope: !419)
!419 = distinct !DILexicalBlock(scope: !415, file: !1, line: 95, column: 21)
!420 = !DILocation(line: 96, column: 44, scope: !419)
!421 = !DILocation(line: 96, column: 15, scope: !419)
!422 = !DILocation(line: 96, column: 22, scope: !419)
!423 = !DILocation(line: 96, column: 49, scope: !419)
!424 = !DILocation(line: 96, column: 13, scope: !419)
!425 = !DILocation(line: 98, column: 3, scope: !419)
!426 = !DILocation(line: 98, column: 10, scope: !427)
!427 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 1)
!428 = !DILocation(line: 98, column: 24, scope: !427)
!429 = !DILocation(line: 98, column: 28, scope: !427)
!430 = !DILocation(line: 98, column: 31, scope: !431)
!431 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 2)
!432 = !DILocation(line: 99, column: 20, scope: !419)
!433 = !DILocation(line: 99, column: 34, scope: !419)
!434 = !DILocation(line: 99, column: 5, scope: !419)
!435 = !DILocation(line: 99, column: 12, scope: !419)
!436 = !DILocation(line: 99, column: 39, scope: !419)
!437 = !DILocation(line: 99, column: 43, scope: !419)
!438 = !DILocation(line: 98, column: 40, scope: !431)
!439 = !DILocation(line: 98, column: 3, scope: !440)
!440 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 3)
!441 = !DILocation(line: 100, column: 9, scope: !442)
!442 = distinct !DILexicalBlock(scope: !443, file: !1, line: 100, column: 8)
!443 = distinct !DILexicalBlock(scope: !419, file: !1, line: 99, column: 48)
!444 = !DILocation(line: 100, column: 8, scope: !443)
!445 = !DILocation(line: 103, column: 5, scope: !442)
!446 = !DILocation(line: 105, column: 4, scope: !443)
!447 = !DILocation(line: 106, column: 30, scope: !443)
!448 = !DILocation(line: 106, column: 44, scope: !443)
!449 = !DILocation(line: 106, column: 15, scope: !443)
!450 = !DILocation(line: 106, column: 22, scope: !443)
!451 = !DILocation(line: 106, column: 49, scope: !443)
!452 = !DILocation(line: 106, column: 13, scope: !443)
!453 = !DILocation(line: 107, column: 31, scope: !443)
!454 = !DILocation(line: 107, column: 45, scope: !443)
!455 = !DILocation(line: 107, column: 16, scope: !443)
!456 = !DILocation(line: 107, column: 23, scope: !443)
!457 = !DILocation(line: 107, column: 50, scope: !443)
!458 = !DILocation(line: 107, column: 14, scope: !443)
!459 = !DILocation(line: 98, column: 3, scope: !460)
!460 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 4)
!461 = !DILocation(line: 110, column: 7, scope: !462)
!462 = distinct !DILexicalBlock(scope: !419, file: !1, line: 110, column: 7)
!463 = !DILocation(line: 110, column: 16, scope: !462)
!464 = !DILocation(line: 110, column: 21, scope: !462)
!465 = !DILocation(line: 110, column: 24, scope: !466)
!466 = !DILexicalBlockFile(scope: !462, file: !1, discriminator: 1)
!467 = !DILocation(line: 110, column: 34, scope: !466)
!468 = !DILocation(line: 110, column: 7, scope: !466)
!469 = !DILocation(line: 111, column: 13, scope: !462)
!470 = !DILocation(line: 111, column: 4, scope: !462)
!471 = !DILocation(line: 112, column: 2, scope: !419)
!472 = !DILocation(line: 114, column: 6, scope: !473)
!473 = distinct !DILexicalBlock(scope: !65, file: !1, line: 114, column: 6)
!474 = !DILocation(line: 114, column: 14, scope: !473)
!475 = !DILocation(line: 114, column: 6, scope: !65)
!476 = !DILocation(line: 115, column: 7, scope: !477)
!477 = distinct !DILexicalBlock(scope: !478, file: !1, line: 115, column: 7)
!478 = distinct !DILexicalBlock(scope: !473, file: !1, line: 114, column: 20)
!479 = !DILocation(line: 115, column: 15, scope: !477)
!480 = !DILocation(line: 115, column: 22, scope: !477)
!481 = !DILocation(line: 115, column: 19, scope: !477)
!482 = !DILocation(line: 116, column: 5, scope: !477)
!483 = !DILocation(line: 116, column: 9, scope: !484)
!484 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 1)
!485 = !DILocation(line: 116, column: 17, scope: !484)
!486 = !DILocation(line: 116, column: 24, scope: !484)
!487 = !DILocation(line: 116, column: 21, scope: !484)
!488 = !DILocation(line: 117, column: 6, scope: !477)
!489 = !DILocation(line: 117, column: 9, scope: !484)
!490 = !DILocation(line: 117, column: 19, scope: !484)
!491 = !DILocation(line: 118, column: 5, scope: !477)
!492 = !DILocation(line: 118, column: 9, scope: !484)
!493 = !DILocation(line: 118, column: 17, scope: !484)
!494 = !DILocation(line: 118, column: 24, scope: !484)
!495 = !DILocation(line: 118, column: 21, scope: !484)
!496 = !DILocation(line: 119, column: 6, scope: !477)
!497 = !DILocation(line: 119, column: 9, scope: !484)
!498 = !DILocation(line: 119, column: 19, scope: !484)
!499 = !DILocation(line: 115, column: 7, scope: !500)
!500 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 1)
!501 = !DILocation(line: 120, column: 16, scope: !502)
!502 = distinct !DILexicalBlock(scope: !477, file: !1, line: 119, column: 43)
!503 = !DILocation(line: 120, column: 5, scope: !502)
!504 = !DILocation(line: 120, column: 14, scope: !502)
!505 = !DILocation(line: 121, column: 15, scope: !502)
!506 = !DILocation(line: 121, column: 5, scope: !502)
!507 = !DILocation(line: 121, column: 13, scope: !502)
!508 = !DILocation(line: 122, column: 12, scope: !502)
!509 = !DILocation(line: 122, column: 16, scope: !502)
!510 = !DILocation(line: 122, column: 24, scope: !502)
!511 = !DILocation(line: 122, column: 4, scope: !502)
!512 = !DILocation(line: 123, column: 4, scope: !502)
!513 = !DILocation(line: 125, column: 2, scope: !478)
!514 = !DILocation(line: 127, column: 6, scope: !515)
!515 = distinct !DILexicalBlock(scope: !65, file: !1, line: 127, column: 6)
!516 = !DILocation(line: 127, column: 15, scope: !515)
!517 = !DILocation(line: 127, column: 19, scope: !515)
!518 = !DILocation(line: 127, column: 22, scope: !519)
!519 = !DILexicalBlockFile(scope: !515, file: !1, discriminator: 1)
!520 = !DILocation(line: 127, column: 32, scope: !519)
!521 = !DILocation(line: 127, column: 6, scope: !519)
!522 = !DILocation(line: 128, column: 4, scope: !523)
!523 = distinct !DILexicalBlock(scope: !515, file: !1, line: 127, column: 38)
!524 = !DILocation(line: 128, column: 13, scope: !523)
!525 = !DILocation(line: 129, column: 4, scope: !523)
!526 = !DILocation(line: 129, column: 12, scope: !523)
!527 = !DILocation(line: 130, column: 3, scope: !523)
!528 = !DILocation(line: 135, column: 40, scope: !65)
!529 = !DILocation(line: 136, column: 5, scope: !65)
!530 = !DILocation(line: 136, column: 12, scope: !65)
!531 = !DILocation(line: 136, column: 27, scope: !65)
!532 = !DILocation(line: 136, column: 34, scope: !65)
!533 = !DILocation(line: 135, column: 32, scope: !65)
!534 = !DILocation(line: 135, column: 2, scope: !65)
!535 = !DILocation(line: 135, column: 9, scope: !65)
!536 = !DILocation(line: 135, column: 30, scope: !65)
!537 = !DILocation(line: 138, column: 6, scope: !538)
!538 = distinct !DILexicalBlock(scope: !65, file: !1, line: 138, column: 6)
!539 = !DILocation(line: 138, column: 13, scope: !538)
!540 = !DILocation(line: 138, column: 34, scope: !538)
!541 = !DILocation(line: 138, column: 6, scope: !65)
!542 = !DILocalVariable(name: "new_dist", scope: !543, file: !1, line: 139, type: !258)
!543 = distinct !DILexicalBlock(scope: !538, file: !1, line: 138, column: 40)
!544 = !DILocation(line: 139, column: 18, scope: !543)
!545 = !DILocation(line: 140, column: 5, scope: !543)
!546 = !DILocation(line: 140, column: 12, scope: !543)
!547 = !DILocation(line: 140, column: 26, scope: !543)
!548 = !DILocation(line: 139, column: 29, scope: !543)
!549 = !DILocation(line: 139, column: 36, scope: !543)
!550 = !DILocation(line: 140, column: 31, scope: !543)
!551 = !DILocation(line: 142, column: 8, scope: !552)
!552 = distinct !DILexicalBlock(scope: !543, file: !1, line: 142, column: 7)
!553 = !DILocation(line: 142, column: 15, scope: !552)
!554 = !DILocation(line: 142, column: 39, scope: !552)
!555 = !DILocation(line: 142, column: 36, scope: !552)
!556 = !DILocation(line: 143, column: 6, scope: !552)
!557 = !DILocation(line: 143, column: 9, scope: !558)
!558 = !DILexicalBlockFile(scope: !552, file: !1, discriminator: 1)
!559 = !DILocation(line: 143, column: 20, scope: !558)
!560 = !DILocation(line: 143, column: 18, scope: !558)
!561 = !DILocation(line: 144, column: 5, scope: !552)
!562 = !DILocation(line: 144, column: 9, scope: !558)
!563 = !DILocation(line: 144, column: 16, scope: !558)
!564 = !DILocation(line: 144, column: 40, scope: !558)
!565 = !DILocation(line: 144, column: 49, scope: !558)
!566 = !DILocation(line: 144, column: 37, scope: !558)
!567 = !DILocation(line: 145, column: 6, scope: !552)
!568 = !DILocation(line: 145, column: 10, scope: !558)
!569 = !DILocation(line: 146, column: 5, scope: !552)
!570 = !DILocation(line: 146, column: 9, scope: !558)
!571 = !DILocation(line: 146, column: 16, scope: !558)
!572 = !DILocation(line: 146, column: 39, scope: !558)
!573 = !DILocation(line: 146, column: 48, scope: !558)
!574 = !DILocation(line: 146, column: 37, scope: !558)
!575 = !DILocation(line: 147, column: 5, scope: !552)
!576 = !DILocation(line: 147, column: 9, scope: !558)
!577 = !DILocation(line: 147, column: 16, scope: !558)
!578 = !DILocation(line: 147, column: 37, scope: !558)
!579 = !DILocation(line: 147, column: 44, scope: !558)
!580 = !DILocation(line: 147, column: 41, scope: !558)
!581 = !DILocation(line: 148, column: 6, scope: !552)
!582 = !DILocation(line: 148, column: 9, scope: !558)
!583 = !DILocation(line: 148, column: 18, scope: !558)
!584 = !DILocation(line: 149, column: 6, scope: !552)
!585 = !DILocation(line: 149, column: 9, scope: !558)
!586 = !DILocation(line: 142, column: 7, scope: !587)
!587 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 1)
!588 = !DILocation(line: 150, column: 5, scope: !589)
!589 = distinct !DILexicalBlock(scope: !552, file: !1, line: 149, column: 44)
!590 = !DILocation(line: 150, column: 14, scope: !589)
!591 = !DILocation(line: 151, column: 5, scope: !589)
!592 = !DILocation(line: 151, column: 13, scope: !589)
!593 = !DILocation(line: 152, column: 4, scope: !589)
!594 = !DILocation(line: 154, column: 2, scope: !543)
!595 = !DILocation(line: 159, column: 2, scope: !65)
!596 = !DILocation(line: 161, column: 10, scope: !65)
!597 = !DILocation(line: 161, column: 19, scope: !65)
!598 = !DILocation(line: 161, column: 8, scope: !65)
!599 = !DILocation(line: 163, column: 9, scope: !600)
!600 = distinct !DILexicalBlock(scope: !65, file: !1, line: 163, column: 2)
!601 = !DILocation(line: 163, column: 7, scope: !600)
!602 = !DILocation(line: 163, column: 14, scope: !603)
!603 = !DILexicalBlockFile(scope: !604, file: !1, discriminator: 1)
!604 = distinct !DILexicalBlock(scope: !600, file: !1, line: 163, column: 2)
!605 = !DILocation(line: 163, column: 16, scope: !603)
!606 = !DILocation(line: 163, column: 2, scope: !603)
!607 = !DILocalVariable(name: "len", scope: !608, file: !1, line: 164, type: !13)
!608 = distinct !DILexicalBlock(scope: !604, file: !1, line: 163, column: 38)
!609 = !DILocation(line: 164, column: 12, scope: !608)
!610 = !DILocalVariable(name: "buf_back", scope: !608, file: !1, line: 166, type: !326)
!611 = !DILocation(line: 166, column: 24, scope: !608)
!612 = !DILocation(line: 166, column: 35, scope: !608)
!613 = !DILocation(line: 166, column: 53, scope: !608)
!614 = !DILocation(line: 166, column: 41, scope: !608)
!615 = !DILocation(line: 166, column: 48, scope: !608)
!616 = !DILocation(line: 166, column: 39, scope: !608)
!617 = !DILocation(line: 166, column: 56, scope: !608)
!618 = !DILocation(line: 168, column: 7, scope: !619)
!619 = distinct !DILexicalBlock(scope: !608, file: !1, line: 168, column: 7)
!620 = !DILocation(line: 168, column: 7, scope: !608)
!621 = !DILocation(line: 169, column: 4, scope: !619)
!622 = !DILocation(line: 171, column: 12, scope: !623)
!623 = distinct !DILexicalBlock(scope: !608, file: !1, line: 171, column: 3)
!624 = !DILocation(line: 171, column: 8, scope: !623)
!625 = !DILocation(line: 171, column: 17, scope: !626)
!626 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 1)
!627 = distinct !DILexicalBlock(scope: !623, file: !1, line: 171, column: 3)
!628 = !DILocation(line: 171, column: 23, scope: !626)
!629 = !DILocation(line: 171, column: 21, scope: !626)
!630 = !DILocation(line: 172, column: 5, scope: !627)
!631 = !DILocation(line: 172, column: 12, scope: !626)
!632 = !DILocation(line: 172, column: 8, scope: !626)
!633 = !DILocation(line: 172, column: 29, scope: !626)
!634 = !DILocation(line: 172, column: 20, scope: !626)
!635 = !DILocation(line: 172, column: 17, scope: !626)
!636 = !DILocation(line: 171, column: 3, scope: !637)
!637 = !DILexicalBlockFile(scope: !623, file: !1, discriminator: 2)
!638 = !DILocation(line: 171, column: 3, scope: !639)
!639 = !DILexicalBlockFile(scope: !623, file: !1, discriminator: 3)
!640 = !DILocation(line: 172, column: 35, scope: !641)
!641 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 2)
!642 = !DILocation(line: 171, column: 3, scope: !643)
!643 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 4)
!644 = !DILocation(line: 174, column: 7, scope: !645)
!645 = distinct !DILexicalBlock(scope: !608, file: !1, line: 174, column: 7)
!646 = !DILocation(line: 174, column: 14, scope: !645)
!647 = !DILocation(line: 174, column: 11, scope: !645)
!648 = !DILocation(line: 174, column: 7, scope: !608)
!649 = !DILocation(line: 175, column: 5, scope: !650)
!650 = distinct !DILexicalBlock(scope: !645, file: !1, line: 174, column: 21)
!651 = !DILocation(line: 175, column: 14, scope: !650)
!652 = !DILocation(line: 176, column: 5, scope: !650)
!653 = !DILocation(line: 176, column: 13, scope: !650)
!654 = !DILocation(line: 177, column: 4, scope: !650)
!655 = !DILocation(line: 179, column: 2, scope: !608)
!656 = !DILocation(line: 163, column: 33, scope: !657)
!657 = !DILexicalBlockFile(scope: !604, file: !1, discriminator: 2)
!658 = !DILocation(line: 163, column: 2, scope: !657)
!659 = !DILocation(line: 181, column: 14, scope: !65)
!660 = !DILocation(line: 181, column: 24, scope: !65)
!661 = !DILocation(line: 181, column: 3, scope: !65)
!662 = !DILocation(line: 181, column: 12, scope: !65)
!663 = !DILocation(line: 182, column: 13, scope: !65)
!664 = !DILocation(line: 182, column: 3, scope: !65)
!665 = !DILocation(line: 182, column: 11, scope: !65)
!666 = !DILocation(line: 183, column: 10, scope: !65)
!667 = !DILocation(line: 183, column: 14, scope: !65)
!668 = !DILocation(line: 183, column: 23, scope: !65)
!669 = !DILocation(line: 183, column: 2, scope: !65)
!670 = !DILocation(line: 184, column: 2, scope: !65)
!671 = !DILocation(line: 185, column: 1, scope: !65)
!672 = !DILocalVariable(name: "mf", arg: 1, scope: !220, file: !86, line: 222, type: !223)
!673 = !DILocation(line: 222, column: 23, scope: !220)
!674 = !DILocation(line: 224, column: 9, scope: !220)
!675 = !DILocation(line: 224, column: 13, scope: !220)
!676 = !DILocation(line: 224, column: 22, scope: !220)
!677 = !DILocation(line: 224, column: 26, scope: !220)
!678 = !DILocation(line: 224, column: 20, scope: !220)
!679 = !DILocation(line: 224, column: 2, scope: !220)
!680 = !DILocalVariable(name: "mf", arg: 1, scope: !225, file: !86, line: 230, type: !223)
!681 = !DILocation(line: 230, column: 25, scope: !225)
!682 = !DILocation(line: 232, column: 9, scope: !225)
!683 = !DILocation(line: 232, column: 13, scope: !225)
!684 = !DILocation(line: 232, column: 25, scope: !225)
!685 = !DILocation(line: 232, column: 29, scope: !225)
!686 = !DILocation(line: 232, column: 23, scope: !225)
!687 = !DILocation(line: 232, column: 2, scope: !225)
!688 = !DILocalVariable(name: "mf", arg: 1, scope: !228, file: !86, line: 268, type: !181)
!689 = !DILocation(line: 268, column: 18, scope: !228)
!690 = !DILocalVariable(name: "amount", arg: 2, scope: !228, file: !86, line: 268, type: !13)
!691 = !DILocation(line: 268, column: 31, scope: !228)
!692 = !DILocation(line: 270, column: 6, scope: !693)
!693 = distinct !DILexicalBlock(scope: !228, file: !86, line: 270, column: 6)
!694 = !DILocation(line: 270, column: 13, scope: !693)
!695 = !DILocation(line: 270, column: 6, scope: !228)
!696 = !DILocation(line: 271, column: 3, scope: !697)
!697 = distinct !DILexicalBlock(scope: !693, file: !86, line: 270, column: 19)
!698 = !DILocation(line: 271, column: 7, scope: !697)
!699 = !DILocation(line: 271, column: 12, scope: !697)
!700 = !DILocation(line: 271, column: 16, scope: !697)
!701 = !DILocation(line: 272, column: 21, scope: !697)
!702 = !DILocation(line: 272, column: 3, scope: !697)
!703 = !DILocation(line: 272, column: 7, scope: !697)
!704 = !DILocation(line: 272, column: 18, scope: !697)
!705 = !DILocation(line: 273, column: 2, scope: !697)
!706 = !DILocation(line: 274, column: 1, scope: !228)
