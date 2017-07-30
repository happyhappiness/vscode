; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_normal.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_coder_s = type { %struct.lzma_range_encoder, i32, [4 x i32], [274 x %struct.lzma_match], i32, i32, i8, i8, i8, i32, i32, i32, [16 x [768 x i16]], [12 x [16 x i16]], [12 x i16], [12 x i16], [12 x i16], [12 x i16], [12 x [16 x i16]], [4 x [64 x i16]], [114 x i16], [16 x i16], %struct.lzma_length_encoder, %struct.lzma_length_encoder, [4 x [64 x i32]], [4 x [128 x i32]], i32, i32, [16 x i32], i32, i32, i32, [4096 x %struct.lzma_optimal] }
%struct.lzma_range_encoder = type { i64, i64, i32, i8, i64, i64, [58 x i32], [58 x i16*] }
%struct.lzma_match = type { i32, i32 }
%struct.lzma_length_encoder = type { i16, i16, [16 x [8 x i16]], [16 x [8 x i16]], [256 x i16], [16 x [272 x i32]], i32, [16 x i32] }
%struct.lzma_optimal = type { i32, i8, i8, i32, i32, i32, i32, i32, [4 x i32] }
%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }

@.str = private unnamed_addr constant [19 x i8] c"mf->read_ahead > 0\00", align 1
@.str.1 = private unnamed_addr constant [97 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_normal.c\00", align 1
@__PRETTY_FUNCTION__.lzma_lzma_optimum_normal = private unnamed_addr constant [121 x i8] c"void lzma_lzma_optimum_normal(lzma_coder *restrict, lzma_mf *restrict, uint32_t *restrict, uint32_t *restrict, uint32_t)\00", align 1
@.str.2 = private unnamed_addr constant [16 x i8] c"cur < (1 << 12)\00", align 1
@lzma_rc_prices = external constant [128 x i8], align 16
@lzma_fastpos = external constant [8192 x i8], align 16
@.str.3 = private unnamed_addr constant [20 x i8] c"mf->read_ahead == 1\00", align 1
@__PRETTY_FUNCTION__.helper1 = private unnamed_addr constant [108 x i8] c"uint32_t helper1(lzma_coder *restrict, lzma_mf *restrict, uint32_t *restrict, uint32_t *restrict, uint32_t)\00", align 1
@.str.4 = private unnamed_addr constant [23 x i8] c"pos >= (1 << (14 / 2))\00", align 1
@.str.5 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/fastpos.h\00", align 1
@__PRETTY_FUNCTION__.get_pos_slot_2 = private unnamed_addr constant [34 x i8] c"uint32_t get_pos_slot_2(uint32_t)\00", align 1

; Function Attrs: nounwind uwtable
define void @lzma_lzma_optimum_normal(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i32* noalias %back_res, i32* noalias %len_res, i32 %position) #0 !dbg !65 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %back_res.addr = alloca i32*, align 8
  %len_res.addr = alloca i32*, align 8
  %position.addr = alloca i32, align 4
  %reps = alloca [4 x i32], align 16
  %len_end = alloca i32, align 4
  %cur = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !304, metadata !305), !dbg !306
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !307, metadata !305), !dbg !308
  store i32* %back_res, i32** %back_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %back_res.addr, metadata !309, metadata !305), !dbg !310
  store i32* %len_res, i32** %len_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %len_res.addr, metadata !311, metadata !305), !dbg !312
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !313, metadata !305), !dbg !314
  call void @llvm.dbg.declare(metadata [4 x i32]* %reps, metadata !315, metadata !305), !dbg !316
  call void @llvm.dbg.declare(metadata i32* %len_end, metadata !317, metadata !305), !dbg !318
  call void @llvm.dbg.declare(metadata i32* %cur, metadata !319, metadata !305), !dbg !320
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !321
  %opts_end_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 30, !dbg !323
  %1 = load i32, i32* %opts_end_index, align 4, !dbg !323
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !324
  %opts_current_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 31, !dbg !325
  %3 = load i32, i32* %opts_current_index, align 8, !dbg !325
  %cmp = icmp ne i32 %1, %3, !dbg !326
  br i1 %cmp, label %if.then, label %if.end, !dbg !327

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !328
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 6, !dbg !328
  %5 = load i32, i32* %read_ahead, align 4, !dbg !328
  %cmp1 = icmp ugt i32 %5, 0, !dbg !328
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !328

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !330

cond.false:                                       ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([97 x i8], [97 x i8]* @.str.1, i32 0, i32 0), i32 878, i8* getelementptr inbounds ([121 x i8], [121 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_optimum_normal, i32 0, i32 0)) #6, !dbg !332
  unreachable, !dbg !332
                                                  ; No predecessors!
  br label %cond.end, !dbg !334

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !336
  %opts_current_index2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 31, !dbg !337
  %8 = load i32, i32* %opts_current_index2, align 8, !dbg !337
  %idxprom = zext i32 %8 to i64, !dbg !338
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !338
  %opts = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 32, !dbg !339
  %arrayidx = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts, i64 0, i64 %idxprom, !dbg !338
  %pos_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx, i32 0, i32 6, !dbg !340
  %10 = load i32, i32* %pos_prev, align 4, !dbg !340
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !341
  %opts_current_index3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 31, !dbg !342
  %12 = load i32, i32* %opts_current_index3, align 8, !dbg !342
  %sub = sub i32 %10, %12, !dbg !343
  %13 = load i32*, i32** %len_res.addr, align 8, !dbg !344
  store i32 %sub, i32* %13, align 4, !dbg !345
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !346
  %opts_current_index4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 31, !dbg !347
  %15 = load i32, i32* %opts_current_index4, align 8, !dbg !347
  %idxprom5 = zext i32 %15 to i64, !dbg !348
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !348
  %opts6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 32, !dbg !349
  %arrayidx7 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts6, i64 0, i64 %idxprom5, !dbg !348
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx7, i32 0, i32 7, !dbg !350
  %17 = load i32, i32* %back_prev, align 4, !dbg !350
  %18 = load i32*, i32** %back_res.addr, align 8, !dbg !351
  store i32 %17, i32* %18, align 4, !dbg !352
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !353
  %opts_current_index8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 31, !dbg !354
  %20 = load i32, i32* %opts_current_index8, align 8, !dbg !354
  %idxprom9 = zext i32 %20 to i64, !dbg !355
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !355
  %opts10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 32, !dbg !356
  %arrayidx11 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts10, i64 0, i64 %idxprom9, !dbg !355
  %pos_prev12 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx11, i32 0, i32 6, !dbg !357
  %22 = load i32, i32* %pos_prev12, align 4, !dbg !357
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !358
  %opts_current_index13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 31, !dbg !359
  store i32 %22, i32* %opts_current_index13, align 8, !dbg !360
  br label %return, !dbg !361

if.end:                                           ; preds = %entry
  %24 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !362
  %read_ahead14 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %24, i32 0, i32 6, !dbg !364
  %25 = load i32, i32* %read_ahead14, align 4, !dbg !364
  %cmp15 = icmp eq i32 %25, 0, !dbg !365
  br i1 %cmp15, label %if.then16, label %if.end23, !dbg !366

if.then16:                                        ; preds = %if.end
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !367
  %match_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 27, !dbg !370
  %27 = load i32, i32* %match_price_count, align 4, !dbg !370
  %cmp17 = icmp uge i32 %27, 128, !dbg !371
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !372

if.then18:                                        ; preds = %if.then16
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !373
  call void @fill_distances_prices(%struct.lzma_coder_s* %28), !dbg !374
  br label %if.end19, !dbg !374

if.end19:                                         ; preds = %if.then18, %if.then16
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !375
  %align_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 29, !dbg !377
  %30 = load i32, i32* %align_price_count, align 8, !dbg !377
  %cmp20 = icmp uge i32 %30, 16, !dbg !378
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !379

if.then21:                                        ; preds = %if.end19
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !380
  call void @fill_align_prices(%struct.lzma_coder_s* %31), !dbg !381
  br label %if.end22, !dbg !381

if.end22:                                         ; preds = %if.then21, %if.end19
  br label %if.end23, !dbg !382

if.end23:                                         ; preds = %if.end22, %if.end
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !383
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !384
  %34 = load i32*, i32** %back_res.addr, align 8, !dbg !385
  %35 = load i32*, i32** %len_res.addr, align 8, !dbg !386
  %36 = load i32, i32* %position.addr, align 4, !dbg !387
  %call = call i32 @helper1(%struct.lzma_coder_s* %32, %struct.lzma_mf_s* %33, i32* %34, i32* %35, i32 %36), !dbg !388
  store i32 %call, i32* %len_end, align 4, !dbg !389
  %37 = load i32, i32* %len_end, align 4, !dbg !390
  %cmp24 = icmp eq i32 %37, -1, !dbg !392
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !393

if.then25:                                        ; preds = %if.end23
  br label %return, !dbg !394

if.end26:                                         ; preds = %if.end23
  %arraydecay = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i32 0, i32 0, !dbg !395
  %38 = bitcast i32* %arraydecay to i8*, !dbg !395
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !396
  %reps27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 2, !dbg !397
  %arraydecay28 = getelementptr inbounds [4 x i32], [4 x i32]* %reps27, i32 0, i32 0, !dbg !395
  %40 = bitcast i32* %arraydecay28 to i8*, !dbg !395
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %38, i8* %40, i64 16, i32 4, i1 false), !dbg !395
  store i32 1, i32* %cur, align 4, !dbg !398
  br label %for.cond, !dbg !400

for.cond:                                         ; preds = %for.inc, %if.end26
  %41 = load i32, i32* %cur, align 4, !dbg !401
  %42 = load i32, i32* %len_end, align 4, !dbg !404
  %cmp29 = icmp ult i32 %41, %42, !dbg !405
  br i1 %cmp29, label %for.body, label %for.end, !dbg !406

for.body:                                         ; preds = %for.cond
  %43 = load i32, i32* %cur, align 4, !dbg !407
  %cmp30 = icmp ult i32 %43, 4096, !dbg !407
  br i1 %cmp30, label %cond.true31, label %cond.false32, !dbg !407

cond.true31:                                      ; preds = %for.body
  br label %cond.end33, !dbg !409

cond.false32:                                     ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([97 x i8], [97 x i8]* @.str.1, i32 0, i32 0), i32 910, i8* getelementptr inbounds ([121 x i8], [121 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_optimum_normal, i32 0, i32 0)) #6, !dbg !411
  unreachable, !dbg !411
                                                  ; No predecessors!
  br label %cond.end33, !dbg !413

cond.end33:                                       ; preds = %44, %cond.true31
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !415
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !416
  %matches_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 4, !dbg !417
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !418
  %matches = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 3, !dbg !419
  %arraydecay34 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches, i32 0, i32 0, !dbg !418
  %call35 = call i32 @lzma_mf_find(%struct.lzma_mf_s* %45, i32* %matches_count, %struct.lzma_match* %arraydecay34), !dbg !420
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !421
  %longest_match_length = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 5, !dbg !422
  store i32 %call35, i32* %longest_match_length, align 8, !dbg !423
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !424
  %longest_match_length36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 5, !dbg !426
  %50 = load i32, i32* %longest_match_length36, align 8, !dbg !426
  %51 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !427
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %51, i32 0, i32 18, !dbg !428
  %52 = load i32, i32* %nice_len, align 8, !dbg !428
  %cmp37 = icmp uge i32 %50, %52, !dbg !429
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !430

if.then38:                                        ; preds = %cond.end33
  br label %for.end, !dbg !431

if.end39:                                         ; preds = %cond.end33
  %53 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !432
  %arraydecay40 = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i32 0, i32 0, !dbg !433
  %54 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !434
  %call41 = call i8* @mf_ptr(%struct.lzma_mf_s* %54), !dbg !435
  %add.ptr = getelementptr inbounds i8, i8* %call41, i64 -1, !dbg !436
  %55 = load i32, i32* %len_end, align 4, !dbg !437
  %56 = load i32, i32* %position.addr, align 4, !dbg !438
  %57 = load i32, i32* %cur, align 4, !dbg !439
  %add = add i32 %56, %57, !dbg !440
  %58 = load i32, i32* %cur, align 4, !dbg !441
  %59 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !442
  %nice_len42 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %59, i32 0, i32 18, !dbg !443
  %60 = load i32, i32* %nice_len42, align 8, !dbg !443
  %61 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !444
  %call43 = call i32 @mf_avail(%struct.lzma_mf_s* %61), !dbg !444
  %add44 = add i32 %call43, 1, !dbg !444
  %62 = load i32, i32* %cur, align 4, !dbg !444
  %sub45 = sub i32 4095, %62, !dbg !444
  %cmp46 = icmp ult i32 %add44, %sub45, !dbg !444
  br i1 %cmp46, label %cond.true47, label %cond.false50, !dbg !444

cond.true47:                                      ; preds = %if.end39
  %63 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !445
  %call48 = call i32 @mf_avail(%struct.lzma_mf_s* %63), !dbg !445
  %add49 = add i32 %call48, 1, !dbg !445
  br label %cond.end52, !dbg !445

cond.false50:                                     ; preds = %if.end39
  %64 = load i32, i32* %cur, align 4, !dbg !446
  %sub51 = sub i32 4095, %64, !dbg !446
  br label %cond.end52, !dbg !446

cond.end52:                                       ; preds = %cond.false50, %cond.true47
  %cond = phi i32 [ %add49, %cond.true47 ], [ %sub51, %cond.false50 ], !dbg !447
  %call53 = call i32 @helper2(%struct.lzma_coder_s* %53, i32* %arraydecay40, i8* %add.ptr, i32 %55, i32 %add, i32 %58, i32 %60, i32 %cond), !dbg !448
  store i32 %call53, i32* %len_end, align 4, !dbg !449
  br label %for.inc, !dbg !450

for.inc:                                          ; preds = %cond.end52
  %65 = load i32, i32* %cur, align 4, !dbg !451
  %inc = add i32 %65, 1, !dbg !451
  store i32 %inc, i32* %cur, align 4, !dbg !451
  br label %for.cond, !dbg !453

for.end:                                          ; preds = %if.then38, %for.cond
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !454
  %67 = load i32*, i32** %len_res.addr, align 8, !dbg !455
  %68 = load i32*, i32** %back_res.addr, align 8, !dbg !456
  %69 = load i32, i32* %cur, align 4, !dbg !457
  call void @backward(%struct.lzma_coder_s* %66, i32* %67, i32* %68, i32 %69), !dbg !458
  br label %return, !dbg !459

return:                                           ; preds = %for.end, %if.then25, %cond.end
  ret void, !dbg !460
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind uwtable
define internal void @fill_distances_prices(%struct.lzma_coder_s* %coder) #0 !dbg !220 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %len_to_pos_state = alloca i32, align 4
  %pos_slot = alloca i32, align 4
  %i = alloca i32, align 4
  %pos_slot_prices = alloca i32*, align 8
  %pos_slot40 = alloca i32, align 4
  %footer_bits = alloca i32, align 4
  %base = alloca i32, align 4
  %price = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !461, metadata !305), !dbg !462
  call void @llvm.dbg.declare(metadata i32* %len_to_pos_state, metadata !463, metadata !305), !dbg !464
  call void @llvm.dbg.declare(metadata i32* %pos_slot, metadata !465, metadata !305), !dbg !466
  call void @llvm.dbg.declare(metadata i32* %i, metadata !467, metadata !305), !dbg !468
  store i32 0, i32* %len_to_pos_state, align 4, !dbg !469
  br label %for.cond, !dbg !471

for.cond:                                         ; preds = %for.inc34, %entry
  %0 = load i32, i32* %len_to_pos_state, align 4, !dbg !472
  %cmp = icmp ult i32 %0, 4, !dbg !474
  br i1 %cmp, label %for.body, label %for.end36, !dbg !475

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32** %pos_slot_prices, metadata !477, metadata !305), !dbg !480
  %1 = load i32, i32* %len_to_pos_state, align 4, !dbg !481
  %idxprom = zext i32 %1 to i64, !dbg !482
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !482
  %pos_slot_prices1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 24, !dbg !483
  %arrayidx = getelementptr inbounds [4 x [64 x i32]], [4 x [64 x i32]]* %pos_slot_prices1, i64 0, i64 %idxprom, !dbg !482
  %arraydecay = getelementptr inbounds [64 x i32], [64 x i32]* %arrayidx, i32 0, i32 0, !dbg !482
  store i32* %arraydecay, i32** %pos_slot_prices, align 8, !dbg !480
  store i32 0, i32* %pos_slot, align 4, !dbg !484
  br label %for.cond2, !dbg !486

for.cond2:                                        ; preds = %for.inc, %for.body
  %3 = load i32, i32* %pos_slot, align 4, !dbg !487
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !489
  %dist_table_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 26, !dbg !490
  %5 = load i32, i32* %dist_table_size, align 8, !dbg !490
  %cmp3 = icmp ult i32 %3, %5, !dbg !491
  br i1 %cmp3, label %for.body4, label %for.end, !dbg !492

for.body4:                                        ; preds = %for.cond2
  %6 = load i32, i32* %len_to_pos_state, align 4, !dbg !494
  %idxprom5 = zext i32 %6 to i64, !dbg !495
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !495
  %pos_slot6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 19, !dbg !496
  %arrayidx7 = getelementptr inbounds [4 x [64 x i16]], [4 x [64 x i16]]* %pos_slot6, i64 0, i64 %idxprom5, !dbg !495
  %arraydecay8 = getelementptr inbounds [64 x i16], [64 x i16]* %arrayidx7, i32 0, i32 0, !dbg !495
  %8 = load i32, i32* %pos_slot, align 4, !dbg !497
  %call = call i32 @rc_bittree_price(i16* %arraydecay8, i32 6, i32 %8), !dbg !498
  %9 = load i32, i32* %pos_slot, align 4, !dbg !499
  %idxprom9 = zext i32 %9 to i64, !dbg !500
  %10 = load i32*, i32** %pos_slot_prices, align 8, !dbg !500
  %arrayidx10 = getelementptr inbounds i32, i32* %10, i64 %idxprom9, !dbg !500
  store i32 %call, i32* %arrayidx10, align 4, !dbg !501
  br label %for.inc, !dbg !500

for.inc:                                          ; preds = %for.body4
  %11 = load i32, i32* %pos_slot, align 4, !dbg !502
  %inc = add i32 %11, 1, !dbg !502
  store i32 %inc, i32* %pos_slot, align 4, !dbg !502
  br label %for.cond2, !dbg !504

for.end:                                          ; preds = %for.cond2
  store i32 14, i32* %pos_slot, align 4, !dbg !506
  br label %for.cond11, !dbg !508

for.cond11:                                       ; preds = %for.inc19, %for.end
  %12 = load i32, i32* %pos_slot, align 4, !dbg !509
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !511
  %dist_table_size12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 26, !dbg !512
  %14 = load i32, i32* %dist_table_size12, align 8, !dbg !512
  %cmp13 = icmp ult i32 %12, %14, !dbg !513
  br i1 %cmp13, label %for.body14, label %for.end21, !dbg !514

for.body14:                                       ; preds = %for.cond11
  %15 = load i32, i32* %pos_slot, align 4, !dbg !516
  %shr = lshr i32 %15, 1, !dbg !517
  %sub = sub i32 %shr, 1, !dbg !518
  %sub15 = sub i32 %sub, 4, !dbg !519
  %call16 = call i32 @rc_direct_price(i32 %sub15), !dbg !520
  %16 = load i32, i32* %pos_slot, align 4, !dbg !521
  %idxprom17 = zext i32 %16 to i64, !dbg !522
  %17 = load i32*, i32** %pos_slot_prices, align 8, !dbg !522
  %arrayidx18 = getelementptr inbounds i32, i32* %17, i64 %idxprom17, !dbg !522
  %18 = load i32, i32* %arrayidx18, align 4, !dbg !523
  %add = add i32 %18, %call16, !dbg !523
  store i32 %add, i32* %arrayidx18, align 4, !dbg !523
  br label %for.inc19, !dbg !522

for.inc19:                                        ; preds = %for.body14
  %19 = load i32, i32* %pos_slot, align 4, !dbg !524
  %inc20 = add i32 %19, 1, !dbg !524
  store i32 %inc20, i32* %pos_slot, align 4, !dbg !524
  br label %for.cond11, !dbg !526

for.end21:                                        ; preds = %for.cond11
  store i32 0, i32* %i, align 4, !dbg !528
  br label %for.cond22, !dbg !530

for.cond22:                                       ; preds = %for.inc31, %for.end21
  %20 = load i32, i32* %i, align 4, !dbg !531
  %cmp23 = icmp ult i32 %20, 4, !dbg !534
  br i1 %cmp23, label %for.body24, label %for.end33, !dbg !535

for.body24:                                       ; preds = %for.cond22
  %21 = load i32, i32* %i, align 4, !dbg !536
  %idxprom25 = zext i32 %21 to i64, !dbg !537
  %22 = load i32*, i32** %pos_slot_prices, align 8, !dbg !537
  %arrayidx26 = getelementptr inbounds i32, i32* %22, i64 %idxprom25, !dbg !537
  %23 = load i32, i32* %arrayidx26, align 4, !dbg !537
  %24 = load i32, i32* %i, align 4, !dbg !538
  %idxprom27 = zext i32 %24 to i64, !dbg !539
  %25 = load i32, i32* %len_to_pos_state, align 4, !dbg !540
  %idxprom28 = zext i32 %25 to i64, !dbg !539
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !539
  %distances_prices = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 25, !dbg !541
  %arrayidx29 = getelementptr inbounds [4 x [128 x i32]], [4 x [128 x i32]]* %distances_prices, i64 0, i64 %idxprom28, !dbg !539
  %arrayidx30 = getelementptr inbounds [128 x i32], [128 x i32]* %arrayidx29, i64 0, i64 %idxprom27, !dbg !539
  store i32 %23, i32* %arrayidx30, align 4, !dbg !542
  br label %for.inc31, !dbg !539

for.inc31:                                        ; preds = %for.body24
  %27 = load i32, i32* %i, align 4, !dbg !543
  %inc32 = add i32 %27, 1, !dbg !543
  store i32 %inc32, i32* %i, align 4, !dbg !543
  br label %for.cond22, !dbg !545

for.end33:                                        ; preds = %for.cond22
  br label %for.inc34, !dbg !546

for.inc34:                                        ; preds = %for.end33
  %28 = load i32, i32* %len_to_pos_state, align 4, !dbg !547
  %inc35 = add i32 %28, 1, !dbg !547
  store i32 %inc35, i32* %len_to_pos_state, align 4, !dbg !547
  br label %for.cond, !dbg !548

for.end36:                                        ; preds = %for.cond
  store i32 4, i32* %i, align 4, !dbg !550
  br label %for.cond37, !dbg !552

for.cond37:                                       ; preds = %for.inc67, %for.end36
  %29 = load i32, i32* %i, align 4, !dbg !553
  %cmp38 = icmp ult i32 %29, 128, !dbg !556
  br i1 %cmp38, label %for.body39, label %for.end69, !dbg !557

for.body39:                                       ; preds = %for.cond37
  call void @llvm.dbg.declare(metadata i32* %pos_slot40, metadata !558, metadata !305), !dbg !560
  %30 = load i32, i32* %i, align 4, !dbg !561
  %call41 = call i32 @get_pos_slot(i32 %30), !dbg !562
  store i32 %call41, i32* %pos_slot40, align 4, !dbg !560
  call void @llvm.dbg.declare(metadata i32* %footer_bits, metadata !563, metadata !305), !dbg !564
  %31 = load i32, i32* %pos_slot40, align 4, !dbg !565
  %shr42 = lshr i32 %31, 1, !dbg !566
  %sub43 = sub i32 %shr42, 1, !dbg !567
  store i32 %sub43, i32* %footer_bits, align 4, !dbg !564
  call void @llvm.dbg.declare(metadata i32* %base, metadata !568, metadata !305), !dbg !569
  %32 = load i32, i32* %pos_slot40, align 4, !dbg !570
  %and = and i32 %32, 1, !dbg !571
  %or = or i32 2, %and, !dbg !572
  %33 = load i32, i32* %footer_bits, align 4, !dbg !573
  %shl = shl i32 %or, %33, !dbg !574
  store i32 %shl, i32* %base, align 4, !dbg !569
  call void @llvm.dbg.declare(metadata i32* %price, metadata !575, metadata !305), !dbg !576
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !577
  %pos_special = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 20, !dbg !578
  %arraydecay44 = getelementptr inbounds [114 x i16], [114 x i16]* %pos_special, i32 0, i32 0, !dbg !577
  %35 = load i32, i32* %base, align 4, !dbg !579
  %idx.ext = zext i32 %35 to i64, !dbg !580
  %add.ptr = getelementptr inbounds i16, i16* %arraydecay44, i64 %idx.ext, !dbg !580
  %36 = load i32, i32* %pos_slot40, align 4, !dbg !581
  %idx.ext45 = zext i32 %36 to i64, !dbg !582
  %idx.neg = sub i64 0, %idx.ext45, !dbg !582
  %add.ptr46 = getelementptr inbounds i16, i16* %add.ptr, i64 %idx.neg, !dbg !582
  %add.ptr47 = getelementptr inbounds i16, i16* %add.ptr46, i64 -1, !dbg !583
  %37 = load i32, i32* %footer_bits, align 4, !dbg !584
  %38 = load i32, i32* %i, align 4, !dbg !585
  %39 = load i32, i32* %base, align 4, !dbg !586
  %sub48 = sub i32 %38, %39, !dbg !587
  %call49 = call i32 @rc_bittree_reverse_price(i16* %add.ptr47, i32 %37, i32 %sub48), !dbg !588
  store i32 %call49, i32* %price, align 4, !dbg !576
  store i32 0, i32* %len_to_pos_state, align 4, !dbg !589
  br label %for.cond50, !dbg !591

for.cond50:                                       ; preds = %for.inc64, %for.body39
  %40 = load i32, i32* %len_to_pos_state, align 4, !dbg !592
  %cmp51 = icmp ult i32 %40, 4, !dbg !594
  br i1 %cmp51, label %for.body52, label %for.end66, !dbg !595

for.body52:                                       ; preds = %for.cond50
  %41 = load i32, i32* %price, align 4, !dbg !597
  %42 = load i32, i32* %pos_slot40, align 4, !dbg !598
  %idxprom53 = zext i32 %42 to i64, !dbg !599
  %43 = load i32, i32* %len_to_pos_state, align 4, !dbg !600
  %idxprom54 = zext i32 %43 to i64, !dbg !599
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !599
  %pos_slot_prices55 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 24, !dbg !601
  %arrayidx56 = getelementptr inbounds [4 x [64 x i32]], [4 x [64 x i32]]* %pos_slot_prices55, i64 0, i64 %idxprom54, !dbg !599
  %arrayidx57 = getelementptr inbounds [64 x i32], [64 x i32]* %arrayidx56, i64 0, i64 %idxprom53, !dbg !599
  %45 = load i32, i32* %arrayidx57, align 4, !dbg !599
  %add58 = add i32 %41, %45, !dbg !602
  %46 = load i32, i32* %i, align 4, !dbg !603
  %idxprom59 = zext i32 %46 to i64, !dbg !604
  %47 = load i32, i32* %len_to_pos_state, align 4, !dbg !605
  %idxprom60 = zext i32 %47 to i64, !dbg !604
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !604
  %distances_prices61 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 25, !dbg !606
  %arrayidx62 = getelementptr inbounds [4 x [128 x i32]], [4 x [128 x i32]]* %distances_prices61, i64 0, i64 %idxprom60, !dbg !604
  %arrayidx63 = getelementptr inbounds [128 x i32], [128 x i32]* %arrayidx62, i64 0, i64 %idxprom59, !dbg !604
  store i32 %add58, i32* %arrayidx63, align 4, !dbg !607
  br label %for.inc64, !dbg !604

for.inc64:                                        ; preds = %for.body52
  %49 = load i32, i32* %len_to_pos_state, align 4, !dbg !608
  %inc65 = add i32 %49, 1, !dbg !608
  store i32 %inc65, i32* %len_to_pos_state, align 4, !dbg !608
  br label %for.cond50, !dbg !609

for.end66:                                        ; preds = %for.cond50
  br label %for.inc67, !dbg !611

for.inc67:                                        ; preds = %for.end66
  %50 = load i32, i32* %i, align 4, !dbg !612
  %inc68 = add i32 %50, 1, !dbg !612
  store i32 %inc68, i32* %i, align 4, !dbg !612
  br label %for.cond37, !dbg !614

for.end69:                                        ; preds = %for.cond37
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !615
  %match_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 27, !dbg !616
  store i32 0, i32* %match_price_count, align 4, !dbg !617
  ret void, !dbg !618
}

; Function Attrs: nounwind uwtable
define internal void @fill_align_prices(%struct.lzma_coder_s* %coder) #0 !dbg !244 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %i = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !619, metadata !305), !dbg !620
  call void @llvm.dbg.declare(metadata i32* %i, metadata !621, metadata !305), !dbg !622
  store i32 0, i32* %i, align 4, !dbg !623
  br label %for.cond, !dbg !625

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !626
  %cmp = icmp ult i32 %0, 16, !dbg !629
  br i1 %cmp, label %for.body, label %for.end, !dbg !630

for.body:                                         ; preds = %for.cond
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !631
  %pos_align = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 21, !dbg !632
  %arraydecay = getelementptr inbounds [16 x i16], [16 x i16]* %pos_align, i32 0, i32 0, !dbg !631
  %2 = load i32, i32* %i, align 4, !dbg !633
  %call = call i32 @rc_bittree_reverse_price(i16* %arraydecay, i32 4, i32 %2), !dbg !634
  %3 = load i32, i32* %i, align 4, !dbg !635
  %idxprom = zext i32 %3 to i64, !dbg !636
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !636
  %align_prices = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 28, !dbg !637
  %arrayidx = getelementptr inbounds [16 x i32], [16 x i32]* %align_prices, i64 0, i64 %idxprom, !dbg !636
  store i32 %call, i32* %arrayidx, align 4, !dbg !638
  br label %for.inc, !dbg !636

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !639
  %inc = add i32 %5, 1, !dbg !639
  store i32 %inc, i32* %i, align 4, !dbg !639
  br label %for.cond, !dbg !641

for.end:                                          ; preds = %for.cond
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !642
  %align_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 29, !dbg !643
  store i32 0, i32* %align_price_count, align 8, !dbg !644
  ret void, !dbg !645
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @helper1(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i32* noalias %back_res, i32* noalias %len_res, i32 %position) #3 !dbg !245 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %back_res.addr = alloca i32*, align 8
  %len_res.addr = alloca i32*, align 8
  %position.addr = alloca i32, align 4
  %buf_avail = alloca i32, align 4
  %buf = alloca i8*, align 8
  %rep_lens = alloca [4 x i32], align 16
  %rep_max_index = alloca i32, align 4
  %i = alloca i32, align 4
  %current_byte = alloca i8, align 1
  %match_byte = alloca i8, align 1
  %pos_state = alloca i32, align 4
  %match_price = alloca i32, align 4
  %rep_match_price = alloca i32, align 4
  %len_end = alloca i32, align 4
  %len = alloca i32, align 4
  %normal_match_price = alloca i32, align 4
  %nice_len = alloca i32, align 4
  %len_main = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_test = alloca i32, align 4
  %buf_back = alloca i8*, align 8
  %short_rep_price = alloca i32, align 4
  %price182 = alloca i32, align 4
  %rep_len = alloca i32, align 4
  %cur_and_len_price = alloca i32, align 4
  %i244 = alloca i32, align 4
  %dist253 = alloca i32, align 4
  %cur_and_len_price258 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !646, metadata !305), !dbg !647
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !648, metadata !305), !dbg !649
  store i32* %back_res, i32** %back_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %back_res.addr, metadata !650, metadata !305), !dbg !651
  store i32* %len_res, i32** %len_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %len_res.addr, metadata !652, metadata !305), !dbg !653
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !654, metadata !305), !dbg !655
  call void @llvm.dbg.declare(metadata i32* %buf_avail, metadata !656, metadata !305), !dbg !657
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !658, metadata !305), !dbg !659
  call void @llvm.dbg.declare(metadata [4 x i32]* %rep_lens, metadata !660, metadata !305), !dbg !661
  call void @llvm.dbg.declare(metadata i32* %rep_max_index, metadata !662, metadata !305), !dbg !663
  store i32 0, i32* %rep_max_index, align 4, !dbg !663
  call void @llvm.dbg.declare(metadata i32* %i, metadata !664, metadata !305), !dbg !665
  call void @llvm.dbg.declare(metadata i8* %current_byte, metadata !666, metadata !305), !dbg !667
  call void @llvm.dbg.declare(metadata i8* %match_byte, metadata !668, metadata !305), !dbg !669
  call void @llvm.dbg.declare(metadata i32* %pos_state, metadata !670, metadata !305), !dbg !671
  call void @llvm.dbg.declare(metadata i32* %match_price, metadata !672, metadata !305), !dbg !673
  call void @llvm.dbg.declare(metadata i32* %rep_match_price, metadata !674, metadata !305), !dbg !675
  call void @llvm.dbg.declare(metadata i32* %len_end, metadata !676, metadata !305), !dbg !677
  call void @llvm.dbg.declare(metadata i32* %len, metadata !678, metadata !305), !dbg !679
  call void @llvm.dbg.declare(metadata i32* %normal_match_price, metadata !680, metadata !305), !dbg !681
  call void @llvm.dbg.declare(metadata i32* %nice_len, metadata !682, metadata !305), !dbg !683
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !684
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 18, !dbg !685
  %1 = load i32, i32* %nice_len1, align 8, !dbg !685
  store i32 %1, i32* %nice_len, align 4, !dbg !683
  call void @llvm.dbg.declare(metadata i32* %len_main, metadata !686, metadata !305), !dbg !687
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !688, metadata !305), !dbg !689
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !690
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 6, !dbg !692
  %3 = load i32, i32* %read_ahead, align 4, !dbg !692
  %cmp = icmp eq i32 %3, 0, !dbg !693
  br i1 %cmp, label %if.then, label %if.else, !dbg !694

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !695
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !697
  %matches = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 3, !dbg !698
  %arraydecay = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches, i32 0, i32 0, !dbg !697
  %call = call i32 @lzma_mf_find(%struct.lzma_mf_s* %4, i32* %matches_count, %struct.lzma_match* %arraydecay), !dbg !699
  store i32 %call, i32* %len_main, align 4, !dbg !700
  br label %if.end, !dbg !701

if.else:                                          ; preds = %entry
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !702
  %read_ahead2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 6, !dbg !702
  %7 = load i32, i32* %read_ahead2, align 4, !dbg !702
  %cmp3 = icmp eq i32 %7, 1, !dbg !702
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !702

cond.true:                                        ; preds = %if.else
  br label %cond.end, !dbg !704

cond.false:                                       ; preds = %if.else
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([97 x i8], [97 x i8]* @.str.1, i32 0, i32 0), i32 310, i8* getelementptr inbounds ([108 x i8], [108 x i8]* @__PRETTY_FUNCTION__.helper1, i32 0, i32 0)) #6, !dbg !706
  unreachable, !dbg !706
                                                  ; No predecessors!
  br label %cond.end, !dbg !708

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !710
  %longest_match_length = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 5, !dbg !711
  %10 = load i32, i32* %longest_match_length, align 8, !dbg !711
  store i32 %10, i32* %len_main, align 4, !dbg !712
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !713
  %matches_count4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 4, !dbg !714
  %12 = load i32, i32* %matches_count4, align 4, !dbg !714
  store i32 %12, i32* %matches_count, align 4, !dbg !715
  br label %if.end

if.end:                                           ; preds = %cond.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !716
  %call5 = call i32 @mf_avail(%struct.lzma_mf_s* %13), !dbg !716
  %add = add i32 %call5, 1, !dbg !716
  %cmp6 = icmp ult i32 %add, 273, !dbg !716
  br i1 %cmp6, label %cond.true7, label %cond.false10, !dbg !716

cond.true7:                                       ; preds = %if.end
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !717
  %call8 = call i32 @mf_avail(%struct.lzma_mf_s* %14), !dbg !717
  %add9 = add i32 %call8, 1, !dbg !717
  br label %cond.end11, !dbg !717

cond.false10:                                     ; preds = %if.end
  br label %cond.end11, !dbg !719

cond.end11:                                       ; preds = %cond.false10, %cond.true7
  %cond = phi i32 [ %add9, %cond.true7 ], [ 273, %cond.false10 ], !dbg !721
  store i32 %cond, i32* %buf_avail, align 4, !dbg !723
  %15 = load i32, i32* %buf_avail, align 4, !dbg !724
  %cmp12 = icmp ult i32 %15, 2, !dbg !726
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !727

if.then13:                                        ; preds = %cond.end11
  %16 = load i32*, i32** %back_res.addr, align 8, !dbg !728
  store i32 -1, i32* %16, align 4, !dbg !730
  %17 = load i32*, i32** %len_res.addr, align 8, !dbg !731
  store i32 1, i32* %17, align 4, !dbg !732
  store i32 -1, i32* %retval, align 4, !dbg !733
  br label %return, !dbg !733

if.end14:                                         ; preds = %cond.end11
  %18 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !734
  %call15 = call i8* @mf_ptr(%struct.lzma_mf_s* %18), !dbg !735
  %add.ptr = getelementptr inbounds i8, i8* %call15, i64 -1, !dbg !736
  store i8* %add.ptr, i8** %buf, align 8, !dbg !737
  store i32 0, i32* %i, align 4, !dbg !738
  br label %for.cond, !dbg !740

for.cond:                                         ; preds = %for.inc46, %if.end14
  %19 = load i32, i32* %i, align 4, !dbg !741
  %cmp16 = icmp ult i32 %19, 4, !dbg !744
  br i1 %cmp16, label %for.body, label %for.end48, !dbg !745

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %len_test, metadata !746, metadata !305), !dbg !748
  call void @llvm.dbg.declare(metadata i8** %buf_back, metadata !749, metadata !305), !dbg !751
  %20 = load i8*, i8** %buf, align 8, !dbg !752
  %21 = load i32, i32* %i, align 4, !dbg !753
  %idxprom = zext i32 %21 to i64, !dbg !754
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !754
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 2, !dbg !755
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 %idxprom, !dbg !754
  %23 = load i32, i32* %arrayidx, align 4, !dbg !754
  %idx.ext = zext i32 %23 to i64, !dbg !756
  %idx.neg = sub i64 0, %idx.ext, !dbg !756
  %add.ptr17 = getelementptr inbounds i8, i8* %20, i64 %idx.neg, !dbg !756
  %add.ptr18 = getelementptr inbounds i8, i8* %add.ptr17, i64 -1, !dbg !757
  store i8* %add.ptr18, i8** %buf_back, align 8, !dbg !751
  %24 = load i8*, i8** %buf, align 8, !dbg !758
  %25 = bitcast i8* %24 to i16*, !dbg !758
  %26 = load i16, i16* %25, align 2, !dbg !758
  %conv = zext i16 %26 to i32, !dbg !758
  %27 = load i8*, i8** %buf_back, align 8, !dbg !758
  %28 = bitcast i8* %27 to i16*, !dbg !758
  %29 = load i16, i16* %28, align 2, !dbg !758
  %conv19 = zext i16 %29 to i32, !dbg !758
  %cmp20 = icmp ne i32 %conv, %conv19, !dbg !758
  br i1 %cmp20, label %if.then22, label %if.end25, !dbg !760

if.then22:                                        ; preds = %for.body
  %30 = load i32, i32* %i, align 4, !dbg !761
  %idxprom23 = zext i32 %30 to i64, !dbg !763
  %arrayidx24 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom23, !dbg !763
  store i32 0, i32* %arrayidx24, align 4, !dbg !764
  br label %for.inc46, !dbg !765

if.end25:                                         ; preds = %for.body
  store i32 2, i32* %len_test, align 4, !dbg !766
  br label %for.cond26, !dbg !768

for.cond26:                                       ; preds = %for.inc, %if.end25
  %31 = load i32, i32* %len_test, align 4, !dbg !769
  %32 = load i32, i32* %buf_avail, align 4, !dbg !772
  %cmp27 = icmp ult i32 %31, %32, !dbg !773
  br i1 %cmp27, label %land.rhs, label %land.end, !dbg !774

land.rhs:                                         ; preds = %for.cond26
  %33 = load i32, i32* %len_test, align 4, !dbg !775
  %idxprom29 = zext i32 %33 to i64, !dbg !776
  %34 = load i8*, i8** %buf, align 8, !dbg !776
  %arrayidx30 = getelementptr inbounds i8, i8* %34, i64 %idxprom29, !dbg !776
  %35 = load i8, i8* %arrayidx30, align 1, !dbg !776
  %conv31 = zext i8 %35 to i32, !dbg !776
  %36 = load i32, i32* %len_test, align 4, !dbg !777
  %idxprom32 = zext i32 %36 to i64, !dbg !778
  %37 = load i8*, i8** %buf_back, align 8, !dbg !778
  %arrayidx33 = getelementptr inbounds i8, i8* %37, i64 %idxprom32, !dbg !778
  %38 = load i8, i8* %arrayidx33, align 1, !dbg !778
  %conv34 = zext i8 %38 to i32, !dbg !778
  %cmp35 = icmp eq i32 %conv31, %conv34, !dbg !779
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond26
  %39 = phi i1 [ false, %for.cond26 ], [ %cmp35, %land.rhs ]
  br i1 %39, label %for.body37, label %for.end, !dbg !780

for.body37:                                       ; preds = %land.end
  br label %for.inc, !dbg !782

for.inc:                                          ; preds = %for.body37
  %40 = load i32, i32* %len_test, align 4, !dbg !784
  %inc = add i32 %40, 1, !dbg !784
  store i32 %inc, i32* %len_test, align 4, !dbg !784
  br label %for.cond26, !dbg !785

for.end:                                          ; preds = %land.end
  %41 = load i32, i32* %len_test, align 4, !dbg !787
  %42 = load i32, i32* %i, align 4, !dbg !788
  %idxprom38 = zext i32 %42 to i64, !dbg !789
  %arrayidx39 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom38, !dbg !789
  store i32 %41, i32* %arrayidx39, align 4, !dbg !790
  %43 = load i32, i32* %len_test, align 4, !dbg !791
  %44 = load i32, i32* %rep_max_index, align 4, !dbg !793
  %idxprom40 = zext i32 %44 to i64, !dbg !794
  %arrayidx41 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom40, !dbg !794
  %45 = load i32, i32* %arrayidx41, align 4, !dbg !794
  %cmp42 = icmp ugt i32 %43, %45, !dbg !795
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !796

if.then44:                                        ; preds = %for.end
  %46 = load i32, i32* %i, align 4, !dbg !797
  store i32 %46, i32* %rep_max_index, align 4, !dbg !798
  br label %if.end45, !dbg !799

if.end45:                                         ; preds = %if.then44, %for.end
  br label %for.inc46, !dbg !800

for.inc46:                                        ; preds = %if.end45, %if.then22
  %47 = load i32, i32* %i, align 4, !dbg !801
  %inc47 = add i32 %47, 1, !dbg !801
  store i32 %inc47, i32* %i, align 4, !dbg !801
  br label %for.cond, !dbg !803

for.end48:                                        ; preds = %for.cond
  %48 = load i32, i32* %rep_max_index, align 4, !dbg !804
  %idxprom49 = zext i32 %48 to i64, !dbg !806
  %arrayidx50 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom49, !dbg !806
  %49 = load i32, i32* %arrayidx50, align 4, !dbg !806
  %50 = load i32, i32* %nice_len, align 4, !dbg !807
  %cmp51 = icmp uge i32 %49, %50, !dbg !808
  br i1 %cmp51, label %if.then53, label %if.end56, !dbg !809

if.then53:                                        ; preds = %for.end48
  %51 = load i32, i32* %rep_max_index, align 4, !dbg !810
  %52 = load i32*, i32** %back_res.addr, align 8, !dbg !812
  store i32 %51, i32* %52, align 4, !dbg !813
  %53 = load i32, i32* %rep_max_index, align 4, !dbg !814
  %idxprom54 = zext i32 %53 to i64, !dbg !815
  %arrayidx55 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom54, !dbg !815
  %54 = load i32, i32* %arrayidx55, align 4, !dbg !815
  %55 = load i32*, i32** %len_res.addr, align 8, !dbg !816
  store i32 %54, i32* %55, align 4, !dbg !817
  %56 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !818
  %57 = load i32*, i32** %len_res.addr, align 8, !dbg !819
  %58 = load i32, i32* %57, align 4, !dbg !820
  %sub = sub i32 %58, 1, !dbg !821
  call void @mf_skip(%struct.lzma_mf_s* %56, i32 %sub), !dbg !822
  store i32 -1, i32* %retval, align 4, !dbg !823
  br label %return, !dbg !823

if.end56:                                         ; preds = %for.end48
  %59 = load i32, i32* %len_main, align 4, !dbg !824
  %60 = load i32, i32* %nice_len, align 4, !dbg !826
  %cmp57 = icmp uge i32 %59, %60, !dbg !827
  br i1 %cmp57, label %if.then59, label %if.end66, !dbg !828

if.then59:                                        ; preds = %if.end56
  %61 = load i32, i32* %matches_count, align 4, !dbg !829
  %sub60 = sub i32 %61, 1, !dbg !831
  %idxprom61 = zext i32 %sub60 to i64, !dbg !832
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !832
  %matches62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 3, !dbg !833
  %arrayidx63 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches62, i64 0, i64 %idxprom61, !dbg !832
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx63, i32 0, i32 1, !dbg !834
  %63 = load i32, i32* %dist, align 4, !dbg !834
  %add64 = add i32 %63, 4, !dbg !835
  %64 = load i32*, i32** %back_res.addr, align 8, !dbg !836
  store i32 %add64, i32* %64, align 4, !dbg !837
  %65 = load i32, i32* %len_main, align 4, !dbg !838
  %66 = load i32*, i32** %len_res.addr, align 8, !dbg !839
  store i32 %65, i32* %66, align 4, !dbg !840
  %67 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !841
  %68 = load i32, i32* %len_main, align 4, !dbg !842
  %sub65 = sub i32 %68, 1, !dbg !843
  call void @mf_skip(%struct.lzma_mf_s* %67, i32 %sub65), !dbg !844
  store i32 -1, i32* %retval, align 4, !dbg !845
  br label %return, !dbg !845

if.end66:                                         ; preds = %if.end56
  %69 = load i8*, i8** %buf, align 8, !dbg !846
  %70 = load i8, i8* %69, align 1, !dbg !847
  store i8 %70, i8* %current_byte, align 1, !dbg !848
  %71 = load i8*, i8** %buf, align 8, !dbg !849
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !850
  %reps67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 2, !dbg !851
  %arrayidx68 = getelementptr inbounds [4 x i32], [4 x i32]* %reps67, i64 0, i64 0, !dbg !850
  %73 = load i32, i32* %arrayidx68, align 4, !dbg !850
  %idx.ext69 = zext i32 %73 to i64, !dbg !852
  %idx.neg70 = sub i64 0, %idx.ext69, !dbg !852
  %add.ptr71 = getelementptr inbounds i8, i8* %71, i64 %idx.neg70, !dbg !852
  %add.ptr72 = getelementptr inbounds i8, i8* %add.ptr71, i64 -1, !dbg !853
  %74 = load i8, i8* %add.ptr72, align 1, !dbg !854
  store i8 %74, i8* %match_byte, align 1, !dbg !855
  %75 = load i32, i32* %len_main, align 4, !dbg !856
  %cmp73 = icmp ult i32 %75, 2, !dbg !858
  br i1 %cmp73, label %land.lhs.true, label %if.end85, !dbg !859

land.lhs.true:                                    ; preds = %if.end66
  %76 = load i8, i8* %current_byte, align 1, !dbg !860
  %conv75 = zext i8 %76 to i32, !dbg !860
  %77 = load i8, i8* %match_byte, align 1, !dbg !862
  %conv76 = zext i8 %77 to i32, !dbg !862
  %cmp77 = icmp ne i32 %conv75, %conv76, !dbg !863
  br i1 %cmp77, label %land.lhs.true79, label %if.end85, !dbg !864

land.lhs.true79:                                  ; preds = %land.lhs.true
  %78 = load i32, i32* %rep_max_index, align 4, !dbg !865
  %idxprom80 = zext i32 %78 to i64, !dbg !866
  %arrayidx81 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom80, !dbg !866
  %79 = load i32, i32* %arrayidx81, align 4, !dbg !866
  %cmp82 = icmp ult i32 %79, 2, !dbg !867
  br i1 %cmp82, label %if.then84, label %if.end85, !dbg !868

if.then84:                                        ; preds = %land.lhs.true79
  %80 = load i32*, i32** %back_res.addr, align 8, !dbg !869
  store i32 -1, i32* %80, align 4, !dbg !871
  %81 = load i32*, i32** %len_res.addr, align 8, !dbg !872
  store i32 1, i32* %81, align 4, !dbg !873
  store i32 -1, i32* %retval, align 4, !dbg !874
  br label %return, !dbg !874

if.end85:                                         ; preds = %land.lhs.true79, %land.lhs.true, %if.end66
  %82 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !875
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %82, i32 0, i32 1, !dbg !876
  %83 = load i32, i32* %state, align 8, !dbg !876
  %84 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !877
  %opts = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %84, i32 0, i32 32, !dbg !878
  %arrayidx86 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts, i64 0, i64 0, !dbg !877
  %state87 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx86, i32 0, i32 0, !dbg !879
  store i32 %83, i32* %state87, align 4, !dbg !880
  %85 = load i32, i32* %position.addr, align 4, !dbg !881
  %86 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !882
  %pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %86, i32 0, i32 9, !dbg !883
  %87 = load i32, i32* %pos_mask, align 8, !dbg !883
  %and = and i32 %85, %87, !dbg !884
  store i32 %and, i32* %pos_state, align 4, !dbg !885
  %88 = load i32, i32* %pos_state, align 4, !dbg !886
  %idxprom88 = zext i32 %88 to i64, !dbg !887
  %89 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !888
  %state89 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %89, i32 0, i32 1, !dbg !889
  %90 = load i32, i32* %state89, align 8, !dbg !889
  %idxprom90 = zext i32 %90 to i64, !dbg !887
  %91 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !887
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %91, i32 0, i32 13, !dbg !890
  %arrayidx91 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 %idxprom90, !dbg !887
  %arrayidx92 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx91, i64 0, i64 %idxprom88, !dbg !887
  %92 = load i16, i16* %arrayidx92, align 2, !dbg !887
  %call93 = call i32 @rc_bit_0_price(i16 zeroext %92), !dbg !891
  %93 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !892
  %94 = load i32, i32* %position.addr, align 4, !dbg !893
  %95 = load i8*, i8** %buf, align 8, !dbg !894
  %arrayidx94 = getelementptr inbounds i8, i8* %95, i64 -1, !dbg !894
  %96 = load i8, i8* %arrayidx94, align 1, !dbg !894
  %conv95 = zext i8 %96 to i32, !dbg !894
  %97 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !895
  %state96 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %97, i32 0, i32 1, !dbg !895
  %98 = load i32, i32* %state96, align 8, !dbg !895
  %cmp97 = icmp ult i32 %98, 7, !dbg !895
  %lnot = xor i1 %cmp97, true, !dbg !896
  %99 = load i8, i8* %match_byte, align 1, !dbg !897
  %conv99 = zext i8 %99 to i32, !dbg !897
  %100 = load i8, i8* %current_byte, align 1, !dbg !898
  %conv100 = zext i8 %100 to i32, !dbg !898
  %call101 = call i32 @get_literal_price(%struct.lzma_coder_s* %93, i32 %94, i32 %conv95, i1 zeroext %lnot, i32 %conv99, i32 %conv100), !dbg !899
  %add102 = add i32 %call93, %call101, !dbg !900
  %101 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !901
  %opts103 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %101, i32 0, i32 32, !dbg !902
  %arrayidx104 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts103, i64 0, i64 1, !dbg !901
  %price = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx104, i32 0, i32 5, !dbg !903
  store i32 %add102, i32* %price, align 4, !dbg !904
  %102 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !905
  %opts105 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %102, i32 0, i32 32, !dbg !906
  %arrayidx106 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts105, i64 0, i64 1, !dbg !905
  call void @make_literal(%struct.lzma_optimal* %arrayidx106), !dbg !907
  %103 = load i32, i32* %pos_state, align 4, !dbg !908
  %idxprom107 = zext i32 %103 to i64, !dbg !909
  %104 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !910
  %state108 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %104, i32 0, i32 1, !dbg !911
  %105 = load i32, i32* %state108, align 8, !dbg !911
  %idxprom109 = zext i32 %105 to i64, !dbg !909
  %106 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !909
  %is_match110 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %106, i32 0, i32 13, !dbg !912
  %arrayidx111 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match110, i64 0, i64 %idxprom109, !dbg !909
  %arrayidx112 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx111, i64 0, i64 %idxprom107, !dbg !909
  %107 = load i16, i16* %arrayidx112, align 2, !dbg !909
  %call113 = call i32 @rc_bit_1_price(i16 zeroext %107), !dbg !913
  store i32 %call113, i32* %match_price, align 4, !dbg !914
  %108 = load i32, i32* %match_price, align 4, !dbg !915
  %109 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !916
  %state114 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %109, i32 0, i32 1, !dbg !917
  %110 = load i32, i32* %state114, align 8, !dbg !917
  %idxprom115 = zext i32 %110 to i64, !dbg !918
  %111 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !918
  %is_rep = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %111, i32 0, i32 14, !dbg !919
  %arrayidx116 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep, i64 0, i64 %idxprom115, !dbg !918
  %112 = load i16, i16* %arrayidx116, align 2, !dbg !918
  %call117 = call i32 @rc_bit_1_price(i16 zeroext %112), !dbg !920
  %add118 = add i32 %108, %call117, !dbg !921
  store i32 %add118, i32* %rep_match_price, align 4, !dbg !922
  %113 = load i8, i8* %match_byte, align 1, !dbg !923
  %conv119 = zext i8 %113 to i32, !dbg !923
  %114 = load i8, i8* %current_byte, align 1, !dbg !925
  %conv120 = zext i8 %114 to i32, !dbg !925
  %cmp121 = icmp eq i32 %conv119, %conv120, !dbg !926
  br i1 %cmp121, label %if.then123, label %if.end139, !dbg !927

if.then123:                                       ; preds = %if.end85
  call void @llvm.dbg.declare(metadata i32* %short_rep_price, metadata !928, metadata !305), !dbg !930
  %115 = load i32, i32* %rep_match_price, align 4, !dbg !931
  %116 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !932
  %117 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !933
  %state124 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %117, i32 0, i32 1, !dbg !934
  %118 = load i32, i32* %state124, align 8, !dbg !934
  %119 = load i32, i32* %pos_state, align 4, !dbg !935
  %call125 = call i32 @get_short_rep_price(%struct.lzma_coder_s* %116, i32 %118, i32 %119), !dbg !936
  %add126 = add i32 %115, %call125, !dbg !937
  store i32 %add126, i32* %short_rep_price, align 4, !dbg !930
  %120 = load i32, i32* %short_rep_price, align 4, !dbg !938
  %121 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !940
  %opts127 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %121, i32 0, i32 32, !dbg !941
  %arrayidx128 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts127, i64 0, i64 1, !dbg !940
  %price129 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx128, i32 0, i32 5, !dbg !942
  %122 = load i32, i32* %price129, align 4, !dbg !942
  %cmp130 = icmp ult i32 %120, %122, !dbg !943
  br i1 %cmp130, label %if.then132, label %if.end138, !dbg !944

if.then132:                                       ; preds = %if.then123
  %123 = load i32, i32* %short_rep_price, align 4, !dbg !945
  %124 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !947
  %opts133 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %124, i32 0, i32 32, !dbg !948
  %arrayidx134 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts133, i64 0, i64 1, !dbg !947
  %price135 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx134, i32 0, i32 5, !dbg !949
  store i32 %123, i32* %price135, align 4, !dbg !950
  %125 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !951
  %opts136 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %125, i32 0, i32 32, !dbg !952
  %arrayidx137 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts136, i64 0, i64 1, !dbg !951
  call void @make_short_rep(%struct.lzma_optimal* %arrayidx137), !dbg !953
  br label %if.end138, !dbg !954

if.end138:                                        ; preds = %if.then132, %if.then123
  br label %if.end139, !dbg !955

if.end139:                                        ; preds = %if.end138, %if.end85
  %126 = load i32, i32* %len_main, align 4, !dbg !956
  %127 = load i32, i32* %rep_max_index, align 4, !dbg !956
  %idxprom140 = zext i32 %127 to i64, !dbg !956
  %arrayidx141 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom140, !dbg !956
  %128 = load i32, i32* %arrayidx141, align 4, !dbg !956
  %cmp142 = icmp ugt i32 %126, %128, !dbg !956
  br i1 %cmp142, label %cond.true144, label %cond.false145, !dbg !956

cond.true144:                                     ; preds = %if.end139
  %129 = load i32, i32* %len_main, align 4, !dbg !957
  br label %cond.end148, !dbg !957

cond.false145:                                    ; preds = %if.end139
  %130 = load i32, i32* %rep_max_index, align 4, !dbg !958
  %idxprom146 = zext i32 %130 to i64, !dbg !958
  %arrayidx147 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom146, !dbg !958
  %131 = load i32, i32* %arrayidx147, align 4, !dbg !958
  br label %cond.end148, !dbg !958

cond.end148:                                      ; preds = %cond.false145, %cond.true144
  %cond149 = phi i32 [ %129, %cond.true144 ], [ %131, %cond.false145 ], !dbg !959
  store i32 %cond149, i32* %len_end, align 4, !dbg !960
  %132 = load i32, i32* %len_end, align 4, !dbg !961
  %cmp150 = icmp ult i32 %132, 2, !dbg !963
  br i1 %cmp150, label %if.then152, label %if.end155, !dbg !964

if.then152:                                       ; preds = %cond.end148
  %133 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !965
  %opts153 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %133, i32 0, i32 32, !dbg !967
  %arrayidx154 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts153, i64 0, i64 1, !dbg !965
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx154, i32 0, i32 7, !dbg !968
  %134 = load i32, i32* %back_prev, align 4, !dbg !968
  %135 = load i32*, i32** %back_res.addr, align 8, !dbg !969
  store i32 %134, i32* %135, align 4, !dbg !970
  %136 = load i32*, i32** %len_res.addr, align 8, !dbg !971
  store i32 1, i32* %136, align 4, !dbg !972
  store i32 -1, i32* %retval, align 4, !dbg !973
  br label %return, !dbg !973

if.end155:                                        ; preds = %cond.end148
  %137 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !974
  %opts156 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %137, i32 0, i32 32, !dbg !975
  %arrayidx157 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts156, i64 0, i64 1, !dbg !974
  %pos_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx157, i32 0, i32 6, !dbg !976
  store i32 0, i32* %pos_prev, align 4, !dbg !977
  store i32 0, i32* %i, align 4, !dbg !978
  br label %for.cond158, !dbg !980

for.cond158:                                      ; preds = %for.inc169, %if.end155
  %138 = load i32, i32* %i, align 4, !dbg !981
  %cmp159 = icmp ult i32 %138, 4, !dbg !984
  br i1 %cmp159, label %for.body161, label %for.end171, !dbg !985

for.body161:                                      ; preds = %for.cond158
  %139 = load i32, i32* %i, align 4, !dbg !986
  %idxprom162 = zext i32 %139 to i64, !dbg !987
  %140 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !987
  %reps163 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %140, i32 0, i32 2, !dbg !988
  %arrayidx164 = getelementptr inbounds [4 x i32], [4 x i32]* %reps163, i64 0, i64 %idxprom162, !dbg !987
  %141 = load i32, i32* %arrayidx164, align 4, !dbg !987
  %142 = load i32, i32* %i, align 4, !dbg !989
  %idxprom165 = zext i32 %142 to i64, !dbg !990
  %143 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !990
  %opts166 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %143, i32 0, i32 32, !dbg !991
  %arrayidx167 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts166, i64 0, i64 0, !dbg !990
  %backs = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx167, i32 0, i32 8, !dbg !992
  %arrayidx168 = getelementptr inbounds [4 x i32], [4 x i32]* %backs, i64 0, i64 %idxprom165, !dbg !990
  store i32 %141, i32* %arrayidx168, align 4, !dbg !993
  br label %for.inc169, !dbg !990

for.inc169:                                       ; preds = %for.body161
  %144 = load i32, i32* %i, align 4, !dbg !994
  %inc170 = add i32 %144, 1, !dbg !994
  store i32 %inc170, i32* %i, align 4, !dbg !994
  br label %for.cond158, !dbg !996

for.end171:                                       ; preds = %for.cond158
  %145 = load i32, i32* %len_end, align 4, !dbg !997
  store i32 %145, i32* %len, align 4, !dbg !998
  br label %do.body, !dbg !999

do.body:                                          ; preds = %do.cond, %for.end171
  %146 = load i32, i32* %len, align 4, !dbg !1000
  %idxprom172 = zext i32 %146 to i64, !dbg !1002
  %147 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1002
  %opts173 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %147, i32 0, i32 32, !dbg !1003
  %arrayidx174 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts173, i64 0, i64 %idxprom172, !dbg !1002
  %price175 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx174, i32 0, i32 5, !dbg !1004
  store i32 1073741824, i32* %price175, align 4, !dbg !1005
  br label %do.cond, !dbg !1006

do.cond:                                          ; preds = %do.body
  %148 = load i32, i32* %len, align 4, !dbg !1007
  %dec = add i32 %148, -1, !dbg !1007
  store i32 %dec, i32* %len, align 4, !dbg !1007
  %cmp176 = icmp uge i32 %dec, 2, !dbg !1008
  br i1 %cmp176, label %do.body, label %do.end, !dbg !1009

do.end:                                           ; preds = %do.cond
  store i32 0, i32* %i, align 4, !dbg !1010
  br label %for.cond178, !dbg !1012

for.cond178:                                      ; preds = %for.inc223, %do.end
  %149 = load i32, i32* %i, align 4, !dbg !1013
  %cmp179 = icmp ult i32 %149, 4, !dbg !1016
  br i1 %cmp179, label %for.body181, label %for.end225, !dbg !1017

for.body181:                                      ; preds = %for.cond178
  call void @llvm.dbg.declare(metadata i32* %price182, metadata !1018, metadata !305), !dbg !1020
  call void @llvm.dbg.declare(metadata i32* %rep_len, metadata !1021, metadata !305), !dbg !1022
  %150 = load i32, i32* %i, align 4, !dbg !1023
  %idxprom183 = zext i32 %150 to i64, !dbg !1024
  %arrayidx184 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 %idxprom183, !dbg !1024
  %151 = load i32, i32* %arrayidx184, align 4, !dbg !1024
  store i32 %151, i32* %rep_len, align 4, !dbg !1022
  %152 = load i32, i32* %rep_len, align 4, !dbg !1025
  %cmp185 = icmp ult i32 %152, 2, !dbg !1027
  br i1 %cmp185, label %if.then187, label %if.end188, !dbg !1028

if.then187:                                       ; preds = %for.body181
  br label %for.inc223, !dbg !1029

if.end188:                                        ; preds = %for.body181
  %153 = load i32, i32* %rep_match_price, align 4, !dbg !1030
  %154 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1031
  %155 = load i32, i32* %i, align 4, !dbg !1032
  %156 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1033
  %state189 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %156, i32 0, i32 1, !dbg !1034
  %157 = load i32, i32* %state189, align 8, !dbg !1034
  %158 = load i32, i32* %pos_state, align 4, !dbg !1035
  %call190 = call i32 @get_pure_rep_price(%struct.lzma_coder_s* %154, i32 %155, i32 %157, i32 %158), !dbg !1036
  %add191 = add i32 %153, %call190, !dbg !1037
  store i32 %add191, i32* %price182, align 4, !dbg !1038
  br label %do.body192, !dbg !1039

do.body192:                                       ; preds = %do.cond218, %if.end188
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price, metadata !1040, metadata !305), !dbg !1042
  %159 = load i32, i32* %price182, align 4, !dbg !1043
  %160 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1044
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %160, i32 0, i32 23, !dbg !1045
  %161 = load i32, i32* %rep_len, align 4, !dbg !1046
  %162 = load i32, i32* %pos_state, align 4, !dbg !1047
  %call193 = call i32 @get_len_price(%struct.lzma_length_encoder* %rep_len_encoder, i32 %161, i32 %162), !dbg !1048
  %add194 = add i32 %159, %call193, !dbg !1049
  store i32 %add194, i32* %cur_and_len_price, align 4, !dbg !1042
  %163 = load i32, i32* %cur_and_len_price, align 4, !dbg !1050
  %164 = load i32, i32* %rep_len, align 4, !dbg !1052
  %idxprom195 = zext i32 %164 to i64, !dbg !1053
  %165 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1053
  %opts196 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %165, i32 0, i32 32, !dbg !1054
  %arrayidx197 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts196, i64 0, i64 %idxprom195, !dbg !1053
  %price198 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx197, i32 0, i32 5, !dbg !1055
  %166 = load i32, i32* %price198, align 4, !dbg !1055
  %cmp199 = icmp ult i32 %163, %166, !dbg !1056
  br i1 %cmp199, label %if.then201, label %if.end217, !dbg !1057

if.then201:                                       ; preds = %do.body192
  %167 = load i32, i32* %cur_and_len_price, align 4, !dbg !1058
  %168 = load i32, i32* %rep_len, align 4, !dbg !1060
  %idxprom202 = zext i32 %168 to i64, !dbg !1061
  %169 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1061
  %opts203 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %169, i32 0, i32 32, !dbg !1062
  %arrayidx204 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts203, i64 0, i64 %idxprom202, !dbg !1061
  %price205 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx204, i32 0, i32 5, !dbg !1063
  store i32 %167, i32* %price205, align 4, !dbg !1064
  %170 = load i32, i32* %rep_len, align 4, !dbg !1065
  %idxprom206 = zext i32 %170 to i64, !dbg !1066
  %171 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1066
  %opts207 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %171, i32 0, i32 32, !dbg !1067
  %arrayidx208 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts207, i64 0, i64 %idxprom206, !dbg !1066
  %pos_prev209 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx208, i32 0, i32 6, !dbg !1068
  store i32 0, i32* %pos_prev209, align 4, !dbg !1069
  %172 = load i32, i32* %i, align 4, !dbg !1070
  %173 = load i32, i32* %rep_len, align 4, !dbg !1071
  %idxprom210 = zext i32 %173 to i64, !dbg !1072
  %174 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1072
  %opts211 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %174, i32 0, i32 32, !dbg !1073
  %arrayidx212 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts211, i64 0, i64 %idxprom210, !dbg !1072
  %back_prev213 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx212, i32 0, i32 7, !dbg !1074
  store i32 %172, i32* %back_prev213, align 4, !dbg !1075
  %175 = load i32, i32* %rep_len, align 4, !dbg !1076
  %idxprom214 = zext i32 %175 to i64, !dbg !1077
  %176 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1077
  %opts215 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %176, i32 0, i32 32, !dbg !1078
  %arrayidx216 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts215, i64 0, i64 %idxprom214, !dbg !1077
  %prev_1_is_literal = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx216, i32 0, i32 1, !dbg !1079
  store i8 0, i8* %prev_1_is_literal, align 4, !dbg !1080
  br label %if.end217, !dbg !1081

if.end217:                                        ; preds = %if.then201, %do.body192
  br label %do.cond218, !dbg !1082

do.cond218:                                       ; preds = %if.end217
  %177 = load i32, i32* %rep_len, align 4, !dbg !1083
  %dec219 = add i32 %177, -1, !dbg !1083
  store i32 %dec219, i32* %rep_len, align 4, !dbg !1083
  %cmp220 = icmp uge i32 %dec219, 2, !dbg !1085
  br i1 %cmp220, label %do.body192, label %do.end222, !dbg !1086

do.end222:                                        ; preds = %do.cond218
  br label %for.inc223, !dbg !1087

for.inc223:                                       ; preds = %do.end222, %if.then187
  %178 = load i32, i32* %i, align 4, !dbg !1088
  %inc224 = add i32 %178, 1, !dbg !1088
  store i32 %inc224, i32* %i, align 4, !dbg !1088
  br label %for.cond178, !dbg !1090

for.end225:                                       ; preds = %for.cond178
  %179 = load i32, i32* %match_price, align 4, !dbg !1091
  %180 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1092
  %state226 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %180, i32 0, i32 1, !dbg !1093
  %181 = load i32, i32* %state226, align 8, !dbg !1093
  %idxprom227 = zext i32 %181 to i64, !dbg !1094
  %182 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1094
  %is_rep228 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %182, i32 0, i32 14, !dbg !1095
  %arrayidx229 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep228, i64 0, i64 %idxprom227, !dbg !1094
  %183 = load i16, i16* %arrayidx229, align 2, !dbg !1094
  %call230 = call i32 @rc_bit_0_price(i16 zeroext %183), !dbg !1096
  %add231 = add i32 %179, %call230, !dbg !1097
  store i32 %add231, i32* %normal_match_price, align 4, !dbg !1098
  %arrayidx232 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 0, !dbg !1099
  %184 = load i32, i32* %arrayidx232, align 16, !dbg !1099
  %cmp233 = icmp uge i32 %184, 2, !dbg !1100
  br i1 %cmp233, label %cond.true235, label %cond.false238, !dbg !1099

cond.true235:                                     ; preds = %for.end225
  %arrayidx236 = getelementptr inbounds [4 x i32], [4 x i32]* %rep_lens, i64 0, i64 0, !dbg !1101
  %185 = load i32, i32* %arrayidx236, align 16, !dbg !1101
  %add237 = add i32 %185, 1, !dbg !1102
  br label %cond.end239, !dbg !1103

cond.false238:                                    ; preds = %for.end225
  br label %cond.end239, !dbg !1104

cond.end239:                                      ; preds = %cond.false238, %cond.true235
  %cond240 = phi i32 [ %add237, %cond.true235 ], [ 2, %cond.false238 ], !dbg !1105
  store i32 %cond240, i32* %len, align 4, !dbg !1106
  %186 = load i32, i32* %len, align 4, !dbg !1107
  %187 = load i32, i32* %len_main, align 4, !dbg !1109
  %cmp241 = icmp ule i32 %186, %187, !dbg !1110
  br i1 %cmp241, label %if.then243, label %if.end302, !dbg !1111

if.then243:                                       ; preds = %cond.end239
  call void @llvm.dbg.declare(metadata i32* %i244, metadata !1112, metadata !305), !dbg !1114
  store i32 0, i32* %i244, align 4, !dbg !1114
  br label %while.cond, !dbg !1115

while.cond:                                       ; preds = %while.body, %if.then243
  %188 = load i32, i32* %len, align 4, !dbg !1116
  %189 = load i32, i32* %i244, align 4, !dbg !1118
  %idxprom245 = zext i32 %189 to i64, !dbg !1119
  %190 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1119
  %matches246 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %190, i32 0, i32 3, !dbg !1120
  %arrayidx247 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches246, i64 0, i64 %idxprom245, !dbg !1119
  %len248 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx247, i32 0, i32 0, !dbg !1121
  %191 = load i32, i32* %len248, align 4, !dbg !1121
  %cmp249 = icmp ugt i32 %188, %191, !dbg !1122
  br i1 %cmp249, label %while.body, label %while.end, !dbg !1123

while.body:                                       ; preds = %while.cond
  %192 = load i32, i32* %i244, align 4, !dbg !1124
  %inc251 = add i32 %192, 1, !dbg !1124
  store i32 %inc251, i32* %i244, align 4, !dbg !1124
  br label %while.cond, !dbg !1125

while.end:                                        ; preds = %while.cond
  br label %for.cond252, !dbg !1127

for.cond252:                                      ; preds = %for.inc299, %while.end
  call void @llvm.dbg.declare(metadata i32* %dist253, metadata !1128, metadata !305), !dbg !1132
  %193 = load i32, i32* %i244, align 4, !dbg !1133
  %idxprom254 = zext i32 %193 to i64, !dbg !1134
  %194 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1134
  %matches255 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %194, i32 0, i32 3, !dbg !1135
  %arrayidx256 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches255, i64 0, i64 %idxprom254, !dbg !1134
  %dist257 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx256, i32 0, i32 1, !dbg !1136
  %195 = load i32, i32* %dist257, align 4, !dbg !1136
  store i32 %195, i32* %dist253, align 4, !dbg !1132
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price258, metadata !1137, metadata !305), !dbg !1138
  %196 = load i32, i32* %normal_match_price, align 4, !dbg !1139
  %197 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1140
  %198 = load i32, i32* %dist253, align 4, !dbg !1141
  %199 = load i32, i32* %len, align 4, !dbg !1142
  %200 = load i32, i32* %pos_state, align 4, !dbg !1143
  %call259 = call i32 @get_pos_len_price(%struct.lzma_coder_s* %197, i32 %198, i32 %199, i32 %200), !dbg !1144
  %add260 = add i32 %196, %call259, !dbg !1145
  store i32 %add260, i32* %cur_and_len_price258, align 4, !dbg !1138
  %201 = load i32, i32* %cur_and_len_price258, align 4, !dbg !1146
  %202 = load i32, i32* %len, align 4, !dbg !1148
  %idxprom261 = zext i32 %202 to i64, !dbg !1149
  %203 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1149
  %opts262 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %203, i32 0, i32 32, !dbg !1150
  %arrayidx263 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts262, i64 0, i64 %idxprom261, !dbg !1149
  %price264 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx263, i32 0, i32 5, !dbg !1151
  %204 = load i32, i32* %price264, align 4, !dbg !1151
  %cmp265 = icmp ult i32 %201, %204, !dbg !1152
  br i1 %cmp265, label %if.then267, label %if.end285, !dbg !1153

if.then267:                                       ; preds = %for.cond252
  %205 = load i32, i32* %cur_and_len_price258, align 4, !dbg !1154
  %206 = load i32, i32* %len, align 4, !dbg !1156
  %idxprom268 = zext i32 %206 to i64, !dbg !1157
  %207 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1157
  %opts269 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %207, i32 0, i32 32, !dbg !1158
  %arrayidx270 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts269, i64 0, i64 %idxprom268, !dbg !1157
  %price271 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx270, i32 0, i32 5, !dbg !1159
  store i32 %205, i32* %price271, align 4, !dbg !1160
  %208 = load i32, i32* %len, align 4, !dbg !1161
  %idxprom272 = zext i32 %208 to i64, !dbg !1162
  %209 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1162
  %opts273 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %209, i32 0, i32 32, !dbg !1163
  %arrayidx274 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts273, i64 0, i64 %idxprom272, !dbg !1162
  %pos_prev275 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx274, i32 0, i32 6, !dbg !1164
  store i32 0, i32* %pos_prev275, align 4, !dbg !1165
  %210 = load i32, i32* %dist253, align 4, !dbg !1166
  %add276 = add i32 %210, 4, !dbg !1167
  %211 = load i32, i32* %len, align 4, !dbg !1168
  %idxprom277 = zext i32 %211 to i64, !dbg !1169
  %212 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1169
  %opts278 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %212, i32 0, i32 32, !dbg !1170
  %arrayidx279 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts278, i64 0, i64 %idxprom277, !dbg !1169
  %back_prev280 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx279, i32 0, i32 7, !dbg !1171
  store i32 %add276, i32* %back_prev280, align 4, !dbg !1172
  %213 = load i32, i32* %len, align 4, !dbg !1173
  %idxprom281 = zext i32 %213 to i64, !dbg !1174
  %214 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1174
  %opts282 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %214, i32 0, i32 32, !dbg !1175
  %arrayidx283 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts282, i64 0, i64 %idxprom281, !dbg !1174
  %prev_1_is_literal284 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx283, i32 0, i32 1, !dbg !1176
  store i8 0, i8* %prev_1_is_literal284, align 4, !dbg !1177
  br label %if.end285, !dbg !1178

if.end285:                                        ; preds = %if.then267, %for.cond252
  %215 = load i32, i32* %len, align 4, !dbg !1179
  %216 = load i32, i32* %i244, align 4, !dbg !1181
  %idxprom286 = zext i32 %216 to i64, !dbg !1182
  %217 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1182
  %matches287 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %217, i32 0, i32 3, !dbg !1183
  %arrayidx288 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches287, i64 0, i64 %idxprom286, !dbg !1182
  %len289 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx288, i32 0, i32 0, !dbg !1184
  %218 = load i32, i32* %len289, align 4, !dbg !1184
  %cmp290 = icmp eq i32 %215, %218, !dbg !1185
  br i1 %cmp290, label %if.then292, label %if.end298, !dbg !1186

if.then292:                                       ; preds = %if.end285
  %219 = load i32, i32* %i244, align 4, !dbg !1187
  %inc293 = add i32 %219, 1, !dbg !1187
  store i32 %inc293, i32* %i244, align 4, !dbg !1187
  %220 = load i32, i32* %matches_count, align 4, !dbg !1189
  %cmp294 = icmp eq i32 %inc293, %220, !dbg !1190
  br i1 %cmp294, label %if.then296, label %if.end297, !dbg !1191

if.then296:                                       ; preds = %if.then292
  br label %for.end301, !dbg !1192

if.end297:                                        ; preds = %if.then292
  br label %if.end298, !dbg !1193

if.end298:                                        ; preds = %if.end297, %if.end285
  br label %for.inc299, !dbg !1195

for.inc299:                                       ; preds = %if.end298
  %221 = load i32, i32* %len, align 4, !dbg !1196
  %inc300 = add i32 %221, 1, !dbg !1196
  store i32 %inc300, i32* %len, align 4, !dbg !1196
  br label %for.cond252, !dbg !1198

for.end301:                                       ; preds = %if.then296
  br label %if.end302, !dbg !1199

if.end302:                                        ; preds = %for.end301, %cond.end239
  %222 = load i32, i32* %len_end, align 4, !dbg !1200
  store i32 %222, i32* %retval, align 4, !dbg !1201
  br label %return, !dbg !1201

return:                                           ; preds = %if.end302, %if.then152, %if.then84, %if.then59, %if.then53, %if.then13
  %223 = load i32, i32* %retval, align 4, !dbg !1202
  ret i32 %223, !dbg !1202
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @lzma_mf_find(%struct.lzma_mf_s*, i32*, %struct.lzma_match*) #5

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @helper2(%struct.lzma_coder_s* %coder, i32* %reps, i8* %buf, i32 %len_end, i32 %position, i32 %cur, i32 %nice_len, i32 %buf_avail_full) #3 !dbg !282 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %reps.addr = alloca i32*, align 8
  %buf.addr = alloca i8*, align 8
  %len_end.addr = alloca i32, align 4
  %position.addr = alloca i32, align 4
  %cur.addr = alloca i32, align 4
  %nice_len.addr = alloca i32, align 4
  %buf_avail_full.addr = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %new_len = alloca i32, align 4
  %pos_prev = alloca i32, align 4
  %state = alloca i32, align 4
  %buf_avail = alloca i32, align 4
  %rep_index = alloca i32, align 4
  %i = alloca i32, align 4
  %cur_price = alloca i32, align 4
  %current_byte = alloca i8, align 1
  %match_byte = alloca i8, align 1
  %pos_state = alloca i32, align 4
  %cur_and_1_price = alloca i32, align 4
  %next_is_literal = alloca i8, align 1
  %match_price = alloca i32, align 4
  %rep_match_price = alloca i32, align 4
  %start_len = alloca i32, align 4
  %pos = alloca i32, align 4
  %i107 = alloca i32, align 4
  %short_rep_price = alloca i32, align 4
  %buf_back = alloca i8*, align 8
  %limit = alloca i32, align 4
  %len_test = alloca i32, align 4
  %pos_state_next = alloca i32, align 4
  %next_rep_match_price = alloca i32, align 4
  %offset = alloca i32, align 4
  %cur_and_len_price = alloca i32, align 4
  %state_2 = alloca i32, align 4
  %len_test396 = alloca i32, align 4
  %len_test_2 = alloca i32, align 4
  %len_test_temp = alloca i32, align 4
  %price397 = alloca i32, align 4
  %limit398 = alloca i32, align 4
  %buf_back399 = alloca i8*, align 8
  %cur_and_len_price442 = alloca i32, align 4
  %pos_state_next513 = alloca i32, align 4
  %cur_and_len_literal_price = alloca i32, align 4
  %next_rep_match_price514 = alloca i32, align 4
  %offset515 = alloca i32, align 4
  %cur_and_len_price516 = alloca i32, align 4
  %state_2517 = alloca i32, align 4
  %len_test654 = alloca i32, align 4
  %i655 = alloca i32, align 4
  %normal_match_price = alloca i32, align 4
  %cur_back = alloca i32, align 4
  %cur_and_len_price686 = alloca i32, align 4
  %buf_back726 = alloca i8*, align 8
  %len_test_2731 = alloca i32, align 4
  %limit733 = alloca i32, align 4
  %pos_state_next764 = alloca i32, align 4
  %cur_and_len_literal_price765 = alloca i32, align 4
  %next_rep_match_price766 = alloca i32, align 4
  %offset767 = alloca i32, align 4
  %state_2768 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !1203, metadata !305), !dbg !1204
  store i32* %reps, i32** %reps.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %reps.addr, metadata !1205, metadata !305), !dbg !1206
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1207, metadata !305), !dbg !1208
  store i32 %len_end, i32* %len_end.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_end.addr, metadata !1209, metadata !305), !dbg !1210
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !1211, metadata !305), !dbg !1212
  store i32 %cur, i32* %cur.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur.addr, metadata !1213, metadata !305), !dbg !1214
  store i32 %nice_len, i32* %nice_len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nice_len.addr, metadata !1215, metadata !305), !dbg !1216
  store i32 %buf_avail_full, i32* %buf_avail_full.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %buf_avail_full.addr, metadata !1217, metadata !305), !dbg !1218
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !1219, metadata !305), !dbg !1220
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1221
  %matches_count1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 4, !dbg !1222
  %1 = load i32, i32* %matches_count1, align 4, !dbg !1222
  store i32 %1, i32* %matches_count, align 4, !dbg !1220
  call void @llvm.dbg.declare(metadata i32* %new_len, metadata !1223, metadata !305), !dbg !1224
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1225
  %longest_match_length = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 5, !dbg !1226
  %3 = load i32, i32* %longest_match_length, align 8, !dbg !1226
  store i32 %3, i32* %new_len, align 4, !dbg !1224
  call void @llvm.dbg.declare(metadata i32* %pos_prev, metadata !1227, metadata !305), !dbg !1228
  %4 = load i32, i32* %cur.addr, align 4, !dbg !1229
  %idxprom = zext i32 %4 to i64, !dbg !1230
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1230
  %opts = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 32, !dbg !1231
  %arrayidx = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts, i64 0, i64 %idxprom, !dbg !1230
  %pos_prev2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx, i32 0, i32 6, !dbg !1232
  %6 = load i32, i32* %pos_prev2, align 4, !dbg !1232
  store i32 %6, i32* %pos_prev, align 4, !dbg !1228
  call void @llvm.dbg.declare(metadata i32* %state, metadata !1233, metadata !305), !dbg !1234
  call void @llvm.dbg.declare(metadata i32* %buf_avail, metadata !1235, metadata !305), !dbg !1236
  call void @llvm.dbg.declare(metadata i32* %rep_index, metadata !1237, metadata !305), !dbg !1238
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1239, metadata !305), !dbg !1240
  call void @llvm.dbg.declare(metadata i32* %cur_price, metadata !1241, metadata !305), !dbg !1242
  call void @llvm.dbg.declare(metadata i8* %current_byte, metadata !1243, metadata !305), !dbg !1244
  call void @llvm.dbg.declare(metadata i8* %match_byte, metadata !1245, metadata !305), !dbg !1246
  call void @llvm.dbg.declare(metadata i32* %pos_state, metadata !1247, metadata !305), !dbg !1248
  call void @llvm.dbg.declare(metadata i32* %cur_and_1_price, metadata !1249, metadata !305), !dbg !1250
  call void @llvm.dbg.declare(metadata i8* %next_is_literal, metadata !1251, metadata !305), !dbg !1252
  store i8 0, i8* %next_is_literal, align 1, !dbg !1252
  call void @llvm.dbg.declare(metadata i32* %match_price, metadata !1253, metadata !305), !dbg !1254
  call void @llvm.dbg.declare(metadata i32* %rep_match_price, metadata !1255, metadata !305), !dbg !1256
  call void @llvm.dbg.declare(metadata i32* %start_len, metadata !1257, metadata !305), !dbg !1258
  store i32 2, i32* %start_len, align 4, !dbg !1258
  %7 = load i32, i32* %cur.addr, align 4, !dbg !1259
  %idxprom3 = zext i32 %7 to i64, !dbg !1261
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1261
  %opts4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 32, !dbg !1262
  %arrayidx5 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts4, i64 0, i64 %idxprom3, !dbg !1261
  %prev_1_is_literal = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx5, i32 0, i32 1, !dbg !1263
  %9 = load i8, i8* %prev_1_is_literal, align 4, !dbg !1263
  %tobool = trunc i8 %9 to i1, !dbg !1263
  br i1 %tobool, label %if.then, label %if.else39, !dbg !1264

if.then:                                          ; preds = %entry
  %10 = load i32, i32* %pos_prev, align 4, !dbg !1265
  %dec = add i32 %10, -1, !dbg !1265
  store i32 %dec, i32* %pos_prev, align 4, !dbg !1265
  %11 = load i32, i32* %cur.addr, align 4, !dbg !1267
  %idxprom6 = zext i32 %11 to i64, !dbg !1269
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1269
  %opts7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 32, !dbg !1270
  %arrayidx8 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts7, i64 0, i64 %idxprom6, !dbg !1269
  %prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx8, i32 0, i32 2, !dbg !1271
  %13 = load i8, i8* %prev_2, align 1, !dbg !1271
  %tobool9 = trunc i8 %13 to i1, !dbg !1271
  br i1 %tobool9, label %if.then10, label %if.else25, !dbg !1272

if.then10:                                        ; preds = %if.then
  %14 = load i32, i32* %cur.addr, align 4, !dbg !1273
  %idxprom11 = zext i32 %14 to i64, !dbg !1275
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1275
  %opts12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 32, !dbg !1276
  %arrayidx13 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts12, i64 0, i64 %idxprom11, !dbg !1275
  %pos_prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx13, i32 0, i32 3, !dbg !1277
  %16 = load i32, i32* %pos_prev_2, align 4, !dbg !1277
  %idxprom14 = zext i32 %16 to i64, !dbg !1278
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1278
  %opts15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 32, !dbg !1279
  %arrayidx16 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts15, i64 0, i64 %idxprom14, !dbg !1278
  %state17 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx16, i32 0, i32 0, !dbg !1280
  %18 = load i32, i32* %state17, align 4, !dbg !1280
  store i32 %18, i32* %state, align 4, !dbg !1281
  %19 = load i32, i32* %cur.addr, align 4, !dbg !1282
  %idxprom18 = zext i32 %19 to i64, !dbg !1284
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1284
  %opts19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 32, !dbg !1285
  %arrayidx20 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts19, i64 0, i64 %idxprom18, !dbg !1284
  %back_prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx20, i32 0, i32 4, !dbg !1286
  %21 = load i32, i32* %back_prev_2, align 4, !dbg !1286
  %cmp = icmp ult i32 %21, 4, !dbg !1287
  br i1 %cmp, label %if.then21, label %if.else, !dbg !1288

if.then21:                                        ; preds = %if.then10
  %22 = load i32, i32* %state, align 4, !dbg !1289
  %cmp22 = icmp ult i32 %22, 7, !dbg !1289
  %cond = select i1 %cmp22, i32 8, i32 11, !dbg !1289
  store i32 %cond, i32* %state, align 4, !dbg !1289
  br label %if.end, !dbg !1289

if.else:                                          ; preds = %if.then10
  %23 = load i32, i32* %state, align 4, !dbg !1290
  %cmp23 = icmp ult i32 %23, 7, !dbg !1290
  %cond24 = select i1 %cmp23, i32 7, i32 10, !dbg !1290
  store i32 %cond24, i32* %state, align 4, !dbg !1290
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then21
  br label %if.end30, !dbg !1291

if.else25:                                        ; preds = %if.then
  %24 = load i32, i32* %pos_prev, align 4, !dbg !1292
  %idxprom26 = zext i32 %24 to i64, !dbg !1294
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1294
  %opts27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 32, !dbg !1295
  %arrayidx28 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts27, i64 0, i64 %idxprom26, !dbg !1294
  %state29 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx28, i32 0, i32 0, !dbg !1296
  %26 = load i32, i32* %state29, align 4, !dbg !1296
  store i32 %26, i32* %state, align 4, !dbg !1297
  br label %if.end30

if.end30:                                         ; preds = %if.else25, %if.end
  %27 = load i32, i32* %state, align 4, !dbg !1298
  %cmp31 = icmp ule i32 %27, 3, !dbg !1298
  br i1 %cmp31, label %cond.true, label %cond.false, !dbg !1298

cond.true:                                        ; preds = %if.end30
  br label %cond.end37, !dbg !1299

cond.false:                                       ; preds = %if.end30
  %28 = load i32, i32* %state, align 4, !dbg !1301
  %cmp32 = icmp ule i32 %28, 9, !dbg !1301
  br i1 %cmp32, label %cond.true33, label %cond.false34, !dbg !1301

cond.true33:                                      ; preds = %cond.false
  %29 = load i32, i32* %state, align 4, !dbg !1303
  %sub = sub i32 %29, 3, !dbg !1303
  br label %cond.end, !dbg !1303

cond.false34:                                     ; preds = %cond.false
  %30 = load i32, i32* %state, align 4, !dbg !1305
  %sub35 = sub i32 %30, 6, !dbg !1305
  br label %cond.end, !dbg !1305

cond.end:                                         ; preds = %cond.false34, %cond.true33
  %cond36 = phi i32 [ %sub, %cond.true33 ], [ %sub35, %cond.false34 ], !dbg !1307
  br label %cond.end37, !dbg !1307

cond.end37:                                       ; preds = %cond.end, %cond.true
  %cond38 = phi i32 [ 0, %cond.true ], [ %cond36, %cond.end ], !dbg !1309
  store i32 %cond38, i32* %state, align 4, !dbg !1309
  br label %if.end44, !dbg !1311

if.else39:                                        ; preds = %entry
  %31 = load i32, i32* %pos_prev, align 4, !dbg !1312
  %idxprom40 = zext i32 %31 to i64, !dbg !1314
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1314
  %opts41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 32, !dbg !1315
  %arrayidx42 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts41, i64 0, i64 %idxprom40, !dbg !1314
  %state43 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx42, i32 0, i32 0, !dbg !1316
  %33 = load i32, i32* %state43, align 4, !dbg !1316
  store i32 %33, i32* %state, align 4, !dbg !1317
  br label %if.end44

if.end44:                                         ; preds = %if.else39, %cond.end37
  %34 = load i32, i32* %pos_prev, align 4, !dbg !1318
  %35 = load i32, i32* %cur.addr, align 4, !dbg !1320
  %sub45 = sub i32 %35, 1, !dbg !1321
  %cmp46 = icmp eq i32 %34, %sub45, !dbg !1322
  br i1 %cmp46, label %if.then47, label %if.else69, !dbg !1323

if.then47:                                        ; preds = %if.end44
  %36 = load i32, i32* %cur.addr, align 4, !dbg !1324
  %idxprom48 = zext i32 %36 to i64, !dbg !1324
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1324
  %opts49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 32, !dbg !1324
  %arrayidx50 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts49, i64 0, i64 %idxprom48, !dbg !1324
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx50, i32 0, i32 7, !dbg !1324
  %38 = load i32, i32* %back_prev, align 4, !dbg !1324
  %cmp51 = icmp eq i32 %38, 0, !dbg !1324
  br i1 %cmp51, label %if.then52, label %if.else55, !dbg !1327

if.then52:                                        ; preds = %if.then47
  %39 = load i32, i32* %state, align 4, !dbg !1328
  %cmp53 = icmp ult i32 %39, 7, !dbg !1328
  %cond54 = select i1 %cmp53, i32 9, i32 11, !dbg !1328
  store i32 %cond54, i32* %state, align 4, !dbg !1328
  br label %if.end68, !dbg !1328

if.else55:                                        ; preds = %if.then47
  %40 = load i32, i32* %state, align 4, !dbg !1329
  %cmp56 = icmp ule i32 %40, 3, !dbg !1329
  br i1 %cmp56, label %cond.true57, label %cond.false58, !dbg !1329

cond.true57:                                      ; preds = %if.else55
  br label %cond.end66, !dbg !1330

cond.false58:                                     ; preds = %if.else55
  %41 = load i32, i32* %state, align 4, !dbg !1332
  %cmp59 = icmp ule i32 %41, 9, !dbg !1332
  br i1 %cmp59, label %cond.true60, label %cond.false62, !dbg !1332

cond.true60:                                      ; preds = %cond.false58
  %42 = load i32, i32* %state, align 4, !dbg !1334
  %sub61 = sub i32 %42, 3, !dbg !1334
  br label %cond.end64, !dbg !1334

cond.false62:                                     ; preds = %cond.false58
  %43 = load i32, i32* %state, align 4, !dbg !1336
  %sub63 = sub i32 %43, 6, !dbg !1336
  br label %cond.end64, !dbg !1336

cond.end64:                                       ; preds = %cond.false62, %cond.true60
  %cond65 = phi i32 [ %sub61, %cond.true60 ], [ %sub63, %cond.false62 ], !dbg !1338
  br label %cond.end66, !dbg !1338

cond.end66:                                       ; preds = %cond.end64, %cond.true57
  %cond67 = phi i32 [ 0, %cond.true57 ], [ %cond65, %cond.end64 ], !dbg !1340
  store i32 %cond67, i32* %state, align 4, !dbg !1340
  br label %if.end68

if.end68:                                         ; preds = %cond.end66, %if.then52
  br label %if.end157, !dbg !1342

if.else69:                                        ; preds = %if.end44
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1343, metadata !305), !dbg !1345
  %44 = load i32, i32* %cur.addr, align 4, !dbg !1346
  %idxprom70 = zext i32 %44 to i64, !dbg !1348
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1348
  %opts71 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 32, !dbg !1349
  %arrayidx72 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts71, i64 0, i64 %idxprom70, !dbg !1348
  %prev_1_is_literal73 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx72, i32 0, i32 1, !dbg !1350
  %46 = load i8, i8* %prev_1_is_literal73, align 4, !dbg !1350
  %tobool74 = trunc i8 %46 to i1, !dbg !1350
  br i1 %tobool74, label %land.lhs.true, label %if.else91, !dbg !1351

land.lhs.true:                                    ; preds = %if.else69
  %47 = load i32, i32* %cur.addr, align 4, !dbg !1352
  %idxprom75 = zext i32 %47 to i64, !dbg !1354
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1354
  %opts76 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 32, !dbg !1355
  %arrayidx77 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts76, i64 0, i64 %idxprom75, !dbg !1354
  %prev_278 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx77, i32 0, i32 2, !dbg !1356
  %49 = load i8, i8* %prev_278, align 1, !dbg !1356
  %tobool79 = trunc i8 %49 to i1, !dbg !1356
  br i1 %tobool79, label %if.then80, label %if.else91, !dbg !1357

if.then80:                                        ; preds = %land.lhs.true
  %50 = load i32, i32* %cur.addr, align 4, !dbg !1359
  %idxprom81 = zext i32 %50 to i64, !dbg !1361
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1361
  %opts82 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 32, !dbg !1362
  %arrayidx83 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts82, i64 0, i64 %idxprom81, !dbg !1361
  %pos_prev_284 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx83, i32 0, i32 3, !dbg !1363
  %52 = load i32, i32* %pos_prev_284, align 4, !dbg !1363
  store i32 %52, i32* %pos_prev, align 4, !dbg !1364
  %53 = load i32, i32* %cur.addr, align 4, !dbg !1365
  %idxprom85 = zext i32 %53 to i64, !dbg !1366
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1366
  %opts86 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 32, !dbg !1367
  %arrayidx87 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts86, i64 0, i64 %idxprom85, !dbg !1366
  %back_prev_288 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx87, i32 0, i32 4, !dbg !1368
  %55 = load i32, i32* %back_prev_288, align 4, !dbg !1368
  store i32 %55, i32* %pos, align 4, !dbg !1369
  %56 = load i32, i32* %state, align 4, !dbg !1370
  %cmp89 = icmp ult i32 %56, 7, !dbg !1370
  %cond90 = select i1 %cmp89, i32 8, i32 11, !dbg !1370
  store i32 %cond90, i32* %state, align 4, !dbg !1370
  br label %if.end104, !dbg !1371

if.else91:                                        ; preds = %land.lhs.true, %if.else69
  %57 = load i32, i32* %cur.addr, align 4, !dbg !1372
  %idxprom92 = zext i32 %57 to i64, !dbg !1374
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1374
  %opts93 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 32, !dbg !1375
  %arrayidx94 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts93, i64 0, i64 %idxprom92, !dbg !1374
  %back_prev95 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx94, i32 0, i32 7, !dbg !1376
  %59 = load i32, i32* %back_prev95, align 4, !dbg !1376
  store i32 %59, i32* %pos, align 4, !dbg !1377
  %60 = load i32, i32* %pos, align 4, !dbg !1378
  %cmp96 = icmp ult i32 %60, 4, !dbg !1380
  br i1 %cmp96, label %if.then97, label %if.else100, !dbg !1381

if.then97:                                        ; preds = %if.else91
  %61 = load i32, i32* %state, align 4, !dbg !1382
  %cmp98 = icmp ult i32 %61, 7, !dbg !1382
  %cond99 = select i1 %cmp98, i32 8, i32 11, !dbg !1382
  store i32 %cond99, i32* %state, align 4, !dbg !1382
  br label %if.end103, !dbg !1382

if.else100:                                       ; preds = %if.else91
  %62 = load i32, i32* %state, align 4, !dbg !1383
  %cmp101 = icmp ult i32 %62, 7, !dbg !1383
  %cond102 = select i1 %cmp101, i32 7, i32 10, !dbg !1383
  store i32 %cond102, i32* %state, align 4, !dbg !1383
  br label %if.end103

if.end103:                                        ; preds = %if.else100, %if.then97
  br label %if.end104

if.end104:                                        ; preds = %if.end103, %if.then80
  %63 = load i32, i32* %pos, align 4, !dbg !1384
  %cmp105 = icmp ult i32 %63, 4, !dbg !1386
  br i1 %cmp105, label %if.then106, label %if.else138, !dbg !1387

if.then106:                                       ; preds = %if.end104
  call void @llvm.dbg.declare(metadata i32* %i107, metadata !1388, metadata !305), !dbg !1390
  %64 = load i32, i32* %pos, align 4, !dbg !1391
  %idxprom108 = zext i32 %64 to i64, !dbg !1392
  %65 = load i32, i32* %pos_prev, align 4, !dbg !1393
  %idxprom109 = zext i32 %65 to i64, !dbg !1392
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1392
  %opts110 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 32, !dbg !1394
  %arrayidx111 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts110, i64 0, i64 %idxprom109, !dbg !1392
  %backs = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx111, i32 0, i32 8, !dbg !1395
  %arrayidx112 = getelementptr inbounds [4 x i32], [4 x i32]* %backs, i64 0, i64 %idxprom108, !dbg !1392
  %67 = load i32, i32* %arrayidx112, align 4, !dbg !1392
  %68 = load i32*, i32** %reps.addr, align 8, !dbg !1396
  %arrayidx113 = getelementptr inbounds i32, i32* %68, i64 0, !dbg !1396
  store i32 %67, i32* %arrayidx113, align 4, !dbg !1397
  store i32 1, i32* %i107, align 4, !dbg !1398
  br label %for.cond, !dbg !1400

for.cond:                                         ; preds = %for.inc, %if.then106
  %69 = load i32, i32* %i107, align 4, !dbg !1401
  %70 = load i32, i32* %pos, align 4, !dbg !1404
  %cmp114 = icmp ule i32 %69, %70, !dbg !1405
  br i1 %cmp114, label %for.body, label %for.end, !dbg !1406

for.body:                                         ; preds = %for.cond
  %71 = load i32, i32* %i107, align 4, !dbg !1407
  %sub115 = sub i32 %71, 1, !dbg !1408
  %idxprom116 = zext i32 %sub115 to i64, !dbg !1409
  %72 = load i32, i32* %pos_prev, align 4, !dbg !1410
  %idxprom117 = zext i32 %72 to i64, !dbg !1409
  %73 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1409
  %opts118 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %73, i32 0, i32 32, !dbg !1411
  %arrayidx119 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts118, i64 0, i64 %idxprom117, !dbg !1409
  %backs120 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx119, i32 0, i32 8, !dbg !1412
  %arrayidx121 = getelementptr inbounds [4 x i32], [4 x i32]* %backs120, i64 0, i64 %idxprom116, !dbg !1409
  %74 = load i32, i32* %arrayidx121, align 4, !dbg !1409
  %75 = load i32, i32* %i107, align 4, !dbg !1413
  %idxprom122 = zext i32 %75 to i64, !dbg !1414
  %76 = load i32*, i32** %reps.addr, align 8, !dbg !1414
  %arrayidx123 = getelementptr inbounds i32, i32* %76, i64 %idxprom122, !dbg !1414
  store i32 %74, i32* %arrayidx123, align 4, !dbg !1415
  br label %for.inc, !dbg !1414

for.inc:                                          ; preds = %for.body
  %77 = load i32, i32* %i107, align 4, !dbg !1416
  %inc = add i32 %77, 1, !dbg !1416
  store i32 %inc, i32* %i107, align 4, !dbg !1416
  br label %for.cond, !dbg !1418

for.end:                                          ; preds = %for.cond
  br label %for.cond124, !dbg !1419

for.cond124:                                      ; preds = %for.inc135, %for.end
  %78 = load i32, i32* %i107, align 4, !dbg !1420
  %cmp125 = icmp ult i32 %78, 4, !dbg !1424
  br i1 %cmp125, label %for.body126, label %for.end137, !dbg !1425

for.body126:                                      ; preds = %for.cond124
  %79 = load i32, i32* %i107, align 4, !dbg !1426
  %idxprom127 = zext i32 %79 to i64, !dbg !1427
  %80 = load i32, i32* %pos_prev, align 4, !dbg !1428
  %idxprom128 = zext i32 %80 to i64, !dbg !1427
  %81 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1427
  %opts129 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %81, i32 0, i32 32, !dbg !1429
  %arrayidx130 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts129, i64 0, i64 %idxprom128, !dbg !1427
  %backs131 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx130, i32 0, i32 8, !dbg !1430
  %arrayidx132 = getelementptr inbounds [4 x i32], [4 x i32]* %backs131, i64 0, i64 %idxprom127, !dbg !1427
  %82 = load i32, i32* %arrayidx132, align 4, !dbg !1427
  %83 = load i32, i32* %i107, align 4, !dbg !1431
  %idxprom133 = zext i32 %83 to i64, !dbg !1432
  %84 = load i32*, i32** %reps.addr, align 8, !dbg !1432
  %arrayidx134 = getelementptr inbounds i32, i32* %84, i64 %idxprom133, !dbg !1432
  store i32 %82, i32* %arrayidx134, align 4, !dbg !1433
  br label %for.inc135, !dbg !1432

for.inc135:                                       ; preds = %for.body126
  %85 = load i32, i32* %i107, align 4, !dbg !1434
  %inc136 = add i32 %85, 1, !dbg !1434
  store i32 %inc136, i32* %i107, align 4, !dbg !1434
  br label %for.cond124, !dbg !1436

for.end137:                                       ; preds = %for.cond124
  br label %if.end156, !dbg !1437

if.else138:                                       ; preds = %if.end104
  %86 = load i32, i32* %pos, align 4, !dbg !1438
  %sub139 = sub i32 %86, 4, !dbg !1440
  %87 = load i32*, i32** %reps.addr, align 8, !dbg !1441
  %arrayidx140 = getelementptr inbounds i32, i32* %87, i64 0, !dbg !1441
  store i32 %sub139, i32* %arrayidx140, align 4, !dbg !1442
  store i32 1, i32* %i, align 4, !dbg !1443
  br label %for.cond141, !dbg !1445

for.cond141:                                      ; preds = %for.inc153, %if.else138
  %88 = load i32, i32* %i, align 4, !dbg !1446
  %cmp142 = icmp ult i32 %88, 4, !dbg !1449
  br i1 %cmp142, label %for.body143, label %for.end155, !dbg !1450

for.body143:                                      ; preds = %for.cond141
  %89 = load i32, i32* %i, align 4, !dbg !1451
  %sub144 = sub i32 %89, 1, !dbg !1452
  %idxprom145 = zext i32 %sub144 to i64, !dbg !1453
  %90 = load i32, i32* %pos_prev, align 4, !dbg !1454
  %idxprom146 = zext i32 %90 to i64, !dbg !1453
  %91 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1453
  %opts147 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %91, i32 0, i32 32, !dbg !1455
  %arrayidx148 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts147, i64 0, i64 %idxprom146, !dbg !1453
  %backs149 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx148, i32 0, i32 8, !dbg !1456
  %arrayidx150 = getelementptr inbounds [4 x i32], [4 x i32]* %backs149, i64 0, i64 %idxprom145, !dbg !1453
  %92 = load i32, i32* %arrayidx150, align 4, !dbg !1453
  %93 = load i32, i32* %i, align 4, !dbg !1457
  %idxprom151 = zext i32 %93 to i64, !dbg !1458
  %94 = load i32*, i32** %reps.addr, align 8, !dbg !1458
  %arrayidx152 = getelementptr inbounds i32, i32* %94, i64 %idxprom151, !dbg !1458
  store i32 %92, i32* %arrayidx152, align 4, !dbg !1459
  br label %for.inc153, !dbg !1458

for.inc153:                                       ; preds = %for.body143
  %95 = load i32, i32* %i, align 4, !dbg !1460
  %inc154 = add i32 %95, 1, !dbg !1460
  store i32 %inc154, i32* %i, align 4, !dbg !1460
  br label %for.cond141, !dbg !1462

for.end155:                                       ; preds = %for.cond141
  br label %if.end156

if.end156:                                        ; preds = %for.end155, %for.end137
  br label %if.end157

if.end157:                                        ; preds = %if.end156, %if.end68
  %96 = load i32, i32* %state, align 4, !dbg !1463
  %97 = load i32, i32* %cur.addr, align 4, !dbg !1464
  %idxprom158 = zext i32 %97 to i64, !dbg !1465
  %98 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1465
  %opts159 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %98, i32 0, i32 32, !dbg !1466
  %arrayidx160 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts159, i64 0, i64 %idxprom158, !dbg !1465
  %state161 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx160, i32 0, i32 0, !dbg !1467
  store i32 %96, i32* %state161, align 4, !dbg !1468
  store i32 0, i32* %i, align 4, !dbg !1469
  br label %for.cond162, !dbg !1471

for.cond162:                                      ; preds = %for.inc173, %if.end157
  %99 = load i32, i32* %i, align 4, !dbg !1472
  %cmp163 = icmp ult i32 %99, 4, !dbg !1475
  br i1 %cmp163, label %for.body164, label %for.end175, !dbg !1476

for.body164:                                      ; preds = %for.cond162
  %100 = load i32, i32* %i, align 4, !dbg !1477
  %idxprom165 = zext i32 %100 to i64, !dbg !1478
  %101 = load i32*, i32** %reps.addr, align 8, !dbg !1478
  %arrayidx166 = getelementptr inbounds i32, i32* %101, i64 %idxprom165, !dbg !1478
  %102 = load i32, i32* %arrayidx166, align 4, !dbg !1478
  %103 = load i32, i32* %i, align 4, !dbg !1479
  %idxprom167 = zext i32 %103 to i64, !dbg !1480
  %104 = load i32, i32* %cur.addr, align 4, !dbg !1481
  %idxprom168 = zext i32 %104 to i64, !dbg !1480
  %105 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1480
  %opts169 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %105, i32 0, i32 32, !dbg !1482
  %arrayidx170 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts169, i64 0, i64 %idxprom168, !dbg !1480
  %backs171 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx170, i32 0, i32 8, !dbg !1483
  %arrayidx172 = getelementptr inbounds [4 x i32], [4 x i32]* %backs171, i64 0, i64 %idxprom167, !dbg !1480
  store i32 %102, i32* %arrayidx172, align 4, !dbg !1484
  br label %for.inc173, !dbg !1480

for.inc173:                                       ; preds = %for.body164
  %106 = load i32, i32* %i, align 4, !dbg !1485
  %inc174 = add i32 %106, 1, !dbg !1485
  store i32 %inc174, i32* %i, align 4, !dbg !1485
  br label %for.cond162, !dbg !1487

for.end175:                                       ; preds = %for.cond162
  %107 = load i32, i32* %cur.addr, align 4, !dbg !1488
  %idxprom176 = zext i32 %107 to i64, !dbg !1489
  %108 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1489
  %opts177 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %108, i32 0, i32 32, !dbg !1490
  %arrayidx178 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts177, i64 0, i64 %idxprom176, !dbg !1489
  %price = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx178, i32 0, i32 5, !dbg !1491
  %109 = load i32, i32* %price, align 4, !dbg !1491
  store i32 %109, i32* %cur_price, align 4, !dbg !1492
  %110 = load i8*, i8** %buf.addr, align 8, !dbg !1493
  %111 = load i8, i8* %110, align 1, !dbg !1494
  store i8 %111, i8* %current_byte, align 1, !dbg !1495
  %112 = load i8*, i8** %buf.addr, align 8, !dbg !1496
  %113 = load i32*, i32** %reps.addr, align 8, !dbg !1497
  %arrayidx179 = getelementptr inbounds i32, i32* %113, i64 0, !dbg !1497
  %114 = load i32, i32* %arrayidx179, align 4, !dbg !1497
  %idx.ext = zext i32 %114 to i64, !dbg !1498
  %idx.neg = sub i64 0, %idx.ext, !dbg !1498
  %add.ptr = getelementptr inbounds i8, i8* %112, i64 %idx.neg, !dbg !1498
  %add.ptr180 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !1499
  %115 = load i8, i8* %add.ptr180, align 1, !dbg !1500
  store i8 %115, i8* %match_byte, align 1, !dbg !1501
  %116 = load i32, i32* %position.addr, align 4, !dbg !1502
  %117 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1503
  %pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %117, i32 0, i32 9, !dbg !1504
  %118 = load i32, i32* %pos_mask, align 8, !dbg !1504
  %and = and i32 %116, %118, !dbg !1505
  store i32 %and, i32* %pos_state, align 4, !dbg !1506
  %119 = load i32, i32* %cur_price, align 4, !dbg !1507
  %120 = load i32, i32* %pos_state, align 4, !dbg !1508
  %idxprom181 = zext i32 %120 to i64, !dbg !1509
  %121 = load i32, i32* %state, align 4, !dbg !1510
  %idxprom182 = zext i32 %121 to i64, !dbg !1509
  %122 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1509
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %122, i32 0, i32 13, !dbg !1511
  %arrayidx183 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 %idxprom182, !dbg !1509
  %arrayidx184 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx183, i64 0, i64 %idxprom181, !dbg !1509
  %123 = load i16, i16* %arrayidx184, align 2, !dbg !1509
  %call = call i32 @rc_bit_0_price(i16 zeroext %123), !dbg !1512
  %add = add i32 %119, %call, !dbg !1513
  %124 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1514
  %125 = load i32, i32* %position.addr, align 4, !dbg !1515
  %126 = load i8*, i8** %buf.addr, align 8, !dbg !1516
  %arrayidx185 = getelementptr inbounds i8, i8* %126, i64 -1, !dbg !1516
  %127 = load i8, i8* %arrayidx185, align 1, !dbg !1516
  %conv = zext i8 %127 to i32, !dbg !1516
  %128 = load i32, i32* %state, align 4, !dbg !1517
  %cmp186 = icmp ult i32 %128, 7, !dbg !1517
  %lnot = xor i1 %cmp186, true, !dbg !1518
  %129 = load i8, i8* %match_byte, align 1, !dbg !1519
  %conv188 = zext i8 %129 to i32, !dbg !1519
  %130 = load i8, i8* %current_byte, align 1, !dbg !1520
  %conv189 = zext i8 %130 to i32, !dbg !1520
  %call190 = call i32 @get_literal_price(%struct.lzma_coder_s* %124, i32 %125, i32 %conv, i1 zeroext %lnot, i32 %conv188, i32 %conv189), !dbg !1521
  %add191 = add i32 %add, %call190, !dbg !1522
  store i32 %add191, i32* %cur_and_1_price, align 4, !dbg !1523
  %131 = load i32, i32* %cur_and_1_price, align 4, !dbg !1524
  %132 = load i32, i32* %cur.addr, align 4, !dbg !1526
  %add192 = add i32 %132, 1, !dbg !1527
  %idxprom193 = zext i32 %add192 to i64, !dbg !1528
  %133 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1528
  %opts194 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %133, i32 0, i32 32, !dbg !1529
  %arrayidx195 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts194, i64 0, i64 %idxprom193, !dbg !1528
  %price196 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx195, i32 0, i32 5, !dbg !1530
  %134 = load i32, i32* %price196, align 4, !dbg !1530
  %cmp197 = icmp ult i32 %131, %134, !dbg !1531
  br i1 %cmp197, label %if.then199, label %if.end214, !dbg !1532

if.then199:                                       ; preds = %for.end175
  %135 = load i32, i32* %cur_and_1_price, align 4, !dbg !1533
  %136 = load i32, i32* %cur.addr, align 4, !dbg !1535
  %add200 = add i32 %136, 1, !dbg !1536
  %idxprom201 = zext i32 %add200 to i64, !dbg !1537
  %137 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1537
  %opts202 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %137, i32 0, i32 32, !dbg !1538
  %arrayidx203 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts202, i64 0, i64 %idxprom201, !dbg !1537
  %price204 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx203, i32 0, i32 5, !dbg !1539
  store i32 %135, i32* %price204, align 4, !dbg !1540
  %138 = load i32, i32* %cur.addr, align 4, !dbg !1541
  %139 = load i32, i32* %cur.addr, align 4, !dbg !1542
  %add205 = add i32 %139, 1, !dbg !1543
  %idxprom206 = zext i32 %add205 to i64, !dbg !1544
  %140 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1544
  %opts207 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %140, i32 0, i32 32, !dbg !1545
  %arrayidx208 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts207, i64 0, i64 %idxprom206, !dbg !1544
  %pos_prev209 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx208, i32 0, i32 6, !dbg !1546
  store i32 %138, i32* %pos_prev209, align 4, !dbg !1547
  %141 = load i32, i32* %cur.addr, align 4, !dbg !1548
  %add210 = add i32 %141, 1, !dbg !1549
  %idxprom211 = zext i32 %add210 to i64, !dbg !1550
  %142 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1550
  %opts212 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %142, i32 0, i32 32, !dbg !1551
  %arrayidx213 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts212, i64 0, i64 %idxprom211, !dbg !1550
  call void @make_literal(%struct.lzma_optimal* %arrayidx213), !dbg !1552
  store i8 1, i8* %next_is_literal, align 1, !dbg !1553
  br label %if.end214, !dbg !1554

if.end214:                                        ; preds = %if.then199, %for.end175
  %143 = load i32, i32* %cur_price, align 4, !dbg !1555
  %144 = load i32, i32* %pos_state, align 4, !dbg !1556
  %idxprom215 = zext i32 %144 to i64, !dbg !1557
  %145 = load i32, i32* %state, align 4, !dbg !1558
  %idxprom216 = zext i32 %145 to i64, !dbg !1557
  %146 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1557
  %is_match217 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %146, i32 0, i32 13, !dbg !1559
  %arrayidx218 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match217, i64 0, i64 %idxprom216, !dbg !1557
  %arrayidx219 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx218, i64 0, i64 %idxprom215, !dbg !1557
  %147 = load i16, i16* %arrayidx219, align 2, !dbg !1557
  %call220 = call i32 @rc_bit_1_price(i16 zeroext %147), !dbg !1560
  %add221 = add i32 %143, %call220, !dbg !1561
  store i32 %add221, i32* %match_price, align 4, !dbg !1562
  %148 = load i32, i32* %match_price, align 4, !dbg !1563
  %149 = load i32, i32* %state, align 4, !dbg !1564
  %idxprom222 = zext i32 %149 to i64, !dbg !1565
  %150 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1565
  %is_rep = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %150, i32 0, i32 14, !dbg !1566
  %arrayidx223 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep, i64 0, i64 %idxprom222, !dbg !1565
  %151 = load i16, i16* %arrayidx223, align 2, !dbg !1565
  %call224 = call i32 @rc_bit_1_price(i16 zeroext %151), !dbg !1567
  %add225 = add i32 %148, %call224, !dbg !1568
  store i32 %add225, i32* %rep_match_price, align 4, !dbg !1569
  %152 = load i8, i8* %match_byte, align 1, !dbg !1570
  %conv226 = zext i8 %152 to i32, !dbg !1570
  %153 = load i8, i8* %current_byte, align 1, !dbg !1572
  %conv227 = zext i8 %153 to i32, !dbg !1572
  %cmp228 = icmp eq i32 %conv226, %conv227, !dbg !1573
  br i1 %cmp228, label %land.lhs.true230, label %if.end272, !dbg !1574

land.lhs.true230:                                 ; preds = %if.end214
  %154 = load i32, i32* %cur.addr, align 4, !dbg !1575
  %add231 = add i32 %154, 1, !dbg !1577
  %idxprom232 = zext i32 %add231 to i64, !dbg !1578
  %155 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1578
  %opts233 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %155, i32 0, i32 32, !dbg !1579
  %arrayidx234 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts233, i64 0, i64 %idxprom232, !dbg !1578
  %pos_prev235 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx234, i32 0, i32 6, !dbg !1580
  %156 = load i32, i32* %pos_prev235, align 4, !dbg !1580
  %157 = load i32, i32* %cur.addr, align 4, !dbg !1581
  %cmp236 = icmp ult i32 %156, %157, !dbg !1582
  br i1 %cmp236, label %land.lhs.true238, label %if.then246, !dbg !1583

land.lhs.true238:                                 ; preds = %land.lhs.true230
  %158 = load i32, i32* %cur.addr, align 4, !dbg !1584
  %add239 = add i32 %158, 1, !dbg !1585
  %idxprom240 = zext i32 %add239 to i64, !dbg !1586
  %159 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1586
  %opts241 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %159, i32 0, i32 32, !dbg !1587
  %arrayidx242 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts241, i64 0, i64 %idxprom240, !dbg !1586
  %back_prev243 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx242, i32 0, i32 7, !dbg !1588
  %160 = load i32, i32* %back_prev243, align 4, !dbg !1588
  %cmp244 = icmp eq i32 %160, 0, !dbg !1589
  br i1 %cmp244, label %if.end272, label %if.then246, !dbg !1590

if.then246:                                       ; preds = %land.lhs.true238, %land.lhs.true230
  call void @llvm.dbg.declare(metadata i32* %short_rep_price, metadata !1592, metadata !305), !dbg !1594
  %161 = load i32, i32* %rep_match_price, align 4, !dbg !1595
  %162 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1596
  %163 = load i32, i32* %state, align 4, !dbg !1597
  %164 = load i32, i32* %pos_state, align 4, !dbg !1598
  %call247 = call i32 @get_short_rep_price(%struct.lzma_coder_s* %162, i32 %163, i32 %164), !dbg !1599
  %add248 = add i32 %161, %call247, !dbg !1600
  store i32 %add248, i32* %short_rep_price, align 4, !dbg !1594
  %165 = load i32, i32* %short_rep_price, align 4, !dbg !1601
  %166 = load i32, i32* %cur.addr, align 4, !dbg !1603
  %add249 = add i32 %166, 1, !dbg !1604
  %idxprom250 = zext i32 %add249 to i64, !dbg !1605
  %167 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1605
  %opts251 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %167, i32 0, i32 32, !dbg !1606
  %arrayidx252 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts251, i64 0, i64 %idxprom250, !dbg !1605
  %price253 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx252, i32 0, i32 5, !dbg !1607
  %168 = load i32, i32* %price253, align 4, !dbg !1607
  %cmp254 = icmp ule i32 %165, %168, !dbg !1608
  br i1 %cmp254, label %if.then256, label %if.end271, !dbg !1609

if.then256:                                       ; preds = %if.then246
  %169 = load i32, i32* %short_rep_price, align 4, !dbg !1610
  %170 = load i32, i32* %cur.addr, align 4, !dbg !1612
  %add257 = add i32 %170, 1, !dbg !1613
  %idxprom258 = zext i32 %add257 to i64, !dbg !1614
  %171 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1614
  %opts259 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %171, i32 0, i32 32, !dbg !1615
  %arrayidx260 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts259, i64 0, i64 %idxprom258, !dbg !1614
  %price261 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx260, i32 0, i32 5, !dbg !1616
  store i32 %169, i32* %price261, align 4, !dbg !1617
  %172 = load i32, i32* %cur.addr, align 4, !dbg !1618
  %173 = load i32, i32* %cur.addr, align 4, !dbg !1619
  %add262 = add i32 %173, 1, !dbg !1620
  %idxprom263 = zext i32 %add262 to i64, !dbg !1621
  %174 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1621
  %opts264 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %174, i32 0, i32 32, !dbg !1622
  %arrayidx265 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts264, i64 0, i64 %idxprom263, !dbg !1621
  %pos_prev266 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx265, i32 0, i32 6, !dbg !1623
  store i32 %172, i32* %pos_prev266, align 4, !dbg !1624
  %175 = load i32, i32* %cur.addr, align 4, !dbg !1625
  %add267 = add i32 %175, 1, !dbg !1626
  %idxprom268 = zext i32 %add267 to i64, !dbg !1627
  %176 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1627
  %opts269 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %176, i32 0, i32 32, !dbg !1628
  %arrayidx270 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts269, i64 0, i64 %idxprom268, !dbg !1627
  call void @make_short_rep(%struct.lzma_optimal* %arrayidx270), !dbg !1629
  store i8 1, i8* %next_is_literal, align 1, !dbg !1630
  br label %if.end271, !dbg !1631

if.end271:                                        ; preds = %if.then256, %if.then246
  br label %if.end272, !dbg !1632

if.end272:                                        ; preds = %if.end271, %land.lhs.true238, %if.end214
  %177 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1633
  %cmp273 = icmp ult i32 %177, 2, !dbg !1635
  br i1 %cmp273, label %if.then275, label %if.end276, !dbg !1636

if.then275:                                       ; preds = %if.end272
  %178 = load i32, i32* %len_end.addr, align 4, !dbg !1637
  store i32 %178, i32* %retval, align 4, !dbg !1638
  br label %return, !dbg !1638

if.end276:                                        ; preds = %if.end272
  %179 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1639
  %180 = load i32, i32* %nice_len.addr, align 4, !dbg !1639
  %cmp277 = icmp ult i32 %179, %180, !dbg !1639
  br i1 %cmp277, label %cond.true279, label %cond.false280, !dbg !1639

cond.true279:                                     ; preds = %if.end276
  %181 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1640
  br label %cond.end281, !dbg !1640

cond.false280:                                    ; preds = %if.end276
  %182 = load i32, i32* %nice_len.addr, align 4, !dbg !1641
  br label %cond.end281, !dbg !1641

cond.end281:                                      ; preds = %cond.false280, %cond.true279
  %cond282 = phi i32 [ %181, %cond.true279 ], [ %182, %cond.false280 ], !dbg !1643
  store i32 %cond282, i32* %buf_avail, align 4, !dbg !1645
  %183 = load i8, i8* %next_is_literal, align 1, !dbg !1646
  %tobool283 = trunc i8 %183 to i1, !dbg !1646
  br i1 %tobool283, label %if.end391, label %land.lhs.true284, !dbg !1648

land.lhs.true284:                                 ; preds = %cond.end281
  %184 = load i8, i8* %match_byte, align 1, !dbg !1649
  %conv285 = zext i8 %184 to i32, !dbg !1649
  %185 = load i8, i8* %current_byte, align 1, !dbg !1651
  %conv286 = zext i8 %185 to i32, !dbg !1651
  %cmp287 = icmp ne i32 %conv285, %conv286, !dbg !1652
  br i1 %cmp287, label %if.then289, label %if.end391, !dbg !1653

if.then289:                                       ; preds = %land.lhs.true284
  call void @llvm.dbg.declare(metadata i8** %buf_back, metadata !1654, metadata !305), !dbg !1656
  %186 = load i8*, i8** %buf.addr, align 8, !dbg !1657
  %187 = load i32*, i32** %reps.addr, align 8, !dbg !1658
  %arrayidx290 = getelementptr inbounds i32, i32* %187, i64 0, !dbg !1658
  %188 = load i32, i32* %arrayidx290, align 4, !dbg !1658
  %idx.ext291 = zext i32 %188 to i64, !dbg !1659
  %idx.neg292 = sub i64 0, %idx.ext291, !dbg !1659
  %add.ptr293 = getelementptr inbounds i8, i8* %186, i64 %idx.neg292, !dbg !1659
  %add.ptr294 = getelementptr inbounds i8, i8* %add.ptr293, i64 -1, !dbg !1660
  store i8* %add.ptr294, i8** %buf_back, align 8, !dbg !1656
  call void @llvm.dbg.declare(metadata i32* %limit, metadata !1661, metadata !305), !dbg !1662
  %189 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1663
  %190 = load i32, i32* %nice_len.addr, align 4, !dbg !1663
  %add295 = add i32 %190, 1, !dbg !1663
  %cmp296 = icmp ult i32 %189, %add295, !dbg !1663
  br i1 %cmp296, label %cond.true298, label %cond.false299, !dbg !1663

cond.true298:                                     ; preds = %if.then289
  %191 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1664
  br label %cond.end301, !dbg !1664

cond.false299:                                    ; preds = %if.then289
  %192 = load i32, i32* %nice_len.addr, align 4, !dbg !1666
  %add300 = add i32 %192, 1, !dbg !1666
  br label %cond.end301, !dbg !1666

cond.end301:                                      ; preds = %cond.false299, %cond.true298
  %cond302 = phi i32 [ %191, %cond.true298 ], [ %add300, %cond.false299 ], !dbg !1668
  store i32 %cond302, i32* %limit, align 4, !dbg !1670
  call void @llvm.dbg.declare(metadata i32* %len_test, metadata !1671, metadata !305), !dbg !1672
  store i32 1, i32* %len_test, align 4, !dbg !1672
  br label %while.cond, !dbg !1673

while.cond:                                       ; preds = %while.body, %cond.end301
  %193 = load i32, i32* %len_test, align 4, !dbg !1674
  %194 = load i32, i32* %limit, align 4, !dbg !1675
  %cmp303 = icmp ult i32 %193, %194, !dbg !1676
  br i1 %cmp303, label %land.rhs, label %land.end, !dbg !1677

land.rhs:                                         ; preds = %while.cond
  %195 = load i32, i32* %len_test, align 4, !dbg !1678
  %idxprom305 = zext i32 %195 to i64, !dbg !1679
  %196 = load i8*, i8** %buf.addr, align 8, !dbg !1679
  %arrayidx306 = getelementptr inbounds i8, i8* %196, i64 %idxprom305, !dbg !1679
  %197 = load i8, i8* %arrayidx306, align 1, !dbg !1679
  %conv307 = zext i8 %197 to i32, !dbg !1679
  %198 = load i32, i32* %len_test, align 4, !dbg !1680
  %idxprom308 = zext i32 %198 to i64, !dbg !1681
  %199 = load i8*, i8** %buf_back, align 8, !dbg !1681
  %arrayidx309 = getelementptr inbounds i8, i8* %199, i64 %idxprom308, !dbg !1681
  %200 = load i8, i8* %arrayidx309, align 1, !dbg !1681
  %conv310 = zext i8 %200 to i32, !dbg !1681
  %cmp311 = icmp eq i32 %conv307, %conv310, !dbg !1682
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %201 = phi i1 [ false, %while.cond ], [ %cmp311, %land.rhs ]
  br i1 %201, label %while.body, label %while.end, !dbg !1683

while.body:                                       ; preds = %land.end
  %202 = load i32, i32* %len_test, align 4, !dbg !1684
  %inc313 = add i32 %202, 1, !dbg !1684
  store i32 %inc313, i32* %len_test, align 4, !dbg !1684
  br label %while.cond, !dbg !1685

while.end:                                        ; preds = %land.end
  %203 = load i32, i32* %len_test, align 4, !dbg !1687
  %dec314 = add i32 %203, -1, !dbg !1687
  store i32 %dec314, i32* %len_test, align 4, !dbg !1687
  %204 = load i32, i32* %len_test, align 4, !dbg !1688
  %cmp315 = icmp uge i32 %204, 2, !dbg !1690
  br i1 %cmp315, label %if.then317, label %if.end390, !dbg !1691

if.then317:                                       ; preds = %while.end
  call void @llvm.dbg.declare(metadata i32* %pos_state_next, metadata !1692, metadata !305), !dbg !1694
  call void @llvm.dbg.declare(metadata i32* %next_rep_match_price, metadata !1695, metadata !305), !dbg !1696
  call void @llvm.dbg.declare(metadata i32* %offset, metadata !1697, metadata !305), !dbg !1698
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price, metadata !1699, metadata !305), !dbg !1700
  call void @llvm.dbg.declare(metadata i32* %state_2, metadata !1701, metadata !305), !dbg !1702
  %205 = load i32, i32* %state, align 4, !dbg !1703
  store i32 %205, i32* %state_2, align 4, !dbg !1702
  %206 = load i32, i32* %state_2, align 4, !dbg !1704
  %cmp318 = icmp ule i32 %206, 3, !dbg !1704
  br i1 %cmp318, label %cond.true320, label %cond.false321, !dbg !1704

cond.true320:                                     ; preds = %if.then317
  br label %cond.end330, !dbg !1705

cond.false321:                                    ; preds = %if.then317
  %207 = load i32, i32* %state_2, align 4, !dbg !1707
  %cmp322 = icmp ule i32 %207, 9, !dbg !1707
  br i1 %cmp322, label %cond.true324, label %cond.false326, !dbg !1707

cond.true324:                                     ; preds = %cond.false321
  %208 = load i32, i32* %state_2, align 4, !dbg !1709
  %sub325 = sub i32 %208, 3, !dbg !1709
  br label %cond.end328, !dbg !1709

cond.false326:                                    ; preds = %cond.false321
  %209 = load i32, i32* %state_2, align 4, !dbg !1711
  %sub327 = sub i32 %209, 6, !dbg !1711
  br label %cond.end328, !dbg !1711

cond.end328:                                      ; preds = %cond.false326, %cond.true324
  %cond329 = phi i32 [ %sub325, %cond.true324 ], [ %sub327, %cond.false326 ], !dbg !1713
  br label %cond.end330, !dbg !1713

cond.end330:                                      ; preds = %cond.end328, %cond.true320
  %cond331 = phi i32 [ 0, %cond.true320 ], [ %cond329, %cond.end328 ], !dbg !1715
  store i32 %cond331, i32* %state_2, align 4, !dbg !1715
  %210 = load i32, i32* %position.addr, align 4, !dbg !1717
  %add332 = add i32 %210, 1, !dbg !1718
  %211 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1719
  %pos_mask333 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %211, i32 0, i32 9, !dbg !1720
  %212 = load i32, i32* %pos_mask333, align 8, !dbg !1720
  %and334 = and i32 %add332, %212, !dbg !1721
  store i32 %and334, i32* %pos_state_next, align 4, !dbg !1722
  %213 = load i32, i32* %cur_and_1_price, align 4, !dbg !1723
  %214 = load i32, i32* %pos_state_next, align 4, !dbg !1724
  %idxprom335 = zext i32 %214 to i64, !dbg !1725
  %215 = load i32, i32* %state_2, align 4, !dbg !1726
  %idxprom336 = zext i32 %215 to i64, !dbg !1725
  %216 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1725
  %is_match337 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %216, i32 0, i32 13, !dbg !1727
  %arrayidx338 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match337, i64 0, i64 %idxprom336, !dbg !1725
  %arrayidx339 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx338, i64 0, i64 %idxprom335, !dbg !1725
  %217 = load i16, i16* %arrayidx339, align 2, !dbg !1725
  %call340 = call i32 @rc_bit_1_price(i16 zeroext %217), !dbg !1728
  %add341 = add i32 %213, %call340, !dbg !1729
  %218 = load i32, i32* %state_2, align 4, !dbg !1730
  %idxprom342 = zext i32 %218 to i64, !dbg !1731
  %219 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1731
  %is_rep343 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %219, i32 0, i32 14, !dbg !1732
  %arrayidx344 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep343, i64 0, i64 %idxprom342, !dbg !1731
  %220 = load i16, i16* %arrayidx344, align 2, !dbg !1731
  %call345 = call i32 @rc_bit_1_price(i16 zeroext %220), !dbg !1733
  %add346 = add i32 %add341, %call345, !dbg !1734
  store i32 %add346, i32* %next_rep_match_price, align 4, !dbg !1735
  %221 = load i32, i32* %cur.addr, align 4, !dbg !1736
  %add347 = add i32 %221, 1, !dbg !1737
  %222 = load i32, i32* %len_test, align 4, !dbg !1738
  %add348 = add i32 %add347, %222, !dbg !1739
  store i32 %add348, i32* %offset, align 4, !dbg !1740
  br label %while.cond349, !dbg !1741

while.cond349:                                    ; preds = %while.body352, %cond.end330
  %223 = load i32, i32* %len_end.addr, align 4, !dbg !1742
  %224 = load i32, i32* %offset, align 4, !dbg !1743
  %cmp350 = icmp ult i32 %223, %224, !dbg !1744
  br i1 %cmp350, label %while.body352, label %while.end358, !dbg !1745

while.body352:                                    ; preds = %while.cond349
  %225 = load i32, i32* %len_end.addr, align 4, !dbg !1746
  %inc353 = add i32 %225, 1, !dbg !1746
  store i32 %inc353, i32* %len_end.addr, align 4, !dbg !1746
  %idxprom354 = zext i32 %inc353 to i64, !dbg !1747
  %226 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1747
  %opts355 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %226, i32 0, i32 32, !dbg !1748
  %arrayidx356 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts355, i64 0, i64 %idxprom354, !dbg !1747
  %price357 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx356, i32 0, i32 5, !dbg !1749
  store i32 1073741824, i32* %price357, align 4, !dbg !1750
  br label %while.cond349, !dbg !1751

while.end358:                                     ; preds = %while.cond349
  %227 = load i32, i32* %next_rep_match_price, align 4, !dbg !1752
  %228 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1753
  %229 = load i32, i32* %len_test, align 4, !dbg !1754
  %230 = load i32, i32* %state_2, align 4, !dbg !1755
  %231 = load i32, i32* %pos_state_next, align 4, !dbg !1756
  %call359 = call i32 @get_rep_price(%struct.lzma_coder_s* %228, i32 0, i32 %229, i32 %230, i32 %231), !dbg !1757
  %add360 = add i32 %227, %call359, !dbg !1758
  store i32 %add360, i32* %cur_and_len_price, align 4, !dbg !1759
  %232 = load i32, i32* %cur_and_len_price, align 4, !dbg !1760
  %233 = load i32, i32* %offset, align 4, !dbg !1762
  %idxprom361 = zext i32 %233 to i64, !dbg !1763
  %234 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1763
  %opts362 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %234, i32 0, i32 32, !dbg !1764
  %arrayidx363 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts362, i64 0, i64 %idxprom361, !dbg !1763
  %price364 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx363, i32 0, i32 5, !dbg !1765
  %235 = load i32, i32* %price364, align 4, !dbg !1765
  %cmp365 = icmp ult i32 %232, %235, !dbg !1766
  br i1 %cmp365, label %if.then367, label %if.end389, !dbg !1767

if.then367:                                       ; preds = %while.end358
  %236 = load i32, i32* %cur_and_len_price, align 4, !dbg !1768
  %237 = load i32, i32* %offset, align 4, !dbg !1770
  %idxprom368 = zext i32 %237 to i64, !dbg !1771
  %238 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1771
  %opts369 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %238, i32 0, i32 32, !dbg !1772
  %arrayidx370 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts369, i64 0, i64 %idxprom368, !dbg !1771
  %price371 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx370, i32 0, i32 5, !dbg !1773
  store i32 %236, i32* %price371, align 4, !dbg !1774
  %239 = load i32, i32* %cur.addr, align 4, !dbg !1775
  %add372 = add i32 %239, 1, !dbg !1776
  %240 = load i32, i32* %offset, align 4, !dbg !1777
  %idxprom373 = zext i32 %240 to i64, !dbg !1778
  %241 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1778
  %opts374 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %241, i32 0, i32 32, !dbg !1779
  %arrayidx375 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts374, i64 0, i64 %idxprom373, !dbg !1778
  %pos_prev376 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx375, i32 0, i32 6, !dbg !1780
  store i32 %add372, i32* %pos_prev376, align 4, !dbg !1781
  %242 = load i32, i32* %offset, align 4, !dbg !1782
  %idxprom377 = zext i32 %242 to i64, !dbg !1783
  %243 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1783
  %opts378 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %243, i32 0, i32 32, !dbg !1784
  %arrayidx379 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts378, i64 0, i64 %idxprom377, !dbg !1783
  %back_prev380 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx379, i32 0, i32 7, !dbg !1785
  store i32 0, i32* %back_prev380, align 4, !dbg !1786
  %244 = load i32, i32* %offset, align 4, !dbg !1787
  %idxprom381 = zext i32 %244 to i64, !dbg !1788
  %245 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1788
  %opts382 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %245, i32 0, i32 32, !dbg !1789
  %arrayidx383 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts382, i64 0, i64 %idxprom381, !dbg !1788
  %prev_1_is_literal384 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx383, i32 0, i32 1, !dbg !1790
  store i8 1, i8* %prev_1_is_literal384, align 4, !dbg !1791
  %246 = load i32, i32* %offset, align 4, !dbg !1792
  %idxprom385 = zext i32 %246 to i64, !dbg !1793
  %247 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1793
  %opts386 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %247, i32 0, i32 32, !dbg !1794
  %arrayidx387 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts386, i64 0, i64 %idxprom385, !dbg !1793
  %prev_2388 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx387, i32 0, i32 2, !dbg !1795
  store i8 0, i8* %prev_2388, align 1, !dbg !1796
  br label %if.end389, !dbg !1797

if.end389:                                        ; preds = %if.then367, %while.end358
  br label %if.end390, !dbg !1798

if.end390:                                        ; preds = %if.end389, %while.end
  br label %if.end391, !dbg !1799

if.end391:                                        ; preds = %if.end390, %land.lhs.true284, %cond.end281
  store i32 0, i32* %rep_index, align 4, !dbg !1800
  br label %for.cond392, !dbg !1802

for.cond392:                                      ; preds = %for.inc631, %if.end391
  %248 = load i32, i32* %rep_index, align 4, !dbg !1803
  %cmp393 = icmp ult i32 %248, 4, !dbg !1806
  br i1 %cmp393, label %for.body395, label %for.end633, !dbg !1807

for.body395:                                      ; preds = %for.cond392
  call void @llvm.dbg.declare(metadata i32* %len_test396, metadata !1808, metadata !305), !dbg !1810
  call void @llvm.dbg.declare(metadata i32* %len_test_2, metadata !1811, metadata !305), !dbg !1812
  call void @llvm.dbg.declare(metadata i32* %len_test_temp, metadata !1813, metadata !305), !dbg !1814
  call void @llvm.dbg.declare(metadata i32* %price397, metadata !1815, metadata !305), !dbg !1816
  call void @llvm.dbg.declare(metadata i32* %limit398, metadata !1817, metadata !305), !dbg !1818
  call void @llvm.dbg.declare(metadata i8** %buf_back399, metadata !1819, metadata !305), !dbg !1820
  %249 = load i8*, i8** %buf.addr, align 8, !dbg !1821
  %250 = load i32, i32* %rep_index, align 4, !dbg !1822
  %idxprom400 = zext i32 %250 to i64, !dbg !1823
  %251 = load i32*, i32** %reps.addr, align 8, !dbg !1823
  %arrayidx401 = getelementptr inbounds i32, i32* %251, i64 %idxprom400, !dbg !1823
  %252 = load i32, i32* %arrayidx401, align 4, !dbg !1823
  %idx.ext402 = zext i32 %252 to i64, !dbg !1824
  %idx.neg403 = sub i64 0, %idx.ext402, !dbg !1824
  %add.ptr404 = getelementptr inbounds i8, i8* %249, i64 %idx.neg403, !dbg !1824
  %add.ptr405 = getelementptr inbounds i8, i8* %add.ptr404, i64 -1, !dbg !1825
  store i8* %add.ptr405, i8** %buf_back399, align 8, !dbg !1820
  %253 = load i8*, i8** %buf.addr, align 8, !dbg !1826
  %254 = bitcast i8* %253 to i16*, !dbg !1826
  %255 = load i16, i16* %254, align 2, !dbg !1826
  %conv406 = zext i16 %255 to i32, !dbg !1826
  %256 = load i8*, i8** %buf_back399, align 8, !dbg !1826
  %257 = bitcast i8* %256 to i16*, !dbg !1826
  %258 = load i16, i16* %257, align 2, !dbg !1826
  %conv407 = zext i16 %258 to i32, !dbg !1826
  %cmp408 = icmp ne i32 %conv406, %conv407, !dbg !1826
  br i1 %cmp408, label %if.then410, label %if.end411, !dbg !1828

if.then410:                                       ; preds = %for.body395
  br label %for.inc631, !dbg !1829

if.end411:                                        ; preds = %for.body395
  store i32 2, i32* %len_test396, align 4, !dbg !1830
  br label %for.cond412, !dbg !1832

for.cond412:                                      ; preds = %for.inc426, %if.end411
  %259 = load i32, i32* %len_test396, align 4, !dbg !1833
  %260 = load i32, i32* %buf_avail, align 4, !dbg !1836
  %cmp413 = icmp ult i32 %259, %260, !dbg !1837
  br i1 %cmp413, label %land.rhs415, label %land.end424, !dbg !1838

land.rhs415:                                      ; preds = %for.cond412
  %261 = load i32, i32* %len_test396, align 4, !dbg !1839
  %idxprom416 = zext i32 %261 to i64, !dbg !1840
  %262 = load i8*, i8** %buf.addr, align 8, !dbg !1840
  %arrayidx417 = getelementptr inbounds i8, i8* %262, i64 %idxprom416, !dbg !1840
  %263 = load i8, i8* %arrayidx417, align 1, !dbg !1840
  %conv418 = zext i8 %263 to i32, !dbg !1840
  %264 = load i32, i32* %len_test396, align 4, !dbg !1841
  %idxprom419 = zext i32 %264 to i64, !dbg !1842
  %265 = load i8*, i8** %buf_back399, align 8, !dbg !1842
  %arrayidx420 = getelementptr inbounds i8, i8* %265, i64 %idxprom419, !dbg !1842
  %266 = load i8, i8* %arrayidx420, align 1, !dbg !1842
  %conv421 = zext i8 %266 to i32, !dbg !1842
  %cmp422 = icmp eq i32 %conv418, %conv421, !dbg !1843
  br label %land.end424

land.end424:                                      ; preds = %land.rhs415, %for.cond412
  %267 = phi i1 [ false, %for.cond412 ], [ %cmp422, %land.rhs415 ]
  br i1 %267, label %for.body425, label %for.end428, !dbg !1844

for.body425:                                      ; preds = %land.end424
  br label %for.inc426, !dbg !1846

for.inc426:                                       ; preds = %for.body425
  %268 = load i32, i32* %len_test396, align 4, !dbg !1848
  %inc427 = add i32 %268, 1, !dbg !1848
  store i32 %inc427, i32* %len_test396, align 4, !dbg !1848
  br label %for.cond412, !dbg !1849

for.end428:                                       ; preds = %land.end424
  br label %while.cond429, !dbg !1851

while.cond429:                                    ; preds = %while.body433, %for.end428
  %269 = load i32, i32* %len_end.addr, align 4, !dbg !1852
  %270 = load i32, i32* %cur.addr, align 4, !dbg !1854
  %271 = load i32, i32* %len_test396, align 4, !dbg !1855
  %add430 = add i32 %270, %271, !dbg !1856
  %cmp431 = icmp ult i32 %269, %add430, !dbg !1857
  br i1 %cmp431, label %while.body433, label %while.end439, !dbg !1858

while.body433:                                    ; preds = %while.cond429
  %272 = load i32, i32* %len_end.addr, align 4, !dbg !1859
  %inc434 = add i32 %272, 1, !dbg !1859
  store i32 %inc434, i32* %len_end.addr, align 4, !dbg !1859
  %idxprom435 = zext i32 %inc434 to i64, !dbg !1860
  %273 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1860
  %opts436 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %273, i32 0, i32 32, !dbg !1861
  %arrayidx437 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts436, i64 0, i64 %idxprom435, !dbg !1860
  %price438 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx437, i32 0, i32 5, !dbg !1862
  store i32 1073741824, i32* %price438, align 4, !dbg !1863
  br label %while.cond429, !dbg !1864

while.end439:                                     ; preds = %while.cond429
  %274 = load i32, i32* %len_test396, align 4, !dbg !1866
  store i32 %274, i32* %len_test_temp, align 4, !dbg !1867
  %275 = load i32, i32* %rep_match_price, align 4, !dbg !1868
  %276 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1869
  %277 = load i32, i32* %rep_index, align 4, !dbg !1870
  %278 = load i32, i32* %state, align 4, !dbg !1871
  %279 = load i32, i32* %pos_state, align 4, !dbg !1872
  %call440 = call i32 @get_pure_rep_price(%struct.lzma_coder_s* %276, i32 %277, i32 %278, i32 %279), !dbg !1873
  %add441 = add i32 %275, %call440, !dbg !1874
  store i32 %add441, i32* %price397, align 4, !dbg !1875
  br label %do.body, !dbg !1876

do.body:                                          ; preds = %do.cond, %while.end439
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price442, metadata !1877, metadata !305), !dbg !1879
  %280 = load i32, i32* %price397, align 4, !dbg !1880
  %281 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1881
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %281, i32 0, i32 23, !dbg !1882
  %282 = load i32, i32* %len_test396, align 4, !dbg !1883
  %283 = load i32, i32* %pos_state, align 4, !dbg !1884
  %call443 = call i32 @get_len_price(%struct.lzma_length_encoder* %rep_len_encoder, i32 %282, i32 %283), !dbg !1885
  %add444 = add i32 %280, %call443, !dbg !1886
  store i32 %add444, i32* %cur_and_len_price442, align 4, !dbg !1879
  %284 = load i32, i32* %cur_and_len_price442, align 4, !dbg !1887
  %285 = load i32, i32* %cur.addr, align 4, !dbg !1889
  %286 = load i32, i32* %len_test396, align 4, !dbg !1890
  %add445 = add i32 %285, %286, !dbg !1891
  %idxprom446 = zext i32 %add445 to i64, !dbg !1892
  %287 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1892
  %opts447 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %287, i32 0, i32 32, !dbg !1893
  %arrayidx448 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts447, i64 0, i64 %idxprom446, !dbg !1892
  %price449 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx448, i32 0, i32 5, !dbg !1894
  %288 = load i32, i32* %price449, align 4, !dbg !1894
  %cmp450 = icmp ult i32 %284, %288, !dbg !1895
  br i1 %cmp450, label %if.then452, label %if.end473, !dbg !1896

if.then452:                                       ; preds = %do.body
  %289 = load i32, i32* %cur_and_len_price442, align 4, !dbg !1897
  %290 = load i32, i32* %cur.addr, align 4, !dbg !1899
  %291 = load i32, i32* %len_test396, align 4, !dbg !1900
  %add453 = add i32 %290, %291, !dbg !1901
  %idxprom454 = zext i32 %add453 to i64, !dbg !1902
  %292 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1902
  %opts455 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %292, i32 0, i32 32, !dbg !1903
  %arrayidx456 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts455, i64 0, i64 %idxprom454, !dbg !1902
  %price457 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx456, i32 0, i32 5, !dbg !1904
  store i32 %289, i32* %price457, align 4, !dbg !1905
  %293 = load i32, i32* %cur.addr, align 4, !dbg !1906
  %294 = load i32, i32* %cur.addr, align 4, !dbg !1907
  %295 = load i32, i32* %len_test396, align 4, !dbg !1908
  %add458 = add i32 %294, %295, !dbg !1909
  %idxprom459 = zext i32 %add458 to i64, !dbg !1910
  %296 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1910
  %opts460 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %296, i32 0, i32 32, !dbg !1911
  %arrayidx461 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts460, i64 0, i64 %idxprom459, !dbg !1910
  %pos_prev462 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx461, i32 0, i32 6, !dbg !1912
  store i32 %293, i32* %pos_prev462, align 4, !dbg !1913
  %297 = load i32, i32* %rep_index, align 4, !dbg !1914
  %298 = load i32, i32* %cur.addr, align 4, !dbg !1915
  %299 = load i32, i32* %len_test396, align 4, !dbg !1916
  %add463 = add i32 %298, %299, !dbg !1917
  %idxprom464 = zext i32 %add463 to i64, !dbg !1918
  %300 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1918
  %opts465 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %300, i32 0, i32 32, !dbg !1919
  %arrayidx466 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts465, i64 0, i64 %idxprom464, !dbg !1918
  %back_prev467 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx466, i32 0, i32 7, !dbg !1920
  store i32 %297, i32* %back_prev467, align 4, !dbg !1921
  %301 = load i32, i32* %cur.addr, align 4, !dbg !1922
  %302 = load i32, i32* %len_test396, align 4, !dbg !1923
  %add468 = add i32 %301, %302, !dbg !1924
  %idxprom469 = zext i32 %add468 to i64, !dbg !1925
  %303 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1925
  %opts470 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %303, i32 0, i32 32, !dbg !1926
  %arrayidx471 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts470, i64 0, i64 %idxprom469, !dbg !1925
  %prev_1_is_literal472 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx471, i32 0, i32 1, !dbg !1927
  store i8 0, i8* %prev_1_is_literal472, align 4, !dbg !1928
  br label %if.end473, !dbg !1929

if.end473:                                        ; preds = %if.then452, %do.body
  br label %do.cond, !dbg !1930

do.cond:                                          ; preds = %if.end473
  %304 = load i32, i32* %len_test396, align 4, !dbg !1931
  %dec474 = add i32 %304, -1, !dbg !1931
  store i32 %dec474, i32* %len_test396, align 4, !dbg !1931
  %cmp475 = icmp uge i32 %dec474, 2, !dbg !1932
  br i1 %cmp475, label %do.body, label %do.end, !dbg !1933

do.end:                                           ; preds = %do.cond
  %305 = load i32, i32* %len_test_temp, align 4, !dbg !1934
  store i32 %305, i32* %len_test396, align 4, !dbg !1935
  %306 = load i32, i32* %rep_index, align 4, !dbg !1936
  %cmp477 = icmp eq i32 %306, 0, !dbg !1938
  br i1 %cmp477, label %if.then479, label %if.end481, !dbg !1939

if.then479:                                       ; preds = %do.end
  %307 = load i32, i32* %len_test396, align 4, !dbg !1940
  %add480 = add i32 %307, 1, !dbg !1941
  store i32 %add480, i32* %start_len, align 4, !dbg !1942
  br label %if.end481, !dbg !1943

if.end481:                                        ; preds = %if.then479, %do.end
  %308 = load i32, i32* %len_test396, align 4, !dbg !1944
  %add482 = add i32 %308, 1, !dbg !1945
  store i32 %add482, i32* %len_test_2, align 4, !dbg !1946
  %309 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1947
  %310 = load i32, i32* %len_test_2, align 4, !dbg !1947
  %311 = load i32, i32* %nice_len.addr, align 4, !dbg !1947
  %add483 = add i32 %310, %311, !dbg !1947
  %cmp484 = icmp ult i32 %309, %add483, !dbg !1947
  br i1 %cmp484, label %cond.true486, label %cond.false487, !dbg !1947

cond.true486:                                     ; preds = %if.end481
  %312 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !1948
  br label %cond.end489, !dbg !1948

cond.false487:                                    ; preds = %if.end481
  %313 = load i32, i32* %len_test_2, align 4, !dbg !1949
  %314 = load i32, i32* %nice_len.addr, align 4, !dbg !1949
  %add488 = add i32 %313, %314, !dbg !1949
  br label %cond.end489, !dbg !1949

cond.end489:                                      ; preds = %cond.false487, %cond.true486
  %cond490 = phi i32 [ %312, %cond.true486 ], [ %add488, %cond.false487 ], !dbg !1950
  store i32 %cond490, i32* %limit398, align 4, !dbg !1952
  br label %for.cond491, !dbg !1953

for.cond491:                                      ; preds = %for.inc505, %cond.end489
  %315 = load i32, i32* %len_test_2, align 4, !dbg !1954
  %316 = load i32, i32* %limit398, align 4, !dbg !1958
  %cmp492 = icmp ult i32 %315, %316, !dbg !1959
  br i1 %cmp492, label %land.rhs494, label %land.end503, !dbg !1960

land.rhs494:                                      ; preds = %for.cond491
  %317 = load i32, i32* %len_test_2, align 4, !dbg !1961
  %idxprom495 = zext i32 %317 to i64, !dbg !1962
  %318 = load i8*, i8** %buf.addr, align 8, !dbg !1962
  %arrayidx496 = getelementptr inbounds i8, i8* %318, i64 %idxprom495, !dbg !1962
  %319 = load i8, i8* %arrayidx496, align 1, !dbg !1962
  %conv497 = zext i8 %319 to i32, !dbg !1962
  %320 = load i32, i32* %len_test_2, align 4, !dbg !1963
  %idxprom498 = zext i32 %320 to i64, !dbg !1964
  %321 = load i8*, i8** %buf_back399, align 8, !dbg !1964
  %arrayidx499 = getelementptr inbounds i8, i8* %321, i64 %idxprom498, !dbg !1964
  %322 = load i8, i8* %arrayidx499, align 1, !dbg !1964
  %conv500 = zext i8 %322 to i32, !dbg !1964
  %cmp501 = icmp eq i32 %conv497, %conv500, !dbg !1965
  br label %land.end503

land.end503:                                      ; preds = %land.rhs494, %for.cond491
  %323 = phi i1 [ false, %for.cond491 ], [ %cmp501, %land.rhs494 ]
  br i1 %323, label %for.body504, label %for.end507, !dbg !1966

for.body504:                                      ; preds = %land.end503
  br label %for.inc505, !dbg !1968

for.inc505:                                       ; preds = %for.body504
  %324 = load i32, i32* %len_test_2, align 4, !dbg !1970
  %inc506 = add i32 %324, 1, !dbg !1970
  store i32 %inc506, i32* %len_test_2, align 4, !dbg !1970
  br label %for.cond491, !dbg !1971

for.end507:                                       ; preds = %land.end503
  %325 = load i32, i32* %len_test396, align 4, !dbg !1973
  %add508 = add i32 %325, 1, !dbg !1974
  %326 = load i32, i32* %len_test_2, align 4, !dbg !1975
  %sub509 = sub i32 %326, %add508, !dbg !1975
  store i32 %sub509, i32* %len_test_2, align 4, !dbg !1975
  %327 = load i32, i32* %len_test_2, align 4, !dbg !1976
  %cmp510 = icmp uge i32 %327, 2, !dbg !1978
  br i1 %cmp510, label %if.then512, label %if.end630, !dbg !1979

if.then512:                                       ; preds = %for.end507
  call void @llvm.dbg.declare(metadata i32* %pos_state_next513, metadata !1980, metadata !305), !dbg !1982
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_literal_price, metadata !1983, metadata !305), !dbg !1984
  call void @llvm.dbg.declare(metadata i32* %next_rep_match_price514, metadata !1985, metadata !305), !dbg !1986
  call void @llvm.dbg.declare(metadata i32* %offset515, metadata !1987, metadata !305), !dbg !1988
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price516, metadata !1989, metadata !305), !dbg !1990
  call void @llvm.dbg.declare(metadata i32* %state_2517, metadata !1991, metadata !305), !dbg !1992
  %328 = load i32, i32* %state, align 4, !dbg !1993
  store i32 %328, i32* %state_2517, align 4, !dbg !1992
  %329 = load i32, i32* %state_2517, align 4, !dbg !1994
  %cmp518 = icmp ult i32 %329, 7, !dbg !1994
  %cond520 = select i1 %cmp518, i32 8, i32 11, !dbg !1994
  store i32 %cond520, i32* %state_2517, align 4, !dbg !1994
  %330 = load i32, i32* %position.addr, align 4, !dbg !1995
  %331 = load i32, i32* %len_test396, align 4, !dbg !1996
  %add521 = add i32 %330, %331, !dbg !1997
  %332 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1998
  %pos_mask522 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %332, i32 0, i32 9, !dbg !1999
  %333 = load i32, i32* %pos_mask522, align 8, !dbg !1999
  %and523 = and i32 %add521, %333, !dbg !2000
  store i32 %and523, i32* %pos_state_next513, align 4, !dbg !2001
  %334 = load i32, i32* %price397, align 4, !dbg !2002
  %335 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2003
  %rep_len_encoder524 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %335, i32 0, i32 23, !dbg !2004
  %336 = load i32, i32* %len_test396, align 4, !dbg !2005
  %337 = load i32, i32* %pos_state, align 4, !dbg !2006
  %call525 = call i32 @get_len_price(%struct.lzma_length_encoder* %rep_len_encoder524, i32 %336, i32 %337), !dbg !2007
  %add526 = add i32 %334, %call525, !dbg !2008
  %338 = load i32, i32* %pos_state_next513, align 4, !dbg !2009
  %idxprom527 = zext i32 %338 to i64, !dbg !2010
  %339 = load i32, i32* %state_2517, align 4, !dbg !2011
  %idxprom528 = zext i32 %339 to i64, !dbg !2010
  %340 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2010
  %is_match529 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %340, i32 0, i32 13, !dbg !2012
  %arrayidx530 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match529, i64 0, i64 %idxprom528, !dbg !2010
  %arrayidx531 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx530, i64 0, i64 %idxprom527, !dbg !2010
  %341 = load i16, i16* %arrayidx531, align 2, !dbg !2010
  %call532 = call i32 @rc_bit_0_price(i16 zeroext %341), !dbg !2013
  %add533 = add i32 %add526, %call532, !dbg !2014
  %342 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2015
  %343 = load i32, i32* %position.addr, align 4, !dbg !2016
  %344 = load i32, i32* %len_test396, align 4, !dbg !2017
  %add534 = add i32 %343, %344, !dbg !2018
  %345 = load i32, i32* %len_test396, align 4, !dbg !2019
  %sub535 = sub i32 %345, 1, !dbg !2020
  %idxprom536 = zext i32 %sub535 to i64, !dbg !2021
  %346 = load i8*, i8** %buf.addr, align 8, !dbg !2021
  %arrayidx537 = getelementptr inbounds i8, i8* %346, i64 %idxprom536, !dbg !2021
  %347 = load i8, i8* %arrayidx537, align 1, !dbg !2021
  %conv538 = zext i8 %347 to i32, !dbg !2021
  %348 = load i32, i32* %len_test396, align 4, !dbg !2022
  %idxprom539 = zext i32 %348 to i64, !dbg !2023
  %349 = load i8*, i8** %buf_back399, align 8, !dbg !2023
  %arrayidx540 = getelementptr inbounds i8, i8* %349, i64 %idxprom539, !dbg !2023
  %350 = load i8, i8* %arrayidx540, align 1, !dbg !2023
  %conv541 = zext i8 %350 to i32, !dbg !2023
  %351 = load i32, i32* %len_test396, align 4, !dbg !2024
  %idxprom542 = zext i32 %351 to i64, !dbg !2025
  %352 = load i8*, i8** %buf.addr, align 8, !dbg !2025
  %arrayidx543 = getelementptr inbounds i8, i8* %352, i64 %idxprom542, !dbg !2025
  %353 = load i8, i8* %arrayidx543, align 1, !dbg !2025
  %conv544 = zext i8 %353 to i32, !dbg !2025
  %call545 = call i32 @get_literal_price(%struct.lzma_coder_s* %342, i32 %add534, i32 %conv538, i1 zeroext true, i32 %conv541, i32 %conv544), !dbg !2026
  %add546 = add i32 %add533, %call545, !dbg !2027
  store i32 %add546, i32* %cur_and_len_literal_price, align 4, !dbg !2028
  %354 = load i32, i32* %state_2517, align 4, !dbg !2029
  %cmp547 = icmp ule i32 %354, 3, !dbg !2029
  br i1 %cmp547, label %cond.true549, label %cond.false550, !dbg !2029

cond.true549:                                     ; preds = %if.then512
  br label %cond.end559, !dbg !2030

cond.false550:                                    ; preds = %if.then512
  %355 = load i32, i32* %state_2517, align 4, !dbg !2032
  %cmp551 = icmp ule i32 %355, 9, !dbg !2032
  br i1 %cmp551, label %cond.true553, label %cond.false555, !dbg !2032

cond.true553:                                     ; preds = %cond.false550
  %356 = load i32, i32* %state_2517, align 4, !dbg !2034
  %sub554 = sub i32 %356, 3, !dbg !2034
  br label %cond.end557, !dbg !2034

cond.false555:                                    ; preds = %cond.false550
  %357 = load i32, i32* %state_2517, align 4, !dbg !2036
  %sub556 = sub i32 %357, 6, !dbg !2036
  br label %cond.end557, !dbg !2036

cond.end557:                                      ; preds = %cond.false555, %cond.true553
  %cond558 = phi i32 [ %sub554, %cond.true553 ], [ %sub556, %cond.false555 ], !dbg !2038
  br label %cond.end559, !dbg !2038

cond.end559:                                      ; preds = %cond.end557, %cond.true549
  %cond560 = phi i32 [ 0, %cond.true549 ], [ %cond558, %cond.end557 ], !dbg !2040
  store i32 %cond560, i32* %state_2517, align 4, !dbg !2040
  %358 = load i32, i32* %position.addr, align 4, !dbg !2042
  %359 = load i32, i32* %len_test396, align 4, !dbg !2043
  %add561 = add i32 %358, %359, !dbg !2044
  %add562 = add i32 %add561, 1, !dbg !2045
  %360 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2046
  %pos_mask563 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %360, i32 0, i32 9, !dbg !2047
  %361 = load i32, i32* %pos_mask563, align 8, !dbg !2047
  %and564 = and i32 %add562, %361, !dbg !2048
  store i32 %and564, i32* %pos_state_next513, align 4, !dbg !2049
  %362 = load i32, i32* %cur_and_len_literal_price, align 4, !dbg !2050
  %363 = load i32, i32* %pos_state_next513, align 4, !dbg !2051
  %idxprom565 = zext i32 %363 to i64, !dbg !2052
  %364 = load i32, i32* %state_2517, align 4, !dbg !2053
  %idxprom566 = zext i32 %364 to i64, !dbg !2052
  %365 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2052
  %is_match567 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %365, i32 0, i32 13, !dbg !2054
  %arrayidx568 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match567, i64 0, i64 %idxprom566, !dbg !2052
  %arrayidx569 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx568, i64 0, i64 %idxprom565, !dbg !2052
  %366 = load i16, i16* %arrayidx569, align 2, !dbg !2052
  %call570 = call i32 @rc_bit_1_price(i16 zeroext %366), !dbg !2055
  %add571 = add i32 %362, %call570, !dbg !2056
  %367 = load i32, i32* %state_2517, align 4, !dbg !2057
  %idxprom572 = zext i32 %367 to i64, !dbg !2058
  %368 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2058
  %is_rep573 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %368, i32 0, i32 14, !dbg !2059
  %arrayidx574 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep573, i64 0, i64 %idxprom572, !dbg !2058
  %369 = load i16, i16* %arrayidx574, align 2, !dbg !2058
  %call575 = call i32 @rc_bit_1_price(i16 zeroext %369), !dbg !2060
  %add576 = add i32 %add571, %call575, !dbg !2061
  store i32 %add576, i32* %next_rep_match_price514, align 4, !dbg !2062
  %370 = load i32, i32* %cur.addr, align 4, !dbg !2063
  %371 = load i32, i32* %len_test396, align 4, !dbg !2064
  %add577 = add i32 %370, %371, !dbg !2065
  %add578 = add i32 %add577, 1, !dbg !2066
  %372 = load i32, i32* %len_test_2, align 4, !dbg !2067
  %add579 = add i32 %add578, %372, !dbg !2068
  store i32 %add579, i32* %offset515, align 4, !dbg !2069
  br label %while.cond580, !dbg !2070

while.cond580:                                    ; preds = %while.body583, %cond.end559
  %373 = load i32, i32* %len_end.addr, align 4, !dbg !2071
  %374 = load i32, i32* %offset515, align 4, !dbg !2072
  %cmp581 = icmp ult i32 %373, %374, !dbg !2073
  br i1 %cmp581, label %while.body583, label %while.end589, !dbg !2074

while.body583:                                    ; preds = %while.cond580
  %375 = load i32, i32* %len_end.addr, align 4, !dbg !2075
  %inc584 = add i32 %375, 1, !dbg !2075
  store i32 %inc584, i32* %len_end.addr, align 4, !dbg !2075
  %idxprom585 = zext i32 %inc584 to i64, !dbg !2076
  %376 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2076
  %opts586 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %376, i32 0, i32 32, !dbg !2077
  %arrayidx587 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts586, i64 0, i64 %idxprom585, !dbg !2076
  %price588 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx587, i32 0, i32 5, !dbg !2078
  store i32 1073741824, i32* %price588, align 4, !dbg !2079
  br label %while.cond580, !dbg !2080

while.end589:                                     ; preds = %while.cond580
  %377 = load i32, i32* %next_rep_match_price514, align 4, !dbg !2081
  %378 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2082
  %379 = load i32, i32* %len_test_2, align 4, !dbg !2083
  %380 = load i32, i32* %state_2517, align 4, !dbg !2084
  %381 = load i32, i32* %pos_state_next513, align 4, !dbg !2085
  %call590 = call i32 @get_rep_price(%struct.lzma_coder_s* %378, i32 0, i32 %379, i32 %380, i32 %381), !dbg !2086
  %add591 = add i32 %377, %call590, !dbg !2087
  store i32 %add591, i32* %cur_and_len_price516, align 4, !dbg !2088
  %382 = load i32, i32* %cur_and_len_price516, align 4, !dbg !2089
  %383 = load i32, i32* %offset515, align 4, !dbg !2091
  %idxprom592 = zext i32 %383 to i64, !dbg !2092
  %384 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2092
  %opts593 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %384, i32 0, i32 32, !dbg !2093
  %arrayidx594 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts593, i64 0, i64 %idxprom592, !dbg !2092
  %price595 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx594, i32 0, i32 5, !dbg !2094
  %385 = load i32, i32* %price595, align 4, !dbg !2094
  %cmp596 = icmp ult i32 %382, %385, !dbg !2095
  br i1 %cmp596, label %if.then598, label %if.end629, !dbg !2096

if.then598:                                       ; preds = %while.end589
  %386 = load i32, i32* %cur_and_len_price516, align 4, !dbg !2097
  %387 = load i32, i32* %offset515, align 4, !dbg !2099
  %idxprom599 = zext i32 %387 to i64, !dbg !2100
  %388 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2100
  %opts600 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %388, i32 0, i32 32, !dbg !2101
  %arrayidx601 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts600, i64 0, i64 %idxprom599, !dbg !2100
  %price602 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx601, i32 0, i32 5, !dbg !2102
  store i32 %386, i32* %price602, align 4, !dbg !2103
  %389 = load i32, i32* %cur.addr, align 4, !dbg !2104
  %390 = load i32, i32* %len_test396, align 4, !dbg !2105
  %add603 = add i32 %389, %390, !dbg !2106
  %add604 = add i32 %add603, 1, !dbg !2107
  %391 = load i32, i32* %offset515, align 4, !dbg !2108
  %idxprom605 = zext i32 %391 to i64, !dbg !2109
  %392 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2109
  %opts606 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %392, i32 0, i32 32, !dbg !2110
  %arrayidx607 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts606, i64 0, i64 %idxprom605, !dbg !2109
  %pos_prev608 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx607, i32 0, i32 6, !dbg !2111
  store i32 %add604, i32* %pos_prev608, align 4, !dbg !2112
  %393 = load i32, i32* %offset515, align 4, !dbg !2113
  %idxprom609 = zext i32 %393 to i64, !dbg !2114
  %394 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2114
  %opts610 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %394, i32 0, i32 32, !dbg !2115
  %arrayidx611 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts610, i64 0, i64 %idxprom609, !dbg !2114
  %back_prev612 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx611, i32 0, i32 7, !dbg !2116
  store i32 0, i32* %back_prev612, align 4, !dbg !2117
  %395 = load i32, i32* %offset515, align 4, !dbg !2118
  %idxprom613 = zext i32 %395 to i64, !dbg !2119
  %396 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2119
  %opts614 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %396, i32 0, i32 32, !dbg !2120
  %arrayidx615 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts614, i64 0, i64 %idxprom613, !dbg !2119
  %prev_1_is_literal616 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx615, i32 0, i32 1, !dbg !2121
  store i8 1, i8* %prev_1_is_literal616, align 4, !dbg !2122
  %397 = load i32, i32* %offset515, align 4, !dbg !2123
  %idxprom617 = zext i32 %397 to i64, !dbg !2124
  %398 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2124
  %opts618 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %398, i32 0, i32 32, !dbg !2125
  %arrayidx619 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts618, i64 0, i64 %idxprom617, !dbg !2124
  %prev_2620 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx619, i32 0, i32 2, !dbg !2126
  store i8 1, i8* %prev_2620, align 1, !dbg !2127
  %399 = load i32, i32* %cur.addr, align 4, !dbg !2128
  %400 = load i32, i32* %offset515, align 4, !dbg !2129
  %idxprom621 = zext i32 %400 to i64, !dbg !2130
  %401 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2130
  %opts622 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %401, i32 0, i32 32, !dbg !2131
  %arrayidx623 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts622, i64 0, i64 %idxprom621, !dbg !2130
  %pos_prev_2624 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx623, i32 0, i32 3, !dbg !2132
  store i32 %399, i32* %pos_prev_2624, align 4, !dbg !2133
  %402 = load i32, i32* %rep_index, align 4, !dbg !2134
  %403 = load i32, i32* %offset515, align 4, !dbg !2135
  %idxprom625 = zext i32 %403 to i64, !dbg !2136
  %404 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2136
  %opts626 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %404, i32 0, i32 32, !dbg !2137
  %arrayidx627 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts626, i64 0, i64 %idxprom625, !dbg !2136
  %back_prev_2628 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx627, i32 0, i32 4, !dbg !2138
  store i32 %402, i32* %back_prev_2628, align 4, !dbg !2139
  br label %if.end629, !dbg !2140

if.end629:                                        ; preds = %if.then598, %while.end589
  br label %if.end630, !dbg !2141

if.end630:                                        ; preds = %if.end629, %for.end507
  br label %for.inc631, !dbg !2142

for.inc631:                                       ; preds = %if.end630, %if.then410
  %405 = load i32, i32* %rep_index, align 4, !dbg !2143
  %inc632 = add i32 %405, 1, !dbg !2143
  store i32 %inc632, i32* %rep_index, align 4, !dbg !2143
  br label %for.cond392, !dbg !2145

for.end633:                                       ; preds = %for.cond392
  %406 = load i32, i32* %new_len, align 4, !dbg !2146
  %407 = load i32, i32* %buf_avail, align 4, !dbg !2148
  %cmp634 = icmp ugt i32 %406, %407, !dbg !2149
  br i1 %cmp634, label %if.then636, label %if.end650, !dbg !2150

if.then636:                                       ; preds = %for.end633
  %408 = load i32, i32* %buf_avail, align 4, !dbg !2151
  store i32 %408, i32* %new_len, align 4, !dbg !2153
  store i32 0, i32* %matches_count, align 4, !dbg !2154
  br label %while.cond637, !dbg !2155

while.cond637:                                    ; preds = %while.body642, %if.then636
  %409 = load i32, i32* %new_len, align 4, !dbg !2156
  %410 = load i32, i32* %matches_count, align 4, !dbg !2158
  %idxprom638 = zext i32 %410 to i64, !dbg !2159
  %411 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2159
  %matches = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %411, i32 0, i32 3, !dbg !2160
  %arrayidx639 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches, i64 0, i64 %idxprom638, !dbg !2159
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx639, i32 0, i32 0, !dbg !2161
  %412 = load i32, i32* %len, align 4, !dbg !2161
  %cmp640 = icmp ugt i32 %409, %412, !dbg !2162
  br i1 %cmp640, label %while.body642, label %while.end644, !dbg !2163

while.body642:                                    ; preds = %while.cond637
  %413 = load i32, i32* %matches_count, align 4, !dbg !2164
  %inc643 = add i32 %413, 1, !dbg !2164
  store i32 %inc643, i32* %matches_count, align 4, !dbg !2164
  br label %while.cond637, !dbg !2165

while.end644:                                     ; preds = %while.cond637
  %414 = load i32, i32* %new_len, align 4, !dbg !2167
  %415 = load i32, i32* %matches_count, align 4, !dbg !2168
  %inc645 = add i32 %415, 1, !dbg !2168
  store i32 %inc645, i32* %matches_count, align 4, !dbg !2168
  %idxprom646 = zext i32 %415 to i64, !dbg !2169
  %416 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2169
  %matches647 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %416, i32 0, i32 3, !dbg !2170
  %arrayidx648 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches647, i64 0, i64 %idxprom646, !dbg !2169
  %len649 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx648, i32 0, i32 0, !dbg !2171
  store i32 %414, i32* %len649, align 4, !dbg !2172
  br label %if.end650, !dbg !2173

if.end650:                                        ; preds = %while.end644, %for.end633
  %417 = load i32, i32* %new_len, align 4, !dbg !2174
  %418 = load i32, i32* %start_len, align 4, !dbg !2176
  %cmp651 = icmp uge i32 %417, %418, !dbg !2177
  br i1 %cmp651, label %if.then653, label %if.end888, !dbg !2178

if.then653:                                       ; preds = %if.end650
  call void @llvm.dbg.declare(metadata i32* %len_test654, metadata !2179, metadata !305), !dbg !2181
  call void @llvm.dbg.declare(metadata i32* %i655, metadata !2182, metadata !305), !dbg !2183
  store i32 0, i32* %i655, align 4, !dbg !2183
  call void @llvm.dbg.declare(metadata i32* %normal_match_price, metadata !2184, metadata !305), !dbg !2185
  %419 = load i32, i32* %match_price, align 4, !dbg !2186
  %420 = load i32, i32* %state, align 4, !dbg !2187
  %idxprom656 = zext i32 %420 to i64, !dbg !2188
  %421 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2188
  %is_rep657 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %421, i32 0, i32 14, !dbg !2189
  %arrayidx658 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep657, i64 0, i64 %idxprom656, !dbg !2188
  %422 = load i16, i16* %arrayidx658, align 2, !dbg !2188
  %call659 = call i32 @rc_bit_0_price(i16 zeroext %422), !dbg !2190
  %add660 = add i32 %419, %call659, !dbg !2191
  store i32 %add660, i32* %normal_match_price, align 4, !dbg !2185
  br label %while.cond661, !dbg !2192

while.cond661:                                    ; preds = %while.body665, %if.then653
  %423 = load i32, i32* %len_end.addr, align 4, !dbg !2193
  %424 = load i32, i32* %cur.addr, align 4, !dbg !2195
  %425 = load i32, i32* %new_len, align 4, !dbg !2196
  %add662 = add i32 %424, %425, !dbg !2197
  %cmp663 = icmp ult i32 %423, %add662, !dbg !2198
  br i1 %cmp663, label %while.body665, label %while.end671, !dbg !2199

while.body665:                                    ; preds = %while.cond661
  %426 = load i32, i32* %len_end.addr, align 4, !dbg !2200
  %inc666 = add i32 %426, 1, !dbg !2200
  store i32 %inc666, i32* %len_end.addr, align 4, !dbg !2200
  %idxprom667 = zext i32 %inc666 to i64, !dbg !2201
  %427 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2201
  %opts668 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %427, i32 0, i32 32, !dbg !2202
  %arrayidx669 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts668, i64 0, i64 %idxprom667, !dbg !2201
  %price670 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx669, i32 0, i32 5, !dbg !2203
  store i32 1073741824, i32* %price670, align 4, !dbg !2204
  br label %while.cond661, !dbg !2205

while.end671:                                     ; preds = %while.cond661
  br label %while.cond672, !dbg !2207

while.cond672:                                    ; preds = %while.body679, %while.end671
  %428 = load i32, i32* %start_len, align 4, !dbg !2208
  %429 = load i32, i32* %i655, align 4, !dbg !2209
  %idxprom673 = zext i32 %429 to i64, !dbg !2210
  %430 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2210
  %matches674 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %430, i32 0, i32 3, !dbg !2211
  %arrayidx675 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches674, i64 0, i64 %idxprom673, !dbg !2210
  %len676 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx675, i32 0, i32 0, !dbg !2212
  %431 = load i32, i32* %len676, align 4, !dbg !2212
  %cmp677 = icmp ugt i32 %428, %431, !dbg !2213
  br i1 %cmp677, label %while.body679, label %while.end681, !dbg !2214

while.body679:                                    ; preds = %while.cond672
  %432 = load i32, i32* %i655, align 4, !dbg !2215
  %inc680 = add i32 %432, 1, !dbg !2215
  store i32 %inc680, i32* %i655, align 4, !dbg !2215
  br label %while.cond672, !dbg !2216

while.end681:                                     ; preds = %while.cond672
  %433 = load i32, i32* %start_len, align 4, !dbg !2217
  store i32 %433, i32* %len_test654, align 4, !dbg !2219
  br label %for.cond682, !dbg !2220

for.cond682:                                      ; preds = %for.inc885, %while.end681
  call void @llvm.dbg.declare(metadata i32* %cur_back, metadata !2221, metadata !305), !dbg !2224
  %434 = load i32, i32* %i655, align 4, !dbg !2225
  %idxprom683 = zext i32 %434 to i64, !dbg !2226
  %435 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2226
  %matches684 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %435, i32 0, i32 3, !dbg !2227
  %arrayidx685 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches684, i64 0, i64 %idxprom683, !dbg !2226
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx685, i32 0, i32 1, !dbg !2228
  %436 = load i32, i32* %dist, align 4, !dbg !2228
  store i32 %436, i32* %cur_back, align 4, !dbg !2224
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_price686, metadata !2229, metadata !305), !dbg !2230
  %437 = load i32, i32* %normal_match_price, align 4, !dbg !2231
  %438 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2232
  %439 = load i32, i32* %cur_back, align 4, !dbg !2233
  %440 = load i32, i32* %len_test654, align 4, !dbg !2234
  %441 = load i32, i32* %pos_state, align 4, !dbg !2235
  %call687 = call i32 @get_pos_len_price(%struct.lzma_coder_s* %438, i32 %439, i32 %440, i32 %441), !dbg !2236
  %add688 = add i32 %437, %call687, !dbg !2237
  store i32 %add688, i32* %cur_and_len_price686, align 4, !dbg !2230
  %442 = load i32, i32* %cur_and_len_price686, align 4, !dbg !2238
  %443 = load i32, i32* %cur.addr, align 4, !dbg !2240
  %444 = load i32, i32* %len_test654, align 4, !dbg !2241
  %add689 = add i32 %443, %444, !dbg !2242
  %idxprom690 = zext i32 %add689 to i64, !dbg !2243
  %445 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2243
  %opts691 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %445, i32 0, i32 32, !dbg !2244
  %arrayidx692 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts691, i64 0, i64 %idxprom690, !dbg !2243
  %price693 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx692, i32 0, i32 5, !dbg !2245
  %446 = load i32, i32* %price693, align 4, !dbg !2245
  %cmp694 = icmp ult i32 %442, %446, !dbg !2246
  br i1 %cmp694, label %if.then696, label %if.end718, !dbg !2247

if.then696:                                       ; preds = %for.cond682
  %447 = load i32, i32* %cur_and_len_price686, align 4, !dbg !2248
  %448 = load i32, i32* %cur.addr, align 4, !dbg !2250
  %449 = load i32, i32* %len_test654, align 4, !dbg !2251
  %add697 = add i32 %448, %449, !dbg !2252
  %idxprom698 = zext i32 %add697 to i64, !dbg !2253
  %450 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2253
  %opts699 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %450, i32 0, i32 32, !dbg !2254
  %arrayidx700 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts699, i64 0, i64 %idxprom698, !dbg !2253
  %price701 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx700, i32 0, i32 5, !dbg !2255
  store i32 %447, i32* %price701, align 4, !dbg !2256
  %451 = load i32, i32* %cur.addr, align 4, !dbg !2257
  %452 = load i32, i32* %cur.addr, align 4, !dbg !2258
  %453 = load i32, i32* %len_test654, align 4, !dbg !2259
  %add702 = add i32 %452, %453, !dbg !2260
  %idxprom703 = zext i32 %add702 to i64, !dbg !2261
  %454 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2261
  %opts704 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %454, i32 0, i32 32, !dbg !2262
  %arrayidx705 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts704, i64 0, i64 %idxprom703, !dbg !2261
  %pos_prev706 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx705, i32 0, i32 6, !dbg !2263
  store i32 %451, i32* %pos_prev706, align 4, !dbg !2264
  %455 = load i32, i32* %cur_back, align 4, !dbg !2265
  %add707 = add i32 %455, 4, !dbg !2266
  %456 = load i32, i32* %cur.addr, align 4, !dbg !2267
  %457 = load i32, i32* %len_test654, align 4, !dbg !2268
  %add708 = add i32 %456, %457, !dbg !2269
  %idxprom709 = zext i32 %add708 to i64, !dbg !2270
  %458 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2270
  %opts710 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %458, i32 0, i32 32, !dbg !2271
  %arrayidx711 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts710, i64 0, i64 %idxprom709, !dbg !2270
  %back_prev712 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx711, i32 0, i32 7, !dbg !2272
  store i32 %add707, i32* %back_prev712, align 4, !dbg !2273
  %459 = load i32, i32* %cur.addr, align 4, !dbg !2274
  %460 = load i32, i32* %len_test654, align 4, !dbg !2275
  %add713 = add i32 %459, %460, !dbg !2276
  %idxprom714 = zext i32 %add713 to i64, !dbg !2277
  %461 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2277
  %opts715 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %461, i32 0, i32 32, !dbg !2278
  %arrayidx716 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts715, i64 0, i64 %idxprom714, !dbg !2277
  %prev_1_is_literal717 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx716, i32 0, i32 1, !dbg !2279
  store i8 0, i8* %prev_1_is_literal717, align 4, !dbg !2280
  br label %if.end718, !dbg !2281

if.end718:                                        ; preds = %if.then696, %for.cond682
  %462 = load i32, i32* %len_test654, align 4, !dbg !2282
  %463 = load i32, i32* %i655, align 4, !dbg !2284
  %idxprom719 = zext i32 %463 to i64, !dbg !2285
  %464 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2285
  %matches720 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %464, i32 0, i32 3, !dbg !2286
  %arrayidx721 = getelementptr inbounds [274 x %struct.lzma_match], [274 x %struct.lzma_match]* %matches720, i64 0, i64 %idxprom719, !dbg !2285
  %len722 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx721, i32 0, i32 0, !dbg !2287
  %465 = load i32, i32* %len722, align 4, !dbg !2287
  %cmp723 = icmp eq i32 %462, %465, !dbg !2288
  br i1 %cmp723, label %if.then725, label %if.end884, !dbg !2289

if.then725:                                       ; preds = %if.end718
  call void @llvm.dbg.declare(metadata i8** %buf_back726, metadata !2290, metadata !305), !dbg !2292
  %466 = load i8*, i8** %buf.addr, align 8, !dbg !2293
  %467 = load i32, i32* %cur_back, align 4, !dbg !2294
  %idx.ext727 = zext i32 %467 to i64, !dbg !2295
  %idx.neg728 = sub i64 0, %idx.ext727, !dbg !2295
  %add.ptr729 = getelementptr inbounds i8, i8* %466, i64 %idx.neg728, !dbg !2295
  %add.ptr730 = getelementptr inbounds i8, i8* %add.ptr729, i64 -1, !dbg !2296
  store i8* %add.ptr730, i8** %buf_back726, align 8, !dbg !2292
  call void @llvm.dbg.declare(metadata i32* %len_test_2731, metadata !2297, metadata !305), !dbg !2298
  %468 = load i32, i32* %len_test654, align 4, !dbg !2299
  %add732 = add i32 %468, 1, !dbg !2300
  store i32 %add732, i32* %len_test_2731, align 4, !dbg !2298
  call void @llvm.dbg.declare(metadata i32* %limit733, metadata !2301, metadata !305), !dbg !2302
  %469 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !2303
  %470 = load i32, i32* %len_test_2731, align 4, !dbg !2303
  %471 = load i32, i32* %nice_len.addr, align 4, !dbg !2303
  %add734 = add i32 %470, %471, !dbg !2303
  %cmp735 = icmp ult i32 %469, %add734, !dbg !2303
  br i1 %cmp735, label %cond.true737, label %cond.false738, !dbg !2303

cond.true737:                                     ; preds = %if.then725
  %472 = load i32, i32* %buf_avail_full.addr, align 4, !dbg !2304
  br label %cond.end740, !dbg !2304

cond.false738:                                    ; preds = %if.then725
  %473 = load i32, i32* %len_test_2731, align 4, !dbg !2306
  %474 = load i32, i32* %nice_len.addr, align 4, !dbg !2306
  %add739 = add i32 %473, %474, !dbg !2306
  br label %cond.end740, !dbg !2306

cond.end740:                                      ; preds = %cond.false738, %cond.true737
  %cond741 = phi i32 [ %472, %cond.true737 ], [ %add739, %cond.false738 ], !dbg !2308
  store i32 %cond741, i32* %limit733, align 4, !dbg !2310
  br label %for.cond742, !dbg !2311

for.cond742:                                      ; preds = %for.inc756, %cond.end740
  %475 = load i32, i32* %len_test_2731, align 4, !dbg !2312
  %476 = load i32, i32* %limit733, align 4, !dbg !2316
  %cmp743 = icmp ult i32 %475, %476, !dbg !2317
  br i1 %cmp743, label %land.rhs745, label %land.end754, !dbg !2318

land.rhs745:                                      ; preds = %for.cond742
  %477 = load i32, i32* %len_test_2731, align 4, !dbg !2319
  %idxprom746 = zext i32 %477 to i64, !dbg !2320
  %478 = load i8*, i8** %buf.addr, align 8, !dbg !2320
  %arrayidx747 = getelementptr inbounds i8, i8* %478, i64 %idxprom746, !dbg !2320
  %479 = load i8, i8* %arrayidx747, align 1, !dbg !2320
  %conv748 = zext i8 %479 to i32, !dbg !2320
  %480 = load i32, i32* %len_test_2731, align 4, !dbg !2321
  %idxprom749 = zext i32 %480 to i64, !dbg !2322
  %481 = load i8*, i8** %buf_back726, align 8, !dbg !2322
  %arrayidx750 = getelementptr inbounds i8, i8* %481, i64 %idxprom749, !dbg !2322
  %482 = load i8, i8* %arrayidx750, align 1, !dbg !2322
  %conv751 = zext i8 %482 to i32, !dbg !2322
  %cmp752 = icmp eq i32 %conv748, %conv751, !dbg !2323
  br label %land.end754

land.end754:                                      ; preds = %land.rhs745, %for.cond742
  %483 = phi i1 [ false, %for.cond742 ], [ %cmp752, %land.rhs745 ]
  br i1 %483, label %for.body755, label %for.end758, !dbg !2324

for.body755:                                      ; preds = %land.end754
  br label %for.inc756, !dbg !2326

for.inc756:                                       ; preds = %for.body755
  %484 = load i32, i32* %len_test_2731, align 4, !dbg !2328
  %inc757 = add i32 %484, 1, !dbg !2328
  store i32 %inc757, i32* %len_test_2731, align 4, !dbg !2328
  br label %for.cond742, !dbg !2329

for.end758:                                       ; preds = %land.end754
  %485 = load i32, i32* %len_test654, align 4, !dbg !2331
  %add759 = add i32 %485, 1, !dbg !2332
  %486 = load i32, i32* %len_test_2731, align 4, !dbg !2333
  %sub760 = sub i32 %486, %add759, !dbg !2333
  store i32 %sub760, i32* %len_test_2731, align 4, !dbg !2333
  %487 = load i32, i32* %len_test_2731, align 4, !dbg !2334
  %cmp761 = icmp uge i32 %487, 2, !dbg !2336
  br i1 %cmp761, label %if.then763, label %if.end878, !dbg !2337

if.then763:                                       ; preds = %for.end758
  call void @llvm.dbg.declare(metadata i32* %pos_state_next764, metadata !2338, metadata !305), !dbg !2340
  call void @llvm.dbg.declare(metadata i32* %cur_and_len_literal_price765, metadata !2341, metadata !305), !dbg !2342
  call void @llvm.dbg.declare(metadata i32* %next_rep_match_price766, metadata !2343, metadata !305), !dbg !2344
  call void @llvm.dbg.declare(metadata i32* %offset767, metadata !2345, metadata !305), !dbg !2346
  call void @llvm.dbg.declare(metadata i32* %state_2768, metadata !2347, metadata !305), !dbg !2348
  %488 = load i32, i32* %state, align 4, !dbg !2349
  store i32 %488, i32* %state_2768, align 4, !dbg !2348
  %489 = load i32, i32* %state_2768, align 4, !dbg !2350
  %cmp769 = icmp ult i32 %489, 7, !dbg !2350
  %cond771 = select i1 %cmp769, i32 7, i32 10, !dbg !2350
  store i32 %cond771, i32* %state_2768, align 4, !dbg !2350
  %490 = load i32, i32* %position.addr, align 4, !dbg !2351
  %491 = load i32, i32* %len_test654, align 4, !dbg !2352
  %add772 = add i32 %490, %491, !dbg !2353
  %492 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2354
  %pos_mask773 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %492, i32 0, i32 9, !dbg !2355
  %493 = load i32, i32* %pos_mask773, align 8, !dbg !2355
  %and774 = and i32 %add772, %493, !dbg !2356
  store i32 %and774, i32* %pos_state_next764, align 4, !dbg !2357
  %494 = load i32, i32* %cur_and_len_price686, align 4, !dbg !2358
  %495 = load i32, i32* %pos_state_next764, align 4, !dbg !2359
  %idxprom775 = zext i32 %495 to i64, !dbg !2360
  %496 = load i32, i32* %state_2768, align 4, !dbg !2361
  %idxprom776 = zext i32 %496 to i64, !dbg !2360
  %497 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2360
  %is_match777 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %497, i32 0, i32 13, !dbg !2362
  %arrayidx778 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match777, i64 0, i64 %idxprom776, !dbg !2360
  %arrayidx779 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx778, i64 0, i64 %idxprom775, !dbg !2360
  %498 = load i16, i16* %arrayidx779, align 2, !dbg !2360
  %call780 = call i32 @rc_bit_0_price(i16 zeroext %498), !dbg !2363
  %add781 = add i32 %494, %call780, !dbg !2364
  %499 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2365
  %500 = load i32, i32* %position.addr, align 4, !dbg !2366
  %501 = load i32, i32* %len_test654, align 4, !dbg !2367
  %add782 = add i32 %500, %501, !dbg !2368
  %502 = load i32, i32* %len_test654, align 4, !dbg !2369
  %sub783 = sub i32 %502, 1, !dbg !2370
  %idxprom784 = zext i32 %sub783 to i64, !dbg !2371
  %503 = load i8*, i8** %buf.addr, align 8, !dbg !2371
  %arrayidx785 = getelementptr inbounds i8, i8* %503, i64 %idxprom784, !dbg !2371
  %504 = load i8, i8* %arrayidx785, align 1, !dbg !2371
  %conv786 = zext i8 %504 to i32, !dbg !2371
  %505 = load i32, i32* %len_test654, align 4, !dbg !2372
  %idxprom787 = zext i32 %505 to i64, !dbg !2373
  %506 = load i8*, i8** %buf_back726, align 8, !dbg !2373
  %arrayidx788 = getelementptr inbounds i8, i8* %506, i64 %idxprom787, !dbg !2373
  %507 = load i8, i8* %arrayidx788, align 1, !dbg !2373
  %conv789 = zext i8 %507 to i32, !dbg !2373
  %508 = load i32, i32* %len_test654, align 4, !dbg !2374
  %idxprom790 = zext i32 %508 to i64, !dbg !2375
  %509 = load i8*, i8** %buf.addr, align 8, !dbg !2375
  %arrayidx791 = getelementptr inbounds i8, i8* %509, i64 %idxprom790, !dbg !2375
  %510 = load i8, i8* %arrayidx791, align 1, !dbg !2375
  %conv792 = zext i8 %510 to i32, !dbg !2375
  %call793 = call i32 @get_literal_price(%struct.lzma_coder_s* %499, i32 %add782, i32 %conv786, i1 zeroext true, i32 %conv789, i32 %conv792), !dbg !2376
  %add794 = add i32 %add781, %call793, !dbg !2377
  store i32 %add794, i32* %cur_and_len_literal_price765, align 4, !dbg !2378
  %511 = load i32, i32* %state_2768, align 4, !dbg !2379
  %cmp795 = icmp ule i32 %511, 3, !dbg !2379
  br i1 %cmp795, label %cond.true797, label %cond.false798, !dbg !2379

cond.true797:                                     ; preds = %if.then763
  br label %cond.end807, !dbg !2380

cond.false798:                                    ; preds = %if.then763
  %512 = load i32, i32* %state_2768, align 4, !dbg !2382
  %cmp799 = icmp ule i32 %512, 9, !dbg !2382
  br i1 %cmp799, label %cond.true801, label %cond.false803, !dbg !2382

cond.true801:                                     ; preds = %cond.false798
  %513 = load i32, i32* %state_2768, align 4, !dbg !2384
  %sub802 = sub i32 %513, 3, !dbg !2384
  br label %cond.end805, !dbg !2384

cond.false803:                                    ; preds = %cond.false798
  %514 = load i32, i32* %state_2768, align 4, !dbg !2386
  %sub804 = sub i32 %514, 6, !dbg !2386
  br label %cond.end805, !dbg !2386

cond.end805:                                      ; preds = %cond.false803, %cond.true801
  %cond806 = phi i32 [ %sub802, %cond.true801 ], [ %sub804, %cond.false803 ], !dbg !2388
  br label %cond.end807, !dbg !2388

cond.end807:                                      ; preds = %cond.end805, %cond.true797
  %cond808 = phi i32 [ 0, %cond.true797 ], [ %cond806, %cond.end805 ], !dbg !2390
  store i32 %cond808, i32* %state_2768, align 4, !dbg !2390
  %515 = load i32, i32* %pos_state_next764, align 4, !dbg !2392
  %add809 = add i32 %515, 1, !dbg !2393
  %516 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2394
  %pos_mask810 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %516, i32 0, i32 9, !dbg !2395
  %517 = load i32, i32* %pos_mask810, align 8, !dbg !2395
  %and811 = and i32 %add809, %517, !dbg !2396
  store i32 %and811, i32* %pos_state_next764, align 4, !dbg !2397
  %518 = load i32, i32* %cur_and_len_literal_price765, align 4, !dbg !2398
  %519 = load i32, i32* %pos_state_next764, align 4, !dbg !2399
  %idxprom812 = zext i32 %519 to i64, !dbg !2400
  %520 = load i32, i32* %state_2768, align 4, !dbg !2401
  %idxprom813 = zext i32 %520 to i64, !dbg !2400
  %521 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2400
  %is_match814 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %521, i32 0, i32 13, !dbg !2402
  %arrayidx815 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match814, i64 0, i64 %idxprom813, !dbg !2400
  %arrayidx816 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx815, i64 0, i64 %idxprom812, !dbg !2400
  %522 = load i16, i16* %arrayidx816, align 2, !dbg !2400
  %call817 = call i32 @rc_bit_1_price(i16 zeroext %522), !dbg !2403
  %add818 = add i32 %518, %call817, !dbg !2404
  %523 = load i32, i32* %state_2768, align 4, !dbg !2405
  %idxprom819 = zext i32 %523 to i64, !dbg !2406
  %524 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2406
  %is_rep820 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %524, i32 0, i32 14, !dbg !2407
  %arrayidx821 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep820, i64 0, i64 %idxprom819, !dbg !2406
  %525 = load i16, i16* %arrayidx821, align 2, !dbg !2406
  %call822 = call i32 @rc_bit_1_price(i16 zeroext %525), !dbg !2408
  %add823 = add i32 %add818, %call822, !dbg !2409
  store i32 %add823, i32* %next_rep_match_price766, align 4, !dbg !2410
  %526 = load i32, i32* %cur.addr, align 4, !dbg !2411
  %527 = load i32, i32* %len_test654, align 4, !dbg !2412
  %add824 = add i32 %526, %527, !dbg !2413
  %add825 = add i32 %add824, 1, !dbg !2414
  %528 = load i32, i32* %len_test_2731, align 4, !dbg !2415
  %add826 = add i32 %add825, %528, !dbg !2416
  store i32 %add826, i32* %offset767, align 4, !dbg !2417
  br label %while.cond827, !dbg !2418

while.cond827:                                    ; preds = %while.body830, %cond.end807
  %529 = load i32, i32* %len_end.addr, align 4, !dbg !2419
  %530 = load i32, i32* %offset767, align 4, !dbg !2420
  %cmp828 = icmp ult i32 %529, %530, !dbg !2421
  br i1 %cmp828, label %while.body830, label %while.end836, !dbg !2422

while.body830:                                    ; preds = %while.cond827
  %531 = load i32, i32* %len_end.addr, align 4, !dbg !2423
  %inc831 = add i32 %531, 1, !dbg !2423
  store i32 %inc831, i32* %len_end.addr, align 4, !dbg !2423
  %idxprom832 = zext i32 %inc831 to i64, !dbg !2424
  %532 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2424
  %opts833 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %532, i32 0, i32 32, !dbg !2425
  %arrayidx834 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts833, i64 0, i64 %idxprom832, !dbg !2424
  %price835 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx834, i32 0, i32 5, !dbg !2426
  store i32 1073741824, i32* %price835, align 4, !dbg !2427
  br label %while.cond827, !dbg !2428

while.end836:                                     ; preds = %while.cond827
  %533 = load i32, i32* %next_rep_match_price766, align 4, !dbg !2429
  %534 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2430
  %535 = load i32, i32* %len_test_2731, align 4, !dbg !2431
  %536 = load i32, i32* %state_2768, align 4, !dbg !2432
  %537 = load i32, i32* %pos_state_next764, align 4, !dbg !2433
  %call837 = call i32 @get_rep_price(%struct.lzma_coder_s* %534, i32 0, i32 %535, i32 %536, i32 %537), !dbg !2434
  %add838 = add i32 %533, %call837, !dbg !2435
  store i32 %add838, i32* %cur_and_len_price686, align 4, !dbg !2436
  %538 = load i32, i32* %cur_and_len_price686, align 4, !dbg !2437
  %539 = load i32, i32* %offset767, align 4, !dbg !2439
  %idxprom839 = zext i32 %539 to i64, !dbg !2440
  %540 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2440
  %opts840 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %540, i32 0, i32 32, !dbg !2441
  %arrayidx841 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts840, i64 0, i64 %idxprom839, !dbg !2440
  %price842 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx841, i32 0, i32 5, !dbg !2442
  %541 = load i32, i32* %price842, align 4, !dbg !2442
  %cmp843 = icmp ult i32 %538, %541, !dbg !2443
  br i1 %cmp843, label %if.then845, label %if.end877, !dbg !2444

if.then845:                                       ; preds = %while.end836
  %542 = load i32, i32* %cur_and_len_price686, align 4, !dbg !2445
  %543 = load i32, i32* %offset767, align 4, !dbg !2447
  %idxprom846 = zext i32 %543 to i64, !dbg !2448
  %544 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2448
  %opts847 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %544, i32 0, i32 32, !dbg !2449
  %arrayidx848 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts847, i64 0, i64 %idxprom846, !dbg !2448
  %price849 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx848, i32 0, i32 5, !dbg !2450
  store i32 %542, i32* %price849, align 4, !dbg !2451
  %545 = load i32, i32* %cur.addr, align 4, !dbg !2452
  %546 = load i32, i32* %len_test654, align 4, !dbg !2453
  %add850 = add i32 %545, %546, !dbg !2454
  %add851 = add i32 %add850, 1, !dbg !2455
  %547 = load i32, i32* %offset767, align 4, !dbg !2456
  %idxprom852 = zext i32 %547 to i64, !dbg !2457
  %548 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2457
  %opts853 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %548, i32 0, i32 32, !dbg !2458
  %arrayidx854 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts853, i64 0, i64 %idxprom852, !dbg !2457
  %pos_prev855 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx854, i32 0, i32 6, !dbg !2459
  store i32 %add851, i32* %pos_prev855, align 4, !dbg !2460
  %549 = load i32, i32* %offset767, align 4, !dbg !2461
  %idxprom856 = zext i32 %549 to i64, !dbg !2462
  %550 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2462
  %opts857 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %550, i32 0, i32 32, !dbg !2463
  %arrayidx858 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts857, i64 0, i64 %idxprom856, !dbg !2462
  %back_prev859 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx858, i32 0, i32 7, !dbg !2464
  store i32 0, i32* %back_prev859, align 4, !dbg !2465
  %551 = load i32, i32* %offset767, align 4, !dbg !2466
  %idxprom860 = zext i32 %551 to i64, !dbg !2467
  %552 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2467
  %opts861 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %552, i32 0, i32 32, !dbg !2468
  %arrayidx862 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts861, i64 0, i64 %idxprom860, !dbg !2467
  %prev_1_is_literal863 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx862, i32 0, i32 1, !dbg !2469
  store i8 1, i8* %prev_1_is_literal863, align 4, !dbg !2470
  %553 = load i32, i32* %offset767, align 4, !dbg !2471
  %idxprom864 = zext i32 %553 to i64, !dbg !2472
  %554 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2472
  %opts865 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %554, i32 0, i32 32, !dbg !2473
  %arrayidx866 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts865, i64 0, i64 %idxprom864, !dbg !2472
  %prev_2867 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx866, i32 0, i32 2, !dbg !2474
  store i8 1, i8* %prev_2867, align 1, !dbg !2475
  %555 = load i32, i32* %cur.addr, align 4, !dbg !2476
  %556 = load i32, i32* %offset767, align 4, !dbg !2477
  %idxprom868 = zext i32 %556 to i64, !dbg !2478
  %557 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2478
  %opts869 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %557, i32 0, i32 32, !dbg !2479
  %arrayidx870 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts869, i64 0, i64 %idxprom868, !dbg !2478
  %pos_prev_2871 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx870, i32 0, i32 3, !dbg !2480
  store i32 %555, i32* %pos_prev_2871, align 4, !dbg !2481
  %558 = load i32, i32* %cur_back, align 4, !dbg !2482
  %add872 = add i32 %558, 4, !dbg !2483
  %559 = load i32, i32* %offset767, align 4, !dbg !2484
  %idxprom873 = zext i32 %559 to i64, !dbg !2485
  %560 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2485
  %opts874 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %560, i32 0, i32 32, !dbg !2486
  %arrayidx875 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts874, i64 0, i64 %idxprom873, !dbg !2485
  %back_prev_2876 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx875, i32 0, i32 4, !dbg !2487
  store i32 %add872, i32* %back_prev_2876, align 4, !dbg !2488
  br label %if.end877, !dbg !2489

if.end877:                                        ; preds = %if.then845, %while.end836
  br label %if.end878, !dbg !2490

if.end878:                                        ; preds = %if.end877, %for.end758
  %561 = load i32, i32* %i655, align 4, !dbg !2491
  %inc879 = add i32 %561, 1, !dbg !2491
  store i32 %inc879, i32* %i655, align 4, !dbg !2491
  %562 = load i32, i32* %matches_count, align 4, !dbg !2493
  %cmp880 = icmp eq i32 %inc879, %562, !dbg !2494
  br i1 %cmp880, label %if.then882, label %if.end883, !dbg !2495

if.then882:                                       ; preds = %if.end878
  br label %for.end887, !dbg !2496

if.end883:                                        ; preds = %if.end878
  br label %if.end884, !dbg !2497

if.end884:                                        ; preds = %if.end883, %if.end718
  br label %for.inc885, !dbg !2498

for.inc885:                                       ; preds = %if.end884
  %563 = load i32, i32* %len_test654, align 4, !dbg !2499
  %inc886 = add i32 %563, 1, !dbg !2499
  store i32 %inc886, i32* %len_test654, align 4, !dbg !2499
  br label %for.cond682, !dbg !2501

for.end887:                                       ; preds = %if.then882
  br label %if.end888, !dbg !2502

if.end888:                                        ; preds = %for.end887, %if.end650
  %564 = load i32, i32* %len_end.addr, align 4, !dbg !2503
  store i32 %564, i32* %retval, align 4, !dbg !2504
  br label %return, !dbg !2504

return:                                           ; preds = %if.end888, %if.then275
  %565 = load i32, i32* %retval, align 4, !dbg !2505
  ret i32 %565, !dbg !2505
}

; Function Attrs: inlinehint nounwind uwtable
define internal i8* @mf_ptr(%struct.lzma_mf_s* %mf) #3 !dbg !290 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !2506, metadata !305), !dbg !2507
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2508
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 0, !dbg !2509
  %1 = load i8*, i8** %buffer, align 8, !dbg !2509
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2510
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !2511
  %3 = load i32, i32* %read_pos, align 8, !dbg !2511
  %idx.ext = zext i32 %3 to i64, !dbg !2512
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !2512
  ret i8* %add.ptr, !dbg !2513
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @mf_avail(%struct.lzma_mf_s* %mf) #3 !dbg !295 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !2514, metadata !305), !dbg !2515
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2516
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 8, !dbg !2517
  %1 = load i32, i32* %write_pos, align 4, !dbg !2517
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2518
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !2519
  %3 = load i32, i32* %read_pos, align 8, !dbg !2519
  %sub = sub i32 %1, %3, !dbg !2520
  ret i32 %sub, !dbg !2521
}

; Function Attrs: nounwind uwtable
define internal void @backward(%struct.lzma_coder_s* noalias %coder, i32* noalias %len_res, i32* noalias %back_res, i32 %cur) #0 !dbg !298 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %len_res.addr = alloca i32*, align 8
  %back_res.addr = alloca i32*, align 8
  %cur.addr = alloca i32, align 4
  %pos_mem = alloca i32, align 4
  %back_mem = alloca i32, align 4
  %pos_prev4 = alloca i32, align 4
  %back_cur = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2522, metadata !305), !dbg !2523
  store i32* %len_res, i32** %len_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %len_res.addr, metadata !2524, metadata !305), !dbg !2525
  store i32* %back_res, i32** %back_res.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %back_res.addr, metadata !2526, metadata !305), !dbg !2527
  store i32 %cur, i32* %cur.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur.addr, metadata !2528, metadata !305), !dbg !2529
  call void @llvm.dbg.declare(metadata i32* %pos_mem, metadata !2530, metadata !305), !dbg !2531
  %0 = load i32, i32* %cur.addr, align 4, !dbg !2532
  %idxprom = zext i32 %0 to i64, !dbg !2533
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2533
  %opts = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 32, !dbg !2534
  %arrayidx = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts, i64 0, i64 %idxprom, !dbg !2533
  %pos_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx, i32 0, i32 6, !dbg !2535
  %2 = load i32, i32* %pos_prev, align 4, !dbg !2535
  store i32 %2, i32* %pos_mem, align 4, !dbg !2531
  call void @llvm.dbg.declare(metadata i32* %back_mem, metadata !2536, metadata !305), !dbg !2537
  %3 = load i32, i32* %cur.addr, align 4, !dbg !2538
  %idxprom1 = zext i32 %3 to i64, !dbg !2539
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2539
  %opts2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 32, !dbg !2540
  %arrayidx3 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts2, i64 0, i64 %idxprom1, !dbg !2539
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx3, i32 0, i32 7, !dbg !2541
  %5 = load i32, i32* %back_prev, align 4, !dbg !2541
  store i32 %5, i32* %back_mem, align 4, !dbg !2537
  %6 = load i32, i32* %cur.addr, align 4, !dbg !2542
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2543
  %opts_end_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 30, !dbg !2544
  store i32 %6, i32* %opts_end_index, align 4, !dbg !2545
  br label %do.body, !dbg !2546

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %pos_prev4, metadata !2547, metadata !305), !dbg !2549
  %8 = load i32, i32* %pos_mem, align 4, !dbg !2550
  store i32 %8, i32* %pos_prev4, align 4, !dbg !2549
  call void @llvm.dbg.declare(metadata i32* %back_cur, metadata !2551, metadata !305), !dbg !2552
  %9 = load i32, i32* %back_mem, align 4, !dbg !2553
  store i32 %9, i32* %back_cur, align 4, !dbg !2552
  %10 = load i32, i32* %cur.addr, align 4, !dbg !2554
  %idxprom5 = zext i32 %10 to i64, !dbg !2556
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2556
  %opts6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 32, !dbg !2557
  %arrayidx7 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts6, i64 0, i64 %idxprom5, !dbg !2556
  %prev_1_is_literal = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx7, i32 0, i32 1, !dbg !2558
  %12 = load i8, i8* %prev_1_is_literal, align 4, !dbg !2558
  %tobool = trunc i8 %12 to i1, !dbg !2558
  br i1 %tobool, label %if.then, label %if.end41, !dbg !2559

if.then:                                          ; preds = %do.body
  %13 = load i32, i32* %pos_mem, align 4, !dbg !2560
  %idxprom8 = zext i32 %13 to i64, !dbg !2562
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2562
  %opts9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 32, !dbg !2563
  %arrayidx10 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts9, i64 0, i64 %idxprom8, !dbg !2562
  call void @make_literal(%struct.lzma_optimal* %arrayidx10), !dbg !2564
  %15 = load i32, i32* %pos_mem, align 4, !dbg !2565
  %sub = sub i32 %15, 1, !dbg !2566
  %16 = load i32, i32* %pos_mem, align 4, !dbg !2567
  %idxprom11 = zext i32 %16 to i64, !dbg !2568
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2568
  %opts12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 32, !dbg !2569
  %arrayidx13 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts12, i64 0, i64 %idxprom11, !dbg !2568
  %pos_prev14 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx13, i32 0, i32 6, !dbg !2570
  store i32 %sub, i32* %pos_prev14, align 4, !dbg !2571
  %18 = load i32, i32* %cur.addr, align 4, !dbg !2572
  %idxprom15 = zext i32 %18 to i64, !dbg !2574
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2574
  %opts16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 32, !dbg !2575
  %arrayidx17 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts16, i64 0, i64 %idxprom15, !dbg !2574
  %prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx17, i32 0, i32 2, !dbg !2576
  %20 = load i8, i8* %prev_2, align 1, !dbg !2576
  %tobool18 = trunc i8 %20 to i1, !dbg !2576
  br i1 %tobool18, label %if.then19, label %if.end, !dbg !2577

if.then19:                                        ; preds = %if.then
  %21 = load i32, i32* %pos_mem, align 4, !dbg !2578
  %sub20 = sub i32 %21, 1, !dbg !2580
  %idxprom21 = zext i32 %sub20 to i64, !dbg !2581
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2581
  %opts22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 32, !dbg !2582
  %arrayidx23 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts22, i64 0, i64 %idxprom21, !dbg !2581
  %prev_1_is_literal24 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx23, i32 0, i32 1, !dbg !2583
  store i8 0, i8* %prev_1_is_literal24, align 4, !dbg !2584
  %23 = load i32, i32* %cur.addr, align 4, !dbg !2585
  %idxprom25 = zext i32 %23 to i64, !dbg !2586
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2586
  %opts26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 32, !dbg !2587
  %arrayidx27 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts26, i64 0, i64 %idxprom25, !dbg !2586
  %pos_prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx27, i32 0, i32 3, !dbg !2588
  %25 = load i32, i32* %pos_prev_2, align 4, !dbg !2588
  %26 = load i32, i32* %pos_mem, align 4, !dbg !2589
  %sub28 = sub i32 %26, 1, !dbg !2590
  %idxprom29 = zext i32 %sub28 to i64, !dbg !2591
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2591
  %opts30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 32, !dbg !2592
  %arrayidx31 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts30, i64 0, i64 %idxprom29, !dbg !2591
  %pos_prev32 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx31, i32 0, i32 6, !dbg !2593
  store i32 %25, i32* %pos_prev32, align 4, !dbg !2594
  %28 = load i32, i32* %cur.addr, align 4, !dbg !2595
  %idxprom33 = zext i32 %28 to i64, !dbg !2596
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2596
  %opts34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 32, !dbg !2597
  %arrayidx35 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts34, i64 0, i64 %idxprom33, !dbg !2596
  %back_prev_2 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx35, i32 0, i32 4, !dbg !2598
  %30 = load i32, i32* %back_prev_2, align 4, !dbg !2598
  %31 = load i32, i32* %pos_mem, align 4, !dbg !2599
  %sub36 = sub i32 %31, 1, !dbg !2600
  %idxprom37 = zext i32 %sub36 to i64, !dbg !2601
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2601
  %opts38 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 32, !dbg !2602
  %arrayidx39 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts38, i64 0, i64 %idxprom37, !dbg !2601
  %back_prev40 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx39, i32 0, i32 7, !dbg !2603
  store i32 %30, i32* %back_prev40, align 4, !dbg !2604
  br label %if.end, !dbg !2605

if.end:                                           ; preds = %if.then19, %if.then
  br label %if.end41, !dbg !2606

if.end41:                                         ; preds = %if.end, %do.body
  %33 = load i32, i32* %pos_prev4, align 4, !dbg !2607
  %idxprom42 = zext i32 %33 to i64, !dbg !2608
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2608
  %opts43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 32, !dbg !2609
  %arrayidx44 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts43, i64 0, i64 %idxprom42, !dbg !2608
  %back_prev45 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx44, i32 0, i32 7, !dbg !2610
  %35 = load i32, i32* %back_prev45, align 4, !dbg !2610
  store i32 %35, i32* %back_mem, align 4, !dbg !2611
  %36 = load i32, i32* %pos_prev4, align 4, !dbg !2612
  %idxprom46 = zext i32 %36 to i64, !dbg !2613
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2613
  %opts47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 32, !dbg !2614
  %arrayidx48 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts47, i64 0, i64 %idxprom46, !dbg !2613
  %pos_prev49 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx48, i32 0, i32 6, !dbg !2615
  %38 = load i32, i32* %pos_prev49, align 4, !dbg !2615
  store i32 %38, i32* %pos_mem, align 4, !dbg !2616
  %39 = load i32, i32* %back_cur, align 4, !dbg !2617
  %40 = load i32, i32* %pos_prev4, align 4, !dbg !2618
  %idxprom50 = zext i32 %40 to i64, !dbg !2619
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2619
  %opts51 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 32, !dbg !2620
  %arrayidx52 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts51, i64 0, i64 %idxprom50, !dbg !2619
  %back_prev53 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx52, i32 0, i32 7, !dbg !2621
  store i32 %39, i32* %back_prev53, align 4, !dbg !2622
  %42 = load i32, i32* %cur.addr, align 4, !dbg !2623
  %43 = load i32, i32* %pos_prev4, align 4, !dbg !2624
  %idxprom54 = zext i32 %43 to i64, !dbg !2625
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2625
  %opts55 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 32, !dbg !2626
  %arrayidx56 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts55, i64 0, i64 %idxprom54, !dbg !2625
  %pos_prev57 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx56, i32 0, i32 6, !dbg !2627
  store i32 %42, i32* %pos_prev57, align 4, !dbg !2628
  %45 = load i32, i32* %pos_prev4, align 4, !dbg !2629
  store i32 %45, i32* %cur.addr, align 4, !dbg !2630
  br label %do.cond, !dbg !2631

do.cond:                                          ; preds = %if.end41
  %46 = load i32, i32* %cur.addr, align 4, !dbg !2632
  %cmp = icmp ne i32 %46, 0, !dbg !2634
  br i1 %cmp, label %do.body, label %do.end, !dbg !2635

do.end:                                           ; preds = %do.cond
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2636
  %opts58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 32, !dbg !2637
  %arrayidx59 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts58, i64 0, i64 0, !dbg !2636
  %pos_prev60 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx59, i32 0, i32 6, !dbg !2638
  %48 = load i32, i32* %pos_prev60, align 4, !dbg !2638
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2639
  %opts_current_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 31, !dbg !2640
  store i32 %48, i32* %opts_current_index, align 8, !dbg !2641
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2642
  %opts61 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 32, !dbg !2643
  %arrayidx62 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts61, i64 0, i64 0, !dbg !2642
  %pos_prev63 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx62, i32 0, i32 6, !dbg !2644
  %51 = load i32, i32* %pos_prev63, align 4, !dbg !2644
  %52 = load i32*, i32** %len_res.addr, align 8, !dbg !2645
  store i32 %51, i32* %52, align 4, !dbg !2646
  %53 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2647
  %opts64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %53, i32 0, i32 32, !dbg !2648
  %arrayidx65 = getelementptr inbounds [4096 x %struct.lzma_optimal], [4096 x %struct.lzma_optimal]* %opts64, i64 0, i64 0, !dbg !2647
  %back_prev66 = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %arrayidx65, i32 0, i32 7, !dbg !2649
  %54 = load i32, i32* %back_prev66, align 4, !dbg !2649
  %55 = load i32*, i32** %back_res.addr, align 8, !dbg !2650
  store i32 %54, i32* %55, align 4, !dbg !2651
  ret void, !dbg !2652
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bittree_price(i16* %probs, i32 %bit_levels, i32 %symbol) #3 !dbg !223 {
entry:
  %probs.addr = alloca i16*, align 8
  %bit_levels.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %price = alloca i32, align 4
  %bit = alloca i32, align 4
  store i16* %probs, i16** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %probs.addr, metadata !2653, metadata !305), !dbg !2654
  store i32 %bit_levels, i32* %bit_levels.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_levels.addr, metadata !2655, metadata !305), !dbg !2656
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2657, metadata !305), !dbg !2658
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2659, metadata !305), !dbg !2660
  store i32 0, i32* %price, align 4, !dbg !2660
  %0 = load i32, i32* %bit_levels.addr, align 4, !dbg !2661
  %shl = shl i32 1, %0, !dbg !2662
  %1 = load i32, i32* %symbol.addr, align 4, !dbg !2663
  %add = add i32 %1, %shl, !dbg !2663
  store i32 %add, i32* %symbol.addr, align 4, !dbg !2663
  br label %do.body, !dbg !2664

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2665, metadata !305), !dbg !2667
  %2 = load i32, i32* %symbol.addr, align 4, !dbg !2668
  %and = and i32 %2, 1, !dbg !2669
  store i32 %and, i32* %bit, align 4, !dbg !2667
  %3 = load i32, i32* %symbol.addr, align 4, !dbg !2670
  %shr = lshr i32 %3, 1, !dbg !2670
  store i32 %shr, i32* %symbol.addr, align 4, !dbg !2670
  %4 = load i32, i32* %symbol.addr, align 4, !dbg !2671
  %idxprom = zext i32 %4 to i64, !dbg !2672
  %5 = load i16*, i16** %probs.addr, align 8, !dbg !2672
  %arrayidx = getelementptr inbounds i16, i16* %5, i64 %idxprom, !dbg !2672
  %6 = load i16, i16* %arrayidx, align 2, !dbg !2672
  %7 = load i32, i32* %bit, align 4, !dbg !2673
  %call = call i32 @rc_bit_price(i16 zeroext %6, i32 %7), !dbg !2674
  %8 = load i32, i32* %price, align 4, !dbg !2675
  %add1 = add i32 %8, %call, !dbg !2675
  store i32 %add1, i32* %price, align 4, !dbg !2675
  br label %do.cond, !dbg !2676

do.cond:                                          ; preds = %do.body
  %9 = load i32, i32* %symbol.addr, align 4, !dbg !2677
  %cmp = icmp ne i32 %9, 1, !dbg !2679
  br i1 %cmp, label %do.body, label %do.end, !dbg !2680

do.end:                                           ; preds = %do.cond
  %10 = load i32, i32* %price, align 4, !dbg !2681
  ret i32 %10, !dbg !2682
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_direct_price(i32 %bits) #3 !dbg !234 {
entry:
  %bits.addr = alloca i32, align 4
  store i32 %bits, i32* %bits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bits.addr, metadata !2683, metadata !305), !dbg !2684
  %0 = load i32, i32* %bits.addr, align 4, !dbg !2685
  %shl = shl i32 %0, 4, !dbg !2686
  ret i32 %shl, !dbg !2687
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pos_slot(i32 %pos) #3 !dbg !237 {
entry:
  %retval = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !2688, metadata !305), !dbg !2689
  %0 = load i32, i32* %pos.addr, align 4, !dbg !2690
  %cmp = icmp ult i32 %0, 8192, !dbg !2692
  br i1 %cmp, label %if.then, label %if.end, !dbg !2693

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %pos.addr, align 4, !dbg !2694
  %idxprom = zext i32 %1 to i64, !dbg !2695
  %arrayidx = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom, !dbg !2695
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2695
  %conv = zext i8 %2 to i32, !dbg !2695
  store i32 %conv, i32* %retval, align 4, !dbg !2696
  br label %return, !dbg !2696

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %pos.addr, align 4, !dbg !2697
  %cmp1 = icmp ult i32 %3, 33554432, !dbg !2699
  br i1 %cmp1, label %if.then3, label %if.end7, !dbg !2700

if.then3:                                         ; preds = %if.end
  %4 = load i32, i32* %pos.addr, align 4, !dbg !2701
  %shr = lshr i32 %4, 12, !dbg !2701
  %idxprom4 = zext i32 %shr to i64, !dbg !2701
  %arrayidx5 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom4, !dbg !2701
  %5 = load i8, i8* %arrayidx5, align 1, !dbg !2701
  %conv6 = zext i8 %5 to i32, !dbg !2701
  %add = add nsw i32 %conv6, 24, !dbg !2701
  store i32 %add, i32* %retval, align 4, !dbg !2702
  br label %return, !dbg !2702

if.end7:                                          ; preds = %if.end
  %6 = load i32, i32* %pos.addr, align 4, !dbg !2703
  %shr8 = lshr i32 %6, 24, !dbg !2703
  %idxprom9 = zext i32 %shr8 to i64, !dbg !2703
  %arrayidx10 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom9, !dbg !2703
  %7 = load i8, i8* %arrayidx10, align 1, !dbg !2703
  %conv11 = zext i8 %7 to i32, !dbg !2703
  %add12 = add nsw i32 %conv11, 48, !dbg !2703
  store i32 %add12, i32* %retval, align 4, !dbg !2704
  br label %return, !dbg !2704

return:                                           ; preds = %if.end7, %if.then3, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2705
  ret i32 %8, !dbg !2705
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bittree_reverse_price(i16* %probs, i32 %bit_levels, i32 %symbol) #3 !dbg !241 {
entry:
  %probs.addr = alloca i16*, align 8
  %bit_levels.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %price = alloca i32, align 4
  %model_index = alloca i32, align 4
  %bit = alloca i32, align 4
  store i16* %probs, i16** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %probs.addr, metadata !2706, metadata !305), !dbg !2707
  store i32 %bit_levels, i32* %bit_levels.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_levels.addr, metadata !2708, metadata !305), !dbg !2709
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2710, metadata !305), !dbg !2711
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2712, metadata !305), !dbg !2713
  store i32 0, i32* %price, align 4, !dbg !2713
  call void @llvm.dbg.declare(metadata i32* %model_index, metadata !2714, metadata !305), !dbg !2715
  store i32 1, i32* %model_index, align 4, !dbg !2715
  br label %do.body, !dbg !2716

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2717, metadata !305), !dbg !2719
  %0 = load i32, i32* %symbol.addr, align 4, !dbg !2720
  %and = and i32 %0, 1, !dbg !2721
  store i32 %and, i32* %bit, align 4, !dbg !2719
  %1 = load i32, i32* %symbol.addr, align 4, !dbg !2722
  %shr = lshr i32 %1, 1, !dbg !2722
  store i32 %shr, i32* %symbol.addr, align 4, !dbg !2722
  %2 = load i32, i32* %model_index, align 4, !dbg !2723
  %idxprom = zext i32 %2 to i64, !dbg !2724
  %3 = load i16*, i16** %probs.addr, align 8, !dbg !2724
  %arrayidx = getelementptr inbounds i16, i16* %3, i64 %idxprom, !dbg !2724
  %4 = load i16, i16* %arrayidx, align 2, !dbg !2724
  %5 = load i32, i32* %bit, align 4, !dbg !2725
  %call = call i32 @rc_bit_price(i16 zeroext %4, i32 %5), !dbg !2726
  %6 = load i32, i32* %price, align 4, !dbg !2727
  %add = add i32 %6, %call, !dbg !2727
  store i32 %add, i32* %price, align 4, !dbg !2727
  %7 = load i32, i32* %model_index, align 4, !dbg !2728
  %shl = shl i32 %7, 1, !dbg !2729
  %8 = load i32, i32* %bit, align 4, !dbg !2730
  %add1 = add i32 %shl, %8, !dbg !2731
  store i32 %add1, i32* %model_index, align 4, !dbg !2732
  br label %do.cond, !dbg !2733

do.cond:                                          ; preds = %do.body
  %9 = load i32, i32* %bit_levels.addr, align 4, !dbg !2734
  %dec = add i32 %9, -1, !dbg !2734
  store i32 %dec, i32* %bit_levels.addr, align 4, !dbg !2734
  %cmp = icmp ne i32 %dec, 0, !dbg !2736
  br i1 %cmp, label %do.body, label %do.end, !dbg !2737

do.end:                                           ; preds = %do.cond
  %10 = load i32, i32* %price, align 4, !dbg !2738
  ret i32 %10, !dbg !2739
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_price(i16 zeroext %prob, i32 %bit) #3 !dbg !231 {
entry:
  %prob.addr = alloca i16, align 2
  %bit.addr = alloca i32, align 4
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2740, metadata !305), !dbg !2741
  store i32 %bit, i32* %bit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit.addr, metadata !2742, metadata !305), !dbg !2743
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2744
  %conv = zext i16 %0 to i32, !dbg !2744
  %1 = load i32, i32* %bit.addr, align 4, !dbg !2745
  %sub = sub i32 0, %1, !dbg !2746
  %and = and i32 %sub, 2047, !dbg !2747
  %xor = xor i32 %conv, %and, !dbg !2748
  %shr = lshr i32 %xor, 4, !dbg !2749
  %idxprom = zext i32 %shr to i64, !dbg !2750
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2750
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2750
  %conv1 = zext i8 %2 to i32, !dbg !2750
  ret i32 %conv1, !dbg !2751
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @mf_skip(%struct.lzma_mf_s* %mf, i32 %amount) #3 !dbg !248 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !2752, metadata !305), !dbg !2753
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !2754, metadata !305), !dbg !2755
  %0 = load i32, i32* %amount.addr, align 4, !dbg !2756
  %cmp = icmp ne i32 %0, 0, !dbg !2758
  br i1 %cmp, label %if.then, label %if.end, !dbg !2759

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2760
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 11, !dbg !2762
  %2 = load void (%struct.lzma_mf_s*, i32)*, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !2762
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2763
  %4 = load i32, i32* %amount.addr, align 4, !dbg !2764
  call void %2(%struct.lzma_mf_s* %3, i32 %4), !dbg !2760
  %5 = load i32, i32* %amount.addr, align 4, !dbg !2765
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2766
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 6, !dbg !2767
  %7 = load i32, i32* %read_ahead, align 4, !dbg !2768
  %add = add i32 %7, %5, !dbg !2768
  store i32 %add, i32* %read_ahead, align 4, !dbg !2768
  br label %if.end, !dbg !2769

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !2770
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_0_price(i16 zeroext %prob) #3 !dbg !249 {
entry:
  %prob.addr = alloca i16, align 2
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2771, metadata !305), !dbg !2772
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2773
  %conv = zext i16 %0 to i32, !dbg !2773
  %shr = ashr i32 %conv, 4, !dbg !2774
  %idxprom = sext i32 %shr to i64, !dbg !2775
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2775
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2775
  %conv1 = zext i8 %1 to i32, !dbg !2775
  ret i32 %conv1, !dbg !2776
}

; Function Attrs: nounwind uwtable
define internal i32 @get_literal_price(%struct.lzma_coder_s* %coder, i32 %pos, i32 %prev_byte, i1 zeroext %match_mode, i32 %match_byte, i32 %symbol) #0 !dbg !252 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %pos.addr = alloca i32, align 4
  %prev_byte.addr = alloca i32, align 4
  %match_mode.addr = alloca i8, align 1
  %match_byte.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %subcoder = alloca i16*, align 8
  %price = alloca i32, align 4
  %offset = alloca i32, align 4
  %match_bit = alloca i32, align 4
  %subcoder_index = alloca i32, align 4
  %bit = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2777, metadata !305), !dbg !2778
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !2779, metadata !305), !dbg !2780
  store i32 %prev_byte, i32* %prev_byte.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %prev_byte.addr, metadata !2781, metadata !305), !dbg !2782
  %frombool = zext i1 %match_mode to i8
  store i8 %frombool, i8* %match_mode.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %match_mode.addr, metadata !2783, metadata !305), !dbg !2784
  store i32 %match_byte, i32* %match_byte.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %match_byte.addr, metadata !2785, metadata !305), !dbg !2786
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2787, metadata !305), !dbg !2788
  call void @llvm.dbg.declare(metadata i16** %subcoder, metadata !2789, metadata !305), !dbg !2790
  %0 = load i32, i32* %pos.addr, align 4, !dbg !2791
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2791
  %literal_pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 11, !dbg !2791
  %2 = load i32, i32* %literal_pos_mask, align 8, !dbg !2791
  %and = and i32 %0, %2, !dbg !2791
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2791
  %literal_context_bits = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 10, !dbg !2791
  %4 = load i32, i32* %literal_context_bits, align 4, !dbg !2791
  %shl = shl i32 %and, %4, !dbg !2791
  %5 = load i32, i32* %prev_byte.addr, align 4, !dbg !2791
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2791
  %literal_context_bits1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 10, !dbg !2791
  %7 = load i32, i32* %literal_context_bits1, align 4, !dbg !2791
  %sub = sub i32 8, %7, !dbg !2791
  %shr = lshr i32 %5, %sub, !dbg !2791
  %add = add i32 %shl, %shr, !dbg !2791
  %idxprom = zext i32 %add to i64, !dbg !2791
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2791
  %literal = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 12, !dbg !2791
  %arrayidx = getelementptr inbounds [16 x [768 x i16]], [16 x [768 x i16]]* %literal, i64 0, i64 %idxprom, !dbg !2791
  %arraydecay = getelementptr inbounds [768 x i16], [768 x i16]* %arrayidx, i32 0, i32 0, !dbg !2791
  store i16* %arraydecay, i16** %subcoder, align 8, !dbg !2790
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2792, metadata !305), !dbg !2793
  store i32 0, i32* %price, align 4, !dbg !2793
  %9 = load i8, i8* %match_mode.addr, align 1, !dbg !2794
  %tobool = trunc i8 %9 to i1, !dbg !2794
  br i1 %tobool, label %if.else, label %if.then, !dbg !2796

if.then:                                          ; preds = %entry
  %10 = load i16*, i16** %subcoder, align 8, !dbg !2797
  %11 = load i32, i32* %symbol.addr, align 4, !dbg !2799
  %call = call i32 @rc_bittree_price(i16* %10, i32 8, i32 %11), !dbg !2800
  store i32 %call, i32* %price, align 4, !dbg !2801
  br label %if.end, !dbg !2802

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %offset, metadata !2803, metadata !305), !dbg !2805
  store i32 256, i32* %offset, align 4, !dbg !2805
  %12 = load i32, i32* %symbol.addr, align 4, !dbg !2806
  %add2 = add i32 %12, 256, !dbg !2806
  store i32 %add2, i32* %symbol.addr, align 4, !dbg !2806
  br label %do.body, !dbg !2807

do.body:                                          ; preds = %do.cond, %if.else
  call void @llvm.dbg.declare(metadata i32* %match_bit, metadata !2808, metadata !305), !dbg !2810
  call void @llvm.dbg.declare(metadata i32* %subcoder_index, metadata !2811, metadata !305), !dbg !2812
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2813, metadata !305), !dbg !2814
  %13 = load i32, i32* %match_byte.addr, align 4, !dbg !2815
  %shl3 = shl i32 %13, 1, !dbg !2815
  store i32 %shl3, i32* %match_byte.addr, align 4, !dbg !2815
  %14 = load i32, i32* %match_byte.addr, align 4, !dbg !2816
  %15 = load i32, i32* %offset, align 4, !dbg !2817
  %and4 = and i32 %14, %15, !dbg !2818
  store i32 %and4, i32* %match_bit, align 4, !dbg !2819
  %16 = load i32, i32* %offset, align 4, !dbg !2820
  %17 = load i32, i32* %match_bit, align 4, !dbg !2821
  %add5 = add i32 %16, %17, !dbg !2822
  %18 = load i32, i32* %symbol.addr, align 4, !dbg !2823
  %shr6 = lshr i32 %18, 8, !dbg !2824
  %add7 = add i32 %add5, %shr6, !dbg !2825
  store i32 %add7, i32* %subcoder_index, align 4, !dbg !2826
  %19 = load i32, i32* %symbol.addr, align 4, !dbg !2827
  %shr8 = lshr i32 %19, 7, !dbg !2828
  %and9 = and i32 %shr8, 1, !dbg !2829
  store i32 %and9, i32* %bit, align 4, !dbg !2830
  %20 = load i32, i32* %subcoder_index, align 4, !dbg !2831
  %idxprom10 = zext i32 %20 to i64, !dbg !2832
  %21 = load i16*, i16** %subcoder, align 8, !dbg !2832
  %arrayidx11 = getelementptr inbounds i16, i16* %21, i64 %idxprom10, !dbg !2832
  %22 = load i16, i16* %arrayidx11, align 2, !dbg !2832
  %23 = load i32, i32* %bit, align 4, !dbg !2833
  %call12 = call i32 @rc_bit_price(i16 zeroext %22, i32 %23), !dbg !2834
  %24 = load i32, i32* %price, align 4, !dbg !2835
  %add13 = add i32 %24, %call12, !dbg !2835
  store i32 %add13, i32* %price, align 4, !dbg !2835
  %25 = load i32, i32* %symbol.addr, align 4, !dbg !2836
  %shl14 = shl i32 %25, 1, !dbg !2836
  store i32 %shl14, i32* %symbol.addr, align 4, !dbg !2836
  %26 = load i32, i32* %match_byte.addr, align 4, !dbg !2837
  %27 = load i32, i32* %symbol.addr, align 4, !dbg !2838
  %xor = xor i32 %26, %27, !dbg !2839
  %neg = xor i32 %xor, -1, !dbg !2840
  %28 = load i32, i32* %offset, align 4, !dbg !2841
  %and15 = and i32 %28, %neg, !dbg !2841
  store i32 %and15, i32* %offset, align 4, !dbg !2841
  br label %do.cond, !dbg !2842

do.cond:                                          ; preds = %do.body
  %29 = load i32, i32* %symbol.addr, align 4, !dbg !2843
  %cmp = icmp ult i32 %29, 65536, !dbg !2845
  br i1 %cmp, label %do.body, label %do.end, !dbg !2846

do.end:                                           ; preds = %do.cond
  br label %if.end

if.end:                                           ; preds = %do.end, %if.then
  %30 = load i32, i32* %price, align 4, !dbg !2847
  ret i32 %30, !dbg !2848
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @make_literal(%struct.lzma_optimal* %optimal) #3 !dbg !259 {
entry:
  %optimal.addr = alloca %struct.lzma_optimal*, align 8
  store %struct.lzma_optimal* %optimal, %struct.lzma_optimal** %optimal.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_optimal** %optimal.addr, metadata !2849, metadata !305), !dbg !2850
  %0 = load %struct.lzma_optimal*, %struct.lzma_optimal** %optimal.addr, align 8, !dbg !2851
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %0, i32 0, i32 7, !dbg !2852
  store i32 -1, i32* %back_prev, align 4, !dbg !2853
  %1 = load %struct.lzma_optimal*, %struct.lzma_optimal** %optimal.addr, align 8, !dbg !2854
  %prev_1_is_literal = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %1, i32 0, i32 1, !dbg !2855
  store i8 0, i8* %prev_1_is_literal, align 4, !dbg !2856
  ret void, !dbg !2857
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_1_price(i16 zeroext %prob) #3 !dbg !263 {
entry:
  %prob.addr = alloca i16, align 2
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2858, metadata !305), !dbg !2859
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2860
  %conv = zext i16 %0 to i32, !dbg !2860
  %xor = xor i32 %conv, 2047, !dbg !2861
  %shr = lshr i32 %xor, 4, !dbg !2862
  %idxprom = zext i32 %shr to i64, !dbg !2863
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2863
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2863
  %conv1 = zext i8 %1 to i32, !dbg !2863
  ret i32 %conv1, !dbg !2864
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_short_rep_price(%struct.lzma_coder_s* %coder, i32 %state, i32 %pos_state) #3 !dbg !264 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %state.addr = alloca i32, align 4
  %pos_state.addr = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2865, metadata !305), !dbg !2866
  store i32 %state, i32* %state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %state.addr, metadata !2867, metadata !305), !dbg !2868
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2869, metadata !305), !dbg !2870
  %0 = load i32, i32* %state.addr, align 4, !dbg !2871
  %idxprom = zext i32 %0 to i64, !dbg !2872
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2872
  %is_rep0 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 15, !dbg !2873
  %arrayidx = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep0, i64 0, i64 %idxprom, !dbg !2872
  %2 = load i16, i16* %arrayidx, align 2, !dbg !2872
  %call = call i32 @rc_bit_0_price(i16 zeroext %2), !dbg !2874
  %3 = load i32, i32* %pos_state.addr, align 4, !dbg !2875
  %idxprom1 = zext i32 %3 to i64, !dbg !2876
  %4 = load i32, i32* %state.addr, align 4, !dbg !2877
  %idxprom2 = zext i32 %4 to i64, !dbg !2876
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2876
  %is_rep0_long = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 18, !dbg !2878
  %arrayidx3 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_rep0_long, i64 0, i64 %idxprom2, !dbg !2876
  %arrayidx4 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx3, i64 0, i64 %idxprom1, !dbg !2876
  %6 = load i16, i16* %arrayidx4, align 2, !dbg !2876
  %call5 = call i32 @rc_bit_0_price(i16 zeroext %6), !dbg !2879
  %add = add i32 %call, %call5, !dbg !2880
  ret i32 %add, !dbg !2881
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @make_short_rep(%struct.lzma_optimal* %optimal) #3 !dbg !268 {
entry:
  %optimal.addr = alloca %struct.lzma_optimal*, align 8
  store %struct.lzma_optimal* %optimal, %struct.lzma_optimal** %optimal.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_optimal** %optimal.addr, metadata !2882, metadata !305), !dbg !2883
  %0 = load %struct.lzma_optimal*, %struct.lzma_optimal** %optimal.addr, align 8, !dbg !2884
  %back_prev = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %0, i32 0, i32 7, !dbg !2885
  store i32 0, i32* %back_prev, align 4, !dbg !2886
  %1 = load %struct.lzma_optimal*, %struct.lzma_optimal** %optimal.addr, align 8, !dbg !2887
  %prev_1_is_literal = getelementptr inbounds %struct.lzma_optimal, %struct.lzma_optimal* %1, i32 0, i32 1, !dbg !2888
  store i8 0, i8* %prev_1_is_literal, align 4, !dbg !2889
  ret void, !dbg !2890
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pure_rep_price(%struct.lzma_coder_s* %coder, i32 %rep_index, i32 %state, i32 %pos_state) #3 !dbg !269 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %rep_index.addr = alloca i32, align 4
  %state.addr = alloca i32, align 4
  %pos_state.addr = alloca i32, align 4
  %price = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2891, metadata !305), !dbg !2892
  store i32 %rep_index, i32* %rep_index.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rep_index.addr, metadata !2893, metadata !305), !dbg !2894
  store i32 %state, i32* %state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %state.addr, metadata !2895, metadata !305), !dbg !2896
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2897, metadata !305), !dbg !2898
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2899, metadata !305), !dbg !2900
  %0 = load i32, i32* %rep_index.addr, align 4, !dbg !2901
  %cmp = icmp eq i32 %0, 0, !dbg !2903
  br i1 %cmp, label %if.then, label %if.else, !dbg !2904

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %state.addr, align 4, !dbg !2905
  %idxprom = zext i32 %1 to i64, !dbg !2907
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2907
  %is_rep0 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 15, !dbg !2908
  %arrayidx = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep0, i64 0, i64 %idxprom, !dbg !2907
  %3 = load i16, i16* %arrayidx, align 2, !dbg !2907
  %call = call i32 @rc_bit_0_price(i16 zeroext %3), !dbg !2909
  store i32 %call, i32* %price, align 4, !dbg !2910
  %4 = load i32, i32* %pos_state.addr, align 4, !dbg !2911
  %idxprom1 = zext i32 %4 to i64, !dbg !2912
  %5 = load i32, i32* %state.addr, align 4, !dbg !2913
  %idxprom2 = zext i32 %5 to i64, !dbg !2912
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2912
  %is_rep0_long = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 18, !dbg !2914
  %arrayidx3 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_rep0_long, i64 0, i64 %idxprom2, !dbg !2912
  %arrayidx4 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx3, i64 0, i64 %idxprom1, !dbg !2912
  %7 = load i16, i16* %arrayidx4, align 2, !dbg !2912
  %call5 = call i32 @rc_bit_1_price(i16 zeroext %7), !dbg !2915
  %8 = load i32, i32* %price, align 4, !dbg !2916
  %add = add i32 %8, %call5, !dbg !2916
  store i32 %add, i32* %price, align 4, !dbg !2916
  br label %if.end26, !dbg !2917

if.else:                                          ; preds = %entry
  %9 = load i32, i32* %state.addr, align 4, !dbg !2918
  %idxprom6 = zext i32 %9 to i64, !dbg !2920
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2920
  %is_rep07 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 15, !dbg !2921
  %arrayidx8 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep07, i64 0, i64 %idxprom6, !dbg !2920
  %11 = load i16, i16* %arrayidx8, align 2, !dbg !2920
  %call9 = call i32 @rc_bit_1_price(i16 zeroext %11), !dbg !2922
  store i32 %call9, i32* %price, align 4, !dbg !2923
  %12 = load i32, i32* %rep_index.addr, align 4, !dbg !2924
  %cmp10 = icmp eq i32 %12, 1, !dbg !2926
  br i1 %cmp10, label %if.then11, label %if.else16, !dbg !2927

if.then11:                                        ; preds = %if.else
  %13 = load i32, i32* %state.addr, align 4, !dbg !2928
  %idxprom12 = zext i32 %13 to i64, !dbg !2930
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2930
  %is_rep1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 16, !dbg !2931
  %arrayidx13 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep1, i64 0, i64 %idxprom12, !dbg !2930
  %15 = load i16, i16* %arrayidx13, align 2, !dbg !2930
  %call14 = call i32 @rc_bit_0_price(i16 zeroext %15), !dbg !2932
  %16 = load i32, i32* %price, align 4, !dbg !2933
  %add15 = add i32 %16, %call14, !dbg !2933
  store i32 %add15, i32* %price, align 4, !dbg !2933
  br label %if.end, !dbg !2934

if.else16:                                        ; preds = %if.else
  %17 = load i32, i32* %state.addr, align 4, !dbg !2935
  %idxprom17 = zext i32 %17 to i64, !dbg !2937
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2937
  %is_rep118 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 16, !dbg !2938
  %arrayidx19 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep118, i64 0, i64 %idxprom17, !dbg !2937
  %19 = load i16, i16* %arrayidx19, align 2, !dbg !2937
  %call20 = call i32 @rc_bit_1_price(i16 zeroext %19), !dbg !2939
  %20 = load i32, i32* %price, align 4, !dbg !2940
  %add21 = add i32 %20, %call20, !dbg !2940
  store i32 %add21, i32* %price, align 4, !dbg !2940
  %21 = load i32, i32* %state.addr, align 4, !dbg !2941
  %idxprom22 = zext i32 %21 to i64, !dbg !2942
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2942
  %is_rep2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 17, !dbg !2943
  %arrayidx23 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep2, i64 0, i64 %idxprom22, !dbg !2942
  %23 = load i16, i16* %arrayidx23, align 2, !dbg !2942
  %24 = load i32, i32* %rep_index.addr, align 4, !dbg !2944
  %sub = sub i32 %24, 2, !dbg !2945
  %call24 = call i32 @rc_bit_price(i16 zeroext %23, i32 %sub), !dbg !2946
  %25 = load i32, i32* %price, align 4, !dbg !2947
  %add25 = add i32 %25, %call24, !dbg !2947
  store i32 %add25, i32* %price, align 4, !dbg !2947
  br label %if.end

if.end:                                           ; preds = %if.else16, %if.then11
  br label %if.end26

if.end26:                                         ; preds = %if.end, %if.then
  %26 = load i32, i32* %price, align 4, !dbg !2948
  ret i32 %26, !dbg !2949
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_len_price(%struct.lzma_length_encoder* %lencoder, i32 %len, i32 %pos_state) #3 !dbg !272 {
entry:
  %lencoder.addr = alloca %struct.lzma_length_encoder*, align 8
  %len.addr = alloca i32, align 4
  %pos_state.addr = alloca i32, align 4
  store %struct.lzma_length_encoder* %lencoder, %struct.lzma_length_encoder** %lencoder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_length_encoder** %lencoder.addr, metadata !2950, metadata !305), !dbg !2951
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2952, metadata !305), !dbg !2953
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2954, metadata !305), !dbg !2955
  %0 = load i32, i32* %len.addr, align 4, !dbg !2956
  %sub = sub i32 %0, 2, !dbg !2957
  %idxprom = zext i32 %sub to i64, !dbg !2958
  %1 = load i32, i32* %pos_state.addr, align 4, !dbg !2959
  %idxprom1 = zext i32 %1 to i64, !dbg !2958
  %2 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !2958
  %prices = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %2, i32 0, i32 5, !dbg !2960
  %arrayidx = getelementptr inbounds [16 x [272 x i32]], [16 x [272 x i32]]* %prices, i64 0, i64 %idxprom1, !dbg !2958
  %arrayidx2 = getelementptr inbounds [272 x i32], [272 x i32]* %arrayidx, i64 0, i64 %idxprom, !dbg !2958
  %3 = load i32, i32* %arrayidx2, align 4, !dbg !2958
  ret i32 %3, !dbg !2961
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pos_len_price(%struct.lzma_coder_s* %coder, i32 %pos, i32 %len, i32 %pos_state) #3 !dbg !278 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %pos.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %pos_state.addr = alloca i32, align 4
  %len_to_pos_state = alloca i32, align 4
  %price = alloca i32, align 4
  %pos_slot = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2962, metadata !305), !dbg !2963
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !2964, metadata !305), !dbg !2965
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2966, metadata !305), !dbg !2967
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2968, metadata !305), !dbg !2969
  call void @llvm.dbg.declare(metadata i32* %len_to_pos_state, metadata !2970, metadata !305), !dbg !2971
  %0 = load i32, i32* %len.addr, align 4, !dbg !2972
  %cmp = icmp ult i32 %0, 6, !dbg !2972
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2972

cond.true:                                        ; preds = %entry
  %1 = load i32, i32* %len.addr, align 4, !dbg !2973
  %sub = sub i32 %1, 2, !dbg !2973
  br label %cond.end, !dbg !2973

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !2975

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %sub, %cond.true ], [ 3, %cond.false ], !dbg !2977
  store i32 %cond, i32* %len_to_pos_state, align 4, !dbg !2979
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2980, metadata !305), !dbg !2981
  %2 = load i32, i32* %pos.addr, align 4, !dbg !2982
  %cmp1 = icmp ult i32 %2, 128, !dbg !2984
  br i1 %cmp1, label %if.then, label %if.else, !dbg !2985

if.then:                                          ; preds = %cond.end
  %3 = load i32, i32* %pos.addr, align 4, !dbg !2986
  %idxprom = zext i32 %3 to i64, !dbg !2988
  %4 = load i32, i32* %len_to_pos_state, align 4, !dbg !2989
  %idxprom2 = zext i32 %4 to i64, !dbg !2988
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2988
  %distances_prices = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 25, !dbg !2990
  %arrayidx = getelementptr inbounds [4 x [128 x i32]], [4 x [128 x i32]]* %distances_prices, i64 0, i64 %idxprom2, !dbg !2988
  %arrayidx3 = getelementptr inbounds [128 x i32], [128 x i32]* %arrayidx, i64 0, i64 %idxprom, !dbg !2988
  %6 = load i32, i32* %arrayidx3, align 4, !dbg !2988
  store i32 %6, i32* %price, align 4, !dbg !2991
  br label %if.end, !dbg !2992

if.else:                                          ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i32* %pos_slot, metadata !2993, metadata !305), !dbg !2995
  %7 = load i32, i32* %pos.addr, align 4, !dbg !2996
  %call = call i32 @get_pos_slot_2(i32 %7), !dbg !2997
  store i32 %call, i32* %pos_slot, align 4, !dbg !2995
  %8 = load i32, i32* %pos_slot, align 4, !dbg !2998
  %idxprom4 = zext i32 %8 to i64, !dbg !2999
  %9 = load i32, i32* %len_to_pos_state, align 4, !dbg !3000
  %idxprom5 = zext i32 %9 to i64, !dbg !2999
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2999
  %pos_slot_prices = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 24, !dbg !3001
  %arrayidx6 = getelementptr inbounds [4 x [64 x i32]], [4 x [64 x i32]]* %pos_slot_prices, i64 0, i64 %idxprom5, !dbg !2999
  %arrayidx7 = getelementptr inbounds [64 x i32], [64 x i32]* %arrayidx6, i64 0, i64 %idxprom4, !dbg !2999
  %11 = load i32, i32* %arrayidx7, align 4, !dbg !2999
  %12 = load i32, i32* %pos.addr, align 4, !dbg !3002
  %and = and i32 %12, 15, !dbg !3003
  %idxprom8 = zext i32 %and to i64, !dbg !3004
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !3004
  %align_prices = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 28, !dbg !3005
  %arrayidx9 = getelementptr inbounds [16 x i32], [16 x i32]* %align_prices, i64 0, i64 %idxprom8, !dbg !3004
  %14 = load i32, i32* %arrayidx9, align 4, !dbg !3004
  %add = add i32 %11, %14, !dbg !3006
  store i32 %add, i32* %price, align 4, !dbg !3007
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !3008
  %match_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 22, !dbg !3009
  %16 = load i32, i32* %len.addr, align 4, !dbg !3010
  %17 = load i32, i32* %pos_state.addr, align 4, !dbg !3011
  %call10 = call i32 @get_len_price(%struct.lzma_length_encoder* %match_len_encoder, i32 %16, i32 %17), !dbg !3012
  %18 = load i32, i32* %price, align 4, !dbg !3013
  %add11 = add i32 %18, %call10, !dbg !3013
  store i32 %add11, i32* %price, align 4, !dbg !3013
  %19 = load i32, i32* %price, align 4, !dbg !3014
  ret i32 %19, !dbg !3015
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pos_slot_2(i32 %pos) #3 !dbg !281 {
entry:
  %retval = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !3016, metadata !305), !dbg !3017
  %0 = load i32, i32* %pos.addr, align 4, !dbg !3018
  %cmp = icmp uge i32 %0, 128, !dbg !3018
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3018

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !3019

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.5, i32 0, i32 0), i32 128, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.get_pos_slot_2, i32 0, i32 0)) #6, !dbg !3021
  unreachable, !dbg !3021
                                                  ; No predecessors!
  br label %cond.end, !dbg !3023

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %pos.addr, align 4, !dbg !3025
  %cmp1 = icmp ult i32 %2, 524288, !dbg !3027
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3028

if.then:                                          ; preds = %cond.end
  %3 = load i32, i32* %pos.addr, align 4, !dbg !3029
  %shr = lshr i32 %3, 6, !dbg !3029
  %idxprom = zext i32 %shr to i64, !dbg !3029
  %arrayidx = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom, !dbg !3029
  %4 = load i8, i8* %arrayidx, align 1, !dbg !3029
  %conv = zext i8 %4 to i32, !dbg !3029
  %add = add nsw i32 %conv, 12, !dbg !3029
  store i32 %add, i32* %retval, align 4, !dbg !3030
  br label %return, !dbg !3030

if.end:                                           ; preds = %cond.end
  %5 = load i32, i32* %pos.addr, align 4, !dbg !3031
  %cmp2 = icmp ult i32 %5, -2147483648, !dbg !3033
  br i1 %cmp2, label %if.then4, label %if.end10, !dbg !3034

if.then4:                                         ; preds = %if.end
  %6 = load i32, i32* %pos.addr, align 4, !dbg !3035
  %shr5 = lshr i32 %6, 18, !dbg !3035
  %idxprom6 = zext i32 %shr5 to i64, !dbg !3035
  %arrayidx7 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom6, !dbg !3035
  %7 = load i8, i8* %arrayidx7, align 1, !dbg !3035
  %conv8 = zext i8 %7 to i32, !dbg !3035
  %add9 = add nsw i32 %conv8, 36, !dbg !3035
  store i32 %add9, i32* %retval, align 4, !dbg !3036
  br label %return, !dbg !3036

if.end10:                                         ; preds = %if.end
  %8 = load i32, i32* %pos.addr, align 4, !dbg !3037
  %shr11 = lshr i32 %8, 30, !dbg !3037
  %idxprom12 = zext i32 %shr11 to i64, !dbg !3037
  %arrayidx13 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom12, !dbg !3037
  %9 = load i8, i8* %arrayidx13, align 1, !dbg !3037
  %conv14 = zext i8 %9 to i32, !dbg !3037
  %add15 = add nsw i32 %conv14, 60, !dbg !3037
  store i32 %add15, i32* %retval, align 4, !dbg !3038
  br label %return, !dbg !3038

return:                                           ; preds = %if.end10, %if.then4, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !3039
  ret i32 %10, !dbg !3039
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_rep_price(%struct.lzma_coder_s* %coder, i32 %rep_index, i32 %len, i32 %state, i32 %pos_state) #3 !dbg !287 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %rep_index.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %state.addr = alloca i32, align 4
  %pos_state.addr = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !3040, metadata !305), !dbg !3041
  store i32 %rep_index, i32* %rep_index.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rep_index.addr, metadata !3042, metadata !305), !dbg !3043
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !3044, metadata !305), !dbg !3045
  store i32 %state, i32* %state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %state.addr, metadata !3046, metadata !305), !dbg !3047
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !3048, metadata !305), !dbg !3049
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !3050
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 23, !dbg !3051
  %1 = load i32, i32* %len.addr, align 4, !dbg !3052
  %2 = load i32, i32* %pos_state.addr, align 4, !dbg !3053
  %call = call i32 @get_len_price(%struct.lzma_length_encoder* %rep_len_encoder, i32 %1, i32 %2), !dbg !3054
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !3055
  %4 = load i32, i32* %rep_index.addr, align 4, !dbg !3056
  %5 = load i32, i32* %state.addr, align 4, !dbg !3057
  %6 = load i32, i32* %pos_state.addr, align 4, !dbg !3058
  %call1 = call i32 @get_pure_rep_price(%struct.lzma_coder_s* %3, i32 %4, i32 %5, i32 %6), !dbg !3059
  %add = add i32 %call, %call1, !dbg !3060
  ret i32 %add, !dbg !3061
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!301, !302}
!llvm.ident = !{!303}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !61, subprograms: !64)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_optimum_normal.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!64 = !{!65, !220, !223, !231, !234, !237, !241, !244, !245, !248, !249, !252, !259, !263, !264, !268, !269, !272, !278, !281, !282, !287, !290, !295, !298}
!65 = distinct !DISubprogram(name: "lzma_lzma_optimum_normal", scope: !1, file: !1, line: 868, type: !66, isLocal: false, isDefinition: true, scopeLine: 871, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!66 = !DISubroutineType(types: !67)
!67 = !{null, !68, !180, !218, !218, !13}
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
!220 = distinct !DISubprogram(name: "fill_distances_prices", scope: !1, file: !1, line: 135, type: !221, isLocal: true, isDefinition: true, scopeLine: 136, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!221 = !DISubroutineType(types: !222)
!222 = !{null, !69}
!223 = distinct !DISubprogram(name: "rc_bittree_price", scope: !224, file: !224, line: 52, type: !225, isLocal: true, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!224 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/price.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!225 = !DISubroutineType(types: !226)
!226 = !{!13, !227, !230, !13}
!227 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !228)
!228 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!229 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !29)
!230 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!231 = distinct !DISubprogram(name: "rc_bit_price", scope: !224, file: !224, line: 29, type: !232, isLocal: true, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!232 = !DISubroutineType(types: !233)
!233 = !{!13, !229, !230}
!234 = distinct !DISubprogram(name: "rc_direct_price", scope: !224, file: !224, line: 87, type: !235, isLocal: true, isDefinition: true, scopeLine: 88, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!235 = !DISubroutineType(types: !236)
!236 = !{!13, !230}
!237 = distinct !DISubprogram(name: "get_pos_slot", scope: !238, file: !238, line: 110, type: !239, isLocal: true, isDefinition: true, scopeLine: 111, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!238 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/fastpos.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!239 = !DISubroutineType(types: !240)
!240 = !{!13, !13}
!241 = distinct !DISubprogram(name: "rc_bittree_reverse_price", scope: !224, file: !224, line: 69, type: !242, isLocal: true, isDefinition: true, scopeLine: 71, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!242 = !DISubroutineType(types: !243)
!243 = !{!13, !227, !13, !13}
!244 = distinct !DISubprogram(name: "fill_align_prices", scope: !1, file: !1, line: 196, type: !221, isLocal: true, isDefinition: true, scopeLine: 197, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!245 = distinct !DISubprogram(name: "helper1", scope: !1, file: !1, line: 281, type: !246, isLocal: true, isDefinition: true, scopeLine: 284, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!246 = !DISubroutineType(types: !247)
!247 = !{!13, !68, !180, !218, !218, !13}
!248 = distinct !DISubprogram(name: "mf_skip", scope: !86, file: !86, line: 268, type: !203, isLocal: true, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!249 = distinct !DISubprogram(name: "rc_bit_0_price", scope: !224, file: !224, line: 37, type: !250, isLocal: true, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!250 = !DISubroutineType(types: !251)
!251 = !{!13, !229}
!252 = distinct !DISubprogram(name: "get_literal_price", scope: !1, file: !1, line: 21, type: !253, isLocal: true, isDefinition: true, scopeLine: 24, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!253 = !DISubroutineType(types: !254)
!254 = !{!13, !255, !230, !230, !258, !13, !13}
!255 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !256)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !70)
!258 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !96)
!259 = distinct !DISubprogram(name: "make_literal", scope: !1, file: !1, line: 213, type: !260, isLocal: true, isDefinition: true, scopeLine: 214, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!260 = !DISubroutineType(types: !261)
!261 = !{null, !262}
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!263 = distinct !DISubprogram(name: "rc_bit_1_price", scope: !224, file: !224, line: 44, type: !250, isLocal: true, isDefinition: true, scopeLine: 45, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!264 = distinct !DISubprogram(name: "get_short_rep_price", scope: !1, file: !1, line: 70, type: !265, isLocal: true, isDefinition: true, scopeLine: 72, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!265 = !DISubroutineType(types: !266)
!266 = !{!13, !255, !267, !230}
!267 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !78)
!268 = distinct !DISubprogram(name: "make_short_rep", scope: !1, file: !1, line: 221, type: !260, isLocal: true, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!269 = distinct !DISubprogram(name: "get_pure_rep_price", scope: !1, file: !1, line: 79, type: !270, isLocal: true, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!270 = !DISubroutineType(types: !271)
!271 = !{!13, !255, !230, !267, !13}
!272 = distinct !DISubprogram(name: "get_len_price", scope: !1, file: !1, line: 60, type: !273, isLocal: true, isDefinition: true, scopeLine: 62, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!273 = !DISubroutineType(types: !274)
!274 = !{!13, !275, !230, !230}
!275 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !276)
!276 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !130)
!278 = distinct !DISubprogram(name: "get_pos_len_price", scope: !1, file: !1, line: 114, type: !279, isLocal: true, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!279 = !DISubroutineType(types: !280)
!280 = !{!13, !255, !230, !230, !230}
!281 = distinct !DISubprogram(name: "get_pos_slot_2", scope: !238, file: !238, line: 126, type: !239, isLocal: true, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!282 = distinct !DISubprogram(name: "helper2", scope: !1, file: !1, line: 476, type: !283, isLocal: true, isDefinition: true, scopeLine: 479, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!283 = !DISubroutineType(types: !284)
!284 = !{!13, !69, !206, !285, !13, !13, !230, !230, !230}
!285 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !286, size: 64, align: 64)
!286 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!287 = distinct !DISubprogram(name: "get_rep_price", scope: !1, file: !1, line: 104, type: !288, isLocal: true, isDefinition: true, scopeLine: 107, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!288 = !DISubroutineType(types: !289)
!289 = !{!13, !255, !230, !230, !267, !230}
!290 = distinct !DISubprogram(name: "mf_ptr", scope: !86, file: !86, line: 222, type: !291, isLocal: true, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!291 = !DISubroutineType(types: !292)
!292 = !{!186, !293}
!293 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !294, size: 64, align: 64)
!294 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !182)
!295 = distinct !DISubprogram(name: "mf_avail", scope: !86, file: !86, line: 230, type: !296, isLocal: true, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!296 = !DISubroutineType(types: !297)
!297 = !{!13, !293}
!298 = distinct !DISubprogram(name: "backward", scope: !1, file: !1, line: 233, type: !299, isLocal: true, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !219)
!299 = !DISubroutineType(types: !300)
!300 = !{null, !68, !218, !218, !13}
!301 = !{i32 2, !"Dwarf Version", i32 4}
!302 = !{i32 2, !"Debug Info Version", i32 3}
!303 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!304 = !DILocalVariable(name: "coder", arg: 1, scope: !65, file: !1, line: 868, type: !68)
!305 = !DIExpression()
!306 = !DILocation(line: 868, column: 52, scope: !65)
!307 = !DILocalVariable(name: "mf", arg: 2, scope: !65, file: !1, line: 868, type: !180)
!308 = !DILocation(line: 868, column: 82, scope: !65)
!309 = !DILocalVariable(name: "back_res", arg: 3, scope: !65, file: !1, line: 869, type: !218)
!310 = !DILocation(line: 869, column: 27, scope: !65)
!311 = !DILocalVariable(name: "len_res", arg: 4, scope: !65, file: !1, line: 869, type: !218)
!312 = !DILocation(line: 869, column: 61, scope: !65)
!313 = !DILocalVariable(name: "position", arg: 5, scope: !65, file: !1, line: 870, type: !13)
!314 = !DILocation(line: 870, column: 12, scope: !65)
!315 = !DILocalVariable(name: "reps", scope: !65, file: !1, line: 872, type: !80)
!316 = !DILocation(line: 872, column: 11, scope: !65)
!317 = !DILocalVariable(name: "len_end", scope: !65, file: !1, line: 873, type: !13)
!318 = !DILocation(line: 873, column: 11, scope: !65)
!319 = !DILocalVariable(name: "cur", scope: !65, file: !1, line: 874, type: !13)
!320 = !DILocation(line: 874, column: 11, scope: !65)
!321 = !DILocation(line: 877, column: 6, scope: !322)
!322 = distinct !DILexicalBlock(scope: !65, file: !1, line: 877, column: 6)
!323 = !DILocation(line: 877, column: 13, scope: !322)
!324 = !DILocation(line: 877, column: 31, scope: !322)
!325 = !DILocation(line: 877, column: 38, scope: !322)
!326 = !DILocation(line: 877, column: 28, scope: !322)
!327 = !DILocation(line: 877, column: 6, scope: !65)
!328 = !DILocation(line: 878, column: 3, scope: !329)
!329 = distinct !DILexicalBlock(scope: !322, file: !1, line: 877, column: 58)
!330 = !DILocation(line: 878, column: 3, scope: !331)
!331 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 1)
!332 = !DILocation(line: 878, column: 3, scope: !333)
!333 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 2)
!334 = !DILocation(line: 878, column: 3, scope: !335)
!335 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 3)
!336 = !DILocation(line: 879, column: 26, scope: !329)
!337 = !DILocation(line: 879, column: 33, scope: !329)
!338 = !DILocation(line: 879, column: 14, scope: !329)
!339 = !DILocation(line: 879, column: 21, scope: !329)
!340 = !DILocation(line: 879, column: 53, scope: !329)
!341 = !DILocation(line: 880, column: 7, scope: !329)
!342 = !DILocation(line: 880, column: 14, scope: !329)
!343 = !DILocation(line: 880, column: 5, scope: !329)
!344 = !DILocation(line: 879, column: 4, scope: !329)
!345 = !DILocation(line: 879, column: 12, scope: !329)
!346 = !DILocation(line: 881, column: 27, scope: !329)
!347 = !DILocation(line: 881, column: 34, scope: !329)
!348 = !DILocation(line: 881, column: 15, scope: !329)
!349 = !DILocation(line: 881, column: 22, scope: !329)
!350 = !DILocation(line: 881, column: 54, scope: !329)
!351 = !DILocation(line: 881, column: 4, scope: !329)
!352 = !DILocation(line: 881, column: 13, scope: !329)
!353 = !DILocation(line: 883, column: 5, scope: !329)
!354 = !DILocation(line: 883, column: 12, scope: !329)
!355 = !DILocation(line: 882, column: 31, scope: !329)
!356 = !DILocation(line: 882, column: 38, scope: !329)
!357 = !DILocation(line: 883, column: 32, scope: !329)
!358 = !DILocation(line: 882, column: 3, scope: !329)
!359 = !DILocation(line: 882, column: 10, scope: !329)
!360 = !DILocation(line: 882, column: 29, scope: !329)
!361 = !DILocation(line: 884, column: 3, scope: !329)
!362 = !DILocation(line: 890, column: 6, scope: !363)
!363 = distinct !DILexicalBlock(scope: !65, file: !1, line: 890, column: 6)
!364 = !DILocation(line: 890, column: 10, scope: !363)
!365 = !DILocation(line: 890, column: 21, scope: !363)
!366 = !DILocation(line: 890, column: 6, scope: !65)
!367 = !DILocation(line: 891, column: 7, scope: !368)
!368 = distinct !DILexicalBlock(scope: !369, file: !1, line: 891, column: 7)
!369 = distinct !DILexicalBlock(scope: !363, file: !1, line: 890, column: 27)
!370 = !DILocation(line: 891, column: 14, scope: !368)
!371 = !DILocation(line: 891, column: 32, scope: !368)
!372 = !DILocation(line: 891, column: 7, scope: !369)
!373 = !DILocation(line: 892, column: 26, scope: !368)
!374 = !DILocation(line: 892, column: 4, scope: !368)
!375 = !DILocation(line: 894, column: 7, scope: !376)
!376 = distinct !DILexicalBlock(scope: !369, file: !1, line: 894, column: 7)
!377 = !DILocation(line: 894, column: 14, scope: !376)
!378 = !DILocation(line: 894, column: 32, scope: !376)
!379 = !DILocation(line: 894, column: 7, scope: !369)
!380 = !DILocation(line: 895, column: 22, scope: !376)
!381 = !DILocation(line: 895, column: 4, scope: !376)
!382 = !DILocation(line: 896, column: 2, scope: !369)
!383 = !DILocation(line: 902, column: 20, scope: !65)
!384 = !DILocation(line: 902, column: 27, scope: !65)
!385 = !DILocation(line: 902, column: 31, scope: !65)
!386 = !DILocation(line: 902, column: 41, scope: !65)
!387 = !DILocation(line: 902, column: 50, scope: !65)
!388 = !DILocation(line: 902, column: 12, scope: !65)
!389 = !DILocation(line: 902, column: 10, scope: !65)
!390 = !DILocation(line: 903, column: 6, scope: !391)
!391 = distinct !DILexicalBlock(scope: !65, file: !1, line: 903, column: 6)
!392 = !DILocation(line: 903, column: 14, scope: !391)
!393 = !DILocation(line: 903, column: 6, scope: !65)
!394 = !DILocation(line: 904, column: 3, scope: !391)
!395 = !DILocation(line: 907, column: 2, scope: !65)
!396 = !DILocation(line: 907, column: 15, scope: !65)
!397 = !DILocation(line: 907, column: 22, scope: !65)
!398 = !DILocation(line: 909, column: 11, scope: !399)
!399 = distinct !DILexicalBlock(scope: !65, file: !1, line: 909, column: 2)
!400 = !DILocation(line: 909, column: 7, scope: !399)
!401 = !DILocation(line: 909, column: 16, scope: !402)
!402 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 1)
!403 = distinct !DILexicalBlock(scope: !399, file: !1, line: 909, column: 2)
!404 = !DILocation(line: 909, column: 22, scope: !402)
!405 = !DILocation(line: 909, column: 20, scope: !402)
!406 = !DILocation(line: 909, column: 2, scope: !402)
!407 = !DILocation(line: 910, column: 3, scope: !408)
!408 = distinct !DILexicalBlock(scope: !403, file: !1, line: 909, column: 38)
!409 = !DILocation(line: 910, column: 3, scope: !410)
!410 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 1)
!411 = !DILocation(line: 910, column: 3, scope: !412)
!412 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 2)
!413 = !DILocation(line: 910, column: 3, scope: !414)
!414 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 3)
!415 = !DILocation(line: 913, column: 5, scope: !408)
!416 = !DILocation(line: 913, column: 10, scope: !408)
!417 = !DILocation(line: 913, column: 17, scope: !408)
!418 = !DILocation(line: 913, column: 32, scope: !408)
!419 = !DILocation(line: 913, column: 39, scope: !408)
!420 = !DILocation(line: 912, column: 33, scope: !408)
!421 = !DILocation(line: 912, column: 3, scope: !408)
!422 = !DILocation(line: 912, column: 10, scope: !408)
!423 = !DILocation(line: 912, column: 31, scope: !408)
!424 = !DILocation(line: 915, column: 7, scope: !425)
!425 = distinct !DILexicalBlock(scope: !408, file: !1, line: 915, column: 7)
!426 = !DILocation(line: 915, column: 14, scope: !425)
!427 = !DILocation(line: 915, column: 38, scope: !425)
!428 = !DILocation(line: 915, column: 42, scope: !425)
!429 = !DILocation(line: 915, column: 35, scope: !425)
!430 = !DILocation(line: 915, column: 7, scope: !408)
!431 = !DILocation(line: 916, column: 4, scope: !425)
!432 = !DILocation(line: 918, column: 21, scope: !408)
!433 = !DILocation(line: 918, column: 28, scope: !408)
!434 = !DILocation(line: 918, column: 41, scope: !408)
!435 = !DILocation(line: 918, column: 34, scope: !408)
!436 = !DILocation(line: 918, column: 45, scope: !408)
!437 = !DILocation(line: 918, column: 50, scope: !408)
!438 = !DILocation(line: 919, column: 5, scope: !408)
!439 = !DILocation(line: 919, column: 16, scope: !408)
!440 = !DILocation(line: 919, column: 14, scope: !408)
!441 = !DILocation(line: 919, column: 21, scope: !408)
!442 = !DILocation(line: 919, column: 26, scope: !408)
!443 = !DILocation(line: 919, column: 30, scope: !408)
!444 = !DILocation(line: 920, column: 5, scope: !408)
!445 = !DILocation(line: 920, column: 5, scope: !410)
!446 = !DILocation(line: 920, column: 5, scope: !412)
!447 = !DILocation(line: 920, column: 5, scope: !414)
!448 = !DILocation(line: 918, column: 13, scope: !410)
!449 = !DILocation(line: 918, column: 11, scope: !410)
!450 = !DILocation(line: 921, column: 2, scope: !408)
!451 = !DILocation(line: 909, column: 31, scope: !452)
!452 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 2)
!453 = !DILocation(line: 909, column: 2, scope: !452)
!454 = !DILocation(line: 923, column: 11, scope: !65)
!455 = !DILocation(line: 923, column: 18, scope: !65)
!456 = !DILocation(line: 923, column: 27, scope: !65)
!457 = !DILocation(line: 923, column: 37, scope: !65)
!458 = !DILocation(line: 923, column: 2, scope: !65)
!459 = !DILocation(line: 924, column: 2, scope: !65)
!460 = !DILocation(line: 925, column: 1, scope: !65)
!461 = !DILocalVariable(name: "coder", arg: 1, scope: !220, file: !1, line: 135, type: !69)
!462 = !DILocation(line: 135, column: 35, scope: !220)
!463 = !DILocalVariable(name: "len_to_pos_state", scope: !220, file: !1, line: 137, type: !13)
!464 = !DILocation(line: 137, column: 11, scope: !220)
!465 = !DILocalVariable(name: "pos_slot", scope: !220, file: !1, line: 138, type: !13)
!466 = !DILocation(line: 138, column: 11, scope: !220)
!467 = !DILocalVariable(name: "i", scope: !220, file: !1, line: 139, type: !13)
!468 = !DILocation(line: 139, column: 11, scope: !220)
!469 = !DILocation(line: 141, column: 24, scope: !470)
!470 = distinct !DILexicalBlock(scope: !220, file: !1, line: 141, column: 2)
!471 = !DILocation(line: 141, column: 7, scope: !470)
!472 = !DILocation(line: 142, column: 4, scope: !473)
!473 = distinct !DILexicalBlock(scope: !470, file: !1, line: 141, column: 2)
!474 = !DILocation(line: 142, column: 21, scope: !473)
!475 = !DILocation(line: 141, column: 2, scope: !476)
!476 = !DILexicalBlockFile(scope: !470, file: !1, discriminator: 1)
!477 = !DILocalVariable(name: "pos_slot_prices", scope: !478, file: !1, line: 145, type: !479)
!478 = distinct !DILexicalBlock(scope: !473, file: !1, line: 143, column: 24)
!479 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !206)
!480 = !DILocation(line: 145, column: 19, scope: !478)
!481 = !DILocation(line: 146, column: 30, scope: !478)
!482 = !DILocation(line: 146, column: 7, scope: !478)
!483 = !DILocation(line: 146, column: 14, scope: !478)
!484 = !DILocation(line: 149, column: 17, scope: !485)
!485 = distinct !DILexicalBlock(scope: !478, file: !1, line: 149, column: 3)
!486 = !DILocation(line: 149, column: 8, scope: !485)
!487 = !DILocation(line: 150, column: 5, scope: !488)
!488 = distinct !DILexicalBlock(scope: !485, file: !1, line: 149, column: 3)
!489 = !DILocation(line: 150, column: 16, scope: !488)
!490 = !DILocation(line: 150, column: 23, scope: !488)
!491 = !DILocation(line: 150, column: 14, scope: !488)
!492 = !DILocation(line: 149, column: 3, scope: !493)
!493 = !DILexicalBlockFile(scope: !485, file: !1, discriminator: 1)
!494 = !DILocation(line: 152, column: 22, scope: !488)
!495 = !DILocation(line: 152, column: 6, scope: !488)
!496 = !DILocation(line: 152, column: 13, scope: !488)
!497 = !DILocation(line: 153, column: 21, scope: !488)
!498 = !DILocation(line: 151, column: 32, scope: !488)
!499 = !DILocation(line: 151, column: 20, scope: !488)
!500 = !DILocation(line: 151, column: 4, scope: !488)
!501 = !DILocation(line: 151, column: 30, scope: !488)
!502 = !DILocation(line: 150, column: 40, scope: !503)
!503 = !DILexicalBlockFile(scope: !488, file: !1, discriminator: 1)
!504 = !DILocation(line: 149, column: 3, scope: !505)
!505 = !DILexicalBlockFile(scope: !488, file: !1, discriminator: 2)
!506 = !DILocation(line: 158, column: 17, scope: !507)
!507 = distinct !DILexicalBlock(scope: !478, file: !1, line: 158, column: 3)
!508 = !DILocation(line: 158, column: 8, scope: !507)
!509 = !DILocation(line: 159, column: 5, scope: !510)
!510 = distinct !DILexicalBlock(scope: !507, file: !1, line: 158, column: 3)
!511 = !DILocation(line: 159, column: 16, scope: !510)
!512 = !DILocation(line: 159, column: 23, scope: !510)
!513 = !DILocation(line: 159, column: 14, scope: !510)
!514 = !DILocation(line: 158, column: 3, scope: !515)
!515 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 1)
!516 = !DILocation(line: 161, column: 8, scope: !510)
!517 = !DILocation(line: 161, column: 17, scope: !510)
!518 = !DILocation(line: 161, column: 23, scope: !510)
!519 = !DILocation(line: 161, column: 28, scope: !510)
!520 = !DILocation(line: 160, column: 33, scope: !510)
!521 = !DILocation(line: 160, column: 20, scope: !510)
!522 = !DILocation(line: 160, column: 4, scope: !510)
!523 = !DILocation(line: 160, column: 30, scope: !510)
!524 = !DILocation(line: 159, column: 40, scope: !525)
!525 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 1)
!526 = !DILocation(line: 158, column: 3, scope: !527)
!527 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 2)
!528 = !DILocation(line: 166, column: 10, scope: !529)
!529 = distinct !DILexicalBlock(scope: !478, file: !1, line: 166, column: 3)
!530 = !DILocation(line: 166, column: 8, scope: !529)
!531 = !DILocation(line: 166, column: 15, scope: !532)
!532 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!533 = distinct !DILexicalBlock(scope: !529, file: !1, line: 166, column: 3)
!534 = !DILocation(line: 166, column: 17, scope: !532)
!535 = !DILocation(line: 166, column: 3, scope: !532)
!536 = !DILocation(line: 168, column: 24, scope: !533)
!537 = !DILocation(line: 168, column: 8, scope: !533)
!538 = !DILocation(line: 167, column: 46, scope: !533)
!539 = !DILocation(line: 167, column: 4, scope: !533)
!540 = !DILocation(line: 167, column: 28, scope: !533)
!541 = !DILocation(line: 167, column: 11, scope: !533)
!542 = !DILocation(line: 168, column: 6, scope: !533)
!543 = !DILocation(line: 166, column: 42, scope: !544)
!544 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 2)
!545 = !DILocation(line: 166, column: 3, scope: !544)
!546 = !DILocation(line: 169, column: 2, scope: !478)
!547 = !DILocation(line: 143, column: 4, scope: !473)
!548 = !DILocation(line: 141, column: 2, scope: !549)
!549 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 2)
!550 = !DILocation(line: 174, column: 9, scope: !551)
!551 = distinct !DILexicalBlock(scope: !220, file: !1, line: 174, column: 2)
!552 = !DILocation(line: 174, column: 7, scope: !551)
!553 = !DILocation(line: 174, column: 34, scope: !554)
!554 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 1)
!555 = distinct !DILexicalBlock(scope: !551, file: !1, line: 174, column: 2)
!556 = !DILocation(line: 174, column: 36, scope: !554)
!557 = !DILocation(line: 174, column: 2, scope: !554)
!558 = !DILocalVariable(name: "pos_slot", scope: !559, file: !1, line: 175, type: !230)
!559 = distinct !DILexicalBlock(scope: !555, file: !1, line: 174, column: 59)
!560 = !DILocation(line: 175, column: 18, scope: !559)
!561 = !DILocation(line: 175, column: 42, scope: !559)
!562 = !DILocation(line: 175, column: 29, scope: !559)
!563 = !DILocalVariable(name: "footer_bits", scope: !559, file: !1, line: 176, type: !230)
!564 = !DILocation(line: 176, column: 18, scope: !559)
!565 = !DILocation(line: 176, column: 34, scope: !559)
!566 = !DILocation(line: 176, column: 43, scope: !559)
!567 = !DILocation(line: 176, column: 49, scope: !559)
!568 = !DILocalVariable(name: "base", scope: !559, file: !1, line: 177, type: !230)
!569 = !DILocation(line: 177, column: 18, scope: !559)
!570 = !DILocation(line: 177, column: 31, scope: !559)
!571 = !DILocation(line: 177, column: 40, scope: !559)
!572 = !DILocation(line: 177, column: 28, scope: !559)
!573 = !DILocation(line: 177, column: 49, scope: !559)
!574 = !DILocation(line: 177, column: 46, scope: !559)
!575 = !DILocalVariable(name: "price", scope: !559, file: !1, line: 178, type: !230)
!576 = !DILocation(line: 178, column: 18, scope: !559)
!577 = !DILocation(line: 179, column: 5, scope: !559)
!578 = !DILocation(line: 179, column: 12, scope: !559)
!579 = !DILocation(line: 179, column: 26, scope: !559)
!580 = !DILocation(line: 179, column: 24, scope: !559)
!581 = !DILocation(line: 179, column: 33, scope: !559)
!582 = !DILocation(line: 179, column: 31, scope: !559)
!583 = !DILocation(line: 179, column: 42, scope: !559)
!584 = !DILocation(line: 180, column: 5, scope: !559)
!585 = !DILocation(line: 180, column: 18, scope: !559)
!586 = !DILocation(line: 180, column: 22, scope: !559)
!587 = !DILocation(line: 180, column: 20, scope: !559)
!588 = !DILocation(line: 178, column: 26, scope: !559)
!589 = !DILocation(line: 182, column: 25, scope: !590)
!590 = distinct !DILexicalBlock(scope: !559, file: !1, line: 182, column: 3)
!591 = !DILocation(line: 182, column: 8, scope: !590)
!592 = !DILocation(line: 183, column: 5, scope: !593)
!593 = distinct !DILexicalBlock(scope: !590, file: !1, line: 182, column: 3)
!594 = !DILocation(line: 183, column: 22, scope: !593)
!595 = !DILocation(line: 182, column: 3, scope: !596)
!596 = !DILexicalBlockFile(scope: !590, file: !1, discriminator: 1)
!597 = !DILocation(line: 186, column: 8, scope: !593)
!598 = !DILocation(line: 187, column: 25, scope: !593)
!599 = !DILocation(line: 186, column: 16, scope: !593)
!600 = !DILocation(line: 187, column: 7, scope: !593)
!601 = !DILocation(line: 186, column: 23, scope: !593)
!602 = !DILocation(line: 186, column: 14, scope: !593)
!603 = !DILocation(line: 185, column: 46, scope: !593)
!604 = !DILocation(line: 185, column: 4, scope: !593)
!605 = !DILocation(line: 185, column: 28, scope: !593)
!606 = !DILocation(line: 185, column: 11, scope: !593)
!607 = !DILocation(line: 186, column: 6, scope: !593)
!608 = !DILocation(line: 184, column: 5, scope: !593)
!609 = !DILocation(line: 182, column: 3, scope: !610)
!610 = !DILexicalBlockFile(scope: !593, file: !1, discriminator: 2)
!611 = !DILocation(line: 188, column: 2, scope: !559)
!612 = !DILocation(line: 174, column: 54, scope: !613)
!613 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 2)
!614 = !DILocation(line: 174, column: 2, scope: !613)
!615 = !DILocation(line: 190, column: 2, scope: !220)
!616 = !DILocation(line: 190, column: 9, scope: !220)
!617 = !DILocation(line: 190, column: 27, scope: !220)
!618 = !DILocation(line: 191, column: 2, scope: !220)
!619 = !DILocalVariable(name: "coder", arg: 1, scope: !244, file: !1, line: 196, type: !69)
!620 = !DILocation(line: 196, column: 31, scope: !244)
!621 = !DILocalVariable(name: "i", scope: !244, file: !1, line: 198, type: !13)
!622 = !DILocation(line: 198, column: 11, scope: !244)
!623 = !DILocation(line: 199, column: 9, scope: !624)
!624 = distinct !DILexicalBlock(scope: !244, file: !1, line: 199, column: 2)
!625 = !DILocation(line: 199, column: 7, scope: !624)
!626 = !DILocation(line: 199, column: 14, scope: !627)
!627 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 1)
!628 = distinct !DILexicalBlock(scope: !624, file: !1, line: 199, column: 2)
!629 = !DILocation(line: 199, column: 16, scope: !627)
!630 = !DILocation(line: 199, column: 2, scope: !627)
!631 = !DILocation(line: 201, column: 5, scope: !628)
!632 = !DILocation(line: 201, column: 12, scope: !628)
!633 = !DILocation(line: 201, column: 35, scope: !628)
!634 = !DILocation(line: 200, column: 28, scope: !628)
!635 = !DILocation(line: 200, column: 23, scope: !628)
!636 = !DILocation(line: 200, column: 3, scope: !628)
!637 = !DILocation(line: 200, column: 10, scope: !628)
!638 = !DILocation(line: 200, column: 26, scope: !628)
!639 = !DILocation(line: 199, column: 36, scope: !640)
!640 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 2)
!641 = !DILocation(line: 199, column: 2, scope: !640)
!642 = !DILocation(line: 203, column: 2, scope: !244)
!643 = !DILocation(line: 203, column: 9, scope: !244)
!644 = !DILocation(line: 203, column: 27, scope: !244)
!645 = !DILocation(line: 204, column: 2, scope: !244)
!646 = !DILocalVariable(name: "coder", arg: 1, scope: !245, file: !1, line: 281, type: !68)
!647 = !DILocation(line: 281, column: 35, scope: !245)
!648 = !DILocalVariable(name: "mf", arg: 2, scope: !245, file: !1, line: 281, type: !180)
!649 = !DILocation(line: 281, column: 65, scope: !245)
!650 = !DILocalVariable(name: "back_res", arg: 3, scope: !245, file: !1, line: 282, type: !218)
!651 = !DILocation(line: 282, column: 27, scope: !245)
!652 = !DILocalVariable(name: "len_res", arg: 4, scope: !245, file: !1, line: 282, type: !218)
!653 = !DILocation(line: 282, column: 61, scope: !245)
!654 = !DILocalVariable(name: "position", arg: 5, scope: !245, file: !1, line: 283, type: !13)
!655 = !DILocation(line: 283, column: 12, scope: !245)
!656 = !DILocalVariable(name: "buf_avail", scope: !245, file: !1, line: 285, type: !13)
!657 = !DILocation(line: 285, column: 11, scope: !245)
!658 = !DILocalVariable(name: "buf", scope: !245, file: !1, line: 286, type: !285)
!659 = !DILocation(line: 286, column: 17, scope: !245)
!660 = !DILocalVariable(name: "rep_lens", scope: !245, file: !1, line: 287, type: !80)
!661 = !DILocation(line: 287, column: 11, scope: !245)
!662 = !DILocalVariable(name: "rep_max_index", scope: !245, file: !1, line: 288, type: !13)
!663 = !DILocation(line: 288, column: 11, scope: !245)
!664 = !DILocalVariable(name: "i", scope: !245, file: !1, line: 289, type: !13)
!665 = !DILocation(line: 289, column: 11, scope: !245)
!666 = !DILocalVariable(name: "current_byte", scope: !245, file: !1, line: 291, type: !16)
!667 = !DILocation(line: 291, column: 10, scope: !245)
!668 = !DILocalVariable(name: "match_byte", scope: !245, file: !1, line: 292, type: !16)
!669 = !DILocation(line: 292, column: 10, scope: !245)
!670 = !DILocalVariable(name: "pos_state", scope: !245, file: !1, line: 294, type: !13)
!671 = !DILocation(line: 294, column: 11, scope: !245)
!672 = !DILocalVariable(name: "match_price", scope: !245, file: !1, line: 295, type: !13)
!673 = !DILocation(line: 295, column: 11, scope: !245)
!674 = !DILocalVariable(name: "rep_match_price", scope: !245, file: !1, line: 296, type: !13)
!675 = !DILocation(line: 296, column: 11, scope: !245)
!676 = !DILocalVariable(name: "len_end", scope: !245, file: !1, line: 297, type: !13)
!677 = !DILocation(line: 297, column: 11, scope: !245)
!678 = !DILocalVariable(name: "len", scope: !245, file: !1, line: 298, type: !13)
!679 = !DILocation(line: 298, column: 11, scope: !245)
!680 = !DILocalVariable(name: "normal_match_price", scope: !245, file: !1, line: 300, type: !13)
!681 = !DILocation(line: 300, column: 11, scope: !245)
!682 = !DILocalVariable(name: "nice_len", scope: !245, file: !1, line: 302, type: !230)
!683 = !DILocation(line: 302, column: 17, scope: !245)
!684 = !DILocation(line: 302, column: 28, scope: !245)
!685 = !DILocation(line: 302, column: 32, scope: !245)
!686 = !DILocalVariable(name: "len_main", scope: !245, file: !1, line: 304, type: !13)
!687 = !DILocation(line: 304, column: 11, scope: !245)
!688 = !DILocalVariable(name: "matches_count", scope: !245, file: !1, line: 305, type: !13)
!689 = !DILocation(line: 305, column: 11, scope: !245)
!690 = !DILocation(line: 307, column: 6, scope: !691)
!691 = distinct !DILexicalBlock(scope: !245, file: !1, line: 307, column: 6)
!692 = !DILocation(line: 307, column: 10, scope: !691)
!693 = !DILocation(line: 307, column: 21, scope: !691)
!694 = !DILocation(line: 307, column: 6, scope: !245)
!695 = !DILocation(line: 308, column: 22, scope: !696)
!696 = distinct !DILexicalBlock(scope: !691, file: !1, line: 307, column: 27)
!697 = !DILocation(line: 308, column: 42, scope: !696)
!698 = !DILocation(line: 308, column: 49, scope: !696)
!699 = !DILocation(line: 308, column: 14, scope: !696)
!700 = !DILocation(line: 308, column: 12, scope: !696)
!701 = !DILocation(line: 309, column: 2, scope: !696)
!702 = !DILocation(line: 310, column: 3, scope: !703)
!703 = distinct !DILexicalBlock(scope: !691, file: !1, line: 309, column: 9)
!704 = !DILocation(line: 310, column: 3, scope: !705)
!705 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 1)
!706 = !DILocation(line: 310, column: 3, scope: !707)
!707 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 2)
!708 = !DILocation(line: 310, column: 3, scope: !709)
!709 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 3)
!710 = !DILocation(line: 311, column: 14, scope: !703)
!711 = !DILocation(line: 311, column: 21, scope: !703)
!712 = !DILocation(line: 311, column: 12, scope: !703)
!713 = !DILocation(line: 312, column: 19, scope: !703)
!714 = !DILocation(line: 312, column: 26, scope: !703)
!715 = !DILocation(line: 312, column: 17, scope: !703)
!716 = !DILocation(line: 315, column: 14, scope: !245)
!717 = !DILocation(line: 315, column: 14, scope: !718)
!718 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 1)
!719 = !DILocation(line: 315, column: 14, scope: !720)
!720 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 2)
!721 = !DILocation(line: 315, column: 14, scope: !722)
!722 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 3)
!723 = !DILocation(line: 315, column: 12, scope: !722)
!724 = !DILocation(line: 316, column: 6, scope: !725)
!725 = distinct !DILexicalBlock(scope: !245, file: !1, line: 316, column: 6)
!726 = !DILocation(line: 316, column: 16, scope: !725)
!727 = !DILocation(line: 316, column: 6, scope: !245)
!728 = !DILocation(line: 317, column: 4, scope: !729)
!729 = distinct !DILexicalBlock(scope: !725, file: !1, line: 316, column: 21)
!730 = !DILocation(line: 317, column: 13, scope: !729)
!731 = !DILocation(line: 318, column: 4, scope: !729)
!732 = !DILocation(line: 318, column: 12, scope: !729)
!733 = !DILocation(line: 319, column: 3, scope: !729)
!734 = !DILocation(line: 322, column: 15, scope: !245)
!735 = !DILocation(line: 322, column: 8, scope: !245)
!736 = !DILocation(line: 322, column: 19, scope: !245)
!737 = !DILocation(line: 322, column: 6, scope: !245)
!738 = !DILocation(line: 324, column: 9, scope: !739)
!739 = distinct !DILexicalBlock(scope: !245, file: !1, line: 324, column: 2)
!740 = !DILocation(line: 324, column: 7, scope: !739)
!741 = !DILocation(line: 324, column: 14, scope: !742)
!742 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 1)
!743 = distinct !DILexicalBlock(scope: !739, file: !1, line: 324, column: 2)
!744 = !DILocation(line: 324, column: 16, scope: !742)
!745 = !DILocation(line: 324, column: 2, scope: !742)
!746 = !DILocalVariable(name: "len_test", scope: !747, file: !1, line: 325, type: !13)
!747 = distinct !DILexicalBlock(scope: !743, file: !1, line: 324, column: 38)
!748 = !DILocation(line: 325, column: 12, scope: !747)
!749 = !DILocalVariable(name: "buf_back", scope: !747, file: !1, line: 327, type: !750)
!750 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !285)
!751 = !DILocation(line: 327, column: 24, scope: !747)
!752 = !DILocation(line: 327, column: 35, scope: !747)
!753 = !DILocation(line: 327, column: 53, scope: !747)
!754 = !DILocation(line: 327, column: 41, scope: !747)
!755 = !DILocation(line: 327, column: 48, scope: !747)
!756 = !DILocation(line: 327, column: 39, scope: !747)
!757 = !DILocation(line: 327, column: 56, scope: !747)
!758 = !DILocation(line: 329, column: 7, scope: !759)
!759 = distinct !DILexicalBlock(scope: !747, file: !1, line: 329, column: 7)
!760 = !DILocation(line: 329, column: 7, scope: !747)
!761 = !DILocation(line: 330, column: 13, scope: !762)
!762 = distinct !DILexicalBlock(scope: !759, file: !1, line: 329, column: 36)
!763 = !DILocation(line: 330, column: 4, scope: !762)
!764 = !DILocation(line: 330, column: 16, scope: !762)
!765 = !DILocation(line: 331, column: 4, scope: !762)
!766 = !DILocation(line: 334, column: 17, scope: !767)
!767 = distinct !DILexicalBlock(scope: !747, file: !1, line: 334, column: 3)
!768 = !DILocation(line: 334, column: 8, scope: !767)
!769 = !DILocation(line: 334, column: 22, scope: !770)
!770 = !DILexicalBlockFile(scope: !771, file: !1, discriminator: 1)
!771 = distinct !DILexicalBlock(scope: !767, file: !1, line: 334, column: 3)
!772 = !DILocation(line: 334, column: 33, scope: !770)
!773 = !DILocation(line: 334, column: 31, scope: !770)
!774 = !DILocation(line: 335, column: 5, scope: !771)
!775 = !DILocation(line: 335, column: 12, scope: !770)
!776 = !DILocation(line: 335, column: 8, scope: !770)
!777 = !DILocation(line: 335, column: 34, scope: !770)
!778 = !DILocation(line: 335, column: 25, scope: !770)
!779 = !DILocation(line: 335, column: 22, scope: !770)
!780 = !DILocation(line: 334, column: 3, scope: !781)
!781 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 2)
!782 = !DILocation(line: 334, column: 3, scope: !783)
!783 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 3)
!784 = !DILocation(line: 336, column: 5, scope: !771)
!785 = !DILocation(line: 334, column: 3, scope: !786)
!786 = !DILexicalBlockFile(scope: !771, file: !1, discriminator: 4)
!787 = !DILocation(line: 338, column: 17, scope: !747)
!788 = !DILocation(line: 338, column: 12, scope: !747)
!789 = !DILocation(line: 338, column: 3, scope: !747)
!790 = !DILocation(line: 338, column: 15, scope: !747)
!791 = !DILocation(line: 339, column: 7, scope: !792)
!792 = distinct !DILexicalBlock(scope: !747, file: !1, line: 339, column: 7)
!793 = !DILocation(line: 339, column: 27, scope: !792)
!794 = !DILocation(line: 339, column: 18, scope: !792)
!795 = !DILocation(line: 339, column: 16, scope: !792)
!796 = !DILocation(line: 339, column: 7, scope: !747)
!797 = !DILocation(line: 340, column: 20, scope: !792)
!798 = !DILocation(line: 340, column: 18, scope: !792)
!799 = !DILocation(line: 340, column: 4, scope: !792)
!800 = !DILocation(line: 341, column: 2, scope: !747)
!801 = !DILocation(line: 324, column: 33, scope: !802)
!802 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 2)
!803 = !DILocation(line: 324, column: 2, scope: !802)
!804 = !DILocation(line: 343, column: 15, scope: !805)
!805 = distinct !DILexicalBlock(scope: !245, file: !1, line: 343, column: 6)
!806 = !DILocation(line: 343, column: 6, scope: !805)
!807 = !DILocation(line: 343, column: 33, scope: !805)
!808 = !DILocation(line: 343, column: 30, scope: !805)
!809 = !DILocation(line: 343, column: 6, scope: !245)
!810 = !DILocation(line: 344, column: 15, scope: !811)
!811 = distinct !DILexicalBlock(scope: !805, file: !1, line: 343, column: 43)
!812 = !DILocation(line: 344, column: 4, scope: !811)
!813 = !DILocation(line: 344, column: 13, scope: !811)
!814 = !DILocation(line: 345, column: 23, scope: !811)
!815 = !DILocation(line: 345, column: 14, scope: !811)
!816 = !DILocation(line: 345, column: 4, scope: !811)
!817 = !DILocation(line: 345, column: 12, scope: !811)
!818 = !DILocation(line: 346, column: 11, scope: !811)
!819 = !DILocation(line: 346, column: 16, scope: !811)
!820 = !DILocation(line: 346, column: 15, scope: !811)
!821 = !DILocation(line: 346, column: 24, scope: !811)
!822 = !DILocation(line: 346, column: 3, scope: !811)
!823 = !DILocation(line: 347, column: 3, scope: !811)
!824 = !DILocation(line: 351, column: 6, scope: !825)
!825 = distinct !DILexicalBlock(scope: !245, file: !1, line: 351, column: 6)
!826 = !DILocation(line: 351, column: 18, scope: !825)
!827 = !DILocation(line: 351, column: 15, scope: !825)
!828 = !DILocation(line: 351, column: 6, scope: !245)
!829 = !DILocation(line: 352, column: 30, scope: !830)
!830 = distinct !DILexicalBlock(scope: !825, file: !1, line: 351, column: 28)
!831 = !DILocation(line: 352, column: 44, scope: !830)
!832 = !DILocation(line: 352, column: 15, scope: !830)
!833 = !DILocation(line: 352, column: 22, scope: !830)
!834 = !DILocation(line: 352, column: 49, scope: !830)
!835 = !DILocation(line: 353, column: 5, scope: !830)
!836 = !DILocation(line: 352, column: 4, scope: !830)
!837 = !DILocation(line: 352, column: 13, scope: !830)
!838 = !DILocation(line: 354, column: 14, scope: !830)
!839 = !DILocation(line: 354, column: 4, scope: !830)
!840 = !DILocation(line: 354, column: 12, scope: !830)
!841 = !DILocation(line: 355, column: 11, scope: !830)
!842 = !DILocation(line: 355, column: 15, scope: !830)
!843 = !DILocation(line: 355, column: 24, scope: !830)
!844 = !DILocation(line: 355, column: 3, scope: !830)
!845 = !DILocation(line: 356, column: 3, scope: !830)
!846 = !DILocation(line: 359, column: 18, scope: !245)
!847 = !DILocation(line: 359, column: 17, scope: !245)
!848 = !DILocation(line: 359, column: 15, scope: !245)
!849 = !DILocation(line: 360, column: 17, scope: !245)
!850 = !DILocation(line: 360, column: 23, scope: !245)
!851 = !DILocation(line: 360, column: 30, scope: !245)
!852 = !DILocation(line: 360, column: 21, scope: !245)
!853 = !DILocation(line: 360, column: 38, scope: !245)
!854 = !DILocation(line: 360, column: 15, scope: !245)
!855 = !DILocation(line: 360, column: 13, scope: !245)
!856 = !DILocation(line: 362, column: 6, scope: !857)
!857 = distinct !DILexicalBlock(scope: !245, file: !1, line: 362, column: 6)
!858 = !DILocation(line: 362, column: 15, scope: !857)
!859 = !DILocation(line: 362, column: 19, scope: !857)
!860 = !DILocation(line: 362, column: 22, scope: !861)
!861 = !DILexicalBlockFile(scope: !857, file: !1, discriminator: 1)
!862 = !DILocation(line: 362, column: 38, scope: !861)
!863 = !DILocation(line: 362, column: 35, scope: !861)
!864 = !DILocation(line: 363, column: 4, scope: !857)
!865 = !DILocation(line: 363, column: 16, scope: !861)
!866 = !DILocation(line: 363, column: 7, scope: !861)
!867 = !DILocation(line: 363, column: 31, scope: !861)
!868 = !DILocation(line: 362, column: 6, scope: !720)
!869 = !DILocation(line: 364, column: 4, scope: !870)
!870 = distinct !DILexicalBlock(scope: !857, file: !1, line: 363, column: 36)
!871 = !DILocation(line: 364, column: 13, scope: !870)
!872 = !DILocation(line: 365, column: 4, scope: !870)
!873 = !DILocation(line: 365, column: 12, scope: !870)
!874 = !DILocation(line: 366, column: 3, scope: !870)
!875 = !DILocation(line: 369, column: 25, scope: !245)
!876 = !DILocation(line: 369, column: 32, scope: !245)
!877 = !DILocation(line: 369, column: 2, scope: !245)
!878 = !DILocation(line: 369, column: 9, scope: !245)
!879 = !DILocation(line: 369, column: 17, scope: !245)
!880 = !DILocation(line: 369, column: 23, scope: !245)
!881 = !DILocation(line: 371, column: 14, scope: !245)
!882 = !DILocation(line: 371, column: 25, scope: !245)
!883 = !DILocation(line: 371, column: 32, scope: !245)
!884 = !DILocation(line: 371, column: 23, scope: !245)
!885 = !DILocation(line: 371, column: 12, scope: !245)
!886 = !DILocation(line: 374, column: 35, scope: !245)
!887 = !DILocation(line: 374, column: 5, scope: !245)
!888 = !DILocation(line: 374, column: 21, scope: !245)
!889 = !DILocation(line: 374, column: 28, scope: !245)
!890 = !DILocation(line: 374, column: 12, scope: !245)
!891 = !DILocation(line: 373, column: 25, scope: !245)
!892 = !DILocation(line: 375, column: 24, scope: !245)
!893 = !DILocation(line: 375, column: 31, scope: !245)
!894 = !DILocation(line: 375, column: 41, scope: !245)
!895 = !DILocation(line: 376, column: 6, scope: !245)
!896 = !DILocation(line: 376, column: 5, scope: !245)
!897 = !DILocation(line: 377, column: 5, scope: !245)
!898 = !DILocation(line: 377, column: 17, scope: !245)
!899 = !DILocation(line: 375, column: 6, scope: !245)
!900 = !DILocation(line: 375, column: 4, scope: !245)
!901 = !DILocation(line: 373, column: 2, scope: !245)
!902 = !DILocation(line: 373, column: 9, scope: !245)
!903 = !DILocation(line: 373, column: 17, scope: !245)
!904 = !DILocation(line: 373, column: 23, scope: !245)
!905 = !DILocation(line: 379, column: 16, scope: !245)
!906 = !DILocation(line: 379, column: 23, scope: !245)
!907 = !DILocation(line: 379, column: 2, scope: !245)
!908 = !DILocation(line: 382, column: 34, scope: !245)
!909 = !DILocation(line: 382, column: 4, scope: !245)
!910 = !DILocation(line: 382, column: 20, scope: !245)
!911 = !DILocation(line: 382, column: 27, scope: !245)
!912 = !DILocation(line: 382, column: 11, scope: !245)
!913 = !DILocation(line: 381, column: 16, scope: !245)
!914 = !DILocation(line: 381, column: 14, scope: !245)
!915 = !DILocation(line: 383, column: 20, scope: !245)
!916 = !DILocation(line: 384, column: 35, scope: !245)
!917 = !DILocation(line: 384, column: 42, scope: !245)
!918 = !DILocation(line: 384, column: 21, scope: !245)
!919 = !DILocation(line: 384, column: 28, scope: !245)
!920 = !DILocation(line: 384, column: 6, scope: !245)
!921 = !DILocation(line: 384, column: 4, scope: !245)
!922 = !DILocation(line: 383, column: 18, scope: !245)
!923 = !DILocation(line: 386, column: 6, scope: !924)
!924 = distinct !DILexicalBlock(scope: !245, file: !1, line: 386, column: 6)
!925 = !DILocation(line: 386, column: 20, scope: !924)
!926 = !DILocation(line: 386, column: 17, scope: !924)
!927 = !DILocation(line: 386, column: 6, scope: !245)
!928 = !DILocalVariable(name: "short_rep_price", scope: !929, file: !1, line: 387, type: !230)
!929 = distinct !DILexicalBlock(scope: !924, file: !1, line: 386, column: 34)
!930 = !DILocation(line: 387, column: 18, scope: !929)
!931 = !DILocation(line: 387, column: 36, scope: !929)
!932 = !DILocation(line: 389, column: 6, scope: !929)
!933 = !DILocation(line: 389, column: 13, scope: !929)
!934 = !DILocation(line: 389, column: 20, scope: !929)
!935 = !DILocation(line: 389, column: 27, scope: !929)
!936 = !DILocation(line: 388, column: 7, scope: !929)
!937 = !DILocation(line: 388, column: 5, scope: !929)
!938 = !DILocation(line: 391, column: 7, scope: !939)
!939 = distinct !DILexicalBlock(scope: !929, file: !1, line: 391, column: 7)
!940 = !DILocation(line: 391, column: 25, scope: !939)
!941 = !DILocation(line: 391, column: 32, scope: !939)
!942 = !DILocation(line: 391, column: 40, scope: !939)
!943 = !DILocation(line: 391, column: 23, scope: !939)
!944 = !DILocation(line: 391, column: 7, scope: !929)
!945 = !DILocation(line: 392, column: 27, scope: !946)
!946 = distinct !DILexicalBlock(scope: !939, file: !1, line: 391, column: 47)
!947 = !DILocation(line: 392, column: 4, scope: !946)
!948 = !DILocation(line: 392, column: 11, scope: !946)
!949 = !DILocation(line: 392, column: 19, scope: !946)
!950 = !DILocation(line: 392, column: 25, scope: !946)
!951 = !DILocation(line: 393, column: 20, scope: !946)
!952 = !DILocation(line: 393, column: 27, scope: !946)
!953 = !DILocation(line: 393, column: 4, scope: !946)
!954 = !DILocation(line: 394, column: 3, scope: !946)
!955 = !DILocation(line: 395, column: 2, scope: !929)
!956 = !DILocation(line: 397, column: 12, scope: !245)
!957 = !DILocation(line: 397, column: 12, scope: !718)
!958 = !DILocation(line: 397, column: 12, scope: !720)
!959 = !DILocation(line: 397, column: 12, scope: !722)
!960 = !DILocation(line: 397, column: 10, scope: !722)
!961 = !DILocation(line: 399, column: 6, scope: !962)
!962 = distinct !DILexicalBlock(scope: !245, file: !1, line: 399, column: 6)
!963 = !DILocation(line: 399, column: 14, scope: !962)
!964 = !DILocation(line: 399, column: 6, scope: !245)
!965 = !DILocation(line: 400, column: 15, scope: !966)
!966 = distinct !DILexicalBlock(scope: !962, file: !1, line: 399, column: 19)
!967 = !DILocation(line: 400, column: 22, scope: !966)
!968 = !DILocation(line: 400, column: 30, scope: !966)
!969 = !DILocation(line: 400, column: 4, scope: !966)
!970 = !DILocation(line: 400, column: 13, scope: !966)
!971 = !DILocation(line: 401, column: 4, scope: !966)
!972 = !DILocation(line: 401, column: 12, scope: !966)
!973 = !DILocation(line: 402, column: 3, scope: !966)
!974 = !DILocation(line: 405, column: 2, scope: !245)
!975 = !DILocation(line: 405, column: 9, scope: !245)
!976 = !DILocation(line: 405, column: 17, scope: !245)
!977 = !DILocation(line: 405, column: 26, scope: !245)
!978 = !DILocation(line: 407, column: 9, scope: !979)
!979 = distinct !DILexicalBlock(scope: !245, file: !1, line: 407, column: 2)
!980 = !DILocation(line: 407, column: 7, scope: !979)
!981 = !DILocation(line: 407, column: 14, scope: !982)
!982 = !DILexicalBlockFile(scope: !983, file: !1, discriminator: 1)
!983 = distinct !DILexicalBlock(scope: !979, file: !1, line: 407, column: 2)
!984 = !DILocation(line: 407, column: 16, scope: !982)
!985 = !DILocation(line: 407, column: 2, scope: !982)
!986 = !DILocation(line: 408, column: 41, scope: !983)
!987 = !DILocation(line: 408, column: 29, scope: !983)
!988 = !DILocation(line: 408, column: 36, scope: !983)
!989 = !DILocation(line: 408, column: 24, scope: !983)
!990 = !DILocation(line: 408, column: 3, scope: !983)
!991 = !DILocation(line: 408, column: 10, scope: !983)
!992 = !DILocation(line: 408, column: 18, scope: !983)
!993 = !DILocation(line: 408, column: 27, scope: !983)
!994 = !DILocation(line: 407, column: 33, scope: !995)
!995 = !DILexicalBlockFile(scope: !983, file: !1, discriminator: 2)
!996 = !DILocation(line: 407, column: 2, scope: !995)
!997 = !DILocation(line: 410, column: 8, scope: !245)
!998 = !DILocation(line: 410, column: 6, scope: !245)
!999 = !DILocation(line: 411, column: 2, scope: !245)
!1000 = !DILocation(line: 412, column: 15, scope: !1001)
!1001 = distinct !DILexicalBlock(scope: !245, file: !1, line: 411, column: 5)
!1002 = !DILocation(line: 412, column: 3, scope: !1001)
!1003 = !DILocation(line: 412, column: 10, scope: !1001)
!1004 = !DILocation(line: 412, column: 20, scope: !1001)
!1005 = !DILocation(line: 412, column: 26, scope: !1001)
!1006 = !DILocation(line: 413, column: 2, scope: !1001)
!1007 = !DILocation(line: 413, column: 11, scope: !718)
!1008 = !DILocation(line: 413, column: 17, scope: !718)
!1009 = !DILocation(line: 413, column: 2, scope: !718)
!1010 = !DILocation(line: 416, column: 9, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !245, file: !1, line: 416, column: 2)
!1012 = !DILocation(line: 416, column: 7, scope: !1011)
!1013 = !DILocation(line: 416, column: 14, scope: !1014)
!1014 = !DILexicalBlockFile(scope: !1015, file: !1, discriminator: 1)
!1015 = distinct !DILexicalBlock(scope: !1011, file: !1, line: 416, column: 2)
!1016 = !DILocation(line: 416, column: 16, scope: !1014)
!1017 = !DILocation(line: 416, column: 2, scope: !1014)
!1018 = !DILocalVariable(name: "price", scope: !1019, file: !1, line: 417, type: !13)
!1019 = distinct !DILexicalBlock(scope: !1015, file: !1, line: 416, column: 38)
!1020 = !DILocation(line: 417, column: 12, scope: !1019)
!1021 = !DILocalVariable(name: "rep_len", scope: !1019, file: !1, line: 419, type: !13)
!1022 = !DILocation(line: 419, column: 12, scope: !1019)
!1023 = !DILocation(line: 419, column: 31, scope: !1019)
!1024 = !DILocation(line: 419, column: 22, scope: !1019)
!1025 = !DILocation(line: 420, column: 7, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !1019, file: !1, line: 420, column: 7)
!1027 = !DILocation(line: 420, column: 15, scope: !1026)
!1028 = !DILocation(line: 420, column: 7, scope: !1019)
!1029 = !DILocation(line: 421, column: 4, scope: !1026)
!1030 = !DILocation(line: 423, column: 11, scope: !1019)
!1031 = !DILocation(line: 424, column: 5, scope: !1019)
!1032 = !DILocation(line: 424, column: 12, scope: !1019)
!1033 = !DILocation(line: 424, column: 15, scope: !1019)
!1034 = !DILocation(line: 424, column: 22, scope: !1019)
!1035 = !DILocation(line: 424, column: 29, scope: !1019)
!1036 = !DILocation(line: 423, column: 29, scope: !1019)
!1037 = !DILocation(line: 423, column: 27, scope: !1019)
!1038 = !DILocation(line: 423, column: 9, scope: !1019)
!1039 = !DILocation(line: 426, column: 3, scope: !1019)
!1040 = !DILocalVariable(name: "cur_and_len_price", scope: !1041, file: !1, line: 427, type: !230)
!1041 = distinct !DILexicalBlock(scope: !1019, file: !1, line: 426, column: 6)
!1042 = !DILocation(line: 427, column: 19, scope: !1041)
!1043 = !DILocation(line: 427, column: 39, scope: !1041)
!1044 = !DILocation(line: 429, column: 8, scope: !1041)
!1045 = !DILocation(line: 429, column: 15, scope: !1041)
!1046 = !DILocation(line: 430, column: 7, scope: !1041)
!1047 = !DILocation(line: 430, column: 16, scope: !1041)
!1048 = !DILocation(line: 428, column: 8, scope: !1041)
!1049 = !DILocation(line: 428, column: 6, scope: !1041)
!1050 = !DILocation(line: 432, column: 8, scope: !1051)
!1051 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 432, column: 8)
!1052 = !DILocation(line: 432, column: 40, scope: !1051)
!1053 = !DILocation(line: 432, column: 28, scope: !1051)
!1054 = !DILocation(line: 432, column: 35, scope: !1051)
!1055 = !DILocation(line: 432, column: 49, scope: !1051)
!1056 = !DILocation(line: 432, column: 26, scope: !1051)
!1057 = !DILocation(line: 432, column: 8, scope: !1041)
!1058 = !DILocation(line: 433, column: 34, scope: !1059)
!1059 = distinct !DILexicalBlock(scope: !1051, file: !1, line: 432, column: 56)
!1060 = !DILocation(line: 433, column: 17, scope: !1059)
!1061 = !DILocation(line: 433, column: 5, scope: !1059)
!1062 = !DILocation(line: 433, column: 12, scope: !1059)
!1063 = !DILocation(line: 433, column: 26, scope: !1059)
!1064 = !DILocation(line: 433, column: 32, scope: !1059)
!1065 = !DILocation(line: 434, column: 17, scope: !1059)
!1066 = !DILocation(line: 434, column: 5, scope: !1059)
!1067 = !DILocation(line: 434, column: 12, scope: !1059)
!1068 = !DILocation(line: 434, column: 26, scope: !1059)
!1069 = !DILocation(line: 434, column: 35, scope: !1059)
!1070 = !DILocation(line: 435, column: 38, scope: !1059)
!1071 = !DILocation(line: 435, column: 17, scope: !1059)
!1072 = !DILocation(line: 435, column: 5, scope: !1059)
!1073 = !DILocation(line: 435, column: 12, scope: !1059)
!1074 = !DILocation(line: 435, column: 26, scope: !1059)
!1075 = !DILocation(line: 435, column: 36, scope: !1059)
!1076 = !DILocation(line: 436, column: 17, scope: !1059)
!1077 = !DILocation(line: 436, column: 5, scope: !1059)
!1078 = !DILocation(line: 436, column: 12, scope: !1059)
!1079 = !DILocation(line: 436, column: 26, scope: !1059)
!1080 = !DILocation(line: 436, column: 44, scope: !1059)
!1081 = !DILocation(line: 437, column: 4, scope: !1059)
!1082 = !DILocation(line: 438, column: 3, scope: !1041)
!1083 = !DILocation(line: 438, column: 12, scope: !1084)
!1084 = !DILexicalBlockFile(scope: !1019, file: !1, discriminator: 1)
!1085 = !DILocation(line: 438, column: 22, scope: !1084)
!1086 = !DILocation(line: 438, column: 3, scope: !1084)
!1087 = !DILocation(line: 439, column: 2, scope: !1019)
!1088 = !DILocation(line: 416, column: 33, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1015, file: !1, discriminator: 2)
!1090 = !DILocation(line: 416, column: 2, scope: !1089)
!1091 = !DILocation(line: 442, column: 23, scope: !245)
!1092 = !DILocation(line: 443, column: 35, scope: !245)
!1093 = !DILocation(line: 443, column: 42, scope: !245)
!1094 = !DILocation(line: 443, column: 21, scope: !245)
!1095 = !DILocation(line: 443, column: 28, scope: !245)
!1096 = !DILocation(line: 443, column: 6, scope: !245)
!1097 = !DILocation(line: 443, column: 4, scope: !245)
!1098 = !DILocation(line: 442, column: 21, scope: !245)
!1099 = !DILocation(line: 445, column: 8, scope: !245)
!1100 = !DILocation(line: 445, column: 20, scope: !245)
!1101 = !DILocation(line: 445, column: 27, scope: !718)
!1102 = !DILocation(line: 445, column: 39, scope: !718)
!1103 = !DILocation(line: 445, column: 8, scope: !718)
!1104 = !DILocation(line: 445, column: 8, scope: !720)
!1105 = !DILocation(line: 445, column: 8, scope: !722)
!1106 = !DILocation(line: 445, column: 6, scope: !722)
!1107 = !DILocation(line: 446, column: 6, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !245, file: !1, line: 446, column: 6)
!1109 = !DILocation(line: 446, column: 13, scope: !1108)
!1110 = !DILocation(line: 446, column: 10, scope: !1108)
!1111 = !DILocation(line: 446, column: 6, scope: !245)
!1112 = !DILocalVariable(name: "i", scope: !1113, file: !1, line: 447, type: !13)
!1113 = distinct !DILexicalBlock(scope: !1108, file: !1, line: 446, column: 23)
!1114 = !DILocation(line: 447, column: 12, scope: !1113)
!1115 = !DILocation(line: 448, column: 3, scope: !1113)
!1116 = !DILocation(line: 448, column: 10, scope: !1117)
!1117 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 1)
!1118 = !DILocation(line: 448, column: 31, scope: !1117)
!1119 = !DILocation(line: 448, column: 16, scope: !1117)
!1120 = !DILocation(line: 448, column: 23, scope: !1117)
!1121 = !DILocation(line: 448, column: 34, scope: !1117)
!1122 = !DILocation(line: 448, column: 14, scope: !1117)
!1123 = !DILocation(line: 448, column: 3, scope: !1117)
!1124 = !DILocation(line: 449, column: 4, scope: !1113)
!1125 = !DILocation(line: 448, column: 3, scope: !1126)
!1126 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 2)
!1127 = !DILocation(line: 451, column: 3, scope: !1113)
!1128 = !DILocalVariable(name: "dist", scope: !1129, file: !1, line: 452, type: !230)
!1129 = distinct !DILexicalBlock(scope: !1130, file: !1, line: 451, column: 18)
!1130 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 451, column: 3)
!1131 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 451, column: 3)
!1132 = !DILocation(line: 452, column: 19, scope: !1129)
!1133 = !DILocation(line: 452, column: 41, scope: !1129)
!1134 = !DILocation(line: 452, column: 26, scope: !1129)
!1135 = !DILocation(line: 452, column: 33, scope: !1129)
!1136 = !DILocation(line: 452, column: 44, scope: !1129)
!1137 = !DILocalVariable(name: "cur_and_len_price", scope: !1129, file: !1, line: 453, type: !230)
!1138 = !DILocation(line: 453, column: 19, scope: !1129)
!1139 = !DILocation(line: 453, column: 39, scope: !1129)
!1140 = !DILocation(line: 454, column: 26, scope: !1129)
!1141 = !DILocation(line: 455, column: 7, scope: !1129)
!1142 = !DILocation(line: 455, column: 13, scope: !1129)
!1143 = !DILocation(line: 455, column: 18, scope: !1129)
!1144 = !DILocation(line: 454, column: 8, scope: !1129)
!1145 = !DILocation(line: 454, column: 6, scope: !1129)
!1146 = !DILocation(line: 457, column: 8, scope: !1147)
!1147 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 457, column: 8)
!1148 = !DILocation(line: 457, column: 40, scope: !1147)
!1149 = !DILocation(line: 457, column: 28, scope: !1147)
!1150 = !DILocation(line: 457, column: 35, scope: !1147)
!1151 = !DILocation(line: 457, column: 45, scope: !1147)
!1152 = !DILocation(line: 457, column: 26, scope: !1147)
!1153 = !DILocation(line: 457, column: 8, scope: !1129)
!1154 = !DILocation(line: 458, column: 30, scope: !1155)
!1155 = distinct !DILexicalBlock(scope: !1147, file: !1, line: 457, column: 52)
!1156 = !DILocation(line: 458, column: 17, scope: !1155)
!1157 = !DILocation(line: 458, column: 5, scope: !1155)
!1158 = !DILocation(line: 458, column: 12, scope: !1155)
!1159 = !DILocation(line: 458, column: 22, scope: !1155)
!1160 = !DILocation(line: 458, column: 28, scope: !1155)
!1161 = !DILocation(line: 459, column: 17, scope: !1155)
!1162 = !DILocation(line: 459, column: 5, scope: !1155)
!1163 = !DILocation(line: 459, column: 12, scope: !1155)
!1164 = !DILocation(line: 459, column: 22, scope: !1155)
!1165 = !DILocation(line: 459, column: 31, scope: !1155)
!1166 = !DILocation(line: 461, column: 9, scope: !1155)
!1167 = !DILocation(line: 461, column: 14, scope: !1155)
!1168 = !DILocation(line: 460, column: 17, scope: !1155)
!1169 = !DILocation(line: 460, column: 5, scope: !1155)
!1170 = !DILocation(line: 460, column: 12, scope: !1155)
!1171 = !DILocation(line: 460, column: 22, scope: !1155)
!1172 = !DILocation(line: 461, column: 7, scope: !1155)
!1173 = !DILocation(line: 462, column: 17, scope: !1155)
!1174 = !DILocation(line: 462, column: 5, scope: !1155)
!1175 = !DILocation(line: 462, column: 12, scope: !1155)
!1176 = !DILocation(line: 462, column: 22, scope: !1155)
!1177 = !DILocation(line: 462, column: 40, scope: !1155)
!1178 = !DILocation(line: 463, column: 4, scope: !1155)
!1179 = !DILocation(line: 465, column: 8, scope: !1180)
!1180 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 465, column: 8)
!1181 = !DILocation(line: 465, column: 30, scope: !1180)
!1182 = !DILocation(line: 465, column: 15, scope: !1180)
!1183 = !DILocation(line: 465, column: 22, scope: !1180)
!1184 = !DILocation(line: 465, column: 33, scope: !1180)
!1185 = !DILocation(line: 465, column: 12, scope: !1180)
!1186 = !DILocation(line: 465, column: 8, scope: !1129)
!1187 = !DILocation(line: 466, column: 9, scope: !1188)
!1188 = distinct !DILexicalBlock(scope: !1180, file: !1, line: 466, column: 9)
!1189 = !DILocation(line: 466, column: 16, scope: !1188)
!1190 = !DILocation(line: 466, column: 13, scope: !1188)
!1191 = !DILocation(line: 466, column: 9, scope: !1180)
!1192 = !DILocation(line: 467, column: 6, scope: !1188)
!1193 = !DILocation(line: 466, column: 16, scope: !1194)
!1194 = !DILexicalBlockFile(scope: !1188, file: !1, discriminator: 1)
!1195 = !DILocation(line: 468, column: 3, scope: !1129)
!1196 = !DILocation(line: 451, column: 11, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !1130, file: !1, discriminator: 1)
!1198 = !DILocation(line: 451, column: 3, scope: !1197)
!1199 = !DILocation(line: 469, column: 2, scope: !1113)
!1200 = !DILocation(line: 471, column: 9, scope: !245)
!1201 = !DILocation(line: 471, column: 2, scope: !245)
!1202 = !DILocation(line: 472, column: 1, scope: !245)
!1203 = !DILocalVariable(name: "coder", arg: 1, scope: !282, file: !1, line: 476, type: !69)
!1204 = !DILocation(line: 476, column: 21, scope: !282)
!1205 = !DILocalVariable(name: "reps", arg: 2, scope: !282, file: !1, line: 476, type: !206)
!1206 = !DILocation(line: 476, column: 38, scope: !282)
!1207 = !DILocalVariable(name: "buf", arg: 3, scope: !282, file: !1, line: 476, type: !285)
!1208 = !DILocation(line: 476, column: 59, scope: !282)
!1209 = !DILocalVariable(name: "len_end", arg: 4, scope: !282, file: !1, line: 477, type: !13)
!1210 = !DILocation(line: 477, column: 12, scope: !282)
!1211 = !DILocalVariable(name: "position", arg: 5, scope: !282, file: !1, line: 477, type: !13)
!1212 = !DILocation(line: 477, column: 30, scope: !282)
!1213 = !DILocalVariable(name: "cur", arg: 6, scope: !282, file: !1, line: 477, type: !230)
!1214 = !DILocation(line: 477, column: 55, scope: !282)
!1215 = !DILocalVariable(name: "nice_len", arg: 7, scope: !282, file: !1, line: 478, type: !230)
!1216 = !DILocation(line: 478, column: 18, scope: !282)
!1217 = !DILocalVariable(name: "buf_avail_full", arg: 8, scope: !282, file: !1, line: 478, type: !230)
!1218 = !DILocation(line: 478, column: 43, scope: !282)
!1219 = !DILocalVariable(name: "matches_count", scope: !282, file: !1, line: 480, type: !13)
!1220 = !DILocation(line: 480, column: 11, scope: !282)
!1221 = !DILocation(line: 480, column: 27, scope: !282)
!1222 = !DILocation(line: 480, column: 34, scope: !282)
!1223 = !DILocalVariable(name: "new_len", scope: !282, file: !1, line: 481, type: !13)
!1224 = !DILocation(line: 481, column: 11, scope: !282)
!1225 = !DILocation(line: 481, column: 21, scope: !282)
!1226 = !DILocation(line: 481, column: 28, scope: !282)
!1227 = !DILocalVariable(name: "pos_prev", scope: !282, file: !1, line: 482, type: !13)
!1228 = !DILocation(line: 482, column: 11, scope: !282)
!1229 = !DILocation(line: 482, column: 34, scope: !282)
!1230 = !DILocation(line: 482, column: 22, scope: !282)
!1231 = !DILocation(line: 482, column: 29, scope: !282)
!1232 = !DILocation(line: 482, column: 39, scope: !282)
!1233 = !DILocalVariable(name: "state", scope: !282, file: !1, line: 483, type: !78)
!1234 = !DILocation(line: 483, column: 18, scope: !282)
!1235 = !DILocalVariable(name: "buf_avail", scope: !282, file: !1, line: 484, type: !13)
!1236 = !DILocation(line: 484, column: 11, scope: !282)
!1237 = !DILocalVariable(name: "rep_index", scope: !282, file: !1, line: 485, type: !13)
!1238 = !DILocation(line: 485, column: 11, scope: !282)
!1239 = !DILocalVariable(name: "i", scope: !282, file: !1, line: 486, type: !13)
!1240 = !DILocation(line: 486, column: 11, scope: !282)
!1241 = !DILocalVariable(name: "cur_price", scope: !282, file: !1, line: 488, type: !13)
!1242 = !DILocation(line: 488, column: 11, scope: !282)
!1243 = !DILocalVariable(name: "current_byte", scope: !282, file: !1, line: 489, type: !16)
!1244 = !DILocation(line: 489, column: 10, scope: !282)
!1245 = !DILocalVariable(name: "match_byte", scope: !282, file: !1, line: 490, type: !16)
!1246 = !DILocation(line: 490, column: 10, scope: !282)
!1247 = !DILocalVariable(name: "pos_state", scope: !282, file: !1, line: 491, type: !13)
!1248 = !DILocation(line: 491, column: 11, scope: !282)
!1249 = !DILocalVariable(name: "cur_and_1_price", scope: !282, file: !1, line: 492, type: !13)
!1250 = !DILocation(line: 492, column: 11, scope: !282)
!1251 = !DILocalVariable(name: "next_is_literal", scope: !282, file: !1, line: 493, type: !96)
!1252 = !DILocation(line: 493, column: 7, scope: !282)
!1253 = !DILocalVariable(name: "match_price", scope: !282, file: !1, line: 494, type: !13)
!1254 = !DILocation(line: 494, column: 11, scope: !282)
!1255 = !DILocalVariable(name: "rep_match_price", scope: !282, file: !1, line: 495, type: !13)
!1256 = !DILocation(line: 495, column: 11, scope: !282)
!1257 = !DILocalVariable(name: "start_len", scope: !282, file: !1, line: 496, type: !13)
!1258 = !DILocation(line: 496, column: 11, scope: !282)
!1259 = !DILocation(line: 498, column: 18, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !282, file: !1, line: 498, column: 6)
!1261 = !DILocation(line: 498, column: 6, scope: !1260)
!1262 = !DILocation(line: 498, column: 13, scope: !1260)
!1263 = !DILocation(line: 498, column: 23, scope: !1260)
!1264 = !DILocation(line: 498, column: 6, scope: !282)
!1265 = !DILocation(line: 499, column: 3, scope: !1266)
!1266 = distinct !DILexicalBlock(scope: !1260, file: !1, line: 498, column: 42)
!1267 = !DILocation(line: 501, column: 19, scope: !1268)
!1268 = distinct !DILexicalBlock(scope: !1266, file: !1, line: 501, column: 7)
!1269 = !DILocation(line: 501, column: 7, scope: !1268)
!1270 = !DILocation(line: 501, column: 14, scope: !1268)
!1271 = !DILocation(line: 501, column: 24, scope: !1268)
!1272 = !DILocation(line: 501, column: 7, scope: !1266)
!1273 = !DILocation(line: 502, column: 36, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !1268, file: !1, line: 501, column: 32)
!1275 = !DILocation(line: 502, column: 24, scope: !1274)
!1276 = !DILocation(line: 502, column: 31, scope: !1274)
!1277 = !DILocation(line: 502, column: 41, scope: !1274)
!1278 = !DILocation(line: 502, column: 12, scope: !1274)
!1279 = !DILocation(line: 502, column: 19, scope: !1274)
!1280 = !DILocation(line: 502, column: 53, scope: !1274)
!1281 = !DILocation(line: 502, column: 10, scope: !1274)
!1282 = !DILocation(line: 504, column: 20, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 504, column: 8)
!1284 = !DILocation(line: 504, column: 8, scope: !1283)
!1285 = !DILocation(line: 504, column: 15, scope: !1283)
!1286 = !DILocation(line: 504, column: 25, scope: !1283)
!1287 = !DILocation(line: 504, column: 37, scope: !1283)
!1288 = !DILocation(line: 504, column: 8, scope: !1274)
!1289 = !DILocation(line: 505, column: 5, scope: !1283)
!1290 = !DILocation(line: 507, column: 5, scope: !1283)
!1291 = !DILocation(line: 509, column: 3, scope: !1274)
!1292 = !DILocation(line: 510, column: 24, scope: !1293)
!1293 = distinct !DILexicalBlock(scope: !1268, file: !1, line: 509, column: 10)
!1294 = !DILocation(line: 510, column: 12, scope: !1293)
!1295 = !DILocation(line: 510, column: 19, scope: !1293)
!1296 = !DILocation(line: 510, column: 34, scope: !1293)
!1297 = !DILocation(line: 510, column: 10, scope: !1293)
!1298 = !DILocation(line: 513, column: 3, scope: !1266)
!1299 = !DILocation(line: 513, column: 3, scope: !1300)
!1300 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 1)
!1301 = !DILocation(line: 513, column: 3, scope: !1302)
!1302 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 2)
!1303 = !DILocation(line: 513, column: 3, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 3)
!1305 = !DILocation(line: 513, column: 3, scope: !1306)
!1306 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 4)
!1307 = !DILocation(line: 513, column: 3, scope: !1308)
!1308 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 5)
!1309 = !DILocation(line: 513, column: 3, scope: !1310)
!1310 = !DILexicalBlockFile(scope: !1266, file: !1, discriminator: 6)
!1311 = !DILocation(line: 515, column: 2, scope: !1266)
!1312 = !DILocation(line: 516, column: 23, scope: !1313)
!1313 = distinct !DILexicalBlock(scope: !1260, file: !1, line: 515, column: 9)
!1314 = !DILocation(line: 516, column: 11, scope: !1313)
!1315 = !DILocation(line: 516, column: 18, scope: !1313)
!1316 = !DILocation(line: 516, column: 33, scope: !1313)
!1317 = !DILocation(line: 516, column: 9, scope: !1313)
!1318 = !DILocation(line: 519, column: 6, scope: !1319)
!1319 = distinct !DILexicalBlock(scope: !282, file: !1, line: 519, column: 6)
!1320 = !DILocation(line: 519, column: 18, scope: !1319)
!1321 = !DILocation(line: 519, column: 22, scope: !1319)
!1322 = !DILocation(line: 519, column: 15, scope: !1319)
!1323 = !DILocation(line: 519, column: 6, scope: !282)
!1324 = !DILocation(line: 520, column: 7, scope: !1325)
!1325 = distinct !DILexicalBlock(scope: !1326, file: !1, line: 520, column: 7)
!1326 = distinct !DILexicalBlock(scope: !1319, file: !1, line: 519, column: 27)
!1327 = !DILocation(line: 520, column: 7, scope: !1326)
!1328 = !DILocation(line: 521, column: 4, scope: !1325)
!1329 = !DILocation(line: 523, column: 4, scope: !1325)
!1330 = !DILocation(line: 523, column: 4, scope: !1331)
!1331 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 1)
!1332 = !DILocation(line: 523, column: 4, scope: !1333)
!1333 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 2)
!1334 = !DILocation(line: 523, column: 4, scope: !1335)
!1335 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 3)
!1336 = !DILocation(line: 523, column: 4, scope: !1337)
!1337 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 4)
!1338 = !DILocation(line: 523, column: 4, scope: !1339)
!1339 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 5)
!1340 = !DILocation(line: 523, column: 4, scope: !1341)
!1341 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 6)
!1342 = !DILocation(line: 524, column: 2, scope: !1326)
!1343 = !DILocalVariable(name: "pos", scope: !1344, file: !1, line: 525, type: !13)
!1344 = distinct !DILexicalBlock(scope: !1319, file: !1, line: 524, column: 9)
!1345 = !DILocation(line: 525, column: 12, scope: !1344)
!1346 = !DILocation(line: 526, column: 19, scope: !1347)
!1347 = distinct !DILexicalBlock(scope: !1344, file: !1, line: 526, column: 7)
!1348 = !DILocation(line: 526, column: 7, scope: !1347)
!1349 = !DILocation(line: 526, column: 14, scope: !1347)
!1350 = !DILocation(line: 526, column: 24, scope: !1347)
!1351 = !DILocation(line: 527, column: 5, scope: !1347)
!1352 = !DILocation(line: 527, column: 20, scope: !1353)
!1353 = !DILexicalBlockFile(scope: !1347, file: !1, discriminator: 1)
!1354 = !DILocation(line: 527, column: 8, scope: !1353)
!1355 = !DILocation(line: 527, column: 15, scope: !1353)
!1356 = !DILocation(line: 527, column: 25, scope: !1353)
!1357 = !DILocation(line: 526, column: 7, scope: !1358)
!1358 = !DILexicalBlockFile(scope: !1344, file: !1, discriminator: 1)
!1359 = !DILocation(line: 528, column: 27, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !1347, file: !1, line: 527, column: 33)
!1361 = !DILocation(line: 528, column: 15, scope: !1360)
!1362 = !DILocation(line: 528, column: 22, scope: !1360)
!1363 = !DILocation(line: 528, column: 32, scope: !1360)
!1364 = !DILocation(line: 528, column: 13, scope: !1360)
!1365 = !DILocation(line: 529, column: 22, scope: !1360)
!1366 = !DILocation(line: 529, column: 10, scope: !1360)
!1367 = !DILocation(line: 529, column: 17, scope: !1360)
!1368 = !DILocation(line: 529, column: 27, scope: !1360)
!1369 = !DILocation(line: 529, column: 8, scope: !1360)
!1370 = !DILocation(line: 530, column: 4, scope: !1360)
!1371 = !DILocation(line: 531, column: 3, scope: !1360)
!1372 = !DILocation(line: 532, column: 22, scope: !1373)
!1373 = distinct !DILexicalBlock(scope: !1347, file: !1, line: 531, column: 10)
!1374 = !DILocation(line: 532, column: 10, scope: !1373)
!1375 = !DILocation(line: 532, column: 17, scope: !1373)
!1376 = !DILocation(line: 532, column: 27, scope: !1373)
!1377 = !DILocation(line: 532, column: 8, scope: !1373)
!1378 = !DILocation(line: 533, column: 8, scope: !1379)
!1379 = distinct !DILexicalBlock(scope: !1373, file: !1, line: 533, column: 8)
!1380 = !DILocation(line: 533, column: 12, scope: !1379)
!1381 = !DILocation(line: 533, column: 8, scope: !1373)
!1382 = !DILocation(line: 534, column: 5, scope: !1379)
!1383 = !DILocation(line: 536, column: 5, scope: !1379)
!1384 = !DILocation(line: 539, column: 7, scope: !1385)
!1385 = distinct !DILexicalBlock(scope: !1344, file: !1, line: 539, column: 7)
!1386 = !DILocation(line: 539, column: 11, scope: !1385)
!1387 = !DILocation(line: 539, column: 7, scope: !1344)
!1388 = !DILocalVariable(name: "i", scope: !1389, file: !1, line: 540, type: !13)
!1389 = distinct !DILexicalBlock(scope: !1385, file: !1, line: 539, column: 28)
!1390 = !DILocation(line: 540, column: 13, scope: !1389)
!1391 = !DILocation(line: 542, column: 42, scope: !1389)
!1392 = !DILocation(line: 542, column: 14, scope: !1389)
!1393 = !DILocation(line: 542, column: 26, scope: !1389)
!1394 = !DILocation(line: 542, column: 21, scope: !1389)
!1395 = !DILocation(line: 542, column: 36, scope: !1389)
!1396 = !DILocation(line: 542, column: 4, scope: !1389)
!1397 = !DILocation(line: 542, column: 12, scope: !1389)
!1398 = !DILocation(line: 544, column: 11, scope: !1399)
!1399 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 544, column: 4)
!1400 = !DILocation(line: 544, column: 9, scope: !1399)
!1401 = !DILocation(line: 544, column: 16, scope: !1402)
!1402 = !DILexicalBlockFile(scope: !1403, file: !1, discriminator: 1)
!1403 = distinct !DILexicalBlock(scope: !1399, file: !1, line: 544, column: 4)
!1404 = !DILocation(line: 544, column: 21, scope: !1402)
!1405 = !DILocation(line: 544, column: 18, scope: !1402)
!1406 = !DILocation(line: 544, column: 4, scope: !1402)
!1407 = !DILocation(line: 545, column: 43, scope: !1403)
!1408 = !DILocation(line: 545, column: 45, scope: !1403)
!1409 = !DILocation(line: 545, column: 15, scope: !1403)
!1410 = !DILocation(line: 545, column: 27, scope: !1403)
!1411 = !DILocation(line: 545, column: 22, scope: !1403)
!1412 = !DILocation(line: 545, column: 37, scope: !1403)
!1413 = !DILocation(line: 545, column: 10, scope: !1403)
!1414 = !DILocation(line: 545, column: 5, scope: !1403)
!1415 = !DILocation(line: 545, column: 13, scope: !1403)
!1416 = !DILocation(line: 544, column: 26, scope: !1417)
!1417 = !DILexicalBlockFile(scope: !1403, file: !1, discriminator: 2)
!1418 = !DILocation(line: 544, column: 4, scope: !1417)
!1419 = !DILocation(line: 547, column: 4, scope: !1389)
!1420 = !DILocation(line: 547, column: 11, scope: !1421)
!1421 = !DILexicalBlockFile(scope: !1422, file: !1, discriminator: 1)
!1422 = distinct !DILexicalBlock(scope: !1423, file: !1, line: 547, column: 4)
!1423 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 547, column: 4)
!1424 = !DILocation(line: 547, column: 13, scope: !1421)
!1425 = !DILocation(line: 547, column: 4, scope: !1421)
!1426 = !DILocation(line: 548, column: 43, scope: !1422)
!1427 = !DILocation(line: 548, column: 15, scope: !1422)
!1428 = !DILocation(line: 548, column: 27, scope: !1422)
!1429 = !DILocation(line: 548, column: 22, scope: !1422)
!1430 = !DILocation(line: 548, column: 37, scope: !1422)
!1431 = !DILocation(line: 548, column: 10, scope: !1422)
!1432 = !DILocation(line: 548, column: 5, scope: !1422)
!1433 = !DILocation(line: 548, column: 13, scope: !1422)
!1434 = !DILocation(line: 547, column: 30, scope: !1435)
!1435 = !DILexicalBlockFile(scope: !1422, file: !1, discriminator: 2)
!1436 = !DILocation(line: 547, column: 4, scope: !1435)
!1437 = !DILocation(line: 550, column: 3, scope: !1389)
!1438 = !DILocation(line: 551, column: 14, scope: !1439)
!1439 = distinct !DILexicalBlock(scope: !1385, file: !1, line: 550, column: 10)
!1440 = !DILocation(line: 551, column: 18, scope: !1439)
!1441 = !DILocation(line: 551, column: 4, scope: !1439)
!1442 = !DILocation(line: 551, column: 12, scope: !1439)
!1443 = !DILocation(line: 553, column: 11, scope: !1444)
!1444 = distinct !DILexicalBlock(scope: !1439, file: !1, line: 553, column: 4)
!1445 = !DILocation(line: 553, column: 9, scope: !1444)
!1446 = !DILocation(line: 553, column: 16, scope: !1447)
!1447 = !DILexicalBlockFile(scope: !1448, file: !1, discriminator: 1)
!1448 = distinct !DILexicalBlock(scope: !1444, file: !1, line: 553, column: 4)
!1449 = !DILocation(line: 553, column: 18, scope: !1447)
!1450 = !DILocation(line: 553, column: 4, scope: !1447)
!1451 = !DILocation(line: 554, column: 43, scope: !1448)
!1452 = !DILocation(line: 554, column: 45, scope: !1448)
!1453 = !DILocation(line: 554, column: 15, scope: !1448)
!1454 = !DILocation(line: 554, column: 27, scope: !1448)
!1455 = !DILocation(line: 554, column: 22, scope: !1448)
!1456 = !DILocation(line: 554, column: 37, scope: !1448)
!1457 = !DILocation(line: 554, column: 10, scope: !1448)
!1458 = !DILocation(line: 554, column: 5, scope: !1448)
!1459 = !DILocation(line: 554, column: 13, scope: !1448)
!1460 = !DILocation(line: 553, column: 35, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1448, file: !1, discriminator: 2)
!1462 = !DILocation(line: 553, column: 4, scope: !1461)
!1463 = !DILocation(line: 558, column: 27, scope: !282)
!1464 = !DILocation(line: 558, column: 14, scope: !282)
!1465 = !DILocation(line: 558, column: 2, scope: !282)
!1466 = !DILocation(line: 558, column: 9, scope: !282)
!1467 = !DILocation(line: 558, column: 19, scope: !282)
!1468 = !DILocation(line: 558, column: 25, scope: !282)
!1469 = !DILocation(line: 560, column: 9, scope: !1470)
!1470 = distinct !DILexicalBlock(scope: !282, file: !1, line: 560, column: 2)
!1471 = !DILocation(line: 560, column: 7, scope: !1470)
!1472 = !DILocation(line: 560, column: 14, scope: !1473)
!1473 = !DILexicalBlockFile(scope: !1474, file: !1, discriminator: 1)
!1474 = distinct !DILexicalBlock(scope: !1470, file: !1, line: 560, column: 2)
!1475 = !DILocation(line: 560, column: 16, scope: !1473)
!1476 = !DILocation(line: 560, column: 2, scope: !1473)
!1477 = !DILocation(line: 561, column: 36, scope: !1474)
!1478 = !DILocation(line: 561, column: 31, scope: !1474)
!1479 = !DILocation(line: 561, column: 26, scope: !1474)
!1480 = !DILocation(line: 561, column: 3, scope: !1474)
!1481 = !DILocation(line: 561, column: 15, scope: !1474)
!1482 = !DILocation(line: 561, column: 10, scope: !1474)
!1483 = !DILocation(line: 561, column: 20, scope: !1474)
!1484 = !DILocation(line: 561, column: 29, scope: !1474)
!1485 = !DILocation(line: 560, column: 33, scope: !1486)
!1486 = !DILexicalBlockFile(scope: !1474, file: !1, discriminator: 2)
!1487 = !DILocation(line: 560, column: 2, scope: !1486)
!1488 = !DILocation(line: 563, column: 26, scope: !282)
!1489 = !DILocation(line: 563, column: 14, scope: !282)
!1490 = !DILocation(line: 563, column: 21, scope: !282)
!1491 = !DILocation(line: 563, column: 31, scope: !282)
!1492 = !DILocation(line: 563, column: 12, scope: !282)
!1493 = !DILocation(line: 565, column: 18, scope: !282)
!1494 = !DILocation(line: 565, column: 17, scope: !282)
!1495 = !DILocation(line: 565, column: 15, scope: !282)
!1496 = !DILocation(line: 566, column: 17, scope: !282)
!1497 = !DILocation(line: 566, column: 23, scope: !282)
!1498 = !DILocation(line: 566, column: 21, scope: !282)
!1499 = !DILocation(line: 566, column: 31, scope: !282)
!1500 = !DILocation(line: 566, column: 15, scope: !282)
!1501 = !DILocation(line: 566, column: 13, scope: !282)
!1502 = !DILocation(line: 568, column: 14, scope: !282)
!1503 = !DILocation(line: 568, column: 25, scope: !282)
!1504 = !DILocation(line: 568, column: 32, scope: !282)
!1505 = !DILocation(line: 568, column: 23, scope: !282)
!1506 = !DILocation(line: 568, column: 12, scope: !282)
!1507 = !DILocation(line: 570, column: 20, scope: !282)
!1508 = !DILocation(line: 571, column: 44, scope: !282)
!1509 = !DILocation(line: 571, column: 21, scope: !282)
!1510 = !DILocation(line: 571, column: 37, scope: !282)
!1511 = !DILocation(line: 571, column: 28, scope: !282)
!1512 = !DILocation(line: 571, column: 6, scope: !282)
!1513 = !DILocation(line: 571, column: 4, scope: !282)
!1514 = !DILocation(line: 572, column: 24, scope: !282)
!1515 = !DILocation(line: 572, column: 31, scope: !282)
!1516 = !DILocation(line: 572, column: 41, scope: !282)
!1517 = !DILocation(line: 573, column: 5, scope: !282)
!1518 = !DILocation(line: 573, column: 4, scope: !282)
!1519 = !DILocation(line: 573, column: 30, scope: !282)
!1520 = !DILocation(line: 573, column: 42, scope: !282)
!1521 = !DILocation(line: 572, column: 6, scope: !282)
!1522 = !DILocation(line: 572, column: 4, scope: !282)
!1523 = !DILocation(line: 570, column: 18, scope: !282)
!1524 = !DILocation(line: 575, column: 6, scope: !1525)
!1525 = distinct !DILexicalBlock(scope: !282, file: !1, line: 575, column: 6)
!1526 = !DILocation(line: 575, column: 36, scope: !1525)
!1527 = !DILocation(line: 575, column: 40, scope: !1525)
!1528 = !DILocation(line: 575, column: 24, scope: !1525)
!1529 = !DILocation(line: 575, column: 31, scope: !1525)
!1530 = !DILocation(line: 575, column: 45, scope: !1525)
!1531 = !DILocation(line: 575, column: 22, scope: !1525)
!1532 = !DILocation(line: 575, column: 6, scope: !282)
!1533 = !DILocation(line: 576, column: 32, scope: !1534)
!1534 = distinct !DILexicalBlock(scope: !1525, file: !1, line: 575, column: 52)
!1535 = !DILocation(line: 576, column: 15, scope: !1534)
!1536 = !DILocation(line: 576, column: 19, scope: !1534)
!1537 = !DILocation(line: 576, column: 3, scope: !1534)
!1538 = !DILocation(line: 576, column: 10, scope: !1534)
!1539 = !DILocation(line: 576, column: 24, scope: !1534)
!1540 = !DILocation(line: 576, column: 30, scope: !1534)
!1541 = !DILocation(line: 577, column: 35, scope: !1534)
!1542 = !DILocation(line: 577, column: 15, scope: !1534)
!1543 = !DILocation(line: 577, column: 19, scope: !1534)
!1544 = !DILocation(line: 577, column: 3, scope: !1534)
!1545 = !DILocation(line: 577, column: 10, scope: !1534)
!1546 = !DILocation(line: 577, column: 24, scope: !1534)
!1547 = !DILocation(line: 577, column: 33, scope: !1534)
!1548 = !DILocation(line: 578, column: 29, scope: !1534)
!1549 = !DILocation(line: 578, column: 33, scope: !1534)
!1550 = !DILocation(line: 578, column: 17, scope: !1534)
!1551 = !DILocation(line: 578, column: 24, scope: !1534)
!1552 = !DILocation(line: 578, column: 3, scope: !1534)
!1553 = !DILocation(line: 579, column: 19, scope: !1534)
!1554 = !DILocation(line: 580, column: 2, scope: !1534)
!1555 = !DILocation(line: 582, column: 16, scope: !282)
!1556 = !DILocation(line: 583, column: 44, scope: !282)
!1557 = !DILocation(line: 583, column: 21, scope: !282)
!1558 = !DILocation(line: 583, column: 37, scope: !282)
!1559 = !DILocation(line: 583, column: 28, scope: !282)
!1560 = !DILocation(line: 583, column: 6, scope: !282)
!1561 = !DILocation(line: 583, column: 4, scope: !282)
!1562 = !DILocation(line: 582, column: 14, scope: !282)
!1563 = !DILocation(line: 584, column: 20, scope: !282)
!1564 = !DILocation(line: 585, column: 35, scope: !282)
!1565 = !DILocation(line: 585, column: 21, scope: !282)
!1566 = !DILocation(line: 585, column: 28, scope: !282)
!1567 = !DILocation(line: 585, column: 6, scope: !282)
!1568 = !DILocation(line: 585, column: 4, scope: !282)
!1569 = !DILocation(line: 584, column: 18, scope: !282)
!1570 = !DILocation(line: 587, column: 6, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !282, file: !1, line: 587, column: 6)
!1572 = !DILocation(line: 587, column: 20, scope: !1571)
!1573 = !DILocation(line: 587, column: 17, scope: !1571)
!1574 = !DILocation(line: 588, column: 4, scope: !1571)
!1575 = !DILocation(line: 588, column: 21, scope: !1576)
!1576 = !DILexicalBlockFile(scope: !1571, file: !1, discriminator: 1)
!1577 = !DILocation(line: 588, column: 25, scope: !1576)
!1578 = !DILocation(line: 588, column: 9, scope: !1576)
!1579 = !DILocation(line: 588, column: 16, scope: !1576)
!1580 = !DILocation(line: 588, column: 30, scope: !1576)
!1581 = !DILocation(line: 588, column: 41, scope: !1576)
!1582 = !DILocation(line: 588, column: 39, scope: !1576)
!1583 = !DILocation(line: 589, column: 5, scope: !1571)
!1584 = !DILocation(line: 589, column: 20, scope: !1576)
!1585 = !DILocation(line: 589, column: 24, scope: !1576)
!1586 = !DILocation(line: 589, column: 8, scope: !1576)
!1587 = !DILocation(line: 589, column: 15, scope: !1576)
!1588 = !DILocation(line: 589, column: 29, scope: !1576)
!1589 = !DILocation(line: 589, column: 39, scope: !1576)
!1590 = !DILocation(line: 587, column: 6, scope: !1591)
!1591 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 1)
!1592 = !DILocalVariable(name: "short_rep_price", scope: !1593, file: !1, line: 591, type: !230)
!1593 = distinct !DILexicalBlock(scope: !1571, file: !1, line: 589, column: 46)
!1594 = !DILocation(line: 591, column: 18, scope: !1593)
!1595 = !DILocation(line: 591, column: 36, scope: !1593)
!1596 = !DILocation(line: 592, column: 27, scope: !1593)
!1597 = !DILocation(line: 592, column: 34, scope: !1593)
!1598 = !DILocation(line: 592, column: 41, scope: !1593)
!1599 = !DILocation(line: 592, column: 7, scope: !1593)
!1600 = !DILocation(line: 592, column: 5, scope: !1593)
!1601 = !DILocation(line: 594, column: 7, scope: !1602)
!1602 = distinct !DILexicalBlock(scope: !1593, file: !1, line: 594, column: 7)
!1603 = !DILocation(line: 594, column: 38, scope: !1602)
!1604 = !DILocation(line: 594, column: 42, scope: !1602)
!1605 = !DILocation(line: 594, column: 26, scope: !1602)
!1606 = !DILocation(line: 594, column: 33, scope: !1602)
!1607 = !DILocation(line: 594, column: 47, scope: !1602)
!1608 = !DILocation(line: 594, column: 23, scope: !1602)
!1609 = !DILocation(line: 594, column: 7, scope: !1593)
!1610 = !DILocation(line: 595, column: 33, scope: !1611)
!1611 = distinct !DILexicalBlock(scope: !1602, file: !1, line: 594, column: 54)
!1612 = !DILocation(line: 595, column: 16, scope: !1611)
!1613 = !DILocation(line: 595, column: 20, scope: !1611)
!1614 = !DILocation(line: 595, column: 4, scope: !1611)
!1615 = !DILocation(line: 595, column: 11, scope: !1611)
!1616 = !DILocation(line: 595, column: 25, scope: !1611)
!1617 = !DILocation(line: 595, column: 31, scope: !1611)
!1618 = !DILocation(line: 596, column: 36, scope: !1611)
!1619 = !DILocation(line: 596, column: 16, scope: !1611)
!1620 = !DILocation(line: 596, column: 20, scope: !1611)
!1621 = !DILocation(line: 596, column: 4, scope: !1611)
!1622 = !DILocation(line: 596, column: 11, scope: !1611)
!1623 = !DILocation(line: 596, column: 25, scope: !1611)
!1624 = !DILocation(line: 596, column: 34, scope: !1611)
!1625 = !DILocation(line: 597, column: 32, scope: !1611)
!1626 = !DILocation(line: 597, column: 36, scope: !1611)
!1627 = !DILocation(line: 597, column: 20, scope: !1611)
!1628 = !DILocation(line: 597, column: 27, scope: !1611)
!1629 = !DILocation(line: 597, column: 4, scope: !1611)
!1630 = !DILocation(line: 598, column: 20, scope: !1611)
!1631 = !DILocation(line: 599, column: 3, scope: !1611)
!1632 = !DILocation(line: 600, column: 2, scope: !1593)
!1633 = !DILocation(line: 602, column: 6, scope: !1634)
!1634 = distinct !DILexicalBlock(scope: !282, file: !1, line: 602, column: 6)
!1635 = !DILocation(line: 602, column: 21, scope: !1634)
!1636 = !DILocation(line: 602, column: 6, scope: !282)
!1637 = !DILocation(line: 603, column: 10, scope: !1634)
!1638 = !DILocation(line: 603, column: 3, scope: !1634)
!1639 = !DILocation(line: 605, column: 14, scope: !282)
!1640 = !DILocation(line: 605, column: 14, scope: !1591)
!1641 = !DILocation(line: 605, column: 14, scope: !1642)
!1642 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 2)
!1643 = !DILocation(line: 605, column: 14, scope: !1644)
!1644 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 3)
!1645 = !DILocation(line: 605, column: 12, scope: !1644)
!1646 = !DILocation(line: 607, column: 7, scope: !1647)
!1647 = distinct !DILexicalBlock(scope: !282, file: !1, line: 607, column: 6)
!1648 = !DILocation(line: 607, column: 23, scope: !1647)
!1649 = !DILocation(line: 607, column: 26, scope: !1650)
!1650 = !DILexicalBlockFile(scope: !1647, file: !1, discriminator: 1)
!1651 = !DILocation(line: 607, column: 40, scope: !1650)
!1652 = !DILocation(line: 607, column: 37, scope: !1650)
!1653 = !DILocation(line: 607, column: 6, scope: !1650)
!1654 = !DILocalVariable(name: "buf_back", scope: !1655, file: !1, line: 609, type: !750)
!1655 = distinct !DILexicalBlock(scope: !1647, file: !1, line: 607, column: 54)
!1656 = !DILocation(line: 609, column: 24, scope: !1655)
!1657 = !DILocation(line: 609, column: 35, scope: !1655)
!1658 = !DILocation(line: 609, column: 41, scope: !1655)
!1659 = !DILocation(line: 609, column: 39, scope: !1655)
!1660 = !DILocation(line: 609, column: 49, scope: !1655)
!1661 = !DILocalVariable(name: "limit", scope: !1655, file: !1, line: 610, type: !230)
!1662 = !DILocation(line: 610, column: 18, scope: !1655)
!1663 = !DILocation(line: 610, column: 26, scope: !1655)
!1664 = !DILocation(line: 610, column: 26, scope: !1665)
!1665 = !DILexicalBlockFile(scope: !1655, file: !1, discriminator: 1)
!1666 = !DILocation(line: 610, column: 26, scope: !1667)
!1667 = !DILexicalBlockFile(scope: !1655, file: !1, discriminator: 2)
!1668 = !DILocation(line: 610, column: 26, scope: !1669)
!1669 = !DILexicalBlockFile(scope: !1655, file: !1, discriminator: 3)
!1670 = !DILocation(line: 610, column: 18, scope: !1669)
!1671 = !DILocalVariable(name: "len_test", scope: !1655, file: !1, line: 612, type: !13)
!1672 = !DILocation(line: 612, column: 12, scope: !1655)
!1673 = !DILocation(line: 613, column: 3, scope: !1655)
!1674 = !DILocation(line: 613, column: 10, scope: !1665)
!1675 = !DILocation(line: 613, column: 21, scope: !1665)
!1676 = !DILocation(line: 613, column: 19, scope: !1665)
!1677 = !DILocation(line: 613, column: 27, scope: !1665)
!1678 = !DILocation(line: 613, column: 34, scope: !1667)
!1679 = !DILocation(line: 613, column: 30, scope: !1667)
!1680 = !DILocation(line: 613, column: 56, scope: !1667)
!1681 = !DILocation(line: 613, column: 47, scope: !1667)
!1682 = !DILocation(line: 613, column: 44, scope: !1667)
!1683 = !DILocation(line: 613, column: 3, scope: !1669)
!1684 = !DILocation(line: 614, column: 4, scope: !1655)
!1685 = !DILocation(line: 613, column: 3, scope: !1686)
!1686 = !DILexicalBlockFile(scope: !1655, file: !1, discriminator: 4)
!1687 = !DILocation(line: 616, column: 3, scope: !1655)
!1688 = !DILocation(line: 618, column: 7, scope: !1689)
!1689 = distinct !DILexicalBlock(scope: !1655, file: !1, line: 618, column: 7)
!1690 = !DILocation(line: 618, column: 16, scope: !1689)
!1691 = !DILocation(line: 618, column: 7, scope: !1655)
!1692 = !DILocalVariable(name: "pos_state_next", scope: !1693, file: !1, line: 619, type: !13)
!1693 = distinct !DILexicalBlock(scope: !1689, file: !1, line: 618, column: 22)
!1694 = !DILocation(line: 619, column: 13, scope: !1693)
!1695 = !DILocalVariable(name: "next_rep_match_price", scope: !1693, file: !1, line: 620, type: !13)
!1696 = !DILocation(line: 620, column: 13, scope: !1693)
!1697 = !DILocalVariable(name: "offset", scope: !1693, file: !1, line: 621, type: !13)
!1698 = !DILocation(line: 621, column: 13, scope: !1693)
!1699 = !DILocalVariable(name: "cur_and_len_price", scope: !1693, file: !1, line: 622, type: !13)
!1700 = !DILocation(line: 622, column: 13, scope: !1693)
!1701 = !DILocalVariable(name: "state_2", scope: !1693, file: !1, line: 624, type: !78)
!1702 = !DILocation(line: 624, column: 20, scope: !1693)
!1703 = !DILocation(line: 624, column: 30, scope: !1693)
!1704 = !DILocation(line: 625, column: 4, scope: !1693)
!1705 = !DILocation(line: 625, column: 4, scope: !1706)
!1706 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 1)
!1707 = !DILocation(line: 625, column: 4, scope: !1708)
!1708 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 2)
!1709 = !DILocation(line: 625, column: 4, scope: !1710)
!1710 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 3)
!1711 = !DILocation(line: 625, column: 4, scope: !1712)
!1712 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 4)
!1713 = !DILocation(line: 625, column: 4, scope: !1714)
!1714 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 5)
!1715 = !DILocation(line: 625, column: 4, scope: !1716)
!1716 = !DILexicalBlockFile(scope: !1693, file: !1, discriminator: 6)
!1717 = !DILocation(line: 627, column: 22, scope: !1693)
!1718 = !DILocation(line: 627, column: 31, scope: !1693)
!1719 = !DILocation(line: 627, column: 38, scope: !1693)
!1720 = !DILocation(line: 627, column: 45, scope: !1693)
!1721 = !DILocation(line: 627, column: 36, scope: !1693)
!1722 = !DILocation(line: 627, column: 19, scope: !1693)
!1723 = !DILocation(line: 628, column: 27, scope: !1693)
!1724 = !DILocation(line: 629, column: 48, scope: !1693)
!1725 = !DILocation(line: 629, column: 23, scope: !1693)
!1726 = !DILocation(line: 629, column: 39, scope: !1693)
!1727 = !DILocation(line: 629, column: 30, scope: !1693)
!1728 = !DILocation(line: 629, column: 8, scope: !1693)
!1729 = !DILocation(line: 629, column: 6, scope: !1693)
!1730 = !DILocation(line: 630, column: 37, scope: !1693)
!1731 = !DILocation(line: 630, column: 23, scope: !1693)
!1732 = !DILocation(line: 630, column: 30, scope: !1693)
!1733 = !DILocation(line: 630, column: 8, scope: !1693)
!1734 = !DILocation(line: 630, column: 6, scope: !1693)
!1735 = !DILocation(line: 628, column: 25, scope: !1693)
!1736 = !DILocation(line: 633, column: 13, scope: !1693)
!1737 = !DILocation(line: 633, column: 17, scope: !1693)
!1738 = !DILocation(line: 633, column: 23, scope: !1693)
!1739 = !DILocation(line: 633, column: 21, scope: !1693)
!1740 = !DILocation(line: 633, column: 11, scope: !1693)
!1741 = !DILocation(line: 635, column: 4, scope: !1693)
!1742 = !DILocation(line: 635, column: 11, scope: !1706)
!1743 = !DILocation(line: 635, column: 21, scope: !1706)
!1744 = !DILocation(line: 635, column: 19, scope: !1706)
!1745 = !DILocation(line: 635, column: 4, scope: !1706)
!1746 = !DILocation(line: 636, column: 17, scope: !1693)
!1747 = !DILocation(line: 636, column: 5, scope: !1693)
!1748 = !DILocation(line: 636, column: 12, scope: !1693)
!1749 = !DILocation(line: 636, column: 28, scope: !1693)
!1750 = !DILocation(line: 636, column: 34, scope: !1693)
!1751 = !DILocation(line: 635, column: 4, scope: !1708)
!1752 = !DILocation(line: 638, column: 24, scope: !1693)
!1753 = !DILocation(line: 639, column: 22, scope: !1693)
!1754 = !DILocation(line: 639, column: 32, scope: !1693)
!1755 = !DILocation(line: 640, column: 7, scope: !1693)
!1756 = !DILocation(line: 640, column: 16, scope: !1693)
!1757 = !DILocation(line: 639, column: 8, scope: !1693)
!1758 = !DILocation(line: 639, column: 6, scope: !1693)
!1759 = !DILocation(line: 638, column: 22, scope: !1693)
!1760 = !DILocation(line: 642, column: 8, scope: !1761)
!1761 = distinct !DILexicalBlock(scope: !1693, file: !1, line: 642, column: 8)
!1762 = !DILocation(line: 642, column: 40, scope: !1761)
!1763 = !DILocation(line: 642, column: 28, scope: !1761)
!1764 = !DILocation(line: 642, column: 35, scope: !1761)
!1765 = !DILocation(line: 642, column: 48, scope: !1761)
!1766 = !DILocation(line: 642, column: 26, scope: !1761)
!1767 = !DILocation(line: 642, column: 8, scope: !1693)
!1768 = !DILocation(line: 643, column: 33, scope: !1769)
!1769 = distinct !DILexicalBlock(scope: !1761, file: !1, line: 642, column: 55)
!1770 = !DILocation(line: 643, column: 17, scope: !1769)
!1771 = !DILocation(line: 643, column: 5, scope: !1769)
!1772 = !DILocation(line: 643, column: 12, scope: !1769)
!1773 = !DILocation(line: 643, column: 25, scope: !1769)
!1774 = !DILocation(line: 643, column: 31, scope: !1769)
!1775 = !DILocation(line: 644, column: 36, scope: !1769)
!1776 = !DILocation(line: 644, column: 40, scope: !1769)
!1777 = !DILocation(line: 644, column: 17, scope: !1769)
!1778 = !DILocation(line: 644, column: 5, scope: !1769)
!1779 = !DILocation(line: 644, column: 12, scope: !1769)
!1780 = !DILocation(line: 644, column: 25, scope: !1769)
!1781 = !DILocation(line: 644, column: 34, scope: !1769)
!1782 = !DILocation(line: 645, column: 17, scope: !1769)
!1783 = !DILocation(line: 645, column: 5, scope: !1769)
!1784 = !DILocation(line: 645, column: 12, scope: !1769)
!1785 = !DILocation(line: 645, column: 25, scope: !1769)
!1786 = !DILocation(line: 645, column: 35, scope: !1769)
!1787 = !DILocation(line: 646, column: 17, scope: !1769)
!1788 = !DILocation(line: 646, column: 5, scope: !1769)
!1789 = !DILocation(line: 646, column: 12, scope: !1769)
!1790 = !DILocation(line: 646, column: 25, scope: !1769)
!1791 = !DILocation(line: 646, column: 43, scope: !1769)
!1792 = !DILocation(line: 647, column: 17, scope: !1769)
!1793 = !DILocation(line: 647, column: 5, scope: !1769)
!1794 = !DILocation(line: 647, column: 12, scope: !1769)
!1795 = !DILocation(line: 647, column: 25, scope: !1769)
!1796 = !DILocation(line: 647, column: 32, scope: !1769)
!1797 = !DILocation(line: 648, column: 4, scope: !1769)
!1798 = !DILocation(line: 650, column: 3, scope: !1693)
!1799 = !DILocation(line: 651, column: 2, scope: !1655)
!1800 = !DILocation(line: 654, column: 17, scope: !1801)
!1801 = distinct !DILexicalBlock(scope: !282, file: !1, line: 654, column: 2)
!1802 = !DILocation(line: 654, column: 7, scope: !1801)
!1803 = !DILocation(line: 654, column: 22, scope: !1804)
!1804 = !DILexicalBlockFile(scope: !1805, file: !1, discriminator: 1)
!1805 = distinct !DILexicalBlock(scope: !1801, file: !1, line: 654, column: 2)
!1806 = !DILocation(line: 654, column: 32, scope: !1804)
!1807 = !DILocation(line: 654, column: 2, scope: !1804)
!1808 = !DILocalVariable(name: "len_test", scope: !1809, file: !1, line: 655, type: !13)
!1809 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 654, column: 62)
!1810 = !DILocation(line: 655, column: 12, scope: !1809)
!1811 = !DILocalVariable(name: "len_test_2", scope: !1809, file: !1, line: 655, type: !13)
!1812 = !DILocation(line: 655, column: 22, scope: !1809)
!1813 = !DILocalVariable(name: "len_test_temp", scope: !1809, file: !1, line: 655, type: !13)
!1814 = !DILocation(line: 655, column: 34, scope: !1809)
!1815 = !DILocalVariable(name: "price", scope: !1809, file: !1, line: 656, type: !13)
!1816 = !DILocation(line: 656, column: 12, scope: !1809)
!1817 = !DILocalVariable(name: "limit", scope: !1809, file: !1, line: 656, type: !13)
!1818 = !DILocation(line: 656, column: 19, scope: !1809)
!1819 = !DILocalVariable(name: "buf_back", scope: !1809, file: !1, line: 658, type: !750)
!1820 = !DILocation(line: 658, column: 24, scope: !1809)
!1821 = !DILocation(line: 658, column: 35, scope: !1809)
!1822 = !DILocation(line: 658, column: 46, scope: !1809)
!1823 = !DILocation(line: 658, column: 41, scope: !1809)
!1824 = !DILocation(line: 658, column: 39, scope: !1809)
!1825 = !DILocation(line: 658, column: 57, scope: !1809)
!1826 = !DILocation(line: 659, column: 7, scope: !1827)
!1827 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 659, column: 7)
!1828 = !DILocation(line: 659, column: 7, scope: !1809)
!1829 = !DILocation(line: 660, column: 4, scope: !1827)
!1830 = !DILocation(line: 662, column: 17, scope: !1831)
!1831 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 662, column: 3)
!1832 = !DILocation(line: 662, column: 8, scope: !1831)
!1833 = !DILocation(line: 662, column: 22, scope: !1834)
!1834 = !DILexicalBlockFile(scope: !1835, file: !1, discriminator: 1)
!1835 = distinct !DILexicalBlock(scope: !1831, file: !1, line: 662, column: 3)
!1836 = !DILocation(line: 662, column: 33, scope: !1834)
!1837 = !DILocation(line: 662, column: 31, scope: !1834)
!1838 = !DILocation(line: 663, column: 5, scope: !1835)
!1839 = !DILocation(line: 663, column: 12, scope: !1834)
!1840 = !DILocation(line: 663, column: 8, scope: !1834)
!1841 = !DILocation(line: 663, column: 34, scope: !1834)
!1842 = !DILocation(line: 663, column: 25, scope: !1834)
!1843 = !DILocation(line: 663, column: 22, scope: !1834)
!1844 = !DILocation(line: 662, column: 3, scope: !1845)
!1845 = !DILexicalBlockFile(scope: !1831, file: !1, discriminator: 2)
!1846 = !DILocation(line: 662, column: 3, scope: !1847)
!1847 = !DILexicalBlockFile(scope: !1831, file: !1, discriminator: 3)
!1848 = !DILocation(line: 664, column: 5, scope: !1835)
!1849 = !DILocation(line: 662, column: 3, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !1835, file: !1, discriminator: 4)
!1851 = !DILocation(line: 666, column: 3, scope: !1809)
!1852 = !DILocation(line: 666, column: 10, scope: !1853)
!1853 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 1)
!1854 = !DILocation(line: 666, column: 20, scope: !1853)
!1855 = !DILocation(line: 666, column: 26, scope: !1853)
!1856 = !DILocation(line: 666, column: 24, scope: !1853)
!1857 = !DILocation(line: 666, column: 18, scope: !1853)
!1858 = !DILocation(line: 666, column: 3, scope: !1853)
!1859 = !DILocation(line: 667, column: 16, scope: !1809)
!1860 = !DILocation(line: 667, column: 4, scope: !1809)
!1861 = !DILocation(line: 667, column: 11, scope: !1809)
!1862 = !DILocation(line: 667, column: 27, scope: !1809)
!1863 = !DILocation(line: 667, column: 33, scope: !1809)
!1864 = !DILocation(line: 666, column: 3, scope: !1865)
!1865 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 2)
!1866 = !DILocation(line: 669, column: 19, scope: !1809)
!1867 = !DILocation(line: 669, column: 17, scope: !1809)
!1868 = !DILocation(line: 670, column: 11, scope: !1809)
!1869 = !DILocation(line: 671, column: 5, scope: !1809)
!1870 = !DILocation(line: 671, column: 12, scope: !1809)
!1871 = !DILocation(line: 671, column: 23, scope: !1809)
!1872 = !DILocation(line: 671, column: 30, scope: !1809)
!1873 = !DILocation(line: 670, column: 29, scope: !1809)
!1874 = !DILocation(line: 670, column: 27, scope: !1809)
!1875 = !DILocation(line: 670, column: 9, scope: !1809)
!1876 = !DILocation(line: 673, column: 3, scope: !1809)
!1877 = !DILocalVariable(name: "cur_and_len_price", scope: !1878, file: !1, line: 674, type: !230)
!1878 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 673, column: 6)
!1879 = !DILocation(line: 674, column: 19, scope: !1878)
!1880 = !DILocation(line: 674, column: 39, scope: !1878)
!1881 = !DILocation(line: 675, column: 23, scope: !1878)
!1882 = !DILocation(line: 675, column: 30, scope: !1878)
!1883 = !DILocation(line: 676, column: 8, scope: !1878)
!1884 = !DILocation(line: 676, column: 18, scope: !1878)
!1885 = !DILocation(line: 675, column: 8, scope: !1878)
!1886 = !DILocation(line: 675, column: 6, scope: !1878)
!1887 = !DILocation(line: 678, column: 8, scope: !1888)
!1888 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 678, column: 8)
!1889 = !DILocation(line: 678, column: 40, scope: !1888)
!1890 = !DILocation(line: 678, column: 46, scope: !1888)
!1891 = !DILocation(line: 678, column: 44, scope: !1888)
!1892 = !DILocation(line: 678, column: 28, scope: !1888)
!1893 = !DILocation(line: 678, column: 35, scope: !1888)
!1894 = !DILocation(line: 678, column: 56, scope: !1888)
!1895 = !DILocation(line: 678, column: 26, scope: !1888)
!1896 = !DILocation(line: 678, column: 8, scope: !1878)
!1897 = !DILocation(line: 679, column: 41, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !1888, file: !1, line: 678, column: 63)
!1899 = !DILocation(line: 679, column: 17, scope: !1898)
!1900 = !DILocation(line: 679, column: 23, scope: !1898)
!1901 = !DILocation(line: 679, column: 21, scope: !1898)
!1902 = !DILocation(line: 679, column: 5, scope: !1898)
!1903 = !DILocation(line: 679, column: 12, scope: !1898)
!1904 = !DILocation(line: 679, column: 33, scope: !1898)
!1905 = !DILocation(line: 679, column: 39, scope: !1898)
!1906 = !DILocation(line: 680, column: 44, scope: !1898)
!1907 = !DILocation(line: 680, column: 17, scope: !1898)
!1908 = !DILocation(line: 680, column: 23, scope: !1898)
!1909 = !DILocation(line: 680, column: 21, scope: !1898)
!1910 = !DILocation(line: 680, column: 5, scope: !1898)
!1911 = !DILocation(line: 680, column: 12, scope: !1898)
!1912 = !DILocation(line: 680, column: 33, scope: !1898)
!1913 = !DILocation(line: 680, column: 42, scope: !1898)
!1914 = !DILocation(line: 681, column: 45, scope: !1898)
!1915 = !DILocation(line: 681, column: 17, scope: !1898)
!1916 = !DILocation(line: 681, column: 23, scope: !1898)
!1917 = !DILocation(line: 681, column: 21, scope: !1898)
!1918 = !DILocation(line: 681, column: 5, scope: !1898)
!1919 = !DILocation(line: 681, column: 12, scope: !1898)
!1920 = !DILocation(line: 681, column: 33, scope: !1898)
!1921 = !DILocation(line: 681, column: 43, scope: !1898)
!1922 = !DILocation(line: 682, column: 17, scope: !1898)
!1923 = !DILocation(line: 682, column: 23, scope: !1898)
!1924 = !DILocation(line: 682, column: 21, scope: !1898)
!1925 = !DILocation(line: 682, column: 5, scope: !1898)
!1926 = !DILocation(line: 682, column: 12, scope: !1898)
!1927 = !DILocation(line: 682, column: 33, scope: !1898)
!1928 = !DILocation(line: 682, column: 51, scope: !1898)
!1929 = !DILocation(line: 683, column: 4, scope: !1898)
!1930 = !DILocation(line: 684, column: 3, scope: !1878)
!1931 = !DILocation(line: 684, column: 12, scope: !1853)
!1932 = !DILocation(line: 684, column: 23, scope: !1853)
!1933 = !DILocation(line: 684, column: 3, scope: !1853)
!1934 = !DILocation(line: 686, column: 14, scope: !1809)
!1935 = !DILocation(line: 686, column: 12, scope: !1809)
!1936 = !DILocation(line: 688, column: 7, scope: !1937)
!1937 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 688, column: 7)
!1938 = !DILocation(line: 688, column: 17, scope: !1937)
!1939 = !DILocation(line: 688, column: 7, scope: !1809)
!1940 = !DILocation(line: 689, column: 16, scope: !1937)
!1941 = !DILocation(line: 689, column: 25, scope: !1937)
!1942 = !DILocation(line: 689, column: 14, scope: !1937)
!1943 = !DILocation(line: 689, column: 4, scope: !1937)
!1944 = !DILocation(line: 692, column: 16, scope: !1809)
!1945 = !DILocation(line: 692, column: 25, scope: !1809)
!1946 = !DILocation(line: 692, column: 14, scope: !1809)
!1947 = !DILocation(line: 693, column: 11, scope: !1809)
!1948 = !DILocation(line: 693, column: 11, scope: !1853)
!1949 = !DILocation(line: 693, column: 11, scope: !1865)
!1950 = !DILocation(line: 693, column: 11, scope: !1951)
!1951 = !DILexicalBlockFile(scope: !1809, file: !1, discriminator: 3)
!1952 = !DILocation(line: 693, column: 9, scope: !1951)
!1953 = !DILocation(line: 695, column: 3, scope: !1809)
!1954 = !DILocation(line: 695, column: 10, scope: !1955)
!1955 = !DILexicalBlockFile(scope: !1956, file: !1, discriminator: 1)
!1956 = distinct !DILexicalBlock(scope: !1957, file: !1, line: 695, column: 3)
!1957 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 695, column: 3)
!1958 = !DILocation(line: 695, column: 23, scope: !1955)
!1959 = !DILocation(line: 695, column: 21, scope: !1955)
!1960 = !DILocation(line: 696, column: 5, scope: !1956)
!1961 = !DILocation(line: 696, column: 12, scope: !1955)
!1962 = !DILocation(line: 696, column: 8, scope: !1955)
!1963 = !DILocation(line: 696, column: 36, scope: !1955)
!1964 = !DILocation(line: 696, column: 27, scope: !1955)
!1965 = !DILocation(line: 696, column: 24, scope: !1955)
!1966 = !DILocation(line: 695, column: 3, scope: !1967)
!1967 = !DILexicalBlockFile(scope: !1957, file: !1, discriminator: 2)
!1968 = !DILocation(line: 695, column: 3, scope: !1969)
!1969 = !DILexicalBlockFile(scope: !1957, file: !1, discriminator: 3)
!1970 = !DILocation(line: 697, column: 5, scope: !1956)
!1971 = !DILocation(line: 695, column: 3, scope: !1972)
!1972 = !DILexicalBlockFile(scope: !1956, file: !1, discriminator: 4)
!1973 = !DILocation(line: 699, column: 17, scope: !1809)
!1974 = !DILocation(line: 699, column: 26, scope: !1809)
!1975 = !DILocation(line: 699, column: 14, scope: !1809)
!1976 = !DILocation(line: 701, column: 7, scope: !1977)
!1977 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 701, column: 7)
!1978 = !DILocation(line: 701, column: 18, scope: !1977)
!1979 = !DILocation(line: 701, column: 7, scope: !1809)
!1980 = !DILocalVariable(name: "pos_state_next", scope: !1981, file: !1, line: 702, type: !13)
!1981 = distinct !DILexicalBlock(scope: !1977, file: !1, line: 701, column: 24)
!1982 = !DILocation(line: 702, column: 13, scope: !1981)
!1983 = !DILocalVariable(name: "cur_and_len_literal_price", scope: !1981, file: !1, line: 703, type: !13)
!1984 = !DILocation(line: 703, column: 13, scope: !1981)
!1985 = !DILocalVariable(name: "next_rep_match_price", scope: !1981, file: !1, line: 704, type: !13)
!1986 = !DILocation(line: 704, column: 13, scope: !1981)
!1987 = !DILocalVariable(name: "offset", scope: !1981, file: !1, line: 705, type: !13)
!1988 = !DILocation(line: 705, column: 13, scope: !1981)
!1989 = !DILocalVariable(name: "cur_and_len_price", scope: !1981, file: !1, line: 706, type: !13)
!1990 = !DILocation(line: 706, column: 13, scope: !1981)
!1991 = !DILocalVariable(name: "state_2", scope: !1981, file: !1, line: 708, type: !78)
!1992 = !DILocation(line: 708, column: 20, scope: !1981)
!1993 = !DILocation(line: 708, column: 30, scope: !1981)
!1994 = !DILocation(line: 709, column: 4, scope: !1981)
!1995 = !DILocation(line: 711, column: 22, scope: !1981)
!1996 = !DILocation(line: 711, column: 33, scope: !1981)
!1997 = !DILocation(line: 711, column: 31, scope: !1981)
!1998 = !DILocation(line: 711, column: 45, scope: !1981)
!1999 = !DILocation(line: 711, column: 52, scope: !1981)
!2000 = !DILocation(line: 711, column: 43, scope: !1981)
!2001 = !DILocation(line: 711, column: 19, scope: !1981)
!2002 = !DILocation(line: 713, column: 32, scope: !1981)
!2003 = !DILocation(line: 714, column: 23, scope: !1981)
!2004 = !DILocation(line: 714, column: 30, scope: !1981)
!2005 = !DILocation(line: 715, column: 7, scope: !1981)
!2006 = !DILocation(line: 715, column: 17, scope: !1981)
!2007 = !DILocation(line: 714, column: 8, scope: !1981)
!2008 = !DILocation(line: 714, column: 6, scope: !1981)
!2009 = !DILocation(line: 716, column: 48, scope: !1981)
!2010 = !DILocation(line: 716, column: 23, scope: !1981)
!2011 = !DILocation(line: 716, column: 39, scope: !1981)
!2012 = !DILocation(line: 716, column: 30, scope: !1981)
!2013 = !DILocation(line: 716, column: 8, scope: !1981)
!2014 = !DILocation(line: 716, column: 6, scope: !1981)
!2015 = !DILocation(line: 717, column: 26, scope: !1981)
!2016 = !DILocation(line: 717, column: 33, scope: !1981)
!2017 = !DILocation(line: 717, column: 44, scope: !1981)
!2018 = !DILocation(line: 717, column: 42, scope: !1981)
!2019 = !DILocation(line: 718, column: 11, scope: !1981)
!2020 = !DILocation(line: 718, column: 20, scope: !1981)
!2021 = !DILocation(line: 718, column: 7, scope: !1981)
!2022 = !DILocation(line: 719, column: 16, scope: !1981)
!2023 = !DILocation(line: 719, column: 7, scope: !1981)
!2024 = !DILocation(line: 719, column: 31, scope: !1981)
!2025 = !DILocation(line: 719, column: 27, scope: !1981)
!2026 = !DILocation(line: 717, column: 8, scope: !1981)
!2027 = !DILocation(line: 717, column: 6, scope: !1981)
!2028 = !DILocation(line: 713, column: 30, scope: !1981)
!2029 = !DILocation(line: 721, column: 4, scope: !1981)
!2030 = !DILocation(line: 721, column: 4, scope: !2031)
!2031 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 1)
!2032 = !DILocation(line: 721, column: 4, scope: !2033)
!2033 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 2)
!2034 = !DILocation(line: 721, column: 4, scope: !2035)
!2035 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 3)
!2036 = !DILocation(line: 721, column: 4, scope: !2037)
!2037 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 4)
!2038 = !DILocation(line: 721, column: 4, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 5)
!2040 = !DILocation(line: 721, column: 4, scope: !2041)
!2041 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 6)
!2042 = !DILocation(line: 723, column: 22, scope: !1981)
!2043 = !DILocation(line: 723, column: 33, scope: !1981)
!2044 = !DILocation(line: 723, column: 31, scope: !1981)
!2045 = !DILocation(line: 723, column: 42, scope: !1981)
!2046 = !DILocation(line: 723, column: 49, scope: !1981)
!2047 = !DILocation(line: 723, column: 56, scope: !1981)
!2048 = !DILocation(line: 723, column: 47, scope: !1981)
!2049 = !DILocation(line: 723, column: 19, scope: !1981)
!2050 = !DILocation(line: 725, column: 27, scope: !1981)
!2051 = !DILocation(line: 726, column: 48, scope: !1981)
!2052 = !DILocation(line: 726, column: 23, scope: !1981)
!2053 = !DILocation(line: 726, column: 39, scope: !1981)
!2054 = !DILocation(line: 726, column: 30, scope: !1981)
!2055 = !DILocation(line: 726, column: 8, scope: !1981)
!2056 = !DILocation(line: 726, column: 6, scope: !1981)
!2057 = !DILocation(line: 727, column: 37, scope: !1981)
!2058 = !DILocation(line: 727, column: 23, scope: !1981)
!2059 = !DILocation(line: 727, column: 30, scope: !1981)
!2060 = !DILocation(line: 727, column: 8, scope: !1981)
!2061 = !DILocation(line: 727, column: 6, scope: !1981)
!2062 = !DILocation(line: 725, column: 25, scope: !1981)
!2063 = !DILocation(line: 730, column: 13, scope: !1981)
!2064 = !DILocation(line: 730, column: 19, scope: !1981)
!2065 = !DILocation(line: 730, column: 17, scope: !1981)
!2066 = !DILocation(line: 730, column: 28, scope: !1981)
!2067 = !DILocation(line: 730, column: 34, scope: !1981)
!2068 = !DILocation(line: 730, column: 32, scope: !1981)
!2069 = !DILocation(line: 730, column: 11, scope: !1981)
!2070 = !DILocation(line: 732, column: 4, scope: !1981)
!2071 = !DILocation(line: 732, column: 11, scope: !2031)
!2072 = !DILocation(line: 732, column: 21, scope: !2031)
!2073 = !DILocation(line: 732, column: 19, scope: !2031)
!2074 = !DILocation(line: 732, column: 4, scope: !2031)
!2075 = !DILocation(line: 733, column: 17, scope: !1981)
!2076 = !DILocation(line: 733, column: 5, scope: !1981)
!2077 = !DILocation(line: 733, column: 12, scope: !1981)
!2078 = !DILocation(line: 733, column: 28, scope: !1981)
!2079 = !DILocation(line: 733, column: 34, scope: !1981)
!2080 = !DILocation(line: 732, column: 4, scope: !2033)
!2081 = !DILocation(line: 735, column: 24, scope: !1981)
!2082 = !DILocation(line: 736, column: 22, scope: !1981)
!2083 = !DILocation(line: 736, column: 32, scope: !1981)
!2084 = !DILocation(line: 737, column: 7, scope: !1981)
!2085 = !DILocation(line: 737, column: 16, scope: !1981)
!2086 = !DILocation(line: 736, column: 8, scope: !1981)
!2087 = !DILocation(line: 736, column: 6, scope: !1981)
!2088 = !DILocation(line: 735, column: 22, scope: !1981)
!2089 = !DILocation(line: 739, column: 8, scope: !2090)
!2090 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 739, column: 8)
!2091 = !DILocation(line: 739, column: 40, scope: !2090)
!2092 = !DILocation(line: 739, column: 28, scope: !2090)
!2093 = !DILocation(line: 739, column: 35, scope: !2090)
!2094 = !DILocation(line: 739, column: 48, scope: !2090)
!2095 = !DILocation(line: 739, column: 26, scope: !2090)
!2096 = !DILocation(line: 739, column: 8, scope: !1981)
!2097 = !DILocation(line: 740, column: 33, scope: !2098)
!2098 = distinct !DILexicalBlock(scope: !2090, file: !1, line: 739, column: 55)
!2099 = !DILocation(line: 740, column: 17, scope: !2098)
!2100 = !DILocation(line: 740, column: 5, scope: !2098)
!2101 = !DILocation(line: 740, column: 12, scope: !2098)
!2102 = !DILocation(line: 740, column: 25, scope: !2098)
!2103 = !DILocation(line: 740, column: 31, scope: !2098)
!2104 = !DILocation(line: 741, column: 36, scope: !2098)
!2105 = !DILocation(line: 741, column: 42, scope: !2098)
!2106 = !DILocation(line: 741, column: 40, scope: !2098)
!2107 = !DILocation(line: 741, column: 51, scope: !2098)
!2108 = !DILocation(line: 741, column: 17, scope: !2098)
!2109 = !DILocation(line: 741, column: 5, scope: !2098)
!2110 = !DILocation(line: 741, column: 12, scope: !2098)
!2111 = !DILocation(line: 741, column: 25, scope: !2098)
!2112 = !DILocation(line: 741, column: 34, scope: !2098)
!2113 = !DILocation(line: 742, column: 17, scope: !2098)
!2114 = !DILocation(line: 742, column: 5, scope: !2098)
!2115 = !DILocation(line: 742, column: 12, scope: !2098)
!2116 = !DILocation(line: 742, column: 25, scope: !2098)
!2117 = !DILocation(line: 742, column: 35, scope: !2098)
!2118 = !DILocation(line: 743, column: 17, scope: !2098)
!2119 = !DILocation(line: 743, column: 5, scope: !2098)
!2120 = !DILocation(line: 743, column: 12, scope: !2098)
!2121 = !DILocation(line: 743, column: 25, scope: !2098)
!2122 = !DILocation(line: 743, column: 43, scope: !2098)
!2123 = !DILocation(line: 744, column: 17, scope: !2098)
!2124 = !DILocation(line: 744, column: 5, scope: !2098)
!2125 = !DILocation(line: 744, column: 12, scope: !2098)
!2126 = !DILocation(line: 744, column: 25, scope: !2098)
!2127 = !DILocation(line: 744, column: 32, scope: !2098)
!2128 = !DILocation(line: 745, column: 38, scope: !2098)
!2129 = !DILocation(line: 745, column: 17, scope: !2098)
!2130 = !DILocation(line: 745, column: 5, scope: !2098)
!2131 = !DILocation(line: 745, column: 12, scope: !2098)
!2132 = !DILocation(line: 745, column: 25, scope: !2098)
!2133 = !DILocation(line: 745, column: 36, scope: !2098)
!2134 = !DILocation(line: 746, column: 39, scope: !2098)
!2135 = !DILocation(line: 746, column: 17, scope: !2098)
!2136 = !DILocation(line: 746, column: 5, scope: !2098)
!2137 = !DILocation(line: 746, column: 12, scope: !2098)
!2138 = !DILocation(line: 746, column: 25, scope: !2098)
!2139 = !DILocation(line: 746, column: 37, scope: !2098)
!2140 = !DILocation(line: 747, column: 4, scope: !2098)
!2141 = !DILocation(line: 749, column: 3, scope: !1981)
!2142 = !DILocation(line: 750, column: 2, scope: !1809)
!2143 = !DILocation(line: 654, column: 49, scope: !2144)
!2144 = !DILexicalBlockFile(scope: !1805, file: !1, discriminator: 2)
!2145 = !DILocation(line: 654, column: 2, scope: !2144)
!2146 = !DILocation(line: 754, column: 6, scope: !2147)
!2147 = distinct !DILexicalBlock(scope: !282, file: !1, line: 754, column: 6)
!2148 = !DILocation(line: 754, column: 16, scope: !2147)
!2149 = !DILocation(line: 754, column: 14, scope: !2147)
!2150 = !DILocation(line: 754, column: 6, scope: !282)
!2151 = !DILocation(line: 755, column: 13, scope: !2152)
!2152 = distinct !DILexicalBlock(scope: !2147, file: !1, line: 754, column: 27)
!2153 = !DILocation(line: 755, column: 11, scope: !2152)
!2154 = !DILocation(line: 757, column: 17, scope: !2152)
!2155 = !DILocation(line: 758, column: 3, scope: !2152)
!2156 = !DILocation(line: 758, column: 10, scope: !2157)
!2157 = !DILexicalBlockFile(scope: !2152, file: !1, discriminator: 1)
!2158 = !DILocation(line: 758, column: 35, scope: !2157)
!2159 = !DILocation(line: 758, column: 20, scope: !2157)
!2160 = !DILocation(line: 758, column: 27, scope: !2157)
!2161 = !DILocation(line: 758, column: 50, scope: !2157)
!2162 = !DILocation(line: 758, column: 18, scope: !2157)
!2163 = !DILocation(line: 758, column: 3, scope: !2157)
!2164 = !DILocation(line: 759, column: 4, scope: !2152)
!2165 = !DILocation(line: 758, column: 3, scope: !2166)
!2166 = !DILexicalBlockFile(scope: !2152, file: !1, discriminator: 2)
!2167 = !DILocation(line: 761, column: 41, scope: !2152)
!2168 = !DILocation(line: 761, column: 31, scope: !2152)
!2169 = !DILocation(line: 761, column: 3, scope: !2152)
!2170 = !DILocation(line: 761, column: 10, scope: !2152)
!2171 = !DILocation(line: 761, column: 35, scope: !2152)
!2172 = !DILocation(line: 761, column: 39, scope: !2152)
!2173 = !DILocation(line: 762, column: 2, scope: !2152)
!2174 = !DILocation(line: 765, column: 6, scope: !2175)
!2175 = distinct !DILexicalBlock(scope: !282, file: !1, line: 765, column: 6)
!2176 = !DILocation(line: 765, column: 17, scope: !2175)
!2177 = !DILocation(line: 765, column: 14, scope: !2175)
!2178 = !DILocation(line: 765, column: 6, scope: !282)
!2179 = !DILocalVariable(name: "len_test", scope: !2180, file: !1, line: 766, type: !13)
!2180 = distinct !DILexicalBlock(scope: !2175, file: !1, line: 765, column: 28)
!2181 = !DILocation(line: 766, column: 12, scope: !2180)
!2182 = !DILocalVariable(name: "i", scope: !2180, file: !1, line: 767, type: !13)
!2183 = !DILocation(line: 767, column: 12, scope: !2180)
!2184 = !DILocalVariable(name: "normal_match_price", scope: !2180, file: !1, line: 769, type: !230)
!2185 = !DILocation(line: 769, column: 18, scope: !2180)
!2186 = !DILocation(line: 769, column: 39, scope: !2180)
!2187 = !DILocation(line: 770, column: 36, scope: !2180)
!2188 = !DILocation(line: 770, column: 22, scope: !2180)
!2189 = !DILocation(line: 770, column: 29, scope: !2180)
!2190 = !DILocation(line: 770, column: 7, scope: !2180)
!2191 = !DILocation(line: 770, column: 5, scope: !2180)
!2192 = !DILocation(line: 772, column: 3, scope: !2180)
!2193 = !DILocation(line: 772, column: 10, scope: !2194)
!2194 = !DILexicalBlockFile(scope: !2180, file: !1, discriminator: 1)
!2195 = !DILocation(line: 772, column: 20, scope: !2194)
!2196 = !DILocation(line: 772, column: 26, scope: !2194)
!2197 = !DILocation(line: 772, column: 24, scope: !2194)
!2198 = !DILocation(line: 772, column: 18, scope: !2194)
!2199 = !DILocation(line: 772, column: 3, scope: !2194)
!2200 = !DILocation(line: 773, column: 16, scope: !2180)
!2201 = !DILocation(line: 773, column: 4, scope: !2180)
!2202 = !DILocation(line: 773, column: 11, scope: !2180)
!2203 = !DILocation(line: 773, column: 27, scope: !2180)
!2204 = !DILocation(line: 773, column: 33, scope: !2180)
!2205 = !DILocation(line: 772, column: 3, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2180, file: !1, discriminator: 2)
!2207 = !DILocation(line: 775, column: 3, scope: !2180)
!2208 = !DILocation(line: 775, column: 10, scope: !2194)
!2209 = !DILocation(line: 775, column: 37, scope: !2194)
!2210 = !DILocation(line: 775, column: 22, scope: !2194)
!2211 = !DILocation(line: 775, column: 29, scope: !2194)
!2212 = !DILocation(line: 775, column: 40, scope: !2194)
!2213 = !DILocation(line: 775, column: 20, scope: !2194)
!2214 = !DILocation(line: 775, column: 3, scope: !2194)
!2215 = !DILocation(line: 776, column: 4, scope: !2180)
!2216 = !DILocation(line: 775, column: 3, scope: !2206)
!2217 = !DILocation(line: 778, column: 19, scope: !2218)
!2218 = distinct !DILexicalBlock(scope: !2180, file: !1, line: 778, column: 3)
!2219 = !DILocation(line: 778, column: 17, scope: !2218)
!2220 = !DILocation(line: 778, column: 8, scope: !2218)
!2221 = !DILocalVariable(name: "cur_back", scope: !2222, file: !1, line: 779, type: !230)
!2222 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 778, column: 44)
!2223 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 778, column: 3)
!2224 = !DILocation(line: 779, column: 19, scope: !2222)
!2225 = !DILocation(line: 779, column: 45, scope: !2222)
!2226 = !DILocation(line: 779, column: 30, scope: !2222)
!2227 = !DILocation(line: 779, column: 37, scope: !2222)
!2228 = !DILocation(line: 779, column: 48, scope: !2222)
!2229 = !DILocalVariable(name: "cur_and_len_price", scope: !2222, file: !1, line: 780, type: !13)
!2230 = !DILocation(line: 780, column: 13, scope: !2222)
!2231 = !DILocation(line: 780, column: 33, scope: !2222)
!2232 = !DILocation(line: 781, column: 26, scope: !2222)
!2233 = !DILocation(line: 782, column: 7, scope: !2222)
!2234 = !DILocation(line: 782, column: 17, scope: !2222)
!2235 = !DILocation(line: 782, column: 27, scope: !2222)
!2236 = !DILocation(line: 781, column: 8, scope: !2222)
!2237 = !DILocation(line: 781, column: 6, scope: !2222)
!2238 = !DILocation(line: 784, column: 8, scope: !2239)
!2239 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 784, column: 8)
!2240 = !DILocation(line: 784, column: 40, scope: !2239)
!2241 = !DILocation(line: 784, column: 46, scope: !2239)
!2242 = !DILocation(line: 784, column: 44, scope: !2239)
!2243 = !DILocation(line: 784, column: 28, scope: !2239)
!2244 = !DILocation(line: 784, column: 35, scope: !2239)
!2245 = !DILocation(line: 784, column: 56, scope: !2239)
!2246 = !DILocation(line: 784, column: 26, scope: !2239)
!2247 = !DILocation(line: 784, column: 8, scope: !2222)
!2248 = !DILocation(line: 785, column: 41, scope: !2249)
!2249 = distinct !DILexicalBlock(scope: !2239, file: !1, line: 784, column: 63)
!2250 = !DILocation(line: 785, column: 17, scope: !2249)
!2251 = !DILocation(line: 785, column: 23, scope: !2249)
!2252 = !DILocation(line: 785, column: 21, scope: !2249)
!2253 = !DILocation(line: 785, column: 5, scope: !2249)
!2254 = !DILocation(line: 785, column: 12, scope: !2249)
!2255 = !DILocation(line: 785, column: 33, scope: !2249)
!2256 = !DILocation(line: 785, column: 39, scope: !2249)
!2257 = !DILocation(line: 786, column: 44, scope: !2249)
!2258 = !DILocation(line: 786, column: 17, scope: !2249)
!2259 = !DILocation(line: 786, column: 23, scope: !2249)
!2260 = !DILocation(line: 786, column: 21, scope: !2249)
!2261 = !DILocation(line: 786, column: 5, scope: !2249)
!2262 = !DILocation(line: 786, column: 12, scope: !2249)
!2263 = !DILocation(line: 786, column: 33, scope: !2249)
!2264 = !DILocation(line: 786, column: 42, scope: !2249)
!2265 = !DILocation(line: 788, column: 9, scope: !2249)
!2266 = !DILocation(line: 788, column: 18, scope: !2249)
!2267 = !DILocation(line: 787, column: 17, scope: !2249)
!2268 = !DILocation(line: 787, column: 23, scope: !2249)
!2269 = !DILocation(line: 787, column: 21, scope: !2249)
!2270 = !DILocation(line: 787, column: 5, scope: !2249)
!2271 = !DILocation(line: 787, column: 12, scope: !2249)
!2272 = !DILocation(line: 787, column: 33, scope: !2249)
!2273 = !DILocation(line: 788, column: 7, scope: !2249)
!2274 = !DILocation(line: 789, column: 17, scope: !2249)
!2275 = !DILocation(line: 789, column: 23, scope: !2249)
!2276 = !DILocation(line: 789, column: 21, scope: !2249)
!2277 = !DILocation(line: 789, column: 5, scope: !2249)
!2278 = !DILocation(line: 789, column: 12, scope: !2249)
!2279 = !DILocation(line: 789, column: 33, scope: !2249)
!2280 = !DILocation(line: 789, column: 51, scope: !2249)
!2281 = !DILocation(line: 790, column: 4, scope: !2249)
!2282 = !DILocation(line: 792, column: 8, scope: !2283)
!2283 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 792, column: 8)
!2284 = !DILocation(line: 792, column: 35, scope: !2283)
!2285 = !DILocation(line: 792, column: 20, scope: !2283)
!2286 = !DILocation(line: 792, column: 27, scope: !2283)
!2287 = !DILocation(line: 792, column: 38, scope: !2283)
!2288 = !DILocation(line: 792, column: 17, scope: !2283)
!2289 = !DILocation(line: 792, column: 8, scope: !2222)
!2290 = !DILocalVariable(name: "buf_back", scope: !2291, file: !1, line: 794, type: !750)
!2291 = distinct !DILexicalBlock(scope: !2283, file: !1, line: 792, column: 43)
!2292 = !DILocation(line: 794, column: 26, scope: !2291)
!2293 = !DILocation(line: 794, column: 37, scope: !2291)
!2294 = !DILocation(line: 794, column: 43, scope: !2291)
!2295 = !DILocation(line: 794, column: 41, scope: !2291)
!2296 = !DILocation(line: 794, column: 52, scope: !2291)
!2297 = !DILocalVariable(name: "len_test_2", scope: !2291, file: !1, line: 795, type: !13)
!2298 = !DILocation(line: 795, column: 14, scope: !2291)
!2299 = !DILocation(line: 795, column: 27, scope: !2291)
!2300 = !DILocation(line: 795, column: 36, scope: !2291)
!2301 = !DILocalVariable(name: "limit", scope: !2291, file: !1, line: 796, type: !230)
!2302 = !DILocation(line: 796, column: 20, scope: !2291)
!2303 = !DILocation(line: 796, column: 28, scope: !2291)
!2304 = !DILocation(line: 796, column: 28, scope: !2305)
!2305 = !DILexicalBlockFile(scope: !2291, file: !1, discriminator: 1)
!2306 = !DILocation(line: 796, column: 28, scope: !2307)
!2307 = !DILexicalBlockFile(scope: !2291, file: !1, discriminator: 2)
!2308 = !DILocation(line: 796, column: 28, scope: !2309)
!2309 = !DILexicalBlockFile(scope: !2291, file: !1, discriminator: 3)
!2310 = !DILocation(line: 796, column: 20, scope: !2309)
!2311 = !DILocation(line: 799, column: 5, scope: !2291)
!2312 = !DILocation(line: 799, column: 12, scope: !2313)
!2313 = !DILexicalBlockFile(scope: !2314, file: !1, discriminator: 1)
!2314 = distinct !DILexicalBlock(scope: !2315, file: !1, line: 799, column: 5)
!2315 = distinct !DILexicalBlock(scope: !2291, file: !1, line: 799, column: 5)
!2316 = !DILocation(line: 799, column: 25, scope: !2313)
!2317 = !DILocation(line: 799, column: 23, scope: !2313)
!2318 = !DILocation(line: 799, column: 31, scope: !2313)
!2319 = !DILocation(line: 800, column: 11, scope: !2314)
!2320 = !DILocation(line: 800, column: 7, scope: !2314)
!2321 = !DILocation(line: 800, column: 35, scope: !2314)
!2322 = !DILocation(line: 800, column: 26, scope: !2314)
!2323 = !DILocation(line: 800, column: 23, scope: !2314)
!2324 = !DILocation(line: 799, column: 5, scope: !2325)
!2325 = !DILexicalBlockFile(scope: !2315, file: !1, discriminator: 2)
!2326 = !DILocation(line: 799, column: 5, scope: !2327)
!2327 = !DILexicalBlockFile(scope: !2315, file: !1, discriminator: 3)
!2328 = !DILocation(line: 801, column: 7, scope: !2314)
!2329 = !DILocation(line: 799, column: 5, scope: !2330)
!2330 = !DILexicalBlockFile(scope: !2314, file: !1, discriminator: 4)
!2331 = !DILocation(line: 803, column: 19, scope: !2291)
!2332 = !DILocation(line: 803, column: 28, scope: !2291)
!2333 = !DILocation(line: 803, column: 16, scope: !2291)
!2334 = !DILocation(line: 805, column: 9, scope: !2335)
!2335 = distinct !DILexicalBlock(scope: !2291, file: !1, line: 805, column: 9)
!2336 = !DILocation(line: 805, column: 20, scope: !2335)
!2337 = !DILocation(line: 805, column: 9, scope: !2291)
!2338 = !DILocalVariable(name: "pos_state_next", scope: !2339, file: !1, line: 806, type: !13)
!2339 = distinct !DILexicalBlock(scope: !2335, file: !1, line: 805, column: 26)
!2340 = !DILocation(line: 806, column: 15, scope: !2339)
!2341 = !DILocalVariable(name: "cur_and_len_literal_price", scope: !2339, file: !1, line: 807, type: !13)
!2342 = !DILocation(line: 807, column: 15, scope: !2339)
!2343 = !DILocalVariable(name: "next_rep_match_price", scope: !2339, file: !1, line: 808, type: !13)
!2344 = !DILocation(line: 808, column: 15, scope: !2339)
!2345 = !DILocalVariable(name: "offset", scope: !2339, file: !1, line: 809, type: !13)
!2346 = !DILocation(line: 809, column: 15, scope: !2339)
!2347 = !DILocalVariable(name: "state_2", scope: !2339, file: !1, line: 811, type: !78)
!2348 = !DILocation(line: 811, column: 22, scope: !2339)
!2349 = !DILocation(line: 811, column: 32, scope: !2339)
!2350 = !DILocation(line: 812, column: 6, scope: !2339)
!2351 = !DILocation(line: 813, column: 24, scope: !2339)
!2352 = !DILocation(line: 813, column: 35, scope: !2339)
!2353 = !DILocation(line: 813, column: 33, scope: !2339)
!2354 = !DILocation(line: 813, column: 47, scope: !2339)
!2355 = !DILocation(line: 813, column: 54, scope: !2339)
!2356 = !DILocation(line: 813, column: 45, scope: !2339)
!2357 = !DILocation(line: 813, column: 21, scope: !2339)
!2358 = !DILocation(line: 815, column: 34, scope: !2339)
!2359 = !DILocation(line: 817, column: 34, scope: !2339)
!2360 = !DILocation(line: 817, column: 9, scope: !2339)
!2361 = !DILocation(line: 817, column: 25, scope: !2339)
!2362 = !DILocation(line: 817, column: 16, scope: !2339)
!2363 = !DILocation(line: 816, column: 10, scope: !2339)
!2364 = !DILocation(line: 816, column: 8, scope: !2339)
!2365 = !DILocation(line: 818, column: 28, scope: !2339)
!2366 = !DILocation(line: 819, column: 9, scope: !2339)
!2367 = !DILocation(line: 819, column: 20, scope: !2339)
!2368 = !DILocation(line: 819, column: 18, scope: !2339)
!2369 = !DILocation(line: 820, column: 13, scope: !2339)
!2370 = !DILocation(line: 820, column: 22, scope: !2339)
!2371 = !DILocation(line: 820, column: 9, scope: !2339)
!2372 = !DILocation(line: 822, column: 18, scope: !2339)
!2373 = !DILocation(line: 822, column: 9, scope: !2339)
!2374 = !DILocation(line: 823, column: 13, scope: !2339)
!2375 = !DILocation(line: 823, column: 9, scope: !2339)
!2376 = !DILocation(line: 818, column: 10, scope: !2339)
!2377 = !DILocation(line: 818, column: 8, scope: !2339)
!2378 = !DILocation(line: 815, column: 32, scope: !2339)
!2379 = !DILocation(line: 825, column: 6, scope: !2339)
!2380 = !DILocation(line: 825, column: 6, scope: !2381)
!2381 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 1)
!2382 = !DILocation(line: 825, column: 6, scope: !2383)
!2383 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 2)
!2384 = !DILocation(line: 825, column: 6, scope: !2385)
!2385 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 3)
!2386 = !DILocation(line: 825, column: 6, scope: !2387)
!2387 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 4)
!2388 = !DILocation(line: 825, column: 6, scope: !2389)
!2389 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 5)
!2390 = !DILocation(line: 825, column: 6, scope: !2391)
!2391 = !DILexicalBlockFile(scope: !2339, file: !1, discriminator: 6)
!2392 = !DILocation(line: 826, column: 24, scope: !2339)
!2393 = !DILocation(line: 826, column: 39, scope: !2339)
!2394 = !DILocation(line: 826, column: 46, scope: !2339)
!2395 = !DILocation(line: 826, column: 53, scope: !2339)
!2396 = !DILocation(line: 826, column: 44, scope: !2339)
!2397 = !DILocation(line: 826, column: 21, scope: !2339)
!2398 = !DILocation(line: 829, column: 10, scope: !2339)
!2399 = !DILocation(line: 831, column: 34, scope: !2339)
!2400 = !DILocation(line: 831, column: 9, scope: !2339)
!2401 = !DILocation(line: 831, column: 25, scope: !2339)
!2402 = !DILocation(line: 831, column: 16, scope: !2339)
!2403 = !DILocation(line: 830, column: 10, scope: !2339)
!2404 = !DILocation(line: 830, column: 8, scope: !2339)
!2405 = !DILocation(line: 832, column: 39, scope: !2339)
!2406 = !DILocation(line: 832, column: 25, scope: !2339)
!2407 = !DILocation(line: 832, column: 32, scope: !2339)
!2408 = !DILocation(line: 832, column: 10, scope: !2339)
!2409 = !DILocation(line: 832, column: 8, scope: !2339)
!2410 = !DILocation(line: 829, column: 8, scope: !2339)
!2411 = !DILocation(line: 835, column: 15, scope: !2339)
!2412 = !DILocation(line: 835, column: 21, scope: !2339)
!2413 = !DILocation(line: 835, column: 19, scope: !2339)
!2414 = !DILocation(line: 835, column: 30, scope: !2339)
!2415 = !DILocation(line: 835, column: 36, scope: !2339)
!2416 = !DILocation(line: 835, column: 34, scope: !2339)
!2417 = !DILocation(line: 835, column: 13, scope: !2339)
!2418 = !DILocation(line: 837, column: 6, scope: !2339)
!2419 = !DILocation(line: 837, column: 13, scope: !2381)
!2420 = !DILocation(line: 837, column: 23, scope: !2381)
!2421 = !DILocation(line: 837, column: 21, scope: !2381)
!2422 = !DILocation(line: 837, column: 6, scope: !2381)
!2423 = !DILocation(line: 838, column: 19, scope: !2339)
!2424 = !DILocation(line: 838, column: 7, scope: !2339)
!2425 = !DILocation(line: 838, column: 14, scope: !2339)
!2426 = !DILocation(line: 838, column: 30, scope: !2339)
!2427 = !DILocation(line: 838, column: 36, scope: !2339)
!2428 = !DILocation(line: 837, column: 6, scope: !2383)
!2429 = !DILocation(line: 840, column: 26, scope: !2339)
!2430 = !DILocation(line: 841, column: 24, scope: !2339)
!2431 = !DILocation(line: 841, column: 34, scope: !2339)
!2432 = !DILocation(line: 842, column: 9, scope: !2339)
!2433 = !DILocation(line: 842, column: 18, scope: !2339)
!2434 = !DILocation(line: 841, column: 10, scope: !2339)
!2435 = !DILocation(line: 841, column: 8, scope: !2339)
!2436 = !DILocation(line: 840, column: 24, scope: !2339)
!2437 = !DILocation(line: 844, column: 10, scope: !2438)
!2438 = distinct !DILexicalBlock(scope: !2339, file: !1, line: 844, column: 10)
!2439 = !DILocation(line: 844, column: 42, scope: !2438)
!2440 = !DILocation(line: 844, column: 30, scope: !2438)
!2441 = !DILocation(line: 844, column: 37, scope: !2438)
!2442 = !DILocation(line: 844, column: 50, scope: !2438)
!2443 = !DILocation(line: 844, column: 28, scope: !2438)
!2444 = !DILocation(line: 844, column: 10, scope: !2339)
!2445 = !DILocation(line: 845, column: 35, scope: !2446)
!2446 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 844, column: 57)
!2447 = !DILocation(line: 845, column: 19, scope: !2446)
!2448 = !DILocation(line: 845, column: 7, scope: !2446)
!2449 = !DILocation(line: 845, column: 14, scope: !2446)
!2450 = !DILocation(line: 845, column: 27, scope: !2446)
!2451 = !DILocation(line: 845, column: 33, scope: !2446)
!2452 = !DILocation(line: 846, column: 38, scope: !2446)
!2453 = !DILocation(line: 846, column: 44, scope: !2446)
!2454 = !DILocation(line: 846, column: 42, scope: !2446)
!2455 = !DILocation(line: 846, column: 53, scope: !2446)
!2456 = !DILocation(line: 846, column: 19, scope: !2446)
!2457 = !DILocation(line: 846, column: 7, scope: !2446)
!2458 = !DILocation(line: 846, column: 14, scope: !2446)
!2459 = !DILocation(line: 846, column: 27, scope: !2446)
!2460 = !DILocation(line: 846, column: 36, scope: !2446)
!2461 = !DILocation(line: 847, column: 19, scope: !2446)
!2462 = !DILocation(line: 847, column: 7, scope: !2446)
!2463 = !DILocation(line: 847, column: 14, scope: !2446)
!2464 = !DILocation(line: 847, column: 27, scope: !2446)
!2465 = !DILocation(line: 847, column: 37, scope: !2446)
!2466 = !DILocation(line: 848, column: 19, scope: !2446)
!2467 = !DILocation(line: 848, column: 7, scope: !2446)
!2468 = !DILocation(line: 848, column: 14, scope: !2446)
!2469 = !DILocation(line: 848, column: 27, scope: !2446)
!2470 = !DILocation(line: 848, column: 45, scope: !2446)
!2471 = !DILocation(line: 849, column: 19, scope: !2446)
!2472 = !DILocation(line: 849, column: 7, scope: !2446)
!2473 = !DILocation(line: 849, column: 14, scope: !2446)
!2474 = !DILocation(line: 849, column: 27, scope: !2446)
!2475 = !DILocation(line: 849, column: 34, scope: !2446)
!2476 = !DILocation(line: 850, column: 40, scope: !2446)
!2477 = !DILocation(line: 850, column: 19, scope: !2446)
!2478 = !DILocation(line: 850, column: 7, scope: !2446)
!2479 = !DILocation(line: 850, column: 14, scope: !2446)
!2480 = !DILocation(line: 850, column: 27, scope: !2446)
!2481 = !DILocation(line: 850, column: 38, scope: !2446)
!2482 = !DILocation(line: 852, column: 11, scope: !2446)
!2483 = !DILocation(line: 852, column: 20, scope: !2446)
!2484 = !DILocation(line: 851, column: 19, scope: !2446)
!2485 = !DILocation(line: 851, column: 7, scope: !2446)
!2486 = !DILocation(line: 851, column: 14, scope: !2446)
!2487 = !DILocation(line: 851, column: 27, scope: !2446)
!2488 = !DILocation(line: 852, column: 9, scope: !2446)
!2489 = !DILocation(line: 853, column: 6, scope: !2446)
!2490 = !DILocation(line: 855, column: 5, scope: !2339)
!2491 = !DILocation(line: 857, column: 9, scope: !2492)
!2492 = distinct !DILexicalBlock(scope: !2291, file: !1, line: 857, column: 9)
!2493 = !DILocation(line: 857, column: 16, scope: !2492)
!2494 = !DILocation(line: 857, column: 13, scope: !2492)
!2495 = !DILocation(line: 857, column: 9, scope: !2291)
!2496 = !DILocation(line: 858, column: 6, scope: !2492)
!2497 = !DILocation(line: 859, column: 4, scope: !2291)
!2498 = !DILocation(line: 860, column: 3, scope: !2222)
!2499 = !DILocation(line: 778, column: 32, scope: !2500)
!2500 = !DILexicalBlockFile(scope: !2223, file: !1, discriminator: 1)
!2501 = !DILocation(line: 778, column: 3, scope: !2500)
!2502 = !DILocation(line: 861, column: 2, scope: !2180)
!2503 = !DILocation(line: 863, column: 9, scope: !282)
!2504 = !DILocation(line: 863, column: 2, scope: !282)
!2505 = !DILocation(line: 864, column: 1, scope: !282)
!2506 = !DILocalVariable(name: "mf", arg: 1, scope: !290, file: !86, line: 222, type: !293)
!2507 = !DILocation(line: 222, column: 23, scope: !290)
!2508 = !DILocation(line: 224, column: 9, scope: !290)
!2509 = !DILocation(line: 224, column: 13, scope: !290)
!2510 = !DILocation(line: 224, column: 22, scope: !290)
!2511 = !DILocation(line: 224, column: 26, scope: !290)
!2512 = !DILocation(line: 224, column: 20, scope: !290)
!2513 = !DILocation(line: 224, column: 2, scope: !290)
!2514 = !DILocalVariable(name: "mf", arg: 1, scope: !295, file: !86, line: 230, type: !293)
!2515 = !DILocation(line: 230, column: 25, scope: !295)
!2516 = !DILocation(line: 232, column: 9, scope: !295)
!2517 = !DILocation(line: 232, column: 13, scope: !295)
!2518 = !DILocation(line: 232, column: 25, scope: !295)
!2519 = !DILocation(line: 232, column: 29, scope: !295)
!2520 = !DILocation(line: 232, column: 23, scope: !295)
!2521 = !DILocation(line: 232, column: 2, scope: !295)
!2522 = !DILocalVariable(name: "coder", arg: 1, scope: !298, file: !1, line: 233, type: !68)
!2523 = !DILocation(line: 233, column: 36, scope: !298)
!2524 = !DILocalVariable(name: "len_res", arg: 2, scope: !298, file: !1, line: 233, type: !218)
!2525 = !DILocation(line: 233, column: 67, scope: !298)
!2526 = !DILocalVariable(name: "back_res", arg: 3, scope: !298, file: !1, line: 234, type: !218)
!2527 = !DILocation(line: 234, column: 27, scope: !298)
!2528 = !DILocalVariable(name: "cur", arg: 4, scope: !298, file: !1, line: 234, type: !13)
!2529 = !DILocation(line: 234, column: 46, scope: !298)
!2530 = !DILocalVariable(name: "pos_mem", scope: !298, file: !1, line: 236, type: !13)
!2531 = !DILocation(line: 236, column: 11, scope: !298)
!2532 = !DILocation(line: 236, column: 33, scope: !298)
!2533 = !DILocation(line: 236, column: 21, scope: !298)
!2534 = !DILocation(line: 236, column: 28, scope: !298)
!2535 = !DILocation(line: 236, column: 38, scope: !298)
!2536 = !DILocalVariable(name: "back_mem", scope: !298, file: !1, line: 237, type: !13)
!2537 = !DILocation(line: 237, column: 11, scope: !298)
!2538 = !DILocation(line: 237, column: 34, scope: !298)
!2539 = !DILocation(line: 237, column: 22, scope: !298)
!2540 = !DILocation(line: 237, column: 29, scope: !298)
!2541 = !DILocation(line: 237, column: 39, scope: !298)
!2542 = !DILocation(line: 239, column: 26, scope: !298)
!2543 = !DILocation(line: 239, column: 2, scope: !298)
!2544 = !DILocation(line: 239, column: 9, scope: !298)
!2545 = !DILocation(line: 239, column: 24, scope: !298)
!2546 = !DILocation(line: 241, column: 2, scope: !298)
!2547 = !DILocalVariable(name: "pos_prev", scope: !2548, file: !1, line: 242, type: !230)
!2548 = distinct !DILexicalBlock(scope: !298, file: !1, line: 241, column: 5)
!2549 = !DILocation(line: 242, column: 18, scope: !2548)
!2550 = !DILocation(line: 242, column: 29, scope: !2548)
!2551 = !DILocalVariable(name: "back_cur", scope: !2548, file: !1, line: 243, type: !230)
!2552 = !DILocation(line: 243, column: 18, scope: !2548)
!2553 = !DILocation(line: 243, column: 29, scope: !2548)
!2554 = !DILocation(line: 245, column: 19, scope: !2555)
!2555 = distinct !DILexicalBlock(scope: !2548, file: !1, line: 245, column: 7)
!2556 = !DILocation(line: 245, column: 7, scope: !2555)
!2557 = !DILocation(line: 245, column: 14, scope: !2555)
!2558 = !DILocation(line: 245, column: 24, scope: !2555)
!2559 = !DILocation(line: 245, column: 7, scope: !2548)
!2560 = !DILocation(line: 246, column: 30, scope: !2561)
!2561 = distinct !DILexicalBlock(scope: !2555, file: !1, line: 245, column: 43)
!2562 = !DILocation(line: 246, column: 18, scope: !2561)
!2563 = !DILocation(line: 246, column: 25, scope: !2561)
!2564 = !DILocation(line: 246, column: 4, scope: !2561)
!2565 = !DILocation(line: 247, column: 36, scope: !2561)
!2566 = !DILocation(line: 247, column: 44, scope: !2561)
!2567 = !DILocation(line: 247, column: 16, scope: !2561)
!2568 = !DILocation(line: 247, column: 4, scope: !2561)
!2569 = !DILocation(line: 247, column: 11, scope: !2561)
!2570 = !DILocation(line: 247, column: 25, scope: !2561)
!2571 = !DILocation(line: 247, column: 34, scope: !2561)
!2572 = !DILocation(line: 249, column: 20, scope: !2573)
!2573 = distinct !DILexicalBlock(scope: !2561, file: !1, line: 249, column: 8)
!2574 = !DILocation(line: 249, column: 8, scope: !2573)
!2575 = !DILocation(line: 249, column: 15, scope: !2573)
!2576 = !DILocation(line: 249, column: 25, scope: !2573)
!2577 = !DILocation(line: 249, column: 8, scope: !2561)
!2578 = !DILocation(line: 250, column: 17, scope: !2579)
!2579 = distinct !DILexicalBlock(scope: !2573, file: !1, line: 249, column: 33)
!2580 = !DILocation(line: 250, column: 25, scope: !2579)
!2581 = !DILocation(line: 250, column: 5, scope: !2579)
!2582 = !DILocation(line: 250, column: 12, scope: !2579)
!2583 = !DILocation(line: 250, column: 30, scope: !2579)
!2584 = !DILocation(line: 251, column: 7, scope: !2579)
!2585 = !DILocation(line: 253, column: 21, scope: !2579)
!2586 = !DILocation(line: 253, column: 9, scope: !2579)
!2587 = !DILocation(line: 253, column: 16, scope: !2579)
!2588 = !DILocation(line: 253, column: 26, scope: !2579)
!2589 = !DILocation(line: 252, column: 17, scope: !2579)
!2590 = !DILocation(line: 252, column: 25, scope: !2579)
!2591 = !DILocation(line: 252, column: 5, scope: !2579)
!2592 = !DILocation(line: 252, column: 12, scope: !2579)
!2593 = !DILocation(line: 252, column: 30, scope: !2579)
!2594 = !DILocation(line: 253, column: 7, scope: !2579)
!2595 = !DILocation(line: 255, column: 21, scope: !2579)
!2596 = !DILocation(line: 255, column: 9, scope: !2579)
!2597 = !DILocation(line: 255, column: 16, scope: !2579)
!2598 = !DILocation(line: 255, column: 26, scope: !2579)
!2599 = !DILocation(line: 254, column: 17, scope: !2579)
!2600 = !DILocation(line: 254, column: 25, scope: !2579)
!2601 = !DILocation(line: 254, column: 5, scope: !2579)
!2602 = !DILocation(line: 254, column: 12, scope: !2579)
!2603 = !DILocation(line: 254, column: 30, scope: !2579)
!2604 = !DILocation(line: 255, column: 7, scope: !2579)
!2605 = !DILocation(line: 256, column: 4, scope: !2579)
!2606 = !DILocation(line: 257, column: 3, scope: !2561)
!2607 = !DILocation(line: 259, column: 26, scope: !2548)
!2608 = !DILocation(line: 259, column: 14, scope: !2548)
!2609 = !DILocation(line: 259, column: 21, scope: !2548)
!2610 = !DILocation(line: 259, column: 36, scope: !2548)
!2611 = !DILocation(line: 259, column: 12, scope: !2548)
!2612 = !DILocation(line: 260, column: 25, scope: !2548)
!2613 = !DILocation(line: 260, column: 13, scope: !2548)
!2614 = !DILocation(line: 260, column: 20, scope: !2548)
!2615 = !DILocation(line: 260, column: 35, scope: !2548)
!2616 = !DILocation(line: 260, column: 11, scope: !2548)
!2617 = !DILocation(line: 262, column: 37, scope: !2548)
!2618 = !DILocation(line: 262, column: 15, scope: !2548)
!2619 = !DILocation(line: 262, column: 3, scope: !2548)
!2620 = !DILocation(line: 262, column: 10, scope: !2548)
!2621 = !DILocation(line: 262, column: 25, scope: !2548)
!2622 = !DILocation(line: 262, column: 35, scope: !2548)
!2623 = !DILocation(line: 263, column: 36, scope: !2548)
!2624 = !DILocation(line: 263, column: 15, scope: !2548)
!2625 = !DILocation(line: 263, column: 3, scope: !2548)
!2626 = !DILocation(line: 263, column: 10, scope: !2548)
!2627 = !DILocation(line: 263, column: 25, scope: !2548)
!2628 = !DILocation(line: 263, column: 34, scope: !2548)
!2629 = !DILocation(line: 264, column: 9, scope: !2548)
!2630 = !DILocation(line: 264, column: 7, scope: !2548)
!2631 = !DILocation(line: 266, column: 2, scope: !2548)
!2632 = !DILocation(line: 266, column: 11, scope: !2633)
!2633 = !DILexicalBlockFile(scope: !298, file: !1, discriminator: 1)
!2634 = !DILocation(line: 266, column: 15, scope: !2633)
!2635 = !DILocation(line: 266, column: 2, scope: !2633)
!2636 = !DILocation(line: 268, column: 30, scope: !298)
!2637 = !DILocation(line: 268, column: 37, scope: !298)
!2638 = !DILocation(line: 268, column: 45, scope: !298)
!2639 = !DILocation(line: 268, column: 2, scope: !298)
!2640 = !DILocation(line: 268, column: 9, scope: !298)
!2641 = !DILocation(line: 268, column: 28, scope: !298)
!2642 = !DILocation(line: 269, column: 13, scope: !298)
!2643 = !DILocation(line: 269, column: 20, scope: !298)
!2644 = !DILocation(line: 269, column: 28, scope: !298)
!2645 = !DILocation(line: 269, column: 3, scope: !298)
!2646 = !DILocation(line: 269, column: 11, scope: !298)
!2647 = !DILocation(line: 270, column: 14, scope: !298)
!2648 = !DILocation(line: 270, column: 21, scope: !298)
!2649 = !DILocation(line: 270, column: 29, scope: !298)
!2650 = !DILocation(line: 270, column: 3, scope: !298)
!2651 = !DILocation(line: 270, column: 12, scope: !298)
!2652 = !DILocation(line: 272, column: 2, scope: !298)
!2653 = !DILocalVariable(name: "probs", arg: 1, scope: !223, file: !224, line: 52, type: !227)
!2654 = !DILocation(line: 52, column: 43, scope: !223)
!2655 = !DILocalVariable(name: "bit_levels", arg: 2, scope: !223, file: !224, line: 53, type: !230)
!2656 = !DILocation(line: 53, column: 18, scope: !223)
!2657 = !DILocalVariable(name: "symbol", arg: 3, scope: !223, file: !224, line: 53, type: !13)
!2658 = !DILocation(line: 53, column: 39, scope: !223)
!2659 = !DILocalVariable(name: "price", scope: !223, file: !224, line: 55, type: !13)
!2660 = !DILocation(line: 55, column: 11, scope: !223)
!2661 = !DILocation(line: 56, column: 27, scope: !223)
!2662 = !DILocation(line: 56, column: 24, scope: !223)
!2663 = !DILocation(line: 56, column: 9, scope: !223)
!2664 = !DILocation(line: 58, column: 2, scope: !223)
!2665 = !DILocalVariable(name: "bit", scope: !2666, file: !224, line: 59, type: !230)
!2666 = distinct !DILexicalBlock(scope: !223, file: !224, line: 58, column: 5)
!2667 = !DILocation(line: 59, column: 18, scope: !2666)
!2668 = !DILocation(line: 59, column: 24, scope: !2666)
!2669 = !DILocation(line: 59, column: 31, scope: !2666)
!2670 = !DILocation(line: 60, column: 10, scope: !2666)
!2671 = !DILocation(line: 61, column: 31, scope: !2666)
!2672 = !DILocation(line: 61, column: 25, scope: !2666)
!2673 = !DILocation(line: 61, column: 40, scope: !2666)
!2674 = !DILocation(line: 61, column: 12, scope: !2666)
!2675 = !DILocation(line: 61, column: 9, scope: !2666)
!2676 = !DILocation(line: 62, column: 2, scope: !2666)
!2677 = !DILocation(line: 62, column: 11, scope: !2678)
!2678 = !DILexicalBlockFile(scope: !223, file: !224, discriminator: 1)
!2679 = !DILocation(line: 62, column: 18, scope: !2678)
!2680 = !DILocation(line: 62, column: 2, scope: !2678)
!2681 = !DILocation(line: 64, column: 9, scope: !223)
!2682 = !DILocation(line: 64, column: 2, scope: !223)
!2683 = !DILocalVariable(name: "bits", arg: 1, scope: !234, file: !224, line: 87, type: !230)
!2684 = !DILocation(line: 87, column: 32, scope: !234)
!2685 = !DILocation(line: 89, column: 10, scope: !234)
!2686 = !DILocation(line: 89, column: 15, scope: !234)
!2687 = !DILocation(line: 89, column: 3, scope: !234)
!2688 = !DILocalVariable(name: "pos", arg: 1, scope: !237, file: !238, line: 110, type: !13)
!2689 = !DILocation(line: 110, column: 23, scope: !237)
!2690 = !DILocation(line: 114, column: 6, scope: !2691)
!2691 = distinct !DILexicalBlock(scope: !237, file: !238, line: 114, column: 6)
!2692 = !DILocation(line: 114, column: 10, scope: !2691)
!2693 = !DILocation(line: 114, column: 6, scope: !237)
!2694 = !DILocation(line: 115, column: 23, scope: !2691)
!2695 = !DILocation(line: 115, column: 10, scope: !2691)
!2696 = !DILocation(line: 115, column: 3, scope: !2691)
!2697 = !DILocation(line: 117, column: 6, scope: !2698)
!2698 = distinct !DILexicalBlock(scope: !237, file: !238, line: 117, column: 6)
!2699 = !DILocation(line: 117, column: 10, scope: !2698)
!2700 = !DILocation(line: 117, column: 6, scope: !237)
!2701 = !DILocation(line: 118, column: 10, scope: !2698)
!2702 = !DILocation(line: 118, column: 3, scope: !2698)
!2703 = !DILocation(line: 120, column: 9, scope: !237)
!2704 = !DILocation(line: 120, column: 2, scope: !237)
!2705 = !DILocation(line: 121, column: 1, scope: !237)
!2706 = !DILocalVariable(name: "probs", arg: 1, scope: !241, file: !224, line: 69, type: !227)
!2707 = !DILocation(line: 69, column: 51, scope: !241)
!2708 = !DILocalVariable(name: "bit_levels", arg: 2, scope: !241, file: !224, line: 70, type: !13)
!2709 = !DILocation(line: 70, column: 12, scope: !241)
!2710 = !DILocalVariable(name: "symbol", arg: 3, scope: !241, file: !224, line: 70, type: !13)
!2711 = !DILocation(line: 70, column: 33, scope: !241)
!2712 = !DILocalVariable(name: "price", scope: !241, file: !224, line: 72, type: !13)
!2713 = !DILocation(line: 72, column: 11, scope: !241)
!2714 = !DILocalVariable(name: "model_index", scope: !241, file: !224, line: 73, type: !13)
!2715 = !DILocation(line: 73, column: 11, scope: !241)
!2716 = !DILocation(line: 75, column: 2, scope: !241)
!2717 = !DILocalVariable(name: "bit", scope: !2718, file: !224, line: 76, type: !230)
!2718 = distinct !DILexicalBlock(scope: !241, file: !224, line: 75, column: 5)
!2719 = !DILocation(line: 76, column: 18, scope: !2718)
!2720 = !DILocation(line: 76, column: 24, scope: !2718)
!2721 = !DILocation(line: 76, column: 31, scope: !2718)
!2722 = !DILocation(line: 77, column: 10, scope: !2718)
!2723 = !DILocation(line: 78, column: 31, scope: !2718)
!2724 = !DILocation(line: 78, column: 25, scope: !2718)
!2725 = !DILocation(line: 78, column: 45, scope: !2718)
!2726 = !DILocation(line: 78, column: 12, scope: !2718)
!2727 = !DILocation(line: 78, column: 9, scope: !2718)
!2728 = !DILocation(line: 79, column: 18, scope: !2718)
!2729 = !DILocation(line: 79, column: 30, scope: !2718)
!2730 = !DILocation(line: 79, column: 38, scope: !2718)
!2731 = !DILocation(line: 79, column: 36, scope: !2718)
!2732 = !DILocation(line: 79, column: 15, scope: !2718)
!2733 = !DILocation(line: 80, column: 2, scope: !2718)
!2734 = !DILocation(line: 80, column: 11, scope: !2735)
!2735 = !DILexicalBlockFile(scope: !241, file: !224, discriminator: 1)
!2736 = !DILocation(line: 80, column: 24, scope: !2735)
!2737 = !DILocation(line: 80, column: 2, scope: !2735)
!2738 = !DILocation(line: 82, column: 9, scope: !241)
!2739 = !DILocation(line: 82, column: 2, scope: !241)
!2740 = !DILocalVariable(name: "prob", arg: 1, scope: !231, file: !224, line: 29, type: !229)
!2741 = !DILocation(line: 29, column: 32, scope: !231)
!2742 = !DILocalVariable(name: "bit", arg: 2, scope: !231, file: !224, line: 29, type: !230)
!2743 = !DILocation(line: 29, column: 53, scope: !231)
!2744 = !DILocation(line: 31, column: 25, scope: !231)
!2745 = !DILocation(line: 31, column: 48, scope: !231)
!2746 = !DILocation(line: 31, column: 46, scope: !231)
!2747 = !DILocation(line: 32, column: 4, scope: !231)
!2748 = !DILocation(line: 31, column: 30, scope: !231)
!2749 = !DILocation(line: 32, column: 33, scope: !231)
!2750 = !DILocation(line: 31, column: 9, scope: !231)
!2751 = !DILocation(line: 31, column: 2, scope: !231)
!2752 = !DILocalVariable(name: "mf", arg: 1, scope: !248, file: !86, line: 268, type: !181)
!2753 = !DILocation(line: 268, column: 18, scope: !248)
!2754 = !DILocalVariable(name: "amount", arg: 2, scope: !248, file: !86, line: 268, type: !13)
!2755 = !DILocation(line: 268, column: 31, scope: !248)
!2756 = !DILocation(line: 270, column: 6, scope: !2757)
!2757 = distinct !DILexicalBlock(scope: !248, file: !86, line: 270, column: 6)
!2758 = !DILocation(line: 270, column: 13, scope: !2757)
!2759 = !DILocation(line: 270, column: 6, scope: !248)
!2760 = !DILocation(line: 271, column: 3, scope: !2761)
!2761 = distinct !DILexicalBlock(scope: !2757, file: !86, line: 270, column: 19)
!2762 = !DILocation(line: 271, column: 7, scope: !2761)
!2763 = !DILocation(line: 271, column: 12, scope: !2761)
!2764 = !DILocation(line: 271, column: 16, scope: !2761)
!2765 = !DILocation(line: 272, column: 21, scope: !2761)
!2766 = !DILocation(line: 272, column: 3, scope: !2761)
!2767 = !DILocation(line: 272, column: 7, scope: !2761)
!2768 = !DILocation(line: 272, column: 18, scope: !2761)
!2769 = !DILocation(line: 273, column: 2, scope: !2761)
!2770 = !DILocation(line: 274, column: 1, scope: !248)
!2771 = !DILocalVariable(name: "prob", arg: 1, scope: !249, file: !224, line: 37, type: !229)
!2772 = !DILocation(line: 37, column: 34, scope: !249)
!2773 = !DILocation(line: 39, column: 24, scope: !249)
!2774 = !DILocation(line: 39, column: 29, scope: !249)
!2775 = !DILocation(line: 39, column: 9, scope: !249)
!2776 = !DILocation(line: 39, column: 2, scope: !249)
!2777 = !DILocalVariable(name: "coder", arg: 1, scope: !252, file: !1, line: 21, type: !255)
!2778 = !DILocation(line: 21, column: 43, scope: !252)
!2779 = !DILocalVariable(name: "pos", arg: 2, scope: !252, file: !1, line: 21, type: !230)
!2780 = !DILocation(line: 21, column: 65, scope: !252)
!2781 = !DILocalVariable(name: "prev_byte", arg: 3, scope: !252, file: !1, line: 22, type: !230)
!2782 = !DILocation(line: 22, column: 18, scope: !252)
!2783 = !DILocalVariable(name: "match_mode", arg: 4, scope: !252, file: !1, line: 22, type: !258)
!2784 = !DILocation(line: 22, column: 40, scope: !252)
!2785 = !DILocalVariable(name: "match_byte", arg: 5, scope: !252, file: !1, line: 23, type: !13)
!2786 = !DILocation(line: 23, column: 12, scope: !252)
!2787 = !DILocalVariable(name: "symbol", arg: 6, scope: !252, file: !1, line: 23, type: !13)
!2788 = !DILocation(line: 23, column: 33, scope: !252)
!2789 = !DILocalVariable(name: "subcoder", scope: !252, file: !1, line: 25, type: !227)
!2790 = !DILocation(line: 25, column: 27, scope: !252)
!2791 = !DILocation(line: 25, column: 38, scope: !252)
!2792 = !DILocalVariable(name: "price", scope: !252, file: !1, line: 29, type: !13)
!2793 = !DILocation(line: 29, column: 11, scope: !252)
!2794 = !DILocation(line: 31, column: 7, scope: !2795)
!2795 = distinct !DILexicalBlock(scope: !252, file: !1, line: 31, column: 6)
!2796 = !DILocation(line: 31, column: 6, scope: !252)
!2797 = !DILocation(line: 32, column: 28, scope: !2798)
!2798 = distinct !DILexicalBlock(scope: !2795, file: !1, line: 31, column: 19)
!2799 = !DILocation(line: 32, column: 41, scope: !2798)
!2800 = !DILocation(line: 32, column: 11, scope: !2798)
!2801 = !DILocation(line: 32, column: 9, scope: !2798)
!2802 = !DILocation(line: 33, column: 2, scope: !2798)
!2803 = !DILocalVariable(name: "offset", scope: !2804, file: !1, line: 34, type: !13)
!2804 = distinct !DILexicalBlock(scope: !2795, file: !1, line: 33, column: 9)
!2805 = !DILocation(line: 34, column: 12, scope: !2804)
!2806 = !DILocation(line: 35, column: 10, scope: !2804)
!2807 = !DILocation(line: 37, column: 3, scope: !2804)
!2808 = !DILocalVariable(name: "match_bit", scope: !2809, file: !1, line: 38, type: !13)
!2809 = distinct !DILexicalBlock(scope: !2804, file: !1, line: 37, column: 6)
!2810 = !DILocation(line: 38, column: 13, scope: !2809)
!2811 = !DILocalVariable(name: "subcoder_index", scope: !2809, file: !1, line: 39, type: !13)
!2812 = !DILocation(line: 39, column: 13, scope: !2809)
!2813 = !DILocalVariable(name: "bit", scope: !2809, file: !1, line: 40, type: !13)
!2814 = !DILocation(line: 40, column: 13, scope: !2809)
!2815 = !DILocation(line: 42, column: 15, scope: !2809)
!2816 = !DILocation(line: 44, column: 16, scope: !2809)
!2817 = !DILocation(line: 44, column: 29, scope: !2809)
!2818 = !DILocation(line: 44, column: 27, scope: !2809)
!2819 = !DILocation(line: 44, column: 14, scope: !2809)
!2820 = !DILocation(line: 45, column: 21, scope: !2809)
!2821 = !DILocation(line: 45, column: 30, scope: !2809)
!2822 = !DILocation(line: 45, column: 28, scope: !2809)
!2823 = !DILocation(line: 45, column: 43, scope: !2809)
!2824 = !DILocation(line: 45, column: 50, scope: !2809)
!2825 = !DILocation(line: 45, column: 40, scope: !2809)
!2826 = !DILocation(line: 45, column: 19, scope: !2809)
!2827 = !DILocation(line: 46, column: 11, scope: !2809)
!2828 = !DILocation(line: 46, column: 18, scope: !2809)
!2829 = !DILocation(line: 46, column: 24, scope: !2809)
!2830 = !DILocation(line: 46, column: 8, scope: !2809)
!2831 = !DILocation(line: 47, column: 35, scope: !2809)
!2832 = !DILocation(line: 47, column: 26, scope: !2809)
!2833 = !DILocation(line: 47, column: 52, scope: !2809)
!2834 = !DILocation(line: 47, column: 13, scope: !2809)
!2835 = !DILocation(line: 47, column: 10, scope: !2809)
!2836 = !DILocation(line: 49, column: 11, scope: !2809)
!2837 = !DILocation(line: 50, column: 16, scope: !2809)
!2838 = !DILocation(line: 50, column: 29, scope: !2809)
!2839 = !DILocation(line: 50, column: 27, scope: !2809)
!2840 = !DILocation(line: 50, column: 14, scope: !2809)
!2841 = !DILocation(line: 50, column: 11, scope: !2809)
!2842 = !DILocation(line: 52, column: 3, scope: !2809)
!2843 = !DILocation(line: 52, column: 12, scope: !2844)
!2844 = !DILexicalBlockFile(scope: !2804, file: !1, discriminator: 1)
!2845 = !DILocation(line: 52, column: 19, scope: !2844)
!2846 = !DILocation(line: 52, column: 3, scope: !2844)
!2847 = !DILocation(line: 55, column: 9, scope: !252)
!2848 = !DILocation(line: 55, column: 2, scope: !252)
!2849 = !DILocalVariable(name: "optimal", arg: 1, scope: !259, file: !1, line: 213, type: !262)
!2850 = !DILocation(line: 213, column: 28, scope: !259)
!2851 = !DILocation(line: 215, column: 2, scope: !259)
!2852 = !DILocation(line: 215, column: 11, scope: !259)
!2853 = !DILocation(line: 215, column: 21, scope: !259)
!2854 = !DILocation(line: 216, column: 2, scope: !259)
!2855 = !DILocation(line: 216, column: 11, scope: !259)
!2856 = !DILocation(line: 216, column: 29, scope: !259)
!2857 = !DILocation(line: 217, column: 1, scope: !259)
!2858 = !DILocalVariable(name: "prob", arg: 1, scope: !263, file: !224, line: 44, type: !229)
!2859 = !DILocation(line: 44, column: 34, scope: !263)
!2860 = !DILocation(line: 46, column: 25, scope: !263)
!2861 = !DILocation(line: 46, column: 30, scope: !263)
!2862 = !DILocation(line: 47, column: 4, scope: !263)
!2863 = !DILocation(line: 46, column: 9, scope: !263)
!2864 = !DILocation(line: 46, column: 2, scope: !263)
!2865 = !DILocalVariable(name: "coder", arg: 1, scope: !264, file: !1, line: 70, type: !255)
!2866 = !DILocation(line: 70, column: 45, scope: !264)
!2867 = !DILocalVariable(name: "state", arg: 2, scope: !264, file: !1, line: 71, type: !267)
!2868 = !DILocation(line: 71, column: 25, scope: !264)
!2869 = !DILocalVariable(name: "pos_state", arg: 3, scope: !264, file: !1, line: 71, type: !230)
!2870 = !DILocation(line: 71, column: 47, scope: !264)
!2871 = !DILocation(line: 73, column: 39, scope: !264)
!2872 = !DILocation(line: 73, column: 24, scope: !264)
!2873 = !DILocation(line: 73, column: 31, scope: !264)
!2874 = !DILocation(line: 73, column: 9, scope: !264)
!2875 = !DILocation(line: 74, column: 47, scope: !264)
!2876 = !DILocation(line: 74, column: 20, scope: !264)
!2877 = !DILocation(line: 74, column: 40, scope: !264)
!2878 = !DILocation(line: 74, column: 27, scope: !264)
!2879 = !DILocation(line: 74, column: 5, scope: !264)
!2880 = !DILocation(line: 74, column: 3, scope: !264)
!2881 = !DILocation(line: 73, column: 2, scope: !264)
!2882 = !DILocalVariable(name: "optimal", arg: 1, scope: !268, file: !1, line: 221, type: !262)
!2883 = !DILocation(line: 221, column: 30, scope: !268)
!2884 = !DILocation(line: 223, column: 2, scope: !268)
!2885 = !DILocation(line: 223, column: 11, scope: !268)
!2886 = !DILocation(line: 223, column: 21, scope: !268)
!2887 = !DILocation(line: 224, column: 2, scope: !268)
!2888 = !DILocation(line: 224, column: 11, scope: !268)
!2889 = !DILocation(line: 224, column: 29, scope: !268)
!2890 = !DILocation(line: 225, column: 1, scope: !268)
!2891 = !DILocalVariable(name: "coder", arg: 1, scope: !269, file: !1, line: 79, type: !255)
!2892 = !DILocation(line: 79, column: 44, scope: !269)
!2893 = !DILocalVariable(name: "rep_index", arg: 2, scope: !269, file: !1, line: 79, type: !230)
!2894 = !DILocation(line: 79, column: 66, scope: !269)
!2895 = !DILocalVariable(name: "state", arg: 3, scope: !269, file: !1, line: 80, type: !267)
!2896 = !DILocation(line: 80, column: 25, scope: !269)
!2897 = !DILocalVariable(name: "pos_state", arg: 4, scope: !269, file: !1, line: 80, type: !13)
!2898 = !DILocation(line: 80, column: 41, scope: !269)
!2899 = !DILocalVariable(name: "price", scope: !269, file: !1, line: 82, type: !13)
!2900 = !DILocation(line: 82, column: 11, scope: !269)
!2901 = !DILocation(line: 84, column: 6, scope: !2902)
!2902 = distinct !DILexicalBlock(scope: !269, file: !1, line: 84, column: 6)
!2903 = !DILocation(line: 84, column: 16, scope: !2902)
!2904 = !DILocation(line: 84, column: 6, scope: !269)
!2905 = !DILocation(line: 85, column: 41, scope: !2906)
!2906 = distinct !DILexicalBlock(scope: !2902, file: !1, line: 84, column: 22)
!2907 = !DILocation(line: 85, column: 26, scope: !2906)
!2908 = !DILocation(line: 85, column: 33, scope: !2906)
!2909 = !DILocation(line: 85, column: 11, scope: !2906)
!2910 = !DILocation(line: 85, column: 9, scope: !2906)
!2911 = !DILocation(line: 86, column: 54, scope: !2906)
!2912 = !DILocation(line: 86, column: 27, scope: !2906)
!2913 = !DILocation(line: 86, column: 47, scope: !2906)
!2914 = !DILocation(line: 86, column: 34, scope: !2906)
!2915 = !DILocation(line: 86, column: 12, scope: !2906)
!2916 = !DILocation(line: 86, column: 9, scope: !2906)
!2917 = !DILocation(line: 87, column: 2, scope: !2906)
!2918 = !DILocation(line: 88, column: 41, scope: !2919)
!2919 = distinct !DILexicalBlock(scope: !2902, file: !1, line: 87, column: 9)
!2920 = !DILocation(line: 88, column: 26, scope: !2919)
!2921 = !DILocation(line: 88, column: 33, scope: !2919)
!2922 = !DILocation(line: 88, column: 11, scope: !2919)
!2923 = !DILocation(line: 88, column: 9, scope: !2919)
!2924 = !DILocation(line: 90, column: 7, scope: !2925)
!2925 = distinct !DILexicalBlock(scope: !2919, file: !1, line: 90, column: 7)
!2926 = !DILocation(line: 90, column: 17, scope: !2925)
!2927 = !DILocation(line: 90, column: 7, scope: !2919)
!2928 = !DILocation(line: 91, column: 43, scope: !2929)
!2929 = distinct !DILexicalBlock(scope: !2925, file: !1, line: 90, column: 23)
!2930 = !DILocation(line: 91, column: 28, scope: !2929)
!2931 = !DILocation(line: 91, column: 35, scope: !2929)
!2932 = !DILocation(line: 91, column: 13, scope: !2929)
!2933 = !DILocation(line: 91, column: 10, scope: !2929)
!2934 = !DILocation(line: 92, column: 3, scope: !2929)
!2935 = !DILocation(line: 93, column: 43, scope: !2936)
!2936 = distinct !DILexicalBlock(scope: !2925, file: !1, line: 92, column: 10)
!2937 = !DILocation(line: 93, column: 28, scope: !2936)
!2938 = !DILocation(line: 93, column: 35, scope: !2936)
!2939 = !DILocation(line: 93, column: 13, scope: !2936)
!2940 = !DILocation(line: 93, column: 10, scope: !2936)
!2941 = !DILocation(line: 94, column: 41, scope: !2936)
!2942 = !DILocation(line: 94, column: 26, scope: !2936)
!2943 = !DILocation(line: 94, column: 33, scope: !2936)
!2944 = !DILocation(line: 95, column: 6, scope: !2936)
!2945 = !DILocation(line: 95, column: 16, scope: !2936)
!2946 = !DILocation(line: 94, column: 13, scope: !2936)
!2947 = !DILocation(line: 94, column: 10, scope: !2936)
!2948 = !DILocation(line: 99, column: 9, scope: !269)
!2949 = !DILocation(line: 99, column: 2, scope: !269)
!2950 = !DILocalVariable(name: "lencoder", arg: 1, scope: !272, file: !1, line: 60, type: !275)
!2951 = !DILocation(line: 60, column: 48, scope: !272)
!2952 = !DILocalVariable(name: "len", arg: 2, scope: !272, file: !1, line: 61, type: !230)
!2953 = !DILocation(line: 61, column: 18, scope: !272)
!2954 = !DILocalVariable(name: "pos_state", arg: 3, scope: !272, file: !1, line: 61, type: !230)
!2955 = !DILocation(line: 61, column: 38, scope: !272)
!2956 = !DILocation(line: 65, column: 37, scope: !272)
!2957 = !DILocation(line: 65, column: 41, scope: !272)
!2958 = !DILocation(line: 65, column: 9, scope: !272)
!2959 = !DILocation(line: 65, column: 26, scope: !272)
!2960 = !DILocation(line: 65, column: 19, scope: !272)
!2961 = !DILocation(line: 65, column: 2, scope: !272)
!2962 = !DILocalVariable(name: "coder", arg: 1, scope: !278, file: !1, line: 114, type: !255)
!2963 = !DILocation(line: 114, column: 43, scope: !278)
!2964 = !DILocalVariable(name: "pos", arg: 2, scope: !278, file: !1, line: 114, type: !230)
!2965 = !DILocation(line: 114, column: 65, scope: !278)
!2966 = !DILocalVariable(name: "len", arg: 3, scope: !278, file: !1, line: 115, type: !230)
!2967 = !DILocation(line: 115, column: 18, scope: !278)
!2968 = !DILocalVariable(name: "pos_state", arg: 4, scope: !278, file: !1, line: 115, type: !230)
!2969 = !DILocation(line: 115, column: 38, scope: !278)
!2970 = !DILocalVariable(name: "len_to_pos_state", scope: !278, file: !1, line: 117, type: !230)
!2971 = !DILocation(line: 117, column: 17, scope: !278)
!2972 = !DILocation(line: 117, column: 36, scope: !278)
!2973 = !DILocation(line: 117, column: 36, scope: !2974)
!2974 = !DILexicalBlockFile(scope: !278, file: !1, discriminator: 1)
!2975 = !DILocation(line: 117, column: 36, scope: !2976)
!2976 = !DILexicalBlockFile(scope: !278, file: !1, discriminator: 2)
!2977 = !DILocation(line: 117, column: 36, scope: !2978)
!2978 = !DILexicalBlockFile(scope: !278, file: !1, discriminator: 3)
!2979 = !DILocation(line: 117, column: 17, scope: !2978)
!2980 = !DILocalVariable(name: "price", scope: !278, file: !1, line: 118, type: !13)
!2981 = !DILocation(line: 118, column: 11, scope: !278)
!2982 = !DILocation(line: 120, column: 6, scope: !2983)
!2983 = distinct !DILexicalBlock(scope: !278, file: !1, line: 120, column: 6)
!2984 = !DILocation(line: 120, column: 10, scope: !2983)
!2985 = !DILocation(line: 120, column: 6, scope: !278)
!2986 = !DILocation(line: 121, column: 53, scope: !2987)
!2987 = distinct !DILexicalBlock(scope: !2983, file: !1, line: 120, column: 28)
!2988 = !DILocation(line: 121, column: 11, scope: !2987)
!2989 = !DILocation(line: 121, column: 35, scope: !2987)
!2990 = !DILocation(line: 121, column: 18, scope: !2987)
!2991 = !DILocation(line: 121, column: 9, scope: !2987)
!2992 = !DILocation(line: 122, column: 2, scope: !2987)
!2993 = !DILocalVariable(name: "pos_slot", scope: !2994, file: !1, line: 123, type: !230)
!2994 = distinct !DILexicalBlock(scope: !2983, file: !1, line: 122, column: 9)
!2995 = !DILocation(line: 123, column: 18, scope: !2994)
!2996 = !DILocation(line: 123, column: 44, scope: !2994)
!2997 = !DILocation(line: 123, column: 29, scope: !2994)
!2998 = !DILocation(line: 124, column: 52, scope: !2994)
!2999 = !DILocation(line: 124, column: 11, scope: !2994)
!3000 = !DILocation(line: 124, column: 34, scope: !2994)
!3001 = !DILocation(line: 124, column: 18, scope: !2994)
!3002 = !DILocation(line: 125, column: 27, scope: !2994)
!3003 = !DILocation(line: 125, column: 31, scope: !2994)
!3004 = !DILocation(line: 125, column: 7, scope: !2994)
!3005 = !DILocation(line: 125, column: 14, scope: !2994)
!3006 = !DILocation(line: 125, column: 5, scope: !2994)
!3007 = !DILocation(line: 124, column: 9, scope: !2994)
!3008 = !DILocation(line: 128, column: 26, scope: !278)
!3009 = !DILocation(line: 128, column: 33, scope: !278)
!3010 = !DILocation(line: 128, column: 52, scope: !278)
!3011 = !DILocation(line: 128, column: 57, scope: !278)
!3012 = !DILocation(line: 128, column: 11, scope: !278)
!3013 = !DILocation(line: 128, column: 8, scope: !278)
!3014 = !DILocation(line: 130, column: 9, scope: !278)
!3015 = !DILocation(line: 130, column: 2, scope: !278)
!3016 = !DILocalVariable(name: "pos", arg: 1, scope: !281, file: !238, line: 126, type: !13)
!3017 = !DILocation(line: 126, column: 25, scope: !281)
!3018 = !DILocation(line: 128, column: 2, scope: !281)
!3019 = !DILocation(line: 128, column: 2, scope: !3020)
!3020 = !DILexicalBlockFile(scope: !281, file: !238, discriminator: 1)
!3021 = !DILocation(line: 128, column: 2, scope: !3022)
!3022 = !DILexicalBlockFile(scope: !281, file: !238, discriminator: 2)
!3023 = !DILocation(line: 128, column: 2, scope: !3024)
!3024 = !DILexicalBlockFile(scope: !281, file: !238, discriminator: 3)
!3025 = !DILocation(line: 130, column: 6, scope: !3026)
!3026 = distinct !DILexicalBlock(scope: !281, file: !238, line: 130, column: 6)
!3027 = !DILocation(line: 130, column: 10, scope: !3026)
!3028 = !DILocation(line: 130, column: 6, scope: !281)
!3029 = !DILocation(line: 131, column: 10, scope: !3026)
!3030 = !DILocation(line: 131, column: 3, scope: !3026)
!3031 = !DILocation(line: 133, column: 6, scope: !3032)
!3032 = distinct !DILexicalBlock(scope: !281, file: !238, line: 133, column: 6)
!3033 = !DILocation(line: 133, column: 10, scope: !3032)
!3034 = !DILocation(line: 133, column: 6, scope: !281)
!3035 = !DILocation(line: 134, column: 10, scope: !3032)
!3036 = !DILocation(line: 134, column: 3, scope: !3032)
!3037 = !DILocation(line: 136, column: 9, scope: !281)
!3038 = !DILocation(line: 136, column: 2, scope: !281)
!3039 = !DILocation(line: 137, column: 1, scope: !281)
!3040 = !DILocalVariable(name: "coder", arg: 1, scope: !287, file: !1, line: 104, type: !255)
!3041 = !DILocation(line: 104, column: 39, scope: !287)
!3042 = !DILocalVariable(name: "rep_index", arg: 2, scope: !287, file: !1, line: 104, type: !230)
!3043 = !DILocation(line: 104, column: 61, scope: !287)
!3044 = !DILocalVariable(name: "len", arg: 3, scope: !287, file: !1, line: 105, type: !230)
!3045 = !DILocation(line: 105, column: 18, scope: !287)
!3046 = !DILocalVariable(name: "state", arg: 4, scope: !287, file: !1, line: 105, type: !267)
!3047 = !DILocation(line: 105, column: 45, scope: !287)
!3048 = !DILocalVariable(name: "pos_state", arg: 5, scope: !287, file: !1, line: 106, type: !230)
!3049 = !DILocation(line: 106, column: 18, scope: !287)
!3050 = !DILocation(line: 108, column: 24, scope: !287)
!3051 = !DILocation(line: 108, column: 31, scope: !287)
!3052 = !DILocation(line: 108, column: 48, scope: !287)
!3053 = !DILocation(line: 108, column: 53, scope: !287)
!3054 = !DILocation(line: 108, column: 9, scope: !287)
!3055 = !DILocation(line: 109, column: 24, scope: !287)
!3056 = !DILocation(line: 109, column: 31, scope: !287)
!3057 = !DILocation(line: 109, column: 42, scope: !287)
!3058 = !DILocation(line: 109, column: 49, scope: !287)
!3059 = !DILocation(line: 109, column: 5, scope: !287)
!3060 = !DILocation(line: 109, column: 3, scope: !287)
!3061 = !DILocation(line: 108, column: 2, scope: !287)
